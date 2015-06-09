#include <string>
#include <malloc.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <sstream>

#include <xscutimer.h>
#include "xil_cache.h"
#include "xil_mmu.h"
#include "xparameters.h"
#include "GraphManager.h"
#include "BitmapBFSOperation.h"
#include "sdcard.h"
#include "BFSAccelerator.h"
#include "HardwareBFSManager.h"

using namespace std;

unsigned int inputRegs[] = { 0x43c00000, 0x43c40000, 0x43c20000, 0x43c60000 };
unsigned int outputRegs[] = { 0x43c10000, 0x43c50000, 0x43c30000, 0x43c70000 };
DistVecElem * resVecDump = (DistVecElem *) 0x1F000000;

const float peMHz = 150.0;
unsigned int hardwarePECount;
unsigned int matrixID = 0;

#define TIMER_DEVICE_ID		XPAR_XSCUTIMER_0_DEVICE_ID

XScuTimer timer;

#define TIMER_DISABLE	0;
#define SWITCH_USING_MODEL

void TimerSetup() {
	TIMER_DISABLE
	XScuTimer_Config * timerConfig = XScuTimer_LookupConfig(TIMER_DEVICE_ID);
	XScuTimer_CfgInitialize(&timer, timerConfig, timerConfig->BaseAddr);
	XScuTimer_DisableAutoReload(&timer);
	XScuTimer_DisableInterrupt(&timer);
	//XScuTimer_SetPrescaler(&timer, 1);
}

void TimerLoadAndStart(unsigned int value) {
	TIMER_DISABLE
	XScuTimer_LoadTimer(&timer, value);
	XScuTimer_Start(&timer);
}

void TimerStop() {
	TIMER_DISABLE
	XScuTimer_Stop(&timer);
}

unsigned int TimerRead() {
	return XScuTimer_GetCounterValue(&timer);
}

const char * getMatrixName(unsigned int id, unsigned int peCount) {
	if (peCount == 1) {
		return getMatrixNameP1(id);
	} else if (peCount == 2) {
		return getMatrixNameP2(id);
	} else if (peCount == 4) {
		return getMatrixNameP4((id));
	} else {
		cout << "Unknown PE count!" << endl;
		return NULL;
	}
}

unsigned int loadedMatrixID = 0, loadedPECount = 0;
void * loadedBasePtr = 0;

void * loadMatrix(unsigned int id, unsigned int peCount) {
	VERBOSE(
			cout << "Loading matrix " << id << " with " << peCount << " partitions.." << endl; cout << "Matrix name: " << getMatrixName(id, peCount) << endl;);
	void * ret = 0;

	// is this already loaded?
	if (loadedMatrixID == id && loadedPECount == peCount) {
		VERBOSE(cout << "Reusing in-memory matrix..." << endl);
		return loadedBasePtr;
	}

	mount();
	if (peCount == 1) {
		ret = loadMatrixP1(id);
	} else if (peCount == 2) {
		ret = loadMatrixP2(id);
	} else if (peCount == 4) {
		ret = loadMatrixP4((id));
	} else {
		cout << "Unknown PE count!" << endl;
	}

	if (ret) {
		// cache the loaded matrix details to reuse later
		loadedMatrixID = id;
		loadedPECount = peCount;
		loadedBasePtr = ret;
	}

	unmount();
	return ret;
}

void HardwareBFS(unsigned int matrixID, unsigned int rootNode) {
	Xil_DCacheDisable();
	VERBOSE(cout << "Method: Hardware BFS" << endl);
	void * configBase = loadMatrix(matrixID, hardwarePECount);
	GraphManager gm((unsigned int *) configBase);
	VERBOSE(gm.printBaseInfo());

	HardwareBFSManager mgr(inputRegs, outputRegs);

	mgr.setGraph(&gm);
	mgr.initVectorSingleRoot(rootNode);
	mgr.setNextDistance(1);
	mgr.clearAllResultVectors();

	for (int i = 0; i < hardwarePECount; i++)
		mgr.assignPartition(i, i);

	VERBOSE(cout << "Initializing accelerator BRAMs..." << endl);
	mgr.initAccelBRAMs();
	VERBOSE(mgr.verifyAccelBRAMs());

	VERBOSE(cout << "Starting accelerator with PE count " << hardwarePECount << endl);

	unsigned int updateCount = 0, steps = 0, totalUpdates = 0;
	unsigned int timerStart = 0xffffffff, timerStop;
	unsigned long int totalPETicks = 0, totalLevelTicks = 0;
	unsigned int regularOp, levelGen;


	 cout << matrixID << "\t" << rootNode << "\t"
	 << gm.getRowCount() << "\t" << gm.getNzCount() << "\t";

	do {

		TimerLoadAndStart(timerStart);
		mgr.step(false);
		timerStop = TimerRead();
		TimerStop();
		regularOp = timerStart - timerStop;
		totalPETicks += timerStart - timerStop;
		//float peCycles = (timerStart - timerStop) * (peMHz / 333.0);
		/*
		 cout << (unsigned int) peCycles << " ticks of a " << peMHz << " MHz clock" << endl;
		 cout << "Bandwidth: " << endl;
		 cout << (float) gm->getTotalWorkloadSize() / peCycles << " bytes/cycle" << endl;
		 */

		TimerLoadAndStart(timerStart);
		updateCount = mgr.updateResults_Hardware();
		//updateCount = mgr.updateResults_Software();
		timerStop = TimerRead();
		TimerStop();
		levelGen = timerStart - timerStop;
		totalLevelTicks += timerStart - timerStop;
		/*
		 cout << "LevelGen and input update: " << endl;
		 cout << timerStart - timerStop << " ticks of an 333 MHz clock" << endl;
		 cout << updateCount << " updates at step " << steps << endl << endl << endl;
		 */
		totalUpdates += updateCount;

		/*
		cout << steps << "\t" << updateCount << "\t" << levelGen + regularOp
				<< "\t" << levelGen << "\t" << regularOp << endl;
				*/

		cout << levelGen + regularOp << "\t";

		steps++;

		if (steps > 10) {
			cout << "error! too many steps" << endl;
			break;
		}

	} while (updateCount > 0);
	cout << endl;

	VERBOSE(

	cout << "BFS operation took " << steps << " steps to converge" << endl;
	cout << "Total " << totalUpdates << " updates" << endl;
	cout << "PE ticks: " << totalPETicks << ", level ticks: " << totalLevelTicks
			<< endl;
	float elapsedSecs = (float) (totalPETicks + totalLevelTicks)
			/ (333333333.0f);
	cout << "Elapsed time (s): " << elapsedSecs << endl;
	float teps = (float) gm.getNzCount() / elapsedSecs;
	cout << "MTEPS: " << teps / 1000000.0f << endl;);

	mgr.resetAll();
}

void SoftwareBFS(unsigned int matrixID, unsigned int rootNode) {
	Xil_DCacheEnable();
	VERBOSE(cout << "Method: Software BFS" << endl);
	void * configBase = loadMatrix(matrixID, 1);
	GraphManager mgr((unsigned int *) configBase);
	VERBOSE(mgr.printBaseInfo());
	GraphMatrixData * graphData = mgr.getPartitionData(0);
	BitmapBFSOperation op(graphData);
	op.setRootNode(rootNode);
	unsigned int timerStart = 0xffffffff, timerStop;
	unsigned long int totalTicks = 0;


	 cout << matrixID << "\t" << "sw" << "\t" << rootNode << "\t"
	 << hardwarePECount << "\t";

	 cout << "SW about to start..." << endl;
	 int x;
	 cin >> x;

	int i = 0, frontierSize = 0;
	while (!op.isConverged()) {
		TimerLoadAndStart(timerStart);
		frontierSize = op.step();
		timerStop = TimerRead();
		TimerStop();
		//cout << i << "\t" << frontierSize << "\t" << timerStart - timerStop << "\t" << op.getEdgeVisits() << endl;
		cout << timerStart-timerStop << "\t";

		//cout << timerStart - timerStop << "\t";
		i++;
		totalTicks += timerStart - timerStop;
		//cout << timerStart - timerStop << " ticks of an 333 MHz clock" << endl;
		//std::cout << "Frontier size at step " << i << " = " << frontierSize << std::endl << endl << endl;
	}
	cout << endl;

	VERBOSE(cout << "BFS took " << i << " steps to finish" << endl;
	cout << op.getResultCount() << " distances have been written" << endl;
	cout << "Total ticks: " << totalTicks << endl;
	float elapsedSecs = (float) totalTicks / (333333333.0f);
	cout << "Elapsed time (s): " << elapsedSecs << endl;
	float teps = (float) graphData->nz / elapsedSecs;
	cout << "MTEPS: " << teps / 1000000.0f << endl);

	Xil_DCacheDisable();
}

unsigned int predictCPUTicks(unsigned int edgesToVisit) {
	return edgesToVisit * 20;
}

unsigned int predictFPGATicks(unsigned int nodes, unsigned int edges,
		unsigned int predFrontierSize) {
	float distgenAdj = 1.11;	// BW util adjustment for dist.gen
	float parRdPenalty = 1.333;	// 1 / BWUtil, depends on PE count but oh well
	float fAdj = 2.22;	// 333/150 MHz
	unsigned int randWrPenalty = 10; // penalty for random writes in distgen
	// base distgen cost
	unsigned int distGenCost = distgenAdj * fAdj * (nodes / hardwarePECount);
	// cost of random writes due to dist.vec update
	distGenCost += predFrontierSize * randWrPenalty;
	// cost of BFS step itself
	unsigned int stepCost = (nodes + edges / (2 * hardwarePECount)) * fAdj
			* parRdPenalty;

	return stepCost + distGenCost;
}

void HybridBFS(unsigned int matrixID, unsigned int rootNode) {
	// There are many operations whose time cost are not measured in this function,
	// and the reason is the ZedBoard limitations. Specifically, the software and parallel hardware
	// executions need different input data (hardware variant is partitioned), but the ZedBoard
	// DRAM is not large enough to store both sets of input data. Therefore, every time we switch execution
	// modes, we wipe out the old data and read out the new from SD card, which takes a looot of time.
	// In a more capable platform, this would not be required.
	Xil_DCacheEnable();
	unsigned int bitmapWords = 0;
	unsigned int frontierSize, steps = 0;
	unsigned int ticks[10];
	unsigned int switchCPUtoFPGA = 0, switchFPGAtoCPU = 0;
	memset(ticks, 0, 10 * 4);
	// start with software BFS, execute two levels
	void * configBase = loadMatrix(matrixID, 1);
	GraphManager * singlePart = new GraphManager((unsigned int *) configBase);
	VERBOSE(singlePart->printBaseInfo());
	unsigned int graphNodes = singlePart->getRowCount();
	unsigned int graphEdges = singlePart->getNzCount();
	BitmapBFSOperation * swExec = new BitmapBFSOperation(
			singlePart->getPartitionData(0));
	bitmapWords = swExec->getBitmapWordCount();
	// allocate the bitmap, used both by software and hardware variants
	unsigned int * bitmap = new unsigned int[bitmapWords];
	// important to call these functions in this order:
	swExec->setResultVector(resVecDump);
	swExec->setBitmap(bitmap);
	swExec->resetBFS();
	swExec->setRootNode(rootNode);
	frontierSize = 1;

	unsigned int timerStart = 0xffffffff, timerStop;
	unsigned int totalCPU = 0;

	bool doSwitch = false;

	while (!doSwitch) {
		TimerLoadAndStart(timerStart);
		frontierSize = swExec->step();
		timerStop = TimerRead();
		TimerStop();
		VERBOSE(
				cout << steps << "\t frontier (SW): " << frontierSize << "\ ticks " << timerStart-timerStop << endl);
		ticks[steps] = timerStart - timerStop;
		steps++;
		totalCPU += timerStart - timerStop;
#ifdef SWITCH_USING_MODEL
		unsigned int predFPGA = predictFPGATicks(graphNodes, graphEdges,
				frontierSize * 2);
		unsigned int predCPU = predictCPUTicks(swExec->getEdgeVisits());
		doSwitch = (predFPGA < predCPU ? true : false);
		if (timerStart - timerStop > predFPGA)
			doSwitch = true;
#else
		doSwitch = (frontierSize > 0.01*graphNodes);
#endif
		VERBOSE(
				cout << "Performance prediction (FPGA/CPU/doSwitch): " << predFPGA << " " << predCPU << " " << doSwitch << endl);
	}

	// cleanup software
	delete swExec;
	delete singlePart;

	// go over to the FPGA, execute two levels there
	configBase = loadMatrix(matrixID, hardwarePECount);
	GraphManager * multiPart = new GraphManager((unsigned int *) configBase);

	HardwareBFSManager mgr(inputRegs, outputRegs);
	VERBOSE(multiPart->printBaseInfo());
	mgr.setGraph(multiPart);
	mgr.initFromBitmap(bitmap);
	mgr.setNextDistance(steps + 1);
	assert(multiPart->getPartitionCount() == hardwarePECount);
	mgr.clearAllResultVectors();

	VERBOSE(
			cout << "Assigning partitions to FPGA PEs and initializing BRAM..." << endl);

	TimerLoadAndStart(timerStart);
	Xil_DCacheDisable();
	for (unsigned int i = 0; i < hardwarePECount; i++)
		mgr.assignPartition(i, i);
	mgr.initAccelBRAMs();
	timerStop = TimerRead();
	TimerStop();
	switchCPUtoFPGA = timerStart - timerStop;

	VERBOSE(cout << "CPU to FPGA switch time: " << switchCPUtoFPGA << endl);

	// can be removed, just here to make sure the BRAM initialization works correctly
	VERBOSE(mgr.verifyAccelBRAMs());

	unsigned int totalLevGen = 0, totalFPGAStep = 0;

	do {
		TimerLoadAndStart(timerStart);
		mgr.step(false);
		timerStop = TimerRead();
		TimerStop();
		totalFPGAStep += timerStart - timerStop;
		ticks[steps] = timerStart - timerStop;

		TimerLoadAndStart(timerStart);
		frontierSize = mgr.updateResults_Hardware();
		timerStop = TimerRead();
		TimerStop();
		totalLevGen += timerStart - timerStop;
		VERBOSE(
				cout << steps << "\t frontier (HW): " << frontierSize << "\t level ticks " << timerStart-timerStop << "\t regular ticks " << ticks[steps] << endl);
		ticks[steps] += timerStart - timerStop;

		steps++;
	} while (frontierSize > 0.05 * graphNodes);

	mgr.resetAll();

	delete multiPart;

	configBase = loadMatrix(matrixID, 1);
	singlePart = new GraphManager((unsigned int *) configBase);
	swExec = new BitmapBFSOperation(singlePart->getPartitionData(0));
	swExec->setResultVector(resVecDump);
	swExec->setRootNode(rootNode);
	swExec->setNextDistance(steps + 1);
	swExec->setBitmap(bitmap);

	TimerLoadAndStart(timerStart);
	unsigned int reconstructedFrontierSize = swExec->reconstructFrontier(true);
	Xil_DCacheEnable();
	timerStop = TimerRead();
	TimerStop();
	switchFPGAtoCPU = timerStart - timerStop;

	VERBOSE(cout << "FPGA to CPU switch time: " << switchFPGAtoCPU << endl);

	// ensure hw-accelerated frontier reconstruction works properly
	if (frontierSize != reconstructedFrontierSize) {
		VERBOSE(
				cout << "WARNING: reconstructed frontier size differs:" << endl; cout << "BFS step said " << frontierSize << endl; cout << "Accelerator said " << reconstructedFrontierSize << endl);
	}

	VERBOSE(cout << "Executing remaining steps in software..." << endl);

	while (!swExec->isConverged()) {
		TimerLoadAndStart(timerStart);
		frontierSize = swExec->step();
		timerStop = TimerRead();
		TimerStop();
		VERBOSE(
				cout << steps << "\t frontier (SW): " << frontierSize << "\ ticks " << timerStart-timerStop << endl);
		ticks[steps++] = timerStart - timerStop;
		totalCPU += timerStart - timerStop;
	};

	VERBOSE(cout << "All steps finished! Total steps = " << steps << endl);

	VERBOSE(cout << "Ticks per step and performance report" << endl);
	float totalTicks = 0;
	cout << matrixID << "\t" << rootNode << "\t" << singlePart->getColCount()
			<< "\t" << singlePart->getNzCount() << "\t";
	cout << totalCPU << "\t" << totalFPGAStep << "\t" << totalLevGen << "\t";
	cout << switchCPUtoFPGA << "\t" << switchFPGAtoCPU << "\t";
	for (int s = 0; s < steps; s++) {
		cout << ticks[s] << "\t";
		totalTicks += ticks[s];
	}
	cout << endl;

	totalTicks += switchCPUtoFPGA + switchFPGAtoCPU;
	float secs = totalTicks / 333333333.0;
	float mteps = (((float) singlePart->getNzCount()) / secs) / 1000000.0;
	VERBOSE(
			cout << "Total ticks: " << totalTicks << endl; cout << "Switch CPU to FPGA: " << switchCPUtoFPGA << " percentOfTotal = " << 100.0 * ((float) switchCPUtoFPGA / totalTicks) << endl; cout << "Switch FPGA to CPU: " << switchFPGAtoCPU << " percentOfTotal = " << 100.0 * ((float) switchFPGAtoCPU / totalTicks) << endl; cout << "MTEPS: " << mteps << endl);

	delete singlePart;
	delete swExec;
	delete[] bitmap;
}


static const char * cmdBuffer =
		"10 4 1259 h 10 4 1024 h 10 4 1451 h 10 4 1587 h 10 4 548 h 10 4 526 h 10 4 272 h 10 4 1239 h 10 4 31 h 10 4 784 h 10 4 1116 h 11 4 1162 h 11 4 806 h 11 4 2028 h 11 4 1360 h 11 4 271 h 11 4 806 h 11 4 1848 h 11 4 1803 h 11 4 950 h 11 4 1415 h 11 4 1298 h 11 4 355 h 11 4 282 h 11 4 1736 h 11 4 1557 h 11 4 1352 h  12 4 1944 h 12 4 1752 h 12 4 95 h 12 4 1147 h 12 4 1858 h 12 4 1604 h 12 4 694 h 12 4 1548 h 12 4 1313 h 12 4 792 h 12 4 1297 h 12 4 614 h 12 4 60 h 12 4 313 h 12 4 1091 h 12 4 1351 h  13 4 1589 h 13 4 981 h 13 4 1228 h 13 4 1183 h 13 4 92 h 13 4 403 h 13 4 1044 h 13 4 1398 h 13 4 687 h 13 4 98 h 13 4 1607 h 13 4 415 h 13 4 953 h 13 4 1955 h 13 4 332 h 13 4 1498 h  14 4 1672 h 14 4 1698 h 14 4 1911 h 14 4 1554 h 14 4 1377 h 14 4 1480 h 14 4 282 h 14 4 22 h 14 4 1341 h 14 4 127 h 14 4 1964 h 14 4 549 h 14 4 199 h 14 4 414 h 14 4 1788 h 14 4 626 h  15 4 1388 h 15 4 1973 h 15 4 1335 h 15 4 73 h 15 4 1193 h 15 4 1114 h 15 4 987 h 15 4 1233 h 15 4 1566 h 15 4 30 h 15 4 1750 h 15 4 354 h 15 4 1123 h 15 4 1950 h 15 4 84 h 15 4 1373 h  16 4 1540 h 16 4 41 h 16 4 351 h 16 4 1579 h 16 4 460 h 16 4 439 h 16 4 209 h 16 4 1480 h 16 4 1352 h 16 4 1222 h 16 4 1972 h 16 4 1105 h 16 4 610 h 16 4 1410 h 16 4 1471 h 16 4 121 h  17 4 169 h 17 4 688 h 17 4 1936 h 17 4 234 h 17 4 874 h 17 4 376 h 17 4 1701 h 17 4 1647 h 17 4 409 h 17 4 364 h 17 4 1587 h 17 4 1901 h 17 4 1421 h 17 4 337 h 17 4 1647 h 17 4 1206 h  18 4 1269h 18 4 1305h 18 4 959h 18 4 258h 18 4 1690h 18 4 1138h 18 4 1745h 18 4 1200h 18 4 510h 18 4 1686h 18 4 1096h 18 4 379h 18 4 157h 18 4 545h 18 4 1422h 18 4 188h ";


/*
static const char * cmdBuffer = "9 4 1236 h 9 4 1960 h";
static unsigned int cmdCount = 2;
*/

int main() {
	//Xil_DisableMMU();
	Xil_DCacheDisable();

	cout << "==========================================================="
			<< endl;

	//string cmdstr(cmdBuffer);
	string cmdstr;
	cout << "Enter command string: " << endl;
	getline(cin,cmdstr);

	cout << "Length of command string: " << cmdstr.length() << endl;
	stringstream cmdStream(cmdstr);


	TimerSetup();

	beginning:

	if(cmdStream.eof()) {
		cout << "all commands finished" << endl;
		return 0;
	}

	VERBOSE(cout << "Enter matrix ID and desired partition count: " << endl);

	//cin >> matrixID >> hardwarePECount;
	cmdStream >> matrixID >> hardwarePECount;

	assert(hardwarePECount <= 4);


	int rootNode = 0;
	VERBOSE(cout << "Enter root node: " << endl);
	//cin >> rootNode;
	cmdStream >> rootNode;

	char method = 0;
	VERBOSE(cout << "Enter s for software, h for hybrid, f for FPGA:" << endl);
	//cin >> method;
	cmdStream >> method;

	if (method == 'h')
		HybridBFS(matrixID, rootNode);
	else if (method == 's')
		SoftwareBFS(matrixID, rootNode);
	else if (method == 'f')
		HardwareBFS(matrixID, rootNode);
	else {
		cout << "unrecognized method: " << method << endl;
		return 0;
	}

	goto beginning;

	return 0;
}

void* operator new(size_t size) {
	//cout << "new: size: " << size << endl;
	if (size % 32 != 0)
		size = size - (size % 32) + 32;

	void *p = malloc(size);
	if (p == 0) {
		cout << "OUCHIES: " << size << endl;
		throw std::bad_alloc(); // ANSI/ISO compliant behavior
	}

	return p;
}

void operator delete(void *p) {
	//cout << "delete: " << hex << (unsigned int) p << dec << endl;
	free(p);
}

