#include "HardwareBFSManager.h"
#include <string.h>
#include <iostream>

using namespace std;

HardwareBFSManager::HardwareBFSManager(unsigned int * baseAddrs) {
	m_graphMan = 0;
	m_bfsDistance = 0;
	m_distanceVector = 0;
	m_lastFrontierSize = 0;

	iForEachPE(
			m_pe[i] = new BFSAccelerator(i, baseAddrs[i]); m_busy[i] = false; m_assignedPartition[i]= 0;);
	VERBOSE(cout << "HW accels initialized" << endl);
}

HardwareBFSManager::~HardwareBFSManager() {
	iForEachPE(delete m_pe[i]
	;);
}

void HardwareBFSManager::setGraph(GraphManager* graphMan) {
	assert(graphMan);
	assert(m_graphMan == 0);

	m_graphMan = graphMan;

	m_distanceVector = (DistVecElem *) RESVEC_BASE;
}

BFSAccelerator* HardwareBFSManager::getPE(int i) {
	return m_pe[i];
}

void HardwareBFSManager::initVector(DistVecElem * src, unsigned int count) {
	// TODO initialize inputVector and distanceVector from src
	// nice for taking over from the CPU
	// not implemented yet
	assert(0);
	m_lastFrontierSize = count;
}

void HardwareBFSManager::initVectorSingleRoot(unsigned int root) {
	assert(m_graphMan);

	// set all distance vector elements to -1 (untouched / infinite distance)
	memset(m_distanceVector, (DistVecElem) -1,
			m_graphMan->getRowCount() * sizeof(DistVecElem));

	// set root distance to 0, and mark as visited in the inputVector
	m_distanceVector[root] = 0;

	// create initializer for the corresponding PE
	// TODO this assumes 1-1 mapping between PEs and partitions
	unsigned int targetPE = 4;
	iForEachPE(
			GraphMatrixData * part = m_graphMan->getPartitionData(i); unsigned int rowUpperBound = part->startingRow + part->rows; if(part->startingRow <= root && root < rowUpperBound) { targetPE = i; break; });

	assert(targetPE != 4);

	unsigned int * visitedInds = new unsigned int[1];
	// map root index to PE's row space
	visitedInds[0] = root % m_graphMan->getPartitionData(targetPE)->rows;
	getPE(targetPE)->setVisitedStatus(visitedInds, 1);
	delete[] visitedInds;

	// singe-element frontier
	m_lastFrontierSize = 1;
}

inline unsigned int round_div(unsigned int dividend, unsigned int divisor) {
	return (dividend + (divisor / 2)) / divisor;
}

void HardwareBFSManager::assignPartition(unsigned int partitionInd,
		unsigned int peInd) {
	assert(peInd < hardwarePECount);
	assert(partitionInd < m_graphMan->getPartitionCount());

	// assign the given graph partition to PE and initialize its
	// result memory to corresponding part from the inputVector
	m_assignedPartition[peInd] = m_graphMan->getPartitionData(partitionInd);

	BFSAccelerator * targetPE = getPE(peInd);
	// set up pointers to data in the accelerator
	targetPE->initialize(m_assignedPartition[peInd], m_distanceVector, 0, 0);
}

void HardwareBFSManager::setDistance(unsigned int dist) {
	m_bfsDistance = dist;
}

void HardwareBFSManager::waitAllPEsFinished() {
	unsigned int patience[4];
	// initialize timeouts for each PE
	iForEachPE(patience[i] = 1000000
	; );
	int waitedPECount = hardwarePECount;
	// while we are still waiting on some PEs
	while (waitedPECount > 0) {
		iForEachPE(
		// if we are waiting on this PE
				if(m_busy[i] && patience[i] > 0) {
				// check if PE signalling finished
				if(m_pe[i]->isFinished()) {
				// don't need to wait on this anymore
				//std::cout << "PE " << i << " finished" << std::endl;
				m_pe[i]->saveProfiles(); m_busy[i] = false; waitedPECount--; } else {
				// not finished yet, our patience is growing thin..
				patience[i]--;
				// don't wait after no more patience left
				if(patience[i] == 0) { m_pe[i]->handleTimeout("regular"); waitedPECount--; } } });
	}

}

void HardwareBFSManager::startAll() {
	// set last frontier size, start all PEs and update the m_busy data
	iForEachPE(
			m_pe[i]->start(m_bfsDistance, m_lastFrontierSize); m_busy[i] = true;);
}

void HardwareBFSManager::printDistanceVector() {
	unsigned int cnt=0;
	unsigned int bins[7] = {0,0,0,0,0,0,0};
	for (unsigned int i = 0; i < m_graphMan->getRowCount(); i++)
		if (m_distanceVector[i] != -1) {
			cnt++;
			bins[m_distanceVector[i]]++;
			/*std::cout << "distance[" << i << "] = " << m_distanceVector[i]
								<< std::endl;*/
		}
	cout << "total visited = " << cnt << endl;
	cout << "bins: ";
	for(int i=0; i<7;i++)
		cout << bins[i] << " ";
	cout << endl;
}

unsigned int HardwareBFSManager::getMaxPECycles() {
	unsigned int maxCycles = 0;
	// since the PEs run in parallel, the cost of a step operation
	// is the maximum of all PE's step operation
	iForEachPE(
			unsigned int cycles = m_pe[i]->getLastRunDuration(); if(cycles > maxCycles) maxCycles = cycles;);

	return maxCycles;
}

void HardwareBFSManager::printProfiles() {
	iForEachPE(
			m_pe[i]->printBackendProfile(); m_pe[i]->printFrontendProfile(); m_pe[i]->printNeighborFetchProfile();
			cout << i << " edges " << m_pe[i]->getTraversedEdges() << endl;
	);
}

void HardwareBFSManager::deinitAll() {
	// call deinit on all PEs
	iForEachPE(m_pe[i]->deinit()
	;);
}

void HardwareBFSManager::step() {
	// perform one step of BFS and keep statistics
	//resetAll();
	startAll();
	waitAllPEsFinished();
	deinitAll();
}

unsigned int HardwareBFSManager::levelGeneration() {
	unsigned int patience[4];

	unsigned int finishCount = 0;
	unsigned int updateCount = 0;

	iForEachPE(m_pe[i]->startLevelUpdate(m_bfsDistance+1); m_busy[i]=true;);

	// initialize timeouts for each PE
	iForEachPE(patience[i] = 1000000
	; );
	int waitedPECount = hardwarePECount;
	// while we are still waiting on some PEs
	while (waitedPECount > 0) {
		iForEachPE(
		// if we are waiting on this PE
				if(m_busy[i] && patience[i] > 0) {
				// check if PE signalling finished
				if(m_pe[i]->isFinishedLevelUpdate()) {
				// don't need to wait on this anymore
				//std::cout << "PE " << i << " finished" << std::endl;
				m_busy[i] = false; waitedPECount--; updateCount += m_pe[i]->getLastFrontierSize(); m_pe[i]->deinit(); } else {
				// not finished yet, our patience is growing thin..
				patience[i]--;
				// don't wait after no more patience left
				if(patience[i] == 0) { m_pe[i]->handleTimeout("levgen"); waitedPECount--; } } });
	}

	setDistance(m_bfsDistance + 1);

	m_lastFrontierSize = updateCount;

	return updateCount;
}

void HardwareBFSManager::resetAll() {
	iForEachPE(m_pe[i]->resetAccelerator()
	;);
}

