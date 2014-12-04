// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VDataPuller.h for the primary calling header

#include "VDataPuller.h"       // For This
#include "VDataPuller__Syms.h"

//--------------------
// STATIC VARIABLES


//--------------------

VL_SC_CTOR_IMP(VDataPuller)
#if (SYSTEMC_VERSION>20011000)
    : clk("clk"), reset("reset"), M_AXI_AWREADY("M_AXI_AWREADY"), 
      M_AXI_AWVALID("M_AXI_AWVALID"), M_AXI_AWSIZE("M_AXI_AWSIZE"), 
      M_AXI_AWLEN("M_AXI_AWLEN"), M_AXI_AWPROT("M_AXI_AWPROT"), 
      M_AXI_AWBURST("M_AXI_AWBURST"), M_AXI_AWLOCK("M_AXI_AWLOCK"), 
      M_AXI_AWCACHE("M_AXI_AWCACHE"), M_AXI_AWQOS("M_AXI_AWQOS"), 
      M_AXI_AWID("M_AXI_AWID"), M_AXI_WREADY("M_AXI_WREADY"), 
      M_AXI_WVALID("M_AXI_WVALID"), M_AXI_WSTRB("M_AXI_WSTRB"), 
      M_AXI_WLAST("M_AXI_WLAST"), M_AXI_BREADY("M_AXI_BREADY"), 
      M_AXI_BVALID("M_AXI_BVALID"), M_AXI_BID("M_AXI_BID"), 
      M_AXI_BRESP("M_AXI_BRESP"), M_AXI_ARREADY("M_AXI_ARREADY"), 
      M_AXI_ARVALID("M_AXI_ARVALID"), M_AXI_ARSIZE("M_AXI_ARSIZE"), 
      M_AXI_ARLEN("M_AXI_ARLEN"), M_AXI_ARPROT("M_AXI_ARPROT"), 
      M_AXI_ARBURST("M_AXI_ARBURST"), M_AXI_ARLOCK("M_AXI_ARLOCK"), 
      M_AXI_ARCACHE("M_AXI_ARCACHE"), M_AXI_ARQOS("M_AXI_ARQOS"), 
      M_AXI_ARID("M_AXI_ARID"), M_AXI_RREADY("M_AXI_RREADY"), 
      M_AXI_RVALID("M_AXI_RVALID"), M_AXI_RID("M_AXI_RID"), 
      M_AXI_RLAST("M_AXI_RLAST"), M_AXI_RRESP("M_AXI_RRESP"), 
      io_matrixData_ready("io_matrixData_ready"), io_matrixData_valid("io_matrixData_valid"), 
      io_vectorData_ready("io_vectorData_ready"), io_vectorData_valid("io_vectorData_valid"), 
      io_start("io_start"), io_stop("io_stop"), M_AXI_AWADDR("M_AXI_AWADDR"), 
      M_AXI_ARADDR("M_AXI_ARADDR"), io_matrixPtr("io_matrixPtr"), 
      io_vectorPtr("io_vectorPtr"), M_AXI_WDATA("M_AXI_WDATA"), 
      M_AXI_RDATA("M_AXI_RDATA"), io_matrixData_bits("io_matrixData_bits"), 
      io_vectorData_bits("io_vectorData_bits")
#endif
 {
    VDataPuller__Syms* __restrict vlSymsp = __VlSymsp = new VDataPuller__Syms(this, name());
    VDataPuller* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Sensitivities on all clocks and combo inputs
    SC_METHOD(eval);
    sensitive << clk;
    sensitive << reset;
    sensitive << M_AXI_ARREADY;
    sensitive << M_AXI_RDATA;
    sensitive << M_AXI_RID;
    sensitive << io_matrixData_ready;
    sensitive << io_vectorData_ready;
    sensitive << io_matrixPtr;
    sensitive << io_vectorPtr;
    sensitive << io_start;
    sensitive << io_stop;
    
    // Reset internal values
    
    // Reset structure values
    __Vcellinp__v__io_stop = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_start = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_vectorPtr = VL_RAND_RESET_I(32);
    __Vcellinp__v__io_matrixPtr = VL_RAND_RESET_I(32);
    __Vcellinp__v__io_vectorData_ready = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_matrixData_ready = VL_RAND_RESET_I(1);
    __Vcellinp__v__M_AXI_RID = VL_RAND_RESET_I(2);
    __Vcellinp__v__M_AXI_RDATA = VL_RAND_RESET_Q(64);
    __Vcellinp__v__M_AXI_ARREADY = VL_RAND_RESET_I(1);
    __Vcellinp__v__reset = VL_RAND_RESET_I(1);
    __Vcellinp__v__clk = VL_RAND_RESET_I(1);
    v__DOT__canAcceptData = VL_RAND_RESET_I(1);
    v__DOT__state = VL_RAND_RESET_I(2);
    v__DOT__T10 = VL_RAND_RESET_I(1);
    v__DOT__T13 = VL_RAND_RESET_I(1);
    v__DOT__T17 = VL_RAND_RESET_I(1);
    v__DOT__T21 = VL_RAND_RESET_I(1);
    v__DOT__regDenseVecPtr = VL_RAND_RESET_I(32);
    v__DOT__regMatrixPtr = VL_RAND_RESET_I(32);
    __Vclklast__TOP____Vcellinp__v__clk = VL_RAND_RESET_I(1);
}

void VDataPuller::__Vconfigure(VDataPuller__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

VDataPuller::~VDataPuller() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void VDataPuller::eval() {
    VDataPuller__Syms* __restrict vlSymsp = this->__VlSymsp; // Setup global symbol table
    VDataPuller* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    VL_DEBUG_IF(VL_PRINTF("\n----TOP Evaluate VDataPuller::eval\n"); );
    int __VclockLoop = 0;
    IData __Vchange=1;
    while (VL_LIKELY(__Vchange)) {
	VL_DEBUG_IF(VL_PRINTF(" Clock loop\n"););
	vlSymsp->__Vm_activity = true;
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (++__VclockLoop > 100) vl_fatal(__FILE__,__LINE__,__FILE__,"Verilated model didn't converge");
    }
}

void VDataPuller::_eval_initial_loop(VDataPuller__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    int __VclockLoop = 0;
    IData __Vchange=1;
    while (VL_LIKELY(__Vchange)) {
	_eval_settle(vlSymsp);
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (++__VclockLoop > 100) vl_fatal(__FILE__,__LINE__,__FILE__,"Verilated model didn't DC converge");
    }
}

//--------------------
// Internal Methods

void VDataPuller::_settle__TOP__1(VDataPuller__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VDataPuller::_settle__TOP__1\n"); );
    VDataPuller* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(4,vlTOPp->M_AXI_ARQOS, 0);
    VL_ASSIGN_SII(4,vlTOPp->M_AXI_ARCACHE, 2);
    VL_ASSIGN_SII(1,vlTOPp->M_AXI_ARLOCK, 0);
    VL_ASSIGN_SII(2,vlTOPp->M_AXI_ARBURST, 1);
    VL_ASSIGN_SII(3,vlTOPp->M_AXI_ARPROT, 0);
    VL_ASSIGN_SII(3,vlTOPp->M_AXI_ARSIZE, 0);
    VL_ASSIGN_SII(1,vlTOPp->M_AXI_BREADY, 0);
    VL_ASSIGN_SII(1,vlTOPp->M_AXI_WLAST, 0);
    VL_ASSIGN_SII(8,vlTOPp->M_AXI_WSTRB, 0);
    VL_ASSIGN_SQQ(64,vlTOPp->M_AXI_WDATA, VL_ULL(0));
    VL_ASSIGN_SII(1,vlTOPp->M_AXI_WVALID, 0);
    VL_ASSIGN_SII(2,vlTOPp->M_AXI_AWID, 0);
    VL_ASSIGN_SII(4,vlTOPp->M_AXI_AWQOS, 0);
    VL_ASSIGN_SII(4,vlTOPp->M_AXI_AWCACHE, 0);
    VL_ASSIGN_SII(1,vlTOPp->M_AXI_AWLOCK, 0);
    VL_ASSIGN_SII(2,vlTOPp->M_AXI_AWBURST, 0);
    VL_ASSIGN_SII(3,vlTOPp->M_AXI_AWPROT, 0);
    VL_ASSIGN_SII(8,vlTOPp->M_AXI_AWLEN, 0);
    VL_ASSIGN_SII(3,vlTOPp->M_AXI_AWSIZE, 0);
    VL_ASSIGN_SII(32,vlTOPp->M_AXI_AWADDR, 0);
    VL_ASSIGN_SII(1,vlTOPp->M_AXI_AWVALID, 0);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_vectorData_ready, vlTOPp->io_vectorData_ready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_matrixData_ready, vlTOPp->io_matrixData_ready);
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__M_AXI_RDATA, vlTOPp->M_AXI_RDATA);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__M_AXI_ARREADY, vlTOPp->M_AXI_ARREADY);
    VL_ASSIGN_ISI(2,vlTOPp->__Vcellinp__v__M_AXI_RID, vlTOPp->M_AXI_RID);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__clk, vlTOPp->clk);
}

void VDataPuller::_combo__TOP__2(VDataPuller__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VDataPuller::_combo__TOP__2\n"); );
    VDataPuller* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_vectorData_ready, vlTOPp->io_vectorData_ready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_matrixData_ready, vlTOPp->io_matrixData_ready);
    VL_ASSIGN_QSQ(64,vlTOPp->__Vcellinp__v__M_AXI_RDATA, vlTOPp->M_AXI_RDATA);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__M_AXI_ARREADY, vlTOPp->M_AXI_ARREADY);
    VL_ASSIGN_ISI(2,vlTOPp->__Vcellinp__v__M_AXI_RID, vlTOPp->M_AXI_RID);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__clk, vlTOPp->clk);
    VL_ASSIGN_SQQ(64,vlTOPp->io_vectorData_bits, vlTOPp->__Vcellinp__v__M_AXI_RDATA);
    VL_ASSIGN_SQQ(64,vlTOPp->io_matrixData_bits, vlTOPp->__Vcellinp__v__M_AXI_RDATA);
}

void VDataPuller::_settle__TOP__3(VDataPuller__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VDataPuller::_settle__TOP__3\n"); );
    VDataPuller* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SQQ(64,vlTOPp->io_vectorData_bits, vlTOPp->__Vcellinp__v__M_AXI_RDATA);
    VL_ASSIGN_SQQ(64,vlTOPp->io_matrixData_bits, vlTOPp->__Vcellinp__v__M_AXI_RDATA);
}

void VDataPuller::_sequent__TOP__4(VDataPuller__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VDataPuller::_sequent__TOP__4\n"); );
    VDataPuller* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__v__DOT__state,1,0);
    //char	__VpadToAlign65[3];
    VL_SIG(__Vdly__v__DOT__regDenseVecPtr,31,0);
    VL_SIG(__Vdly__v__DOT__regMatrixPtr,31,0);
    // Body
    __Vdly__v__DOT__regDenseVecPtr = vlTOPp->v__DOT__regDenseVecPtr;
    __Vdly__v__DOT__regMatrixPtr = vlTOPp->v__DOT__regMatrixPtr;
    __Vdly__v__DOT__state = vlTOPp->v__DOT__state;
    // ALWAYS at DataPuller.v:204
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__regDenseVecPtr = 0;
    } else {
	if (vlTOPp->v__DOT__T13) {
	    __Vdly__v__DOT__regDenseVecPtr = ((IData)(8) 
					      + vlTOPp->v__DOT__regDenseVecPtr);
	} else {
	    if ((0 == (IData)(vlTOPp->v__DOT__state))) {
		__Vdly__v__DOT__regDenseVecPtr = vlTOPp->__Vcellinp__v__io_vectorPtr;
	    }
	}
    }
    // ALWAYS at DataPuller.v:211
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__regMatrixPtr = 0;
    } else {
	if (vlTOPp->v__DOT__T21) {
	    __Vdly__v__DOT__regMatrixPtr = ((IData)(0x40) 
					    + vlTOPp->v__DOT__regMatrixPtr);
	} else {
	    if ((0 == (IData)(vlTOPp->v__DOT__state))) {
		__Vdly__v__DOT__regMatrixPtr = vlTOPp->__Vcellinp__v__io_matrixPtr;
	    }
	}
    }
    // ALWAYS at DataPuller.v:191
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__state = 0;
    } else {
	if (vlTOPp->v__DOT__T21) {
	    __Vdly__v__DOT__state = 1;
	} else {
	    if (((IData)(vlTOPp->v__DOT__T17) & (IData)(vlTOPp->__Vcellinp__v__io_stop))) {
		__Vdly__v__DOT__state = 0;
	    } else {
		if (vlTOPp->v__DOT__T13) {
		    __Vdly__v__DOT__state = 2;
		} else {
		    if (((IData)(vlTOPp->v__DOT__T10) 
			 & (IData)(vlTOPp->__Vcellinp__v__io_stop))) {
			__Vdly__v__DOT__state = 0;
		    } else {
			if (((0 == (IData)(vlTOPp->v__DOT__state)) 
			     & (IData)(vlTOPp->__Vcellinp__v__io_start))) {
			    __Vdly__v__DOT__state = 1;
			}
		    }
		}
	    }
	}
    }
    vlTOPp->v__DOT__regDenseVecPtr = __Vdly__v__DOT__regDenseVecPtr;
    vlTOPp->v__DOT__regMatrixPtr = __Vdly__v__DOT__regMatrixPtr;
    vlTOPp->v__DOT__state = __Vdly__v__DOT__state;
    vlTOPp->v__DOT__canAcceptData = ((1 == (IData)(vlTOPp->v__DOT__state)) 
				     | (2 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T10 = ((0 != (IData)(vlTOPp->v__DOT__state)) 
			   & (1 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T17 = ((~ ((0 == (IData)(vlTOPp->v__DOT__state)) 
			       | (1 == (IData)(vlTOPp->v__DOT__state)))) 
			   & (2 == (IData)(vlTOPp->v__DOT__state)));
}

void VDataPuller::_combo__TOP__5(VDataPuller__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VDataPuller::_combo__TOP__5\n"); );
    VDataPuller* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_vectorPtr, vlTOPp->io_vectorPtr);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_matrixPtr, vlTOPp->io_matrixPtr);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_start, vlTOPp->io_start);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__reset, vlTOPp->reset);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_stop, vlTOPp->io_stop);
}

void VDataPuller::_settle__TOP__6(VDataPuller__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VDataPuller::_settle__TOP__6\n"); );
    VDataPuller* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_vectorPtr, vlTOPp->io_vectorPtr);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_matrixPtr, vlTOPp->io_matrixPtr);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_start, vlTOPp->io_start);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__reset, vlTOPp->reset);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_stop, vlTOPp->io_stop);
    vlTOPp->v__DOT__canAcceptData = ((1 == (IData)(vlTOPp->v__DOT__state)) 
				     | (2 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T10 = ((0 != (IData)(vlTOPp->v__DOT__state)) 
			   & (1 == (IData)(vlTOPp->v__DOT__state)));
    vlTOPp->v__DOT__T17 = ((~ ((0 == (IData)(vlTOPp->v__DOT__state)) 
			       | (1 == (IData)(vlTOPp->v__DOT__state)))) 
			   & (2 == (IData)(vlTOPp->v__DOT__state)));
    VL_ASSIGN_SII(1,vlTOPp->io_vectorData_valid, ((IData)(vlTOPp->v__DOT__canAcceptData) 
						  & (1 
						     == (IData)(vlTOPp->__Vcellinp__v__M_AXI_RID))));
    VL_ASSIGN_SII(1,vlTOPp->io_matrixData_valid, ((IData)(vlTOPp->v__DOT__canAcceptData) 
						  & (2 
						     == (IData)(vlTOPp->__Vcellinp__v__M_AXI_RID))));
    VL_ASSIGN_SII(1,vlTOPp->M_AXI_RREADY, ((IData)(vlTOPp->v__DOT__canAcceptData) 
					   & ((1 == (IData)(vlTOPp->__Vcellinp__v__M_AXI_RID))
					       ? (IData)(vlTOPp->__Vcellinp__v__io_vectorData_ready)
					       : (IData)(vlTOPp->__Vcellinp__v__io_matrixData_ready))));
    vlTOPp->v__DOT__T13 = ((IData)(vlTOPp->v__DOT__T10) 
			   & ((~ (IData)(vlTOPp->__Vcellinp__v__io_stop)) 
			      & (IData)(vlTOPp->__Vcellinp__v__M_AXI_ARREADY)));
    VL_ASSIGN_SII(8,vlTOPp->M_AXI_ARLEN, ((IData)(vlTOPp->v__DOT__T17)
					   ? 7 : 0));
    VL_ASSIGN_SII(2,vlTOPp->M_AXI_ARID, ((IData)(vlTOPp->v__DOT__T17)
					  ? 2 : (IData)(vlTOPp->v__DOT__T10)));
    VL_ASSIGN_SII(1,vlTOPp->M_AXI_ARVALID, ((IData)(vlTOPp->v__DOT__T17) 
					    | (IData)(vlTOPp->v__DOT__T10)));
    vlTOPp->v__DOT__T21 = ((IData)(vlTOPp->v__DOT__T17) 
			   & ((~ (IData)(vlTOPp->__Vcellinp__v__io_stop)) 
			      & (IData)(vlTOPp->__Vcellinp__v__M_AXI_ARREADY)));
    VL_ASSIGN_SII(32,vlTOPp->M_AXI_ARADDR, ((IData)(vlTOPp->v__DOT__T17)
					     ? vlTOPp->v__DOT__regMatrixPtr
					     : ((IData)(vlTOPp->v__DOT__T10)
						 ? vlTOPp->v__DOT__regDenseVecPtr
						 : 0)));
}

void VDataPuller::_combo__TOP__7(VDataPuller__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VDataPuller::_combo__TOP__7\n"); );
    VDataPuller* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->io_vectorData_valid, ((IData)(vlTOPp->v__DOT__canAcceptData) 
						  & (1 
						     == (IData)(vlTOPp->__Vcellinp__v__M_AXI_RID))));
    VL_ASSIGN_SII(1,vlTOPp->io_matrixData_valid, ((IData)(vlTOPp->v__DOT__canAcceptData) 
						  & (2 
						     == (IData)(vlTOPp->__Vcellinp__v__M_AXI_RID))));
    VL_ASSIGN_SII(1,vlTOPp->M_AXI_RREADY, ((IData)(vlTOPp->v__DOT__canAcceptData) 
					   & ((1 == (IData)(vlTOPp->__Vcellinp__v__M_AXI_RID))
					       ? (IData)(vlTOPp->__Vcellinp__v__io_vectorData_ready)
					       : (IData)(vlTOPp->__Vcellinp__v__io_matrixData_ready))));
    vlTOPp->v__DOT__T13 = ((IData)(vlTOPp->v__DOT__T10) 
			   & ((~ (IData)(vlTOPp->__Vcellinp__v__io_stop)) 
			      & (IData)(vlTOPp->__Vcellinp__v__M_AXI_ARREADY)));
    vlTOPp->v__DOT__T21 = ((IData)(vlTOPp->v__DOT__T17) 
			   & ((~ (IData)(vlTOPp->__Vcellinp__v__io_stop)) 
			      & (IData)(vlTOPp->__Vcellinp__v__M_AXI_ARREADY)));
}

void VDataPuller::_sequent__TOP__8(VDataPuller__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VDataPuller::_sequent__TOP__8\n"); );
    VDataPuller* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(8,vlTOPp->M_AXI_ARLEN, ((IData)(vlTOPp->v__DOT__T17)
					   ? 7 : 0));
    VL_ASSIGN_SII(2,vlTOPp->M_AXI_ARID, ((IData)(vlTOPp->v__DOT__T17)
					  ? 2 : (IData)(vlTOPp->v__DOT__T10)));
    VL_ASSIGN_SII(1,vlTOPp->M_AXI_ARVALID, ((IData)(vlTOPp->v__DOT__T17) 
					    | (IData)(vlTOPp->v__DOT__T10)));
    VL_ASSIGN_SII(32,vlTOPp->M_AXI_ARADDR, ((IData)(vlTOPp->v__DOT__T17)
					     ? vlTOPp->v__DOT__regMatrixPtr
					     : ((IData)(vlTOPp->v__DOT__T10)
						 ? vlTOPp->v__DOT__regDenseVecPtr
						 : 0)));
}

void VDataPuller::_eval(VDataPuller__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VDataPuller::_eval\n"); );
    VDataPuller* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__2(vlSymsp);
    if (((IData)(vlTOPp->__Vcellinp__v__clk) & (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__v__clk)))) {
	vlTOPp->_sequent__TOP__4(vlSymsp);
    }
    vlTOPp->_combo__TOP__5(vlSymsp);
    vlTOPp->_combo__TOP__7(vlSymsp);
    if (((IData)(vlTOPp->__Vcellinp__v__clk) & (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__v__clk)))) {
	vlTOPp->_sequent__TOP__8(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP____Vcellinp__v__clk = vlTOPp->__Vcellinp__v__clk;
}

void VDataPuller::_eval_initial(VDataPuller__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VDataPuller::_eval_initial\n"); );
    VDataPuller* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VDataPuller::final() {
    VL_DEBUG_IF(VL_PRINTF("    VDataPuller::final\n"); );
    // Variables
    VDataPuller__Syms* __restrict vlSymsp = this->__VlSymsp;
    VDataPuller* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VDataPuller::_eval_settle(VDataPuller__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VDataPuller::_eval_settle\n"); );
    VDataPuller* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__1(vlSymsp);
    vlTOPp->_settle__TOP__3(vlSymsp);
    vlTOPp->_settle__TOP__6(vlSymsp);
}

IData VDataPuller::_change_request(VDataPuller__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VDataPuller::_change_request\n"); );
    VDataPuller* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    IData __req = false;  // Logically a bool
    return __req;
}
