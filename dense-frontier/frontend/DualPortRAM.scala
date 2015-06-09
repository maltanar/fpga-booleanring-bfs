package BFSFrontEnd

import Chisel._
import Literal._
import Node._


class DualPortRAM(widthBits: Int, depth: Int) extends Module {
  val addrBits = log2Up(depth)
  val io = new Bundle {
    val portA = new MemReadWritePort(widthBits, addrBits)
    val portB = new MemReadWritePort(widthBits, addrBits)
  }
  
  // enable sequential reads for data storage (to infer BRAM)
  val memory = Mem(UInt(width=widthBits), depth, true)
  
  // default read outputs
  io.portA.dataOut := Reg(next=memory(io.portA.addr))
  io.portB.dataOut := Reg(next=memory(io.portB.addr))
  
  when(io.portA.writeEn) { memory(io.portA.addr) := io.portA.dataIn }
  
  when(io.portB.writeEn) { memory(io.portB.addr) := io.portB.dataIn }
}
