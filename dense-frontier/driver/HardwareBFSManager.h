#ifndef HARDWAREBFSMANAGER_H_
#define HARDWAREBFSMANAGER_H_

#include "GraphManager.h"
#include "BFSAccelerator.h"

extern unsigned int hardwarePECount;
#define	BFS_PE_COUNT	4
#define RESVEC_BASE		(0x1F000000)

#define iForEachPE(expr)	for(int i = 0; i < hardwarePECount; i++) {expr}

// TODO add support for non-static PE<->partition assignments
// that will enable processing larger graphs than we have BRAM for, in several stripes
// in that case, we need an additional buffer in main memory to copy partial results into

class HardwareBFSManager {
public:
	HardwareBFSManager(unsigned int * inputRegs, unsigned int * outputRegs);
	virtual ~HardwareBFSManager();

	void printDistanceVector(bool verbose);
	void printInputVector();

	void setGraph(GraphManager * graphMan);
	BFSAccelerator * getPE(int i);
	void setNextDistance(unsigned int dist);

	// initialize distanceVector, inputVector from src
	void initFromBitmap(unsigned int * bitmap);				// copy from bitmap
	void initVectorSingleRoot(unsigned int root);		// unset all except root

	void initAccelBRAMs();
	void verifyAccelBRAMs();

	void assignPartition(unsigned int partitionInd, int peInd); // assign partition to PE, init result BRAM
	unsigned int copyPEResultToDRAM(int peInd);
	void step(bool printStats);
	unsigned int updateResults_Software();
	unsigned int updateResults_Hardware();

	void resetAll();
	void clearAllResultVectors();


protected:
	GraphManager * m_graphMan;
	BFSAccelerator m_pe[BFS_PE_COUNT];
	GraphMatrixData * m_assignedPartition[BFS_PE_COUNT];	// which partition assigned to each PE
	bool m_busy[BFS_PE_COUNT];	// busy status for each PE

	DistVecElem * m_distanceVector;	// the "final result" of BFS, 4 bytes per node (distance to root)
	unsigned int * m_inputVector;		// PE input dense vector, 1 bit per node (visited/unvisited)
	unsigned int m_inputVectorWordCount;
	unsigned int m_bfsDistance;
	bool m_deallocateBitmap;


	void waitAllPEsFinished();	// temporary busy wait/polling solution, checking PE status
	void startAll();
	void deinitAll();

	GraphMatrixData * m_identityMatrix;
	void createIdentityMatrix();
	void freeIdentityMatrix();
};

#endif /* HARDWAREBFSMANAGER_H_ */
