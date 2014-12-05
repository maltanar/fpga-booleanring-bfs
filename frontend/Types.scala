package BFSFrontEnd

import Chisel._
import Literal._
import Node._

class MemReadWritePort(lineSize: Int, addrBits: Int) extends Bundle {
  val addr = UInt(INPUT, width=addrBits)
  val dataIn = UInt(INPUT, width=lineSize)
  val writeEn = Bool(INPUT)
  val dataOut = UInt(OUTPUT, width=lineSize)
  override def clone = { new MemReadWritePort(lineSize,addrBits).asInstanceOf[this.type] }
}

// the ISE-generated block RAM is declared as a black box
class VectorStorage extends BlackBox {
  val sizeBits = 32768
  val addrBitsPortA = log2Up(sizeBits/32)
  val addrBitsPortB = log2Up(sizeBits)

  val io = new Bundle {
    val en = Bool(INPUT)
    val portA = new MemReadWritePort(32, addrBitsPortA)
    val portB = new MemReadWritePort(1, addrBitsPortB)
  }

  // rename signals to match generated Verilog inst template
  io.en.setName("ena")
  
  io.portA.addr.setName("addra")
  io.portA.dataIn.setName("dina")
  io.portA.dataOut.setName("douta")
  io.portA.writeEn.setName("wea")
  
  io.portB.addr.setName("addrb")
  io.portB.dataIn.setName("dinb")
  io.portB.dataOut.setName("doutb")
  io.portB.writeEn.setName("web")
}
