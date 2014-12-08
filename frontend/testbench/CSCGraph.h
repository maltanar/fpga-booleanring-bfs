#ifndef CSCGRAPH_H
#define CSCGRAPH_H

#include <QString>
#include <QList>

typedef unsigned int CSCPtr;

class CSCGraph
{
public:
    CSCGraph(QString matrixFileName, bool includeMatrixValues = false);
    ~CSCGraph();

    CSCPtr rowCount() {return m_rowCount;}
    CSCPtr colCount() { return m_colCount;}
    CSCPtr nzCount() {return m_nzCount;}

    QList<CSCPtr> getColLengths();
    QList<CSCPtr> getRowIndices();

protected:
    QString m_matrixName;
    CSCPtr m_rowCount, m_colCount, m_nzCount;
    CSCPtr * m_matrixValues;
    CSCPtr * m_rowIndices;
    CSCPtr * m_colPointers;

};

#endif // CSCGRAPH_H
