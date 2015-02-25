/*
 * BFSAccelerator.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: maltanar
 */

#include <iostream>
#include "BFSAccelerator.h"

using namespace std;

static const char * feStateNames[] = {"Idle", "ReadColLen", "ProcUpper", "ProcBoth", "Finished"};


inline unsigned int BFSBurstAlign(unsigned int base, unsigned int align)
{
	if(base % align == 0)
		return base;
	else
		return base-(base%align)+align;
}

BFSAccelerator::BFSAccelerator() {
	m_inputVectorBits = 0;
}

void BFSAccelerator::setInterfaceRegs(unsigned int inputRegBaseAddr, unsigned int outputRegBaseAddr)
{
	assert(inputRegBaseAddr != 0);
	assert(outputRegBaseAddr != 0);

	m_inputRegs = (volatile unsigned int *) inputRegBaseAddr;
	m_outputRegs = (volatile unsigned int *) outputRegBaseAddr;
}

BFSAccelerator::~BFSAccelerator() {
}

void BFSAccelerator::assignGraph(GraphMatrixData* graph, unsigned int * inputVectorBitArray) {
	assert(graph);
	// make sure we have enough BRAM storage for this graph
	assert(graph->rows < BRAM_BIT_COUNT);
	assert(inputVectorBitArray);

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

	m_outputRegs[rgCtrlStart] = 1;
	m_outputRegs[feCtrlStart] = 1;
}

bool BFSAccelerator::isFinished() {
	bool frontendFinished = (m_inputRegs[feStatState] == feStateFinished);
	//bool backendFinished  = (m_inputRegs[rgStatState] == beStateFinished);

	return /*backendFinished && */ frontendFinished;
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
	m_outputRegs[ctlColPtrFIFOFullThreshold] = 128;
	m_outputRegs[ctlRowIndFIFOFullThreshold] = 768;
	m_outputRegs[ctlDenVecFIFOFullThreshold] = 8;


	// input data pointers
	m_outputRegs[rgCtrlColLenPtr] = (unsigned int) m_graph->colPtr;
	m_outputRegs[rgCtrlRowIndPtr] = (unsigned int) m_graph->rowInd;
	m_outputRegs[rgCtrlDVPtr] = (unsigned int) m_inputVectorBits;

	// align counts to match the backend burst requirements
	// excess data is discarded
	// we use cols+1 since there are m+1 pointers in the colPtr array
	m_outputRegs[rgCtrlColCount] = BFSBurstAlign(m_graph->cols+1, COLPTR_ALIGN);
	m_outputRegs[rgCtrlNZCount] = BFSBurstAlign(m_graph->nz, ROWIND_ALIGN);
}

void BFSAccelerator::setupFrontend() {
	// the only setup the frontend needs is the column count
	m_outputRegs[feCtrlColCount] = m_graph->cols;
}

void BFSAccelerator::setBRAMAccessMux(bool bEnableSwCtrl) {
	// depending on parameter value,
	// give control of BRAM port A to software (true) or to accelerator (false)
	m_outputRegs[ctlBRAMMux] = (bEnableSwCtrl ? 0 : 0xFFFFFFFF);
}

void BFSAccelerator::printFrontendProfile() {
	// print profile information from StateProfiler
	// we use the BRAM address output also to select state

	cout << "Frontend profile stats: " << endl;
	for(unsigned int i = 0; i <= feStateFinished; i++) {
		m_outputRegs[ctlBRAMAddr] = i;
		cout << feStateNames[i] << ": " << m_inputRegs[statFEProfile] << endl;
	}

	m_outputRegs[ctlBRAMAddr] = feStateProcessUpper;
	unsigned int procCycles = m_inputRegs[statFEProfile];

	m_outputRegs[ctlBRAMAddr] = feStateProcessBoth;
	procCycles += m_inputRegs[statFEProfile];

	unsigned int procMinCycles = (m_graph->nz)/2 + m_graph->cols;
	cout << "Proc efficiency: " << (float) procMinCycles / (float) procCycles << endl;

	m_outputRegs[ctlBRAMAddr] = feStateReadColLen;
	unsigned int colLenReadCycles = m_inputRegs[statFEProfile];
	cout << "ReadColLen efficiency: " << (float) m_graph->cols / (float) colLenReadCycles << endl;
}

void BFSAccelerator::resetFIFOs() {
	// reset FIFOs and everything between backend-frontend via I/O regs
	// to ensure all stale data after a BFS step is removed
	m_outputRegs[ctlResetFIFOs] = 1;
	m_outputRegs[ctlResetFIFOs] = 0;
}

void BFSAccelerator::writeBRAMBit(unsigned int addr, unsigned int data) {
	m_outputRegs[ctlBRAMAddr] = addr;
	m_outputRegs[ctlBRAMDataOut] = data;
	m_outputRegs[ctlBRAMWrEn] = 1;
	m_outputRegs[ctlBRAMWrEn] = 0;
}

void BFSAccelerator::clearBRAM() {
	for(unsigned int i = 0; i < BRAM_BIT_COUNT; i++) {
		writeBRAMBit(i, 0);
	}
}

void BFSAccelerator::deinit() {
	// make sure frontend is finished
	assert(m_inputRegs[feStatState] == feStateFinished);
	// flush FIFOs until backend can finish
	while(m_inputRegs[rgStatState] != beStateFinished) {
		// cleanup after BFS step
		resetFIFOs();
	}
	// allow frontend and backend to go back to idle
	m_outputRegs[feCtrlStart] = 0;
	m_outputRegs[rgCtrlStart] = 0;
	resetFIFOs();
}

void BFSAccelerator::printFrontendStats() {
	cout << "Frontend stats" << endl;
	cout << "=================================" << endl;
	cout << "Processed columns: " << m_inputRegs[feStatColCount] << endl;
	cout << "Processed nonzeroes: " << m_inputRegs[feStatNZCount] << endl;
}

void BFSAccelerator::printFIFODataCounts() {
	cout << "FIFO data counts" << endl;
	cout << "=================================" << endl;
	cout << "ColPtr FIFO: " << m_inputRegs[statColPtrFIFODataCount] << endl;
	cout << "RowInd FIFO: " << m_inputRegs[statRowIndFIFODataCount] << endl;
	cout << "DenVec FIFO: " << m_inputRegs[statDenVecFIFODataCount] << endl;
}

void BFSAccelerator::printAcceleratorState() {
	const char * feState[] = {"sIdle"," sReadColLen"," sProcessColumn","sFinished"};
	const char * rgState[] = {"sIdle", "sReqColLen", "sReqRowInd", "sReqDenVec", "sCheckFinished", "sFinished"};

	cout << "Frontend state: " << feState[m_inputRegs[feStatState]] << endl;
	cout << "Backend state: " << rgState[m_inputRegs[rgStatState]] << endl;
	cout << "Backend read response: " << m_inputRegs[rgStatRResp] << endl;
}

unsigned int BFSAccelerator::readBRAMWord(unsigned int addr) {
	m_outputRegs[ctlBRAMWrEn] = 0;
	m_outputRegs[ctlBRAMAddr] = addr * 32;	// due to 32r1w port; use finest granularity
	return m_inputRegs[ctlBRAMDataIn];
}

void BFSAccelerator::printOutputVector() {
	// find locations of 1-bits in the BRAM and print them out
	unsigned int fullCount = 0;
	for(unsigned int i = 0; i < BRAM_WORD_COUNT; i++) {
		unsigned int data = readBRAMWord(i);
		if(data != 0) {
			cout << "BRAM[" << i << "] = " << hex << data << dec << endl;
			fullCount++;
		}
	}

	if(!fullCount)
		cout << "Result vector is completely empty" << endl;
}
