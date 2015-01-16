#include <systemc.h>
#include <iostream>
#include <string>
#include "InputFIFOAdapter.h"
#include "OutputFIFOAdapter.h"
#include "VFrontendController.h"

using namespace std;

// clock period for the test clock
#define   CLOCK_CYCLE   sc_time(10, SC_NS)

#define   MEM_DEPTH     1024

class TestVFrontendController : public sc_module
{
  SC_HAS_PROCESS(TestVFrontendController);

public:  
  TestVFrontendController(sc_module_name name) : 
    sc_module(name), uut("uut"), clk("clk", CLOCK_CYCLE)
    , adp_io_dvValues("adp_io_dvValues"), adp_io_rowIndices("adp_io_rowIndices"), adp_io_colLengths("adp_io_colLengths")
    
  {
    // TODO handle FIFOs
    
    // connect input drivers
    uut.clk(clk);
    uut.reset(sig_reset);
    uut.io_start(sig_io_start);
    uut.io_resMemPort_dataOut(sig_io_resMemPort_dataOut);
    uut.io_colCount(sig_io_colCount);

    // connect output monitors
    uut.io_resMemPort_writeEn(sig_io_resMemPort_writeEn);
    uut.io_processedColCount(sig_io_processedColCount);
    uut.io_state(sig_io_state);
    uut.io_resMemPort_addr(sig_io_resMemPort_addr);
    uut.io_resMemPort_dataIn(sig_io_resMemPort_dataIn);
    uut.io_processedNZCount(sig_io_processedNZCount);


    // FIFO setup
    adp_io_dvValues.clk(clk);
    adp_io_dvValues.fifoInput(fifo_io_dvValues);
    adp_io_dvValues.bindSignalInterface(uut.io_dvValues_valid, uut.io_dvValues_ready, uut.io_dvValues_bits);
    adp_io_rowIndices.clk(clk);
    adp_io_rowIndices.fifoInput(fifo_io_rowIndices);
    adp_io_rowIndices.bindSignalInterface(uut.io_rowIndices_valid, uut.io_rowIndices_ready, uut.io_rowIndices_bits);
    adp_io_colLengths.clk(clk);
    adp_io_colLengths.fifoInput(fifo_io_colLengths);
    adp_io_colLengths.bindSignalInterface(uut.io_colLengths_valid, uut.io_colLengths_ready, uut.io_colLengths_bits);


    
    // declare run_tests as SystemC thread
    SC_THREAD(run_tests);

    SC_THREAD(handleMemWrites);
  }
  
  // initialize the driving signals for the uut inputs
  void init_drivers()
  {
    sig_reset = 0;
    sig_io_start = 0;
    sig_io_resMemPort_dataOut = 0;
    sig_io_colCount = 0;

  }
  
  // reset system if needed
  void reset_system()
  {
    resetMem();
    sig_reset = true;
    waitClockCycles(10);
    sig_reset = false;

  }
  
  void run_tests()
  {
    // initialize input drivers
    init_drivers();
    reset_system();
    cout << "Reset completed at " << sc_time_stamp() << ", starting tests..." << endl;


    testEmptyColStart();
    testSingleColumn();
    testZeroLenColumn();
    sc_stop();
  }
  
  void testEmptyColStart()
  {
    sc_assert(sig_io_state == 0);
    cout << "********************************************" << endl;
    cout << "Running test: zero columns" << endl;
    // set column count to zero and give start signal
    sig_io_colCount = 0;
    sig_io_start = true;
    waitClockCycles(1);
    sc_assert(sig_io_state == 1);   // even with colCount=0 should move to sReadCol
    waitClockCycles(1);
    sc_assert(sig_io_state == 0);   // should go back to sIdle
    waitClockCycles(1);
    sc_assert(sig_io_state == 1);   // start is still high, so should start again
    sig_io_start = false;           // do not start after this
    waitClockCycles(1);
    sc_assert(sig_io_state == 0);   // should go back to sIdle
    cout << "Test successful" << endl;
  }

  void testSingleColumn()
  {
    sc_assert(sig_io_state == 0);
    sc_assert(sig_io_start == false);
    adp_io_colLengths.resetCounters();
    adp_io_dvValues.resetCounters();
    adp_io_rowIndices.resetCounters();
    resetMem();
    // remove remaining elements from FIFOs
    emptyFIFOContents();
    cout << "********************************************" << endl;
    cout << "Running test: single column with 5 elements" << endl;
    cout << "Initializing FIFOs..." << endl;
    sig_io_colCount = 1;          // 1 column

    fifo_io_colLengths.write(5);  // 5 elements in the column
    fifo_io_colLengths.write(6);  // should not be used
    // two dv values, second should not be used
    fifo_io_dvValues.write(1);
    fifo_io_dvValues.write(1);
    // write 10 col indices -- only the first 5 should be used
    for(int i = 0; i< 10; i++)
      fifo_io_rowIndices.write(11 * i);
    waitClockCycles(10);
    // nothing should happen since start was not given
    sc_assert(sig_io_state == 0);
    sig_io_start = true;
    waitClockCycles(1);
    sig_io_start = false;
    // should switch to sReadCol
    sc_assert(sig_io_state == 1);
    waitClockCycles(1);

    // should switch to sProcessColumn and stay there
    for(int i = 0; i < 5; i++)
    {
      sc_assert(sig_io_state == 2);
      waitClockCycles(1);
    }

    // will stay in sProcessColumn for one more cycle, but no new rowinds
    // should be processed
    sc_assert(sig_io_state == 2);
    waitClockCycles(1);

    // column finished, back to sReadColLen
    sc_assert(sig_io_state == 1);
    waitClockCycles(1);
    // no more columns, back to sIdle
    sc_assert(sig_io_state == 0);

    // check FIFO transfer counts
    getFIFOTransferCounts();
    sc_assert(adp_io_colLengths.getTransferCount() == 1);
    sc_assert(adp_io_dvValues.getTransferCount() == 1);
    sc_assert(adp_io_rowIndices.getTransferCount() == 5);

    // check memory
    sc_assert(m_writeCount == 5);

    cout << "Test successful" << endl;
  }

  void testZeroLenColumn()
  {
    sc_assert(sig_io_state == 0);
    sc_assert(sig_io_start == false);
    adp_io_colLengths.resetCounters();
    adp_io_dvValues.resetCounters();
    adp_io_rowIndices.resetCounters();
    resetMem();
    // remove remaining elements from FIFOs
    emptyFIFOContents();
    cout << "********************************************" << endl;
    cout << "Running test: 3 columns of lengths 3-0-3-4, last 3 with 0 dv" << endl;

    sig_io_colCount = 4;
    fifo_io_colLengths.write(3);
    fifo_io_dvValues.write(1);

    fifo_io_colLengths.write(0);
    fifo_io_dvValues.write(0);

    fifo_io_colLengths.write(3);
    fifo_io_dvValues.write(0);

    fifo_io_colLengths.write(4);
    fifo_io_dvValues.write(1);


    for(int i = 1; i <= 14; i++)
      fifo_io_rowIndices.write(11*i);

    sig_io_start = true;
    waitClockCycles(1);
    sig_io_start = false;
    sc_assert(sig_io_state == 1);
    // wait until everything is done
    waitClockCycles(100);
    getFIFOTransferCounts();
    sc_assert(sig_io_state == 0);                             // back to idle
    sc_assert(m_writeCount == 7);                             // should be a total of 7 writes from the dv 1 elements
    sc_assert(adp_io_colLengths.getTransferCount() == 4);     // 4 column lengths
    sc_assert(adp_io_dvValues.getTransferCount() == 4);       // 4 dv elements
    sc_assert(adp_io_rowIndices.getTransferCount() == 10);    // 10 rowinds popped (3 of which did not result in writes due to zero dv)
    cout << "Test successful" << endl;

  }

  void getFIFOTransferCounts()
  {
    cout << "Col lengths FIFO transfers: " << adp_io_colLengths.getTransferCount() << endl;
    cout << "DV FIFO transfers: " << adp_io_dvValues.getTransferCount() << endl;
    cout << "Rowinds FIFO transfers: " << adp_io_rowIndices.getTransferCount() << endl;
    cout << "Available data counts: " << fifo_io_colLengths.num_available() <<" " << fifo_io_dvValues.num_available() << " " << fifo_io_rowIndices.num_available() << endl;
    cout << "Total memory writes: " << m_writeCount << endl;
  }
  
  void waitClockCycles(int N)
  {
    for(int i = 0; i < N; i++)
      wait(clk.posedge_event());
    // for some strange reason the signals don't recover right after the posedge,
    // -- so wait just a little longer after the clock edge
    wait(0.1*CLOCK_CYCLE);
  }
  
  void print_state()
  {
    cout << "Current state: " << sig_io_state << endl;
  }
  
  void print_stats()
  {
    cout << "Processed columnns: " << sig_io_processedColCount << " NZ: " << sig_io_processedNZCount << endl;
  }
  
  sc_clock clk;
  
  // instance for the module being tested
  VFrontendController uut;
  
  // signals for manipulating the module
  sc_signal<bool> sig_reset;
  sc_signal<bool> sig_io_start;
  sc_signal<bool> sig_io_resMemPort_dataOut;
  sc_signal<uint32_t> sig_io_colCount;

  sc_signal<bool> sig_io_resMemPort_writeEn;
  sc_signal<uint32_t> sig_io_processedColCount;
  sc_signal<uint32_t> sig_io_state;
  sc_signal<uint32_t> sig_io_resMemPort_addr;
  sc_signal<bool> sig_io_resMemPort_dataIn;
  sc_signal<uint32_t> sig_io_processedNZCount;


  // FIFO adapters for bridging SystemC FIFOs with signal-level decoupled interfaces
  InputFIFOAdapter<bool> adp_io_dvValues;
  InputFIFOAdapter<uint32_t> adp_io_rowIndices;
  InputFIFOAdapter<uint32_t> adp_io_colLengths;



  // SystemC FIFO declarations for talking to decoupled interfaces
  sc_fifo<bool> fifo_io_dvValues;
  sc_fifo<uint32_t> fifo_io_rowIndices;
  sc_fifo<uint32_t> fifo_io_colLengths;

  void emptyFIFOContents()
  {
    // empty the contents of all input FIFOs and adapters
    adp_io_colLengths.resetContent();
    adp_io_dvValues.resetContent();
    adp_io_rowIndices.resetContent();
  }

  // memory
  bool m_memory[MEM_DEPTH];
  unsigned long int m_writeCount;

  void resetMem()
  {
    m_writeCount = 0;
    for(int i=0; i < MEM_DEPTH; i++)
      m_memory[i] = false;
  }

  void printMem()
  {
    bool nonEmpty=false;
    for(int i=0; i < MEM_DEPTH; i++)
      if(m_memory[i])
      {
        nonEmpty = true;
        cout << "maddr " << i << endl;
      }
    if(!nonEmpty)
      cout << "memory is all zeroes" << endl;
  }

  void handleMemWrites()
  {
    while(1)
    {
      waitClockCycles(1);
      if(sig_io_resMemPort_writeEn)
      {
        sc_assert(sig_io_resMemPort_addr < MEM_DEPTH);
        m_memory[sig_io_resMemPort_addr] = (bool) sig_io_resMemPort_dataIn;
        m_writeCount++;
        cout << "memwrite addr " << sig_io_resMemPort_addr << " =" << sig_io_resMemPort_dataIn << endl;
      }
    }
  }


  
};

int sc_main(int argc, char *argv[])
{
  TestVFrontendController tb("tb");
  
  sc_start();
  
  return 0;
}

