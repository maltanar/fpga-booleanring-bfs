package BFSBackend

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
  
  // define IDs for memory requests
  val colLenReqID = 1
  val rowIndReqID = 2
  val dvReqID = 3
  
  // calculate elements per beat for the various components
  val colLenPerBeat = mmapDataBits / colLenDataBits
  val rowIndPerBeat = mmapDataBits / rowIndDataBits
  val dvPerBeat = mmapDataBits / dvDataBits
  
  // define burst sizes for the various components
  val colLenBurstSize = 8
  val rowIndBurstSize = 8
  val dvBurstSize = 1
  
  // calculate elements per burst for the various components
  val colLenPerBurst = colLenBurstSize * colLenPerBeat
  val rowIndPerBurst = rowIndBurstSize * rowIndPerBeat
  val dvPerBurst = dvBurstSize * dvPerBeat
    
  val io = new Bundle {
    // control interface
    val start = Bool(INPUT)
    val nzCount = UInt(INPUT, 32)
    val colCount = UInt(INPUT, 32)
    val colLenStart = UInt(INPUT, 32)
    val rowIndStart = UInt(INPUT, 32)
    val dvStart = UInt(INPUT, 32)
    
    // status interface
    val state = UInt(OUTPUT, 32)
    
    // AXI read address channel output
    val readAddr = Decoupled(new AXIAddress(addrBits, idBits))

  }
  
  // inputs registered at start, then used for counting down the
  // number of elements left or as memory pointers
  val regColCount = Reg(init = UInt(0, 32))
  val regRowIndCount = Reg(init = UInt(0, 32))
  val regColLenPtr = Reg(init = UInt(0, 32))
  val regRowIndPtr = Reg(init = UInt(0, 32))
  val regDVPtr = Reg(init = UInt(0, 32))
  val regDVCount = Reg(init = UInt(0, 32))
  
  // state machine definitions
  val sIdle :: sReqColLen :: sReqRowInd :: sReqDenVec :: sCheckFinished :: Nil = Enum(UInt(), 5)
  val regState = Reg(init = UInt(sIdle))
  
  // default outputs
  io.state := regState
  
  // readAddr channel data that will be altered by the FSM
  io.readAddr.valid := Bool(false)
  io.readAddr.bits.addr := UInt(0)
  io.readAddr.bits.len := UInt(0)
  io.readAddr.bits.id := UInt(0)
  // the rest of the readAddr channel data is the same and not modified
  io.readAddr.bits.prot := UInt(0)
  io.readAddr.bits.qos := UInt(0)
  io.readAddr.bits.lock := Bool(false)
  io.readAddr.bits.cache := UInt("b0010") // no alloc, modifiable, no buffer
  io.readAddr.bits.size := UInt(log2Up((mmapDataBits/8)-1)) // full-datawidth bursts
  io.readAddr.bits.burst := UInt(1) // incrementing burst
  
  val colCountFinished = (regColCount === UInt(0))
  val rowIndFinished = (regRowIndCount === UInt(0))
  val denseVecFinished = (regDVCount === UInt(0))
  val allFinished = colCountFinished && rowIndFinished && denseVecFinished
  
  
  // FSM for control
  switch ( regState ) {
    is ( sIdle ) {
      // register the inputs while in idle
      // TODO handle burst alignment here!
      regColCount := io.colCount
      regRowIndCount := io.nzCount
      regDVCount := io.colCount
      regColLenPtr := io.colLenStart
      regRowIndPtr := io.rowIndStart
      regDVPtr := io.dvStart
      
      when ( io.start ) { regState := sReqColLen }
    }
    
    is ( sReqColLen ) {
      when ( colCountFinished ) {
        // requests for all col lengths already sent
        regState := sReqRowInd 
      } .otherwise {
        // push out next col len request
        io.readAddr.valid := Bool(true)
        io.readAddr.bits.addr := regColLenPtr
        io.readAddr.bits.id := UInt(colLenReqID)
        
        when ( io.readAddr.ready ) {
          // request accepted
          // decrement column count & move on to sReqRowInd
          regColCount := regColCount - UInt(colLenPerBurst)
          regColLenPtr := regColLenPtr + UInt(colLenPerBurst * 4) // TODO make parametrizable
          regState := sReqRowInd
        }
      }
    }
    
    is ( sReqRowInd ) {
      when ( rowIndFinished ) {
        regState := sReqDenVec
      } .otherwise {
        io.readAddr.valid := Bool(true)
        io.readAddr.bits.addr := regRowIndPtr
        io.readAddr.bits.id := UInt(rowIndReqID)
        
        when ( io.readAddr.ready ) {
          regRowIndCount := regRowIndCount - UInt(rowIndPerBurst)
          regRowIndPtr := regRowIndPtr + UInt(rowIndPerBurst * 4) // TODO make parametrizable
          regState := sReqDenVec
        }
      }
    }
    
    is ( sReqDenVec ) {
      when ( denseVecFinished ) {
        regState := sCheckFinished
      } .otherwise {
        io.readAddr.valid := Bool(true)
        io.readAddr.bits.addr := regDVPtr
        io.readAddr.bits.id := UInt(dvReqID)
        
        when ( io.readAddr.ready ) {
          regDVCount := regDVCount - UInt(dvPerBurst)
          regDVPtr := regDVPtr + UInt(8)  // TODO make parametrizable
          regState := sCheckFinished
        }
      }    
    }
    
    is ( sCheckFinished ) {
      when ( allFinished ) {
        // if all requests issued, go back to idle
        regState := sIdle
      } .otherwise {
        // not all requests are finished
        // keep cycling
        regState := sReqColLen
      }
    }
  }
}

// TODO add test code for the address generator here
