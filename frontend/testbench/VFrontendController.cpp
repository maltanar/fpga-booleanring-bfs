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
      io_memFill("io_memFill"), io_memDump("io_memDump"), 
      io_colLengths_ready("io_colLengths_ready"), io_colLengths_valid("io_colLengths_valid"), 
      io_rowIndices_ready("io_rowIndices_ready"), io_rowIndices_valid("io_rowIndices_valid"), 
      io_vectorMemDataIn_ready("io_vectorMemDataIn_ready"), 
      io_vectorMemDataIn_valid("io_vectorMemDataIn_valid"), 
      io_vectorMemDataOut_ready("io_vectorMemDataOut_ready"), 
      io_vectorMemDataOut_valid("io_vectorMemDataOut_valid"), 
      io_portA_writeEn("io_portA_writeEn"), io_portB_dataIn("io_portB_dataIn"), 
      io_portB_writeEn("io_portB_writeEn"), io_portB_dataOut("io_portB_dataOut"), 
      io_portA_addr("io_portA_addr"), io_portB_addr("io_portB_addr"), 
      io_state("io_state"), io_colCount("io_colCount"), 
      io_inputVecOffset("io_inputVecOffset"), io_outputVecOffset("io_outputVecOffset"), 
      io_colLengths_bits("io_colLengths_bits"), io_rowIndices_bits("io_rowIndices_bits"), 
      io_vectorMemDataIn_bits("io_vectorMemDataIn_bits"), 
      io_vectorMemDataOut_bits("io_vectorMemDataOut_bits"), 
      io_portA_dataIn("io_portA_dataIn"), io_portA_dataOut("io_portA_dataOut")
#endif
 {
    VFrontendController__Syms* __restrict vlSymsp = __VlSymsp = new VFrontendController__Syms(this, name());
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Sensitivities on all clocks and combo inputs
    SC_METHOD(eval);
    sensitive << clk;
    sensitive << reset;
    sensitive << io_start;
    sensitive << io_memFill;
    sensitive << io_memDump;
    sensitive << io_colCount;
    sensitive << io_inputVecOffset;
    sensitive << io_outputVecOffset;
    sensitive << io_colLengths_valid;
    sensitive << io_colLengths_bits;
    sensitive << io_rowIndices_valid;
    sensitive << io_rowIndices_bits;
    sensitive << io_vectorMemDataIn_valid;
    sensitive << io_vectorMemDataIn_bits;
    sensitive << io_vectorMemDataOut_ready;
    sensitive << io_portA_dataOut;
    
    // Reset internal values
    
    // Reset structure values
    __Vcellinp__v__io_portA_dataOut = VL_RAND_RESET_I(32);
    __Vcellinp__v__io_vectorMemDataOut_ready = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_vectorMemDataIn_bits = VL_RAND_RESET_I(32);
    __Vcellinp__v__io_vectorMemDataIn_valid = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_rowIndices_bits = VL_RAND_RESET_I(32);
    __Vcellinp__v__io_rowIndices_valid = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_colLengths_bits = VL_RAND_RESET_I(32);
    __Vcellinp__v__io_colLengths_valid = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_outputVecOffset = VL_RAND_RESET_I(32);
    __Vcellinp__v__io_inputVecOffset = VL_RAND_RESET_I(32);
    __Vcellinp__v__io_colCount = VL_RAND_RESET_I(32);
    __Vcellinp__v__io_memDump = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_memFill = VL_RAND_RESET_I(1);
    __Vcellinp__v__io_start = VL_RAND_RESET_I(1);
    __Vcellinp__v__reset = VL_RAND_RESET_I(1);
    __Vcellinp__v__clk = VL_RAND_RESET_I(1);
    v__DOT__regXIndex = VL_RAND_RESET_I(15);
    v__DOT__regState = VL_RAND_RESET_I(3);
    v__DOT__T22 = VL_RAND_RESET_I(1);
    v__DOT__regColCount = VL_RAND_RESET_I(32);
    v__DOT__T40 = VL_RAND_RESET_I(1);
    v__DOT__T44 = VL_RAND_RESET_I(1);
    v__DOT__T47 = VL_RAND_RESET_I(1);
    v__DOT__T50 = VL_RAND_RESET_I(1);
    v__DOT__regCurrentColLen = VL_RAND_RESET_I(32);
    v__DOT__T58 = VL_RAND_RESET_I(1);
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
    VL_ASSIGN_SII(1,vlTOPp->io_portB_dataIn, 1);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_vectorMemDataIn_bits, vlTOPp->io_vectorMemDataIn_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_vectorMemDataOut_ready, vlTOPp->io_vectorMemDataOut_ready);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_rowIndices_bits, vlTOPp->io_rowIndices_bits);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_outputVecOffset, vlTOPp->io_outputVecOffset);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_start, vlTOPp->io_start);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_colLengths_valid, vlTOPp->io_colLengths_valid);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_portA_dataOut, vlTOPp->io_portA_dataOut);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_vectorMemDataIn_valid, vlTOPp->io_vectorMemDataIn_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_rowIndices_valid, vlTOPp->io_rowIndices_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__clk, vlTOPp->clk);
}

void VFrontendController::_combo__TOP__2(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_combo__TOP__2\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_vectorMemDataIn_bits, vlTOPp->io_vectorMemDataIn_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_vectorMemDataOut_ready, vlTOPp->io_vectorMemDataOut_ready);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_rowIndices_bits, vlTOPp->io_rowIndices_bits);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_outputVecOffset, vlTOPp->io_outputVecOffset);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_start, vlTOPp->io_start);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_colLengths_valid, vlTOPp->io_colLengths_valid);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_portA_dataOut, vlTOPp->io_portA_dataOut);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_vectorMemDataIn_valid, vlTOPp->io_vectorMemDataIn_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_rowIndices_valid, vlTOPp->io_rowIndices_valid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__clk, vlTOPp->clk);
    VL_ASSIGN_SII(32,vlTOPp->io_portA_dataIn, vlTOPp->__Vcellinp__v__io_vectorMemDataIn_bits);
    VL_ASSIGN_SII(15,vlTOPp->io_portB_addr, (0x7fff 
					     & ((IData)((QData)(vlTOPp->__Vcellinp__v__io_rowIndices_bits)) 
						+ (IData)(
							  (VL_ULL(0x3fffffffff) 
							   & ((QData)((IData)(vlTOPp->__Vcellinp__v__io_outputVecOffset)) 
							      << 5))))));
    VL_ASSIGN_SII(32,vlTOPp->io_vectorMemDataOut_bits, vlTOPp->__Vcellinp__v__io_portA_dataOut);
}

void VFrontendController::_settle__TOP__3(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_settle__TOP__3\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(32,vlTOPp->io_portA_dataIn, vlTOPp->__Vcellinp__v__io_vectorMemDataIn_bits);
    VL_ASSIGN_SII(15,vlTOPp->io_portB_addr, (0x7fff 
					     & ((IData)((QData)(vlTOPp->__Vcellinp__v__io_rowIndices_bits)) 
						+ (IData)(
							  (VL_ULL(0x3fffffffff) 
							   & ((QData)((IData)(vlTOPp->__Vcellinp__v__io_outputVecOffset)) 
							      << 5))))));
    VL_ASSIGN_SII(32,vlTOPp->io_vectorMemDataOut_bits, vlTOPp->__Vcellinp__v__io_portA_dataOut);
}

void VFrontendController::_sequent__TOP__4(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_sequent__TOP__4\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__v__DOT__regState,2,0);
    //char	__VpadToAlign65[1];
    VL_SIG16(__Vdly__v__DOT__regXIndex,14,0);
    VL_SIG(__Vdly__v__DOT__regColCount,31,0);
    VL_SIG(__Vdly__v__DOT__regCurrentColLen,31,0);
    // Body
    __Vdly__v__DOT__regColCount = vlTOPp->v__DOT__regColCount;
    __Vdly__v__DOT__regXIndex = vlTOPp->v__DOT__regXIndex;
    __Vdly__v__DOT__regCurrentColLen = vlTOPp->v__DOT__regCurrentColLen;
    __Vdly__v__DOT__regState = vlTOPp->v__DOT__regState;
    // ALWAYS at FrontendController.v:251
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__regColCount = 0;
    } else {
	if (vlTOPp->v__DOT__T40) {
	    __Vdly__v__DOT__regColCount = (vlTOPp->v__DOT__regColCount 
					   - (IData)(1));
	} else {
	    if ((0 == (IData)(vlTOPp->v__DOT__regState))) {
		__Vdly__v__DOT__regColCount = vlTOPp->__Vcellinp__v__io_colCount;
	    }
	}
    }
    // ALWAYS at FrontendController.v:227
    __Vdly__v__DOT__regXIndex = (0x7fff & (IData)((VL_ULL(0x3fffffffff) 
						   & ((IData)(vlTOPp->__Vcellinp__v__reset)
						       ? VL_ULL(0)
						       : 
						      ((IData)(vlTOPp->v__DOT__T50)
						        ? (QData)((IData)(
									  (0x7fff 
									   & ((IData)(1) 
									      + (IData)(vlTOPp->v__DOT__regXIndex)))))
						        : 
						       ((IData)(vlTOPp->v__DOT__T47)
							 ? (QData)((IData)(
									   (0x7fff 
									    & ((IData)(0x20) 
									       + (IData)(vlTOPp->v__DOT__regXIndex)))))
							 : 
							((IData)(vlTOPp->v__DOT__T44)
							  ? (QData)((IData)(
									    (0x7fff 
									     & ((IData)(0x20) 
										+ (IData)(vlTOPp->v__DOT__regXIndex)))))
							  : 
							 ((0 
							   == (IData)(vlTOPp->v__DOT__regState))
							   ? 
							  ((QData)((IData)(vlTOPp->__Vcellinp__v__io_inputVecOffset)) 
							   << 5)
							   : (QData)((IData)(vlTOPp->v__DOT__regXIndex))))))))));
    // ALWAYS at FrontendController.v:258
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__regCurrentColLen = 0;
    } else {
	if (vlTOPp->v__DOT__T58) {
	    __Vdly__v__DOT__regCurrentColLen = (vlTOPp->v__DOT__regCurrentColLen 
						- (IData)(1));
	} else {
	    if (vlTOPp->v__DOT__T40) {
		__Vdly__v__DOT__regCurrentColLen = vlTOPp->__Vcellinp__v__io_colLengths_bits;
	    } else {
		if ((0 == (IData)(vlTOPp->v__DOT__regState))) {
		    __Vdly__v__DOT__regCurrentColLen = 0;
		}
	    }
	}
    }
    // ALWAYS at FrontendController.v:228
    if (vlTOPp->__Vcellinp__v__reset) {
	__Vdly__v__DOT__regState = 0;
    } else {
	if (vlTOPp->v__DOT__T50) {
	    __Vdly__v__DOT__regState = 4;
	} else {
	    if (vlTOPp->v__DOT__T40) {
		__Vdly__v__DOT__regState = 5;
	    } else {
		if (((4 == (IData)(vlTOPp->v__DOT__regState)) 
		     & (0 == vlTOPp->v__DOT__regColCount))) {
		    __Vdly__v__DOT__regState = 0;
		} else {
		    if ((3 == (IData)(vlTOPp->v__DOT__regState))) {
			__Vdly__v__DOT__regState = 2;
		    } else {
			if (((IData)(vlTOPp->v__DOT__T47) 
			     & (0x3ff == (0x3ff & ((IData)(vlTOPp->v__DOT__regXIndex) 
						   >> 5))))) {
			    __Vdly__v__DOT__regState = 0;
			} else {
			    if (vlTOPp->v__DOT__T47) {
				__Vdly__v__DOT__regState = 3;
			    } else {
				if (((IData)(vlTOPp->v__DOT__T44) 
				     & (0x3ff == (0x3ff 
						  & ((IData)(vlTOPp->v__DOT__regXIndex) 
						     >> 5))))) {
				    __Vdly__v__DOT__regState = 0;
				} else {
				    if (((IData)(vlTOPp->v__DOT__T22) 
					 & (~ ((IData)(vlTOPp->__Vcellinp__v__io_memDump) 
					       | (IData)(vlTOPp->__Vcellinp__v__io_memFill))))) {
					__Vdly__v__DOT__regState = 4;
				    } else {
					if (((IData)(vlTOPp->v__DOT__T22) 
					     & ((~ (IData)(vlTOPp->__Vcellinp__v__io_memDump)) 
						& (IData)(vlTOPp->__Vcellinp__v__io_memFill)))) {
					    __Vdly__v__DOT__regState = 1;
					} else {
					    if (((IData)(vlTOPp->v__DOT__T22) 
						 & (IData)(vlTOPp->__Vcellinp__v__io_memDump))) {
						__Vdly__v__DOT__regState = 2;
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    vlTOPp->v__DOT__regCurrentColLen = __Vdly__v__DOT__regCurrentColLen;
    vlTOPp->v__DOT__regXIndex = __Vdly__v__DOT__regXIndex;
    vlTOPp->v__DOT__regColCount = __Vdly__v__DOT__regColCount;
    vlTOPp->v__DOT__regState = __Vdly__v__DOT__regState;
    VL_ASSIGN_SII(10,vlTOPp->io_portA_addr, (0x3ff 
					     & ((IData)(vlTOPp->v__DOT__regXIndex) 
						>> 5)));
    VL_ASSIGN_SII(1,vlTOPp->io_vectorMemDataOut_valid, 
		  (2 == (IData)(vlTOPp->v__DOT__regState)));
    VL_ASSIGN_SII(1,vlTOPp->io_vectorMemDataIn_ready, 
		  (1 == (IData)(vlTOPp->v__DOT__regState)));
    VL_ASSIGN_SII(32,vlTOPp->io_state, vlTOPp->v__DOT__regState);
    VL_ASSIGN_SII(1,vlTOPp->io_rowIndices_ready, ((5 
						   == (IData)(vlTOPp->v__DOT__regState)) 
						  & (0 
						     != vlTOPp->v__DOT__regCurrentColLen)));
    VL_ASSIGN_SII(1,vlTOPp->io_colLengths_ready, ((4 
						   == (IData)(vlTOPp->v__DOT__regState)) 
						  & (0 
						     != vlTOPp->v__DOT__regColCount)));
    vlTOPp->v__DOT__T50 = ((5 == (IData)(vlTOPp->v__DOT__regState)) 
			   & (0 == vlTOPp->v__DOT__regCurrentColLen));
}

void VFrontendController::_combo__TOP__5(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_combo__TOP__5\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_colCount, vlTOPp->io_colCount);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_inputVecOffset, vlTOPp->io_inputVecOffset);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_colLengths_bits, vlTOPp->io_colLengths_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_memDump, vlTOPp->io_memDump);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_memFill, vlTOPp->io_memFill);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__reset, vlTOPp->reset);
    VL_ASSIGN_SII(1,vlTOPp->io_portA_writeEn, ((1 == (IData)(vlTOPp->v__DOT__regState)) 
					       & (IData)(vlTOPp->__Vcellinp__v__io_vectorMemDataIn_valid)));
    vlTOPp->v__DOT__T22 = ((0 == (IData)(vlTOPp->v__DOT__regState)) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_start));
    vlTOPp->v__DOT__T44 = ((1 == (IData)(vlTOPp->v__DOT__regState)) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_vectorMemDataIn_valid));
    vlTOPp->v__DOT__T47 = ((2 == (IData)(vlTOPp->v__DOT__regState)) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_vectorMemDataOut_ready));
    vlTOPp->v__DOT__T40 = ((4 == (IData)(vlTOPp->v__DOT__regState)) 
			   & ((0 != vlTOPp->v__DOT__regColCount) 
			      & (IData)(vlTOPp->__Vcellinp__v__io_colLengths_valid)));
    vlTOPp->v__DOT__T58 = ((5 == (IData)(vlTOPp->v__DOT__regState)) 
			   & ((0 != vlTOPp->v__DOT__regCurrentColLen) 
			      & (IData)(vlTOPp->__Vcellinp__v__io_rowIndices_valid)));
}

void VFrontendController::_settle__TOP__6(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_settle__TOP__6\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_colCount, vlTOPp->io_colCount);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_inputVecOffset, vlTOPp->io_inputVecOffset);
    VL_ASSIGN_ISI(32,vlTOPp->__Vcellinp__v__io_colLengths_bits, vlTOPp->io_colLengths_bits);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_memDump, vlTOPp->io_memDump);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__io_memFill, vlTOPp->io_memFill);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__v__reset, vlTOPp->reset);
    VL_ASSIGN_SII(10,vlTOPp->io_portA_addr, (0x3ff 
					     & ((IData)(vlTOPp->v__DOT__regXIndex) 
						>> 5)));
    VL_ASSIGN_SII(1,vlTOPp->io_vectorMemDataOut_valid, 
		  (2 == (IData)(vlTOPp->v__DOT__regState)));
    VL_ASSIGN_SII(1,vlTOPp->io_vectorMemDataIn_ready, 
		  (1 == (IData)(vlTOPp->v__DOT__regState)));
    VL_ASSIGN_SII(32,vlTOPp->io_state, vlTOPp->v__DOT__regState);
    VL_ASSIGN_SII(1,vlTOPp->io_portA_writeEn, ((1 == (IData)(vlTOPp->v__DOT__regState)) 
					       & (IData)(vlTOPp->__Vcellinp__v__io_vectorMemDataIn_valid)));
    VL_ASSIGN_SII(1,vlTOPp->io_rowIndices_ready, ((5 
						   == (IData)(vlTOPp->v__DOT__regState)) 
						  & (0 
						     != vlTOPp->v__DOT__regCurrentColLen)));
    VL_ASSIGN_SII(1,vlTOPp->io_colLengths_ready, ((4 
						   == (IData)(vlTOPp->v__DOT__regState)) 
						  & (0 
						     != vlTOPp->v__DOT__regColCount)));
    vlTOPp->v__DOT__T22 = ((0 == (IData)(vlTOPp->v__DOT__regState)) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_start));
    vlTOPp->v__DOT__T44 = ((1 == (IData)(vlTOPp->v__DOT__regState)) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_vectorMemDataIn_valid));
    vlTOPp->v__DOT__T47 = ((2 == (IData)(vlTOPp->v__DOT__regState)) 
			   & (IData)(vlTOPp->__Vcellinp__v__io_vectorMemDataOut_ready));
    vlTOPp->v__DOT__T50 = ((5 == (IData)(vlTOPp->v__DOT__regState)) 
			   & (0 == vlTOPp->v__DOT__regCurrentColLen));
    vlTOPp->v__DOT__T40 = ((4 == (IData)(vlTOPp->v__DOT__regState)) 
			   & ((0 != vlTOPp->v__DOT__regColCount) 
			      & (IData)(vlTOPp->__Vcellinp__v__io_colLengths_valid)));
    vlTOPp->v__DOT__T58 = ((5 == (IData)(vlTOPp->v__DOT__regState)) 
			   & ((0 != vlTOPp->v__DOT__regCurrentColLen) 
			      & (IData)(vlTOPp->__Vcellinp__v__io_rowIndices_valid)));
    VL_ASSIGN_SII(1,vlTOPp->io_portB_writeEn, ((IData)(vlTOPp->v__DOT__T58) 
					       & (vlTOPp->__Vcellinp__v__io_portA_dataOut 
						  >> 
						  (0x1f 
						   & (IData)(vlTOPp->v__DOT__regXIndex)))));
}

void VFrontendController::_combo__TOP__7(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_combo__TOP__7\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_SII(1,vlTOPp->io_portB_writeEn, ((IData)(vlTOPp->v__DOT__T58) 
					       & (vlTOPp->__Vcellinp__v__io_portA_dataOut 
						  >> 
						  (0x1f 
						   & (IData)(vlTOPp->v__DOT__regXIndex)))));
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
}

IData VFrontendController::_change_request(VFrontendController__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_PRINTF("    VFrontendController::_change_request\n"); );
    VFrontendController* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    IData __req = false;  // Logically a bool
    return __req;
}
