/*
 * BFSAccelerator.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: maltanar
 */

#include <iostream>
#include "BFSAccelerator.h"

using namespace std;

static const char * feStateNames[] = { "Idle", "ReadColLen", "ProcUpper",
		"ProcBoth", "Finished", "ResultDump" };

static const char * rgStateNames[] = { "sIdle", "sReqColLen", "sReqRowInd",
			"sReqDenVec", "sCheckFinished", "sFinished" };

inline unsigned int BFSBurstAlign(unsigned int base, unsigned int align) {
	if (base % align == 0)
		return base;
	else
		return base - (base % align) + align;
}

BFSAccelerator::BFSAccelerator() {
	m_inputVectorBits = 0;
}

void BFSAccelerator::setInterfaceRegs(unsigned int inputRegBaseAddr,
		unsigned int outputRegBaseAddr) {
	assert(inputRegBaseAddr != 0);
	assert(outputRegBaseAddr != 0);

	m_inputRegs = (volatile unsigned int *) inputRegBaseAddr;
	m_outputRegs = (volatile unsigned int *) outputRegBaseAddr;
}

BFSAccelerator::~BFSAccelerator() {
}

void BFSAccelerator::assignGraph(GraphMatrixData* graph,
		unsigned int * inputVectorBitArray) {
	assert(graph);
	// make sure we have enough BRAM storage for this graph
	assert(graph->rows <= BRAM_BIT_COUNT);
	//assert(inputVectorBitArray);

	m_graph = graph;
	m_inputVectorBits = inputVectorBitArray;

	// make sure the allocated input vector is aligned
	assert((unsigned int )m_inputVectorBits % INPVEC_ALIGN == 0);
	// check alignment for other input vectors
	assert((unsigned int )(graph->colPtr) % COLPTR_ALIGN == 0);
	assert((unsigned int )(graph->rowInd) % ROWIND_ALIGN == 0);

	setupFrontend();
	setupBackend();
}

void BFSAccelerator::start() {
	assert(m_inputRegs[rgStatState] == beStateIdle);
	assert(m_inputRegs[feStatState] == feStateIdle);
	// make sure frontend and backend are set up
	assignGraph(m_graph, m_inputVectorBits);

	// start backend
	volatile char * ctrlBase = (volatile char *) &(m_outputRegs[rgControl]);
	ctrlBase[0] = 1;
	// start frontend
	m_outputRegs[feControl] = 1;
}

bool BFSAccelerator::isFinished() {
	bool frontendFinished = (m_inputRegs[feStatState] == feStateFinished);
	//bool backendFinished  = (m_inputRegs[rgStatState] == beStateFinished);

	return /*backendFinished && */frontendFinished;
}

void BFSAccelerator::setupBackend() {
	// make sure backend is not running prior to setup
	assert(m_inputRegs[rgStatState] == beStateIdle);

	// FIFO full thresholds
	// TODO configure these in a smarter way -- depends on FIFO size, burst size
	// as well as properties of the graph and current memory latency...
	// IMPORTANT! the FIFOs are NOT *guaranteed* not to exceed these thresholds
	// due to the latency in receiving the feedback, so make sure the FIFOs are big
	// enough.
	setThresholds(64, 512, 1);

	// input data pointers
	m_outputRegs[rgCtrlColLenPtr] = (unsigned int) m_graph->colPtr;
	m_outputRegs[rgCtrlRowIndPtr] = (unsigned int) m_graph->rowInd;
	m_outputRegs[rgCtrlDVPtr] = (unsigned int) m_inputVectorBits;

	// align counts to match the backend burst requirements
	// excess data is discarded during reset
	// we use cols+1 since there are m+1 pointers in the colPtr array
	m_outputRegs[rgCtrlColCount] = BFSBurstAlign(m_graph->cols + 1,
			COLPTR_ALIGN);
	m_outputRegs[rgCtrlNZCount] = BFSBurstAlign(m_graph->nz, ROWIND_ALIGN);
}

void BFSAccelerator::setupFrontend() {
	// the frontend needs the column and row count
	m_outputRegs[feCtrlColCount] = m_graph->cols;
	m_outputRegs[feCtrlRowCount] = m_graph->rows;
}

void BFSAccelerator::setBRAMAccessMux(bool bEnableSwCtrl) {
	// depending on parameter value,
	// give control of BRAM port A to software (true) or to accelerator (false)
	// set highest bit of rg control register
	volatile char * ctrlBase = (volatile char *) &(m_outputRegs[rgControl]);
	if(bEnableSwCtrl) {
		//cout << "Software controls BRAM portA" << endl;
		ctrlBase[1] = 0;
	} else {
		//cout << "PE controls BRAM port A" << endl;
		ctrlBase[1] = 1;
	}
}

void BFSAccelerator::printFrontendProfile() {
	// print profile information from StateProfiler
	// we use the BRAM address output also to select state

	cout << "Frontend profile stats: " << endl;
	for (unsigned int i = 0; i <= feStateResDump; i++) {
		m_outputRegs[ctlBRAMAddr] = i;
		cout << feStateNames[i] << ": " << m_inputRegs[statFEProfile] << endl;
	}

	m_outputRegs[ctlBRAMAddr] = feStateProcessUpper;
	unsigned int procCycles = m_inputRegs[statFEProfile];

	m_outputRegs[ctlBRAMAddr] = feStateProcessBoth;
	procCycles += m_inputRegs[statFEProfile];

	unsigned int procMinCycles = (m_graph->nz) / 2 + m_graph->cols;
	cout << "Proc efficiency: " << (float) procMinCycles / (float) procCycles
			<< endl;

	m_outputRegs[ctlBRAMAddr] = feStateReadColLen;
	unsigned int colLenReadCycles = m_inputRegs[statFEProfile];
	cout << "ReadColLen efficiency: "
			<< (float) m_graph->cols / (float) colLenReadCycles << endl;

	unsigned int totalCycles = colLenReadCycles + procCycles;
	unsigned int workSize = m_graph->nz * 4 + (m_graph->cols + 1) * 4
			+ m_graph->cols / 8;
	cout << "Bandwidth: " << (float) workSize / (float) totalCycles
			<< " bytes/cycle" << endl;
}

void BFSAccelerator::startLevelUpdate(unsigned int level, DistVecElem * distVecBase) {
	assert(m_inputRegs[rgStatState] == beStateIdle);
	assert(m_inputRegs[feStatState] == feStateIdle);
	assert(m_graph->startingRow % 64 == 0);
	assert((unsigned int)distVecBase % 4 == 0);

	// make sure accelerator has the BRAM access mux
	setBRAMAccessMux(false);

	// set threshold regs of collen and rowind channels to zero,
	// only enable dense vector channel with good throughput
	// TODO the backend will never "finish" because of this way of doing this;
	// add channel enables in hardware
	setThresholds(0, 0, 512);

	// modify the read channel to generate only portion of inp.vec we are
	// interested in
	m_outputRegs[rgCtrlColCount] = BFSBurstAlign(m_graph->rows, COLPTR_ALIGN);
	m_outputRegs[rgCtrlDVPtr] = (unsigned int) &(m_inputVectorBits[m_graph->startingRow/32]);
	m_outputRegs[rgCtrlInpVecWritePtr] = (unsigned int) &(m_inputVectorBits[m_graph->startingRow/32]);

	// set up current level and distance vector base for this PE
	m_outputRegs[rgCtrlCurrentLevel] = level;
	m_outputRegs[rgCtrlDistVecBase] = (unsigned int) &(distVecBase[m_graph->startingRow]);


	// set up and start frontend in result dump mode
	// control word's upper 16 bits are number of 8-byte words to dump from BRAM
	unsigned short wordCount = (unsigned short) BFSBurstAlign(
			m_graph->rows / 64, 2);
	// bit 1 is enable result dump & level generation, and lowest bit is start
	m_outputRegs[feControl] = (wordCount << 16) | 3;

	// start the backend - enable write channel and dense vector read channel
	volatile char * ctrlBase = (volatile char *) &(m_outputRegs[rgControl]);
	ctrlBase[0] = 1;

}

bool BFSAccelerator::isFinishedLevelUpdate() {
	// checking for whether level update is finished is a bit tricky
	// first, check whether frontend is finished -- no way level update is finished
	// without the frontend being finished
	if(m_inputRegs[feStatState] != feStateFinished) {
		//cout << "frontend not finished: " <<  m_inputRegs[feStatUpdateCount] << " " << m_inputRegs[rgStatWriteCount] << " " << m_inputRegs[rgStatDistVecUpdateCount] << endl;
		return false;
	}

	//cout << "frontend finished, updates = " <<  m_inputRegs[feStatUpdateCount] << endl;

	// next, check whether input vector update operation is finished
	unsigned short wordCount = (unsigned short) BFSBurstAlign(m_graph->rows/64, 2);
	if(m_inputRegs[rgStatWriteCount] != wordCount) {
		//cout << "input update not completed: " << wordCount << " " << m_inputRegs[rgStatWriteCount] << endl;
		return false;
	}

	//cout << "input update completed: " << wordCount << " " << m_inputRegs[rgStatWriteCount] << endl;

	// finally, check whether dist.vec write count and update count from frontend match
	volatile unsigned int frontendUpdates = m_inputRegs[feStatUpdateCount];
	volatile unsigned int backendUpdates = m_inputRegs[rgStatDistVecUpdateCount];
	if(frontendUpdates != backendUpdates)
		return false;

	//cout << "level update OK! " << frontendUpdates << " " << backendUpdates << endl;

	return true;
}

void BFSAccelerator::setThresholds(unsigned int clThres, unsigned int riThres,
		unsigned int dvThres) {
	const unsigned int thresMask = 0x000003FF;
	unsigned int thres = 0;
	thres |= (clThres & thresMask);
	thres |= (riThres & thresMask) << 10;
	thres |= (dvThres & thresMask) << 20;

	m_outputRegs[ctlThresholds] = thres;
}

void BFSAccelerator::resetAccelerator() {
	// reset FIFOs and everything between backend-frontend via I/O regs
	// to ensure all stale data after a BFS step is removed
	volatile char * ctrlBase = (volatile char *) &(m_outputRegs[rgControl]);
	ctrlBase[3] = 0x80;
	ctrlBase[3] = 0;
}

void BFSAccelerator::writeBRAMBit(unsigned int addr, unsigned int data) {
	m_outputRegs[ctlBRAMAddr] = addr;
	m_outputRegs[ctlBRAMDataOut] = data;
	m_outputRegs[ctlBRAMWrEn] = 1;
	m_outputRegs[ctlBRAMWrEn] = 0;
}

void BFSAccelerator::clearBRAM() {
	for (unsigned int i = 0; i < BRAM_BIT_COUNT; i++) {
		writeBRAMBit(i, 0);
	}
}

void BFSAccelerator::deinit() {
	// make sure frontend is finished
	assert(m_inputRegs[feStatState] == feStateFinished);
	// flush FIFOs until backend can finish
	//assert(m_inputRegs[rgStatState] == beStateFinished);

	// allow frontend and backend to go back to idle
	m_outputRegs[feControl] = 0;
	volatile char * ctrlBase = (volatile char *) &(m_outputRegs[rgControl]);
	ctrlBase[0] = 0;
}

void BFSAccelerator::printAcceleratorStats() {
	cout << "Accelerator stats" << endl;
	cout << "=================================" << endl;
	cout << "Processed columns: " << m_inputRegs[feStatColCount] << endl;
	cout << "Processed nonzeroes: " << m_inputRegs[feStatNZCount] << endl;
	cout << "Level updates (frontend): " << m_inputRegs[feStatUpdateCount] << endl;
	cout << "Input vector writes (backend): " << m_inputRegs[rgStatWriteCount] << endl;
	cout << "Level updates (backend): " << m_inputRegs[rgStatDistVecUpdateCount] << endl;
}

void BFSAccelerator::printFIFODataCounts() {
	cout << "FIFO data counts" << endl;
	cout << "=================================" << endl;
	cout << "ColPtr FIFO: " << m_inputRegs[statColPtrFIFODataCount] << endl;
	cout << "RowInd FIFO: " << m_inputRegs[statRowIndFIFODataCount] << endl;
	cout << "DenVec FIFO: " << m_inputRegs[statDenVecFIFODataCount] << endl;
}

void BFSAccelerator::printAcceleratorState() {
	cout << "Frontend state: " << feStateNames[m_inputRegs[feStatState]] << endl;
	cout << "Backend state: " << rgStateNames[m_inputRegs[rgStatState]] << endl;
	cout << "Backend read response: " << m_inputRegs[rgStatRResp] << endl;
	cout << "Backenr write state: " << m_inputRegs[rgStatWriteState] << endl;
}

unsigned int BFSAccelerator::readBRAMWord(unsigned int addr) {
	m_outputRegs[ctlBRAMWrEn] = 0;
	m_outputRegs[ctlBRAMAddr] = addr * 32;// due to 32r1w port; use finest granularity
	return m_inputRegs[ctlBRAMDataIn];
}

void BFSAccelerator::printOutputVector() {
	// find locations of 1-bits in the BRAM and print them out


	unsigned int fullCount = 0;
	for (unsigned int i = 0; i < m_graph->rows; i++) {
		unsigned int data = readBRAMWord(i/32);
		if (((data>>(i%32)) & 0x1) == 1) {
			cout << "BRAM[" << i << "] = " << hex << data << dec << " (located at addr " << (i/32) << ")" << endl;
			fullCount++;
		}
	}

	if (!fullCount)
		cout << "Result vector is completely empty" << endl;
	else
		cout << "Result vector has " << fullCount << " visited locations" << endl;
}
