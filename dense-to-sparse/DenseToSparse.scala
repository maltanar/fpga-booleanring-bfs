package DenseToSparse

import Chisel._
import AXIDefs._
import AXIStreamDefs._

class DenseToSparse() extends Module {
  val io = new Bundle {
    // control + status
    val denseBasePtr = UInt(INPUT, 32)
    val sparseBasePtr = UInt(INPUT, 32)
    val denseCount = UInt(INPUT, 32)
    val lookFor = UInt(INPUT, 32)
    val sparseCount = UInt(OUTPUT, 32)
    val start = Bool(INPUT)
    val finished = Bool(OUTPUT)

    val aximm32 = new AXIMasterIF(32, 32, 2)
  }

  io.aximm32.renameSignals("aximm32")

  val frontierFilter = Module(new FrontierFilter())
  frontierFilter.io.currentLevel <> io.lookFor
  frontierFilter.io.start <> io.start
  frontierFilter.io.distVecCount <> io.denseCount
  frontierFilter.io.frontierSize <> io.sparseCount

  val fifoSize = 32
  val fifoThreshold = fifoSize/4
  val sparseQueue = Module(new Queue(UInt(width=32), entries=fifoSize))
  val denseQueue = Module(new Queue(UInt(width=32), entries=fifoSize))
  denseQueue.io.deq <> frontierFilter.io.distVecIn
  sparseQueue.io.enq <> frontierFilter.io.frontierOut

  io.aximm32.readData.bits.data <> denseQueue.io.enq.bits
  io.aximm32.readData.valid <> denseQueue.io.enq.valid
  io.aximm32.readData.ready <> denseQueue.io.enq.ready

  io.aximm32.writeData.bits.data <> sparseQueue.io.deq.bits
  io.aximm32.writeData.valid <> sparseQueue.io.deq.valid
  io.aximm32.writeData.ready <> sparseQueue.io.deq.ready


  val sIdle :: sRead :: sWrite :: sFinished :: Nil = Enum(UInt(), 4)
  val regState = Reg(init = UInt(sIdle))
  val regReadReqsLeft = Reg(init = UInt(0, 32))
  val regReadReqPtr = Reg(init = UInt(0, 32))
  val regWriteReqPtr = Reg(init = UInt(0, 32))

  io.finished := Bool(false)
  io.aximm32.readAddr.valid := Bool(false)
  io.aximm32.writeAddr.valid := Bool(false)
  io.aximm32.writeResp.ready := !(regState === sIdle)

  io.aximm32.readAddr.bits.addr := regReadReqPtr
  io.aximm32.readAddr.bits.size := UInt(log2Up(32/8)-1)
  io.aximm32.readAddr.bits.len := UInt(0)
  io.aximm32.readAddr.bits.burst := UInt(0)
  io.aximm32.readAddr.bits.id := UInt(0)
  io.aximm32.readAddr.bits.lock := Bool(false)
  io.aximm32.readAddr.bits.cache := UInt("b0010")
  io.aximm32.readAddr.bits.prot := UInt(0)
  io.aximm32.readAddr.bits.qos := UInt(0)

  io.aximm32.writeAddr.bits.addr := regWriteReqPtr
  io.aximm32.writeAddr.bits.size := UInt(log2Up(32/8)-1)
  io.aximm32.writeAddr.bits.len := UInt(0)
  io.aximm32.writeAddr.bits.burst := UInt(0)
  io.aximm32.writeAddr.bits.id := UInt(0)
  io.aximm32.writeAddr.bits.lock := Bool(false)
  io.aximm32.writeAddr.bits.cache := UInt("b0010")
  io.aximm32.writeAddr.bits.prot := UInt(0)
  io.aximm32.writeAddr.bits.qos := UInt(0)

  io.aximm32.writeData.bits.last := Bool(true)
  io.aximm32.writeData.bits.strb := UInt("b1111")

  switch(regState) {
      is(sIdle) {
        when(io.start) {
          regReadReqsLeft := io.denseCount
          regReadReqPtr := io.denseBasePtr
          regWriteReqPtr := io.sparseBasePtr
          regState := sRead
        }
      }

      is(sRead) {
        val readReqsFinished = (regReadReqsLeft === UInt(0))
        val canIssueRead = (denseQueue.io.count < UInt(fifoThreshold))

        when(readReqsFinished) { regState := sWrite}
        .elsewhen(!canIssueRead) { regState := sWrite }
        .otherwise {
          // issue read request
          val burstLen = Mux(regReadReqsLeft < UInt(8), UInt(1), UInt(8))
          // the -1 here is defined by the protocol
          io.aximm32.readAddr.bits.burst := burstLen - UInt(1)
          io.aximm32.readAddr.valid := Bool(true)

          when(io.aximm32.readAddr.ready) {
            regState := sWrite
            regReadReqsLeft := regReadReqsLeft - burstLen
            regReadReqPtr := regReadReqPtr + UInt(4) * burstLen
          }
        }
      }

      is(sWrite) {
        val writeIndsEmpty = (sparseQueue.io.count === UInt(0))
        val filterFinished = (frontierFilter.io.finished)
        when(writeIndsEmpty && filterFinished) { regState := sFinished}
        .elsewhen(!writeIndsEmpty) {
          io.aximm32.writeAddr.valid := Bool(true)

          when(io.aximm32.writeAddr.ready) {
            regWriteReqPtr := regWriteReqPtr + UInt(4)
            regState := sRead
          }
        }
      }

      is(sFinished) {
        io.finished := Bool(true)

        when(!io.start) { regState := sIdle}
      }


  }
}
