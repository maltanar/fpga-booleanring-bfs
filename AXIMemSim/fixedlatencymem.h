#ifndef FIXEDLATENCYMEM_H
#define FIXEDLATENCYMEM_H

#include <QMap>
#include <systemc.h>
#include "types.h"
#include "params.h"


class FixedLatencyMem : public sc_module
{
    SC_HAS_PROCESS(FixedLatencyMem);

public:
    FixedLatencyMem(sc_module_name name);
    ~FixedLatencyMem();

    void setResponseFIFO(sc_fifo<MemResponse> * fifo);

    sc_in_clk clk;

    bool canAcceptRequest();
    void addRequest(MemRequest r);

    // SystemC threads/methods
    void processRequests();

protected:
    QMap<double, MemRequest> m_transactionQueue;
    unsigned int * m_memory;
    sc_fifo<MemResponse> * m_responseFIFO;

    MemResponse performRequest(MemRequest req);
};

#endif // FIXEDLATENCYMEM_H
