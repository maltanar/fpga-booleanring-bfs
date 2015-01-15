#include <systemc.h>
#include <iostream>
#include <string>
#include "InputFIFOAdapter.h"
#include "OutputFIFOAdapter.h"
#include "VFrontendController.h"

using namespace std;

// clock period for the test clock
#define   CLOCK_CYCLE   sc_time(10, SC_NS)

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
    sig_reset = true;
    wait(10*CLOCK_CYCLE);
    sig_reset = false;

  }
  
  void run_tests()
  {
    // initialize input drivers
    init_drivers();
    reset_system();
    cout << "Reset completed at " << sc_time_stamp() << ", starting tests..." << endl;
    wait(0.5*CLOCK_CYCLE);
    testEmptyColStart();
  }
  
  void testEmptyColStart()
  {
    sc_assert(sig_io_state == 0);
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
  
  void waitClockCycles(int N)
  {
    wait(N*CLOCK_CYCLE);
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


  
};

int sc_main(int argc, char *argv[])
{
  TestVFrontendController tb("tb");
  
  sc_start();
  
  return 0;
}

