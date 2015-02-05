package BFSFrontEnd

import Chisel._
import Literal._
import Node._
import AXIStreamDefs._

class LevelGenerator(dataWidthBits: Int) extends Module {
  val io = new Bundle {
    // control interface
    val start = Bool(INPUT)
    val bitCount = UInt(INPUT, 32)
    val basePointer = UInt(INPUT, 32)

    // status interface
    val state = UInt(OUTPUT, 32)

    // data stream inputs
    val oldData = new AXIStreamSlaveIF(UInt(width = dataWidthBits))
    val newData = new AXIStreamSlaveIF(UInt(width = dataWidthBits))

    // address stream output
    val writeAddrs = new AXIStreamMasterIF(UInt(width = 32))
  }

  // internal registers to keep config and state
  val regBitCount = Reg(init = UInt(0, 32))
  val regPointer = Reg(init = UInt(0, 32))
  val regShiftCounter = Reg(init = UInt(0, 32))


  // registers for the incoming data streams
  val regOldData = Reg(init = UInt(0,dataWidthBits))
  val regNewData = Reg(init = UInt(0,dataWidthBits))

  // finite state machine
  val sIdle :: sWaitOld :: sWaitNew :: sRun :: sFinished :: Nil = Enum(UInt(), 5)
  val regState = Reg(init = UInt(sIdle))

  // default outputs
  io.state := regState
  io.writeAddrs.bits := regPointer
  io.writeAddrs.valid := Bool(false)
  io.oldData.ready := Bool(false)
  io.newData.ready := Bool(false)

  switch(regState) {
      is(sIdle) {
        // set config registers from inputs
        regBitCount := io.bitCount
        regPointer := io.basePointer

        when(io.start) {
          regState := sWaitOld
        }
      }

      is(sWaitOld) {
        io.oldData.ready := Bool(true)

        when(io.oldData.valid) {
          regOldData := io.oldData.bits
          regState := sWaitNew
        }
      }

      is(sWaitNew) {
        io.newData.ready := Bool(true)

        when(io.newData.valid) {
          regShiftCounter := UInt(dataWidthBits)
          regNewData := io.newData.bits
          regState := sRun
        }
      }

      is(sRun) {
        when(regBitCount === UInt(0)) {
          // end of the entire level gen operation
          regState := sFinished
        } .elsewhen(regShiftCounter === UInt(0)) {
          // end of word reached, get new words
          regState := sWaitOld
        } .otherwise {
          // core level generation logic:
          // when the bit in the same position in old data is 0 and
          // new data is 1, we create a write request for that position
          val genWriteRequest = !regOldData(0) && regNewData(0)
          io.writeAddrs.valid := genWriteRequest

          when(io.writeAddrs.ready || !genWriteRequest) {
            regOldData  := regOldData >> UInt(1)
            regNewData  := regNewData >> UInt(1)
            regBitCount := regBitCount - UInt(1)
            regShiftCounter := regShiftCounter - UInt(1)
            regPointer := regPointer + UInt(4)
          }
        }
      }

      is(sFinished) {
        // wait for !start to go back to idle
        when(!io.start) { regState := sIdle}
      }
  }
}
