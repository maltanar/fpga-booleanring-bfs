module StreamDeltaGen(input clk, input reset,
    output samples_TREADY,
    input  samples_TVALID,
    input [31:0] samples_TDATA,
    input  deltas_TREADY,
    output deltas_TVALID,
    output[31:0] deltas_TDATA
);

  wire[31:0] sampleDelta;
  reg [31:0] regSample1;
  wire[31:0] T19;
  wire[31:0] T0;
  wire[31:0] T1;
  wire T2;
  wire T3;
  reg [1:0] regState;
  wire[1:0] T20;
  wire[1:0] T4;
  wire[1:0] T5;
  wire[1:0] T6;
  wire T7;
  wire T8;
  wire T9;
  wire T10;
  wire T11;
  wire T12;
  wire T13;
  reg [31:0] regSample2;
  wire[31:0] T21;
  wire[31:0] T14;
  wire[31:0] T15;
  wire[31:0] T16;
  wire T17;
  wire T18;

`ifndef SYNTHESIS
  integer initvar;
  initial begin
    #0.002;
    regSample1 = {1{$random}};
    regState = {1{$random}};
    regSample2 = {1{$random}};
  end
`endif

  assign deltas_TDATA = sampleDelta;
  assign sampleDelta = regSample2 - regSample1;
  assign T19 = reset ? 32'h0 : T0;
  assign T0 = T13 ? regSample2 : T1;
  assign T1 = T2 ? regSample2 : regSample1;
  assign T2 = T3 & samples_TVALID;
  assign T3 = 2'h1 == regState;
  assign T20 = reset ? 2'h0 : T4;
  assign T4 = T9 ? 2'h1 : T5;
  assign T5 = T2 ? 2'h3 : T6;
  assign T6 = T7 ? 2'h1 : regState;
  assign T7 = T8 & samples_TVALID;
  assign T8 = 2'h0 == regState;
  assign T9 = T11 & T10;
  assign T10 = samples_TVALID ^ 1'h1;
  assign T11 = T12 & deltas_TREADY;
  assign T12 = 2'h3 == regState;
  assign T13 = T11 & samples_TVALID;
  assign T21 = reset ? 32'h0 : T14;
  assign T14 = T13 ? samples_TDATA : T15;
  assign T15 = T2 ? samples_TDATA : T16;
  assign T16 = T7 ? samples_TDATA : regSample2;
  assign deltas_TVALID = T12;
  assign samples_TREADY = T17;
  assign T17 = T13 ? 1'h1 : T18;
  assign T18 = T3 ? 1'h1 : T8;

  always @(posedge clk) begin
    if(reset) begin
      regSample1 <= 32'h0;
    end else if(T13) begin
      regSample1 <= regSample2;
    end else if(T2) begin
      regSample1 <= regSample2;
    end
    if(reset) begin
      regState <= 2'h0;
    end else if(T9) begin
      regState <= 2'h1;
    end else if(T2) begin
      regState <= 2'h3;
    end else if(T7) begin
      regState <= 2'h1;
    end
    if(reset) begin
      regSample2 <= 32'h0;
    end else if(T13) begin
      regSample2 <= samples_TDATA;
    end else if(T2) begin
      regSample2 <= samples_TDATA;
    end else if(T7) begin
      regSample2 <= samples_TDATA;
    end
  end
endmodule

