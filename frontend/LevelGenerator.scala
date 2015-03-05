package BFSFrontEnd

import Chisel._
import Literal._
import Node._
import AXIStreamDefs._


class LevelGeneratorInterface(dataWidthBits: Int) extends Bundle {
  // control/status interface
  val start = Bool(INPUT)
  val bitCount = UInt(INPUT, 32)
  val finished = Bool(OUTPUT)
  val writeCount = UInt(OUTPUT, 32)

  // data stream inputs
  val oldData = new AXIStreamSlaveIF(UInt(width = dataWidthBits))
  val newData = new AXIStreamSlaveIF(UInt(width = dataWidthBits))

  // address stream output
  val writeIndices = new AXIStreamMasterIF(UInt(width = 32))
  // copy of the newData stream, for the input vector update
  val newDataCopy = new AXIStreamMasterIF(UInt(width = dataWidthBits))
}

class LevelGenerator(dataWidthBits: Int) extends Module {
  val io = new LevelGeneratorInterface(dataWidthBits)

  // internal registers to keep config and state
  val regBitCount = Reg(init = UInt(0, 32))
  val regWriteIndex = Reg(init = UInt(0, 32))
  val regShiftCounter = Reg(init = UInt(0, 32))
  val regWriteCount = Reg(init = UInt(0, 32))


  // registers for the incoming data streams
  val regOldData = Reg(init = UInt(0,dataWidthBits))
  val regNewData = Reg(init = UInt(0,dataWidthBits))

  // finite state machine
  val sIdle :: sCheckFinished :: sWaitOld :: sWaitNew :: sCopyNew :: sRun :: sFinished :: Nil = Enum(UInt(), 7)
  val regState = Reg(init = UInt(sIdle))

  // default outputs
  io.writeIndices.bits := regWriteIndex
  io.writeIndices.valid := Bool(false)
  io.oldData.ready := Bool(false)
  io.newData.ready := Bool(false)
  io.finished := Bool(false)
  io.writeCount := regWriteCount
  io.newDataCopy.valid := Bool(false)
  io.newDataCopy.bits := regNewData

  switch(regState) {
      is(sIdle) {
        // set config registers from inputs
        regBitCount := io.bitCount
        regWriteIndex := UInt(0)

        when(io.start) {
          regWriteCount := UInt(0)
          regState := sCheckFinished
        }
      }

      is(sCheckFinished) {
        when(regBitCount === UInt(0)) {
          // end of the entire level gen operation
          regState := sFinished
        } .otherwise {
          regState := sWaitOld
          // there may be less than a word's worth of shifts left
          // calculate which is the lesser of the two and assign shiftCounter
          // accordingly
          val incompleteWord = (regBitCount < UInt(dataWidthBits))
          regShiftCounter := Mux(incompleteWord, regBitCount, UInt(dataWidthBits))
        }
      }

      is(sWaitOld) {
        io.oldData.ready := Bool(true)

        when(io.oldData.valid) {
          regOldData := io.oldData.bits
          regState := sWaitNew
        }
      }

      is(sWaitNew) {
        io.newData.ready := Bool(true)

        when(io.newData.valid) {
          regNewData := io.newData.bits
          regState := sCopyNew
        }
      }

      is(sCopyNew) {
        io.newDataCopy.valid := Bool(true)

        when(io.newDataCopy.ready) {
          regState := sRun
        }
      }

      is(sRun) {
        when(regShiftCounter === UInt(0)) {
          // end of word reached, go to CheckFinished
          regState := sCheckFinished
        }  .otherwise {
          // core level generation logic:
          // when the bit in the same position in old data is 0 and
          // new data is 1, we create a write request for that position
          val genWriteRequest = !regOldData(0) && regNewData(0)
          io.writeIndices.valid := genWriteRequest

          when(io.writeIndices.ready || !genWriteRequest) {
            when(genWriteRequest) { regWriteCount := regWriteCount + UInt(1) }
            regOldData  := regOldData >> UInt(1)
            regNewData  := regNewData >> UInt(1)
            regBitCount := regBitCount - UInt(1)
            regShiftCounter := regShiftCounter - UInt(1)
            regWriteIndex := regWriteIndex + UInt(1)
          }
        }
      }

      is(sFinished) {
        io.finished := Bool(true)
        // wait for !start to go back to idle
        when(!io.start) { regState := sIdle}
      }
  }
}
// testbed for the LevelGenerator
// instantiates LevelGenerator and adds FIFOs on I/Os
// this makes testing in Chisel easier
class LevelGeneratorTestBed() extends Module {
  val io = new LevelGeneratorInterface(32)

  val levgen = Module(new LevelGenerator(32))

  val inQueue1 = Module(new Queue(UInt(width=32), entries = 16))
  val inQueue2 = Module(new Queue(UInt(width=32), entries = 16))

  val outQueue = Module(new Queue(UInt(width=32), entries = 32))

  inQueue1.io.enq <> io.oldData
  inQueue1.io.deq <> levgen.io.oldData

  inQueue2.io.enq <> io.newData
  inQueue2.io.deq <> levgen.io.newData

  outQueue.io.enq <> levgen.io.writeIndices
  outQueue.io.deq <> io.writeIndices

  levgen.io.start := io.start
  levgen.io.bitCount := io.bitCount

  io.finished := levgen.io.finished
  io.writeCount := levgen.io.writeCount
}

class LevelGeneratorTester(c: LevelGeneratorTestBed) extends Tester(c) {

  def fillFIFO(inds: Array[Int], fifoIF: DecoupledIO[UInt], fifoObj: Queue[UInt]) {
    var dc = 0
    for(ind <- inds) {
      poke(fifoIF.bits, UInt(ind).litValue())
      poke(fifoIF.valid, 1)
      dc = dc + 1
      step(1)
      expect(fifoObj.io.count, dc)
    }
    poke(fifoIF.valid, 0)
  }

  def drainFIFO(fifoIF: DecoupledIO[UInt], fifoObj: Queue[UInt], golden: Array[Int])
  {
    println("Now examining output FIFO contents...")
    var dc = 0
    while( peek(fifoObj.io.count) != 0) {
      poke(fifoIF.ready, 1)
      if(peek(fifoIF.valid) == 1) {
        expect(fifoIF.bits, golden(dc))
        dc = dc + 1
      }
      step(1)
    }
    poke(fifoIF.ready, 0)
    println("Data elements read: " + dc )
  }

  def launchTestCase( oldData: Array[Int], newData: Array[Int],
                      golden: Array[Int], bitCount: Int, basePtr: Int)
  {
    expect(c.io.finished, 0) // back to idle
    // fill input FIFOs
    fillFIFO(oldData, c.io.oldData, c.inQueue1)
    fillFIFO(newData, c.io.newData, c.inQueue2)
    // set up test
    poke(c.io.bitCount, bitCount)
    poke(c.io.start, 1)
    step(bitCount+10)
    expect(c.inQueue1.io.count, 0)  // queue 1 drained
    expect(c.inQueue2.io.count, 0)  // queue 2 drained
    expect(c.io.finished, 1)
    poke(c.io.start, 0)
    step(1)
    expect(c.io.finished, 0)
    // read contents of output FIFO
    drainFIFO(c.io.writeIndices, c.outQueue, golden)
  }


  println("Test case 1: given no start signal, stay in idle after reset")
  poke(c.io.start, 0)
  poke(c.io.bitCount, 0)
  step(1)
  expect(c.io.finished, 0)

  println("Test case 2: given bitCount = 0, go to sFinished")
  poke(c.io.start, 1)
  poke(c.io.bitCount, 0)
  step(1)
  step(1)
  expect(c.io.finished, 1)
  poke(c.io.start, 0) // remove start
  step(1)
  expect(c.io.finished, 0)

  println("Test case 3: regular usage with a single word (32 bits)")
  // TODO these arrays should be constructed by functions that take in indices
  // and produce the raw data
  val oldData = Array(1)
  val newData = Array(11)
  // TODO the goldData array should be auto-constructed from olData and newData
  var goldData = Array(1, 3)

  launchTestCase(oldData, newData, goldData, 32, 0)

  println("Test case 4: regular usage, less than 32 bits")
  launchTestCase(oldData, newData, goldData, 17, 0)
}
