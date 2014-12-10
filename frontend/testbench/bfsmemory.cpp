#include "bfsmemory.h"


#define DEBUG_PORTB_WRITES

BFSMemory::BFSMemory(sc_module_name name)
{
    SC_CTHREAD(memoryPortA, clk.pos());
    SC_CTHREAD(memoryPortB, clk.pos());
}

bool BFSMemory::checkMemoryContents(unsigned int * cmp, unsigned int wordCount)
{
    bool result = true;

    for(int i = 0; i < wordCount; i++)
        if(m_memory[i] != cmp[i])
        {
            cout << "incorrect mem contents at word addr " << i << endl;
            cout << "expected " << cmp[i] << " found " << m_memory[i] << endl;
            result=false;
        }

    return result;
}

unsigned int *BFSMemory::readAll()
{
    return m_memory;
}

void BFSMemory::memoryPortA()
{
    portA_dataOut = 0;

    while(1)
    {
        wait(1);

        unsigned int addr = portA_addr;
        bool writeEn = portA_writeEn;
        unsigned int dataIn = portA_dataIn;
        //cout << "portA addr " << addr << " val " << m_memory[addr] <<  " at " << NOW << endl;

        portA_dataOut = m_memory[addr];

        if(writeEn)
        {
            m_memory[addr] = dataIn;
            //cout << "portA write addr = " << addr << " data = " << dataIn << " at " << NOW << endl;
        }
    }

}

void BFSMemory::memoryPortB()
{
    portB_dataOut = false;

    while(1)
    {
        wait(1);

        unsigned int addr = portB_addr;
        bool writeEn = portB_writeEn;
        bool dataIn = portB_dataIn;

        portB_dataOut = (bool)((m_memory[addr >> 5] >> (addr & 0x1F)) & 0x1 == 0x1);

        if(writeEn)
        {

            unsigned int ldWord = m_memory[addr >> 5];
#ifdef DEBUG_PORTB_WRITES
            cout << "portB write addr = " << addr << " data = " << dataIn << " at " << sc_time_stamp() << endl;
            cout << "ldWord addr = " << (addr >> 5) << " value = " << ldWord << endl;
            cout << "ldWord desired bit index = " << (addr & 0x1F) << endl;
#endif
            if(dataIn)
                ldWord = ldWord | (1 << (addr & 0x1F));
            else
                ldWord = ldWord & ~(1 << (addr & 0x1F));

            //cout << "ldWord new value = " << ldWord << endl;

            m_memory[addr >> 5] = ldWord;
        }
    }

}
