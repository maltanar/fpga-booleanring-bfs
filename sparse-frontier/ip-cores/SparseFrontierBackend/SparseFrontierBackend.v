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
  reg [2:0] regState;
  wire[2:0] T28;
  wire[2:0] T1;
  wire[2:0] T2;
  wire[2:0] T3;
  wire[2:0] T4;
  wire[2:0] T5;
  wire[2:0] T6;
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
  wire T18;
  wire T19;
  reg [31:0] regCurrentLevel;
  wire[31:0] T29;
  wire[31:0] T20;
  reg [31:0] regDistVecUpdateAddr;
  wire[31:0] T30;
  wire[34:0] T31;
  wire[34:0] T21;
  wire[34:0] T32;
  wire[34:0] T22;
  wire[34:0] T23;
  wire[34:0] T33;
  reg [31:0] regDistVecBase;
  wire[31:0] T34;
  wire[31:0] T24;
  reg [31:0] regDistVecUpdateCount;
  wire[31:0] T35;
  wire[31:0] T25;
  wire[31:0] T26;
  wire[31:0] T27;

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
  assign T0 = 3'h4 == regState;
  assign T28 = reset ? 3'h0 : T1;
  assign T1 = T19 ? 3'h1 : T2;
  assign T2 = T17 ? 3'h4 : T3;
  assign T3 = T15 ? 3'h3 : T4;
  assign T4 = T12 ? 3'h2 : T5;
  assign T5 = T9 ? 3'h0 : T6;
  assign T6 = T7 ? 3'h1 : regState;
  assign T7 = T8 & io_start;
  assign T8 = 3'h0 == regState;
  assign T9 = T11 & T10;
  assign T10 = io_start ^ 1'h1;
  assign T11 = 3'h1 == regState;
  assign T12 = T11 & T13;
  assign T13 = T14 & io_distVecInds_valid;
  assign T14 = T10 ^ 1'h1;
  assign T15 = T16 & io_writeAddrOut_ready;
  assign T16 = 3'h2 == regState;
  assign T17 = T18 & io_writeDataOut_ready;
  assign T18 = 3'h3 == regState;
  assign T19 = T0 & io_writeRespIn_valid;
  assign io_writeDataOut_bits_last = 1'h1;
  assign io_writeDataOut_bits_strb = 4'hf;
  assign io_writeDataOut_bits_data = regCurrentLevel;
  assign T29 = reset ? 32'h0 : T20;
  assign T20 = T8 ? io_currentLevel : regCurrentLevel;
  assign io_writeDataOut_valid = T18;
  assign io_writeAddrOut_bits_qos = 4'h0;
  assign io_writeAddrOut_bits_prot = 3'h0;
  assign io_writeAddrOut_bits_cache = 4'h2;
  assign io_writeAddrOut_bits_lock = 1'h0;
  assign io_writeAddrOut_bits_id = 2'h0;
  assign io_writeAddrOut_bits_burst = 2'h1;
  assign io_writeAddrOut_bits_len = 8'h0;
  assign io_writeAddrOut_bits_size = 3'h2;
  assign io_writeAddrOut_bits_addr = regDistVecUpdateAddr;
  assign T30 = T31[5'h1f:1'h0];
  assign T31 = reset ? 35'h0 : T21;
  assign T21 = T11 ? T22 : T32;
  assign T32 = {3'h0, regDistVecUpdateAddr};
  assign T22 = T33 + T23;
  assign T23 = 3'h4 * io_distVecInds_bits;
  assign T33 = {3'h0, regDistVecBase};
  assign T34 = reset ? 32'h0 : T24;
  assign T24 = T8 ? io_distVecBase : regDistVecBase;
  assign io_writeAddrOut_valid = T16;
  assign io_distVecInds_ready = T11;
  assign io_distVecUpdateCount = regDistVecUpdateCount;
  assign T35 = reset ? 32'h0 : T25;
  assign T25 = T19 ? T27 : T26;
  assign T26 = T7 ? 32'h0 : regDistVecUpdateCount;
  assign T27 = regDistVecUpdateCount + 32'h1;

  always @(posedge clk) begin
    if(reset) begin
      regState <= 3'h0;
    end else if(T19) begin
      regState <= 3'h1;
    end else if(T17) begin
      regState <= 3'h4;
    end else if(T15) begin
      regState <= 3'h3;
    end else if(T12) begin
      regState <= 3'h2;
    end else if(T9) begin
      regState <= 3'h0;
    end else if(T7) begin
      regState <= 3'h1;
    end
    if(reset) begin
      regCurrentLevel <= 32'h0;
    end else if(T8) begin
      regCurrentLevel <= io_currentLevel;
    end
    regDistVecUpdateAddr <= T30;
    if(reset) begin
      regDistVecBase <= 32'h0;
    end else if(T8) begin
      regDistVecBase <= io_distVecBase;
    end
    if(reset) begin
      regDistVecUpdateCount <= 32'h0;
    end else if(T19) begin
      regDistVecUpdateCount <= T27;
    end else if(T7) begin
      regDistVecUpdateCount <= 32'h0;
    end
  end
endmodule

module DistVecToInpVec(input clk, input reset,
    input [31:0] io_distVecCount,
    input [31:0] io_unvisitedValue,
    input  io_start,
    output io_finished,
    output io_distVecInput_ready,
    input  io_distVecInput_valid,
    input [31:0] io_distVecInput_bits,
    input  io_inpVecOutput_ready,
    output io_inpVecOutput_valid,
    output[63:0] io_inpVecOutput_bits
);

  reg [63:0] regOutput;
  wire[63:0] T34;
  wire[63:0] T0;
  wire[63:0] T1;
  wire[63:0] T2;
  wire T3;
  reg [1:0] regState;
  wire[1:0] T35;
  wire[1:0] T4;
  wire[1:0] T5;
  wire[1:0] T6;
  wire[1:0] T7;
  wire T8;
  wire T9;
  wire T10;
  wire readyToFlushOutput;
  reg [31:0] regOutBitCount;
  wire[31:0] T36;
  wire[31:0] T11;
  wire[31:0] T12;
  wire[31:0] T13;
  wire[31:0] T14;
  wire T15;
  wire T16;
  wire T17;
  wire inputFinished;
  reg [31:0] regDistVecElemsLeft;
  wire[31:0] T37;
  wire[31:0] T18;
  wire[31:0] T19;
  wire[31:0] T20;
  wire T21;
  wire[1:0] T22;
  wire T23;
  wire T24;
  wire T25;
  wire[63:0] T26;
  reg [63:0] regMask;
  wire[63:0] T38;
  wire[64:0] T39;
  wire[64:0] T27;
  wire[64:0] T28;
  wire[64:0] T40;
  wire[63:0] T29;
  wire[64:0] T30;
  wire T31;
  wire isVisited;
  wire T32;
  wire T33;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    regOutput = {2{$random}};
    regState = {1{$random}};
    regOutBitCount = {1{$random}};
    regDistVecElemsLeft = {1{$random}};
    regMask = {2{$random}};
  end
// synthesis translate_on
`endif

  assign io_inpVecOutput_bits = regOutput;
  assign T34 = reset ? 64'h0 : T0;
  assign T0 = T32 ? 64'h0 : T1;
  assign T1 = T31 ? T26 : T2;
  assign T2 = T3 ? 64'h0 : regOutput;
  assign T3 = 2'h0 == regState;
  assign T35 = reset ? 2'h0 : T4;
  assign T4 = T23 ? 2'h0 : T5;
  assign T5 = T32 ? T22 : T6;
  assign T6 = T9 ? 2'h2 : T7;
  assign T7 = T8 ? 2'h1 : regState;
  assign T8 = T3 & io_start;
  assign T9 = T21 & T10;
  assign T10 = inputFinished | readyToFlushOutput;
  assign readyToFlushOutput = regOutBitCount == 32'h40;
  assign T36 = reset ? 32'h0 : T11;
  assign T11 = T32 ? 32'h0 : T12;
  assign T12 = T15 ? T14 : T13;
  assign T13 = T3 ? 32'h0 : regOutBitCount;
  assign T14 = regOutBitCount + 32'h1;
  assign T15 = T16 & io_distVecInput_valid;
  assign T16 = T21 & T17;
  assign T17 = T10 ^ 1'h1;
  assign inputFinished = regDistVecElemsLeft == 32'h0;
  assign T37 = reset ? 32'h0 : T18;
  assign T18 = T15 ? T20 : T19;
  assign T19 = T3 ? io_distVecCount : regDistVecElemsLeft;
  assign T20 = regDistVecElemsLeft - 32'h1;
  assign T21 = 2'h1 == regState;
  assign T22 = inputFinished ? 2'h3 : 2'h1;
  assign T23 = T25 & T24;
  assign T24 = io_start ^ 1'h1;
  assign T25 = 2'h3 == regState;
  assign T26 = regOutput | regMask;
  assign T38 = T39[6'h3f:1'h0];
  assign T39 = reset ? 65'h1 : T27;
  assign T27 = T32 ? 65'h1 : T28;
  assign T28 = T15 ? T30 : T40;
  assign T40 = {1'h0, T29};
  assign T29 = T3 ? 64'h1 : regMask;
  assign T30 = regMask << 1'h1;
  assign T31 = T15 & isVisited;
  assign isVisited = io_distVecInput_bits != io_unvisitedValue;
  assign T32 = T33 & io_inpVecOutput_ready;
  assign T33 = 2'h2 == regState;
  assign io_inpVecOutput_valid = T33;
  assign io_distVecInput_ready = T16;
  assign io_finished = T25;

  always @(posedge clk) begin
    if(reset) begin
      regOutput <= 64'h0;
    end else if(T32) begin
      regOutput <= 64'h0;
    end else if(T31) begin
      regOutput <= T26;
    end else if(T3) begin
      regOutput <= 64'h0;
    end
    if(reset) begin
      regState <= 2'h0;
    end else if(T23) begin
      regState <= 2'h0;
    end else if(T32) begin
      regState <= T22;
    end else if(T9) begin
      regState <= 2'h2;
    end else if(T8) begin
      regState <= 2'h1;
    end
    if(reset) begin
      regOutBitCount <= 32'h0;
    end else if(T32) begin
      regOutBitCount <= 32'h0;
    end else if(T15) begin
      regOutBitCount <= T14;
    end else if(T3) begin
      regOutBitCount <= 32'h0;
    end
    if(reset) begin
      regDistVecElemsLeft <= 32'h0;
    end else if(T15) begin
      regDistVecElemsLeft <= T20;
    end else if(T3) begin
      regDistVecElemsLeft <= io_distVecCount;
    end
    regMask <= T38;
  end
endmodule

module BackendThrottler(input clk, input reset,
    input [31:0] io_thresholdT0,
    input [31:0] io_dataCountT0,
    input [31:0] io_thresholdT1,
    input [31:0] io_dataCountT1,
    output io_canProceedT0,
    output io_canProceedT1
);

  wire T0;
  reg [31:0] regThresholdT1;
  wire[31:0] T3;
  reg [31:0] regCountT1;
  wire[31:0] T4;
  wire T1;
  wire T2;
  reg [31:0] regThresholdT0;
  wire[31:0] T5;
  reg [31:0] regCountT0;
  wire[31:0] T6;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    regThresholdT1 = {1{$random}};
    regCountT1 = {1{$random}};
    regThresholdT0 = {1{$random}};
    regCountT0 = {1{$random}};
  end
// synthesis translate_on
`endif

  assign io_canProceedT1 = T0;
  assign T0 = regCountT1 < regThresholdT1;
  assign T3 = reset ? 32'h0 : io_thresholdT1;
  assign T4 = reset ? 32'h0 : io_dataCountT1;
  assign io_canProceedT0 = T1;
  assign T1 = T2 & io_canProceedT1;
  assign T2 = regCountT0 < regThresholdT0;
  assign T5 = reset ? 32'h0 : io_thresholdT0;
  assign T6 = reset ? 32'h0 : io_dataCountT0;

  always @(posedge clk) begin
    if(reset) begin
      regThresholdT1 <= 32'h0;
    end else begin
      regThresholdT1 <= io_thresholdT1;
    end
    if(reset) begin
      regCountT1 <= 32'h0;
    end else begin
      regCountT1 <= io_dataCountT1;
    end
    if(reset) begin
      regThresholdT0 <= 32'h0;
    end else begin
      regThresholdT0 <= io_thresholdT0;
    end
    if(reset) begin
      regCountT0 <= 32'h0;
    end else begin
      regCountT0 <= io_dataCountT0;
    end
  end
endmodule

module FrontierFilter(input clk, input reset,
    input  io_start,
    output io_finished,
    input [31:0] io_distVecCount,
    input [31:0] io_currentLevel,
    output[31:0] io_frontierSize,
    output distVecIn_TREADY,
    input  distVecIn_TVALID,
    input [31:0] distVecIn_TDATA,
    input  frontierOut_TREADY,
    output frontierOut_TVALID,
    output[31:0] frontierOut_TDATA
);

  reg [31:0] regDistVecCount;
  wire[31:0] T34;
  wire[31:0] T0;
  wire[31:0] T1;
  wire[31:0] T2;
  wire T3;
  reg [1:0] regState;
  wire[1:0] T35;
  wire[1:0] T4;
  wire[1:0] T5;
  wire[1:0] T6;
  wire[1:0] T7;
  wire[1:0] T8;
  wire T9;
  wire T10;
  wire T11;
  reg [31:0] regDistVecLeft;
  wire[31:0] T36;
  wire[31:0] T12;
  wire[31:0] T13;
  wire[31:0] T14;
  wire T15;
  wire T16;
  wire T17;
  wire T18;
  wire T19;
  wire T20;
  reg [31:0] regCurrentLevel;
  wire[31:0] T37;
  wire[31:0] T21;
  wire T22;
  wire T23;
  wire T24;
  wire[31:0] T25;
  wire T26;
  wire T27;
  wire[31:0] T28;
  wire T29;
  wire T30;
  reg [31:0] regFrontierSize;
  wire[31:0] T38;
  wire[31:0] T31;
  wire[31:0] T32;
  wire[31:0] T33;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    regDistVecCount = {1{$random}};
    regState = {1{$random}};
    regDistVecLeft = {1{$random}};
    regCurrentLevel = {1{$random}};
    regFrontierSize = {1{$random}};
  end
// synthesis translate_on
`endif

  assign frontierOut_TDATA = regDistVecCount;
  assign T34 = reset ? 32'h0 : T0;
  assign T0 = T29 ? T28 : T1;
  assign T1 = T26 ? T25 : T2;
  assign T2 = T3 ? 32'h0 : regDistVecCount;
  assign T3 = 2'h0 == regState;
  assign T35 = reset ? 2'h0 : T4;
  assign T4 = T22 ? 2'h0 : T5;
  assign T5 = T29 ? 2'h1 : T6;
  assign T6 = T19 ? 2'h2 : T7;
  assign T7 = T10 ? 2'h3 : T8;
  assign T8 = T9 ? 2'h1 : regState;
  assign T9 = T3 & io_start;
  assign T10 = T18 & T11;
  assign T11 = regDistVecLeft == 32'h0;
  assign T36 = reset ? 32'h0 : T12;
  assign T12 = T15 ? T14 : T13;
  assign T13 = T3 ? io_distVecCount : regDistVecLeft;
  assign T14 = regDistVecLeft - 32'h1;
  assign T15 = T16 & distVecIn_TVALID;
  assign T16 = T18 & T17;
  assign T17 = T11 ^ 1'h1;
  assign T18 = 2'h1 == regState;
  assign T19 = T15 & T20;
  assign T20 = distVecIn_TDATA == regCurrentLevel;
  assign T37 = reset ? 32'h0 : T21;
  assign T21 = T3 ? io_currentLevel : regCurrentLevel;
  assign T22 = T24 & T23;
  assign T23 = io_start ^ 1'h1;
  assign T24 = 2'h3 == regState;
  assign T25 = regDistVecCount + 32'h1;
  assign T26 = T15 & T27;
  assign T27 = T20 ^ 1'h1;
  assign T28 = regDistVecCount + 32'h1;
  assign T29 = T30 & frontierOut_TREADY;
  assign T30 = 2'h2 == regState;
  assign frontierOut_TVALID = T30;
  assign distVecIn_TREADY = T16;
  assign io_frontierSize = regFrontierSize;
  assign T38 = reset ? 32'h0 : T31;
  assign T31 = T29 ? T33 : T32;
  assign T32 = T9 ? 32'h0 : regFrontierSize;
  assign T33 = regFrontierSize + 32'h1;
  assign io_finished = T24;

  always @(posedge clk) begin
    if(reset) begin
      regDistVecCount <= 32'h0;
    end else if(T29) begin
      regDistVecCount <= T28;
    end else if(T26) begin
      regDistVecCount <= T25;
    end else if(T3) begin
      regDistVecCount <= 32'h0;
    end
    if(reset) begin
      regState <= 2'h0;
    end else if(T22) begin
      regState <= 2'h0;
    end else if(T29) begin
      regState <= 2'h1;
    end else if(T19) begin
      regState <= 2'h2;
    end else if(T10) begin
      regState <= 2'h3;
    end else if(T9) begin
      regState <= 2'h1;
    end
    if(reset) begin
      regDistVecLeft <= 32'h0;
    end else if(T15) begin
      regDistVecLeft <= T14;
    end else if(T3) begin
      regDistVecLeft <= io_distVecCount;
    end
    if(reset) begin
      regCurrentLevel <= 32'h0;
    end else if(T3) begin
      regCurrentLevel <= io_currentLevel;
    end
    if(reset) begin
      regFrontierSize <= 32'h0;
    end else if(T29) begin
      regFrontierSize <= T33;
    end else if(T9) begin
      regFrontierSize <= 32'h0;
    end
  end
endmodule

module Queue(input clk, input reset,
    output io_enq_ready,
    input  io_enq_valid,
    input [31:0] io_enq_bits,
    input  io_deq_ready,
    output io_deq_valid,
    output[31:0] io_deq_bits,
    output[5:0] io_count
);

  wire[5:0] T0;
  wire[4:0] ptr_diff;
  reg [4:0] R1;
  wire[4:0] T15;
  wire[4:0] T2;
  wire[4:0] T3;
  wire do_deq;
  reg [4:0] R4;
  wire[4:0] T16;
  wire[4:0] T5;
  wire[4:0] T6;
  wire do_enq;
  wire T7;
  wire ptr_match;
  reg  maybe_full;
  wire T17;
  wire T8;
  wire T9;
  wire[31:0] T10;
  reg [31:0] ram [31:0];
  wire[31:0] T11;
  wire T12;
  wire empty;
  wire T13;
  wire T14;
  wire full;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    R1 = {1{$random}};
    R4 = {1{$random}};
    maybe_full = {1{$random}};
    for (initvar = 0; initvar < 32; initvar = initvar+1)
      ram[initvar] = {1{$random}};
  end
// synthesis translate_on
`endif

  assign io_count = T0;
  assign T0 = {T7, ptr_diff};
  assign ptr_diff = R4 - R1;
  assign T15 = reset ? 5'h0 : T2;
  assign T2 = do_deq ? T3 : R1;
  assign T3 = R1 + 5'h1;
  assign do_deq = io_deq_ready & io_deq_valid;
  assign T16 = reset ? 5'h0 : T5;
  assign T5 = do_enq ? T6 : R4;
  assign T6 = R4 + 5'h1;
  assign do_enq = io_enq_ready & io_enq_valid;
  assign T7 = maybe_full & ptr_match;
  assign ptr_match = R4 == R1;
  assign T17 = reset ? 1'h0 : T8;
  assign T8 = T9 ? do_enq : maybe_full;
  assign T9 = do_enq != do_deq;
  assign io_deq_bits = T10;
  assign T10 = ram[R1];
  assign io_deq_valid = T12;
  assign T12 = empty ^ 1'h1;
  assign empty = ptr_match & T13;
  assign T13 = maybe_full ^ 1'h1;
  assign io_enq_ready = T14;
  assign T14 = full ^ 1'h1;
  assign full = ptr_match & maybe_full;

  always @(posedge clk) begin
    if(reset) begin
      R1 <= 5'h0;
    end else if(do_deq) begin
      R1 <= T3;
    end
    if(reset) begin
      R4 <= 5'h0;
    end else if(do_enq) begin
      R4 <= T6;
    end
    if(reset) begin
      maybe_full <= 1'h0;
    end else if(T9) begin
      maybe_full <= do_enq;
    end
    if (do_enq)
      ram[R4] <= io_enq_bits;
  end
endmodule

module AXIStreamOutputMux(
    input  io_sel,
    output strm_TREADY,
    input  strm_TVALID,
    input [31:0] strm_TDATA,
    input  out0_TREADY,
    output out0_TVALID,
    output[31:0] out0_TDATA,
    input  out1_TREADY,
    output out1_TVALID,
    output[31:0] out1_TDATA
);

  wire T0;
  wire T1;
  wire T2;
  wire T3;
  wire T4;
  wire T5;


  assign out1_TDATA = strm_TDATA;
  assign out1_TVALID = T0;
  assign T0 = T1 & strm_TVALID;
  assign T1 = io_sel == 1'h1;
  assign out0_TDATA = strm_TDATA;
  assign out0_TVALID = T2;
  assign T2 = T3 & strm_TVALID;
  assign T3 = io_sel == 1'h0;
  assign strm_TREADY = T4;
  assign T4 = T5 ? out0_TREADY : out1_TREADY;
  assign T5 = io_sel == 1'h0;
endmodule

module NeighborFetcher(input clk, input reset,
    input [31:0] io_rowIndBase,
    input  io_start,
    output[31:0] io_state,
    output[31:0] io_colCount,
    output[31:0] io_nzCount,
    input  io_rowIndReadReqs_ready,
    output io_rowIndReadReqs_valid,
    output[31:0] io_rowIndReadReqs_bits_addr,
    output[2:0] io_rowIndReadReqs_bits_size,
    output[7:0] io_rowIndReadReqs_bits_len,
    output[1:0] io_rowIndReadReqs_bits_burst,
    output[1:0] io_rowIndReadReqs_bits_id,
    output io_rowIndReadReqs_bits_lock,
    output[3:0] io_rowIndReadReqs_bits_cache,
    output[2:0] io_rowIndReadReqs_bits_prot,
    output[3:0] io_rowIndReadReqs_bits_qos,
    output io_rowStartEndIn_ready,
    input  io_rowStartEndIn_valid,
    input [31:0] io_rowStartEndIn_bits,
    input  io_rowIndsMetadata_ready,
    output io_rowIndsMetadata_valid,
    output[31:0] io_rowIndsMetadata_bits
);

  wire[31:0] T0;
  wire[30:0] T1;
  reg [31:0] regElementsLeft;
  wire[31:0] T61;
  wire[31:0] T2;
  wire[31:0] T3;
  wire[31:0] T4;
  reg [31:0] regElementStart;
  wire[31:0] T62;
  wire[34:0] T63;
  wire[34:0] T5;
  wire[34:0] T6;
  wire[34:0] T64;
  wire[31:0] T7;
  wire T8;
  wire T9;
  wire T10;
  wire T11;
  reg [2:0] regState;
  wire[2:0] T65;
  wire[2:0] T12;
  wire[2:0] T13;
  wire[2:0] T14;
  wire[2:0] T15;
  wire[2:0] T16;
  wire[2:0] T17;
  wire[2:0] T18;
  wire[2:0] T19;
  wire T20;
  wire T21;
  wire T22;
  wire T23;
  wire[2:0] T24;
  wire T25;
  wire T26;
  wire T27;
  wire T28;
  wire T29;
  wire T30;
  wire T31;
  wire T32;
  wire[34:0] T33;
  wire[34:0] T66;
  reg [31:0] regRowIndBase;
  wire[31:0] T67;
  wire[31:0] T34;
  wire[34:0] T35;
  wire T36;
  wire[34:0] T68;
  wire[31:0] T37;
  wire[31:0] T69;
  wire[10:0] T38;
  reg [7:0] regBurstElements;
  wire[7:0] T70;
  wire[7:0] T39;
  wire[7:0] T71;
  wire[5:0] T40;
  wire[5:0] T41;
  wire[3:0] T42;
  wire T43;
  wire canDoBurst;
  wire[5:0] T72;
  wire T45;
  wire T46;
  wire T47;
  wire T48;
  wire[31:0] T49;
  wire[31:0] T73;
  wire T50;
  wire T51;
  wire isAligned;
  wire[2:0] T44;
  wire T52;
  wire[7:0] T53;
  reg [7:0] regBurstLen;
  wire[7:0] T74;
  wire[7:0] T54;
  wire[7:0] T75;
  reg [31:0] regTotalNZ;
  wire[31:0] T76;
  wire[31:0] T55;
  wire[31:0] T56;
  wire[31:0] T57;
  wire[31:0] T77;
  reg [31:0] regColCount;
  wire[31:0] T78;
  wire[31:0] T58;
  wire[31:0] T59;
  wire[31:0] T60;
  wire[31:0] T79;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    regElementsLeft = {1{$random}};
    regElementStart = {1{$random}};
    regState = {1{$random}};
    regRowIndBase = {1{$random}};
    regBurstElements = {1{$random}};
    regBurstLen = {1{$random}};
    regTotalNZ = {1{$random}};
    regColCount = {1{$random}};
  end
// synthesis translate_on
`endif

  assign io_rowIndsMetadata_bits = T0;
  assign T0 = {isAligned, T1};
  assign T1 = regElementsLeft[5'h1e:1'h0];
  assign T61 = reset ? 32'h0 : T2;
  assign T2 = T50 ? T49 : T3;
  assign T3 = T48 ? T4 : regElementsLeft;
  assign T4 = io_rowStartEndIn_bits - regElementStart;
  assign T62 = T63[5'h1f:1'h0];
  assign T63 = reset ? 35'h0 : T5;
  assign T5 = T50 ? T68 : T6;
  assign T6 = T36 ? T33 : T64;
  assign T64 = {3'h0, T7};
  assign T7 = T8 ? io_rowStartEndIn_bits : regElementStart;
  assign T8 = T11 & T9;
  assign T9 = T10 ^ 1'h1;
  assign T10 = io_start ^ 1'h1;
  assign T11 = 3'h1 == regState;
  assign T65 = reset ? 3'h0 : T12;
  assign T12 = T50 ? 3'h4 : T13;
  assign T13 = T31 ? 3'h5 : T14;
  assign T14 = T28 ? 3'h1 : T15;
  assign T15 = T26 ? T24 : T16;
  assign T16 = T36 ? 3'h3 : T17;
  assign T17 = T23 ? 3'h2 : T18;
  assign T18 = T22 ? 3'h0 : T19;
  assign T19 = T20 ? 3'h1 : regState;
  assign T20 = T21 & io_start;
  assign T21 = 3'h0 == regState;
  assign T22 = T11 & T10;
  assign T23 = T8 & io_rowStartEndIn_valid;
  assign T24 = T25 ? 3'h1 : 3'h4;
  assign T25 = regElementsLeft == 32'h0;
  assign T26 = T27 & io_rowIndsMetadata_ready;
  assign T27 = 3'h3 == regState;
  assign T28 = T30 & T29;
  assign T29 = regElementsLeft == 32'h0;
  assign T30 = 3'h4 == regState;
  assign T31 = T30 & T32;
  assign T32 = T29 ^ 1'h1;
  assign T33 = T35 + T66;
  assign T66 = {3'h0, regRowIndBase};
  assign T67 = reset ? 32'h0 : T34;
  assign T34 = T20 ? io_rowIndBase : regRowIndBase;
  assign T35 = 3'h4 * regElementStart;
  assign T36 = T48 & io_rowStartEndIn_valid;
  assign T68 = {3'h0, T37};
  assign T37 = regElementStart + T69;
  assign T69 = {21'h0, T38};
  assign T38 = 3'h4 * regBurstElements;
  assign T70 = reset ? 8'h0 : T39;
  assign T39 = T31 ? T71 : regBurstElements;
  assign T71 = {2'h0, T40};
  assign T40 = T45 ? T72 : T41;
  assign T41 = T42 * 2'h2;
  assign T42 = T43 ? 4'h8 : 4'h1;
  assign T43 = isAligned & canDoBurst;
  assign canDoBurst = 32'h10 <= regElementsLeft;
  assign T72 = {2'h0, T42};
  assign T45 = T47 | T46;
  assign T46 = regElementsLeft == 32'h1;
  assign T47 = isAligned ^ 1'h1;
  assign T48 = 3'h2 == regState;
  assign T49 = regElementsLeft - T73;
  assign T73 = {24'h0, regBurstElements};
  assign T50 = T51 & io_rowIndReadReqs_ready;
  assign T51 = 3'h5 == regState;
  assign isAligned = T44 == 3'h0;
  assign T44 = regElementStart[2'h2:1'h0];
  assign io_rowIndsMetadata_valid = T27;
  assign io_rowStartEndIn_ready = T52;
  assign T52 = T48 ? 1'h1 : T8;
  assign io_rowIndReadReqs_bits_qos = 4'h0;
  assign io_rowIndReadReqs_bits_prot = 3'h0;
  assign io_rowIndReadReqs_bits_cache = 4'h2;
  assign io_rowIndReadReqs_bits_lock = 1'h0;
  assign io_rowIndReadReqs_bits_id = 2'h2;
  assign io_rowIndReadReqs_bits_burst = 2'h1;
  assign io_rowIndReadReqs_bits_len = T53;
  assign T53 = regBurstLen - 8'h1;
  assign T74 = reset ? 8'h0 : T54;
  assign T54 = T31 ? T75 : regBurstLen;
  assign T75 = {4'h0, T42};
  assign io_rowIndReadReqs_bits_size = 3'h3;
  assign io_rowIndReadReqs_bits_addr = regElementStart;
  assign io_rowIndReadReqs_valid = T51;
  assign io_nzCount = regTotalNZ;
  assign T76 = reset ? 32'h0 : T55;
  assign T55 = T50 ? T57 : T56;
  assign T56 = T20 ? 32'h0 : regTotalNZ;
  assign T57 = regTotalNZ + T77;
  assign T77 = {24'h0, regBurstElements};
  assign io_colCount = regColCount;
  assign T78 = reset ? 32'h0 : T58;
  assign T58 = T36 ? T60 : T59;
  assign T59 = T20 ? 32'h0 : regColCount;
  assign T60 = regColCount + 32'h1;
  assign io_state = T79;
  assign T79 = {29'h0, regState};

  always @(posedge clk) begin
    if(reset) begin
      regElementsLeft <= 32'h0;
    end else if(T50) begin
      regElementsLeft <= T49;
    end else if(T48) begin
      regElementsLeft <= T4;
    end
    regElementStart <= T62;
    if(reset) begin
      regState <= 3'h0;
    end else if(T50) begin
      regState <= 3'h4;
    end else if(T31) begin
      regState <= 3'h5;
    end else if(T28) begin
      regState <= 3'h1;
    end else if(T26) begin
      regState <= T24;
    end else if(T36) begin
      regState <= 3'h3;
    end else if(T23) begin
      regState <= 3'h2;
    end else if(T22) begin
      regState <= 3'h0;
    end else if(T20) begin
      regState <= 3'h1;
    end
    if(reset) begin
      regRowIndBase <= 32'h0;
    end else if(T20) begin
      regRowIndBase <= io_rowIndBase;
    end
    if(reset) begin
      regBurstElements <= 8'h0;
    end else if(T31) begin
      regBurstElements <= T71;
    end
    if(reset) begin
      regBurstLen <= 8'h0;
    end else if(T31) begin
      regBurstLen <= T75;
    end
    if(reset) begin
      regTotalNZ <= 32'h0;
    end else if(T50) begin
      regTotalNZ <= T57;
    end else if(T20) begin
      regTotalNZ <= 32'h0;
    end
    if(reset) begin
      regColCount <= 32'h0;
    end else if(T36) begin
      regColCount <= T60;
    end else if(T20) begin
      regColCount <= 32'h0;
    end
  end
endmodule

module SparseFrontierBackend(input clk, input reset,
    input [31:0] io_distVecBase,
    input [31:0] io_distVecCount,
    input [31:0] io_colPtrBase,
    input [31:0] io_currentLevel,
    input [31:0] io_rowIndBase,
    output[31:0] io_frontierSize,
    output[31:0] io_nzCount,
    output[31:0] io_distVecWriteCount,
    input [31:0] io_thresholdT0,
    input [31:0] io_dataCountT0,
    input [31:0] io_thresholdT1,
    input [31:0] io_dataCountT1,
    output[31:0] io_state,
    output[31:0] io_ngState,
    output[31:0] io_ngColCount,
    input [31:0] io_ctrl,
    input  aximm32_AWREADY,
    output aximm32_AWVALID,
    output[31:0] aximm32_AWADDR,
    output[2:0] aximm32_AWSIZE,
    output[7:0] aximm32_AWLEN,
    output[1:0] aximm32_AWBURST,
    output[1:0] aximm32_AWID,
    output aximm32_AWLOCK,
    output[3:0] aximm32_AWCACHE,
    output[2:0] aximm32_AWPROT,
    output[3:0] aximm32_AWQOS,
    input  aximm32_WREADY,
    output aximm32_WVALID,
    output[31:0] aximm32_WDATA,
    output[3:0] aximm32_WSTRB,
    output aximm32_WLAST,
    output aximm32_BREADY,
    input  aximm32_BVALID,
    input [1:0] aximm32_BID,
    input [1:0] aximm32_BRESP,
    input  aximm32_ARREADY,
    output aximm32_ARVALID,
    output[31:0] aximm32_ARADDR,
    output[2:0] aximm32_ARSIZE,
    output[7:0] aximm32_ARLEN,
    output[1:0] aximm32_ARBURST,
    output[1:0] aximm32_ARID,
    output aximm32_ARLOCK,
    output[3:0] aximm32_ARCACHE,
    output[2:0] aximm32_ARPROT,
    output[3:0] aximm32_ARQOS,
    output aximm32_RREADY,
    input  aximm32_RVALID,
    input [31:0] aximm32_RDATA,
    input [1:0] aximm32_RID,
    input  aximm32_RLAST,
    input [1:0] aximm32_RRESP,
    input  aximm64_ARREADY,
    output aximm64_ARVALID,
    output[31:0] aximm64_ARADDR,
    output[2:0] aximm64_ARSIZE,
    output[7:0] aximm64_ARLEN,
    output[1:0] aximm64_ARBURST,
    output[1:0] aximm64_ARID,
    output aximm64_ARLOCK,
    output[3:0] aximm64_ARCACHE,
    output[2:0] aximm64_ARPROT,
    output[3:0] aximm64_ARQOS,
    output aximm64_RREADY,
    input  aximm64_RVALID,
    input [63:0] aximm64_RDATA,
    input [1:0] aximm64_RID,
    input  aximm64_RLAST,
    input [1:0] aximm64_RRESP,
    input  readData32_TREADY,
    output readData32_TVALID,
    output[31:0] readData32_TDATA,
    output[1:0] readData32_TDEST,
    output readData32_TLAST,
    output[1:0] readData32_RRESP,
    output distVecIn_TREADY,
    input  distVecIn_TVALID,
    input [31:0] distVecIn_TDATA,
    output rowStartEnd_TREADY,
    input  rowStartEnd_TVALID,
    input [31:0] rowStartEnd_TDATA,
    input  rowIndsData_TREADY,
    output rowIndsData_TVALID,
    output[63:0] rowIndsData_TDATA,
    output[1:0] rowIndsData_TDEST,
    output rowIndsData_TLAST,
    output[1:0] rowIndsData_RRESP,
    input  rowIndsMetadata_TREADY,
    output rowIndsMetadata_TVALID,
    output[31:0] rowIndsMetadata_TDATA,
    output distVecUpdInds_TREADY,
    input  distVecUpdInds_TVALID,
    input [31:0] distVecUpdInds_TDATA,
    input  inpVecOutput_TREADY,
    output inpVecOutput_TVALID,
    output[63:0] inpVecOutput_TDATA
);

  wire regularModeStart;
  wire T0;
  wire enableLevelGen;
  wire startSignal;
  wire T1;
  wire T2;
  wire T3;
  wire T4;
  reg [2:0] regState;
  wire[2:0] T96;
  wire[2:0] T5;
  wire[2:0] T6;
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
  wire[2:0] T17;
  wire[2:0] T18;
  wire T19;
  wire levelGenStart;
  wire T20;
  wire T21;
  wire T22;
  wire T23;
  wire T24;
  wire T25;
  wire T26;
  wire T27;
  wire T28;
  wire distVecNoReqsLeft;
  reg [31:0] regDistVecElemsLeft;
  wire[31:0] T97;
  wire[31:0] T29;
  wire[31:0] T30;
  wire[31:0] T31;
  wire[31:0] T32;
  wire[31:0] T98;
  wire[1:0] maxDistVecBurstSize;
  wire T33;
  wire T34;
  wire T35;
  wire T36;
  wire T37;
  wire T38;
  wire T39;
  wire[31:0] T40;
  wire[31:0] T99;
  wire T41;
  wire T42;
  wire T43;
  wire T44;
  wire T45;
  wire T46;
  wire T47;
  wire T48;
  wire T49;
  wire T50;
  wire T51;
  wire T52;
  wire T53;
  reg [31:0] regFrontierSize;
  wire[31:0] T100;
  wire[31:0] T54;
  wire[31:0] T55;
  wire[31:0] T56;
  wire T57;
  wire T58;
  wire T59;
  wire T60;
  wire T61;
  wire T62;
  wire T63;
  wire T64;
  wire T65;
  wire T66;
  wire T67;
  wire T68;
  wire T69;
  wire T70;
  wire T71;
  wire T72;
  wire T73;
  wire T74;
  wire[1:0] T101;
  wire[7:0] T102;
  wire[1:0] T75;
  wire[1:0] T76;
  wire[1:0] T77;
  wire[1:0] T78;
  wire[1:0] T79;
  wire[31:0] T80;
  wire[31:0] T81;
  wire[31:0] T82;
  reg [31:0] regDistVecPtr;
  wire[31:0] T103;
  wire[31:0] T83;
  wire[31:0] T84;
  wire[31:0] T85;
  wire[31:0] T86;
  wire[31:0] T104;
  wire[4:0] T87;
  wire[31:0] T88;
  wire[31:0] T105;
  wire[4:0] T89;
  wire[31:0] T90;
  reg [31:0] regFrontierIndex;
  wire[31:0] T106;
  wire[34:0] T107;
  wire[34:0] T91;
  wire[34:0] T108;
  wire[34:0] T92;
  reg [31:0] regColPtrBase;
  wire[31:0] T109;
  wire[31:0] T93;
  wire T94;
  wire T95;
  wire[31:0] T110;
  wire[31:0] dvupd_io_distVecUpdateCount;
  wire dvupd_io_distVecInds_ready;
  wire dvupd_io_writeAddrOut_valid;
  wire[31:0] dvupd_io_writeAddrOut_bits_addr;
  wire[2:0] dvupd_io_writeAddrOut_bits_size;
  wire[7:0] dvupd_io_writeAddrOut_bits_len;
  wire[1:0] dvupd_io_writeAddrOut_bits_burst;
  wire[1:0] dvupd_io_writeAddrOut_bits_id;
  wire dvupd_io_writeAddrOut_bits_lock;
  wire[3:0] dvupd_io_writeAddrOut_bits_cache;
  wire[2:0] dvupd_io_writeAddrOut_bits_prot;
  wire[3:0] dvupd_io_writeAddrOut_bits_qos;
  wire dvupd_io_writeDataOut_valid;
  wire[31:0] dvupd_io_writeDataOut_bits_data;
  wire[3:0] dvupd_io_writeDataOut_bits_strb;
  wire dvupd_io_writeDataOut_bits_last;
  wire dvupd_io_writeRespIn_ready;
  wire dv2iv_io_finished;
  wire dv2iv_io_distVecInput_ready;
  wire dv2iv_io_inpVecOutput_valid;
  wire[63:0] dv2iv_io_inpVecOutput_bits;
  wire throttler_io_canProceedT0;
  wire throttler_io_canProceedT1;
  wire frontierFilter_io_finished;
  wire[31:0] frontierFilter_io_frontierSize;
  wire frontierFilter_distVecIn_TREADY;
  wire frontierFilter_frontierOut_TVALID;
  wire[31:0] frontierFilter_frontierOut_TDATA;
  wire frontierQueue_io_enq_ready;
  wire frontierQueue_io_deq_valid;
  wire[31:0] frontierQueue_io_deq_bits;
  wire distVecMux_strm_TREADY;
  wire distVecMux_out0_TVALID;
  wire[31:0] distVecMux_out0_TDATA;
  wire distVecMux_out1_TVALID;
  wire[31:0] distVecMux_out1_TDATA;
  wire[31:0] neighborFetcher_io_state;
  wire[31:0] neighborFetcher_io_colCount;
  wire[31:0] neighborFetcher_io_nzCount;
  wire neighborFetcher_io_rowIndReadReqs_valid;
  wire[31:0] neighborFetcher_io_rowIndReadReqs_bits_addr;
  wire[2:0] neighborFetcher_io_rowIndReadReqs_bits_size;
  wire[7:0] neighborFetcher_io_rowIndReadReqs_bits_len;
  wire[1:0] neighborFetcher_io_rowIndReadReqs_bits_burst;
  wire[1:0] neighborFetcher_io_rowIndReadReqs_bits_id;
  wire neighborFetcher_io_rowIndReadReqs_bits_lock;
  wire[3:0] neighborFetcher_io_rowIndReadReqs_bits_cache;
  wire[2:0] neighborFetcher_io_rowIndReadReqs_bits_prot;
  wire[3:0] neighborFetcher_io_rowIndReadReqs_bits_qos;
  wire neighborFetcher_io_rowStartEndIn_ready;
  wire neighborFetcher_io_rowIndsMetadata_valid;
  wire[31:0] neighborFetcher_io_rowIndsMetadata_bits;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    regState = {1{$random}};
    regDistVecElemsLeft = {1{$random}};
    regFrontierSize = {1{$random}};
    regDistVecPtr = {1{$random}};
    regFrontierIndex = {1{$random}};
    regColPtrBase = {1{$random}};
  end
// synthesis translate_on
`endif

  assign regularModeStart = startSignal & T0;
  assign T0 = enableLevelGen ^ 1'h1;
  assign enableLevelGen = io_ctrl[1'h1:1'h1];
  assign startSignal = io_ctrl[1'h0:1'h0];
  assign T1 = T4 & T2;
  assign T2 = T3 ^ 1'h1;
  assign T3 = throttler_io_canProceedT1 ^ 1'h1;
  assign T4 = 3'h2 == regState;
  assign T96 = reset ? 3'h0 : T5;
  assign T5 = T72 ? 3'h0 : T6;
  assign T6 = T69 ? 3'h1 : T7;
  assign T7 = T63 ? 3'h2 : T8;
  assign T8 = T58 ? 3'h4 : T9;
  assign T9 = T51 ? 3'h5 : T10;
  assign T10 = T49 ? 3'h4 : T11;
  assign T11 = T47 ? 3'h4 : T12;
  assign T12 = T46 ? 3'h3 : T13;
  assign T13 = T45 ? 3'h4 : T14;
  assign T14 = T42 ? 3'h2 : T15;
  assign T15 = T26 ? 3'h2 : T16;
  assign T16 = T24 ? 3'h5 : T17;
  assign T17 = T21 ? 3'h1 : T18;
  assign T18 = T19 ? 3'h6 : regState;
  assign T19 = T20 & levelGenStart;
  assign levelGenStart = startSignal & enableLevelGen;
  assign T20 = 3'h0 == regState;
  assign T21 = T20 & T22;
  assign T22 = T23 & regularModeStart;
  assign T23 = levelGenStart ^ 1'h1;
  assign T24 = T25 & dv2iv_io_finished;
  assign T25 = 3'h6 == regState;
  assign T26 = T41 & T27;
  assign T27 = distVecNoReqsLeft | T28;
  assign T28 = throttler_io_canProceedT0 ^ 1'h1;
  assign distVecNoReqsLeft = regDistVecElemsLeft == 32'h0;
  assign T97 = reset ? 32'h0 : T29;
  assign T29 = T42 ? T40 : T30;
  assign T30 = T34 ? T32 : T31;
  assign T31 = T20 ? io_distVecCount : regDistVecElemsLeft;
  assign T32 = regDistVecElemsLeft - T98;
  assign T98 = {30'h0, maxDistVecBurstSize};
  assign maxDistVecBurstSize = T33 ? 2'h2 : 2'h1;
  assign T33 = 32'h2 <= regDistVecElemsLeft;
  assign T34 = T35 & aximm32_ARREADY;
  assign T35 = T25 & T36;
  assign T36 = T39 & T37;
  assign T37 = T38 & throttler_io_canProceedT0;
  assign T38 = distVecNoReqsLeft ^ 1'h1;
  assign T39 = dv2iv_io_finished ^ 1'h1;
  assign T40 = regDistVecElemsLeft - T99;
  assign T99 = {30'h0, maxDistVecBurstSize};
  assign T41 = 3'h1 == regState;
  assign T42 = T43 & aximm32_ARREADY;
  assign T43 = T41 & T44;
  assign T44 = T27 ^ 1'h1;
  assign T45 = T4 & T3;
  assign T46 = T1 & frontierQueue_io_deq_valid;
  assign T47 = T1 & T48;
  assign T48 = frontierQueue_io_deq_valid ^ 1'h1;
  assign T49 = T50 & aximm32_ARREADY;
  assign T50 = 3'h3 == regState;
  assign T51 = T57 & T52;
  assign T52 = frontierFilter_io_finished & T53;
  assign T53 = regFrontierSize == neighborFetcher_io_colCount;
  assign T100 = reset ? 32'h0 : T54;
  assign T54 = T46 ? T56 : T55;
  assign T55 = T21 ? 32'h0 : regFrontierSize;
  assign T56 = regFrontierSize + 32'h1;
  assign T57 = 3'h4 == regState;
  assign T58 = T57 & T59;
  assign T59 = T62 & T60;
  assign T60 = frontierFilter_io_finished & T61;
  assign T61 = regFrontierSize == frontierFilter_io_frontierSize;
  assign T62 = T52 ^ 1'h1;
  assign T63 = T57 & T64;
  assign T64 = T67 & T65;
  assign T65 = frontierFilter_io_finished & T66;
  assign T66 = T61 ^ 1'h1;
  assign T67 = T68 ^ 1'h1;
  assign T68 = T52 | T60;
  assign T69 = T57 & T70;
  assign T70 = T71 ^ 1'h1;
  assign T71 = T68 | T65;
  assign T72 = T74 & T73;
  assign T73 = startSignal ^ 1'h1;
  assign T74 = 3'h5 == regState;
  assign inpVecOutput_TDATA = dv2iv_io_inpVecOutput_bits;
  assign inpVecOutput_TVALID = dv2iv_io_inpVecOutput_valid;
  assign distVecUpdInds_TREADY = dvupd_io_distVecInds_ready;
  assign rowIndsMetadata_TDATA = neighborFetcher_io_rowIndsMetadata_bits;
  assign rowIndsMetadata_TVALID = neighborFetcher_io_rowIndsMetadata_valid;
  assign rowIndsData_RRESP = aximm64_RRESP;
  assign rowIndsData_TLAST = aximm64_RLAST;
  assign rowIndsData_TDEST = aximm64_RID;
  assign rowIndsData_TDATA = aximm64_RDATA;
  assign rowIndsData_TVALID = aximm64_RVALID;
  assign rowStartEnd_TREADY = neighborFetcher_io_rowStartEndIn_ready;
  assign distVecIn_TREADY = distVecMux_strm_TREADY;
  assign readData32_RRESP = aximm32_RRESP;
  assign readData32_TLAST = aximm32_RLAST;
  assign readData32_TDEST = aximm32_RID;
  assign readData32_TDATA = aximm32_RDATA;
  assign readData32_TVALID = aximm32_RVALID;
  assign aximm64_RREADY = rowIndsData_TREADY;
  assign aximm64_ARQOS = neighborFetcher_io_rowIndReadReqs_bits_qos;
  assign aximm64_ARPROT = neighborFetcher_io_rowIndReadReqs_bits_prot;
  assign aximm64_ARCACHE = neighborFetcher_io_rowIndReadReqs_bits_cache;
  assign aximm64_ARLOCK = neighborFetcher_io_rowIndReadReqs_bits_lock;
  assign aximm64_ARID = neighborFetcher_io_rowIndReadReqs_bits_id;
  assign aximm64_ARBURST = neighborFetcher_io_rowIndReadReqs_bits_burst;
  assign aximm64_ARLEN = neighborFetcher_io_rowIndReadReqs_bits_len;
  assign aximm64_ARSIZE = neighborFetcher_io_rowIndReadReqs_bits_size;
  assign aximm64_ARADDR = neighborFetcher_io_rowIndReadReqs_bits_addr;
  assign aximm64_ARVALID = neighborFetcher_io_rowIndReadReqs_valid;
  assign aximm32_RREADY = readData32_TREADY;
  assign aximm32_ARQOS = 4'h0;
  assign aximm32_ARPROT = 3'h0;
  assign aximm32_ARCACHE = 4'h2;
  assign aximm32_ARLOCK = 1'h0;
  assign aximm32_ARID = T101;
  assign T101 = {1'h0, T50};
  assign aximm32_ARBURST = 2'h1;
  assign aximm32_ARLEN = T102;
  assign T102 = {6'h0, T75};
  assign T75 = T50 ? 2'h1 : T76;
  assign T76 = T43 ? T79 : T77;
  assign T77 = T35 ? T78 : 2'h0;
  assign T78 = maxDistVecBurstSize - 2'h1;
  assign T79 = maxDistVecBurstSize - 2'h1;
  assign aximm32_ARSIZE = 3'h2;
  assign aximm32_ARADDR = T80;
  assign T80 = T50 ? T90 : T81;
  assign T81 = T43 ? regDistVecPtr : T82;
  assign T82 = T35 ? regDistVecPtr : 32'h0;
  assign T103 = reset ? 32'h0 : T83;
  assign T83 = T42 ? T88 : T84;
  assign T84 = T34 ? T86 : T85;
  assign T85 = T20 ? io_distVecBase : regDistVecPtr;
  assign T86 = regDistVecPtr + T104;
  assign T104 = {27'h0, T87};
  assign T87 = 3'h4 * maxDistVecBurstSize;
  assign T88 = regDistVecPtr + T105;
  assign T105 = {27'h0, T89};
  assign T89 = 3'h4 * maxDistVecBurstSize;
  assign T90 = regColPtrBase + regFrontierIndex;
  assign T106 = T107[5'h1f:1'h0];
  assign T107 = reset ? 35'h0 : T91;
  assign T91 = T1 ? T92 : T108;
  assign T108 = {3'h0, regFrontierIndex};
  assign T92 = frontierQueue_io_deq_bits * 3'h4;
  assign T109 = reset ? 32'h0 : T93;
  assign T93 = T20 ? io_colPtrBase : regColPtrBase;
  assign aximm32_ARVALID = T94;
  assign T94 = T50 ? 1'h1 : T95;
  assign T95 = T43 ? 1'h1 : T35;
  assign aximm32_BREADY = dvupd_io_writeRespIn_ready;
  assign aximm32_WLAST = dvupd_io_writeDataOut_bits_last;
  assign aximm32_WSTRB = dvupd_io_writeDataOut_bits_strb;
  assign aximm32_WDATA = dvupd_io_writeDataOut_bits_data;
  assign aximm32_WVALID = dvupd_io_writeDataOut_valid;
  assign aximm32_AWQOS = dvupd_io_writeAddrOut_bits_qos;
  assign aximm32_AWPROT = dvupd_io_writeAddrOut_bits_prot;
  assign aximm32_AWCACHE = dvupd_io_writeAddrOut_bits_cache;
  assign aximm32_AWLOCK = dvupd_io_writeAddrOut_bits_lock;
  assign aximm32_AWID = dvupd_io_writeAddrOut_bits_id;
  assign aximm32_AWBURST = dvupd_io_writeAddrOut_bits_burst;
  assign aximm32_AWLEN = dvupd_io_writeAddrOut_bits_len;
  assign aximm32_AWSIZE = dvupd_io_writeAddrOut_bits_size;
  assign aximm32_AWADDR = dvupd_io_writeAddrOut_bits_addr;
  assign aximm32_AWVALID = dvupd_io_writeAddrOut_valid;
  assign io_ngColCount = neighborFetcher_io_colCount;
  assign io_ngState = neighborFetcher_io_state;
  assign io_state = T110;
  assign T110 = {29'h0, regState};
  assign io_distVecWriteCount = dvupd_io_distVecUpdateCount;
  assign io_nzCount = neighborFetcher_io_nzCount;
  assign io_frontierSize = regFrontierSize;
  DistVecUpdater dvupd(.clk(clk), .reset(reset),
       .io_start( levelGenStart ),
       .io_distVecBase( io_distVecBase ),
       .io_currentLevel( io_currentLevel ),
       .io_distVecUpdateCount( dvupd_io_distVecUpdateCount ),
       .io_distVecInds_ready( dvupd_io_distVecInds_ready ),
       .io_distVecInds_valid( distVecUpdInds_TVALID ),
       .io_distVecInds_bits( distVecUpdInds_TDATA ),
       .io_writeAddrOut_ready( aximm32_AWREADY ),
       .io_writeAddrOut_valid( dvupd_io_writeAddrOut_valid ),
       .io_writeAddrOut_bits_addr( dvupd_io_writeAddrOut_bits_addr ),
       .io_writeAddrOut_bits_size( dvupd_io_writeAddrOut_bits_size ),
       .io_writeAddrOut_bits_len( dvupd_io_writeAddrOut_bits_len ),
       .io_writeAddrOut_bits_burst( dvupd_io_writeAddrOut_bits_burst ),
       .io_writeAddrOut_bits_id( dvupd_io_writeAddrOut_bits_id ),
       .io_writeAddrOut_bits_lock( dvupd_io_writeAddrOut_bits_lock ),
       .io_writeAddrOut_bits_cache( dvupd_io_writeAddrOut_bits_cache ),
       .io_writeAddrOut_bits_prot( dvupd_io_writeAddrOut_bits_prot ),
       .io_writeAddrOut_bits_qos( dvupd_io_writeAddrOut_bits_qos ),
       .io_writeDataOut_ready( aximm32_WREADY ),
       .io_writeDataOut_valid( dvupd_io_writeDataOut_valid ),
       .io_writeDataOut_bits_data( dvupd_io_writeDataOut_bits_data ),
       .io_writeDataOut_bits_strb( dvupd_io_writeDataOut_bits_strb ),
       .io_writeDataOut_bits_last( dvupd_io_writeDataOut_bits_last ),
       .io_writeRespIn_ready( dvupd_io_writeRespIn_ready ),
       .io_writeRespIn_valid( aximm32_BVALID ),
       .io_writeRespIn_bits_id( aximm32_BID ),
       .io_writeRespIn_bits_resp( aximm32_BRESP )
  );
  DistVecToInpVec dv2iv(.clk(clk), .reset(reset),
       .io_distVecCount( io_distVecCount ),
       .io_unvisitedValue( 32'hffffffff ),
       .io_start( levelGenStart ),
       .io_finished( dv2iv_io_finished ),
       .io_distVecInput_ready( dv2iv_io_distVecInput_ready ),
       .io_distVecInput_valid( distVecMux_out1_TVALID ),
       .io_distVecInput_bits( distVecMux_out1_TDATA ),
       .io_inpVecOutput_ready( inpVecOutput_TREADY ),
       .io_inpVecOutput_valid( dv2iv_io_inpVecOutput_valid ),
       .io_inpVecOutput_bits( dv2iv_io_inpVecOutput_bits )
  );
  BackendThrottler throttler(.clk(clk), .reset(reset),
       .io_thresholdT0( io_thresholdT0 ),
       .io_dataCountT0( io_dataCountT0 ),
       .io_thresholdT1( io_thresholdT1 ),
       .io_dataCountT1( io_dataCountT1 ),
       .io_canProceedT0( throttler_io_canProceedT0 ),
       .io_canProceedT1( throttler_io_canProceedT1 )
  );
  FrontierFilter frontierFilter(.clk(clk), .reset(reset),
       .io_start( regularModeStart ),
       .io_finished( frontierFilter_io_finished ),
       .io_distVecCount( io_distVecCount ),
       .io_currentLevel( io_currentLevel ),
       .io_frontierSize( frontierFilter_io_frontierSize ),
       .distVecIn_TREADY( frontierFilter_distVecIn_TREADY ),
       .distVecIn_TVALID( distVecMux_out0_TVALID ),
       .distVecIn_TDATA( distVecMux_out0_TDATA ),
       .frontierOut_TREADY( frontierQueue_io_enq_ready ),
       .frontierOut_TVALID( frontierFilter_frontierOut_TVALID ),
       .frontierOut_TDATA( frontierFilter_frontierOut_TDATA )
  );
  Queue frontierQueue(.clk(clk), .reset(reset),
       .io_enq_ready( frontierQueue_io_enq_ready ),
       .io_enq_valid( frontierFilter_frontierOut_TVALID ),
       .io_enq_bits( frontierFilter_frontierOut_TDATA ),
       .io_deq_ready( T1 ),
       .io_deq_valid( frontierQueue_io_deq_valid ),
       .io_deq_bits( frontierQueue_io_deq_bits )
       //.io_count(  )
  );
  AXIStreamOutputMux distVecMux(
       .io_sel( enableLevelGen ),
       .strm_TREADY( distVecMux_strm_TREADY ),
       .strm_TVALID( distVecIn_TVALID ),
       .strm_TDATA( distVecIn_TDATA ),
       .out0_TREADY( frontierFilter_distVecIn_TREADY ),
       .out0_TVALID( distVecMux_out0_TVALID ),
       .out0_TDATA( distVecMux_out0_TDATA ),
       .out1_TREADY( dv2iv_io_distVecInput_ready ),
       .out1_TVALID( distVecMux_out1_TVALID ),
       .out1_TDATA( distVecMux_out1_TDATA )
  );
  NeighborFetcher neighborFetcher(.clk(clk), .reset(reset),
       .io_rowIndBase( io_rowIndBase ),
       .io_start( regularModeStart ),
       .io_state( neighborFetcher_io_state ),
       .io_colCount( neighborFetcher_io_colCount ),
       .io_nzCount( neighborFetcher_io_nzCount ),
       .io_rowIndReadReqs_ready( aximm64_ARREADY ),
       .io_rowIndReadReqs_valid( neighborFetcher_io_rowIndReadReqs_valid ),
       .io_rowIndReadReqs_bits_addr( neighborFetcher_io_rowIndReadReqs_bits_addr ),
       .io_rowIndReadReqs_bits_size( neighborFetcher_io_rowIndReadReqs_bits_size ),
       .io_rowIndReadReqs_bits_len( neighborFetcher_io_rowIndReadReqs_bits_len ),
       .io_rowIndReadReqs_bits_burst( neighborFetcher_io_rowIndReadReqs_bits_burst ),
       .io_rowIndReadReqs_bits_id( neighborFetcher_io_rowIndReadReqs_bits_id ),
       .io_rowIndReadReqs_bits_lock( neighborFetcher_io_rowIndReadReqs_bits_lock ),
       .io_rowIndReadReqs_bits_cache( neighborFetcher_io_rowIndReadReqs_bits_cache ),
       .io_rowIndReadReqs_bits_prot( neighborFetcher_io_rowIndReadReqs_bits_prot ),
       .io_rowIndReadReqs_bits_qos( neighborFetcher_io_rowIndReadReqs_bits_qos ),
       .io_rowStartEndIn_ready( neighborFetcher_io_rowStartEndIn_ready ),
       .io_rowStartEndIn_valid( rowStartEnd_TVALID ),
       .io_rowStartEndIn_bits( rowStartEnd_TDATA ),
       .io_rowIndsMetadata_ready( rowIndsMetadata_TREADY ),
       .io_rowIndsMetadata_valid( neighborFetcher_io_rowIndsMetadata_valid ),
       .io_rowIndsMetadata_bits( neighborFetcher_io_rowIndsMetadata_bits )
  );

  always @(posedge clk) begin
    if(reset) begin
      regState <= 3'h0;
    end else if(T72) begin
      regState <= 3'h0;
    end else if(T69) begin
      regState <= 3'h1;
    end else if(T63) begin
      regState <= 3'h2;
    end else if(T58) begin
      regState <= 3'h4;
    end else if(T51) begin
      regState <= 3'h5;
    end else if(T49) begin
      regState <= 3'h4;
    end else if(T47) begin
      regState <= 3'h4;
    end else if(T46) begin
      regState <= 3'h3;
    end else if(T45) begin
      regState <= 3'h4;
    end else if(T42) begin
      regState <= 3'h2;
    end else if(T26) begin
      regState <= 3'h2;
    end else if(T24) begin
      regState <= 3'h5;
    end else if(T21) begin
      regState <= 3'h1;
    end else if(T19) begin
      regState <= 3'h6;
    end
    if(reset) begin
      regDistVecElemsLeft <= 32'h0;
    end else if(T42) begin
      regDistVecElemsLeft <= T40;
    end else if(T34) begin
      regDistVecElemsLeft <= T32;
    end else if(T20) begin
      regDistVecElemsLeft <= io_distVecCount;
    end
    if(reset) begin
      regFrontierSize <= 32'h0;
    end else if(T46) begin
      regFrontierSize <= T56;
    end else if(T21) begin
      regFrontierSize <= 32'h0;
    end
    if(reset) begin
      regDistVecPtr <= 32'h0;
    end else if(T42) begin
      regDistVecPtr <= T88;
    end else if(T34) begin
      regDistVecPtr <= T86;
    end else if(T20) begin
      regDistVecPtr <= io_distVecBase;
    end
    regFrontierIndex <= T106;
    if(reset) begin
      regColPtrBase <= 32'h0;
    end else if(T20) begin
      regColPtrBase <= io_colPtrBase;
    end
  end
endmodule
