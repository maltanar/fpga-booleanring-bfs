#include <iostream>
#include <systemc.h>

#include "VFrontendController.h"
#include "InputFIFOAdapter.h"
#include "OutputFIFOAdapter.h"

#include "CSCGraph.h"

#define CLOCK_CYCLE sc_time(1, SC_NS)
#define NOW sc_time_stamp()
#define MEM_WORD_COUNT      1024


class FrontendTester : public sc_module
{
    SC_HAS_PROCESS(FrontendTester);

public:

    sc_in_clk clk;
    sc_signal<bool>	reset;


    sc_signal<bool>	io_start;
    sc_signal<bool>	io_memFill;
    sc_signal<bool>	io_memDump;
    sc_signal<bool>	io_colLengths_ready;
    sc_signal<bool>	io_colLengths_valid;
    sc_signal<bool>	io_rowIndices_ready;
    sc_signal<bool>	io_rowIndices_valid;
    sc_signal<bool>	io_vectorMemDataIn_ready;
    sc_signal<bool>	io_vectorMemDataIn_valid;
    sc_signal<bool>	io_vectorMemDataOut_ready;
    sc_signal<bool>	io_vectorMemDataOut_valid;
    sc_signal<bool>	io_portA_writeEn;
    sc_signal<bool>	io_portB_dataIn;
    sc_signal<bool>	io_portB_writeEn;
    sc_signal<bool>	io_portB_dataOut;
    sc_signal<uint32_t>	io_state;
    sc_signal<uint32_t>	io_portA_addr;
    sc_signal<uint32_t>	io_portB_addr;
    sc_signal<uint32_t>	io_colCount;
    sc_signal<uint32_t>	io_colLengths_bits;
    sc_signal<uint32_t>	io_rowIndices_bits;
    sc_signal<uint32_t>	io_vectorMemDataIn_bits;
    sc_signal<uint32_t>	io_vectorMemDataOut_bits;
    sc_signal<uint32_t>	io_portA_dataIn;
    sc_signal<uint32_t>	io_portA_dataOut;

    sc_fifo<uint32_t> memIn, memOut, rowInd, colLen;
    InputFIFOAdapter<uint32_t> memInAdp;
    OutputFIFOAdapter<uint32_t> memOutAdp;
    InputFIFOAdapter<uint32_t> rowIndAdp, colLenAdp;

    VFrontendController uut;

    unsigned int m_memory[MEM_WORD_COUNT];
    sc_event startFill, startDump;
    sc_event fillFinished, dumpFinished;

    sc_trace_file* Tf;

    FrontendTester(sc_module_name nm) :
        sc_module(nm),
        uut("uut"),
        memInAdp("inadp"),
        memOutAdp("outadp"),
        rowIndAdp("riadp"),
        colLenAdp("cladp")
    {
        uut.clk(clk);
        uut.reset(reset);
        uut.io_start(io_start);
        uut.io_memFill(io_memFill);
        uut.io_memDump(io_memDump);
        uut.io_colCount(io_colCount);
        uut.io_state(io_state);

        uut.io_portA_writeEn(io_portA_writeEn);
        uut.io_portB_dataIn(io_portB_dataIn);
        uut.io_portB_writeEn(io_portB_writeEn);
        uut.io_portB_dataOut(io_portB_dataOut);
        uut.io_portA_addr(io_portA_addr);
        uut.io_portB_addr(io_portB_addr);
        uut.io_portA_dataIn(io_portA_dataIn);
        uut.io_portA_dataOut(io_portA_dataOut);


        // wrap vector memory in FIFO
        memInAdp.clk(clk);
        memInAdp.fifoInput.bind(memIn);
        memInAdp.bindSignalInterface(uut.io_vectorMemDataIn_valid, uut.io_vectorMemDataIn_ready,
                                     uut.io_vectorMemDataIn_bits);

        // wrap vector memory out FIFO
        memOutAdp.clk(clk);
        memOutAdp.fifoOutput.bind(memOut);
        memOutAdp.bindSignalInterface(uut.io_vectorMemDataOut_valid, uut.io_vectorMemDataOut_ready,
                                     uut.io_vectorMemDataOut_bits);

        // wrap col lengths FIFO
        colLenAdp.clk(clk);
        colLenAdp.fifoInput.bind(colLen);
        colLenAdp.bindSignalInterface(uut.io_colLengths_valid, uut.io_colLengths_ready,
                                      uut.io_colLengths_bits);

        // wrap row indices FIFO
        rowIndAdp.clk(clk);
        rowIndAdp.fifoInput.bind(rowInd);
        rowIndAdp.bindSignalInterface(uut.io_rowIndices_valid, uut.io_rowIndices_ready,
                                      uut.io_rowIndices_bits);

        SC_CTHREAD(memoryPortA, clk.pos());
        SC_CTHREAD(memoryPortB, clk.pos());

        SC_THREAD(runFrontendTests);
        sensitive << clk.pos();

        init_trace();
    }

    unsigned int valueForWord(unsigned int i)
    {
        return (i == 0 ? 1 : 0);
    }

    void fillMem(unsigned int * data, unsigned int wordCount)
    {
        for(unsigned int i = 0; i < wordCount; i++)
        {
            memIn.write(data[i]);
        }
    }

    void dumpMem(unsigned int * data, unsigned int wordCount)
    {
        for(unsigned int i = 0; i < wordCount; i++)
        {
            data[i] = memOut.read();
        }
    }

    void printState()
    {
        cout << "currentState @" << NOW << ": ";

        switch(io_state)
        {
        case 0:
            cout << "sIdle";
            break;
        case 1:
            cout << "sMemFill";
            break;
        case 2:
            cout << "sMemDumpWait";
            break;
        case 3:
            cout << "sMemDumpLoad";
            break;
        case 4:
            cout << "sReadColLen";
            break;
        case 5:
            cout << "sProcessColumn";
            break;
        default:
            cout << "unknown! -- " << io_state;
        }

        cout << endl;
    }

    void pushMatrixData(QString matrixName)
    {
        QString fileName = "/home/maltanar/spm-data/graph/" + matrixName;

        // TODO load matrix once & reuse for multiple SpMV iterations
        CSCGraph matrix(fileName);


        cout << "Loaded matrix " << matrixName.toStdString() << endl;
        cout << "Vertex count = " << matrix.rowCount() << endl;
        cout << "Edge count = " << matrix.nzCount() << endl;

        sc_assert(io_state == 0);   // make sure we are in idle

        io_colCount = matrix.colCount();
        io_memDump = false;
        io_memFill = false;
        io_start = true;
        wait(2);
        io_start = false;

        sc_assert(io_state == 4); // should be in sReadColLen

        QList<CSCPtr> colLenData = matrix.getColLengths();
        QList<CSCPtr> rowIndData = matrix.getRowIndices();

        // "address offset" for result vector
        // TODO this should be supported in hardware
        unsigned int yOffset = 64;

        while (!colLenData.empty() || !rowIndData.empty())
        {
            if(!colLenData.empty())
            {
                unsigned int len = colLenData.takeFirst();
                cout << "collen: " << len << endl;
                colLen.write(len);
            }
            if(!rowIndData.empty())
            {
                unsigned int y = yOffset + rowIndData.takeFirst();
                cout << "yind: " << y << endl;
                rowInd.write(y);
            }
        }

        cout << "Finished pushing matrix data, waiting for idle @" << NOW << endl;

        // wait until we go back to idle
        while(io_state != 0)
            wait(1);

        cout << "Column length transfers = " << colLenAdp.getTransferCount() << endl;
        cout << "Row index transfers = " << rowIndAdp.getTransferCount() << endl;
    }

    void printMemBlockNonzeroes(unsigned int * data, unsigned int count)
    {
        cout << "Nonzero locations:" << endl;
        for(unsigned int i = 0; i < count; i++)
        {
            if(data[i] != 0)
                cout << "[" << i << "] = " << data[i] << endl;
        }
    }

    void runFrontendTests()
    {
        reset = true;
        wait(10);
        reset = false;

        // launch memory fill mode
        printState(); // should be sMemFill
        cout << "starting memfill test @" << sc_time_stamp() << endl;
        io_memFill = true;
        io_start = true;
        wait(1);
        io_memFill = false;
        io_start = false;

        unsigned int initData[MEM_WORD_COUNT];

        for(unsigned int i = 0; i < MEM_WORD_COUNT; i++)
            initData[i] = valueForWord(i);

        fillMem(initData, MEM_WORD_COUNT);

        // wait until we're back to idle
        while(io_state != 0)
            wait(1);

        cout << "memfill completed" << endl;
        cout << "memInAdp transfer count = "  << memInAdp.getTransferCount() << endl;

        if(!checkMemoryContents(initData, MEM_WORD_COUNT))
        {
            cout << "memory contents incorrect after memfill!" << endl;
            return;
        }
        else
            cout << "memory contents are correct" << endl;

        wait(5);
        cout << "starting memdump test at " << sc_time_stamp() << endl;
        io_memDump = true;
        io_start = true;
        wait(1);
        io_start = false;
        io_memDump = false;
        unsigned int buf[MEM_WORD_COUNT];
        dumpMem(buf, MEM_WORD_COUNT);
        // TODO check dumped mem
        int res = memcmp(initData, buf, MEM_WORD_COUNT*sizeof(unsigned int));
        cout << "memdump completed, memcmp result = " << res << endl;
        cout << "memOutAdp transfer count = "  << memOutAdp.getTransferCount() << endl;

        printMemBlockNonzeroes(buf, MEM_WORD_COUNT);

        pushMatrixData("Pajek-GD01_b");

        sc_assert(io_state == 0);

        io_memDump = true;
        io_start = true;
        wait(1);
        io_start = false;
        io_memDump = false;
        dumpMem(buf, MEM_WORD_COUNT);
        printMemBlockNonzeroes(buf, MEM_WORD_COUNT);

        return;
    }

    bool checkMemoryContents(unsigned int * cmp, unsigned int wordCount)
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

    void init_trace()
    {
        return;

        Tf = sc_create_vcd_trace_file("traces");
        ((vcd_trace_file*) Tf)->set_time_unit(0.5, SC_NS);

        // add interesting signals and display names

        sc_trace(Tf, clk, "clk");
        sc_trace(Tf, uut.io_vectorMemDataIn_bits, "in_data");
        sc_trace(Tf, uut.io_vectorMemDataIn_ready, "in_ready");
        sc_trace(Tf, uut.io_vectorMemDataIn_valid, "in_valid");

        sc_trace(Tf, io_portA_addr, "portA_addr");
        sc_trace(Tf, io_portA_dataIn, "portA_dataIn");
        sc_trace(Tf, io_portA_writeEn, "portA_writeEn");
        sc_trace(Tf, io_portA_dataOut, "portA_dataOut");

        /*
        sc_trace(Tf, io_vectorMemDataOut_ready, "out_ready");
        sc_trace(Tf, io_vectorMemDataOut_valid, "out_valid");
        sc_trace(Tf, io_vectorMemDataOut_bits, "out_data");
        */
    }

    void finish_trace()
    {
        return;

        sc_close_vcd_trace_file(Tf);
    }

    void memoryPortA()
    {
        io_portA_dataOut = 0;

        while(1)
        {
            wait(1);

            unsigned int addr = io_portA_addr;
            bool writeEn = io_portA_writeEn;
            unsigned int dataIn = io_portA_dataIn;
            //cout << "portA addr " << addr << " val " << m_memory[addr] <<  " at " << NOW << endl;

            io_portA_dataOut = m_memory[addr];

            if(writeEn)
            {
                m_memory[addr] = dataIn;
                //cout << "portA write addr = " << addr << " data = " << dataIn << " at " << NOW << endl;
            }
        }

    }

    void memoryPortB()
    {
        io_portB_dataOut = false;

        while(1)
        {
            wait(1);

            unsigned int addr = io_portB_addr;
            bool writeEn = io_portB_writeEn;
            bool dataIn = io_portB_dataIn;

            io_portB_dataOut = (bool)((m_memory[addr >> 5] >> (addr & 0x1F)) & 0x1 == 0x1);

            if(writeEn)
            {

                unsigned int ldWord = m_memory[addr >> 5];

                cout << "portB write addr = " << addr << " data = " << dataIn << " at " << NOW << endl;
                cout << "ldWord addr = " << (addr >> 5) << " value = " << ldWord << endl;
                cout << "ldWord desired bit index = " << (addr & 0x1F) << endl;

                if(dataIn)
                    ldWord = ldWord | (1 << (addr & 0x1F));
                else
                    ldWord = ldWord & ~(1 << (addr & 0x1F));
                cout << "ldWord new value = " << ldWord << endl;

                m_memory[addr >> 5] = ldWord;
            }
        }

    }

};

int sc_main(int argc, char *argv[])
{
    sc_clock clk("clk", CLOCK_CYCLE);
    FrontendTester t("tester");
    t.clk(clk);

    sc_start();
    t.finish_trace();

    return 0;
}
