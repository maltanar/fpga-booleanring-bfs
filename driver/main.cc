#include <string>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>

#include <xscutimer.h>
#include "xil_cache.h"
#include "xparameters.h"
#include "GraphManager.h"
#include "classicalbfsoperation.h"

#include "BFSAccelerator.h"
#include "HardwareBFSManager.h"

using namespace std;

unsigned int outputRegs[] = { 0x43c00000, 0x43c20000, 0x43c40000, 0x43c60000 };
unsigned int inputRegs[] = { 0x43c10000, 0x43c30000, 0x43c50000, 0x43c70000 };

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

void BFSinHardware(int accNum, unsigned int * configBase,
		unsigned int * vecDump, GraphManager * gm, unsigned int rootNode) {

	HardwareBFSManager mgr(inputRegs, outputRegs);

	mgr.setGraph(gm);
	mgr.initVectorSingleRoot(rootNode);
	mgr.setNextDistance(1);
	assert(gm->getPartitionCount() == BFS_PE_COUNT);
	for(int i = 0; i < BFS_PE_COUNT; i++)
		mgr.assignPartition(i, i);

	cout << "Starting accelerator..." << endl;

	unsigned int updateCount = 0, steps = 0, totalUpdates = 0;
	unsigned int timerStart = 0xffffffff, timerStop;

	do {
		TimerLoadAndStart(timerStart);
		mgr.step(false);
		timerStop = TimerRead();
		TimerStop();
		cout << "Regular operation: " << endl;
		cout << timerStart - timerStop << " ticks of a 333 MHz clock" << endl;
		float peMHz = 150.0;
		float peCycles = (timerStart-timerStop)*(peMHz/333.0);
		cout << (unsigned int) peCycles << " ticks of a " << peMHz << " MHz clock" << endl;
		cout << "Bandwidth: " << endl;

		cout << (float) gm->getTotalWorkloadSize() / peCycles << " bytes/cycle" << endl;

		TimerLoadAndStart(timerStart);
		updateCount = mgr.updateResults();
		timerStop = TimerRead();
		TimerStop();
		cout << "LevelGen and input update: " << endl;
		cout << timerStart - timerStop << " ticks of an 333 MHz clock" << endl;
		totalUpdates += updateCount;
		cout << updateCount << " updates at step " << steps << endl;

		steps++;

		if (steps > 10)
			break;

	} while (updateCount > 0);

	cout << "BFS operation took " << steps << " steps to converge" << endl;
	cout << "Total " << totalUpdates << " updates" << endl;

	// acc.copyDistanceVector((unsigned int *) 0x1F000000);
}

void BFSinSoftware(unsigned int * configBase, unsigned int * vecDump,
		GraphMatrixData * graphData, unsigned int rootNode) {

	ClassicalBFSOperation op(graphData);
	op.setRootNode(rootNode);
	unsigned int timerStart = 0xffffffff, timerStop;

	int i = 0;
	while (!op.isConverged()) {
		TimerLoadAndStart(timerStart);
		op.step();
		timerStop = TimerRead();
		TimerStop();
		i++;
		cout << timerStart - timerStop << " ticks of an 333 MHz clock" << endl;
	}

	cout << "BFS took " << i << " steps to finish" << endl;
	cout << op.getResultCount() << " distances have been written" << endl;
	op.copyResultVector(vecDump);
	cout << "Result copied to 0x" << hex << (unsigned int) vecDump << dec
			<< endl;
}

int main() {

	Xil_DCacheDisable();
	TimerSetup();

	unsigned int * configBase = (unsigned int *) 0x10000000;
	unsigned int * resVecDump = (unsigned int *) 0x1F000000;

	GraphManager gm(configBase);
	gm.printBaseInfo();
	gm.printAllPartitionInfo();

	unsigned int rootNode = 0;
	cout << "Enter root node: " << endl;
	cin >> rootNode;

	cout
			<< "Enter h for hardware BFS, s for software BFS, anything else to exit:"
			<< endl;
	char sel;
	cin >> sel;
	if (sel == 'h') {
		int accId = 0;
		/*cout << "Select PE to use: [0-3]" << endl;
		cin >> accId;
		assert(accId >= 0 && accId <= 3);*/
		BFSinHardware(accId, configBase, resVecDump, &gm,
				rootNode);
	} else if (sel == 's') {
		Xil_DCacheEnable();
		BFSinSoftware(configBase, resVecDump, gm.getPartitionData(0), rootNode);
		Xil_DCacheDisable();
	}

	cout << "All operations completed, exiting..." << endl;

	return 0;
}

