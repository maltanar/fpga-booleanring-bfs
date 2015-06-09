package BFSSparseFrontier

import Chisel._
import AXIDefs._
import AXIStreamDefs._

class SparseFrontierFrontend(memDepthWords: Int) extends Module {
  // TODO get these from global config
  val addrBits = log2Up(memDepthWords*32)

  val io = new Bundle {

    // control+status interface
    val ctrl = UInt(INPUT, 32)
    val state = UInt(OUTPUT, 32)
    val rowCount = UInt(INPUT, 32)
    val frontierSize = UInt(OUTPUT, 32)
    val expectedFrontierSize = UInt(INPUT, 32)
    val processedNZCount = UInt(OUTPUT, 32)

    // input from backend
    val rowIndData = new AXIStreamSlaveIF(UInt(width = 64))
    val rowIndMetadata  = new AXIStreamSlaveIF(UInt(width = 32))

    // interface towards result vector memory
    val resMemPort1 = new AsymMemReadWritePort(1, 32, addrBits)
    val resMemPort2 = new AsymMemReadWritePort(1, 32, addrBits)

    // output for dumping the result vector
    val resultVectorOut = new AXIStreamMasterIF(UInt(width = 64))
  }
  // rename interfaces for Vivado
  io.rowIndData.renameSignals("rowIndData")
  io.rowIndMetadata.renameSignals("rowIndMetadata")
  io.resultVectorOut.renameSignals("resultVectorOut")

  // break out control bits
  val enableBRAMReset = io.ctrl(2)
  val enableBRAMDump = io.ctrl(1)
  val startAccel = io.ctrl(0)

  val regResetAddr = Reg(init=UInt(0,addrBits))
  val regNZCount = Reg(init=UInt(0,32))
  val regRowCount = Reg(init=UInt(0,32))
  val regFrontierSize = Reg(init=UInt(0,32))

  val regRowIndsLeftInCol = Reg(init=UInt(0,31))
  val regAligned = Reg(init=UInt(0))


  val sIdle :: sResetAll :: sDump :: sFetchMeta :: sProcessInds :: sFinished :: Nil = Enum(UInt(), 6)
  val regState = Reg(init=UInt(sIdle))

  // instantiate the ResultDumper
  val resDump = Module(new ResultDumper(memDepthWords))
  // start will be set by FSM when it's time
  val regStartDump = Reg(init=Bool(false))
  resDump.io.start := regStartDump
  resDump.io.readData1 := io.resMemPort1.dataRead
  resDump.io.readData2 := io.resMemPort2.dataRead
  io.resultVectorOut <> resDump.io.resultVectorOut
  // resDump input is in terms of 64-bit words -- divide by 64,
  // equivalent to right shifting 6 places
  resDump.io.wordCount := regRowCount(21,6)

  // default outputs
  io.state := regState
  io.processedNZCount := regNZCount
  io.rowIndData.ready := Bool(false)
  io.rowIndMetadata.ready := Bool(false)
  io.frontierSize := regFrontierSize

  // result vector memory ports
  // port 1 uses the lower rowInd
  // port 2 uses the upper rowInd
  val rowIndUpper = io.rowIndData.bits(63, 32)
  val rowIndLower = io.rowIndData.bits(31, 0)
  // multiplex address to result BRAM depending on value of result dump register
  io.resMemPort1.addr := Mux(regStartDump, resDump.io.readAddr1, rowIndLower)
  io.resMemPort1.writeEn := Bool(false)
  io.resMemPort1.dataWrite := UInt(0)
  io.resMemPort2.addr := Mux(regStartDump, resDump.io.readAddr2, rowIndUpper)
  io.resMemPort2.writeEn := Bool(false)
  io.resMemPort2.dataWrite := UInt(0)

  switch(regState) {
      is(sIdle) {
        regResetAddr := UInt(0)
        regRowCount := io.rowCount
        regStartDump := Bool(false)

        when(startAccel) {
          // BRAM reset and dump operations take priority
          when(enableBRAMReset) {
            regState := sResetAll
          } .elsewhen(enableBRAMDump) {
            regState := sDump
            regStartDump := Bool(true)
          } .otherwise {
            regNZCount := UInt(0)
            regFrontierSize := UInt(0)
            regState := sFetchMeta
          }
        }
      }

      is(sResetAll) {
        // write zeroes to all BRAM locations (up to rowCount)
        when(regResetAddr >= regRowCount-UInt(1)) { regState := sFinished}
        .otherwise {
          // default write data is 0, no need to set that
          // override write addresses
          io.resMemPort1.addr := regResetAddr
          io.resMemPort2.addr := regResetAddr + UInt(1)
          io.resMemPort1.writeEn := Bool(true)
          io.resMemPort2.writeEn := Bool(true)
          regResetAddr := regResetAddr + UInt(2)
        }
      }

      is(sDump) {
        // wait until ResultDumper completes
        when(resDump.io.finished) {
          regState := sFinished
          regStartDump := Bool(false)
        }
      }

      is(sFetchMeta) {
        when(regFrontierSize === io.expectedFrontierSize) { regState := sFinished}
        .otherwise {
          // wait until new metadata is fetched
          io.rowIndMetadata.ready := Bool(true)
          regAligned := io.rowIndMetadata.bits(31)
          regRowIndsLeftInCol := io.rowIndMetadata.bits(30, 0)

          when(io.rowIndMetadata.valid) {
            regFrontierSize := regFrontierSize + UInt(1)
            regState := sProcessInds
          }
        }
      }

      is(sProcessInds) {
        val singleElementLeft = (regRowIndsLeftInCol === UInt(1))
        val noElementsLeft = (regRowIndsLeftInCol === UInt(0))
        // only write 1s in this state
        io.resMemPort1.dataWrite := UInt(1)
        io.resMemPort2.dataWrite := UInt(1)
        // addresses are already assigned by default
        // write enables are dependent on state:
        when(noElementsLeft) { regState := sFetchMeta}
        .otherwise {
          io.rowIndData.ready := Bool(true)

          when(io.rowIndData.valid) {
            when(regAligned === UInt(0)) {
              // unaligned location: process only upper word
              io.resMemPort2.writeEn := Bool(true)
              // will be aligned after this
              regAligned := UInt(1)
              // 1 less rowInd to go
              regRowIndsLeftInCol := regRowIndsLeftInCol - UInt(1)
              regNZCount := regNZCount + UInt(1)
            } .otherwise {
              // aligned location, always process lower word
              io.resMemPort1.writeEn := Bool(true)
              // upper word and elements processed depends on whether there was
              // only 1 element left in this column:
              when(singleElementLeft) {
                // upper invalid (default is false anyway, no need to change)
                // only 1 element
                regRowIndsLeftInCol := regRowIndsLeftInCol - UInt(1)
                regNZCount := regNZCount + UInt(1)
                regAligned := UInt(0)
              } .otherwise {
                // both rowinds valid
                io.resMemPort2.writeEn := Bool(true)
                regRowIndsLeftInCol := regRowIndsLeftInCol - UInt(2)
                regNZCount := regNZCount + UInt(2)
              }
            }
          }
        }
      }

      is(sFinished) {
        // go back to idle when !start
        when(!startAccel) {regState := sIdle}
      }
  }
}
