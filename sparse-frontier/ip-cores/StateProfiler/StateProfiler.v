module StateProfiler(input clk, input reset,
    input  io_start,
    input [31:0] io_probe,
    output[31:0] io_count,
    input [2:0] io_sel
);

  wire[31:0] T0;
  wire[31:0] T1;
  wire[31:0] T2;
  reg [31:0] regStateCount_0;
  wire[31:0] T71;
  wire[31:0] T3;
  wire[31:0] T4;
  wire T5;
  wire T6;
  reg [1:0] regState;
  wire[1:0] T72;
  wire[1:0] T7;
  wire[1:0] T8;
  wire T9;
  wire T10;
  wire T11;
  wire[31:0] T12;
  wire[31:0] T13;
  wire[31:0] T14;
  wire[31:0] T15;
  wire T16;
  wire[2:0] T17;
  wire[2:0] T73;
  reg [31:0] regInState;
  wire[31:0] T74;
  wire[31:0] T18;
  reg [31:0] regStateCount_2;
  wire[31:0] T75;
  wire[31:0] T19;
  wire[31:0] T20;
  wire T21;
  wire T22;
  wire[7:0] T23;
  reg [31:0] regStateCount_3;
  wire[31:0] T76;
  wire[31:0] T24;
  wire[31:0] T25;
  wire T26;
  wire T27;
  wire T28;
  wire T29;
  wire[31:0] T30;
  wire[31:0] T31;
  reg [31:0] regStateCount_4;
  wire[31:0] T77;
  wire[31:0] T32;
  wire[31:0] T33;
  wire T34;
  wire T35;
  reg [31:0] regStateCount_5;
  wire[31:0] T78;
  wire[31:0] T36;
  wire[31:0] T37;
  wire T38;
  wire T39;
  wire T40;
  wire[31:0] T41;
  reg [31:0] regStateCount_6;
  wire[31:0] T79;
  wire[31:0] T42;
  wire[31:0] T43;
  wire T44;
  wire T45;
  reg [31:0] regStateCount_7;
  wire[31:0] T80;
  wire[31:0] T46;
  wire[31:0] T47;
  wire T48;
  wire T49;
  wire T50;
  wire T51;
  wire T52;
  wire T53;
  wire T54;
  reg [31:0] regStateCount_1;
  wire[31:0] T81;
  wire[31:0] T55;
  wire[31:0] T56;
  wire T57;
  wire T58;
  wire T59;
  wire[2:0] T60;
  wire[31:0] T61;
  wire T62;
  wire T63;
  wire[31:0] T64;
  wire[31:0] T65;
  wire T66;
  wire[31:0] T67;
  wire T68;
  wire T69;
  wire T70;

`ifndef SYNTHESIS
  integer initvar;
  initial begin
    #0.002;
    regStateCount_0 = {1{$random}};
    regState = {1{$random}};
    regInState = {1{$random}};
    regStateCount_2 = {1{$random}};
    regStateCount_3 = {1{$random}};
    regStateCount_4 = {1{$random}};
    regStateCount_5 = {1{$random}};
    regStateCount_6 = {1{$random}};
    regStateCount_7 = {1{$random}};
    regStateCount_1 = {1{$random}};
  end
`endif

  assign io_count = T0;
  assign T0 = T70 ? T64 : T1;
  assign T1 = T63 ? T61 : T2;
  assign T2 = T59 ? regStateCount_1 : regStateCount_0;
  assign T71 = reset ? 32'h0 : T3;
  assign T3 = T53 ? T12 : T4;
  assign T4 = T5 ? 32'h0 : regStateCount_0;
  assign T5 = T6 & io_start;
  assign T6 = 2'h0 == regState;
  assign T72 = reset ? 2'h0 : T7;
  assign T7 = T9 ? 2'h0 : T8;
  assign T8 = T5 ? 2'h1 : regState;
  assign T9 = T11 & T10;
  assign T10 = io_start ^ 1'h1;
  assign T11 = 2'h1 == regState;
  assign T12 = T13 + 32'h1;
  assign T13 = T52 ? T30 : T14;
  assign T14 = T29 ? T18 : T15;
  assign T15 = T16 ? regStateCount_1 : regStateCount_0;
  assign T16 = T17[1'h0:1'h0];
  assign T17 = T73;
  assign T73 = regInState[2'h2:1'h0];
  assign T74 = reset ? 32'h0 : io_probe;
  assign T18 = T28 ? regStateCount_3 : regStateCount_2;
  assign T75 = reset ? 32'h0 : T19;
  assign T19 = T21 ? T12 : T20;
  assign T20 = T5 ? 32'h0 : regStateCount_2;
  assign T21 = T11 & T22;
  assign T22 = T23[2'h2:2'h2];
  assign T23 = 1'h1 << T17;
  assign T76 = reset ? 32'h0 : T24;
  assign T24 = T26 ? T12 : T25;
  assign T25 = T5 ? 32'h0 : regStateCount_3;
  assign T26 = T11 & T27;
  assign T27 = T23[2'h3:2'h3];
  assign T28 = T17[1'h0:1'h0];
  assign T29 = T17[1'h1:1'h1];
  assign T30 = T51 ? T41 : T31;
  assign T31 = T40 ? regStateCount_5 : regStateCount_4;
  assign T77 = reset ? 32'h0 : T32;
  assign T32 = T34 ? T12 : T33;
  assign T33 = T5 ? 32'h0 : regStateCount_4;
  assign T34 = T11 & T35;
  assign T35 = T23[3'h4:3'h4];
  assign T78 = reset ? 32'h0 : T36;
  assign T36 = T38 ? T12 : T37;
  assign T37 = T5 ? 32'h0 : regStateCount_5;
  assign T38 = T11 & T39;
  assign T39 = T23[3'h5:3'h5];
  assign T40 = T17[1'h0:1'h0];
  assign T41 = T50 ? regStateCount_7 : regStateCount_6;
  assign T79 = reset ? 32'h0 : T42;
  assign T42 = T44 ? T12 : T43;
  assign T43 = T5 ? 32'h0 : regStateCount_6;
  assign T44 = T11 & T45;
  assign T45 = T23[3'h6:3'h6];
  assign T80 = reset ? 32'h0 : T46;
  assign T46 = T48 ? T12 : T47;
  assign T47 = T5 ? 32'h0 : regStateCount_7;
  assign T48 = T11 & T49;
  assign T49 = T23[3'h7:3'h7];
  assign T50 = T17[1'h0:1'h0];
  assign T51 = T17[1'h1:1'h1];
  assign T52 = T17[2'h2:2'h2];
  assign T53 = T11 & T54;
  assign T54 = T23[1'h0:1'h0];
  assign T81 = reset ? 32'h0 : T55;
  assign T55 = T57 ? T12 : T56;
  assign T56 = T5 ? 32'h0 : regStateCount_1;
  assign T57 = T11 & T58;
  assign T58 = T23[1'h1:1'h1];
  assign T59 = T60[1'h0:1'h0];
  assign T60 = io_sel;
  assign T61 = T62 ? regStateCount_3 : regStateCount_2;
  assign T62 = T60[1'h0:1'h0];
  assign T63 = T60[1'h1:1'h1];
  assign T64 = T69 ? T67 : T65;
  assign T65 = T66 ? regStateCount_5 : regStateCount_4;
  assign T66 = T60[1'h0:1'h0];
  assign T67 = T68 ? regStateCount_7 : regStateCount_6;
  assign T68 = T60[1'h0:1'h0];
  assign T69 = T60[1'h1:1'h1];
  assign T70 = T60[2'h2:2'h2];

  always @(posedge clk) begin
    if(reset) begin
      regStateCount_0 <= 32'h0;
    end else if(T53) begin
      regStateCount_0 <= T12;
    end else if(T5) begin
      regStateCount_0 <= 32'h0;
    end
    if(reset) begin
      regState <= 2'h0;
    end else if(T9) begin
      regState <= 2'h0;
    end else if(T5) begin
      regState <= 2'h1;
    end
    if(reset) begin
      regInState <= 32'h0;
    end else begin
      regInState <= io_probe;
    end
    if(reset) begin
      regStateCount_2 <= 32'h0;
    end else if(T21) begin
      regStateCount_2 <= T12;
    end else if(T5) begin
      regStateCount_2 <= 32'h0;
    end
    if(reset) begin
      regStateCount_3 <= 32'h0;
    end else if(T26) begin
      regStateCount_3 <= T12;
    end else if(T5) begin
      regStateCount_3 <= 32'h0;
    end
    if(reset) begin
      regStateCount_4 <= 32'h0;
    end else if(T34) begin
      regStateCount_4 <= T12;
    end else if(T5) begin
      regStateCount_4 <= 32'h0;
    end
    if(reset) begin
      regStateCount_5 <= 32'h0;
    end else if(T38) begin
      regStateCount_5 <= T12;
    end else if(T5) begin
      regStateCount_5 <= 32'h0;
    end
    if(reset) begin
      regStateCount_6 <= 32'h0;
    end else if(T44) begin
      regStateCount_6 <= T12;
    end else if(T5) begin
      regStateCount_6 <= 32'h0;
    end
    if(reset) begin
      regStateCount_7 <= 32'h0;
    end else if(T48) begin
      regStateCount_7 <= T12;
    end else if(T5) begin
      regStateCount_7 <= 32'h0;
    end
    if(reset) begin
      regStateCount_1 <= 32'h0;
    end else if(T57) begin
      regStateCount_1 <= T12;
    end else if(T5) begin
      regStateCount_1 <= 32'h0;
    end
  end
endmodule

