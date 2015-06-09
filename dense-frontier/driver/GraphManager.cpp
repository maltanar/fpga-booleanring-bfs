/*
 * GraphManager.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: maltanar
 */

#include "GraphManager.h"
#include <iostream>

using namespace std;

GraphManager::GraphManager(unsigned int * configBase) {
	parseConfig(configBase);
}

GraphManager::~GraphManager() {

}

void GraphManager::printBaseInfo() const {
	cout << "===========================================" << endl;
	cout << "GraphManager basic info" << endl;
	cout << "===========================================" << endl;
	cout << "Row count: " << m_rowCount << endl;
	cout << "Col count: " << m_colCount << endl;
	cout << "Nonzero count: " << m_nzCount << endl;
	cout << "Number of partitions:" << m_partitionCount << endl;
	cout << "Partition array located at " << hex << m_partitions << dec << endl;
	cout << "Largest partition row count: " << m_largestPartitionRowCount
			<< endl;
}

void GraphManager::printPartitionInfo(unsigned int no) const {
	assert(no < m_partitionCount);
	cout << "===========================================" << endl;
	cout << "Data for partition " << no << endl;
	cout << "===========================================" << endl;
	cout << "Partition metadata located at " << hex << m_partitions[no] << dec
			<< endl;
	cout << "Row count: " << getPartitionRowCount(no) << endl;
	cout << "Col count: " << m_colCount << endl;
	cout << "Nonzero count: " << getPartitionNZCount(no) << endl;
	cout << "Starting row: " << getPartitionData(no)->startingRow << endl;
	cout << "ColPtr * = " << hex << getPartitionColPtr(no) << dec << endl;
	cout << "RowInd * = " << hex << getPartitionRowInd(no) << dec << endl;
}

void GraphManager::printAllPartitionInfo() const {
	for (unsigned int i = 0; i < m_partitionCount; i++)
		printPartitionInfo(i);
}

void GraphManager::dumpPartitionData(unsigned int no) const {
	GraphMatrixData * data = getPartitionData(no);
	cout << "===========================================" << endl;
	cout << "Dump for partition " << no << endl;
	cout << "===========================================" << endl;
	cout << "ColPtr 0x" << hex << getPartitionColPtr(no) << dec << endl;
	for(unsigned int i=0; i < data->cols+1; i++) {
		cout << data->colPtr[i] << " ";
	}
	cout << endl;
}

void GraphManager::parseConfig(unsigned int * configBase) {
// first 4 bytes of config is number of partitions (P)
m_partitionCount = configBase[0];
// next 4 * P bytes are P pointers to partition configs
m_partitions = (GraphMatrixData **) &(configBase[1]);

// for now, limit partition count to be 0 < p = 16
assert(m_partitionCount > 0);
assert(m_partitionCount <= 16);

m_rowCount = 0;
m_colCount = m_partitions[0]->cols;
m_nzCount = 0;
m_largestPartitionRowCount = 0;

for (unsigned int i = 0; i < m_partitionCount; i++) {
	GraphMatrixData * partition = m_partitions[i];
	// assume horizontal cuts - total rows is the sum of partitions
	m_rowCount += partition->rows;
	m_nzCount += partition->nz;
	m_largestPartitionRowCount = (
			m_rowCount > m_largestPartitionRowCount ?
					m_rowCount : m_largestPartitionRowCount);
	// all partitions should have equal num of cols
	assert(m_colCount == partition->cols);
}
}
