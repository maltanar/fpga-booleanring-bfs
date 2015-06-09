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
// TODO do we need more conservative alignment for bursts? this seems to work (aligned to 8 bytes)
#define		COLPTR_ALIGN		8
#define		ROWIND_ALIGN		8
#define 	BRAM_WORD_COUNT		28*1024
#define		BRAM_BIT_COUNT		(BRAM_WORD_COUNT * 32)

class BFSAccelerator {
public:
	BFSAccelerator();
	virtual ~BFSAccelerator();

	void setInterfaceRegs(unsigned int inputRegBaseAddr, unsigned int outputRegBaseAddr);

	void printOutputVector();
	void printAcceleratorStats();
	void printFIFODataCounts();
	void printAcceleratorState();
	void printFrontendProfile();

	void assignGraph(GraphMatrixData * graph, unsigned int * inputVectorBitArray);

	void start();
	bool isFinished();
	void deinit();
	void resetAccelerator();

	void startLevelUpdate(unsigned int level, DistVecElem * distVecBase);
	bool isFinishedLevelUpdate();
	volatile unsigned int getLevelUpdateCount() {return m_inputRegs[feStatUpdateCount];};

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
		feStateFinished = 4,
		feStateResDump = 5
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
		rgControl = 0,
		rgCtrlNZCount = 1,
		rgCtrlColCount = 2,
		rgCtrlColLenPtr = 3,
		rgCtrlRowIndPtr = 4,
		rgCtrlDVPtr = 5,
		rgStatState = 0,
		rgStatRResp = 4,
		rgStatWriteState = 10,
		rgStatWriteCount = 11,
		rgCtrlDistVecBase = 13,
		rgCtrlCurrentLevel = 14,
		rgStatDistVecUpdateCount = 12,
		rgCtrlInpVecWritePtr = 15
	} ReqGenRegisters;

	typedef enum {
		feControl = 6,
		feCtrlColCount = 7,
		feStatState = 1,
		feStatColCount = 2,
		feStatNZCount = 3,
		feCtrlRowCount = 11,
		feStatUpdateCount = 12
	} FrontendRegisters;

	typedef enum {
		ctlBRAMAddr = 8,
		ctlBRAMDataOut = 9,
		ctlBRAMDataIn = 8,
		ctlBRAMWrEn = 10,
		ctlThresholds = 12,
		statColPtrFIFODataCount = 5,
		statRowIndFIFODataCount = 6,
		statDenVecFIFODataCount = 7,
		statFEProfile = 9,
	} MiscRegisters;

	volatile unsigned int * m_inputRegs;
	volatile unsigned int * m_outputRegs;

	GraphMatrixData * m_graph;
	unsigned int * m_inputVectorBits;

	void setThresholds(unsigned int clThres, unsigned int riThres, unsigned int dvThres);
	void setupBackend();
	void setupFrontend();
};

#endif /* BFSACCELERATOR_H_ */
