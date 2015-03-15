package BFSSparseFrontier

import Chisel._
import Literal._
import Node._
import AXIStreamDefs._

class DistVecToInpVec(outputWidthBits: Int) extends Module {
  val io = new Bundle {
    val distVecCount = UInt(INPUT, 32)
    val unvisitedValue = UInt(INPUT, 32)

    val start = Bool(INPUT)
    val finished = Bool(OUTPUT)

    val distVecInput = new AXIStreamSlaveIF(UInt(width = 32))
    val inpVecOutput = new AXIStreamMasterIF(UInt(width = outputWidthBits))
  }

  val regOutput = Reg(init = UInt(0, outputWidthBits))
  val regMask = Reg(init = UInt(1, outputWidthBits))
  val regOutBitCount = Reg(init = UInt(0, 32))
  val regDistVecElemsLeft = Reg(init = UInt(0, 32))

  val sIdle :: sPullInput :: sPushOutput :: sFinished :: Nil = Enum(UInt(), 4)
  val regState = Reg(init = UInt(sIdle))

  // default outputs
  io.finished := Bool(false)
  io.distVecInput.ready := Bool(false)
  io.inpVecOutput.valid := Bool(false)
  io.inpVecOutput.bits:= regOutput

  val isVisited = (io.distVecInput.bits != io.unvisitedValue)
  val inputFinished = (regDistVecElemsLeft === UInt(0))
  val readyToFlushOutput = (regOutBitCount === UInt(outputWidthBits))

  switch(regState) {
      is(sIdle) {
        regOutput := UInt(0)
        regOutBitCount := UInt(0)
        regMask := UInt(1)
        regDistVecElemsLeft := io.distVecCount
        when(io.start) {
          regState := sPullInput
        }
      }

      is(sPullInput) {
        when(inputFinished || readyToFlushOutput) {
            // always go through sPushOutput to ensure we flush all output
            // data -- distVecCount may not be divisable by outWidth
            regState := sPushOutput
        } .otherwise {
          io.distVecInput.ready := Bool(true)

          when(io.distVecInput.valid) {
            when(isVisited) {regOutput := regOutput | regMask}
            regDistVecElemsLeft := regDistVecElemsLeft - UInt(1)
            regOutBitCount := regOutBitCount + UInt(1)
            regMask := regMask << UInt(1)
          }
        }
      }

      is(sPushOutput) {
        io.inpVecOutput.valid := Bool(true)

        when(io.inpVecOutput.ready) {
          regOutBitCount := UInt(0)
          regOutput := UInt(0)
          regMask := UInt(1)
          regState := Mux(inputFinished, sFinished, sPullInput)
        }
      }

      is(sFinished) {
        io.finished := Bool(true)
        when(!io.start) {
          regState := sIdle
        }
      }
  }
}
