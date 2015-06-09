#include <iostream>
#include <string.h>
#include "BFSAccelerator.h"
#include "DecoupledTester.h"

using namespace std;

const char * backendStateNames[] = { "sIdle", "sReqDistVec", "sFetchIndex",
		"sReqColPtrs", "sCheckFinished", "sFinished", "sLevelGen" };
const int backendStateCount = 7;

const char * frontendStateNames[] = { "sIdle", "sResetAll", "sDump",
		"sFetchMeta", "sProcessInds", "sFinished" };
const int frontendStateCount = 6;

const char * neighborFetchStateNames[] = { "sIdle", "sWaitPtrStart",
		"sWaitPtrEnd", "sPushMetadata", "sBuildReq", "sReq" };
const int neighborFetchStateCount = 6;

inline unsigned int incrementAlign(unsigned int base, unsigned int align) {
	if (base % align == 0)
		return base;
	else
		return base - (base % align) + align;
}

BFSAccelerator::BFSAccelerator(unsigned int id, unsigned int baseAddr) {
	m_inputRegs = (volatile unsigned int *) baseAddr;
	m_outputRegs = (volatile unsigned int *) (baseAddr + 0x1000);
	m_lastFrontierSize = 0;
	m_accelID = id;
	m_graph = 0;
	m_lastRunDuration = 0;

	m_frontendProfile = new unsigned int[frontendStateCount];
	m_backendProfile = new unsigned int[backendStateCount];
	m_neighborFetchProfile = new unsigned int[neighborFetchStateCount];

	if (m_inputRegs[inRegAccelID] != BFS_ACCEL_ID) {
		std::cout << "Error: unexpected accelerator ID "
				<< m_inputRegs[inRegAccelID] << std::endl;
		return;
	} /*else
	 std::cout << "Accelerator init OK" << std::endl;*/

	resetAccelerator();
	setThresholds(768,768);
}

BFSAccelerator::~BFSAccelerator() {
	delete[] m_frontendProfile;
	delete[] m_backendProfile;
	delete[] m_neighborFetchProfile;
}

void BFSAccelerator::clearBRAM() {
	// make sure backend and frontend are idle
	assert(m_inputRegs[inRegBackendState] == 0);
	assert(m_inputRegs[inRegFrontendState] == 0);
	// enter BRAM reset mode in frontend
	// outRegFrontendRowCount must be set for this to work
	m_outputRegs[outRegFrontendRowCount] = BRAM_BIT_COUNT;
	m_outputRegs[outRegFrontendCtrl] = FRONTEND_START | FRONTEND_RESETBRAM;
	// wait until frontend is finished
	while (m_inputRegs[inRegFrontendState] != 5)
		;
	// bring frontend back to idle
	m_outputRegs[outRegFrontendCtrl] = 0;
}

void BFSAccelerator::setVisitedStatus(unsigned int * inds,
		unsigned int visitedCount) {
	VERBOSE(cout << "setVisitedStatus: " << visitedCount << " " << inds[0] << endl);
	// set BRAM content by using a small artificial matrix: 1 column with <visitedCount> entries
	DistVecElem * initDistVec = new DistVecElem[1024];
	memset(initDistVec, 0, 16 * 4);
	// we'll set the frontier filter to look for 1
	DistVecElem initLevel = 1;
	initDistVec[0] = initLevel;

	// single entry in matrix, two col pointers marking start and end:
	unsigned int * initColPtrs = new unsigned int[1024];
	memset(initColPtrs, 0, 16 * 4);
	initColPtrs[0] = 0;
	initColPtrs[1] = visitedCount;

	// TODO set up a regular graph and use accelerator member functions
	// instead of setting these registers manually
	m_outputRegs[outRegBackendColPtrBase] = (unsigned int) initColPtrs;
	m_outputRegs[outRegBackendDistVecBase] = (unsigned int) initDistVec;
	m_outputRegs[outRegBackendRowIndBase] = (unsigned int) inds;
	m_outputRegs[outRegBackendDistVecCount] = 1;
	m_outputRegs[outRegBackendCurrentLevel] = initLevel;
	m_outputRegs[outRegExpFrontierSize] = 1;

	m_outputRegs[outRegBackendCtrl] = 1;
	m_outputRegs[outRegFrontendCtrl] = 1;

	blockUntilFinished(100000);

	// check stat counters to verify we initialized correctly
	assert(m_inputRegs[inRegBackendFrontierSize] == 1);
	assert(m_inputRegs[inRegBackendNZCount] == visitedCount);
	assert(m_inputRegs[inRegFrontendProcessedNZCount] == visitedCount);

	deinit();

	VERBOSE(cout << "setVisitStatus finished successfully" << endl);

	delete[] initColPtrs;
	delete[] initDistVec;

}

void BFSAccelerator::blockUntilFinished(unsigned int timeout, bool levelgen) {
	if (levelgen) {
		while (!isFinishedLevelUpdate()) {
			timeout--;
			if (!timeout) {
				handleTimeout("levelgen");
				break;
			}
		}
	} else {
		while (!isFinished()) {
			timeout--;
			if (!timeout) {
				handleTimeout("regular");
				break;
			}
		}
	}
}

void BFSAccelerator::deinit() {
	m_outputRegs[outRegBackendCtrl] = 0;
	m_outputRegs[outRegFrontendCtrl] = 0;
	resetAccelerator();
}

void BFSAccelerator::handleTimeout(const char * op) {
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << "Timeout in accelerator " << m_accelID << " in op: " << op << endl;
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	printAcceleratorState();
	printFIFOCounts();
	backendProfile();
	frontendProfile();
	deinit();
}

void BFSAccelerator::initialize(GraphMatrixData * graph,
		volatile DistVecElem * distanceVectorBase, unsigned int * visitedInds,
		unsigned int visitedCount) {
	assert(graph->rows < BRAM_BIT_COUNT);

	clearBRAM();

	m_graph = graph;
	m_distanceVector = distanceVectorBase;
	// init result BRAM contents if desired
	if (visitedInds != 0 && visitedCount > 0)
		setVisitedStatus(visitedInds, visitedCount);

	m_lastFrontierSize = visitedCount;
}

void BFSAccelerator::start(DistVecElem level, unsigned int prevFrontierSize) {
	// make sure backend and frontend are idle
	assert(m_inputRegs[inRegBackendState] == 0);
	assert(m_inputRegs[inRegFrontendState] == 0);

	m_outputRegs[outRegBackendCurrentLevel] = level;
	// sourced from parameter, since our own lastFrontierSize is only a part of the
	// entire frontier if we have multiple PEs
	m_outputRegs[outRegExpFrontierSize] = prevFrontierSize;
	setupBackend();
	setupFrontend();

	// issue start for backend and frontend
	m_outputRegs[outRegBackendCtrl] = 1;
	m_outputRegs[outRegFrontendCtrl] = 1;
}

bool BFSAccelerator::isFinished() {
	if (m_inputRegs[inRegBackendState] == 5
			&& m_inputRegs[inRegFrontendState] == 5) {
		m_lastRunDuration = frontendProfile(false);
		return true;
	} else
		return false;
}

void BFSAccelerator::resetAccelerator() {
	m_outputRegs[outRegReset] = 1;
	m_outputRegs[outRegReset] = 0;
}

void BFSAccelerator::startLevelUpdate(DistVecElem levelToGenerate) {
	// set up registers for level generation - a bit different than regular operation
	// the primary difference is what we do with the distanceVector: during level generation,
	// only a portion of the distance vector is traversed.

	// modify distance vector base and count to specify partition
	// distvec will be both read and written during this period
	m_outputRegs[outRegBackendDistVecBase] =
			(unsigned int) &(m_distanceVector[m_graph->startingRow]);
	m_outputRegs[outRegBackendDistVecCount] = m_graph->rows;
	// the currentLevel register only specifies what value we write to the update indices
	m_outputRegs[outRegBackendCurrentLevel] = levelToGenerate;

	// frontend and LevelGen use row count to know how long to operate
	// frontend uses right shift to compute the number of dumped words, so round up its number
	m_outputRegs[outRegFrontendRowCount] = incrementAlign(m_graph->rows, 64);
	m_outputRegs[outRegLevelGenBitCount] = m_graph->rows;

	// give start command to both
	m_outputRegs[outRegFrontendCtrl] = FRONTEND_START | FRONTEND_LEVGEN;
	m_outputRegs[outRegBackendCtrl] = BACKEND_START | BACKEND_LEVGEN;
}

bool BFSAccelerator::isFinishedLevelUpdate() {
	bool allWritten = (m_inputRegs[inRegBackendDistVecWrites]
			== m_inputRegs[inRegLevelGenWriteCount]);
	if (m_inputRegs[inRegLevelGenFinished] && allWritten) {
		m_lastRunDuration = backendProfile(false);
		m_lastFrontierSize = m_inputRegs[inRegLevelGenWriteCount];
		return true;
	} else
		return false;
}

void BFSAccelerator::saveProfiles() {
	backendProfile(false);
	frontendProfile(false);
	neighborFetchProfile(false);
	m_traversedEdges=m_inputRegs[inRegFrontendProcessedNZCount];
}

void BFSAccelerator::printBackendProfile() {
	cout << m_accelID << " backend ";
	for (int i = 0; i < backendStateCount; i++)
		cout << m_backendProfile[i] << " ";
	cout << endl;
}

void BFSAccelerator::printFrontendProfile() {
	cout << m_accelID << " frontend ";
	for (int i = 0; i < frontendStateCount; i++)
		cout << m_frontendProfile[i] << " ";
	cout << endl;
}

void BFSAccelerator::printNeighborFetchProfile() {
	cout << m_accelID << " neighborfetch ";
	for (int i = 0; i < neighborFetchStateCount; i++)
		cout << m_neighborFetchProfile[i] << " ";
	cout << endl;
}

unsigned int BFSAccelerator::neighborFetchProfile(bool verbose) {
	if (verbose) {
		cout << "---------------------------------" << endl;
		cout << "Backend profile for accelID " << m_accelID << endl;
		cout << "---------------------------------" << endl;
	}

	return getProfile(&(m_outputRegs[outRegProfileSel]),
			&(m_inputRegs[inRegNeighborFetchProfiler]), neighborFetchStateCount,
			neighborFetchStateNames, verbose, 3, m_neighborFetchProfile);
}

unsigned int BFSAccelerator::backendProfile(bool verbose) {
	if (verbose) {
		cout << "---------------------------------" << endl;
		cout << "Backend profile for accelID " << m_accelID << endl;
		cout << "---------------------------------" << endl;
	}

	return getProfile(&(m_outputRegs[outRegProfileSel]),
			&(m_inputRegs[inRegBackendProfiler]), backendStateCount,
			backendStateNames, verbose, 3, m_backendProfile);
}

unsigned int BFSAccelerator::frontendProfile(bool verbose) {
	if (verbose) {
		cout << "---------------------------------" << endl;
		cout << "Frontend profile for accelID " << m_accelID << endl;
		cout << "---------------------------------" << endl;
	}
	return getProfile(&(m_outputRegs[outRegProfileSel]),
			&(m_inputRegs[inRegFrontendProfiler]), frontendStateCount,
			frontendStateNames, verbose, 0, m_frontendProfile);
}

void BFSAccelerator::printAcceleratorState() {
	cout << "------------------------------" << endl;
	cout << "Accelerator state for accelID " << m_accelID << endl;
	cout << "------------------------------" << endl;
	cout << "Backend state: "
			<< backendStateNames[m_inputRegs[inRegBackendState]] << endl;
	cout << "Frontend state: "
			<< frontendStateNames[m_inputRegs[inRegFrontendState]] << endl;

	cout << "Frontier size (backend): " << m_inputRegs[inRegBackendFrontierSize]
			<< endl;
	cout << "Frontier size (backend NF): "
			<< m_inputRegs[inRegBackendNGColCount] << endl;
	cout << "Edge count (backend):" << m_inputRegs[inRegBackendNZCount] << endl;

	cout << "Frontier size (frontend): "
			<< m_inputRegs[inRegFrontendFrontierSize] << endl;
	cout << "Edge count (frontend):"
			<< m_inputRegs[inRegFrontendProcessedNZCount] << endl;

	cout << "LevelGen write count: " << m_inputRegs[inRegLevelGenWriteCount]
			<< endl;
	cout << "Backend write count: " << m_inputRegs[inRegBackendDistVecWrites]
			<< endl;
	cout << "LevelGen finished: " << m_inputRegs[inRegLevelGenFinished] << endl;
}

void BFSAccelerator::printFIFOCounts() {
	cout << "---------------------------------" << endl;
	cout << "FIFO data counts for accelID " << m_accelID << endl;
	cout << "---------------------------------" << endl;
	cout << "colPtr: " << getFIFODataCount_colPtr() << endl;
	cout << "distVec: " << getFIFODataCount_distVec() << endl;
	cout << "newData: " << getFIFODataCount_newData() << endl;
	cout << "oldData: " << getFIFODataCount_oldData() << endl;
	cout << "rowData: " << getFIFODataCount_rowData() << endl;
	cout << "rowMetadata: " << getFIFODataCount_rowMetadata() << endl;
	cout << "writeInd: " << getFIFODataCount_writeInd() << endl;
}

void BFSAccelerator::setThresholds(unsigned int T0, unsigned int T1) {
	m_outputRegs[outRegBackendThresholdT0] = T0;
	m_outputRegs[outRegBackendThresholdT1] = T1;
}

void BFSAccelerator::setupBackend() {
	assert(m_graph != 0);
	m_outputRegs[outRegBackendColPtrBase] = (unsigned int) m_graph->colPtr;
	m_outputRegs[outRegBackendDistVecBase] = (unsigned int) m_distanceVector;
	m_outputRegs[outRegBackendDistVecCount] = m_graph->cols;
	m_outputRegs[outRegBackendRowIndBase] = (unsigned int) m_graph->rowInd;
}

void BFSAccelerator::setupFrontend() {

	m_outputRegs[outRegFrontendRowCount] = incrementAlign(m_graph->rows, 64);
}

// helper functions for reading profile and FIFO data count registers
unsigned int BFSAccelerator::getProfile(volatile unsigned int * mux,
		volatile unsigned int * inp, unsigned int stateCount,
		const char ** stateNames, bool verbose, unsigned int muxShift,
		unsigned int * storage) {
	unsigned int total = 0;
	for (unsigned int i = 0; i < stateCount; i++) {
		*mux = i << muxShift;
		unsigned int stateCycles = *inp;
		total += stateCycles;
		if (verbose)
			std::cout << stateNames[i] << " : " << stateCycles << std::endl;
		if (storage)
			storage[i] = stateCycles;
	}
	return total;
}

unsigned int BFSAccelerator::getFIFODataCount_writeInd() {
	unsigned int fifoDataCounts = m_inputRegs[inRegFIFODataCountsBig];
	return (fifoDataCounts >> 20) & 0x3ff;
}

unsigned int BFSAccelerator::getFIFODataCount_colPtr() {
	unsigned int fifoDataCounts = m_inputRegs[inRegFIFODataCountsBig];
	return (fifoDataCounts >> 10) & 0x3ff;
}

unsigned int BFSAccelerator::getFIFODataCount_distVec() {
	unsigned int fifoDataCounts = m_inputRegs[inRegFIFODataCountsBig];
	return fifoDataCounts & 0x3ff;
}

unsigned int BFSAccelerator::getFIFODataCount_newData() {
	unsigned int fifoDataCounts = m_inputRegs[inRegFIFODataCountsSmall];
	return (fifoDataCounts >> 24) & 0xff;
}

unsigned int BFSAccelerator::getFIFODataCount_oldData() {
	unsigned int fifoDataCounts = m_inputRegs[inRegFIFODataCountsSmall];
	return (fifoDataCounts >> 16) & 0xff;
}

unsigned int BFSAccelerator::getFIFODataCount_rowMetadata() {
	unsigned int fifoDataCounts = m_inputRegs[inRegFIFODataCountsSmall];
	return (fifoDataCounts >> 8) & 0xff;
}

unsigned int BFSAccelerator::getFIFODataCount_rowData() {
	unsigned int fifoDataCounts = m_inputRegs[inRegFIFODataCountsSmall];
	return fifoDataCounts & 0xff;
}
