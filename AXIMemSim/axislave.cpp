#include "axislave.h"

AXISlave::AXISlave(sc_module_name name) : sc_module(name)
{
    // TODO make FIFO sizes customizable
    // threads for reads
    SC_CTHREAD(pullReadRequests, clk.pos());
    SC_THREAD(performReads);
    SC_CTHREAD(pushReadResponses, clk.pos());
    // threads for writes
    SC_CTHREAD(pullWriteRequests, clk.pos());
    SC_CTHREAD(pullWriteData, clk.pos());
    SC_THREAD(performWrites);
    SC_CTHREAD(pushWriteResponses, clk.pos());
}

void AXISlave::pullReadRequests()
{
    while(1)
    {
        wait(1);

        readAddrReady = (m_readReqs.num_free() > 0);

        if(m_readReqs.num_free() && readAddrValid)
        {
            DEBUG_AXISLAVE(cout << "read request at " << sc_time_stamp() << ": " << readAddr.read());
            m_readReqs.write(readAddr.read());
        }
    }
}

void AXISlave::performReads()
{
    while(1)
    {
        AXIAddress req = m_readReqs.read();

        const unsigned int beatCount = req.len;
        DEBUG_AXISLAVE(cout << "performing burst read of N-1 = " << beatCount << endl);

        AXIReadData data;

        // TODO derive class for fixed-latency memory with reads/writes
        data.id = req.id;
        data.data = req.addr;
        data.resp = 0;
        data.last = false;

        for(unsigned int i = 0; i < beatCount; i++)
        {
            data.data = req.addr + i;
            m_readResps.write(data);
        }

        // AXI sets burst length to N-1
        data.data = req.addr + beatCount;
        data.last = true;
        m_readResps.write(data);
    }
}

void AXISlave::pushReadResponses()
{
    while(1)
    {
        wait(1);

        readDataValid = false;

        AXIReadData data = m_readResps.read();
        readData = data;
        readDataValid = true;

        while(readDataReady.read() != true)
            wait(1);

        DEBUG_AXISLAVE(cout << "read response at " << sc_time_stamp() << ": " << readData.read());
    }
}

void AXISlave::pullWriteRequests()
{
    while(1)
    {
        writeAddrReady = (m_writeReqs.num_free() > 0);

        wait(1);

        if(m_writeReqs.num_free() && writeAddrValid)
        {
            m_writeReqs.write(writeAddr.read());
        }
    }
}

void AXISlave::pullWriteData()
{
    while(1)
    {
        writeDataReady = (m_writeData.num_free() > 0);

        wait(1);

        if(m_writeData.num_free() && writeDataValid)
        {
            m_writeData.write(writeData.read());
        }
    }
}

void AXISlave::performWrites()
{
    while(1)
    {
        AXIAddress req = m_writeReqs.read();
        AXIWriteData data = m_writeData.read();

        // TODO write burst support
        // TODO write ID checks?

        AXIWriteResponse resp;
        resp.id = req.id;
        resp.resp = 0;

        m_writeResps.write(resp);

    }

}

void AXISlave::pushWriteResponses()
{
    while (1)
    {
        writeRespValid = false;

        AXIWriteResponse resp = m_writeResps.read();
        writeRespValid = true;

        while(!writeRespReady)
            wait(1);
    }

}
