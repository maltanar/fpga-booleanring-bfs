#include "CSCGraph.h"
#include <QDataStream>
#include <QFile>
#include <QDebug>

#include <iostream>

CSCGraph::CSCGraph(QString matrixFileName, bool includeMatrixValues)
{
    if (includeMatrixValues)
    {
        std::cerr << "Reading matrix (edge) values are not yet suppported" << std::endl;
        return;
    }

    QFile f(matrixFileName);

    if(!f.open(QIODevice::ReadOnly))
    {
        std::cerr << "Could not open file: " << std::endl << matrixFileName.toStdString() << std::endl;
        return;
    }

    m_matrixValues = NULL;
    m_rowIndices = NULL;
    m_colPointers = NULL;
    m_rowCount = 0;
    m_colCount = 0;
    m_nzCount = 0;


    // read matrix dimensions
    f.read((char*)&m_rowCount, sizeof(CSCPtr));
    f.read((char*)&m_colCount, sizeof(CSCPtr));
    f.read((char*)&m_nzCount, sizeof(CSCPtr));

    if ( m_rowCount != m_colCount )
    {
        std::cerr << "Non-square matrices cannot be processed as graphs" << std::endl;
        f.close();
        return;
    }

    // read in the row indices
    m_rowIndices = new CSCPtr[m_nzCount];
    f.read((char *)m_rowIndices, m_nzCount * sizeof(CSCPtr));

    // read in the col pointers
    m_colPointers = new CSCPtr[m_rowCount + 1];
    f.read((char *)m_colPointers, (m_rowCount + 1) * sizeof(CSCPtr));

    // TODO read in matrix values

    f.close();
}

CSCGraph::~CSCGraph()
{
    delete [] m_rowIndices;
    delete [] m_colPointers;
}


QList<CSCPtr> CSCGraph::getColLengths()
{
    QList<CSCPtr> colLengths;

    for(CSCPtr i = 0; i < m_colCount; i++)
    {
        colLengths.push_back(m_colPointers[i+1] - m_colPointers[i]);
    }

    return colLengths;
}

QList<CSCPtr> CSCGraph::getRowIndices()
{
    QList<CSCPtr> rowIndices;

    for(CSCPtr i = 0; i < m_nzCount; i++)
    {
        rowIndices.push_back(m_rowIndices[i]);
    }

    return rowIndices;
}
