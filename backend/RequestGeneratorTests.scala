package BFSBackend

import Chisel._
import Literal._
import Node._
import AXIStreamDefs._
import AXIDefs._

class RequestGeneratorTests(c: RequestGenerator) extends Tester(c) {
  // utility functions for the testbench
  def checkReadRequest(baseAddr: Int, bytesPerIter: Int, iterNum: Int, reqId: Int) = {
    expect(c.io.readAddr.valid, 1) // "readAddr.valid should be 1")
    expect(c.io.readAddr.bits.addr, baseAddr+bytesPerIter*iterNum) // "Address should match"
    expect(c.io.readAddr.bits.id, reqId) // "ReqID should be correct")
    expect(c.io.readAddr.bits.len, (bytesPerIter/8)-1) // "Burst length should be correct")
  }
  
  def checkNoRequest() = {
    expect(c.io.readAddr.valid, 0)
  }
  
  // constants for the testbench
  val colLenStart = 0
  val rowIndStart = 1000
  val dvStart = 2000
  val addrBits = 32
  val idBits = 2
  val mmapDataBits = 64       // width of AXI data bus
  val colLenDataBits = 32     // width of each column length
  val rowIndDataBits = 32     // width of each row index
  val dvDataBits = 1          // width of each dense vector element
  
  // define IDs for memory requests
  val colLenReqID = 1
  val rowIndReqID = 2
  val dvReqID = 3
  
  // calculate elements per beat for the various components
  val colLenPerBeat = mmapDataBits / colLenDataBits
  val rowIndPerBeat = mmapDataBits / rowIndDataBits
  val dvPerBeat = mmapDataBits / dvDataBits
  
  // define burst sizes for the various components
  val colLenBurstSize = 8
  val rowIndBurstSize = 8
  val dvBurstSize = 1
  
  // calculate elements per burst for the various components
  val colLenPerBurst = colLenBurstSize * colLenPerBeat
  val rowIndPerBurst = rowIndBurstSize * rowIndPerBeat
  val dvPerBurst = dvBurstSize * dvPerBeat
  val colLenBurstBytes = colLenBurstSize * (mmapDataBits/8)
  val rowIndBurstBytes = rowIndBurstSize * (mmapDataBits/8)
  val dvBurstBytes = dvBurstSize * (mmapDataBits/8)
  // states
  val sIdle = 0
  val sReqColLen = 1
  val sReqRowInd = 2
  val sReqDenVec = 3
  val sCheckFinished = 4
  
  // ======================= start of testbench code ========================
  poke(c.io.start, 0)
  poke(c.io.nzCount, 64)
  poke(c.io.colCount, 64)
  poke(c.io.colLenStart, colLenStart)
  poke(c.io.rowIndStart, rowIndStart)
  poke(c.io.dvStart, dvStart)
  poke(c.io.readAddr.ready, 0)
  peek(c.io.state)
  expect(c.io.state, sIdle) // sIdle after reset
  step(1)
  expect(c.io.state, sIdle) // sIdle with no start
  checkNoRequest()
  poke(c.io.start, 1)
  step(1)
  expect(c.io.state, sReqColLen) // in sReqColLen after start
  checkReadRequest(colLenStart, colLenBurstBytes, 0, colLenReqID)
  step(1)
  // since ready is low, request should stay the same
  checkReadRequest(colLenStart, colLenBurstBytes, 0, colLenReqID)
  // acknowledge request now
  poke(c.io.readAddr.ready, 1)
  step(1)
  expect(c.io.state, 2)
  // check for rowind request
  checkReadRequest(rowIndStart, rowIndBurstBytes, 0, rowIndReqID)
  // acknowledge and continue
  step(1)
  expect(c.io.state, 3)
  // check for dv request
  checkReadRequest(dvStart, dvBurstBytes, 0, dvReqID)
  // acknowledge and continue
  step(1)
  poke(c.io.readAddr.ready, 0) // remove ack
  expect(c.io.state, 4)
  step(1)
  expect(c.io.state, 1) // back to sReqColLen

  // set ack high
  poke(c.io.readAddr.ready, 1)
  for (i <- 1 until 4) {
    expect(c.io.state, 1) // sReqColLen
    checkReadRequest(colLenStart, colLenBurstBytes, i, colLenReqID)
    step(1)
    expect(c.io.state, 2) // sReqRowInd
    checkReadRequest(rowIndStart, rowIndBurstBytes, i, rowIndReqID)
    step(1)
    expect(c.io.state, 3) // sReqDenVec
    checkNoRequest() // no request, should be finished after the first one
    step(1)
    expect(c.io.state, 4) // sCheckFinished
    checkNoRequest()
    step(1)
  }
  
  expect(c.io.state, 0) // finished
  
}
