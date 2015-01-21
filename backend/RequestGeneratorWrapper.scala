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
    
    // status interface
    val state = UInt(OUTPUT, 32)
  }
  
  io.mmap.renameSignals("mmap")

  val reqgen = Module(new RequestGenerator())
  // give read address channel to RequestGenerator
  reqgen.io.readAddr <> io.mmap.readAddr
  // "break out" read data channel through io.strm
  io.strm <> io.mmap.readData
  
  // connect the rest of the signals (control/status)
  io <> reqgen.io
}
