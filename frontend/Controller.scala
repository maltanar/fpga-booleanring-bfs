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
    val start = Bool(INPUT)
    val memFill = Bool(INPUT)
    val memDump = Bool(INPUT)
    val nzCount = UInt(INPUT, 32)
    val colCount = UInt(INPUT, 32)
    
    // SpMV data inputs
    val colLengths = Decoupled(UInt(width = 32)).flip
    val rowIndices = Decoupled(UInt(width = 32)).flip
    
    // i/o for intializing contents
    val vectorMemDataIn = Decoupled(UInt(width = 32)).flip
    val vectorMemDataOut = Decoupled(UInt(width = 32))
    
    // interface towards vector state memory
    val portA = new MemReadWritePort(32, addrBitsA)
    val portB = new MemReadWritePort(1, addrBitsB)    
  }
  
  // internal state registers
  val regNZCount = Reg(init = UInt(0, 32))
  val regColCount = Reg(init = UInt(0, 32))
  val regMemInit = Reg(init = UInt(0, addrBitsA))
  
  val regCurrentColLen = Reg(init = UInt(0, 32))
  
  // current X (input) vector index
  val regXIndex = Reg(init = UInt(0, addrBitsB))
  // upper bits act as VectorStorage portA read address
  val xReadAddr = regXIndex(addrBitsB-1, 5)
  // lower bits are used as input to a decoder
  // TODO if we always treat X as dense, consider shifting instead
  val xBitSelect = regXIndex(4, 0)
 
  val currentXWord = io.portA.dataOut
  val currentXValue = currentXWord(xBitSelect)
  
  // default outputs
  // input queues
  io.colLengths.ready := Bool(false)
  io.rowIndices.ready := Bool(false)
  
  // memory port A -- connected to vectorMemDataIn
  io.portA.addr := regMemInit
  io.portA.writeEn := Bool(false)
  io.portA.dataIn := UInt(1)
  
  // memory port B
  io.portB.addr := io.rowIndices.bits
  io.portB.writeEn := Bool(false)
  io.portB.dataIn := currentXValue
  
  // mem fill/dump queues
  io.vectorMemDataIn.ready := Bool(false)
  io.vectorMemDataOut.bits := io.portA.dataOut
  io.vectorMemDataOut.valid := Bool(false)
  
  
  
  // state machine
  val sIdle :: sMemFill :: sMemDump :: sReadColLen :: sProcessColumn :: Nil = Enum(UInt(), 5)
  val regState = Reg(init = UInt(sIdle))
  
  switch ( regState ) {
    is ( sIdle ) {
      regNZCount := io.nzCount
      regColCount := io.colCount
      regMemInit := UInt(0)
      regXIndex := UInt(0)
      
      when ( io.start )
      {
        when ( io.memDump ) { state := sMemDump}
        .elsewhen ( io.memFill ) { state := sMemFill}
        .otherwise { state := sReadColLen}
      }
    }
    
    is ( sMemFill ) {
      // init contents of vector storage from vectorMemDataIn
      io.portA.writeEn := io.vectorMemDataIn.valid
      io.vectorMemDataIn.ready := Bool(true)
      
      when ( io.vectorMemDataIn.valid ) {
        // increment address with each valid word
        regMemInit := regMemInit + UInt(1)
        // go back to idle when we have filled the whole memory
        when ( regMemInit === UInt(memDepthWords-1) ) { state := sIdle}
      }
    }
    
    is ( sMemDump ) {
      // dump contents of vector storage onto vectorMemDataOut
      io.vectorMemDataOut.valid := Bool(true)
      
      when ( io.vectorMemDataOut.ready ) {
        // increment address with each accepted word
        regMemInit := regMemInit + UInt(1)
        // go back to idle when we have dumped the whole memory
        when ( regMemInit === UInt(memDepthWords-1) ) { state := sIdle}
      }
    }
    
    is ( sReadColLen ) {
      // read in new column length from colLengths
      io.colLengths.ready := Bool(true)
      
      // when no more columns to process, go back to idle
      when ( regColCount === UInt(0) ) { state := sIdle }
      // otherwise, wait for column length data from input queue
      .elsewhen ( io.colLengths.valid ) {
        // got column length, 
        regCurrentColLen := io.colLengths.bits
        regState := sProcessColumn
        regColCount := regColCount - UInt(1)
    }
    
    is ( sProcessColumn ) {
      // read in new column indices + process
      io.rowIndices.ready := Bool(true)
      // TODO check the functionality here
      
      // detect end-of-column
      when ( regCurrentColLen === UInt(0) )
      {
        // end of column -- also corresponds to new x index
        regXIndex := regXIndex + UInt(1)
        // read in a new column length
        regState := sReadColLen
      }
      .elsewhen ( io.rowIndices.valid ) {
        
        // decrement elements left in current col
        regCurrentColLen := regCurrentColLen - UInt(1)
        
      }
    }
  }
  
}
