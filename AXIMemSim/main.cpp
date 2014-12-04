#include <iostream>
#include <systemc.h>

#include "fixedlatencymem.h"

using namespace std;


SC_MODULE(top)
{
    sc_in_clk clk;
    sc_fifo<MemResponse> resps;
    FixedLatencyMem mem;

    SC_CTOR(top) : mem("mem")
    {
        mem.clk(clk);

        mem.setResponseFIFO(&resps);

        SC_CTHREAD(pushRequests, clk.pos());
        SC_CTHREAD(popResponses, clk.pos());
    }

    void pushRequests()
    {
        int n = 0;

        while(n++ < 10)
        {
            wait(1);
            if(mem.canAcceptRequest())
            {
                MemRequest req;
                req.addr = 4*n;
                req.burstLen = 1;
                req.id = 1;
                req.isWrite = false;

                mem.addRequest(req);

                cout << sc_time_stamp() << " added read request to "  << req.addr << endl;
            }
            else
            {
                cout << sc_time_stamp() << " mem could not accept request" << endl;
            }
        }
    }

    void popResponses()
    {
        while(1)
        {
            wait(1);
            if(resps.num_available() > 0)
            {
                cout << sc_time_stamp() << " got response " << resps.read() << endl;
            }
        }
    }
};




int sc_main(int argc, char *argv[])
{
    sc_clock clk("clk", CLOCK_CYCLE);
    top t("t");
    t.clk(clk);

    sc_start();

    return 0;
}
