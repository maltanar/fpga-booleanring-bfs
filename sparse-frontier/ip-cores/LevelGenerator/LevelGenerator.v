module LevelGenerator(input clk, input reset,
    input  io_start,
    input [31:0] io_bitCount,
    output io_finished,
    output[31:0] io_writeCount,
    output oldData_TREADY,
    input  oldData_TVALID,
    input [63:0] oldData_TDATA,
    output newData_TREADY,
    input  newData_TVALID,
    input [63:0] newData_TDATA,
    input  writeIndices_TREADY,
    output writeIndices_TVALID,
    output[31:0] writeIndices_TDATA,
    input  newDataCopy_TREADY,
    output newDataCopy_TVALID,
    output[63:0] newDataCopy_TDATA
);

  reg [63:0] regNewData;
  wire[63:0] T58;
  wire[63:0] T0;
  wire[63:0] T1;
  wire T2;
  wire T3;
  reg [2:0] regState;
  wire[2:0] T59;
  wire[2:0] T4;
  wire[2:0] T5;
  wire[2:0] T6;
  wire[2:0] T7;
  wire[2:0] T8;
  wire[2:0] T9;
  wire[2:0] T10;
  wire[2:0] T11;
  wire T12;
  wire T13;
  wire T14;
  wire T15;
  reg [31:0] regBitCount;
  wire[31:0] T60;
  wire[31:0] T16;
  wire[31:0] T17;
  wire[31:0] T18;
  wire T19;
  wire T20;
  wire T21;
  wire T22;
  wire T23;
  wire T24;
  wire T25;
  wire T26;
  wire T27;
  reg [31:0] regShiftCounter;
  wire[31:0] T61;
  wire[31:0] T28;
  wire[31:0] T29;
  wire[31:0] T30;
  wire T31;
  wire[31:0] T32;
  wire T33;
  wire T34;
  wire T35;
  wire T36;
  wire[63:0] T62;
  wire[62:0] T37;
  wire T38;
  wire T39;
  wire T40;
  wire T41;
  wire T42;
  wire T43;
  wire T44;
  reg [63:0] regOldData;
  wire[63:0] T63;
  wire[63:0] T45;
  wire[63:0] T46;
  wire[63:0] T64;
  wire[62:0] T47;
  wire T48;
  wire T49;
  reg [31:0] regWriteIndex;
  wire[31:0] T65;
  wire[31:0] T50;
  wire[31:0] T51;
  wire[31:0] T52;
  wire T53;
  reg [31:0] regWriteCount;
  wire[31:0] T66;
  wire[31:0] T54;
  wire[31:0] T55;
  wire[31:0] T56;
  wire T57;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    regNewData = {2{$random}};
    regState = {1{$random}};
    regBitCount = {1{$random}};
    regShiftCounter = {1{$random}};
    regOldData = {2{$random}};
    regWriteIndex = {1{$random}};
    regWriteCount = {1{$random}};
  end
// synthesis translate_on
`endif

  assign newDataCopy_TDATA = regNewData;
  assign T58 = reset ? 64'h0 : T0;
  assign T0 = T38 ? T62 : T1;
  assign T1 = T2 ? newData_TDATA : regNewData;
  assign T2 = T3 & newData_TVALID;
  assign T3 = 3'h3 == regState;
  assign T59 = reset ? 3'h0 : T4;
  assign T4 = T34 ? 3'h0 : T5;
  assign T5 = T26 ? 3'h1 : T6;
  assign T6 = T24 ? 3'h5 : T7;
  assign T7 = T2 ? 3'h4 : T8;
  assign T8 = T22 ? 3'h3 : T9;
  assign T9 = T20 ? 3'h2 : T10;
  assign T10 = T14 ? 3'h6 : T11;
  assign T11 = T12 ? 3'h1 : regState;
  assign T12 = T13 & io_start;
  assign T13 = 3'h0 == regState;
  assign T14 = T19 & T15;
  assign T15 = regBitCount == 32'h0;
  assign T60 = reset ? 32'h0 : T16;
  assign T16 = T38 ? T18 : T17;
  assign T17 = T13 ? io_bitCount : regBitCount;
  assign T18 = regBitCount - 32'h1;
  assign T19 = 3'h1 == regState;
  assign T20 = T19 & T21;
  assign T21 = T15 ^ 1'h1;
  assign T22 = T23 & oldData_TVALID;
  assign T23 = 3'h2 == regState;
  assign T24 = T25 & newDataCopy_TREADY;
  assign T25 = 3'h4 == regState;
  assign T26 = T33 & T27;
  assign T27 = regShiftCounter == 32'h0;
  assign T61 = reset ? 32'h0 : T28;
  assign T28 = T38 ? T32 : T29;
  assign T29 = T20 ? T30 : regShiftCounter;
  assign T30 = T31 ? regBitCount : 32'h40;
  assign T31 = regBitCount < 32'h40;
  assign T32 = regShiftCounter - 32'h1;
  assign T33 = 3'h5 == regState;
  assign T34 = T36 & T35;
  assign T35 = io_start ^ 1'h1;
  assign T36 = 3'h6 == regState;
  assign T62 = {1'h0, T37};
  assign T37 = regNewData >> 1'h1;
  assign T38 = T48 & T39;
  assign T39 = writeIndices_TREADY | T40;
  assign T40 = T41 ^ 1'h1;
  assign T41 = T43 & T42;
  assign T42 = regNewData[1'h0:1'h0];
  assign T43 = T44 ^ 1'h1;
  assign T44 = regOldData[1'h0:1'h0];
  assign T63 = reset ? 64'h0 : T45;
  assign T45 = T38 ? T64 : T46;
  assign T46 = T22 ? oldData_TDATA : regOldData;
  assign T64 = {1'h0, T47};
  assign T47 = regOldData >> 1'h1;
  assign T48 = T33 & T49;
  assign T49 = T27 ^ 1'h1;
  assign newDataCopy_TVALID = T25;
  assign writeIndices_TDATA = regWriteIndex;
  assign T65 = reset ? 32'h0 : T50;
  assign T50 = T38 ? T52 : T51;
  assign T51 = T13 ? 32'h0 : regWriteIndex;
  assign T52 = regWriteIndex + 32'h1;
  assign writeIndices_TVALID = T53;
  assign T53 = T48 ? T41 : 1'h0;
  assign newData_TREADY = T3;
  assign oldData_TREADY = T23;
  assign io_writeCount = regWriteCount;
  assign T66 = reset ? 32'h0 : T54;
  assign T54 = T57 ? T56 : T55;
  assign T55 = T12 ? 32'h0 : regWriteCount;
  assign T56 = regWriteCount + 32'h1;
  assign T57 = T38 & T41;
  assign io_finished = T36;

  always @(posedge clk) begin
    if(reset) begin
      regNewData <= 64'h0;
    end else if(T38) begin
      regNewData <= T62;
    end else if(T2) begin
      regNewData <= newData_TDATA;
    end
    if(reset) begin
      regState <= 3'h0;
    end else if(T34) begin
      regState <= 3'h0;
    end else if(T26) begin
      regState <= 3'h1;
    end else if(T24) begin
      regState <= 3'h5;
    end else if(T2) begin
      regState <= 3'h4;
    end else if(T22) begin
      regState <= 3'h3;
    end else if(T20) begin
      regState <= 3'h2;
    end else if(T14) begin
      regState <= 3'h6;
    end else if(T12) begin
      regState <= 3'h1;
    end
    if(reset) begin
      regBitCount <= 32'h0;
    end else if(T38) begin
      regBitCount <= T18;
    end else if(T13) begin
      regBitCount <= io_bitCount;
    end
    if(reset) begin
      regShiftCounter <= 32'h0;
    end else if(T38) begin
      regShiftCounter <= T32;
    end else if(T20) begin
      regShiftCounter <= T30;
    end
    if(reset) begin
      regOldData <= 64'h0;
    end else if(T38) begin
      regOldData <= T64;
    end else if(T22) begin
      regOldData <= oldData_TDATA;
    end
    if(reset) begin
      regWriteIndex <= 32'h0;
    end else if(T38) begin
      regWriteIndex <= T52;
    end else if(T13) begin
      regWriteIndex <= 32'h0;
    end
    if(reset) begin
      regWriteCount <= 32'h0;
    end else if(T57) begin
      regWriteCount <= T56;
    end else if(T12) begin
      regWriteCount <= 32'h0;
    end
  end
endmodule
