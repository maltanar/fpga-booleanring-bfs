// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VFrontendController.h for the primary calling header

#include "VFrontendController.h" // For This
#include "VFrontendController__Syms.h"

//--------------------
// STATIC VARIABLES


//--------------------

VL_SC_CTOR_IMP(VFrontendController)
#if (SYSTEMC_VERSION>20011000)
    : clk("clk"), reset("reset"), io_start("io_start"), 
      io_colLengths_ready("io_colLengths_ready"), io_colLengths_valid("io_colLengths_valid"), 
      io_rowIndices_ready("io_rowIndices_ready"), io_rowIndices_valid("io_rowIndices_valid"), 
      io_dvValues_ready("io_dvValues_ready"), io_dvValues_valid("io_dvValues_valid"), 
      io_dvValues_bits("io_dvValues_bits"), io_resMemPort_dataIn("io_resMemPort_dataIn"), 
      io_resMemPort_writeEn("io_resMemPort_writeEn"), 
      io_resMemPort_dataOut("io_resMemPort_dataOut"), 
      io_resMemPort_addr("io_resMemPort_addr"), io_colCount("io_colCount"), 
      io_state("io_state"), io_processedColCount("io_processedColCount"), 
      io_processedNZCount("io_processedNZCount"), io_colLengths_bits("io_colLengths_bits"), 
      io_rowIndices_bits("io_rowIndices_bits")
#endif
 {
    VFrontendController__Syms* __restrict vlSymsp = __VlSymsp = new VFrontendController__Syms(this, name());
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Sensitivities on all clocks and combo inputs
    SC_METHOD(eval);
    sensitive << clk;
    sensitive << reset;
    sensitive << io_start;
    sensitive << io_colCount;
    sensitive << io_colLengths_valid;
    sensitive << io_colLengths_bits;
    sensitive << io_rowIndices_valid;
    sensitive << io_rowIndices_bits;
    sensitive << io_dvValues_valid;
    sensitive << io_dvValues_bits;
    
    // Reset internal values
    
    // Reset structure values
    __Vcellinp__v__io_dvValues_bits = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_dvValues_valid = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_rowIndices_bits = VL_RAND_RESET_I(32);
    __Vcellinp__v__io_rowIndices_valid = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_colLengths_bits = VL_RAND_RESET_I(32);
    __Vcellinp__v__io_colLengths_valid = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_colCount = VL_RAND_RESET_I(32);
    __Vcellinp__v__io_start = VL_RAND_RESET_I(1);
    __Vcellinp__v__reset = VL_RAND_RESET_I(1);
    __Vcellinp__v__clk = VL_RAND_RESET_I(1);
    v__DOT__T1 = VL_RAND_RESET_I(1);
    v__DOT__T5 = VL_RAND_RESET_I(1);
    v__DOT__regCurrentColLen = VL_RAND_RESET_I(32);
    v__DOT__regState = VL_RAND_RESET_I(2);
    v__DOT__regColCount = VL_RAND_RESET_I(32);
    v__DOT__T22 = VL_RAND_RESET_I(1);
    v__DOT__T23 = VL_RAND_RESET_I(1);
    v__DOT__regProcessedNZCount = VL_RAND_RESET_I(32);
    __Vclklast__TOP____Vcellinp__v__clk = VL_RAND_RESET_I(1);
}

void VFrontendController::__Vconfigure(VFrontendController__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

VFrontendController::~VFrontendController() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void VFrontendController::eval() {
    VFrontendController__Syms* __restrict vlSymsp = this->__VlSymsp; // Setup global symbol table
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    VL_DEBUG_IF(VL_PRINTF("\n----TOP Evaluate VFrontendController::eval\n"); );
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

void VFrontendController::_eval_initial_loop(VFrontendController__Syms* __restrict vlSymsp) {
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

void VFrontendController::_settle__TOP__1(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_settle__TOP__1\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->io_resMemPort_dataIn, 1);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_rowIndices_bits, vlTOPp->io_rowIndices_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_dvValues_bits, vlTOPp->io_dvValues_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_colLengths_valid, vlTOPp->io_colLengths_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_rowIndices_valid, vlTOPp->io_rowIndices_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_dvValues_valid, vlTOPp->io_dvValues_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__clk, vlTOPp->clk);
}

void VFrontendController::_combo__TOP__2(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_combo__TOP__2\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_rowIndices_bits, vlTOPp->io_rowIndices_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_dvValues_bits, vlTOPp->io_dvValues_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_colLengths_valid, vlTOPp->io_colLengths_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_rowIndices_valid, vlTOPp->io_rowIndices_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_dvValues_valid, vlTOPp->io_dvValues_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__clk, vlTOPp->clk);
    VL_ASSIGN_SII(10,vlTOPp->io_resMemPort_addr, (0x3ff 
						  & vlTOPp->__Vcellinp__v__io_rowIndices_bits));
}

void VFrontendController::_settle__TOP__3(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_settle__TOP__3\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(10,vlTOPp->io_resMemPort_addr, (0x3ff 
						  & vlTOPp->__Vcellinp__v__io_rowIndices_bits));
}

void VFrontendController::_sequent__TOP__4(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_sequent__TOP__4\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__v__DOT__regState,1,0);
    //char	__VpadToAlign65[3];
    VL_SIG(__Vdly__v__DOT__regCurrentColLen,31,0);
    VL_SIG(__Vdly__v__DOT__regColCount,31,0);
    VL_SIG(__Vdly__v__DOT__regProcessedNZCount,31,0);
    // Body
    __Vdly__v__DOT__regProcessedNZCount = vlTOPp->v__DOT__regProcessedNZCount;
    __Vdly__v__DOT__regColCount = vlTOPp->v__DOT__regColCount;
    __Vdly__v__DOT__regState = vlTOPp->v__DOT__regState;
    __Vdly__v__DOT__regCurrentColLen = vlTOPp->v__DOT__regCurrentColLen;
    // ALWAYS at FrontendController.v:156
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__regProcessedNZCount = 0;
    } else {
	if (vlTOPp->v__DOT__T1) {
	    __Vdly__v__DOT__regProcessedNZCount = ((IData)(1) 
						   + vlTOPp->v__DOT__regProcessedNZCount);
	} else {
	    if ((0 == (IData)(vlTOPp->v__DOT__regState))) {
		__Vdly__v__DOT__regProcessedNZCount = 0;
	    }
	}
    }
    // ALWAYS at FrontendController.v:149
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__regColCount = 0;
    } else {
	if (vlTOPp->v__DOT__T23) {
	    __Vdly__v__DOT__regColCount = (vlTOPp->v__DOT__regColCount 
					   - (IData)(1));
	} else {
	    if ((0 == (IData)(vlTOPp->v__DOT__regState))) {
		__Vdly__v__DOT__regColCount = vlTOPp->__Vcellinp__v__io_colCount;
	    }
	}
    }
    // ALWAYS at FrontendController.v:138
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__regState = 0;
    } else {
	if (vlTOPp->v__DOT__T22) {
	    __Vdly__v__DOT__regState = 1;
	} else {
	    if (vlTOPp->v__DOT__T23) {
		__Vdly__v__DOT__regState = 2;
	    } else {
		if (((1 == (IData)(vlTOPp->v__DOT__regState)) 
		     & (0 == vlTOPp->v__DOT__regColCount))) {
		    __Vdly__v__DOT__regState = 0;
		} else {
		    if (((0 == (IData)(vlTOPp->v__DOT__regState)) 
			 & (IData)(vlTOPp->__Vcellinp__v__io_start))) {
			__Vdly__v__DOT__regState = 1;
		    }
		}
	    }
	}
    }
    // ALWAYS at FrontendController.v:129
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__regCurrentColLen = 0;
    } else {
	if (vlTOPp->v__DOT__T1) {
	    __Vdly__v__DOT__regCurrentColLen = (vlTOPp->v__DOT__regCurrentColLen 
						- (IData)(1));
	} else {
	    if (vlTOPp->v__DOT__T23) {
		__Vdly__v__DOT__regCurrentColLen = vlTOPp->__Vcellinp__v__io_colLengths_bits;
	    } else {
		if ((0 == (IData)(vlTOPp->v__DOT__regState))) {
		    __Vdly__v__DOT__regCurrentColLen = 0;
		}
	    }
	}
    }
    vlTOPp->v__DOT__regProcessedNZCount = __Vdly__v__DOT__regProcessedNZCount;
    vlTOPp->v__DOT__regColCount = __Vdly__v__DOT__regColCount;
    vlTOPp->v__DOT__regState = __Vdly__v__DOT__regState;
    vlTOPp->v__DOT__regCurrentColLen = __Vdly__v__DOT__regCurrentColLen;
    VL_ASSIGN_SII(32,vlTOPp->io_processedNZCount, vlTOPp->v__DOT__regProcessedNZCount);
    VL_ASSIGN_SII(32,vlTOPp->io_state, vlTOPp->v__DOT__regState);
    VL_ASSIGN_SII(1,vlTOPp->io_colLengths_ready, ((1 
						   == (IData)(vlTOPp->v__DOT__regState)) 
						  & (0 
						     != vlTOPp->v__DOT__regColCount)));
}

void VFrontendController::_combo__TOP__5(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_combo__TOP__5\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_colCount, vlTOPp->io_colCount);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_start, vlTOPp->io_start);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_colLengths_bits, vlTOPp->io_colLengths_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__reset, vlTOPp->reset);
    vlTOPp->v__DOT__T23 = ((1 == (IData)(vlTOPp->v__DOT__regState)) 
			   & ((0 != vlTOPp->v__DOT__regColCount) 
			      & (IData)(vlTOPp->__Vcellinp__v__io_colLengths_valid)));
    vlTOPp->v__DOT__T5 = ((0 == vlTOPp->v__DOT__regCurrentColLen) 
			  & (IData)(vlTOPp->__Vcellinp__v__io_dvValues_valid));
}

void VFrontendController::_settle__TOP__6(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_settle__TOP__6\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_colCount, vlTOPp->io_colCount);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_start, vlTOPp->io_start);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_colLengths_bits, vlTOPp->io_colLengths_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__reset, vlTOPp->reset);
    VL_ASSIGN_SII(32,vlTOPp->io_processedNZCount, vlTOPp->v__DOT__regProcessedNZCount);
    VL_ASSIGN_SII(32,vlTOPp->io_state, vlTOPp->v__DOT__regState);
    VL_ASSIGN_SII(1,vlTOPp->io_colLengths_ready, ((1 
						   == (IData)(vlTOPp->v__DOT__regState)) 
						  & (0 
						     != vlTOPp->v__DOT__regColCount)));
    vlTOPp->v__DOT__T23 = ((1 == (IData)(vlTOPp->v__DOT__regState)) 
			   & ((0 != vlTOPp->v__DOT__regColCount) 
			      & (IData)(vlTOPp->__Vcellinp__v__io_colLengths_valid)));
    vlTOPp->v__DOT__T5 = ((0 == vlTOPp->v__DOT__regCurrentColLen) 
			  & (IData)(vlTOPp->__Vcellinp__v__io_dvValues_valid));
    VL_ASSIGN_SII(32,vlTOPp->io_processedColCount, 
		  (vlTOPp->__Vcellinp__v__io_colCount 
		   - vlTOPp->v__DOT__regColCount));
    vlTOPp->v__DOT__T22 = ((2 == (IData)(vlTOPp->v__DOT__regState)) 
			   & (IData)(vlTOPp->v__DOT__T5));
    vlTOPp->v__DOT__T1 = ((2 == (IData)(vlTOPp->v__DOT__regState)) 
			  & ((~ (IData)(vlTOPp->v__DOT__T5)) 
			     & ((IData)(vlTOPp->__Vcellinp__v__io_rowIndices_valid) 
				& (IData)(vlTOPp->__Vcellinp__v__io_dvValues_valid))));
}

void VFrontendController::_combo__TOP__7(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_combo__TOP__7\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(32,vlTOPp->io_processedColCount, 
		  (vlTOPp->__Vcellinp__v__io_colCount 
		   - vlTOPp->v__DOT__regColCount));
    vlTOPp->v__DOT__T22 = ((2 == (IData)(vlTOPp->v__DOT__regState)) 
			   & (IData)(vlTOPp->v__DOT__T5));
    vlTOPp->v__DOT__T1 = ((2 == (IData)(vlTOPp->v__DOT__regState)) 
			  & ((~ (IData)(vlTOPp->v__DOT__T5)) 
			     & ((IData)(vlTOPp->__Vcellinp__v__io_rowIndices_valid) 
				& (IData)(vlTOPp->__Vcellinp__v__io_dvValues_valid))));
    VL_ASSIGN_SII(1,vlTOPp->io_dvValues_ready, vlTOPp->v__DOT__T22);
    VL_ASSIGN_SII(1,vlTOPp->io_rowIndices_ready, vlTOPp->v__DOT__T1);
    VL_ASSIGN_SII(1,vlTOPp->io_resMemPort_writeEn, 
		  ((IData)(vlTOPp->v__DOT__T1) & (IData)(vlTOPp->__Vcellinp__v__io_dvValues_bits)));
}

void VFrontendController::_settle__TOP__8(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_settle__TOP__8\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->io_dvValues_ready, vlTOPp->v__DOT__T22);
    VL_ASSIGN_SII(1,vlTOPp->io_rowIndices_ready, vlTOPp->v__DOT__T1);
    VL_ASSIGN_SII(1,vlTOPp->io_resMemPort_writeEn, 
		  ((IData)(vlTOPp->v__DOT__T1) & (IData)(vlTOPp->__Vcellinp__v__io_dvValues_bits)));
}

void VFrontendController::_eval(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_eval\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__2(vlSymsp);
    if (((IData)(vlTOPp->__Vcellinp__v__clk) & (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__v__clk)))) {
	vlTOPp->_sequent__TOP__4(vlSymsp);
    }
    vlTOPp->_combo__TOP__5(vlSymsp);
    vlTOPp->_combo__TOP__7(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP____Vcellinp__v__clk = vlTOPp->__Vcellinp__v__clk;
}

void VFrontendController::_eval_initial(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_eval_initial\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VFrontendController::final() {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::final\n"); );
    // Variables
    VFrontendController__Syms* __restrict vlSymsp = this->__VlSymsp;
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VFrontendController::_eval_settle(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_eval_settle\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__1(vlSymsp);
    vlTOPp->_settle__TOP__3(vlSymsp);
    vlTOPp->_settle__TOP__6(vlSymsp);
    vlTOPp->_settle__TOP__8(vlSymsp);
}

IData VFrontendController::_change_request(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_change_request\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    IData __req = false;  // Logically a bool
    return __req;
}
