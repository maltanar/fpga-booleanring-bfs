#ifndef CLASSICALBFSOPERATION_H
#define CLASSICALBFSOPERATION_H

#include <queue>
#include "bfsoperation.h"

class ClassicalBFSOperation : public BFSOperation
{
public:
    ClassicalBFSOperation(GraphMatrixData * graph);
    ~ClassicalBFSOperation();

    virtual unsigned int step();
    virtual void resetBFS();
    virtual void setRootNode(unsigned int number);


protected:
    std::queue<unsigned int> * m_frontier;
};

#endif // CLASSICALBFSOPERATION_H
