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
    val currentLevel = UInt(INPUT, 32)
    val rowIndBase = UInt(INPUT, 32)
    val frontierSize = UInt(OUTPUT, 32)
    val nzCount = UInt(OUTPUT, 32)

    val thresholdT0 = UInt(INPUT, 32)
    val dataCountT0 = UInt(INPUT, 32)

    val thresholdT1 = UInt(INPUT, 32)
    val dataCountT1 = UInt(INPUT, 32)

    // control and status
    val state = UInt(OUTPUT, 32)
    val ngState = UInt(OUTPUT, 32)
    val ngColCount = UInt(OUTPUT, 32)
    val start = Bool(INPUT)

    // for smaller requests: distVec, colPtr
    val aximm32 = new AXIMasterReadOnlyIF(32, 32, 2)
    // for rowind requests
    val aximm64 = new AXIMasterReadOnlyIF(32, 64, 2)

    // decoupled channel to push out read data to AXI stream switch
    val readData32 = Decoupled(new AXIReadData(32, 2))

    // loopback from readData32: dist.vec elements
    val distVecIn = new AXIStreamSlaveIF(UInt(width = 32))
    // loopback from readData32: row start/end pointers after TID demux
    val rowStartEnd = new AXIStreamSlaveIF(UInt(width = 32))

    // output to frontend: row index data and metadata
    val rowIndsData = Decoupled(new AXIReadData(64, 2))
    val rowIndsMetadata = new AXIStreamMasterIF(UInt(width = 32))

  }

  // rename interfaces for Vivado IP integrator
  io.aximm32.renameSignals("aximm32")
  io.aximm64.renameSignals("aximm64")
  io.distVecIn.renameSignals("distVecIn")
  io.rowStartEnd.renameSignals("rowStartEnd")
  io.rowIndsMetadata.renameSignals("rowIndsMetadata")
  var ifName = "readData32"
  io.readData32.bits.id.setName(ifName + "_TDEST")
  io.readData32.bits.data.setName(ifName + "_TDATA")
  io.readData32.bits.resp.setName(ifName + "_RRESP")
  io.readData32.bits.last.setName(ifName + "_TLAST")
  io.readData32.valid.setName(ifName + "_TVALID")
  io.readData32.ready.setName(ifName + "_TREADY")
  ifName = "rowIndsData"
  io.rowIndsData.bits.id.setName(ifName + "_TDEST")
  io.rowIndsData.bits.data.setName(ifName + "_TDATA")
  io.rowIndsData.bits.resp.setName(ifName + "_RRESP")
  io.rowIndsData.bits.last.setName(ifName + "_TLAST")
  io.rowIndsData.valid.setName(ifName + "_TVALID")
  io.rowIndsData.ready.setName(ifName + "_TREADY")

  // break out read data channels
  io.readData32 <> io.aximm32.readData
  io.rowIndsData <> io.aximm64.readData

  // instantiate the throttler
  val throttler = Module(new BackendThrottler())
  throttler.io.thresholdT0 <> io.thresholdT0
  throttler.io.dataCountT0 <> io.dataCountT0
  throttler.io.thresholdT1 <> io.thresholdT1
  throttler.io.dataCountT1 <> io.dataCountT1

  // instantiate the frontier filter -- pick out indices in dist.vec that
  // have value == currentLevel, and push them into frontierQueue
  val frontierFilter = Module(new FrontierFilter())
  val frontierQueue = Module(new Queue(UInt(width=32), entries=32))
  val frontierInds = frontierQueue.io.deq
  frontierFilter.io.start <> io.start
  frontierFilter.io.distVecCount <> io.distVecCount
  frontierFilter.io.currentLevel <> io.currentLevel
  frontierFilter.io.distVecIn <> io.distVecIn
  frontierFilter.io.frontierOut <> frontierQueue.io.enq

  // instantiate the NeighborFetcher -- drain frontierQueue and generate
  // rowIndsData and rowIndsMetadata
  val neighborFetcher = Module(new NeighborFetcher())
  neighborFetcher.io.rowIndBase <> io.rowIndBase
  neighborFetcher.io.start <> io.start
  neighborFetcher.io.nzCount <> io.nzCount
  neighborFetcher.io.rowIndReadReqs <> io.aximm64.readAddr
  neighborFetcher.io.rowStartEndIn <> io.rowStartEnd
  neighborFetcher.io.rowIndsMetadata <> io.rowIndsMetadata

  // registers for internal bookkeeping
  val regDistVecElemsLeft = Reg(init = UInt(0, 32))
  val regDistVecPtr = Reg(init = UInt(0, 32))
  val regColPtrBase = Reg(init = UInt(0, 32))
  val regFrontierIndex = Reg(init = UInt(0, 32))
  val regFrontierSize = Reg(init = UInt(0, 32))

  // FSM for control -- dist.vec and col.ptr requests
  val sIdle :: sReqDistVec :: sFetchIndex :: sReqColPtrs :: sCheckFinished :: sFinished :: Nil = Enum(UInt(), 6)
  val regState = Reg(init = UInt(sIdle))

  io.state := regState
  io.ngState := neighborFetcher.io.state
  io.ngColCount := neighborFetcher.io.colCount


  io.frontierSize := regFrontierSize

  // default outputs -- loopback 32-bit data channels
  frontierInds.ready := Bool(false)

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
  val maxDistVecBurstSize = Mux(regDistVecElemsLeft >= UInt(2), UInt(2), UInt(1))
  val distVecFinished = (regDistVecElemsLeft === UInt(0))

  val distVecReqID = 0
  val colPtrReqID = 1

  switch(regState) {
      is(sIdle) {
        // register control inputs
        regDistVecElemsLeft := io.distVecCount
        regDistVecPtr := io.distVecBase
        regColPtrBase := io.colPtrBase

        when(io.start) {
          regFrontierSize := UInt(0)
          regState := sReqDistVec
        }
      }

      is(sReqDistVec) {
        when(distVecFinished || !throttler.io.canProceedT0) {
          regState := sFetchIndex
        } .otherwise {
          // set up distance vector read request
          io.aximm32.readAddr.valid := Bool(true)
          io.aximm32.readAddr.bits.addr := regDistVecPtr
          // the -1 comes from the AXI definition of the burst length param
          io.aximm32.readAddr.bits.len := maxDistVecBurstSize - UInt(1)
          io.aximm32.readAddr.bits.id := UInt(distVecReqID)

          when(io.aximm32.readAddr.ready) {
            // request acknowledged -- increment pointer, decrement counter
            regDistVecPtr := regDistVecPtr + UInt(4) * maxDistVecBurstSize
            regDistVecElemsLeft := regDistVecElemsLeft - maxDistVecBurstSize
            regState := sFetchIndex
          }
        }
      }

      is(sFetchIndex) {
        // don't pull off frontier unless we can issue its request
        when(!throttler.io.canProceedT1) { regState := sCheckFinished}
        .otherwise {
          // fetch an index from the frontier queue, if there is one waiting
          frontierInds.ready := Bool(true)
          // each frontier index is 4 bytes -- multiply before registering
          regFrontierIndex := frontierInds.bits * UInt(4)

          when(frontierInds.valid) {
            // increment the frontier size
            regFrontierSize := regFrontierSize + UInt(1)
            // request this frontier index' col ptr
            regState := sReqColPtrs
          } .otherwise {
            // no frontier indices waiting
            regState := sCheckFinished
          }
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
        val allRequested = (regFrontierSize === frontierFilter.io.frontierSize)
        val allFinished = (regFrontierSize === neighborFetcher.io.colCount)

        when(distVecFinished &&  allFinished) {
          // all done!
          regState := sFinished
        } .elsewhen(distVecFinished && allRequested) {
          // just waiting on the NeighborFetcher to finish, stay here
          regState := sCheckFinished
        } .elsewhen(distVecFinished && !allRequested) {
          // distvec finished, but more colptrs to request
          regState := sFetchIndex
        } .otherwise {
          // go back to sReqDistVec
          regState := sReqDistVec
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
