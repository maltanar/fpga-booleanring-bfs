package BFSBackend

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

    // AXI MM outputs
    val writeAddrOut   = Decoupled(new AXIAddress(addrBits,idBits))
    val writeDataOut   = Decoupled(new AXIWriteData(addrBits))
    val writeRespIn   = Decoupled(new AXIWriteResponse(idBits)).flip
  }

  val regDistVecUpdateCount = Reg(init=UInt(0,32))
  val regDistVecBase = Reg(init=UInt(0,32))
  val regDistVecUpdateAddr = Reg(init=UInt(0,32))
  val regCurrentLevel = Reg(init=UInt(0,32))

  val sIdle :: sFetch :: sReq :: Nil = Enum(UInt(), 3)
  val regState = Reg(init=UInt(sIdle))

  // default outputs
  // state outputs
  io.distVecUpdateCount := regDistVecUpdateCount
  // write data in and response in channels
  io.distVecInds.ready := Bool(false)
  io.writeRespIn.ready := (regState != sIdle)
  // write address channel
  io.writeAddrOut.valid := Bool(false)
  io.writeAddrOut.bits.addr := regDistVecUpdateAddr

  io.writeAddrOut.bits.id := UInt(0)  // no multiple transactions
  io.writeAddrOut.bits.len := UInt(0) // len 0 is single burst beat
  io.writeAddrOut.bits.prot := UInt(0)
  io.writeAddrOut.bits.qos := UInt(0)
  io.writeAddrOut.bits.lock := Bool(false)
  io.writeAddrOut.bits.cache := UInt("b0010") // no alloc, modifiable, no buffer
  io.writeAddrOut.bits.size := UInt(log2Up((32/8)-1)) // full data width
  io.writeAddrOut.bits.burst := UInt(1) // incrementing burst

  // write data channel
  io.writeDataOut.valid := (regState != sIdle)
  io.writeDataOut.bits.data := regCurrentLevel
  io.writeDataOut.bits.strb := UInt("b1111")  // all bytelanes valid
  io.writeDataOut.bits.last := Bool(true)  // single beat burst - always "last" beat

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
          regDistVecUpdateCount := regDistVecUpdateCount + UInt(1)
          regState := sFetch
        }
      }
  }


}
