#include "axislave.h"

AXISlave::AXISlave(sc_module_name name) : sc_module(name)
{
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
            m_readReqs.write(readAddr.read());
        }
    }
}

void AXISlave::performReads()
{
    while(1)
    {
        AXIAddress req = m_readReqs.read();

        AXIReadData data;

        data.id = req.id;
        data.data = req.addr;
        data.resp = 0;

        m_readResps.write(data);
    }
}

void AXISlave::pushReadResponses()
{
    while(1)
    {
        readDataValid = false;

        AXIReadData data = m_readResps.read();
        readData = data;
        readDataValid = true;

        while(!readDataReady)
            wait(1);
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

        // TODO implement some write functionality here

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
