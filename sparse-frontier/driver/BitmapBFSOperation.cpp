#include "BitmapBFSOperation.h"
#include <string.h>

BitmapBFSOperation::BitmapBFSOperation(GraphMatrixData* graph) :
		BFSOperation(graph) {
	m_frontier = new SimpleQueue(graph->cols);
	m_bitmapWordCount = (graph->cols / 32) + 1;
	m_bitmap = new unsigned int[m_bitmapWordCount];

	resetBFS();
}

BitmapBFSOperation::~BitmapBFSOperation() {
	delete m_bitmap;
	delete m_frontier;
}

unsigned int BitmapBFSOperation::step() {
	// perform the classical BFS algorithm
	unsigned int * ptrs = m_graph->colPtr;
	unsigned int * inds = m_graph->rowInd;

	SimpleQueue * nextFrontier = new SimpleQueue(m_graph->cols);

	while (!m_frontier->isEmpty()) {
		unsigned int v = m_frontier->pop();

		unsigned int neighbors_start = ptrs[v];
		unsigned int neighbors_end = ptrs[v + 1];

		for (unsigned int e = neighbors_start; e < neighbors_end; e++) {
			unsigned int neighbor = inds[e];

			if (testBit(neighbor) == false) {
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

void BitmapBFSOperation::rebuildFrontierFromDistVec() {
	DistVecElem prevDist = m_nextDistance - 1;

	if (m_frontier)
		delete m_frontier;

	m_frontier = new SimpleQueue(m_graph->cols);

	for (unsigned int i = 0; i < m_graph->cols; i++) {
		if (m_resultVector[i] == prevDist)
			m_frontier->push(i);
		if (m_resultVector[i] != -1)
			setBit(i);
	}
}

inline bool BitmapBFSOperation::testBit(unsigned int ind) {
	return ((m_bitmap[ind / 32] & (1 << (ind % 32))) != 0);
}

SimpleQueue::SimpleQueue(unsigned int maxSize) {
	m_queue = new unsigned int[maxSize];
	m_head = 0;
	m_tail = 0;
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
