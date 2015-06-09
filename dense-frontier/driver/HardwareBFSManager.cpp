#include "HardwareBFSManager.h"
#include <string.h>
#include <iostream>

using namespace std;

HardwareBFSManager::HardwareBFSManager(unsigned int * inputRegs,
		unsigned int * outputRegs) {
	m_graphMan = 0;
	m_bfsDistance = 0;
	m_distanceVector = 0;
	m_inputVector = 0;
	m_inputVectorWordCount = 0;
	m_deallocateBitmap = false;
	m_identityMatrix = 0;

	iForEachPE(
			m_busy[i] = false; m_assignedPartition[i]= 0; m_pe[i].setInterfaceRegs(inputRegs[i], outputRegs[i]););
}

HardwareBFSManager::~HardwareBFSManager() {
	// current distanceVector is statically allocated
	/*if (m_distanceVector)
	 delete[] m_distanceVector;*/

	if (m_deallocateBitmap)
		delete[] m_inputVector;

	if (m_identityMatrix)
		freeIdentityMatrix();
}

void HardwareBFSManager::setGraph(GraphManager* graphMan) {
	assert(graphMan);
	assert(m_graphMan == 0);
	//assert(graphMan->getColCount() < 3*64*1024*8);	// check that inputVector fits into OCM

	m_graphMan = graphMan;

	m_inputVectorWordCount = 1 + (graphMan->getRowCount() / 32);
	m_inputVector = new unsigned int[m_inputVectorWordCount];
	m_deallocateBitmap = true;
	//m_inputVector = (unsigned int *) 0x00000008;
	m_distanceVector = (DistVecElem *) RESVEC_BASE;

	createIdentityMatrix();
}

BFSAccelerator* HardwareBFSManager::getPE(int i) {
	return &(m_pe[i]);
}

void HardwareBFSManager::initFromBitmap(unsigned int* bitmap) {
	// TODO initialize inputVector and distanceVector from src
	// nice for taking over from the CPU
	// not implemented yet
	if (m_deallocateBitmap)
		delete[] m_inputVector;
	m_deallocateBitmap = false;
	m_inputVector = bitmap;

	//
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

void HardwareBFSManager::assignPartition(unsigned int partitionInd, int peInd) {
	assert(peInd < BFS_PE_COUNT);
	assert(partitionInd < m_graphMan->getPartitionCount());

	// assign the given graph partition to PE and initialize its
	// result memory to corresponding part from the inputVector
	m_assignedPartition[peInd] = m_graphMan->getPartitionData(partitionInd);

	BFSAccelerator * targetPE = getPE(peInd);
	// set up pointers to data in the accelerator
	targetPE->assignGraph(m_assignedPartition[peInd], m_inputVector);

	/*
	 // initialize result memory of the accelerator
	 // we'll initialize the result BRAM in SW; enable access mux
	 targetPE->setBRAMAccessMux(true);
	 unsigned int rowCount = m_assignedPartition[peInd]->rows;
	 unsigned int rowStart = m_assignedPartition[peInd]->startingRow;
	 //unsigned int writeCount = 0;
	 for (unsigned int i = 0; i < rowCount; i++) {
	 // if position visited, set bit in BRAM
	 if (m_distanceVector[rowStart + i] != -1) {
	 targetPE->writeBRAMBit(i, 1);
	 //writeCount++;
	 }
	 }
	 //std::cout << "PE " << peInd << " wrote " << writeCount << " elements to BRAM" << std::endl;
	 *
	 */
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
	if (inpVecBit != 0)
		m_inputVector[inpVecReadAddr] = inpVecWord;

	return updateCount;
}

void HardwareBFSManager::setNextDistance(unsigned int dist) {
	m_bfsDistance = dist;
}

void HardwareBFSManager::waitAllPEsFinished() {
	unsigned int patience[BFS_PE_COUNT];
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
				if(m_pe[i].isFinished()) {
				// don't need to wait on this anymore
				//std::cout << "PE " << i << " finished" << std::endl;
				m_busy[i] = false; waitedPECount--; } else {
				// not finished yet, our patience is growing thin..
				patience[i]--;
				// don't wait after no more patience left
				if(patience[i] == 0) { std::cout << "PE " << i << " timed out!" << std::endl; m_pe[i].printAcceleratorStats(); m_pe[i].printAcceleratorState(); m_pe[i].printFIFODataCounts(); waitedPECount--; } } });
	}

}

void HardwareBFSManager::startAll() {
	// give BRAM acccess, start all PEs and update the m_busy data
	iForEachPE(
			m_pe[i].setBRAMAccessMux(false); m_pe[i].start(); m_busy[i] = true;);
}

void HardwareBFSManager::printDistanceVector(bool verbose) {
	unsigned int visited = 0;
	for (unsigned int i = 0; i < m_graphMan->getRowCount(); i++)
		if (m_distanceVector[i] != -1) {
			if (verbose)
				std::cout << "distance[" << i << "] = " << m_distanceVector[i]
						<< std::endl;
			visited++;
		}

	std::cout << "Total visited = " << visited << std::endl;
}

unsigned int HardwareBFSManager::updateResults_Software() {
	unsigned int updateCount = 0;

	iForEachPE(updateCount += copyPEResultToDRAM(i)
	;);

	setNextDistance(m_bfsDistance + 1);

	return updateCount;
}

void HardwareBFSManager::clearAllResultVectors() {
	VERBOSE(std::cout << "Clearing result vectors..." << std::endl);
	iForEachPE(m_pe[i].setBRAMAccessMux(true); m_pe[i].clearBRAM()
	;);
}

void HardwareBFSManager::verifyAccelBRAMs() {
	// compare the content of accelerator BRAMs against the input vector

	iForEachPE(
		// enable software access to PE BRAMs
		m_pe[i].setBRAMAccessMux(true);
		unsigned int rowCount = m_assignedPartition[i]->rows;
		unsigned int rowStart = m_assignedPartition[i]->startingRow;

		for (unsigned int x = 0; x < rowCount; x++) {
			unsigned int inpVecWord = m_inputVector[(x + rowStart) / 32];
			unsigned int bramWord = m_pe[i].readBRAMWord(x / 32);

			bool inpVecBitSet = ((inpVecWord >> ((x + rowStart) % 32)) & 0x1)
					== 1;
			bool bramBitSet = ((bramWord >> (x % 32)) & 0x1) == 1;
			if (bramBitSet != inpVecBitSet)
				std::cout << "Bit for PE " << i << " location " << x
						<< " differ" << std::endl;
		}
	);

	std::cout << "BRAM verification complete" << std::endl;
}

void HardwareBFSManager::initAccelBRAMs() {
	// upon a CPU -> FPGA switch, we need to initialize the result memories of each accelerator
	// with its corresponding version of the input vector (= bitmap)
	// we do this by setting up an identity matrix and letting the accelerator run on this, which results
	// in the result vector being initialized to the input vector

	// assign the identity matrix to each PE, with a different starting location on the input vector
	iForEachPE(
			unsigned int startingRow = m_assignedPartition[i]->startingRow;
		unsigned int * denseVectorPortion = &(m_inputVector[startingRow/32]);
		m_pe[i].assignGraph(m_identityMatrix, denseVectorPortion););

	// execute a single step, no level updates required (we are just updating the BRAMs of each accel)
	step(false);
	resetAll();

	// restore original graph partition assignments after initialization
	iForEachPE(m_pe[i].assignGraph(m_assignedPartition[i], m_inputVector)
	;);
}

void HardwareBFSManager::createIdentityMatrix() {
	// identity matrix needs to be only as large as the largest partition's row count
	unsigned int matrixDim = m_graphMan->getLargestPartitionRowCount();
	m_identityMatrix = new GraphMatrixData;
	m_identityMatrix->cols = matrixDim;
	m_identityMatrix->rows = matrixDim;
	m_identityMatrix->nz = matrixDim;
	m_identityMatrix->startingRow = 0;
	m_identityMatrix->colPtr = new unsigned int[matrixDim + 1];
	m_identityMatrix->rowInd = new unsigned int[matrixDim];
	// set up identity matrix elements
	for (unsigned int i = 0; i < matrixDim; i++) {
		m_identityMatrix->colPtr[i] = i;
		m_identityMatrix->rowInd[i] = i;
	}
	m_identityMatrix->colPtr[matrixDim] = matrixDim;
}

void HardwareBFSManager::printInputVector() {
	std::cout << "Input vector dump" << endl;
	unsigned int visited = 0;
	for (unsigned int i = 0; i < m_graphMan->getRowCount(); i++) {
		unsigned int inpVecWord = m_inputVector[i/32];
		if((inpVecWord >> (i%32)) & 0x1 == 1) {
			cout << "inpvec " << i << endl;
			visited++;
		}
	}
	cout << "total visited = " << visited << endl;
}

void HardwareBFSManager::freeIdentityMatrix() {
	delete[] m_identityMatrix->colPtr;
	delete[] m_identityMatrix->rowInd;
	delete m_identityMatrix;
}

void HardwareBFSManager::deinitAll() {
	// call deinit on all PEs
	iForEachPE(m_pe[i].deinit()
	;);
}

void HardwareBFSManager::step(bool printStats) {
	// perform one step of BFS and keep statistics
	resetAll();
	startAll();
	waitAllPEsFinished();
	deinitAll();
	if (printStats)
		iForEachPE(m_pe[i].printFrontendProfile()
		;);
}

unsigned int HardwareBFSManager::updateResults_Hardware() {

	bool busy[BFS_PE_COUNT];
	resetAll();
	iForEachPE(
			m_pe[i].startLevelUpdate(m_bfsDistance, m_distanceVector); busy[i]=true;);

	unsigned int finishCount = 0;
	unsigned int updateCount = 0;

	while (finishCount != hardwarePECount) {
		iForEachPE(if (busy[i] && m_pe[i].isFinishedLevelUpdate()) {
			busy[i] = false
			;
			finishCount++
			;
			updateCount += m_pe[i].getLevelUpdateCount()
			;
			m_pe[i].deinit()
			;
		}

		);
	}

	setNextDistance(m_bfsDistance + 1);

	return updateCount;
}

void HardwareBFSManager::resetAll() {
	iForEachPE(m_pe[i].resetAccelerator()
	;);
}

