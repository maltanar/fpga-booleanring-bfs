/*
 * BFSAccelerator.h
 *
 *  Created on: Feb 3, 2015
 *      Author: maltanar
 */

#ifndef BFSACCELERATOR_H_
#define BFSACCELERATOR_H_

#include "GraphManager.h"

// various flags and defines used by the accelerator
#define 	BRAM_WORD_COUNT		16*1024
#define		BRAM_BIT_COUNT		(BRAM_WORD_COUNT * 32)
#define		BFS_ACCEL_ID		1234567

// control values (corresponding to set bits) for backend and frontend
#define		BACKEND_START		(1)
#define		BACKEND_LEVGEN		(2)
#define 	FRONTEND_START		(1)
#define		FRONTEND_LEVGEN		(2)
#define		FRONTEND_RESETBRAM	(4)

class BFSAccelerator {
public:
	BFSAccelerator(unsigned int id, unsigned int baseAddr);
	virtual ~BFSAccelerator();

	void initialize(GraphMatrixData * graph,
			volatile DistVecElem * distanceVectorBase,
			unsigned int * visitedInds, unsigned int visitedCount);

	void start(DistVecElem level, unsigned int prevFrontierSize);
	bool isFinished();
	void blockUntilFinished(unsigned int timeout, bool levelgen = false);
	void clearBRAM();
	void resetAccelerator();
	void deinit();

	void startLevelUpdate(DistVecElem levelToGenerate);
	bool isFinishedLevelUpdate();

	unsigned int getTraversedEdges() {return m_traversedEdges;};

	void saveProfiles();
	unsigned int * getBackendProfile() {return m_backendProfile;};
	unsigned int * getFrontendProfile() {return m_frontendProfile;};
	unsigned int * getNeighborFetchProfile() {return m_neighborFetchProfile;};

	void printBackendProfile();
	void printFrontendProfile();
	void printNeighborFetchProfile();

	void printAcceleratorState();
	void printFIFOCounts();

	unsigned int getLastFrontierSize() {
		return m_lastFrontierSize;
	}
	;
	void setLastFrontierSize(unsigned int size) {
		m_lastFrontierSize = size;
	}
	;
	unsigned int getLastRunDuration() {
		return m_lastRunDuration;
	}
	;

	void handleTimeout(const char * op);
	void setVisitedStatus(unsigned int * inds, unsigned int visitedCount);

protected:
	typedef enum {
		inRegFrontendFrontierSize = 0,
		inRegFrontendProcessedNZCount = 1,
		inRegBackendFrontierSize = 2,
		inRegBackendNZCount = 3,
		inRegBackendDistVecWrites = 4,
		inRegBackendNGColCount = 5,
		inRegFIFODataCountsBig = 6, // msb : writeInd, colPtr, distVec : lsb
		inRegFIFODataCountsSmall = 7, // msb : newData, oldData, rowMeta, rowData : lsb
		inRegFrontendProfiler = 8,
		inRegBackendProfiler = 9,
		inRegBackendState = 10,
		inRegFrontendState = 11,
		inRegLevelGenWriteCount = 12,
		inRegLevelGenFinished = 13,
		inRegNeighborFetchProfiler = 14,
		inRegAccelID = 15
	} InputRegisters;

	typedef enum {
		outRegFrontendCtrl = 0,
		outRegFrontendRowCount = 1,
		outRegExpFrontierSize = 2,
		outRegBackendCtrl = 3,
		outRegBackendThresholdT0 = 4,
		outRegBackendThresholdT1 = 5,
		outRegBackendRowIndBase = 6,
		outRegBackendCurrentLevel = 7,
		outRegBackendColPtrBase = 8,
		outRegBackendDistVecCount = 9,
		outRegBackendDistVecBase = 10,
		outRegLevelGenBitCount = 11,
		outRegReset = 12,
		outRegProfileSel = 13 // 0-2 frontend, 3-5 backend
	} OutputRegisters;

	volatile unsigned int * m_inputRegs;
	volatile unsigned int * m_outputRegs;

	GraphMatrixData * m_graph;
	volatile DistVecElem * m_distanceVector;
	unsigned int m_lastFrontierSize;
	unsigned int m_accelID;
	unsigned int m_lastRunDuration;

	void setThresholds(unsigned int T0, unsigned int T1);
	void setupBackend();
	void setupFrontend();

	unsigned int getProfile(volatile unsigned int * mux,
			volatile unsigned int * inp, unsigned int stateCount,
			const char ** stateNames, bool verbose = false,
			unsigned int muxShift = 0, unsigned int * storage = 0);

	unsigned int getFIFODataCount_writeInd();
	unsigned int getFIFODataCount_colPtr();
	unsigned int getFIFODataCount_distVec();
	unsigned int getFIFODataCount_newData();
	unsigned int getFIFODataCount_oldData();
	unsigned int getFIFODataCount_rowMetadata();
	unsigned int getFIFODataCount_rowData();

	unsigned int * m_frontendProfile;
	unsigned int * m_backendProfile;
	unsigned int * m_neighborFetchProfile;
	unsigned int m_traversedEdges;

	unsigned int backendProfile(bool verbose = true);
	unsigned int frontendProfile(bool verbose = true);
	unsigned int neighborFetchProfile(bool verbose = true);
};

#endif /* BFSACCELERATOR_H_ */
