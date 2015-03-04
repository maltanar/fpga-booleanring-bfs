package BFSFrontEnd

import Chisel._
import Literal._
import Node._
import AXIStreamDefs._

class ResultDumper(memDepthWords: Int) extends Module {
  // TODO get these from global config
  val addrBits = log2Up(memDepthWords*32)
  val bramStages = 3
  val fifoCapacity = 16
  val bramAddressShift = UInt(5)

  val io = new Bundle {
    // control/status interface
    val start = Bool(INPUT)
    val wordCount = UInt(INPUT, 16)
    val finished = Bool(OUTPUT)

    // BRAM read ports
    val readAddr1 = UInt(OUTPUT, addrBits)
    val readAddr2 = UInt(OUTPUT, addrBits)
    val readData1 = UInt(INPUT, 32)
    val readData2 = UInt(INPUT, 32)

    // data output
    val resultVector = new AXIStreamMasterIF(UInt(width = 64))
    val fifoDataCount = UInt(INPUT, 32)
  }
  io.resultVector.renameSignals("resultVector")

  // TODO use instead "programmable full" threshold on Xilinx FIFOs
  // the 2x here is probably overly cautious, but better safe than sorry
  // (since we don't wait before all responses are committed before checking room)
  val hasRoom = (io.fifoDataCount < UInt((fifoCapacity-2*bramStages-1)))

  // keep track of # words left before result dump is finished
  val regWordsLeft = Reg(init=UInt(0,32))
  // read address register for the BRAM
  val regReadAddr = Reg(init=UInt(0,addrBits))

  // shift register to supply "valid" signal
  // TODO use Chisel Pipe to create this shift register
  // TODO the number of these depends on bramStages
  val regValid1 = Reg(init=Bool(false)) // input of valid shift register
  val regValid2 = Reg(init=Bool(false), next=regValid1)
  val regValid3 = Reg(init=Bool(false), next=regValid2)

  val regReqCount = Reg(init=UInt(0,4))

  // default outputs
  io.resultVector.bits := Cat(io.readData2, io.readData1)
  io.resultVector.valid := regValid3
  // asymmetric r/w width in BRAM: need to shift address while reading
  // for our case, since the read port is 32 bits wide and write is 1 bit wide
  io.readAddr1 := (regReadAddr << bramAddressShift)
  io.readAddr2 := ((regReadAddr + UInt(1)) << bramAddressShift)
  io.finished := Bool(false)

  val sIdle :: sWaitFIFOHasRoom :: sReq :: sFinished :: Nil = Enum(UInt(), 4)
  val regState = Reg(init=UInt(sIdle))

  // default assignment to valid shiftreg
  regValid1 := Bool(false)

  switch(regState) {
      is(sIdle) {
        regReadAddr := UInt(0)
        regReqCount := UInt(0)
        regWordsLeft := io.wordCount

        when (io.start) {
          regState := sWaitFIFOHasRoom
        }
      }

      is(sWaitFIFOHasRoom) {
        when ( regWordsLeft === UInt(0) ) {
          // no words left in BRAM, we are finished
          regState := sFinished
        }
        // we only issue requests to BRAM if the FIFO can hold
        // responses from all (bramStages) requests
        .elsewhen (hasRoom) {
          // calculate the next burst length:
          // we might have less than a full burst's worth of words left in BRAM
          val canDoFullReq = (regWordsLeft > UInt(bramStages))
          regReqCount := Mux(canDoFullReq, UInt(bramStages), regWordsLeft)
          // start burst
          regState := sReq
        }
      }

      is (sReq) {
        when ( regReqCount === UInt(0) ) {
          // no more requests in burst, wait for more room
          regState := sWaitFIFOHasRoom
        } .otherwise {
          // issue requests (one burst beat)
          regValid1 := Bool(true)
          regReqCount := regReqCount - UInt(1)
          // each burst beat is two BRAM word (dual-port)
          regReadAddr := regReadAddr + UInt(2)
          // the words we count on the interface are 8-byte words
          regWordsLeft := regWordsLeft - UInt(1)
          // stay in this state
        }
      }

      is (sFinished) {
        io.finished := Bool(true)
        // wait until !start to go back to idle
        when ( !io.start ) {
          regState := sIdle
        }
      }
  }
}
