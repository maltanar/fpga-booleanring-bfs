#include <iostream>
#include <systemc.h>

#include "peripheral-src/VDataPuller.h"
#include "aximasterwrapper.h"
#include "axislave.h"

using namespace std;


SC_MODULE(top)
{
    sc_in_clk clk;
    VDataPuller uut;
    AXIMasterWrapper wrp;
    AXISlave slv;
    sc_signal<bool> reset, start, stop;
    sc_signal<bool> matrixReady, vectorReady;
    sc_signal<bool> matrixValid, vectorValid;
    sc_signal<vluint64_t> matrixData, vectorData;

    sc_signal<bool> rav, rar, rdv, rdr, wav, war, wdv, wdr, wrv, wrr;
    sc_signal<AXIAddress> ra, wa;
    sc_signal<AXIReadData> rd;
    sc_signal<AXIWriteData> wd;
    sc_signal<AXIWriteResponse> wr;

    sc_signal<unsigned int> matrixPtr, vectorPtr;


    SC_CTOR(top) : uut("uut"), wrp("wrp"), slv("slv")
    {
        slv.clk(clk);
        uut.clk(clk);
        uut.reset(reset);
        uut.io_start(start);
        uut.io_stop(stop);
        uut.io_matrixData_bits(matrixData);
        uut.io_matrixData_valid(matrixValid);
        uut.io_vectorData_bits(vectorData);
        uut.io_vectorData_valid(vectorValid);
        uut.io_matrixData_ready(matrixReady);
        uut.io_vectorData_ready(vectorReady);
        uut.io_matrixPtr(matrixPtr);
        uut.io_vectorPtr(vectorPtr);

        // setup peripheral <-> AXI master wrapper link
        wrp.setupReadAddrChannel(uut.M_AXI_ARREADY, uut.M_AXI_ARVALID, uut.M_AXI_ARSIZE, uut.M_AXI_ARLEN, uut.M_AXI_ARPROT, uut.M_AXI_ARBURST, uut.M_AXI_ARLOCK, uut.M_AXI_ARCACHE, uut.M_AXI_ARQOS, uut.M_AXI_ARID, uut.M_AXI_ARADDR);
        wrp.setupReadDataChannel(uut.M_AXI_RREADY, uut.M_AXI_RVALID, uut.M_AXI_RID, uut.M_AXI_RLAST, uut.M_AXI_RRESP, uut.M_AXI_RDATA);
        wrp.setupWriteAddrChannel(uut.M_AXI_AWREADY, uut.M_AXI_AWVALID, uut.M_AXI_AWSIZE, uut.M_AXI_AWLEN, uut.M_AXI_AWPROT, uut.M_AXI_AWBURST, uut.M_AXI_AWLOCK, uut.M_AXI_AWCACHE, uut.M_AXI_AWQOS, uut.M_AXI_AWID, uut.M_AXI_AWADDR);
        wrp.setupWriteDataChannel(uut.M_AXI_WREADY, uut.M_AXI_WVALID, uut.M_AXI_WSTRB, uut.M_AXI_WLAST, uut.M_AXI_WDATA);
        wrp.setupWriteRespChannel(uut.M_AXI_BREADY, uut.M_AXI_BVALID, uut.M_AXI_BID, uut.M_AXI_BRESP);

        // setup AXI channels between master and slave
        wrp.readAddr(ra);
        slv.readAddr(ra);
        wrp.readAddrReady(rar);
        slv.readAddrReady(rar);
        wrp.readAddrValid(rav);
        slv.readAddrValid(rav);

        wrp.readData(rd);
        slv.readData(rd);
        wrp.readDataReady(rdr);
        slv.readDataReady(rdr);
        wrp.readDataValid(rdv);
        slv.readDataValid(rdv);

        wrp.writeAddr(wa);
        slv.writeAddr(wa);
        wrp.writeAddrReady(war);
        slv.writeAddrReady(war);
        wrp.writeAddrValid(wav);
        slv.writeAddrValid(wav);

        wrp.writeData(wd);
        slv.writeData(wd);
        wrp.writeDataReady(wdr);
        slv.writeDataReady(wdr);
        wrp.writeDataValid(wdv);
        slv.writeDataValid(wdv);

        wrp.writeResp(wr);
        slv.writeResp(wr);
        wrp.writeRespReady(wrr);
        slv.writeRespReady(wrr);
        wrp.writeRespValid(wrv);
        slv.writeRespValid(wrv);



        SC_THREAD(resetThread);
        SC_CTHREAD(outputMonitorThread, clk.pos());
    }

    void resetThread()
    {
        matrixPtr = 0;
        vectorPtr = 1000;
        start = false;
        stop = false;
        reset = true;
        matrixReady = false;
        vectorReady = false;
        wait(5*CLOCK_CYCLE);
        reset = false;
        start = true;
        matrixReady = true;
        vectorReady = true;
        cout << "Start signal given at " << sc_time_stamp() << endl;
    }

    void outputMonitorThread()
    {
        while(1)
        {
            wait(1);

            if (matrixValid)
            {
                cout << sc_time_stamp() << " valid matrix data: " << matrixData << endl;
            }

            if (vectorValid)
            {
                cout << sc_time_stamp() << " valid vector data: " << vectorData << endl;
            }
        }
    }
};


int sc_main(int argc, char *argv[])
{
    sc_clock clk("clk", CLOCK_CYCLE);
    top t("t");
    t.clk(clk);

    sc_start(100*CLOCK_CYCLE);

    return 0;
}
