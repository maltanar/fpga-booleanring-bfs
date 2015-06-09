module RequestGenerator(input clk, input reset,
    input  io_start,
    input [31:0] io_nzCount,
    input [31:0] io_colCount,
    input [31:0] io_colLenStart,
    input [31:0] io_rowIndStart,
    input [31:0] io_dvStart,
    input  io_disableColLen,
    input  io_disableRowInd,
    input  io_disableDenVec,
    output[31:0] io_state,
    input  io_readAddr_ready,
    output io_readAddr_valid,
    output[31:0] io_readAddr_bits_addr,
    output[2:0] io_readAddr_bits_size,
    output[7:0] io_readAddr_bits_len,
    output[1:0] io_readAddr_bits_burst,
    output[1:0] io_readAddr_bits_id,
    output io_readAddr_bits_lock,
    output[3:0] io_readAddr_bits_cache,
    output[2:0] io_readAddr_bits_prot,
    output[3:0] io_readAddr_bits_qos
);

  wire[1:0] T0;
  wire[1:0] T65;
  wire T1;
  wire T2;
  wire T3;
  wire rowIndFinished;
  reg [31:0] regRowIndCount;
  wire[31:0] T66;
  wire[31:0] T4;
  wire[31:0] T5;
  wire T6;
  reg [2:0] regState;
  wire[2:0] T67;
  wire[2:0] T7;
  wire[2:0] T8;
  wire[2:0] T9;
  wire[2:0] T10;
  wire[2:0] T11;
  wire[2:0] T12;
  wire[2:0] T13;
  wire[2:0] T14;
  wire[2:0] T15;
  wire[2:0] T16;
  wire T17;
  wire T18;
  wire T19;
  wire colCountFinished;
  reg [31:0] regColCount;
  wire[31:0] T68;
  wire[31:0] T20;
  wire[31:0] T21;
  wire[31:0] T22;
  wire T23;
  wire T24;
  wire T25;
  wire T26;
  wire T27;
  wire T28;
  wire T29;
  wire denseVecFinished;
  reg [31:0] regDVCount;
  wire[31:0] T69;
  wire[31:0] T30;
  wire[31:0] T31;
  wire[31:0] T32;
  wire T33;
  wire T34;
  wire T35;
  wire allFinished;
  wire T36;
  wire T37;
  wire T38;
  wire T39;
  wire T40;
  wire T41;
  wire T42;
  wire[31:0] T43;
  wire T44;
  wire T45;
  wire T46;
  wire T47;
  wire[7:0] T70;
  wire[2:0] T48;
  wire[2:0] T49;
  wire[2:0] T50;
  wire[31:0] T51;
  wire[31:0] T52;
  wire[31:0] T53;
  reg [31:0] regColLenPtr;
  wire[31:0] T71;
  wire[31:0] T54;
  wire[31:0] T55;
  wire[31:0] T56;
  reg [31:0] regRowIndPtr;
  wire[31:0] T72;
  wire[31:0] T57;
  wire[31:0] T58;
  wire[31:0] T59;
  reg [31:0] regDVPtr;
  wire[31:0] T73;
  wire[31:0] T60;
  wire[31:0] T61;
  wire[31:0] T62;
  wire T63;
  wire T64;
  wire[31:0] T74;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    regRowIndCount = {1{$random}};
    regState = {1{$random}};
    regColCount = {1{$random}};
    regDVCount = {1{$random}};
    regColLenPtr = {1{$random}};
    regRowIndPtr = {1{$random}};
    regDVPtr = {1{$random}};
  end
// synthesis translate_on
`endif

  assign io_readAddr_bits_qos = 4'h0;
  assign io_readAddr_bits_prot = 3'h0;
  assign io_readAddr_bits_cache = 4'h2;
  assign io_readAddr_bits_lock = 1'h0;
  assign io_readAddr_bits_id = T0;
  assign T0 = T46 ? 2'h2 : T65;
  assign T65 = {1'h0, T1};
  assign T1 = T45 & T2;
  assign T2 = T3 ^ 1'h1;
  assign T3 = rowIndFinished | io_disableRowInd;
  assign rowIndFinished = regRowIndCount == 32'h0;
  assign T66 = reset ? 32'h0 : T4;
  assign T4 = T44 ? T43 : T5;
  assign T5 = T6 ? io_nzCount : regRowIndCount;
  assign T6 = 3'h0 == regState;
  assign T67 = reset ? 3'h0 : T7;
  assign T7 = T40 ? 3'h0 : T8;
  assign T8 = T38 ? 3'h1 : T9;
  assign T9 = T35 ? 3'h5 : T10;
  assign T10 = T34 ? 3'h4 : T11;
  assign T11 = T28 ? 3'h4 : T12;
  assign T12 = T44 ? 3'h3 : T13;
  assign T13 = T27 ? 3'h3 : T14;
  assign T14 = T24 ? 3'h2 : T15;
  assign T15 = T18 ? 3'h2 : T16;
  assign T16 = T17 ? 3'h1 : regState;
  assign T17 = T6 & io_start;
  assign T18 = T23 & T19;
  assign T19 = colCountFinished | io_disableColLen;
  assign colCountFinished = regColCount == 32'h0;
  assign T68 = reset ? 32'h0 : T20;
  assign T20 = T24 ? T22 : T21;
  assign T21 = T6 ? io_colCount : regColCount;
  assign T22 = regColCount - 32'h10;
  assign T23 = 3'h1 == regState;
  assign T24 = T25 & io_readAddr_ready;
  assign T25 = T23 & T26;
  assign T26 = T19 ^ 1'h1;
  assign T27 = T45 & T3;
  assign T28 = T33 & T29;
  assign T29 = denseVecFinished | io_disableDenVec;
  assign denseVecFinished = regDVCount == 32'h0;
  assign T69 = reset ? 32'h0 : T30;
  assign T30 = T34 ? T32 : T31;
  assign T31 = T6 ? io_colCount : regDVCount;
  assign T32 = regDVCount - 32'h40;
  assign T33 = 3'h3 == regState;
  assign T34 = T46 & io_readAddr_ready;
  assign T35 = T37 & allFinished;
  assign allFinished = T36 & denseVecFinished;
  assign T36 = colCountFinished & rowIndFinished;
  assign T37 = 3'h4 == regState;
  assign T38 = T37 & T39;
  assign T39 = allFinished ^ 1'h1;
  assign T40 = T42 & T41;
  assign T41 = io_start ^ 1'h1;
  assign T42 = 3'h5 == regState;
  assign T43 = regRowIndCount - 32'h10;
  assign T44 = T1 & io_readAddr_ready;
  assign T45 = 3'h2 == regState;
  assign T46 = T33 & T47;
  assign T47 = T29 ^ 1'h1;
  assign io_readAddr_bits_burst = 2'h1;
  assign io_readAddr_bits_len = T70;
  assign T70 = {5'h0, T48};
  assign T48 = T46 ? 3'h0 : T49;
  assign T49 = T1 ? 3'h7 : T50;
  assign T50 = T25 ? 3'h7 : 3'h0;
  assign io_readAddr_bits_size = 3'h3;
  assign io_readAddr_bits_addr = T51;
  assign T51 = T46 ? regDVPtr : T52;
  assign T52 = T1 ? regRowIndPtr : T53;
  assign T53 = T25 ? regColLenPtr : 32'h0;
  assign T71 = reset ? 32'h0 : T54;
  assign T54 = T24 ? T56 : T55;
  assign T55 = T6 ? io_colLenStart : regColLenPtr;
  assign T56 = regColLenPtr + 32'h40;
  assign T72 = reset ? 32'h0 : T57;
  assign T57 = T44 ? T59 : T58;
  assign T58 = T6 ? io_rowIndStart : regRowIndPtr;
  assign T59 = regRowIndPtr + 32'h40;
  assign T73 = reset ? 32'h0 : T60;
  assign T60 = T34 ? T62 : T61;
  assign T61 = T6 ? io_dvStart : regDVPtr;
  assign T62 = regDVPtr + 32'h8;
  assign io_readAddr_valid = T63;
  assign T63 = T46 ? 1'h1 : T64;
  assign T64 = T1 ? 1'h1 : T25;
  assign io_state = T74;
  assign T74 = {29'h0, regState};

  always @(posedge clk) begin
    if(reset) begin
      regRowIndCount <= 32'h0;
    end else if(T44) begin
      regRowIndCount <= T43;
    end else if(T6) begin
      regRowIndCount <= io_nzCount;
    end
    if(reset) begin
      regState <= 3'h0;
    end else if(T40) begin
      regState <= 3'h0;
    end else if(T38) begin
      regState <= 3'h1;
    end else if(T35) begin
      regState <= 3'h5;
    end else if(T34) begin
      regState <= 3'h4;
    end else if(T28) begin
      regState <= 3'h4;
    end else if(T44) begin
      regState <= 3'h3;
    end else if(T27) begin
      regState <= 3'h3;
    end else if(T24) begin
      regState <= 3'h2;
    end else if(T18) begin
      regState <= 3'h2;
    end else if(T17) begin
      regState <= 3'h1;
    end
    if(reset) begin
      regColCount <= 32'h0;
    end else if(T24) begin
      regColCount <= T22;
    end else if(T6) begin
      regColCount <= io_colCount;
    end
    if(reset) begin
      regDVCount <= 32'h0;
    end else if(T34) begin
      regDVCount <= T32;
    end else if(T6) begin
      regDVCount <= io_colCount;
    end
    if(reset) begin
      regColLenPtr <= 32'h0;
    end else if(T24) begin
      regColLenPtr <= T56;
    end else if(T6) begin
      regColLenPtr <= io_colLenStart;
    end
    if(reset) begin
      regRowIndPtr <= 32'h0;
    end else if(T44) begin
      regRowIndPtr <= T59;
    end else if(T6) begin
      regRowIndPtr <= io_rowIndStart;
    end
    if(reset) begin
      regDVPtr <= 32'h0;
    end else if(T34) begin
      regDVPtr <= T62;
    end else if(T6) begin
      regDVPtr <= io_dvStart;
    end
  end
endmodule

module WriteGenerator(input clk, input reset,
    input  io_start,
    input [31:0] io_basePtr,
    output[31:0] io_state,
    output[31:0] io_writeCount,
    output io_writeDataIn_ready,
    input  io_writeDataIn_valid,
    input [63:0] io_writeDataIn_bits,
    input  io_writeAddrOut_ready,
    output io_writeAddrOut_valid,
    output[31:0] io_writeAddrOut_bits_addr,
    output[2:0] io_writeAddrOut_bits_size,
    output[7:0] io_writeAddrOut_bits_len,
    output[1:0] io_writeAddrOut_bits_burst,
    output[1:0] io_writeAddrOut_bits_id,
    output io_writeAddrOut_bits_lock,
    output[3:0] io_writeAddrOut_bits_cache,
    output[2:0] io_writeAddrOut_bits_prot,
    output[3:0] io_writeAddrOut_bits_qos,
    input  io_writeDataOut_ready,
    output io_writeDataOut_valid,
    output[63:0] io_writeDataOut_bits_data,
    output[7:0] io_writeDataOut_bits_strb,
    output io_writeDataOut_bits_last,
    output io_writeRespIn_ready,
    input  io_writeRespIn_valid,
    input [1:0] io_writeRespIn_bits_id,
    input [1:0] io_writeRespIn_bits_resp
);

  wire T0;
  reg [1:0] regState;
  wire[1:0] T25;
  wire[1:0] T1;
  wire[1:0] T2;
  wire[1:0] T3;
  wire[1:0] T4;
  wire[1:0] T5;
  wire T6;
  wire T7;
  wire T8;
  wire T9;
  wire T10;
  wire T11;
  wire T12;
  wire T13;
  wire T14;
  wire T15;
  wire T16;
  wire T17;
  reg [63:0] regWriteData;
  wire[63:0] T26;
  wire[63:0] T18;
  reg [31:0] regWritePtr;
  wire[31:0] T27;
  wire[31:0] T19;
  wire[31:0] T20;
  wire[31:0] T21;
  reg [31:0] regWriteCount;
  wire[31:0] T28;
  wire[31:0] T22;
  wire[31:0] T23;
  wire[31:0] T24;
  wire[31:0] T29;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    regState = {1{$random}};
    regWriteData = {2{$random}};
    regWritePtr = {1{$random}};
    regWriteCount = {1{$random}};
  end
// synthesis translate_on
`endif

  assign io_writeRespIn_ready = T0;
  assign T0 = regState != 2'h0;
  assign T25 = reset ? 2'h0 : T1;
  assign T1 = T16 ? 2'h1 : T2;
  assign T2 = T14 ? 2'h3 : T3;
  assign T3 = T11 ? 2'h2 : T4;
  assign T4 = T8 ? 2'h0 : T5;
  assign T5 = T6 ? 2'h1 : regState;
  assign T6 = T7 & io_start;
  assign T7 = 2'h0 == regState;
  assign T8 = T10 & T9;
  assign T9 = io_start ^ 1'h1;
  assign T10 = 2'h1 == regState;
  assign T11 = T10 & T12;
  assign T12 = T13 & io_writeDataIn_valid;
  assign T13 = T9 ^ 1'h1;
  assign T14 = T15 & io_writeAddrOut_ready;
  assign T15 = 2'h2 == regState;
  assign T16 = T17 & io_writeDataOut_ready;
  assign T17 = 2'h3 == regState;
  assign io_writeDataOut_bits_last = 1'h1;
  assign io_writeDataOut_bits_strb = 8'hff;
  assign io_writeDataOut_bits_data = regWriteData;
  assign T26 = reset ? 64'h0 : T18;
  assign T18 = T10 ? io_writeDataIn_bits : regWriteData;
  assign io_writeDataOut_valid = T17;
  assign io_writeAddrOut_bits_qos = 4'h0;
  assign io_writeAddrOut_bits_prot = 3'h0;
  assign io_writeAddrOut_bits_cache = 4'h2;
  assign io_writeAddrOut_bits_lock = 1'h0;
  assign io_writeAddrOut_bits_id = 2'h0;
  assign io_writeAddrOut_bits_burst = 2'h1;
  assign io_writeAddrOut_bits_len = 8'h0;
  assign io_writeAddrOut_bits_size = 3'h3;
  assign io_writeAddrOut_bits_addr = regWritePtr;
  assign T27 = reset ? 32'h0 : T19;
  assign T19 = T14 ? T21 : T20;
  assign T20 = T7 ? io_basePtr : regWritePtr;
  assign T21 = regWritePtr + 32'h8;
  assign io_writeAddrOut_valid = T15;
  assign io_writeDataIn_ready = T10;
  assign io_writeCount = regWriteCount;
  assign T28 = reset ? 32'h0 : T22;
  assign T22 = T16 ? T24 : T23;
  assign T23 = T6 ? 32'h0 : regWriteCount;
  assign T24 = regWriteCount + 32'h1;
  assign io_state = T29;
  assign T29 = {30'h0, regState};

  always @(posedge clk) begin
    if(reset) begin
      regState <= 2'h0;
    end else if(T16) begin
      regState <= 2'h1;
    end else if(T14) begin
      regState <= 2'h3;
    end else if(T11) begin
      regState <= 2'h2;
    end else if(T8) begin
      regState <= 2'h0;
    end else if(T6) begin
      regState <= 2'h1;
    end
    if(reset) begin
      regWriteData <= 64'h0;
    end else if(T10) begin
      regWriteData <= io_writeDataIn_bits;
    end
    if(reset) begin
      regWritePtr <= 32'h0;
    end else if(T14) begin
      regWritePtr <= T21;
    end else if(T7) begin
      regWritePtr <= io_basePtr;
    end
    if(reset) begin
      regWriteCount <= 32'h0;
    end else if(T16) begin
      regWriteCount <= T24;
    end else if(T6) begin
      regWriteCount <= 32'h0;
    end
  end
endmodule

module DistVecUpdater(input clk, input reset,
    input  io_start,
    input [31:0] io_distVecBase,
    input [31:0] io_currentLevel,
    output[31:0] io_distVecUpdateCount,
    output io_distVecInds_ready,
    input  io_distVecInds_valid,
    input [31:0] io_distVecInds_bits,
    input  io_writeAddrOut_ready,
    output io_writeAddrOut_valid,
    output[31:0] io_writeAddrOut_bits_addr,
    output[2:0] io_writeAddrOut_bits_size,
    output[7:0] io_writeAddrOut_bits_len,
    output[1:0] io_writeAddrOut_bits_burst,
    output[1:0] io_writeAddrOut_bits_id,
    output io_writeAddrOut_bits_lock,
    output[3:0] io_writeAddrOut_bits_cache,
    output[2:0] io_writeAddrOut_bits_prot,
    output[3:0] io_writeAddrOut_bits_qos,
    input  io_writeDataOut_ready,
    output io_writeDataOut_valid,
    output[31:0] io_writeDataOut_bits_data,
    output[3:0] io_writeDataOut_bits_strb,
    output io_writeDataOut_bits_last,
    output io_writeRespIn_ready,
    input  io_writeRespIn_valid,
    input [1:0] io_writeRespIn_bits_id,
    input [1:0] io_writeRespIn_bits_resp
);

  wire T0;
  reg [1:0] regState;
  wire[1:0] T24;
  wire[1:0] T1;
  wire[1:0] T2;
  wire[1:0] T3;
  wire[1:0] T4;
  wire T5;
  wire T6;
  wire T7;
  wire T8;
  wire T9;
  wire T10;
  wire T11;
  wire T12;
  wire T13;
  wire T14;
  reg [31:0] regCurrentLevel;
  wire[31:0] T25;
  wire[31:0] T15;
  wire T16;
  reg [31:0] regDistVecUpdateAddr;
  wire[31:0] T26;
  wire[34:0] T27;
  wire[34:0] T17;
  wire[34:0] T28;
  wire[34:0] T18;
  wire[34:0] T19;
  wire[34:0] T29;
  reg [31:0] regDistVecBase;
  wire[31:0] T30;
  wire[31:0] T20;
  reg [31:0] regDistVecUpdateCount;
  wire[31:0] T31;
  wire[31:0] T21;
  wire[31:0] T22;
  wire[31:0] T23;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    regState = {1{$random}};
    regCurrentLevel = {1{$random}};
    regDistVecUpdateAddr = {1{$random}};
    regDistVecBase = {1{$random}};
    regDistVecUpdateCount = {1{$random}};
  end
// synthesis translate_on
`endif

  assign io_writeRespIn_ready = T0;
  assign T0 = regState != 2'h0;
  assign T24 = reset ? 2'h0 : T1;
  assign T1 = T13 ? 2'h1 : T2;
  assign T2 = T10 ? 2'h2 : T3;
  assign T3 = T7 ? 2'h0 : T4;
  assign T4 = T5 ? 2'h1 : regState;
  assign T5 = T6 & io_start;
  assign T6 = 2'h0 == regState;
  assign T7 = T9 & T8;
  assign T8 = io_start ^ 1'h1;
  assign T9 = 2'h1 == regState;
  assign T10 = T9 & T11;
  assign T11 = T12 & io_distVecInds_valid;
  assign T12 = T8 ^ 1'h1;
  assign T13 = T14 & io_writeAddrOut_ready;
  assign T14 = 2'h2 == regState;
  assign io_writeDataOut_bits_last = 1'h1;
  assign io_writeDataOut_bits_strb = 4'hf;
  assign io_writeDataOut_bits_data = regCurrentLevel;
  assign T25 = reset ? 32'h0 : T15;
  assign T15 = T6 ? io_currentLevel : regCurrentLevel;
  assign io_writeDataOut_valid = T16;
  assign T16 = regState != 2'h0;
  assign io_writeAddrOut_bits_qos = 4'h0;
  assign io_writeAddrOut_bits_prot = 3'h0;
  assign io_writeAddrOut_bits_cache = 4'h2;
  assign io_writeAddrOut_bits_lock = 1'h0;
  assign io_writeAddrOut_bits_id = 2'h0;
  assign io_writeAddrOut_bits_burst = 2'h1;
  assign io_writeAddrOut_bits_len = 8'h0;
  assign io_writeAddrOut_bits_size = 3'h2;
  assign io_writeAddrOut_bits_addr = regDistVecUpdateAddr;
  assign T26 = T27[5'h1f:1'h0];
  assign T27 = reset ? 35'h0 : T17;
  assign T17 = T9 ? T18 : T28;
  assign T28 = {3'h0, regDistVecUpdateAddr};
  assign T18 = T29 + T19;
  assign T19 = 3'h4 * io_distVecInds_bits;
  assign T29 = {3'h0, regDistVecBase};
  assign T30 = reset ? 32'h0 : T20;
  assign T20 = T6 ? io_distVecBase : regDistVecBase;
  assign io_writeAddrOut_valid = T14;
  assign io_distVecInds_ready = T9;
  assign io_distVecUpdateCount = regDistVecUpdateCount;
  assign T31 = reset ? 32'h0 : T21;
  assign T21 = T13 ? T23 : T22;
  assign T22 = T5 ? 32'h0 : regDistVecUpdateCount;
  assign T23 = regDistVecUpdateCount + 32'h1;

  always @(posedge clk) begin
    if(reset) begin
      regState <= 2'h0;
    end else if(T13) begin
      regState <= 2'h1;
    end else if(T10) begin
      regState <= 2'h2;
    end else if(T7) begin
      regState <= 2'h0;
    end else if(T5) begin
      regState <= 2'h1;
    end
    if(reset) begin
      regCurrentLevel <= 32'h0;
    end else if(T6) begin
      regCurrentLevel <= io_currentLevel;
    end
    regDistVecUpdateAddr <= T26;
    if(reset) begin
      regDistVecBase <= 32'h0;
    end else if(T6) begin
      regDistVecBase <= io_distVecBase;
    end
    if(reset) begin
      regDistVecUpdateCount <= 32'h0;
    end else if(T13) begin
      regDistVecUpdateCount <= T23;
    end else if(T5) begin
      regDistVecUpdateCount <= 32'h0;
    end
  end
endmodule

module RequestGeneratorWrapper(input clk, input reset,
    input  mmap_AWREADY,
    output mmap_AWVALID,
    output[31:0] mmap_AWADDR,
    output[2:0] mmap_AWSIZE,
    output[7:0] mmap_AWLEN,
    output[1:0] mmap_AWBURST,
    output[1:0] mmap_AWID,
    output mmap_AWLOCK,
    output[3:0] mmap_AWCACHE,
    output[2:0] mmap_AWPROT,
    output[3:0] mmap_AWQOS,
    input  mmap_WREADY,
    output mmap_WVALID,
    output[63:0] mmap_WDATA,
    output[7:0] mmap_WSTRB,
    output mmap_WLAST,
    output mmap_BREADY,
    input  mmap_BVALID,
    input [1:0] mmap_BID,
    input [1:0] mmap_BRESP,
    input  mmap_ARREADY,
    output mmap_ARVALID,
    output[31:0] mmap_ARADDR,
    output[2:0] mmap_ARSIZE,
    output[7:0] mmap_ARLEN,
    output[1:0] mmap_ARBURST,
    output[1:0] mmap_ARID,
    output mmap_ARLOCK,
    output[3:0] mmap_ARCACHE,
    output[2:0] mmap_ARPROT,
    output[3:0] mmap_ARQOS,
    output mmap_RREADY,
    input  mmap_RVALID,
    input [63:0] mmap_RDATA,
    input [1:0] mmap_RID,
    input  mmap_RLAST,
    input [1:0] mmap_RRESP,
    input  distVecWrite_AWREADY,
    output distVecWrite_AWVALID,
    output[31:0] distVecWrite_AWADDR,
    output[2:0] distVecWrite_AWSIZE,
    output[7:0] distVecWrite_AWLEN,
    output[1:0] distVecWrite_AWBURST,
    output[1:0] distVecWrite_AWID,
    output distVecWrite_AWLOCK,
    output[3:0] distVecWrite_AWCACHE,
    output[2:0] distVecWrite_AWPROT,
    output[3:0] distVecWrite_AWQOS,
    input  distVecWrite_WREADY,
    output distVecWrite_WVALID,
    output[31:0] distVecWrite_WDATA,
    output[3:0] distVecWrite_WSTRB,
    output distVecWrite_WLAST,
    output distVecWrite_BREADY,
    input  distVecWrite_BVALID,
    input [1:0] distVecWrite_BID,
    input [1:0] distVecWrite_BRESP,
    input  strm_TREADY,
    output strm_TVALID,
    output[63:0] strm_TDATA,
    output[1:0] strm_TDEST,
    output strm_TLAST,
    output[1:0] strm_RRESP,
    output writeDataIn_TREADY,
    input  writeDataIn_TVALID,
    input [63:0] writeDataIn_TDATA,
    output distVecInds_TREADY,
    input  distVecInds_TVALID,
    input [31:0] distVecInds_TDATA,
    input  io_start,
    input [31:0] io_nzCount,
    input [31:0] io_colCount,
    input [31:0] io_colLenStart,
    input [31:0] io_rowIndStart,
    input [31:0] io_dvStart,
    input [31:0] io_writeBase,
    input [31:0] io_distVecBase,
    input [31:0] io_currentLevel,
    input [31:0] io_colLenFullThreshold,
    input [31:0] io_rowIndFullThreshold,
    input [31:0] io_denVecFullThreshold,
    input [31:0] io_colLenDataCount,
    input [31:0] io_rowIndDataCount,
    input [31:0] io_denVecDataCount,
    output[31:0] io_state,
    output[31:0] io_writeState,
    output[31:0] io_writeCount,
    output[31:0] io_distVecUpdateCount
);

  reg  regDenVecFull;
  wire T3;
  wire T0;
  reg  regRowIndFull;
  wire T4;
  wire T1;
  reg  regColLenFull;
  wire T5;
  wire T2;
  wire[31:0] reqgen_io_state;
  wire reqgen_io_readAddr_valid;
  wire[31:0] reqgen_io_readAddr_bits_addr;
  wire[2:0] reqgen_io_readAddr_bits_size;
  wire[7:0] reqgen_io_readAddr_bits_len;
  wire[1:0] reqgen_io_readAddr_bits_burst;
  wire[1:0] reqgen_io_readAddr_bits_id;
  wire reqgen_io_readAddr_bits_lock;
  wire[3:0] reqgen_io_readAddr_bits_cache;
  wire[2:0] reqgen_io_readAddr_bits_prot;
  wire[3:0] reqgen_io_readAddr_bits_qos;
  wire[31:0] writegen_io_state;
  wire[31:0] writegen_io_writeCount;
  wire writegen_io_writeDataIn_ready;
  wire writegen_io_writeAddrOut_valid;
  wire[31:0] writegen_io_writeAddrOut_bits_addr;
  wire[2:0] writegen_io_writeAddrOut_bits_size;
  wire[7:0] writegen_io_writeAddrOut_bits_len;
  wire[1:0] writegen_io_writeAddrOut_bits_burst;
  wire[1:0] writegen_io_writeAddrOut_bits_id;
  wire writegen_io_writeAddrOut_bits_lock;
  wire[3:0] writegen_io_writeAddrOut_bits_cache;
  wire[2:0] writegen_io_writeAddrOut_bits_prot;
  wire[3:0] writegen_io_writeAddrOut_bits_qos;
  wire writegen_io_writeDataOut_valid;
  wire[63:0] writegen_io_writeDataOut_bits_data;
  wire[7:0] writegen_io_writeDataOut_bits_strb;
  wire writegen_io_writeDataOut_bits_last;
  wire writegen_io_writeRespIn_ready;
  wire[31:0] distVecUpdater_io_distVecUpdateCount;
  wire distVecUpdater_io_distVecInds_ready;
  wire distVecUpdater_io_writeAddrOut_valid;
  wire[31:0] distVecUpdater_io_writeAddrOut_bits_addr;
  wire[2:0] distVecUpdater_io_writeAddrOut_bits_size;
  wire[7:0] distVecUpdater_io_writeAddrOut_bits_len;
  wire[1:0] distVecUpdater_io_writeAddrOut_bits_burst;
  wire[1:0] distVecUpdater_io_writeAddrOut_bits_id;
  wire distVecUpdater_io_writeAddrOut_bits_lock;
  wire[3:0] distVecUpdater_io_writeAddrOut_bits_cache;
  wire[2:0] distVecUpdater_io_writeAddrOut_bits_prot;
  wire[3:0] distVecUpdater_io_writeAddrOut_bits_qos;
  wire distVecUpdater_io_writeDataOut_valid;
  wire[31:0] distVecUpdater_io_writeDataOut_bits_data;
  wire[3:0] distVecUpdater_io_writeDataOut_bits_strb;
  wire distVecUpdater_io_writeDataOut_bits_last;
  wire distVecUpdater_io_writeRespIn_ready;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    regDenVecFull = {1{$random}};
    regRowIndFull = {1{$random}};
    regColLenFull = {1{$random}};
  end
// synthesis translate_on
`endif

  assign T3 = reset ? 1'h0 : T0;
  assign T0 = io_denVecFullThreshold <= io_denVecDataCount;
  assign T4 = reset ? 1'h0 : T1;
  assign T1 = io_rowIndFullThreshold <= io_rowIndDataCount;
  assign T5 = reset ? 1'h0 : T2;
  assign T2 = io_colLenFullThreshold <= io_colLenDataCount;
  assign io_distVecUpdateCount = distVecUpdater_io_distVecUpdateCount;
  assign io_writeCount = writegen_io_writeCount;
  assign io_writeState = writegen_io_state;
  assign io_state = reqgen_io_state;
  assign distVecInds_TREADY = distVecUpdater_io_distVecInds_ready;
  assign writeDataIn_TREADY = writegen_io_writeDataIn_ready;
  assign strm_RRESP = mmap_RRESP;
  assign strm_TLAST = mmap_RLAST;
  assign strm_TDEST = mmap_RID;
  assign strm_TDATA = mmap_RDATA;
  assign strm_TVALID = mmap_RVALID;
  assign distVecWrite_BREADY = distVecUpdater_io_writeRespIn_ready;
  assign distVecWrite_WLAST = distVecUpdater_io_writeDataOut_bits_last;
  assign distVecWrite_WSTRB = distVecUpdater_io_writeDataOut_bits_strb;
  assign distVecWrite_WDATA = distVecUpdater_io_writeDataOut_bits_data;
  assign distVecWrite_WVALID = distVecUpdater_io_writeDataOut_valid;
  assign distVecWrite_AWQOS = distVecUpdater_io_writeAddrOut_bits_qos;
  assign distVecWrite_AWPROT = distVecUpdater_io_writeAddrOut_bits_prot;
  assign distVecWrite_AWCACHE = distVecUpdater_io_writeAddrOut_bits_cache;
  assign distVecWrite_AWLOCK = distVecUpdater_io_writeAddrOut_bits_lock;
  assign distVecWrite_AWID = distVecUpdater_io_writeAddrOut_bits_id;
  assign distVecWrite_AWBURST = distVecUpdater_io_writeAddrOut_bits_burst;
  assign distVecWrite_AWLEN = distVecUpdater_io_writeAddrOut_bits_len;
  assign distVecWrite_AWSIZE = distVecUpdater_io_writeAddrOut_bits_size;
  assign distVecWrite_AWADDR = distVecUpdater_io_writeAddrOut_bits_addr;
  assign distVecWrite_AWVALID = distVecUpdater_io_writeAddrOut_valid;
  assign mmap_RREADY = strm_TREADY;
  assign mmap_ARQOS = reqgen_io_readAddr_bits_qos;
  assign mmap_ARPROT = reqgen_io_readAddr_bits_prot;
  assign mmap_ARCACHE = reqgen_io_readAddr_bits_cache;
  assign mmap_ARLOCK = reqgen_io_readAddr_bits_lock;
  assign mmap_ARID = reqgen_io_readAddr_bits_id;
  assign mmap_ARBURST = reqgen_io_readAddr_bits_burst;
  assign mmap_ARLEN = reqgen_io_readAddr_bits_len;
  assign mmap_ARSIZE = reqgen_io_readAddr_bits_size;
  assign mmap_ARADDR = reqgen_io_readAddr_bits_addr;
  assign mmap_ARVALID = reqgen_io_readAddr_valid;
  assign mmap_BREADY = writegen_io_writeRespIn_ready;
  assign mmap_WLAST = writegen_io_writeDataOut_bits_last;
  assign mmap_WSTRB = writegen_io_writeDataOut_bits_strb;
  assign mmap_WDATA = writegen_io_writeDataOut_bits_data;
  assign mmap_WVALID = writegen_io_writeDataOut_valid;
  assign mmap_AWQOS = writegen_io_writeAddrOut_bits_qos;
  assign mmap_AWPROT = writegen_io_writeAddrOut_bits_prot;
  assign mmap_AWCACHE = writegen_io_writeAddrOut_bits_cache;
  assign mmap_AWLOCK = writegen_io_writeAddrOut_bits_lock;
  assign mmap_AWID = writegen_io_writeAddrOut_bits_id;
  assign mmap_AWBURST = writegen_io_writeAddrOut_bits_burst;
  assign mmap_AWLEN = writegen_io_writeAddrOut_bits_len;
  assign mmap_AWSIZE = writegen_io_writeAddrOut_bits_size;
  assign mmap_AWADDR = writegen_io_writeAddrOut_bits_addr;
  assign mmap_AWVALID = writegen_io_writeAddrOut_valid;
  RequestGenerator reqgen(.clk(clk), .reset(reset),
       .io_start( io_start ),
       .io_nzCount( io_nzCount ),
       .io_colCount( io_colCount ),
       .io_colLenStart( io_colLenStart ),
       .io_rowIndStart( io_rowIndStart ),
       .io_dvStart( io_dvStart ),
       .io_disableColLen( regColLenFull ),
       .io_disableRowInd( regRowIndFull ),
       .io_disableDenVec( regDenVecFull ),
       .io_state( reqgen_io_state ),
       .io_readAddr_ready( mmap_ARREADY ),
       .io_readAddr_valid( reqgen_io_readAddr_valid ),
       .io_readAddr_bits_addr( reqgen_io_readAddr_bits_addr ),
       .io_readAddr_bits_size( reqgen_io_readAddr_bits_size ),
       .io_readAddr_bits_len( reqgen_io_readAddr_bits_len ),
       .io_readAddr_bits_burst( reqgen_io_readAddr_bits_burst ),
       .io_readAddr_bits_id( reqgen_io_readAddr_bits_id ),
       .io_readAddr_bits_lock( reqgen_io_readAddr_bits_lock ),
       .io_readAddr_bits_cache( reqgen_io_readAddr_bits_cache ),
       .io_readAddr_bits_prot( reqgen_io_readAddr_bits_prot ),
       .io_readAddr_bits_qos( reqgen_io_readAddr_bits_qos )
  );
  WriteGenerator writegen(.clk(clk), .reset(reset),
       .io_start( io_start ),
       .io_basePtr( io_writeBase ),
       .io_state( writegen_io_state ),
       .io_writeCount( writegen_io_writeCount ),
       .io_writeDataIn_ready( writegen_io_writeDataIn_ready ),
       .io_writeDataIn_valid( writeDataIn_TVALID ),
       .io_writeDataIn_bits( writeDataIn_TDATA ),
       .io_writeAddrOut_ready( mmap_AWREADY ),
       .io_writeAddrOut_valid( writegen_io_writeAddrOut_valid ),
       .io_writeAddrOut_bits_addr( writegen_io_writeAddrOut_bits_addr ),
       .io_writeAddrOut_bits_size( writegen_io_writeAddrOut_bits_size ),
       .io_writeAddrOut_bits_len( writegen_io_writeAddrOut_bits_len ),
       .io_writeAddrOut_bits_burst( writegen_io_writeAddrOut_bits_burst ),
       .io_writeAddrOut_bits_id( writegen_io_writeAddrOut_bits_id ),
       .io_writeAddrOut_bits_lock( writegen_io_writeAddrOut_bits_lock ),
       .io_writeAddrOut_bits_cache( writegen_io_writeAddrOut_bits_cache ),
       .io_writeAddrOut_bits_prot( writegen_io_writeAddrOut_bits_prot ),
       .io_writeAddrOut_bits_qos( writegen_io_writeAddrOut_bits_qos ),
       .io_writeDataOut_ready( mmap_WREADY ),
       .io_writeDataOut_valid( writegen_io_writeDataOut_valid ),
       .io_writeDataOut_bits_data( writegen_io_writeDataOut_bits_data ),
       .io_writeDataOut_bits_strb( writegen_io_writeDataOut_bits_strb ),
       .io_writeDataOut_bits_last( writegen_io_writeDataOut_bits_last ),
       .io_writeRespIn_ready( writegen_io_writeRespIn_ready ),
       .io_writeRespIn_valid( mmap_BVALID ),
       .io_writeRespIn_bits_id( mmap_BID ),
       .io_writeRespIn_bits_resp( mmap_BRESP )
  );
  DistVecUpdater distVecUpdater(.clk(clk), .reset(reset),
       .io_start( io_start ),
       .io_distVecBase( io_distVecBase ),
       .io_currentLevel( io_currentLevel ),
       .io_distVecUpdateCount( distVecUpdater_io_distVecUpdateCount ),
       .io_distVecInds_ready( distVecUpdater_io_distVecInds_ready ),
       .io_distVecInds_valid( distVecInds_TVALID ),
       .io_distVecInds_bits( distVecInds_TDATA ),
       .io_writeAddrOut_ready( distVecWrite_AWREADY ),
       .io_writeAddrOut_valid( distVecUpdater_io_writeAddrOut_valid ),
       .io_writeAddrOut_bits_addr( distVecUpdater_io_writeAddrOut_bits_addr ),
       .io_writeAddrOut_bits_size( distVecUpdater_io_writeAddrOut_bits_size ),
       .io_writeAddrOut_bits_len( distVecUpdater_io_writeAddrOut_bits_len ),
       .io_writeAddrOut_bits_burst( distVecUpdater_io_writeAddrOut_bits_burst ),
       .io_writeAddrOut_bits_id( distVecUpdater_io_writeAddrOut_bits_id ),
       .io_writeAddrOut_bits_lock( distVecUpdater_io_writeAddrOut_bits_lock ),
       .io_writeAddrOut_bits_cache( distVecUpdater_io_writeAddrOut_bits_cache ),
       .io_writeAddrOut_bits_prot( distVecUpdater_io_writeAddrOut_bits_prot ),
       .io_writeAddrOut_bits_qos( distVecUpdater_io_writeAddrOut_bits_qos ),
       .io_writeDataOut_ready( distVecWrite_WREADY ),
       .io_writeDataOut_valid( distVecUpdater_io_writeDataOut_valid ),
       .io_writeDataOut_bits_data( distVecUpdater_io_writeDataOut_bits_data ),
       .io_writeDataOut_bits_strb( distVecUpdater_io_writeDataOut_bits_strb ),
       .io_writeDataOut_bits_last( distVecUpdater_io_writeDataOut_bits_last ),
       .io_writeRespIn_ready( distVecUpdater_io_writeRespIn_ready ),
       .io_writeRespIn_valid( distVecWrite_BVALID ),
       .io_writeRespIn_bits_id( distVecWrite_BID ),
       .io_writeRespIn_bits_resp( distVecWrite_BRESP )
  );

  always @(posedge clk) begin
    if(reset) begin
      regDenVecFull <= 1'h0;
    end else begin
      regDenVecFull <= T0;
    end
    if(reset) begin
      regRowIndFull <= 1'h0;
    end else begin
      regRowIndFull <= T1;
    end
    if(reset) begin
      regColLenFull <= 1'h0;
    end else begin
      regColLenFull <= T2;
    end
  end
endmodule
