package BFSFrontEnd

import Chisel._
import Literal._
import Node._
import AXIStreamDefs._

class FrontendControllerTurbo(memDepthWords: Int) extends Module {
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
    val rowIndices = new AXIStreamSlaveIF(UInt(width = 64))
    val dvValues = new AXIStreamSlaveIF(UInt(width = 1))

    // interface towards result vector memory
    val resMemPort1 = new AsymMemReadWritePort(1, 32, addrBits).flip
    val resMemPort2 = new AsymMemReadWritePort(1, 32, addrBits).flip
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
  val sIdle :: sReadColLen :: sProcessColumnUpper :: sProcessColumnBoth :: sFinished :: Nil = Enum(UInt(), 5)
  val regState = Reg(init = UInt(sIdle))

  // default outputs
  // input queues
  io.colLengths.ready := Bool(false)
  io.rowIndices.ready := Bool(false)
  io.dvValues.ready := Bool(false)

  // result vector memory ports
  // port 1 uses the lower rowInd
  io.resMemPort1.addr := io.rowIndices.bits(31, 0)
  io.resMemPort1.writeEn := Bool(false)
  io.resMemPort1.dataIn := UInt(1)
  // port 2 uses the upper rowInd
  io.resMemPort2.addr := io.rowIndices.bits(63, 32)
  io.resMemPort2.writeEn := Bool(false)
  io.resMemPort2.dataIn := UInt(1)

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
        // one less column to go
        regColCount := regColCount - UInt(1)
        // processing state depends on current NZ count
        when ( regProcessedNZCount(0) === UInt(0) ) {
          // even #NZs processed so far -- we can use both words
          regState := sProcessColumnBoth
        } .otherwise {
          // odd #NZs processed so far -- use upper word only
          regState := sProcessColumnUpper
        }


      }
    }

    is ( sProcessColumnUpper ) {
      // only use upper half of rowInd and port 2 write operation
      val endOfColumn = ( regCurrentColLen === UInt(0) )
      // ready to process the next row index unless end of column
      io.rowIndices.ready := !endOfColumn

      when ( endOfColumn ) {
        // read in a new column
        regState := sReadColLen
      }.elsewhen ( io.rowIndices.valid ) {
        io.resMemPort2.writeEn := regDenseVec
        // decrement elements left in current col
        regCurrentColLen := regCurrentColLen - UInt(1)
        // increment NZ counter by one
        regProcessedNZCount := regProcessedNZCount + UInt(1)

        // go directly to new column if this was the end of the col --
        // saves performance on very sparse graphs
        when ( regCurrentColLen === UInt(1) ) {
          regState := sReadColLen
        } .otherwise {
          //can operate on both upper and lower words for the next
          regState := sProcessColumnBoth
        }
      }
    }

    is ( sProcessColumnBoth ) {
      // can use both upper and lower words within the column boundary
      val endOfColumn = ( regCurrentColLen === UInt(0) )
      val canProcessBoth = ( regCurrentColLen >= UInt(2))

      // signal ready only if not end of column and we can process both
      // why the second condition? because if we have only one element left
      // and signal ready, we will lose the upper word, which belongs to
      // another column
      io.rowIndices.ready := !endOfColumn && canProcessBoth

      when ( endOfColumn )
      {
        // read in a new column
        regState := sReadColLen
      }
      .elsewhen ( io.rowIndices.valid ) {
        when ( canProcessBoth ) {
          // enable both ports
          io.resMemPort1.writeEn := regDenseVec
          io.resMemPort2.writeEn := regDenseVec
          // we've now processed 2 more elements
          regCurrentColLen := regCurrentColLen - UInt(2)
          // increment NZ counter
          regProcessedNZCount := regProcessedNZCount + UInt(2)
          // go directly to new column if this was the end of the col --
          // saves performance on very sparse graphs
          when ( regCurrentColLen === UInt(2) ) {
            regState := sReadColLen
          }
          // we can stay in the same state
        } .otherwise {
          // only one element remaining in column
          // use only lower port
          io.resMemPort1.writeEn := regDenseVec
          // processed only one element
          regCurrentColLen := regCurrentColLen - UInt(1)
          regProcessedNZCount := regProcessedNZCount + UInt(1)
          // end of this column, get a new one
          regState := sReadColLen
        }
      }
    }

    is ( sFinished ) {
      when ( !io.start ) { regState := sIdle }
    }

  }
}
