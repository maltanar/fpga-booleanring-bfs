#ifndef BITMAPBFSOPERATION_H_
#define BITMAPBFSOPERATION_H_

#include <queue>
#include "bfsoperation.h"

class SimpleQueue {
public:
	SimpleQueue(unsigned int maxSize);
	~SimpleQueue();

	void push(unsigned int element);
	unsigned int pop();
	unsigned int size();
	bool isEmpty();

	unsigned int * getBuffer() {return m_queue;};
	void setPointers(unsigned int head, unsigned int tail) {m_head = head; m_tail = tail;};

protected:
	unsigned int * m_queue;
	unsigned int m_head, m_tail;
};

class BitmapBFSOperation: public BFSOperation {
public:
	BitmapBFSOperation(GraphMatrixData * graph);
	virtual ~BitmapBFSOperation();

	unsigned int * getBitmap();
	void setBitmap(unsigned int *);
	unsigned int getBitmapWordCount() { return m_bitmapWordCount; } ;

	virtual unsigned int step();
	virtual void resetBFS();
	virtual void setRootNode(unsigned int number);

	unsigned int reconstructFrontier(bool useHWAcceleration);
	unsigned int getEdgeVisits() {return m_edgeVisits;};

protected:
	SimpleQueue * m_frontier;
	unsigned int * m_bitmap;
	unsigned int m_bitmapWordCount;
	unsigned int m_edgeVisits;
	bool m_isBitmapOurAllocation;

	// helper functions for visited bit set/test (inlined)
	void setBit(unsigned int ind);
	bool testBit(unsigned int ind);
};

#endif /* BITMAPBFSOPERATION_H_ */
