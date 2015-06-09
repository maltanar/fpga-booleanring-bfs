#include <iostream>
#include <sstream>
#include <malloc.h>
#include <xscutimer.h>
#include "xil_cache.h"
#include "xparameters.h"
#include "GraphManager.h"
#include "classicalbfsoperation.h"
#include "BitmapBFSOperation.h"
#include "BFSAccelerator.h"
#include "HardwareBFSManager.h"
#include "sdcard.h"

using namespace std;

unsigned int hardwarePECount;
unsigned int matrixID;

volatile unsigned int * baseData = (volatile unsigned int *) 0x10000000;
volatile int * distVec = (volatile int *) 0x1F000000;

const float peMHz = 102.0;
const float timerMHz = 333.3;
const float ticksPerSec = 1000000.0;

#define TIMER_DEVICE_ID		XPAR_XSCUTIMER_0_DEVICE_ID

XScuTimer timer;

#define TIMER_DISABLE	0;

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
	} else if (peCount == 3) {
		return getMatrixNameP3(id);
	} else if (peCount == 4) {
		return getMatrixNameP4((id));
	} else if (peCount == 5) {
		return getMatrixNameP5((id));
	}else {
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
	} else if (peCount == 3) {
		ret = loadMatrixP3(id);
	} else if (peCount == 4) {
		ret = loadMatrixP4((id));
	} else if (peCount == 5) {
		ret = loadMatrixP5(id);
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

void HybridBFS(unsigned int matrixID, unsigned int rootNode) {

	// TODO
	assert(0);
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

void HardwareBFS(unsigned int matrixID, unsigned int rootNode) {
	unsigned int baseAddrs[] =
			{ 0x43c20000, 0x43c00000, 0x43c10000, 0x43c30000, 0x43c40000};
	VERBOSE(cout << "Performing BFS in hardware.." << endl);
	void * configBase = loadMatrix(matrixID, hardwarePECount);
	GraphManager gm((unsigned int *) configBase);
	VERBOSE(gm.printBaseInfo());
	HardwareBFSManager acc(baseAddrs);

	acc.setGraph(&gm);


	for (int i = 0; i < hardwarePECount; i++)
		acc.assignPartition(i, i);

	acc.initVectorSingleRoot(rootNode);
	acc.setDistance(0);

	unsigned int totalRegularCycles = 0, totalLevGenCycles = 0;
	unsigned int levelRegular = 0, levelLevGen = 0, level = 0;
	unsigned int totalFrontierSize = 0, currentFrontier = 1;

	unsigned int timerStart = 0xffffffff, timerStop;

	cout << matrixID << "\t" << rootNode << "\t" << gm.getRowCount() << "\t"
			<< gm.getNzCount() << "\t";
	cout << endl;
	while (currentFrontier != 0) {
		//cout << "distvec before: " << endl;	acc.printDistanceVector();

		TimerLoadAndStart(timerStart);
		acc.step();
		timerStop = TimerRead();
		TimerStop();
		totalRegularCycles += timerStart - timerStop;
		levelRegular = timerStart - timerStop;
		//acc.printProfiles();

		//cout << "distvec between: " << endl;	acc.printDistanceVector();

		TimerLoadAndStart(timerStart);
		acc.levelGeneration();
		timerStop = TimerRead();
		TimerStop();
		totalLevGenCycles += timerStart - timerStop;
		levelLevGen = timerStart - timerStop;

		totalFrontierSize += acc.getLastFrontierSize();
		currentFrontier = acc.getLastFrontierSize();

		//cout << "distvec after: " << endl;	acc.printDistanceVector();

		cout << "level " << level << " " << currentFrontier << " "
				<< levelRegular + levelLevGen << " " << levelLevGen << " "
				<< levelRegular << endl;


		//cout << levelRegular+levelLevGen << "\t";
		level++;

		if (level >= 10) {
			cout << "!!!!!!! Too many levels, exiting !!!!!!!!!" << endl;
			break;
		}
	}

	VERBOSE(
	cout << "----------------------------" << endl;
	cout << "Summary" << endl;
	cout << "----------------------------" << endl;
	cout << level << " BFS levels, total frontier size " << totalFrontierSize
			<< endl;
	unsigned int workloadSize = gm.getTotalWorkloadSize();
	unsigned int totalCycles = totalRegularCycles + totalLevGenCycles;

	cout << "Total cycles: " << totalCycles << " at " << timerMHz << " MHz"
			<< endl;
	cout << "Regular cycles %: "
			<< 100 * (float) totalRegularCycles / (float) totalCycles << endl;
	cout << "LevGen cycles %: "
			<< 100 * (float) totalLevGenCycles / (float) totalCycles << endl;
	cout << "Bandwidth during regular exec: "
			<< (timerMHz / peMHz) * (float) workloadSize
					/ (float) totalRegularCycles << " bytes/cycle" << endl;

	float secs = (float) totalCycles / (timerMHz * ticksPerSec);
	cout << "Runtime: " << secs << " seconds" << endl;
	float mteps = ((float) (gm.getNzCount()) / secs) / 1000000.0;
	cout << "Performance: " << mteps << " MTEPS" << endl;
	);
}

int main() {
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

		assert(hardwarePECount <= 5);


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
		else
			cout << "unrecognized method: " << method << endl;

		goto beginning;

		return 0;
}

/*
 void* operator new (size_t size)
 {
 cout << "size: " << size << endl;
 if(size % 32 != 0)
 size = size -(size%32) +32;

 void *p=malloc(size);
 if (p==0) {
 cout << "OUCHIES: " << size  << endl;
 throw std::bad_alloc(); // ANSI/ISO compliant behavior
 }

 return p;
 }

 void operator delete (void *p)
 {
 free(p);
 }
 */
