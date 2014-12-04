// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VDataPuller_H_
#define _VDataPuller_H_

#include "systemc.h"
#include "verilated_sc.h"
#include "verilated.h"
class VDataPuller__Syms;

//----------

SC_MODULE(VDataPuller) {
  public:
    // CELLS
    // Public to allow access to /*verilator_public*/ items;
    // otherwise the application code can consider these internals.
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    sc_in<bool>	clk;
    sc_in<bool>	reset;
    sc_in<bool>	M_AXI_AWREADY;
    sc_out<bool>	M_AXI_AWVALID;
    sc_out<uint32_t>	M_AXI_AWSIZE;
    sc_out<uint32_t>	M_AXI_AWLEN;
    sc_out<uint32_t>	M_AXI_AWPROT;
    sc_out<uint32_t>	M_AXI_AWBURST;
    sc_out<bool>	M_AXI_AWLOCK;
    sc_out<uint32_t>	M_AXI_AWCACHE;
    sc_out<uint32_t>	M_AXI_AWQOS;
    sc_out<uint32_t>	M_AXI_AWID;
    sc_in<bool>	M_AXI_WREADY;
    sc_out<bool>	M_AXI_WVALID;
    sc_out<uint32_t>	M_AXI_WSTRB;
    sc_out<bool>	M_AXI_WLAST;
    sc_out<bool>	M_AXI_BREADY;
    sc_in<bool>	M_AXI_BVALID;
    sc_in<uint32_t>	M_AXI_BID;
    sc_in<uint32_t>	M_AXI_BRESP;
    sc_in<bool>	M_AXI_ARREADY;
    sc_out<bool>	M_AXI_ARVALID;
    sc_out<uint32_t>	M_AXI_ARSIZE;
    sc_out<uint32_t>	M_AXI_ARLEN;
    sc_out<uint32_t>	M_AXI_ARPROT;
    sc_out<uint32_t>	M_AXI_ARBURST;
    sc_out<bool>	M_AXI_ARLOCK;
    sc_out<uint32_t>	M_AXI_ARCACHE;
    sc_out<uint32_t>	M_AXI_ARQOS;
    sc_out<uint32_t>	M_AXI_ARID;
    sc_out<bool>	M_AXI_RREADY;
    sc_in<bool>	M_AXI_RVALID;
    sc_in<uint32_t>	M_AXI_RID;
    sc_in<bool>	M_AXI_RLAST;
    sc_in<uint32_t>	M_AXI_RRESP;
    sc_in<bool>	io_matrixData_ready;
    sc_out<bool>	io_matrixData_valid;
    sc_in<bool>	io_vectorData_ready;
    sc_out<bool>	io_vectorData_valid;
    sc_in<bool>	io_start;
    sc_in<bool>	io_stop;
    sc_out<uint32_t>	M_AXI_AWADDR;
    sc_out<uint32_t>	M_AXI_ARADDR;
    sc_in<uint32_t>	io_matrixPtr;
    sc_in<uint32_t>	io_vectorPtr;
    sc_out<vluint64_t>	M_AXI_WDATA;
    sc_in<vluint64_t>	M_AXI_RDATA;
    sc_out<vluint64_t>	io_matrixData_bits;
    sc_out<vluint64_t>	io_vectorData_bits;
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    VL_SIG8(v__DOT__canAcceptData,0,0);
    VL_SIG8(v__DOT__state,1,0);
    VL_SIG8(v__DOT__T10,0,0);
    VL_SIG8(v__DOT__T13,0,0);
    VL_SIG8(v__DOT__T17,0,0);
    VL_SIG8(v__DOT__T21,0,0);
    //char	__VpadToAlign206[2];
    VL_SIG(v__DOT__regDenseVecPtr,31,0);
    VL_SIG(v__DOT__regMatrixPtr,31,0);
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    VL_SIG8(__Vcellinp__v__clk,0,0);
    VL_SIG8(__Vcellinp__v__io_stop,0,0);
    VL_SIG8(__Vcellinp__v__io_start,0,0);
    VL_SIG8(__Vcellinp__v__io_vectorData_ready,0,0);
    VL_SIG8(__Vcellinp__v__io_matrixData_ready,0,0);
    VL_SIG8(__Vcellinp__v__M_AXI_RID,1,0);
    VL_SIG8(__Vcellinp__v__M_AXI_ARREADY,0,0);
    VL_SIG8(__Vcellinp__v__reset,0,0);
    VL_SIG8(__Vclklast__TOP____Vcellinp__v__clk,0,0);
    //char	__VpadToAlign229[3];
    VL_SIG(__Vcellinp__v__io_vectorPtr,31,0);
    VL_SIG(__Vcellinp__v__io_matrixPtr,31,0);
    VL_SIG64(__Vcellinp__v__M_AXI_RDATA,63,0);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    //char	__VpadToAlign252[4];
    VDataPuller__Syms*	__VlSymsp;		// Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    
    // CONSTRUCTORS
  private:
    VDataPuller& operator= (const VDataPuller&);	///< Copying not allowed
    VDataPuller(const VDataPuller&);	///< Copying not allowed
  public:
    SC_CTOR(VDataPuller);
    virtual ~VDataPuller();
    
    // USER METHODS
    
    // API METHODS
  private:
    void eval();
  public:
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(VDataPuller__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(VDataPuller__Syms* symsp, bool first);
  private:
    static IData	_change_request(VDataPuller__Syms* __restrict vlSymsp);
  public:
    static void	_combo__TOP__2(VDataPuller__Syms* __restrict vlSymsp);
    static void	_combo__TOP__5(VDataPuller__Syms* __restrict vlSymsp);
    static void	_combo__TOP__7(VDataPuller__Syms* __restrict vlSymsp);
    static void	_eval(VDataPuller__Syms* __restrict vlSymsp);
    static void	_eval_initial(VDataPuller__Syms* __restrict vlSymsp);
    static void	_eval_settle(VDataPuller__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__4(VDataPuller__Syms* __restrict vlSymsp);
    static void	_sequent__TOP__8(VDataPuller__Syms* __restrict vlSymsp);
    static void	_settle__TOP__1(VDataPuller__Syms* __restrict vlSymsp);
    static void	_settle__TOP__3(VDataPuller__Syms* __restrict vlSymsp);
    static void	_settle__TOP__6(VDataPuller__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif  /*guard*/
