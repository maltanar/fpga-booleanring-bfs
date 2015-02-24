#include "classicalbfsoperation.h"
#include <iostream>

ClassicalBFSOperation::ClassicalBFSOperation(GraphMatrixData *graph) :
    BFSOperation(graph)
{
    m_frontier = new std::queue<unsigned int>();
}

ClassicalBFSOperation::~ClassicalBFSOperation()
{
    delete m_frontier;
}

void ClassicalBFSOperation::step()
{
    // perform the classical BFS algorithm
    unsigned int * ptrs = m_graph->colPtr;
    unsigned int * inds = m_graph->rowInd;

    std::queue<unsigned int> * nextFrontier = new std::queue<unsigned int>();

    while(!m_frontier->empty()) {
        unsigned int v = m_frontier->front();
        m_frontier->pop();

        unsigned int neighbors_start = ptrs[v];
        unsigned int neighbors_end = ptrs[v+1];

        for(unsigned int e = neighbors_start; e < neighbors_end; e++) {
            unsigned int neighbor = inds[e];

            if(m_resultVector[neighbor] == -1) {
                nextFrontier->push(neighbor);
                m_resultCount++;
                m_resultVector[neighbor] = m_nextDistance;
            }
        }
    }

    delete m_frontier;

    m_frontier = nextFrontier;
    m_nextDistance++;

    if(m_frontier->empty())
    	m_isConverged = true;
    else {
    	std::cout << "Frontier size at step " << m_nextDistance << " = " << m_frontier->size() << std::endl;
    }

}

void ClassicalBFSOperation::resetBFS()
{
    BFSOperation::resetBFS();
    delete m_frontier;

    m_frontier = new std::queue<unsigned int>();
}

void ClassicalBFSOperation::setRootNode(unsigned int number)
{
    BFSOperation::setRootNode(number);

    m_frontier->push(m_rootNode);
    m_resultVector[m_rootNode] = 0;
    m_nextDistance++;
}
