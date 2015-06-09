/*
 * BFSAccelerator.h
 *
 *  Created on: Feb 3, 2015
 *      Author: maltanar
 */

#ifndef BFSACCELERATOR_H_
#define BFSACCELERATOR_H_

#include "GraphManager.h"

#define		INPVEC_ALIGN		8
// should be aligned to data_per_beat * burst_beats
#define		COLPTR_ALIGN		64		// 2 data per beat, 8 beats
#define		ROWIND_ALIGN		256		// 2 data per beat, 128 beats
#define 	BRAM_WORD_COUNT		8192
#define		BRAM_BIT_COUNT		(BRAM_WORD_COUNT * 32)

class BFSAccelerator {
public:
	BFSAccelerator();
	virtual ~BFSAccelerator();

	void setInterfaceRegs(unsigned int inputRegBaseAddr, unsigned int outputRegBaseAddr);

	void printOutputVector();
	void printFrontendStats();
	void printFIFODataCounts();
	void printAcceleratorState();
	void printFrontendProfile();

	void assignGraph(GraphMatrixData * graph, unsigned int * inputVectorBitArray);

	void start();
	bool isFinished();
	void deinit();

	// functions to manage the internal result memory
	void setBRAMAccessMux(bool bEnableSwCtrl);
	void clearBRAM();
	void writeBRAMBit(unsigned int addr, unsigned int data);
	unsigned int readBRAMWord(unsigned int addr);

protected:
	typedef enum {
		feStateIdle = 0,
		feStateReadColLen = 1,
		feStateProcessUpper = 2,
		feStateProcessBoth = 3,
		feStateFinished = 4
	} FrontendTurboStates;

	typedef enum {
		beStateIdle = 0,
		beStateReqColLen = 1,
		beStateReqRowInd = 2,
		beStateReqDenVec = 3,
		beStateCheckFinished = 4,
		beStateFinished = 5
	} BackendStates;

	typedef enum {
		rgCtrlStart = 0,
		rgCtrlNZCount = 1,
		rgCtrlColCount = 2,
		rgCtrlColLenPtr = 3,
		rgCtrlRowIndPtr = 4,
		rgCtrlDVPtr = 5,
		rgStatState = 0,
		rgStatRResp = 4
	} ReqGenRegisters;

	typedef enum {
		feCtrlStart = 6,
		feCtrlColCount = 7,
		feStatState = 1,
		feStatColCount = 2,
		feStatNZCount = 3
	} FrontendRegisters;

	typedef enum {
		ctlBRAMAddr = 8,
		ctlBRAMDataOut = 9,
		ctlBRAMDataIn = 8,
		ctlBRAMWrEn = 10,
		ctlResetFIFOs = 11,
		ctlColPtrFIFOFullThreshold = 12,
		ctlRowIndFIFOFullThreshold = 13,
		ctlDenVecFIFOFullThreshold = 14,
		statColPtrFIFODataCount = 5,
		statRowIndFIFODataCount = 6,
		statDenVecFIFODataCount = 7,
		ctlBRAMMux = 15,
		statFEProfile = 9,
	} MiscRegisters;

	volatile unsigned int * m_inputRegs;
	volatile unsigned int * m_outputRegs;

	GraphMatrixData * m_graph;
	unsigned int * m_inputVectorBits;

	void setupBackend();
	void setupFrontend();
	void resetFIFOs();

};

#endif /* BFSACCELERATOR_H_ */
