#ifndef AXISLAVE_H
#define AXISLAVE_H

#include "types.h"
#include "params.h"

#include <systemc.h>


class AXISlave : public sc_module
{
    SC_HAS_PROCESS(AXISlave);

public:
    AXISlave(sc_module_name name);

    sc_in_clk clk;

    void pullReadRequests();
    void performReads();
    void pushReadResponses();

    void pullWriteRequests();
    void pullWriteData();
    void performWrites();
    void pushWriteResponses();

    // read address channel
    sc_in<AXIAddress> readAddr;
    sc_in<bool> readAddrValid;
    sc_out<bool> readAddrReady;

    // read data channel
    sc_out<AXIReadData> readData;
    sc_out<bool> readDataValid;
    sc_in<bool> readDataReady;

    // write address channel
    sc_in<AXIAddress> writeAddr;
    sc_in<bool> writeAddrValid;
    sc_out<bool> writeAddrReady;

    // write data channel
    sc_in<AXIWriteData> writeData;
    sc_in<bool> writeDataValid;
    sc_out<bool> writeDataReady;

    // write response channel
    sc_out<AXIWriteResponse> writeResp;
    sc_out<bool> writeRespValid;
    sc_in<bool> writeRespReady;

protected:
    sc_fifo<AXIAddress> m_readReqs;
    sc_fifo<AXIReadData> m_readResps;

    sc_fifo<AXIAddress> m_writeReqs;
    sc_fifo<AXIWriteData> m_writeData;
    sc_fifo<AXIWriteResponse> m_writeResps;

};

#endif // AXISLAVE_H
