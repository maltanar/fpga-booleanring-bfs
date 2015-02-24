#include "xil_cache.h"
#include "HardwareBFSManager.h"
#include <string.h>
#include <iostream>


HardwareBFSManager::HardwareBFSManager(unsigned int * inputRegs,
		unsigned int * outputRegs) {
	m_graphMan = 0;
	m_bfsDistance = 0;
	m_distanceVector = 0;
	m_inputVector = 0;
	m_inputVectorWordCount = 0;

	iForEachPE(
			m_busy[i] = false; m_assignedPartition[i]= 0; m_pe[i].setInterfaceRegs(inputRegs[i], outputRegs[i]););
}

HardwareBFSManager::~HardwareBFSManager() {
	// current distanceVector is statically allocated
	/*if (m_distanceVector)
		delete[] m_distanceVector;*/

	if (m_inputVector)
		delete[] m_inputVector;
}

void HardwareBFSManager::setGraph(GraphManager* graphMan) {
	assert(graphMan);
	assert(m_graphMan == 0);

	m_graphMan = graphMan;

	m_inputVectorWordCount = 1 + (graphMan->getRowCount() / 32);
	m_inputVector = new unsigned int[m_inputVectorWordCount];
	m_distanceVector = (int *) RESVEC_BASE;
}

BFSAccelerator* HardwareBFSManager::getPE(int i) {
	return &(m_pe[i]);
}

void HardwareBFSManager::initVector(unsigned int* src) {
	// TODO initialize inputVector and distanceVector from src
	// nice for taking over from the CPU
	// not implemented yet
	assert(0);
}

void HardwareBFSManager::initVectorSingleRoot(unsigned int root) {
	// set all input vector elements to 0
	memset(m_inputVector, 0, m_inputVectorWordCount * 4);
	// set all distance vector elements to -1 (untouched / infinite distance)
	memset(m_distanceVector, -1, m_graphMan->getRowCount() * 4);

	// set root distance to 0, and mark as visited in the inputVector
	m_distanceVector[root] = 0;
	m_inputVector[root / 32] = 1 << (root % 32);
}

inline unsigned int round_div(unsigned int dividend, unsigned int divisor) {
	return (dividend + (divisor / 2)) / divisor;
}

void HardwareBFSManager::assignPartition(int partitionInd, int peInd) {
	assert(peInd < BFS_PE_COUNT);
	assert(partitionInd < m_graphMan->getPartitionCount());

	// assign the given graph partition to PE and initialize its
	// result memory to corresponding part from the inputVector
	m_assignedPartition[peInd] = m_graphMan->getPartitionData(partitionInd);

	BFSAccelerator * targetPE = getPE(peInd);
	// we'll initialize the result BRAM in SW; enable access mux
	targetPE->setBRAMAccessMux(true);
	targetPE->clearBRAM();
	// set up pointers to data in the accelerator
	targetPE->assignGraph(m_assignedPartition[peInd], m_inputVector);

	// initialize result memory of the accelerator
	unsigned int rowCount = m_assignedPartition[peInd]->rows;
	unsigned int rowStart = m_assignedPartition[peInd]->startingRow;
	for (unsigned int i = 0; i < rowCount; i++) {
		// if position visited, set bit in BRAM
		if (m_distanceVector[rowStart + i] != -1) {
			targetPE->writeBRAMBit(i, 1);

		}
	}
}

unsigned int HardwareBFSManager::copyPEResultToDRAM(int peInd) {
	// update inputVector and distanceVector from the result memory of the given PE,
	// paying attention to which graph partition it was assigned to calculate the base
	unsigned int updateCount = 0;

	unsigned int rowCount = m_assignedPartition[peInd]->rows;
	unsigned int rowStart = m_assignedPartition[peInd]->startingRow;

	unsigned int bramWord = 0, bramReadAddr = 0;
	unsigned int inpVecWord = 0, inpVecReadAddr = 0, inpVecBit = 0;

	// enable SW access to read from BRAM
	m_pe[peInd].setBRAMAccessMux(true);

	bramWord = m_pe[peInd].readBRAMWord(bramReadAddr);
	inpVecReadAddr = rowStart / 32;
	inpVecBit = rowStart % 32;
	inpVecWord = m_inputVector[inpVecReadAddr];

	for (unsigned int row = 0; row < rowCount; row++) {
		bool inpVecVisited = ((inpVecWord & (1 << inpVecBit)) != 0);
		bool resVecVisited = ((bramWord & 0x1) != 0);

		// should never happen: visited in input, unvisited in output
		assert(!(inpVecVisited && !resVecVisited));

		// unvisited in input, visited in output -- in frontier
		if (resVecVisited && !inpVecVisited) {
			// write value to distanceVector
			m_distanceVector[rowStart + row] = m_bfsDistance;
			// set bit in inputVector for the next iteration
			inpVecWord = inpVecWord | (1 << inpVecBit);
			updateCount++;
		}

		// read new word from BRAM at boundary
		if (row % 32 == 31) {
			bramReadAddr++;
			bramWord = m_pe[peInd].readBRAMWord(bramReadAddr);
		} else
			// right shift BRAM word
			bramWord = bramWord >> 1;

		// inpvec at boundary
		if (inpVecBit == 31) {
			// flush updated word
			m_inputVector[inpVecReadAddr] = inpVecWord;
			inpVecReadAddr++;
			inpVecBit = 0;
			// read new (old) word
			inpVecWord = m_inputVector[inpVecReadAddr];
		} else
			// increment examined inp.vec bit position
			inpVecBit = inpVecBit + 1;
	}
	// flush inpVecWord at the end if needed
	if(inpVecBit != 0)
		m_inputVector[inpVecReadAddr] = inpVecWord;

	return updateCount;
}

void HardwareBFSManager::setNextDistance(unsigned int dist) {
	m_bfsDistance = dist;
}

void HardwareBFSManager::waitAllPEsFinished() {
	unsigned int patience[BFS_PE_COUNT];
	// initialize timeouts for each PE
	iForEachPE(patience[i] = 10000000; );
	int waitedPECount = BFS_PE_COUNT;
	// while we are still waiting on some PEs
	while(waitedPECount > 0) {
		iForEachPE(
			// if we are waiting on this PE
			if(m_busy[i] && patience[i] > 0) {
				// check if PE signalling finished
				if(m_pe[i].isFinished()) {
					// don't need to wait on this anymore
					std::cout << "PE " << i << " finished" << std::endl;
					m_busy[i] = false;
					waitedPECount--;
				}
				else {
					// not finished yet, our patience is growing thin..
					patience[i]--;
					// don't wait after no more patience left
					if(patience[i] == 0) {
						std::cout << "PE " << i << " timed out!" << std::endl;
						m_pe[i].printFrontendStats();
						m_pe[i].printAcceleratorState();
						m_pe[i].printFIFODataCounts();
						waitedPECount--;
					}
				}
			}
			);
	}

}

void HardwareBFSManager::startAll() {
	// give BRAM acccess, start all PEs and update the m_busy data
	iForEachPE(m_pe[i].setBRAMAccessMux(false); m_pe[i].start(); m_busy[i] = true;);
}

void HardwareBFSManager::printDistanceVector() {
	for(unsigned int i = 0; i < m_graphMan->getRowCount(); i++)
		if(m_distanceVector[i] != -1)
			std::cout << "distance[" << i << "] = " << m_distanceVector[i] << std::endl;
}

unsigned int HardwareBFSManager::updateResults() {
	unsigned int updateCount = 0;
	Xil_DCacheEnable();
	iForEachPE(updateCount += copyPEResultToDRAM(i););
	Xil_DCacheDisable();

	setNextDistance(m_bfsDistance + 1);

	return updateCount;
}

void HardwareBFSManager::deinitAll() {
	// call deinit on all PEs
	iForEachPE(m_pe[i].deinit(););
}

void HardwareBFSManager::step() {
	// perform one step of BFS and keep statistics
	startAll();
	waitAllPEsFinished();
	deinitAll();
}
