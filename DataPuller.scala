package BoolRingBFS

import Chisel._
import AXILiteDefs._
import AXIDefs._


class DataPuller() extends Module {
  val io = new Bundle {
    val master = new AXIMasterIF(32, 64, 2)
    // output data queues
    val matrixData = Decoupled(UInt(64))
    val vectorData = Decoupled(UInt(64))
    // start of data
    val matrixPtr = UInt(INPUT, 32)
    val vectorPtr = UInt(INPUT, 32)
    // control
    val start = Bool(INPUT)
    val stop = Bool(INPUT)
  }
  
  io.master.renameSignals()
  
  // shorthands for AXI channels
  val readAddr = io.master.readAddr
  val readData = io.master.readData
  
  // ************************************************************************************ //
  //                                  default outputs
  // ************************************************************************************ //
  
  // master read address & data
  readAddr.valid := Bool(false)
  readAddr.bits.addr := UInt(0)
  readAddr.bits.size := UInt(log2Up((dataBits/8)-1)) // full-datawidth bursts
  readAddr.bits.burst := UInt(1) // incrementing burst
  readAddr.bits.len := UInt(0) 
  readAddr.bits.cache := UInt("b0010") // no alloc, modifiable, no buffer
  readAddr.bits.prot := UInt(0)
  readAddr.bits.qos := UInt(0)
  readAddr.bits.lock := Bool(false)
  readAddr.bits.id := UInt(0)
  readData.ready := Bool(false)
  
  // master write address & data
  // we don't use the write channel in this module
  io.master.writeData.valid := Bool(false)
  io.master.writeAddr.valid := Bool(false)
  io.master.writeResp.ready := Bool(false)
  io.master.writeAddr.bits.addr := UInt(0)
  io.master.writeAddr.bits.prot := UInt(0)
  io.master.writeAddr.bits.size := UInt(0)
  io.master.writeAddr.bits.len := UInt(0)
  io.master.writeAddr.bits.burst := UInt(0)
  io.master.writeAddr.bits.lock := Bool(false)
  io.master.writeAddr.bits.cache := UInt(0)
  io.master.writeAddr.bits.qos := UInt(0)
  io.master.writeAddr.bits.id := UInt(0)
  io.master.writeData.bits.data := UInt(0)
  io.master.writeData.bits.strb := UInt(0)
  io.master.writeData.bits.last := Bool(false)
  
  // output channels
  io.matrixData.valid := Bool(false)
  io.vectorData.valid := Bool(false)
  io.matrixData.bits := readData.bits.data
  io.vectorData.bits := readData.bits.data
  
  // constants
  // TODO take from global config
  val dataBits = 64
  val addrBits = 32
  val wordSize = 32
  val wordsPerBeat = dataBits/wordSize
  
  val vectorBurstLength = 1   // burst length for vector requests
  val vectorBurstID = 1       // request ID for vector requests
  val matrixBurstLength = 8   // burst length for vector requests
  val matrixBurstID = 2       // request ID for vector requests
  
  // registers
  val regMatrixPtr = Reg(init = UInt(0, 32))
  val regDenseVecPtr = Reg(init = UInt(0, 32))
  
  val sIdle :: sFillVector :: sFillMatrix :: Nil = Enum(UInt(), 3)
  val state = Reg(init = UInt(sIdle))
  
  
  // state machine for control
  when ( state === sIdle )
  {
    regMatrixPtr := io.matrixPtr
    regDenseVecPtr := io.vectorPtr
    
    when ( io.start ) { state := sFillVector}
  }
  .elsewhen ( state === sFillVector )
  {
    // issue read request for vector data
    readAddr.valid := Bool(true)
    readAddr.bits.addr := regDenseVecPtr
    readAddr.bits.len := UInt(vectorBurstLength-1)
    readAddr.bits.id := UInt(vectorBurstID)
    
    when ( io.stop ) { state := sIdle }
    .elsewhen ( readAddr.ready ) 
    {
      // address accepted, increment for next
      regDenseVecPtr := regDenseVecPtr + UInt((addrBits/8)*wordsPerBeat*vectorBurstLength)
      state := sFillMatrix
    }
  }
  .elsewhen ( state === sFillMatrix) 
  {
    // issue read request for matrix data
    readAddr.valid := Bool(true)
    readAddr.bits.addr := regMatrixPtr
    readAddr.bits.len := UInt(matrixBurstLength-1)
    readAddr.bits.id := UInt(matrixBurstID)
    
    when ( io.stop ) { state := sIdle }
    .elsewhen ( readAddr.ready )
    {
      // address accepted, increment for next
      regMatrixPtr := regMatrixPtr + UInt((addrBits/8)*wordsPerBeat*matrixBurstLength)
      state := sFillVector
    }
  }
  
  // accept and move read data into appropriate output depending on ID
  val canAcceptData = (state === sFillVector || state === sFillMatrix)
  val dataIsVector = (readData.bits.id === UInt(vectorBurstID))
  val dataIsMatrix = (readData.bits.id === UInt(matrixBurstID))
  
  when ( canAcceptData )
  {
    // TODO this assumes no erronous IDs will be returned
    readData.ready := Mux(dataIsVector, io.vectorData.ready, io.matrixData.ready)
    io.matrixData.valid := dataIsMatrix
    io.vectorData.valid := dataIsVector
  }
}
