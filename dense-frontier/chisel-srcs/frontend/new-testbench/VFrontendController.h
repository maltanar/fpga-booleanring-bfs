// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VFrontendController_H_
#define _VFrontendController_H_

#include "systemc.h"
#include "verilated_sc.h"
#include "verilated.h"
class VFrontendController__Syms;

//----------

SC_MODULE(VFrontendController) {
  public:
    // CELLS
    // Public to allow access to /*verilator_public*/ items;
    // otherwise the application code can consider these internals.
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    sc_in<bool>	clk;
    sc_in<bool>	reset;
    sc_in<bool>	io_start;
    sc_out<bool>	io_colLengths_ready;
    sc_in<bool>	io_colLengths_valid;
    sc_out<bool>	io_rowIndices_ready;
    sc_in<bool>	io_rowIndices_valid;
    sc_out<bool>	io_dvValues_ready;
    sc_in<bool>	io_dvValues_valid;
    sc_in<bool>	io_dvValues_bits;
    sc_out<bool>	io_resMemPort_dataIn;
    sc_out<bool>	io_resMemPort_writeEn;
    sc_in<bool>	io_resMemPort_dataOut;
    sc_out<uint32_t>	io_resMemPort_addr;
    sc_in<uint32_t>	io_colCount;
    sc_out<uint32_t>	io_state;
    sc_out<uint32_t>	io_processedColCount;
    sc_out<uint32_t>	io_processedNZCount;
    sc_in<uint32_t>	io_colLengths_bits;
    sc_in<uint32_t>	io_rowIndices_bits;
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    VL_SIG8(v__DOT__T1,0,0);
    VL_SIG8(v__DOT__T5,0,0);
    VL_SIG8(v__DOT__regState,1,0);
    VL_SIG8(v__DOT__T22,0,0);
    VL_SIG8(v__DOT__T23,0,0);
    //char	__VpadToAlign89[3];
    VL_SIG(v__DOT__regCurrentColLen,31,0);
    VL_SIG(v__DOT__regColCount,31,0);
    VL_SIG(v__DOT__regProcessedNZCount,31,0);
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    VL_SIG8(__Vcellinp__v__clk,0,0);
    VL_SIG8(__Vcellinp__v__io_dvValues_bits,0,0);
    VL_SIG8(__Vcellinp__v__io_dvValues_valid,0,0);
    VL_SIG8(__Vcellinp__v__io_rowIndices_valid,0,0);
    VL_SIG8(__Vcellinp__v__io_colLengths_valid,0,0);
    VL_SIG8(__Vcellinp__v__io_start,0,0);
    VL_SIG8(__Vcellinp__v__reset,0,0);
    VL_SIG8(__Vclklast__TOP____Vcellinp__v__clk,0,0);
    VL_SIG(__Vcellinp__v__io_rowIndices_bits,31,0);
    VL_SIG(__Vcellinp__v__io_colLengths_bits,31,0);
    VL_SIG(__Vcellinp__v__io_colCount,31,0);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    //char	__VpadToAlign132[4];
    VFrontendController__Syms*	__VlSymsp;		// Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    
    // CONSTRUCTORS
  private:
    VFrontendController& operator= (const VFrontendController&);	///< Copying not allowed
    VFrontendController(const VFrontendController&);	///< Copying not allowed
  public:
    SC_CTOR(VFrontendController);
    virtual ~VFrontendController();
    
    // USER METHODS
    
    // API METHODS
  private:
    void eval();
  public:
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(VFrontendController__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(VFrontendController__Syms* symsp, bool first);
  private:
    static IData	_change_request(VFrontendController__Syms* __restrict vlSymsp);
  public:
    static void	_combo__TOP__2(VFrontendController__Syms* __restrict vlSymsp);
    static void	_combo__TOP__5(VFrontendController__Syms* __restrict vlSymsp);
    static void	_combo__TOP__7(VFrontendController__Syms* __restrict vlSymsp);
    static void	_eval(VFrontendController__Syms* __restrict vlSymsp);
    static void	_eval_initial(VFrontendController__Syms* __restrict vlSymsp);
    static void	_eval_settle(VFrontendController__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__4(VFrontendController__Syms* __restrict vlSymsp);
    static void	_settle__TOP__1(VFrontendController__Syms* __restrict vlSymsp);
    static void	_settle__TOP__3(VFrontendController__Syms* __restrict vlSymsp);
    static void	_settle__TOP__6(VFrontendController__Syms* __restrict vlSymsp);
    static void	_settle__TOP__8(VFrontendController__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif  /*guard*/
