packge BFSSparseFrontier

import Chisel._
import AXIDefs._
import AXIStreamDefs._

class NeighborFetcher() extends Module {
  val io = new Bundle {
    val rowIndBase = UInt(INPUT, 32)
    val start = Bool(INPUT)
    val colCount = UInt(OUTPUT, 32)

    // AXI MM interface - 32 bit addr, 64 bit data, 2 bits request id
    // for the rowind requests
    val aximm64 = new AXIMasterReadOnlyIF(32, 64, 2)

    // loopback from readData32: row start/end pointers after TID demux
    val rowStartEnd = new AXIStreamSlaveIF(UInt(width = 32))
    // output to frontend: are the upper&lower rowind words valid?
    val rowIndsValid = Decoupled(UInt(width = 2))
  }

  val regColCount = Reg(init = UInt(0, 32))
  val regRowStart = Reg(init = UInt(0, 32))
  val regRowLen = Reg(init = UInt(0, 32))

  // is the current row ind ptr aligned to 8 bytes?
  val isAligned = (regRowStart(2,0) === UInt(0) )
  val nextBurstSize = Mux(regRowStart >= UInt(8), 8, 1)

  val sIdle :: sWaitPtrStart :: sWaitPtrEnd :: sBuildReq :: sReq :: sGenValid :: Nil = Enum(UInt(), 6)
  val regState = Reg(init = UInt(sIdle))

  io.colCount := regColCount
  io.rowStartEnd.ready := Bool(false)
  io.rowIndsValid.valid := Bool(false)
  io.rowIndsValid.bits := UInt(0)

  // default outputs - 64-bit AXI channel
  io.aximm64.readAddr.valid := Bool(false)
  io.aximm64.readAddr.bits.addr := regRowStart
  io.aximm64.readAddr.bits.len := UInt(0)
  io.aximm64.readAddr.bits.id := UInt(2)
  // not sure if all are full-datawidth bursts -- will modify
  io.aximm64.readAddr.bits.size := UInt(log2Up((64/8)-1))
  // the rest of the readAddr channel data is the same and not modified
  io.aximm64.readAddr.bits.prot := UInt(0)
  io.aximm64.readAddr.bits.qos := UInt(0)
  io.aximm64.readAddr.bits.lock := Bool(false)
  io.aximm64.readAddr.bits.cache := UInt("b0010") // no alloc, modifiable, no buffer
  io.aximm64.readAddr.bits.burst := UInt(1) // incrementing burst

  switch(regState) {
      is(sIdle) {
        when(io.start) {
          regColCount := UInt(0)
          regState := sWaitPtrStart
        }
      }

      is(sWaitPtrStart) {
        // wait for starting colptr
        io.rowStartEnd.ready := Bool(true)
        regRowStart := io.rowStartEnd.bits

        when(io.rowStartEnd.valid) {
          regState := sWaitPtrEnd
        }
      }

      is(sWaitPtrEnd) {
        // wait for ending colptr
        io.rowStartEnd.ready := Bool(true)

        when(io.rowStartEnd.valid) {
          // got a new column
          regColCount := regColCount + UInt(1)
          // calculate column length
          regRowLen := io.rowStartEnd.bits - regRowStart
          regState := sBuildReq
        }
      }

      is(sBuildReq) {
        // if address is unaligned, always do 4b-only request
        when

      }
  }

}
