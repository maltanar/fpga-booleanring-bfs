/*
 * GraphManager.h
 *
 *  Created on: Feb 2, 2015
 *      Author: maltanar
 */

#ifndef GRAPHMANAGER_H_
#define GRAPHMANAGER_H_

#include <assert.h>
#include <stdint.h>

extern unsigned int matrixCountP1;
extern unsigned int matrixCountP2;
extern unsigned int matrixCountP4;

void * loadMatrixP1(unsigned int id);
void * loadMatrixP2(unsigned int id);
void * loadMatrixP3(unsigned int id);
void * loadMatrixP4(unsigned int id);
void * loadMatrixP5(unsigned int id);

const char * getMatrixNameP1(unsigned int id);
const char * getMatrixNameP2(unsigned int id);
const char * getMatrixNameP3(unsigned int id);
const char * getMatrixNameP4(unsigned int id);
const char * getMatrixNameP5(unsigned int id);

#define VERBOSE(x)	x;

typedef int DistVecElem;

typedef struct {
	unsigned int rows;
	unsigned int cols;
	unsigned int nz;
	unsigned int startingRow;
	unsigned int * colPtr;
	unsigned int * rowInd;
} GraphMatrixData;

class GraphManager {
public:
	GraphManager(unsigned int * configBase);
	virtual ~GraphManager();

	void printBaseInfo() const;
	void printPartitionInfo(unsigned int no) const;
	void printAllPartitionInfo() const;
	void dumpPartitionData(unsigned int no) const;

	unsigned int getTotalWorkloadSize() const {
		return m_nzCount*4 + m_partitionCount*(m_colCount+1)*4;
	}

	unsigned int getColCount() const {
		return m_colCount;
	}

	unsigned int getNzCount() const {
		return m_nzCount;
	}

	unsigned int getPartitionCount() const {
		return m_partitionCount;
	}

	unsigned int getRowCount() const {
		return m_rowCount;
	}

	unsigned int getLargestPartitionRowCount() const {
		return m_largestPartitionRowCount;
	}

	unsigned int getPartitionRowCount(unsigned int no) const {
		return m_partitions[no]->rows;
	}

	unsigned int getPartitionNZCount(unsigned int no) const {
		return m_partitions[no]->nz;
	}

	unsigned int * getPartitionColPtr(unsigned int no) const {
		return m_partitions[no]->colPtr;
	}

	unsigned int * getPartitionRowInd(unsigned int no) const {
		return m_partitions[no]->rowInd;
	}

	GraphMatrixData * getPartitionData(unsigned int no) const {
		return m_partitions[no];
	}

protected:
	GraphMatrixData ** m_partitions;
	unsigned int m_partitionCount;

	unsigned int m_rowCount, m_colCount, m_nzCount;
	unsigned int m_largestPartitionRowCount;

	void parseConfig(unsigned int * configBase);
};

#endif /* GRAPHMANAGER_H_ */
