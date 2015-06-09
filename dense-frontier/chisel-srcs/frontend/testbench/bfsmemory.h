#ifndef BFSMEMORY_H
#define BFSMEMORY_H

#include <systemc.h>

#define MEM_WORD_COUNT      1024

class BFSMemory : public sc_module
{
    SC_HAS_PROCESS(BFSMemory);
public:
    BFSMemory(sc_module_name name);

    sc_in_clk clk;

    sc_in<bool>	portA_writeEn;
    sc_in<uint32_t>	portA_addr;
    sc_in<uint32_t>	portA_dataIn;
    sc_out<uint32_t>	portA_dataOut;

    sc_in<bool>	portB_dataIn;
    sc_in<bool>	portB_writeEn;
    sc_in<uint32_t>	portB_addr;
    sc_out<bool>	portB_dataOut;


    void memoryPortA();
    void memoryPortB();

    bool checkMemoryContents(unsigned int * cmp, unsigned int wordCount);
    unsigned int *readAll();

protected:
    unsigned int m_memory[MEM_WORD_COUNT];

};

#endif // BFSMEMORY_H
