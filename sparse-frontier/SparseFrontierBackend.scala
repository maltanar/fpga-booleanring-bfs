package BFSSparseFrontier

import Chisel._
import AXIDefs._
import AXIStreamDefs._

class SparseFrontierBackend() extends Module {
  val io = new Bundle {
    // graph data pointers
    val distVecBase = UInt(INPUT, 32)
    val distVecCount = UInt(INPUT, 32)
    val colPtrBase = UInt(INPUT, 32)
    val rowIndBase = UInt(INPUT, 32)
    // control and status
    val state = UInt(OUTPUT, 32)
    val start = UInt(INPUT, 1)

    // AXI MM interface - 32 bit addr, 64 bit data, 2 bits request id
    // for the rowind requests
    val aximm64 = new AXIMasterReadOnlyIF(32, 64, 2)
    // for smaller requests: distVec, colPtr
    val aximm32 = new AXIMasterReadOnlyIF(32, 32, 2)

    // decoupled channel to push out read data to AXI stream switch
    val readData32 = Decoupled(new AXIReadData(32, 2))

    // loopback from readData32: frontier indices after TID demux
    val frontierInds = new AXIStreamSlaveIF(UInt(width = 32))
    // loopback from readData32: row start/end pointers after TID demux
    val rowStartEnd = new AXIStreamSlaveIF(UInt(width = 32))
    // output to frontend: are the upper&lower rowind words valid?
    val rowIndsAndValid = Decoupled(UInt(width = 66))
  }

  // rename interfaces for Vivado IP integrator
  io.aximm64.renameSignals("aximm64")
  io.aximm32.renameSignals("aximm32")

  // break out read data channels
  io.readData32 <> io.aximm32.readData

  // instantiate rowind req generator and give channels to it:
  val neighborFetcher = Module(new NeighborFetcher())
  neighborFetcher.io.start <> io.start
  neighborFetcher.io.rowIndBase <> io.rowIndBase


  // io.aximm64, io.rowStartEnd, io.rowIndsAndValid, rowIndBase

  // registers for internal bookkeeping
  val regDistVecElemsLeft = Reg(init = UInt(0, 32))
  val regDistVecPtr = Reg(init = UInt(0, 32))
  val regColPtrBase = Reg(init = UInt(0, 32))
  val regRowIndBase = Reg(init = UInt(0, 32))
  val regFrontierIndex = Reg(init = UInt(0, 32))
  val regFrontierSize = Reg(init = UInt(0, 32))

  // FSM for control -- dist.vec and col.ptr requests
  val sIdle :: sReqDistVec :: sFetchIndex :: sReqColPtr :: sCheckFinished :: sFinished :: Nil = Enum(UInt(), 6)
  val regState = Reg(init = UInt(sIdle))

  // default outputs -- loopback 32-bit data channels
  io.frontierInds.ready := Bool(false)
  io.rowStartEnd.ready := Bool(false)

  // default outputs - 32-bit AXI channel
  io.aximm32.readAddr.valid := Bool(false)
  io.aximm32.readAddr.bits.addr := UInt(0)
  io.aximm32.readAddr.bits.len := UInt(0)
  io.aximm32.readAddr.bits.id := UInt(0)
  // the rest of the readAddr channel data is the same and not modified
  io.aximm32.readAddr.bits.prot := UInt(0)
  io.aximm32.readAddr.bits.qos := UInt(0)
  io.aximm32.readAddr.bits.lock := Bool(false)
  io.aximm32.readAddr.bits.cache := UInt("b0010") // no alloc, modifiable, no buffer
  io.aximm32.readAddr.bits.size := UInt(log2Up((32/8)-1)) // full-datawidth bursts
  io.aximm32.readAddr.bits.burst := UInt(1) // incrementing burst

  // the size of the next dist.vec burst -- do large bursts when possible
  val nextDistVecBurstSize = Mux(regDistVecElemsLeft >= UInt(8), 8, 1)
  val distVecFinished = (regDistVecElemsLeft === UInt(0))

  val distVecReqID = 0
  val colPtrReqID = 1

  switch(regState) {
      is(sIdle) {
        // register control inputs
        regDistVecElemsLeft := io.distVecCount
        regDistVecPtr := io.distVecBase
        regColPtrBase := io.colPtrBase
        regRowIndBase := io.rowIndBase

        when(io.start) {
          regFrontierSize := UInt(0)
          regState := sReqDistVec
        }
      }

      is(sReqDistVec) {
        when(distVecFinished) {
          regState := sFetchIndex
        } .otherwise {
          // set up distance vector read request
          io.aximm32.readAddr.valid := Bool(true)
          io.aximm32.readAddr.bits.addr := regDistVecPtr
          // the -1 comes from the AXI definition of the burst length param
          io.aximm32.readAddr.bits.len := UInt(nextDistVecBurstSize-1)
          io.aximm32.readAddr.bits.id := UInt(distVecReqID)

          when(io.aximm32.readAddr.ready) {
            // request acknowledged -- increment pointer, decrement counter
            regDistVecPtr := regDistVecPtr + UInt(4 * nextDistVecBurstSize)
            regDistVecElemsLeft := regDistVecElemsLeft - UInt(nextDistVecBurstSize)
            regState := sFetchIndex
          }
        }
      }

      is(sFetchIndex) {
        // fetch an index from the frontier queue, if there is one waiting
        io.frontierInds.ready := Bool(true)
        // each frontier index is 4 bytes -- multiply before registering
        regFrontierIndex := io.frontierInds.bits * UInt(4)

        when(io.frontierInds.valid) {
          // increment the frontier size
          regFrontierSize := regFrontierSize + UInt(1)
          // request this frontier index' col ptr
          regState := sReqColPtrs
        } .otherwise {
          // no frontier indices waiting
          regState := sCheckFinished
        }
      }

      is(sReqColPtrs) {
        // set up colptr read request
        io.aximm32.readAddr.valid := Bool(true)
        io.aximm32.readAddr.bits.addr := regColPtrBase + regFrontierIndex
        // the colptr read is always 2 beats long (start, end)
        io.aximm32.readAddr.bits.len := UInt(1)
        io.aximm32.readAddr.bits.id := UInt(colPtrReqID)

        when(io.aximm32.readAddr.ready) {
          regState := sCheckFinished
        }
      }

      is(sCheckFinished) {
        // by default, go back to requesting the distance vector
        regState := sReqDistVec
        when(distVecFinished) {
          // TODO wait until entire frontier has been processed
          // -- is distVecFinished really the right condition here? (no)
          regState := sFinished
        }
      }

      is(sFinished) {
        // finished -- wait for !start to go back to idle
        when(!io.start) {
          regState := sIdle
        }
      }
  }
}
