package BFSBackend

import Chisel._
import Literal._
import Node._
import AXIStreamDefs._
import AXILiteDefs._
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

    // AXI lite MM outputs
    val writeAddrOut   = Decoupled(new AXILiteAddress(addrBits))
    val writeDataOut   = Decoupled(new AXILiteWriteData(addrBits))
    val writeRespIn   = Decoupled(UInt(width = 2)).flip
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
  io.writeAddrOut.bits.prot := UInt(0)

  // write data channel
  io.writeDataOut.valid := (regState != sIdle)
  io.writeDataOut.bits.data := regCurrentLevel
  io.writeDataOut.bits.strb := UInt("b1111")  // all bytelanes valid

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
