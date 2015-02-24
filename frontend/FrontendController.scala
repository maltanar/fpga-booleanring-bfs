package BFSFrontEnd

import Chisel._
import Literal._
import Node._
import AXIStreamDefs._

class FrontendController(memDepthWords: Int) extends Module {
  // TODO get these from global config
  val addrBits = log2Up(memDepthWords*32)

  val io = new Bundle {

    // control interface
    val start = Bool(INPUT)
    val colCount = UInt(INPUT, 32)

    // status interface
    val state = UInt(OUTPUT, 32)
    val processedColCount = UInt(OUTPUT, 32)
    val processedNZCount = UInt(OUTPUT, 32)

    // SpMV data inputs
    val colLengths = new AXIStreamSlaveIF(UInt(width = 32))
    val rowIndices = new AXIStreamSlaveIF(UInt(width = 32))
    val dvValues = new AXIStreamSlaveIF(UInt(width = 1))

    // interface towards result vector memory
    val resMemPort = new MemReadWritePort(1, addrBits).flip
  }

  // rename AXI stream interfaces to support Vivado type inference
  io.colLengths.renameSignals("colLengths")
  io.rowIndices.renameSignals("rowIndices")
  io.dvValues.renameSignals("dvValues")

  // internal status registers
  // number of columns in SpM (during execution, num of
  // columns left to process)
  val regColCount = Reg(init = UInt(0, 32))
  // current dense vector element
  val regDenseVec = Reg(init = UInt(0, 1))
  // elements left in current column
  val regCurrentColLen = Reg(init = UInt(0, 32))
  // total NZs processed so far
  val regProcessedNZCount = Reg(init = UInt(0, 32))

  // state machine definitions
  val sIdle :: sReadColLen :: sProcessColumn :: sFinished :: Nil = Enum(UInt(), 4)
  val regState = Reg(init = UInt(sIdle))

  // default outputs
  // input queues
  io.colLengths.ready := Bool(false)
  io.rowIndices.ready := Bool(false)
  io.dvValues.ready := Bool(false)

  // result vector memory port
  io.resMemPort.addr := io.rowIndices.bits
  io.resMemPort.writeEn := Bool(false)
  io.resMemPort.dataIn := UInt(1)

  // status outputs
  io.state := regState
  io.processedColCount := io.colCount - regColCount
  io.processedNZCount := regProcessedNZCount

  // FSM for control
  switch ( regState ) {
    is ( sIdle ) {
      when ( io.start ) {
        // zero out registers
        regCurrentColLen := UInt(0)
        regProcessedNZCount := UInt(0)
        regDenseVec := UInt(0)
        // request column length next cycle
        regState := sReadColLen
        // save colCount from input
        regColCount := io.colCount
      }
    }

    is ( sReadColLen ) {
      // read in new column length from colLengths
      val endOfMatrix = (regColCount === UInt(0))

      // when no more columns to process, go to sFinished
      when ( endOfMatrix ) { regState := sFinished }
      // otherwise, wait for column length and dense vector data
      .elsewhen ( io.colLengths.valid && io.dvValues.valid ) {
        // note that FIFOs are necessary to avoid ready-valid loop here
        io.colLengths.ready := Bool(true)
        io.dvValues.ready := Bool(true)
        // register column length and dense vector values
        regCurrentColLen := io.colLengths.bits
        regDenseVec := io.dvValues.bits
        // start processing
        regState := sProcessColumn
        // one less column to go
        regColCount := regColCount - UInt(1)
      }
    }

    is ( sProcessColumn ) {
      // read in new column indices + process
      val endOfColumn = ( regCurrentColLen === UInt(0) )
      // ready to process the next row index
      io.rowIndices.ready := !endOfColumn

      when ( endOfColumn )
      {
        // read in a new column length
        regState := sReadColLen
      }
      .elsewhen ( io.rowIndices.valid ) {
        // this is the heart of the SpMV operation for BFS:
        // y[i] = x[j] | y[i]
        // - i is provided by the rowIndices FIFO
        // - x[j] is latched in at the same time as column length
        // instead of computing a new result every time,
        // we can use x[j] as write enable for writing a constant 1
        io.resMemPort.writeEn := regDenseVec
        // decrement elements left in current col
        regCurrentColLen := regCurrentColLen - UInt(1)
        // increment NZ counter
        regProcessedNZCount := regProcessedNZCount + UInt(1)
      }
    }

    is ( sFinished ) {
      when ( !io.start ) { regState := sIdle }
    }

  }
}
