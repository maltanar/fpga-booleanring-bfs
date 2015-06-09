package BFSSparseFrontier

import Chisel._
import AXIDefs._
import AXIStreamDefs._


class BackendThrottler() extends Module {
  val io = new Bundle {
    val thresholdT0 = UInt(INPUT, 32)
    val dataCountT0 = UInt(INPUT, 32)

    val thresholdT1 = UInt(INPUT, 32)
    val dataCountT1 = UInt(INPUT, 32)

    // output signal channels to requesters
    val canProceedT0 = Bool(OUTPUT)
    val canProceedT1 = Bool(OUTPUT)
  }

  val regThresholdT0 = Reg(init=UInt(0,32), next=io.thresholdT0)
  val regThresholdT1 = Reg(init=UInt(0,32), next=io.thresholdT1)
  val regCountT0 = Reg(init=UInt(0,32), next=io.dataCountT0)
  val regCountT1 = Reg(init=UInt(0,32), next=io.dataCountT1)

  
  io.canProceedT1 := regCountT1 < regThresholdT1
  io.canProceedT0 := (regCountT0 < regThresholdT0) && io.canProceedT1
}
