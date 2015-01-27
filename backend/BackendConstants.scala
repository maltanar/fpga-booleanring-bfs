package BFSBackend

trait BackendConstants {   
  val addrBits = 32           // width of address for AXI master
  val idBits = 2              // number of ID bits for AXI data bus
  val mmapDataBits = 64       // width of AXI data bus
  val colLenDataBits = 32     // width of each column length
  val rowIndDataBits = 32     // width of each row index
  val dvDataBits = 1          // width of each dense vector element

  // define IDs for memory requests
  val colLenReqID = 0
  val rowIndReqID = 1
  val dvReqID = 2

  // calculate elements per beat for the various components
  val colLenPerBeat = mmapDataBits / colLenDataBits
  val rowIndPerBeat = mmapDataBits / rowIndDataBits
  val dvPerBeat = mmapDataBits / dvDataBits

  // define burst sizes for the various components
  val colLenBurstSize = 1
  val rowIndBurstSize = 1
  val dvBurstSize = 1

  // calculate elements per burst for the various components
  val colLenPerBurst = colLenBurstSize * colLenPerBeat
  val rowIndPerBurst = rowIndBurstSize * rowIndPerBeat
  val dvPerBurst = dvBurstSize * dvPerBeat
}

object Constants extends
   BackendConstants
{
}
