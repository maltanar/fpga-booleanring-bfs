#ifndef BFSOPERATION_H
#define BFSOPERATION_H

#include "GraphManager.h"

class BFSOperation
{
public:
    BFSOperation(GraphMatrixData * graph);
    ~BFSOperation();

    virtual unsigned int step() = 0;

    virtual void resetBFS();

    void copyResultVector(unsigned int * dest);

    virtual void setRootNode(unsigned int number);
    unsigned int getRootNode();
    unsigned int getNextDistance();
    void setNextDistance(unsigned int level);

    DistVecElem *getResultVector();

    void printResultVector();

    bool isConverged() const { return m_isConverged; }
    unsigned int getResultCount() const { return m_resultCount; }


protected:
    GraphMatrixData * m_graph;

    DistVecElem m_nextDistance;
    DistVecElem * m_resultVector;
    unsigned int m_rootNode;
    unsigned int m_resultCount;
    bool m_isConverged;

};

#endif // BFSOPERATION_H
