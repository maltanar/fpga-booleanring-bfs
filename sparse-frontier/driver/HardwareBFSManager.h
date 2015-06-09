#ifndef HARDWAREBFSMANAGER_H_
#define HARDWAREBFSMANAGER_H_

#include "GraphManager.h"
#include "BFSAccelerator.h"

extern unsigned int hardwarePECount;

#define RESVEC_BASE		(0x1F000000)
#define	MAX_PE			5
#define iForEachPE(expr)	for(int i = 0; i < hardwarePECount; i++) {expr}

// TODO add support for non-static PE<->partition assignments
// that will enable processing larger graphs than we have BRAM for, in several stripes
// in that case, we need an additional buffer in main memory to copy partial results into

class HardwareBFSManager {
public:
	HardwareBFSManager(unsigned int * baseAddrs);
	virtual ~HardwareBFSManager();

	void printDistanceVector();

	void setGraph(GraphManager * graphMan);
	BFSAccelerator * getPE(int i);
	void setDistance(unsigned int dist);

	// initialize distvec and result BRAM
	void initVector(DistVecElem * src, unsigned int count);				// copy from vector
	void initVectorSingleRoot(unsigned int root);		// unset all except root

	void assignPartition(unsigned int partitionInd, unsigned int peInd); // assign partition to PE, init result BRAM

	void step();
	unsigned int levelGeneration();
	void printProfiles();

	void resetAll();

	unsigned int getMaxPECycles();
	unsigned int getLastFrontierSize() {return m_lastFrontierSize;}


protected:
	GraphManager * m_graphMan;
	BFSAccelerator * m_pe[MAX_PE];
	GraphMatrixData * m_assignedPartition[MAX_PE];	// which partition assigned to each PE
	bool m_busy[MAX_PE];	// busy status for each PE

	DistVecElem * m_distanceVector;	// the "final result" of BFS, 4 bytes per node (distance to root)
	unsigned int m_bfsDistance;
	unsigned int m_lastFrontierSize;


	void waitAllPEsFinished();	// temporary busy wait/polling solution, checking PE status
	void startAll();
	void deinitAll();
};

#endif /* HARDWAREBFSMANAGER_H_ */
