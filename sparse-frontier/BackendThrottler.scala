package BFSSparseFrontier

import Chisel._
import AXIDefs._
import AXIStreamDefs._

// a unit to throttle the request counts to come into a FIFO, so that the
// FIFO does not fill up and clog the system
// TODO parametrize and use generators - should be generalizable

class BackendThrottler() extends Module {
  val io = new Bundle {
    // the throttler needs to know the FIFO size to calculate whether
    // requests should be allowed
    val fifoSize = UInt(INPUT, 32)
    val fifoDataCount = UInt(INPUT, 32)
    // we use thread ID's to associate request/responses with originators
    // each TID is internally mapped to a fixed request size
    val addRequest = Valid(UInt(INPUT, 1)).flip
    val addResponse = Valid(UInt(INPUT, 1)).flip
    // output signal channels to requesters
    val canProceedT0 = Bool(OUTPUT)
    val canProceedT1 = Bool(OUTPUT)
  }

  io.canProceedT1 := io.fifoDataCount < (io.fifoSize >> UInt(1))
  io.canProceedT0 := io.fifoDataCount < (io.fifoSize >> UInt(1))
  /*

  val sIdle :: sRun :: Nil = Enum(UInt(), 2)
  val regState = Reg(init = UInt(sIdle))

  // number of elements in outstanding (yet unserved) requests
  val regOutstandingElements  = Reg(init = UInt(0, 32))
  val regFIFOSize = Reg(init = UInt(0, 32))
  val regFIFOElements = Reg(init = UInt(0, 32), next = io.fifoDataCount)
  val regTotalElements = Reg(init = UInt(0, 32))

  // TODO generalize this using a little constant memory
  val t0w = 8
  val t1w = 2
  val pessimism = 4

  // each entry here is the number of elements associated with that TID
  val sizeRequests = Mux(io.addRequest.bits === UInt(0), UInt(t0w), UInt(t1w))
  val sizeResponses = Mux(io.addResponse.bits === UInt(0), UInt(t0w), UInt(t1w))
  val deltaRequests = Mux(io.addRequest.valid, sizeRequests, UInt(0))
  val deltaResponses = Mux(io.addResponse.valid, sizeResponses, UInt(0))

  regOutstandingElements := regOutstandingElements+deltaRequests-deltaResponses
  regTotalElements := regFIFOElements + regOutstandingElements

  io.canProceedT0 := (regTotalElements < (regFIFOSize - UInt(pessimism*t0w)))
  io.canProceedT1 := (regTotalElements < (regFIFOSize - UInt(pessimism*t1w)))
  */
}
