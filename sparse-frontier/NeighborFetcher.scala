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
    val rowIndReadReqs = Decoupled(new AXIAddress(32, 2))

    // loopback from readData32: row start/end pointers after TID demux
    val rowStartEndIn = new AXIStreamSlaveIF(UInt(width = 32))

    // rowind metadata: is aligned (highest bit) plus length of column
    val rowIndsMetadata = new AXIStreamMasterIF(UInt(width = 32))
  }

  val regColCount = Reg(init = UInt(0, 32))
  val regRowIndBase = Reg(init = UInt(0, 32))
  val regElementStart = Reg(init = UInt(0, 32))
  val regElementsLeft = Reg(init = UInt(0, 32))
  val regTotalNZ = Reg(init=UInt(0,32))

  // 64 bit channel, 32 bit data: 2 elements per beat
  val elementsPerBeat = 64/32
  // burst length of next request, in 64-bit beats
  val regBurstLen = Reg(init=UInt(0,8))
  // actual number of elements covered by this burst
  val regBurstElements = Reg(init=UInt(0,8))

  val sIdle :: sWaitPtrStart :: sWaitPtrEnd :: sPushMetadata :: sBuildReq :: sReq :: Nil = Enum(UInt(), 6)
  val regState = Reg(init = UInt(sIdle))

  // is the current row ind ptr aligned to 8 bytes?
  val isAligned = (regElementStart(2,0) === UInt(0) )
  val isAlignedVal = Mux(isAligned, UInt(1, width=1), UInt(0, width=1))
  // we do bursts of 8 beats to increase bandwidth utilization:
  // only do bursts if at least 8*2=16 elements are remaining
  val burstLen = 8
  val canDoBurst = (regElementsLeft >= UInt(burstLen*elementsPerBeat))

  // default outputs
  io.state := regState
  io.colCount := regColCount
  io.nzCount := regTotalNZ
  io.rowStartEndIn.ready := Bool(false)
  io.rowIndsMetadata.valid := Bool(false)
  io.rowIndsMetadata.bits := Cat(isAlignedVal, regElementsLeft(30,0))

  // default outputs - 64-bit AXI channel read requests
  io.rowIndReadReqs.valid := Bool(false)
  io.rowIndReadReqs.bits.addr := regElementStart
  io.rowIndReadReqs.bits.len := regBurstLen - UInt(1) // -1 from protocol desc.
  io.rowIndReadReqs.bits.id := UInt(2)
  // full-datawidth bursts
  io.rowIndReadReqs.bits.size := UInt(log2Up((64/8)-1))
  // the rest of the readAddr channel data is the same and not modified
  io.rowIndReadReqs.bits.prot := UInt(0)
  io.rowIndReadReqs.bits.qos := UInt(0)
  io.rowIndReadReqs.bits.lock := Bool(false)
  io.rowIndReadReqs.bits.cache := UInt("b0010") // no alloc, modifiable, no buffer
  io.rowIndReadReqs.bits.burst := UInt(1) // incrementing burst

  switch(regState) {
      is(sIdle) {
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
          io.rowStartEndIn.ready := Bool(true)
          regElementStart := io.rowStartEndIn.bits

          when(io.rowStartEndIn.valid) {
            regState := sWaitPtrEnd
          }
        }
      }

      is(sWaitPtrEnd) {
        // wait for ending colptr
        io.rowStartEndIn.ready := Bool(true)
        // calculate column length
        regElementsLeft := io.rowStartEndIn.bits - regElementStart

        when(io.rowStartEndIn.valid) {
          // got a new column
          regColCount := regColCount + UInt(1)

          // add rowind base to get read pointer
          // also: elementStart is an index, convert to offset
          // (each element is 4 bytes)
          regElementStart := UInt(4)*regElementStart + regRowIndBase
          regState := sPushMetadata
        }
      }

      is(sPushMetadata) {
        val isEmptyCol = (regElementsLeft === UInt(0))
        // metadata should be now ready to push (even for an empty column)
        // metadata consists of isAligned and length of column
        io.rowIndsMetadata.valid := Bool(true)

        // wait until metadata accepted before proceeding
        when(io.rowIndsMetadata.ready) {
          // if column is empty, get a new one. but still important to
          // push its metadata to signal the frontend
          regState := Mux(isEmptyCol, sWaitPtrStart, sBuildReq)
        }
      }

      is(sBuildReq) {
        // do not request if there are no more elements left -- get new col
        when(regElementsLeft === UInt(0)) {
          regState := sWaitPtrStart
        } .otherwise {
          // elements left - still requests to issue
          // compute burst length - this is in 8-byte beats
          val burstLen = Mux(isAligned && canDoBurst, UInt(8), UInt(1))
          regBurstLen := UInt(burstLen)
          // compute how many elements we cover with this burst
          val isHalfBeat = !isAligned || (regElementsLeft === UInt(1))
          regBurstElements := Mux(isHalfBeat,burstLen, burstLen*UInt(2) )
          regState := sReq
        }
      }

      is(sReq) {
        io.rowIndReadReqs.valid := Bool(true)

        when(io.rowIndReadReqs.ready) {
          // read request accepted, update pointers and counts
          regElementStart := regElementStart + UInt(4) * regBurstElements
          regElementsLeft := regElementsLeft - regBurstElements
          regTotalNZ := regTotalNZ + regBurstElements
          // go back to sBuildReq for more requests, or get new column
          regState := sBuildReq
        }
      }
  }

}
