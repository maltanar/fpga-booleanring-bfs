package BFSSparseFrontier

import Chisel._
import Literal._
import Node._
import AXIStreamDefs._
import AXIDefs._
import Constants._

class DistVecUpdater() extends Module {
  val io = new Bundle {
    // control interface
    val start = Bool(INPUT)
    val distVecBase = UInt(INPUT, 32)
    val currentLevel = UInt(INPUT, 32)

    // status output
    val distVecUpdateCount = UInt(OUTPUT, 32)

    // address input for dist. vec. updates
    val distVecInds = new AXIStreamSlaveIF(UInt(width = addrBits))

    // AXI MM write channel outputs
    val writeAddrOut   = Decoupled(new AXIAddress(addrBits, idBits))
    val writeDataOut   = Decoupled(new AXIWriteData(addrBits))
    val writeRespIn   = Decoupled(new AXIWriteResponse(idBits)).flip
  }

  val regDistVecUpdateCount = Reg(init=UInt(0,32))
  val regDistVecBase = Reg(init=UInt(0,32))
  val regDistVecUpdateAddr = Reg(init=UInt(0,32))
  val regCurrentLevel = Reg(init=UInt(0,32))

  val sIdle :: sFetch :: sReq :: sSend :: sWaitResp :: Nil = Enum(UInt(), 5)
  val regState = Reg(init=UInt(sIdle))

  // default outputs
  // state outputs
  io.distVecUpdateCount := regDistVecUpdateCount
  // write data in and response in channels
  io.distVecInds.ready := Bool(false)
  io.writeRespIn.ready := Bool(false)
  // write address channel - the parts that change
  io.writeAddrOut.valid := Bool(false)
  io.writeAddrOut.bits.addr := regDistVecUpdateAddr
  // write address channel - the parts that do not change
  io.writeAddrOut.bits.prot := UInt(0)
  io.writeAddrOut.bits.len := UInt(0) // single beat write
  io.writeAddrOut.bits.id := UInt(0) // constant ID
  io.writeAddrOut.bits.qos := UInt(0)
  io.writeAddrOut.bits.lock := Bool(false)
  io.writeAddrOut.bits.cache := UInt("b0010")
  io.writeAddrOut.bits.size := UInt(log2Up((32/8)-1)) // full-datawidth
  io.writeAddrOut.bits.burst := UInt(1) // incrementing burst

  // write data channel
  io.writeDataOut.valid := Bool(false)
  io.writeDataOut.bits.data := regCurrentLevel
  io.writeDataOut.bits.strb := UInt("b1111")  // all bytelanes valid
  io.writeDataOut.bits.last := Bool(true) // always true for single beat

  switch(regState) {
      is(sIdle) {
        regDistVecBase := io.distVecBase
        regCurrentLevel := io.currentLevel
        when (io.start) {
          regDistVecUpdateCount := UInt(0)
          regState := sFetch
        }
      }

      is(sFetch) {
        // fetch data from input data queue
        io.distVecInds.ready := Bool(true)
        // calculate dv update addr from index
        regDistVecUpdateAddr := regDistVecBase + UInt(4) * io.distVecInds.bits

        when (!io.start) {
          regState := sIdle
        }
        .elsewhen (io.distVecInds.valid) {
          regState := sReq
        }
      }

      is(sReq) {
        // data ready, issue the write request
        io.writeAddrOut.valid := Bool(true)

        when (io.writeAddrOut.ready) {
          regState := sSend
        }
      }

      is(sSend) {
        // dispatch the data
        io.writeDataOut.valid := Bool(true)

        when (io.writeDataOut.ready) {
          regState := sWaitResp
        }
      }

      is(sWaitResp) {
        // wait for write complete response
        io.writeRespIn.ready := Bool(true)

        when (io.writeRespIn.valid) {
          // increment dv update count
          regDistVecUpdateCount := regDistVecUpdateCount + UInt(1)
          regState := sFetch
        }
      }
  }


}
