#include "fixedlatencymem.h"

FixedLatencyMem::FixedLatencyMem(sc_module_name name) : sc_module(name)
{
    m_memory = new unsigned int[MEMORY_SIZE_WORDS];

    for(unsigned int i = 0; i < MEMORY_SIZE_WORDS; i++)
        m_memory[i] = i;

    SC_CTHREAD(processRequests, clk.pos());
}

FixedLatencyMem::~FixedLatencyMem()
{
    delete m_memory;
}

void FixedLatencyMem::setResponseFIFO(sc_fifo<MemResponse> *fifo)
{
    m_responseFIFO = fifo;
}

bool FixedLatencyMem::canAcceptRequest()
{
    return (m_transactionQueue.size() < MEMORY_MAX_REQS);
}

void FixedLatencyMem::addRequest(MemRequest r)
{
    double time_disp = (sc_time_stamp() + MEMORY_LATENCY).to_double();

    m_transactionQueue[time_disp] = r;
}

void FixedLatencyMem::processRequests()
{
    while(1)
    {
        wait(1);

        double time_now = sc_time_stamp().to_double();

        if(m_transactionQueue.contains(time_now))
        {
            MemRequest req = m_transactionQueue[time_now];
            m_transactionQueue.remove(time_now);

            MemResponse resp = performRequest(req);

            m_responseFIFO->write(resp);
        }
    }
}

MemResponse FixedLatencyMem::performRequest(MemRequest req)
{
    MemAddress wordAddr = req.addr / sizeof(MemWord);
    // bounds check
    sc_assert(wordAddr < MEMORY_SIZE_WORDS);

    MemResponse resp;
    resp.id = req.id;
    resp.isWrite = req.isWrite;

    if(req.isWrite)
    {
        m_memory[wordAddr] = req.writeData;
    }
    else
    {
        resp.readData = m_memory[wordAddr];
    }

    return resp;
}


