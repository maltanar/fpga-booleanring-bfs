#ifndef BFSOPERATION_H
#define BFSOPERATION_H

#include "GraphManager.h"

class BFSOperation
{
public:
    BFSOperation(GraphMatrixData * graph);
    ~BFSOperation();

    virtual void step() = 0;

    virtual void resetBFS();

    void copyResultVector(unsigned int * dest);

    virtual void setRootNode(unsigned int number);
    unsigned int getRootNode();
    unsigned int getNextDistance();

    int *getResultVector();

    void printResultVector();

    bool isConverged() const { return m_isConverged; }
    unsigned int getResultCount() const { return m_resultCount; }


protected:
    GraphMatrixData * m_graph;

    unsigned int m_nextDistance;
    int * m_resultVector;
    unsigned int m_rootNode;
    unsigned int m_resultCount;
    bool m_isConverged;

};

#endif // BFSOPERATION_H
