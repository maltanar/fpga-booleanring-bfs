package BFSSparseFrontier

import Chisel._
import AXIDefs._
import AXIStreamDefs._

class NeighborFetcher() extends Module {
  val io = new Bundle {
    val rowIndBase = UInt(INPUT, 32)
    val start = Bool(INPUT)
    val state = UInt(OUTPUT, 32)
    val colCount = UInt(OUTPUT, 32)
    val nzCount = UInt(OUTPUT, 32)

    // read requests for the 64-bit AXI channel
    //val readReqs = Decoupled(new AXIAddress(64, 2))
    val aximm64 = new AXIMasterReadOnlyIF(32, 64, 2)

    // loopback from readData32: row start/end pointers after TID demux
    val rowStartEnd = new AXIStreamSlaveIF(UInt(width = 32))

    // rowind metadata: is aligned (highest bit) plus length of column
    val rowIndsMetadata = Decoupled(UInt(width = 33))
    val rowIndsData = Decoupled(new AXIReadData(64, 2))
  }

  io.aximm64.renameSignals("aximm64")
  io.rowIndsData <> io.aximm64.readData

  val regColCount = Reg(init = UInt(0, 32))
  val regRowIndBase = Reg(init = UInt(0, 32))
  val regElementStart = Reg(init = UInt(0, 32))
  val regElementsLeft = Reg(init = UInt(0, 32))
  val regTotalNZ = Reg(init=UInt(0,32))

  // burst length of next request
  val regBurstLen = Reg(init=UInt(0,8))

  val sIdle :: sWaitPtrStart :: sWaitPtrEnd :: sPushMetadata :: sBuildReq :: sReq :: Nil = Enum(UInt(), 6)
  val regState = Reg(init = UInt(sIdle))

  // is the current row ind ptr aligned to 8 bytes?
  val isAligned = (regElementStart(2,0) === UInt(0) )
  val isAlignedVal = Mux(isAligned, UInt(1, width=1), UInt(0, width=1))
  // only do bursts if at least 8 elements are remaining
  val canDoBurst = (regElementsLeft >= UInt(8))

  // default outputs
  io.state := regState
  io.colCount := regColCount
  io.nzCount := regTotalNZ
  io.rowStartEnd.ready := Bool(false)
  io.rowIndsMetadata.valid := Bool(false)
  io.rowIndsMetadata.bits := Cat(isAlignedVal, regElementsLeft)

  // default outputs - 64-bit AXI channel read requests
  io.aximm64.readAddr.valid := Bool(false)
  io.aximm64.readAddr.bits.addr := regElementStart
  io.aximm64.readAddr.bits.len := regBurstLen - UInt(1) // -1 from protocol desc.
  io.aximm64.readAddr.bits.id := UInt(2)
  // full-datawidth bursts
  io.aximm64.readAddr.bits.size := UInt(log2Up((64/8)-1))
  // the rest of the readAddr channel data is the same and not modified
  io.aximm64.readAddr.bits.prot := UInt(0)
  io.aximm64.readAddr.bits.qos := UInt(0)
  io.aximm64.readAddr.bits.lock := Bool(false)
  io.aximm64.readAddr.bits.cache := UInt("b0010") // no alloc, modifiable, no buffer
  io.aximm64.readAddr.bits.burst := UInt(1) // incrementing burst

  switch(regState) {
      is(sIdle) {
        regBurstLen := UInt(1)
        when(io.start) {
          regRowIndBase := io.rowIndBase
          regColCount := UInt(0)
          regTotalNZ := UInt(0)
          regState := sWaitPtrStart
        }
      }

      is(sWaitPtrStart) {
        when(!io.start) {
          // also serves as exit/stop state
          regState := sIdle
        } .otherwise {
          // wait for starting colptr
          io.rowStartEnd.ready := Bool(true)
          regElementStart := io.rowStartEnd.bits

          when(io.rowStartEnd.valid) {
            regState := sWaitPtrEnd
          }
        }
      }

      is(sWaitPtrEnd) {
        // wait for ending colptr
        io.rowStartEnd.ready := Bool(true)

        when(io.rowStartEnd.valid) {
          // got a new column
          regColCount := regColCount + UInt(1)
          // calculate column length
          regElementsLeft := io.rowStartEnd.bits - regElementStart
          // add rowind base to get read pointer
          regElementStart := regElementStart + regRowIndBase
          regState := sPushMetadata
        }
      }

      is(sPushMetadata) {
        // do not consider empty rows -- no request, go back
        when(regElementsLeft === UInt(0)) {
          regState := sWaitPtrStart
        } .otherwise {
          // metadata should be now ready to push
          // metadata consists of isAligned and length of column
          io.rowIndsMetadata.valid := Bool(true)

          // wait until metadata accepted before proceeding
          when(io.rowIndsMetadata.ready) {
            regState := sBuildReq
          }
        }
      }

      is(sBuildReq) {
        // do not request if there are no more elements left -- get new col
        when(regElementsLeft === UInt(0)) {
          regState := sWaitPtrStart
        } .otherwise {
          // elements left - still requests to issue
          // compute burst length
          val burstLen = Mux(isAligned && canDoBurst, UInt(8), UInt(1))
          regBurstLen := UInt(burstLen)
          regState := sReq
        }
      }

      is(sReq) {
        io.aximm64.readAddr.valid := Bool(true)

        when(io.aximm64.readAddr.ready) {
          // read request accepted, update pointers and counts
          regElementStart := regElementStart + UInt(4) * regBurstLen
          regElementsLeft := regElementsLeft - regBurstLen
          regTotalNZ := regTotalNZ + regBurstLen
          // go back to sBuildReq for more requests, or get new column
          regState := sBuildReq
        }
      }
  }

}
