package BFSFrontEnd

import Chisel._
import Literal._
import Node._
import AXIStreamDefs._
import AXIDefs._

class RequestGenerator() extends Module {
  // TODO make these configurable from some global cfg
  val addrBits = 32
  val idBits = 2
  val mmapDataBits = 64       // width of AXI data bus
  val colLenDataBits = 32     // width of each column length
  val rowIndDataBits = 32     // width of each row index
  val dvDataBits = 1          // width of each dense vector element
  
  // calculate elements per beat for the various components
  val colLenPerBeat = mmapDataBits / colLenDataBits
  val rowIndPerBeat = mmapDataBits / rowIndDataBits
  val dvPerBeat = mmapDataBits / dvDataBits
  
  // define burst sizes for the various components
  val colLenBurstSize = 8
  val riBurstSize = 8
  val dvBurstSize = 1
  
  // calculate elements per burst for the various components
  val colLenPerBurst = colLenBurstSize * colLenPerBeat
  val rowIndPerBurst = rowIndBurstSize * rowIndPerBeat
  val dvPerBurst = dvBurstSize * dvPerBeat
    
  val io = new Bundle {
    // control interface
    val start = Bool(INPUT)
    val colStart = UInt(INPUT, 32)
    val colCount = UInt(INPUT, 32)
    val rowindStart = UInt(INPUT, 32)
    val nzCount = UInt(INPUT, 32)
    val dvStart = UInt(INPUT, 32)
    
    // status interface
    val state = UInt(OUTPUT, 32)
    
    // AXI read address channel output
    val readAddr = Decoupled(new AXIAddress(addrBits, idBits))

  }
  
  // inputs registered at start, then used for counting down the
  // number of elements left or as memory pointers
  val regColCount = Reg(init = UInt(0, 32))
  val regNZCount = Reg(init = UInt(0, 32))
  val regColPtr = Reg(init = UInt(0, 32))
  val regRowIndPtr = Reg(init = UInt(0, 32))
  val regDVPtr = Reg(init = UInt(0, 32))
  
  // state machine definitions
  val sIdle :: sReqColLen :: sReqRowInd :: sReqDenVec :: Nil = Enum(UInt(), 4)
  val regState = Reg(init = UInt(sIdle))
  
  // default outputs
  io.state := regState
  // TODO outputs for readAddr
  
  
  // FSM for control
  switch ( regState ) {
    is ( sIdle ) {      
      
    }
    // TODO state machine for control
  }
}

// TODO add test code for the address generator here
