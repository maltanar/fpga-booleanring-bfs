#include <iostream>
#include <systemc.h>

#include "VFrontendController.h"

#define CLOCK_CYCLE sc_time(1, SC_NS)
#define NOW sc_time_stamp()
#define MEM_WORD_COUNT      1024


class FrontendTester : public sc_module
{
    SC_HAS_PROCESS(FrontendTester);

public:
    FrontendTester(sc_module_name nm) :
        sc_module(nm),
        uut("uut")
    {
        uut.clk(clk);
        uut.reset(reset);
        uut.io_start(io_start);
        uut.io_memFill(io_memFill);
        uut.io_memDump(io_memDump);
        uut.io_colLengths_ready(io_colLengths_ready);
        uut.io_colLengths_valid(io_colLengths_valid);
        uut.io_rowIndices_ready(io_rowIndices_ready);
        uut.io_rowIndices_valid(io_rowIndices_valid);
        uut.io_vectorMemDataIn_ready(io_vectorMemDataIn_ready);
        uut.io_vectorMemDataIn_valid(io_vectorMemDataIn_valid);
        uut.io_vectorMemDataOut_ready(io_vectorMemDataOut_ready);
        uut.io_vectorMemDataOut_valid(io_vectorMemDataOut_valid);
        uut.io_portA_writeEn(io_portA_writeEn);
        uut.io_portB_dataIn(io_portB_dataIn);
        uut.io_portB_writeEn(io_portB_writeEn);
        uut.io_portB_dataOut(io_portB_dataOut);
        uut.io_portA_addr(io_portA_addr);
        uut.io_portB_addr(io_portB_addr);
        uut.io_colCount(io_colCount);
        uut.io_colLengths_bits(io_colLengths_bits);
        uut.io_rowIndices_bits(io_rowIndices_bits);
        uut.io_vectorMemDataIn_bits(io_vectorMemDataIn_bits);
        uut.io_vectorMemDataOut_bits(io_vectorMemDataOut_bits);
        uut.io_portA_dataIn(io_portA_dataIn);
        uut.io_portA_dataOut(io_portA_dataOut);
        uut.io_state(io_state);

        SC_CTHREAD(memoryPortA, clk.pos());
        SC_CTHREAD(memoryPortB, clk.pos());

        SC_THREAD(runFrontendTests);
        SC_CTHREAD(generateMemFill, clk.pos());
        SC_CTHREAD(testMemDump, clk.pos());

        init_trace();
    }

    unsigned int valueForWord(unsigned int i)
    {
        return (i == 0 ? 1 : 0);
    }

    void generateMemFill()
    {
        unsigned int memWordCount = MEM_WORD_COUNT, current = 0;

        while(current < memWordCount)
        {
            io_vectorMemDataIn_bits = valueForWord(current);
            io_vectorMemDataIn_valid = true;

            do {
                wait(1);
            } while(io_vectorMemDataIn_ready == false);


            // test the latency insensitivity
            io_vectorMemDataIn_bits = 0xdeadbeef;
            io_vectorMemDataIn_valid = false;
            wait(2);

            current++;
        }

        io_vectorMemDataIn_valid = false;

        cout << "generateMemFill completed at " << sc_time_stamp() << endl;
        fillFinished.notify(SC_ZERO_TIME);
    }

    void testMemDump()
    {
        unsigned int memWordCount = MEM_WORD_COUNT, current = 0;

        while(current < memWordCount)
        {
            io_vectorMemDataOut_ready = true;
            wait(1);

            if(io_vectorMemDataOut_valid )
            {
                unsigned int expected  = valueForWord(current);

                if (io_vectorMemDataOut_bits != expected)
                {
                    cout << "data mismatch for memDump at element " << current << endl;
                    cout << "expected " << expected << " found " << io_vectorMemDataOut_bits << " @" << NOW << endl;
                }
                else
                {
                    //cout << "data for element " << current << " OK @" << NOW << endl;
                }

                current++;
            }

            // test latency insensitivity
            io_vectorMemDataOut_ready = false;
            wait(2);
        }

        wait(1);
        io_vectorMemDataOut_ready = false;

        cout << "testMemDump completed at " << sc_time_stamp() << endl;
        cout << "portA addr = " << io_portA_addr << endl;
        dumpFinished.notify(SC_ZERO_TIME);
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

    void runFrontendTests()
    {
        reset = true;
        wait(10*CLOCK_CYCLE);
        reset = false;
        // launch memory fill mode
        printState();
        cout << "starting memfill test @" << sc_time_stamp() << endl;
        io_memFill = true;
        io_start = true;
        wait(2*CLOCK_CYCLE);
        io_memFill = false;
        io_start = false;
        printState();
        wait(fillFinished);
        printState();
        if(!checkMemoryContents())
        {
            cout << "memory contents incorrect after memfill!" << endl;
            return;
        }
        else
            cout << "memory contents are correct" << endl;

        wait(5*CLOCK_CYCLE);
        cout << "starting memdump test at " << sc_time_stamp() << endl;
        io_memDump = true;
        io_start = true;
        wait(2*CLOCK_CYCLE);
        printState();
        io_start = false;
        io_memDump = false;
        wait(dumpFinished);
        printState();

        io_colCount = 1;
    }

    bool checkMemoryContents()
    {
        bool result = true;

        for(int i = 0; i < MEM_WORD_COUNT; i++)
            if(m_memory[i] != valueForWord(i))
            {
                cout << "incorrect mem contents at word addr " << i << endl;
                result=false;
                break;
            }

        return result;
    }

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

    VFrontendController uut;

    unsigned int m_memory[MEM_WORD_COUNT];
    sc_event startFill, startDump;
    sc_event fillFinished, dumpFinished;

    sc_trace_file* Tf;

    void init_trace()
    {
        return;

        Tf = sc_create_vcd_trace_file("traces");
        ((vcd_trace_file*) Tf)->set_time_unit(1, SC_NS);

        // add interesting signals and display names

        sc_trace(Tf, clk, "clk");
        sc_trace(Tf, io_portA_addr, "portA_addr");
        sc_trace(Tf, io_portA_dataOut, "portA_dataOut");
        sc_trace(Tf, io_vectorMemDataOut_ready, "out_ready");
        sc_trace(Tf, io_vectorMemDataOut_valid, "out_valid");
        sc_trace(Tf, io_vectorMemDataOut_bits, "out_data");
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
                if(dataIn)
                    ldWord = ldWord | (1 << (addr & 0x1F));
                else
                    ldWord = ldWord & ~(1 << (addr & 0x1F));

                m_memory[addr] = ldWord;
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

    return 0;
}
