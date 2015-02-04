package BFSBackend

import Chisel._
import Literal._
import Node._
import AXIStreamDefs._
import AXIDefs._

class RequestGeneratorWrapper() extends Module {
  val io = new Bundle {
    val mmap = new AXIMasterReadOnlyIF(32, 64, 2)
    val strm = Decoupled(new AXIReadData(64, 2))
    
    // control interface
    val start = Bool(INPUT)
    val nzCount = UInt(INPUT, 32)
    val colCount = UInt(INPUT, 32)
    val colLenStart = UInt(INPUT, 32)
    val rowIndStart = UInt(INPUT, 32)
    val dvStart = UInt(INPUT, 32)
    
    // fullness thresholds for stopping requests
    val colLenFullThreshold = UInt(INPUT, 32)
    val rowIndFullThreshold = UInt(INPUT, 32)
    val denVecFullThreshold = UInt(INPUT, 32)
    
    // FIFO fullness count inputs for stopping requests
    val colLenDataCount = UInt(INPUT, 32)
    val rowIndDataCount = UInt(INPUT, 32)
    val denVecDataCount = UInt(INPUT, 32)
    
    // status interface
    val state = UInt(OUTPUT, 32)
  }
  
  io.mmap.renameSignals("mmap")
  
  // rename signals to recognize as an AXI stream interface
  val ifName = "strm"
  io.strm.bits.id.setName(ifName + "_TDEST")
  io.strm.bits.data.setName(ifName + "_TDATA")
  io.strm.bits.resp.setName(ifName + "_RRESP")
  io.strm.bits.last.setName(ifName + "_TLAST")
  io.strm.valid.setName(ifName + "_TVALID")
  io.strm.ready.setName(ifName + "_TREADY")
  
  // registers for disable request feedback to the request generator
  val regColLenFull = Reg(init = Bool(false))
  val regRowIndFull = Reg(init = Bool(false))
  val regDenVecFull = Reg(init = Bool(false))
  
  regColLenFull := (io.colLenDataCount >= io.colLenFullThreshold)
  regRowIndFull := (io.rowIndDataCount >= io.rowIndFullThreshold)
  regDenVecFull := (io.denVecDataCount >= io.denVecFullThreshold)

  val reqgen = Module(new RequestGenerator())
  // give read address channel to RequestGenerator
  reqgen.io.readAddr <> io.mmap.readAddr
  // "break out" read data channel through io.strm
  io.strm <> io.mmap.readData
  
  // connect feedback registers to request generator
  reqgen.io.disableColLen := regColLenFull
  reqgen.io.disableRowInd := regRowIndFull
  reqgen.io.disableDenVec := regDenVecFull
  
  // connect the rest of the signals (control/status)
  io <> reqgen.io
}
