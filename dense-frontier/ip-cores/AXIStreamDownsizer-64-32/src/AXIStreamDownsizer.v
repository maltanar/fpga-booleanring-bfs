module ParallelInSerialOut64to32(input clk, input reset,
    input [63:0] io_parIn,
    input  io_parWrEn,
    input [31:0] io_serIn,
    output[31:0] io_serOut,
    input  io_shiftEn
);

  reg [31:0] stages_0;
  wire[31:0] T8;
  wire[31:0] T0;
  wire[31:0] T1;
  wire[31:0] T2;
  reg [31:0] stages_1;
  wire[31:0] T9;
  wire[31:0] T3;
  wire[31:0] T4;
  wire[31:0] T5;
  wire T6;
  wire T7;

`ifndef SYNTHESIS
  integer initvar;
  initial begin
    #0.002;
    stages_0 = {1{$random}};
    stages_1 = {1{$random}};
  end
`endif

  assign io_serOut = stages_0;
  assign T8 = reset ? 32'h0 : T0;
  assign T0 = T6 ? stages_1 : T1;
  assign T1 = io_parWrEn ? T2 : stages_0;
  assign T2 = io_parIn[5'h1f:1'h0];
  assign T9 = reset ? 32'h0 : T3;
  assign T3 = T6 ? io_serIn : T4;
  assign T4 = io_parWrEn ? T5 : stages_1;
  assign T5 = io_parIn[6'h3f:6'h20];
  assign T6 = T7 & io_shiftEn;
  assign T7 = io_parWrEn ^ 1'h1;

  always @(posedge clk) begin
    if(reset) begin
      stages_0 <= 32'h0;
    end else if(T6) begin
      stages_0 <= stages_1;
    end else if(io_parWrEn) begin
      stages_0 <= T2;
    end
    if(reset) begin
      stages_1 <= 32'h0;
    end else if(T6) begin
      stages_1 <= io_serIn;
    end else if(io_parWrEn) begin
      stages_1 <= T5;
    end
  end
endmodule

module AXIStreamDownsizer64to32(input clk, input reset,
    output wide_TREADY,
    input  wide_TVALID,
    input [63:0] wide_TDATA,
    input  narrow_TREADY,
    output narrow_TVALID,
    output[31:0] narrow_TDATA
);

  wire T0;
  wire T1;
  reg [1:0] regState;
  wire[1:0] T22;
  wire[1:0] T2;
  wire[1:0] T3;
  wire[1:0] T4;
  wire[1:0] T5;
  wire T6;
  wire T7;
  wire T8;
  wire T9;
  reg  regShiftCount;
  wire T23;
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
  wire T20;
  wire T21;
  wire[31:0] shiftReg_io_serOut;

`ifndef SYNTHESIS
  integer initvar;
  initial begin
    #0.002;
    regState = {1{$random}};
    regShiftCount = {1{$random}};
  end
`endif

  assign T0 = T1 & narrow_TREADY;
  assign T1 = 2'h1 == regState;
  assign T22 = reset ? 2'h0 : T2;
  assign T2 = T17 ? 2'h0 : T3;
  assign T3 = T14 ? 2'h1 : T4;
  assign T4 = T8 ? 2'h2 : T5;
  assign T5 = T6 ? 2'h1 : regState;
  assign T6 = T7 & wide_TVALID;
  assign T7 = 2'h0 == regState;
  assign T8 = T0 & T9;
  assign T9 = regShiftCount == 1'h0;
  assign T23 = reset ? 1'h0 : T10;
  assign T10 = T14 ? 1'h0 : T11;
  assign T11 = T0 ? T13 : T12;
  assign T12 = T7 ? 1'h0 : regShiftCount;
  assign T13 = regShiftCount + 1'h1;
  assign T14 = T15 & wide_TVALID;
  assign T15 = T16 & narrow_TREADY;
  assign T16 = 2'h2 == regState;
  assign T17 = T15 & T18;
  assign T18 = wide_TVALID ^ 1'h1;
  assign T19 = T14 ? 1'h1 : T7;
  assign narrow_TDATA = shiftReg_io_serOut;
  assign narrow_TVALID = T20;
  assign T20 = T16 ? 1'h1 : T1;
  assign wide_TREADY = T21;
  assign T21 = T14 ? 1'h1 : T7;
  ParallelInSerialOut64to32 shiftReg(.clk(clk), .reset(reset),
       .io_parIn( wide_TDATA ),
       .io_parWrEn( T19 ),
       .io_serIn( 32'h0 ),
       .io_serOut( shiftReg_io_serOut ),
       .io_shiftEn( T0 )
  );

  always @(posedge clk) begin
    if(reset) begin
      regState <= 2'h0;
    end else if(T17) begin
      regState <= 2'h0;
    end else if(T14) begin
      regState <= 2'h1;
    end else if(T8) begin
      regState <= 2'h2;
    end else if(T6) begin
      regState <= 2'h1;
    end
    if(reset) begin
      regShiftCount <= 1'h0;
    end else if(T14) begin
      regShiftCount <= 1'h0;
    end else if(T0) begin
      regShiftCount <= T13;
    end else if(T7) begin
      regShiftCount <= 1'h0;
    end
  end
endmodule
