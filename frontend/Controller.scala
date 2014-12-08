package BFSFrontEnd

import Chisel._
import Literal._
import Node._

class FrontendController() extends Module {
  // TODO get these from global config
  val memDepthWords = 1024
  val addrBitsA = log2Up(memDepthWords)
  val addrBitsB = log2Up(memDepthWords*32)
  
  val io = new Bundle {
  
    // control and status interface
    val state = UInt(OUTPUT, 32)
    val start = Bool(INPUT)
    val memFill = Bool(INPUT)
    val memDump = Bool(INPUT)
    val colCount = UInt(INPUT, 32)
    
    // SpMV data inputs
    val colLengths = Decoupled(UInt(width = 32)).flip
    val rowIndices = Decoupled(UInt(width = 32)).flip
    
    // i/o for intializing vector mem contents
    val vectorMemDataIn = Decoupled(UInt(width = 32)).flip
    val vectorMemDataOut = Decoupled(UInt(width = 32))
    
    // interface towards vector memory
    val portA = new MemReadWritePort(32, addrBitsA).flip
    val portB = new MemReadWritePort(1, addrBitsB).flip    
  }
  
  // internal state registers
  // number of columns in SpM (during execution, num of
  // columns left to process)
  val regColCount = Reg(init = UInt(0, 32))
  // elements left in current column
  val regCurrentColLen = Reg(init = UInt(0, 32))
  
  // current X (input) vector index:
  val regXIndex = Reg(init = UInt(0, addrBitsB))
  // - upper bits act as portA read address
  val xReadAddr = regXIndex(addrBitsB-1, 5)
  // - lower bits are used as input to a decoder that selects the
  //   appropriate bit from the 32-bit word
  // TODO if we always treat X as dense, consider shifting instead
  val xBitSelect = regXIndex(4, 0)
 
  val currentXWord = io.portA.dataOut
  val currentXValue = currentXWord(xBitSelect)
  
  // default outputs
  // input queues
  io.colLengths.ready := Bool(false)
  io.rowIndices.ready := Bool(false)
  
  // memory port A
  io.portA.addr := xReadAddr
  io.portA.writeEn := Bool(false)
  io.portA.dataIn := io.vectorMemDataIn.bits
  
  // memory port B
  io.portB.addr := io.rowIndices.bits
  io.portB.writeEn := Bool(false)
  io.portB.dataIn := UInt(1)
  
  // mem fill/dump queues
  io.vectorMemDataIn.ready := Bool(false)
  io.vectorMemDataOut.bits := currentXWord
  io.vectorMemDataOut.valid := Bool(false)
  
  // state machine definitions
  val sIdle :: sMemFill :: sMemDumpWait :: sMemDumpLoad :: sReadColLen :: sProcessColumn :: Nil = Enum(UInt(), 6)
  val regState = Reg(init = UInt(sIdle))
  
  io.state := regState
  
  switch ( regState ) {
    is ( sIdle ) {
      // save colCount from input
      regColCount := io.colCount
      // zero out other register values
      regCurrentColLen := UInt(0)
      regXIndex := UInt(0)
      
      when ( io.start )
      {
        when ( io.memDump ) { regState := sMemDumpWait }
        .elsewhen ( io.memFill ) { regState := sMemFill}
        .otherwise { regState := sReadColLen}
      }
    }
    
    is ( sMemFill ) {
      // init contents of vector storage from vectorMemDataIn
      io.portA.writeEn := io.vectorMemDataIn.valid
      io.vectorMemDataIn.ready := Bool(true)
      
      when ( io.vectorMemDataIn.valid ) {
        // increment address with each valid word
        // add 32 since 1 word = 32 bits 
        // (word address is derived from upper bits of regXIndex)
        regXIndex := regXIndex + UInt(32)
        // go back to idle when we have filled the whole memory
        when ( xReadAddr === UInt(memDepthWords-1) ) { regState := sIdle}
      }
    }
    
    is ( sMemDumpWait ) {
      // dump contents of vector storage onto vectorMemDataOut
      // data already loaded from BRAM, set valid high
      io.vectorMemDataOut.valid := Bool(true)
      
      when ( io.vectorMemDataOut.ready ) {
        regState := sMemDumpLoad
        // increment address and load next word for mem dump
        // add 32 since 1 word = 32 bits 
        regXIndex := regXIndex + UInt(32)
        when ( xReadAddr === UInt(memDepthWords-1) ) { regState := sIdle }
      }
    }
    
    is ( sMemDumpLoad ) {
      // dummy state to delay the valid generation after receiving
      // ready
      regState := sMemDumpWait
    }
    
    is ( sReadColLen ) {
      // read in new column length from colLengths
      // TODO assert this depending on regColCount === 0,
      // otherwise we consume one element too many
      io.colLengths.ready := Bool(true)
      
      // when no more columns to process, go back to idle
      when ( regColCount === UInt(0) ) { regState := sIdle }
      // otherwise, wait for column length data from input queue
      .elsewhen ( io.colLengths.valid ) {
        // got column length, 
        regCurrentColLen := io.colLengths.bits
        regState := sProcessColumn
        regColCount := regColCount - UInt(1)
      }
    }
    
    is ( sProcessColumn ) {
      // read in new column indices + process
      io.rowIndices.ready := Bool(true)
      
      // detect end-of-column
      when ( regCurrentColLen === UInt(0) )
      {
        // end of column -- also corresponds to new x index
        regXIndex := regXIndex + UInt(1)
        // read in a new column length
        regState := sReadColLen
      }
      .elsewhen ( io.rowIndices.valid ) {
        // this is the heart of the SpMV operation for BFS:
        // y[i] = x[j] | y[i]
        // - i is provided by the rowIndices FIFO
        // - j is generated by regXIndex
        // instead of computing a new result every time,
        // we can use x[j] as write enable for writing a constant 1
        io.portB.writeEn := currentXValue
        
        // decrement elements left in current col
        regCurrentColLen := regCurrentColLen - UInt(1)
        // TODO maybe move sReadColLen transition here?
        // if not we'll stay in the same state and pop
        // one element too many due to ready=true
        
      }
    }
  }
}
