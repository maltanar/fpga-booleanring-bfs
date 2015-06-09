#include "BitmapBFSOperation.h"
#include <string.h>

unsigned int DenseToSparse(unsigned int * denseBase, unsigned int denseCount,
		unsigned int value, unsigned int * sparseBase) {
	volatile unsigned int * inputRegs = (volatile unsigned int *) 0x43c80000;
	volatile unsigned int * outputRegs = (volatile unsigned int *) 0x43c90000;

	typedef enum {
		regInSparseCount = 0,
		regInFinished = 1,
		regOutDenseBasePtr = 0,
		regOutSparseBasePtr = 1,
		regOutDenseCount = 2,
		regOutLookForValue = 3,
		regOutStart = 4,
		regInID = 15
	} SparseToDenseRegisters;

	assert(inputRegs[regInID] == 1234567);

	outputRegs[regOutDenseBasePtr] = (unsigned int) denseBase;
	outputRegs[regOutLookForValue] = value;
	outputRegs[regOutDenseCount] = denseCount;
	outputRegs[regOutSparseBasePtr] = (unsigned int) sparseBase;

	// give start signal
	outputRegs[regOutStart] = 1;
	// wait until finished
	while (inputRegs[regInFinished] != 1)
		;

	// back up frontier size value and return
	unsigned int frontier = inputRegs[regInSparseCount];
	outputRegs[regOutStart] = 0;

	return frontier;
}

BitmapBFSOperation::BitmapBFSOperation(GraphMatrixData* graph) :
		BFSOperation(graph) {
	m_frontier = new SimpleQueue(graph->cols);
	m_bitmapWordCount = (graph->cols / 32) + 1;
	m_bitmap = new unsigned int[m_bitmapWordCount];
	m_isBitmapOurAllocation = true;
	m_edgeVisits = 0;
	assert(m_frontier);
	assert(m_bitmap);

	resetBFS();
}

BitmapBFSOperation::~BitmapBFSOperation() {
	if (m_isBitmapOurAllocation)
		delete m_bitmap;
	delete m_frontier;
}

unsigned int BitmapBFSOperation::step() {
	// perform the classical BFS algorithm
	unsigned int * ptrs = m_graph->colPtr;
	unsigned int * inds = m_graph->rowInd;

	SimpleQueue * nextFrontier = new SimpleQueue(m_graph->cols);
	assert(nextFrontier);

	m_edgeVisits = 0;

	while (!m_frontier->isEmpty()) {
		unsigned int v = m_frontier->pop();

		unsigned int neighbors_start = ptrs[v];
		unsigned int neighbors_end = ptrs[v + 1];

		for (unsigned int e = neighbors_start; e < neighbors_end; e++) {
			unsigned int neighbor = inds[e];
			//m_edgeVisits++;

			if (testBit(neighbor) == false) {
				m_edgeVisits+=ptrs[neighbor+1]-ptrs[neighbor];
				nextFrontier->push(neighbor);
				m_resultCount++;
				m_resultVector[neighbor] = m_nextDistance;
				setBit(neighbor);
			}
		}
	}

	delete m_frontier;

	m_frontier = nextFrontier;
	m_nextDistance++;

	if (m_frontier->isEmpty()) {
		m_isConverged = true;
		return 0;
	} else {
		return m_frontier->size();
	}
}

void BitmapBFSOperation::resetBFS() {
	BFSOperation::resetBFS();
	delete m_frontier;

	m_frontier = new SimpleQueue(m_graph->cols);
	assert(m_frontier);
	memset(m_bitmap, 0, 4 * m_bitmapWordCount);
}

void BitmapBFSOperation::setRootNode(unsigned int number) {
	BFSOperation::setRootNode(number);

	m_frontier->push(m_rootNode);
	m_resultVector[m_rootNode] = 0;
	setBit(m_rootNode);
	m_nextDistance++;
}

inline void BitmapBFSOperation::setBit(unsigned int ind) {
	m_bitmap[ind / 32] = m_bitmap[ind / 32] | (1 << (ind % 32));
}

unsigned int* BitmapBFSOperation::getBitmap() {
	return m_bitmap;
}

void BitmapBFSOperation::setBitmap(unsigned int * newBitmap) {
	if (m_isBitmapOurAllocation)
		delete[] m_bitmap;
	m_isBitmapOurAllocation = false;
	m_bitmap = newBitmap;
}

unsigned int BitmapBFSOperation::reconstructFrontier(bool useHWAcceleration) {
	delete m_frontier;
	m_frontier = new SimpleQueue(m_graph->cols);

	if (!useHWAcceleration) {
		// reconstruct the frontier by scanning the result vector and finding the indices of the
		// elements that were written in the previous step (as indicated by m_nextDistance)
		for (unsigned int i = 0; i < m_graph->cols; i++) {
			if (m_resultVector[i] == m_nextDistance - 1)
				m_frontier->push(i);
		}
	} else {
		// use the hw accelerator to speed up frontier reconstruction
		unsigned int * sparseBuffer = m_frontier->getBuffer();
		unsigned int frontierSize = DenseToSparse(
				(unsigned int *) m_resultVector, m_graph->cols,
				(m_nextDistance - 1), sparseBuffer);
		m_frontier->setPointers(0, frontierSize);
	}

	return m_frontier->size();
}

inline bool BitmapBFSOperation::testBit(unsigned int ind) {
	return ((m_bitmap[ind / 32] & (1 << (ind % 32))) != 0);
}

SimpleQueue::SimpleQueue(unsigned int maxSize) {
	m_queue = new unsigned int[maxSize];
	m_head = 0;
	m_tail = 0;

	assert(m_queue);
}

SimpleQueue::~SimpleQueue() {
	delete[] m_queue;
}

void SimpleQueue::push(unsigned int element) {
	m_queue[m_tail] = element;
	m_tail++;
}

unsigned int SimpleQueue::pop() {
	unsigned int elem = m_queue[m_head];
	m_head++;
	return elem;
}

unsigned int SimpleQueue::size() {
	return m_tail - m_head;
}

bool SimpleQueue::isEmpty() {
	return size() == 0;
}
