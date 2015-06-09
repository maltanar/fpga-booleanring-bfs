module ResultDumper(input clk, input reset,
    input  io_start,
    input [15:0] io_wordCount,
    output io_finished,
    output[19:0] io_readAddr1,
    output[19:0] io_readAddr2,
    input [31:0] io_readData1,
    input [31:0] io_readData2,
    input  resultVector_TREADY,
    output resultVector_TVALID,
    output[63:0] resultVector_TDATA,
    input [31:0] io_fifoDataCount
);

  wire[63:0] T0;
  reg  regValid3;
  wire T37;
  reg  regValid2;
  wire T38;
  reg  regValid1;
  wire T39;
  wire T1;
  wire T2;
  wire T3;
  reg [3:0] regReqCount;
  wire[3:0] T40;
  wire[31:0] T41;
  wire[31:0] T4;
  wire[31:0] T5;
  wire[31:0] T42;
  wire[3:0] T6;
  wire T7;
  reg [1:0] regState;
  wire[1:0] T43;
  wire[1:0] T8;
  wire[1:0] T9;
  wire[1:0] T10;
  wire[1:0] T11;
  wire[1:0] T12;
  wire T13;
  wire T14;
  wire T15;
  reg [31:0] regWordsLeft;
  wire[31:0] T44;
  wire[31:0] T16;
  wire[31:0] T17;
  wire[31:0] T45;
  wire[31:0] T18;
  wire T19;
  wire T20;
  wire T21;
  wire T22;
  wire T23;
  wire[31:0] T24;
  wire T25;
  wire T26;
  wire T27;
  wire hasRoom;
  wire T28;
  wire[31:0] T46;
  wire[3:0] T29;
  wire T30;
  wire[19:0] T47;
  wire[24:0] T31;
  wire[19:0] T32;
  reg [19:0] regReadAddr;
  wire[19:0] T48;
  wire[19:0] T33;
  wire[19:0] T34;
  wire[19:0] T35;
  wire[19:0] T49;
  wire[24:0] T36;

`ifndef SYNTHESIS
  integer initvar;
  initial begin
    #0.002;
    regValid3 = {1{$random}};
    regValid2 = {1{$random}};
    regValid1 = {1{$random}};
    regReqCount = {1{$random}};
    regState = {1{$random}};
    regWordsLeft = {1{$random}};
    regReadAddr = {1{$random}};
  end
`endif

  assign resultVector_TDATA = T0;
  assign T0 = {io_readData2, io_readData1};
  assign resultVector_TVALID = regValid3;
  assign T37 = reset ? 1'h0 : regValid2;
  assign T38 = reset ? 1'h0 : regValid1;
  assign T39 = reset ? 1'h0 : T1;
  assign T1 = T30 & T2;
  assign T2 = T3 ^ 1'h1;
  assign T3 = regReqCount == 4'h0;
  assign T40 = T41[2'h3:1'h0];
  assign T41 = reset ? 32'h0 : T4;
  assign T4 = T1 ? T46 : T5;
  assign T5 = T26 ? T24 : T42;
  assign T42 = {28'h0, T6};
  assign T6 = T7 ? 4'h0 : regReqCount;
  assign T7 = 2'h0 == regState;
  assign T43 = reset ? 2'h0 : T8;
  assign T8 = T21 ? 2'h0 : T9;
  assign T9 = T20 ? 2'h1 : T10;
  assign T10 = T26 ? 2'h2 : T11;
  assign T11 = T14 ? 2'h3 : T12;
  assign T12 = T13 ? 2'h1 : regState;
  assign T13 = T7 & io_start;
  assign T14 = T19 & T15;
  assign T15 = regWordsLeft == 32'h0;
  assign T44 = reset ? 32'h0 : T16;
  assign T16 = T1 ? T18 : T17;
  assign T17 = T7 ? T45 : regWordsLeft;
  assign T45 = {16'h0, io_wordCount};
  assign T18 = regWordsLeft - 32'h1;
  assign T19 = 2'h1 == regState;
  assign T20 = T30 & T3;
  assign T21 = T23 & T22;
  assign T22 = io_start ^ 1'h1;
  assign T23 = 2'h3 == regState;
  assign T24 = T25 ? 32'h3 : regWordsLeft;
  assign T25 = 32'h3 < regWordsLeft;
  assign T26 = T19 & T27;
  assign T27 = T28 & hasRoom;
  assign hasRoom = io_fifoDataCount < 32'h9;
  assign T28 = T15 ^ 1'h1;
  assign T46 = {28'h0, T29};
  assign T29 = regReqCount - 4'h1;
  assign T30 = 2'h2 == regState;
  assign io_readAddr2 = T47;
  assign T47 = T31[5'h13:1'h0];
  assign T31 = T32 << 3'h5;
  assign T32 = regReadAddr + 20'h1;
  assign T48 = reset ? 20'h0 : T33;
  assign T33 = T1 ? T35 : T34;
  assign T34 = T7 ? 20'h0 : regReadAddr;
  assign T35 = regReadAddr + 20'h2;
  assign io_readAddr1 = T49;
  assign T49 = T36[5'h13:1'h0];
  assign T36 = regReadAddr << 3'h5;
  assign io_finished = T23;

  always @(posedge clk) begin
    if(reset) begin
      regValid3 <= 1'h0;
    end else begin
      regValid3 <= regValid2;
    end
    if(reset) begin
      regValid2 <= 1'h0;
    end else begin
      regValid2 <= regValid1;
    end
    if(reset) begin
      regValid1 <= 1'h0;
    end else begin
      regValid1 <= T1;
    end
    regReqCount <= T40;
    if(reset) begin
      regState <= 2'h0;
    end else if(T21) begin
      regState <= 2'h0;
    end else if(T20) begin
      regState <= 2'h1;
    end else if(T26) begin
      regState <= 2'h2;
    end else if(T14) begin
      regState <= 2'h3;
    end else if(T13) begin
      regState <= 2'h1;
    end
    if(reset) begin
      regWordsLeft <= 32'h0;
    end else if(T1) begin
      regWordsLeft <= T18;
    end else if(T7) begin
      regWordsLeft <= T45;
    end
    if(reset) begin
      regReadAddr <= 20'h0;
    end else if(T1) begin
      regReadAddr <= T35;
    end else if(T7) begin
      regReadAddr <= 20'h0;
    end
  end
endmodule

module Queue(input clk, input reset,
    output io_enq_ready,
    input  io_enq_valid,
    input [63:0] io_enq_bits,
    input  io_deq_ready,
    output io_deq_valid,
    output[63:0] io_deq_bits,
    output[4:0] io_count
);

  wire[4:0] T0;
  wire[3:0] ptr_diff;
  reg [3:0] R1;
  wire[3:0] T15;
  wire[3:0] T2;
  wire[3:0] T3;
  wire do_deq;
  reg [3:0] R4;
  wire[3:0] T16;
  wire[3:0] T5;
  wire[3:0] T6;
  wire do_enq;
  wire T7;
  wire ptr_match;
  reg  maybe_full;
  wire T17;
  wire T8;
  wire T9;
  wire[63:0] T10;
  reg [63:0] ram [15:0];
  wire[63:0] T11;
  wire T12;
  wire empty;
  wire T13;
  wire T14;
  wire full;

`ifndef SYNTHESIS
  integer initvar;
  initial begin
    #0.002;
    R1 = {1{$random}};
    R4 = {1{$random}};
    maybe_full = {1{$random}};
    for (initvar = 0; initvar < 16; initvar = initvar+1)
      ram[initvar] = {2{$random}};
  end
`endif

  assign io_count = T0;
  assign T0 = {T7, ptr_diff};
  assign ptr_diff = R4 - R1;
  assign T15 = reset ? 4'h0 : T2;
  assign T2 = do_deq ? T3 : R1;
  assign T3 = R1 + 4'h1;
  assign do_deq = io_deq_ready & io_deq_valid;
  assign T16 = reset ? 4'h0 : T5;
  assign T5 = do_enq ? T6 : R4;
  assign T6 = R4 + 4'h1;
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
      R1 <= 4'h0;
    end else if(do_deq) begin
      R1 <= T3;
    end
    if(reset) begin
      R4 <= 4'h0;
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

module LevelGenerator(input clk, input reset,
    input  io_start,
    input [31:0] io_bitCount,
    output io_finished,
    output[31:0] io_writeCount,
    output io_oldData_ready,
    input  io_oldData_valid,
    input [63:0] io_oldData_bits,
    output io_newData_ready,
    input  io_newData_valid,
    input [63:0] io_newData_bits,
    input  io_writeIndices_ready,
    output io_writeIndices_valid,
    output[31:0] io_writeIndices_bits,
    input  io_newDataCopy_ready,
    output io_newDataCopy_valid,
    output[63:0] io_newDataCopy_bits
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
`endif

  assign io_newDataCopy_bits = regNewData;
  assign T58 = reset ? 64'h0 : T0;
  assign T0 = T38 ? T62 : T1;
  assign T1 = T2 ? io_newData_bits : regNewData;
  assign T2 = T3 & io_newData_valid;
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
  assign T22 = T23 & io_oldData_valid;
  assign T23 = 3'h2 == regState;
  assign T24 = T25 & io_newDataCopy_ready;
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
  assign T39 = io_writeIndices_ready | T40;
  assign T40 = T41 ^ 1'h1;
  assign T41 = T43 & T42;
  assign T42 = regNewData[1'h0:1'h0];
  assign T43 = T44 ^ 1'h1;
  assign T44 = regOldData[1'h0:1'h0];
  assign T63 = reset ? 64'h0 : T45;
  assign T45 = T38 ? T64 : T46;
  assign T46 = T22 ? io_oldData_bits : regOldData;
  assign T64 = {1'h0, T47};
  assign T47 = regOldData >> 1'h1;
  assign T48 = T33 & T49;
  assign T49 = T27 ^ 1'h1;
  assign io_newDataCopy_valid = T25;
  assign io_writeIndices_bits = regWriteIndex;
  assign T65 = reset ? 32'h0 : T50;
  assign T50 = T38 ? T52 : T51;
  assign T51 = T13 ? 32'h0 : regWriteIndex;
  assign T52 = regWriteIndex + 32'h1;
  assign io_writeIndices_valid = T53;
  assign T53 = T48 ? T41 : 1'h0;
  assign io_newData_ready = T3;
  assign io_oldData_ready = T23;
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
      regNewData <= io_newData_bits;
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
      regOldData <= io_oldData_bits;
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

module ParallelInSerialOut(input clk, input reset,
    input [63:0] io_parIn,
    input  io_parWrEn,
    input  io_serIn,
    output io_serOut,
    input  io_shiftEn
);

  reg  stages_0;
  wire T194;
  wire T0;
  wire T1;
  wire T2;
  reg  stages_1;
  wire T195;
  wire T3;
  wire T4;
  wire T5;
  reg  stages_2;
  wire T196;
  wire T6;
  wire T7;
  wire T8;
  reg  stages_3;
  wire T197;
  wire T9;
  wire T10;
  wire T11;
  reg  stages_4;
  wire T198;
  wire T12;
  wire T13;
  wire T14;
  reg  stages_5;
  wire T199;
  wire T15;
  wire T16;
  wire T17;
  reg  stages_6;
  wire T200;
  wire T18;
  wire T19;
  wire T20;
  reg  stages_7;
  wire T201;
  wire T21;
  wire T22;
  wire T23;
  reg  stages_8;
  wire T202;
  wire T24;
  wire T25;
  wire T26;
  reg  stages_9;
  wire T203;
  wire T27;
  wire T28;
  wire T29;
  reg  stages_10;
  wire T204;
  wire T30;
  wire T31;
  wire T32;
  reg  stages_11;
  wire T205;
  wire T33;
  wire T34;
  wire T35;
  reg  stages_12;
  wire T206;
  wire T36;
  wire T37;
  wire T38;
  reg  stages_13;
  wire T207;
  wire T39;
  wire T40;
  wire T41;
  reg  stages_14;
  wire T208;
  wire T42;
  wire T43;
  wire T44;
  reg  stages_15;
  wire T209;
  wire T45;
  wire T46;
  wire T47;
  reg  stages_16;
  wire T210;
  wire T48;
  wire T49;
  wire T50;
  reg  stages_17;
  wire T211;
  wire T51;
  wire T52;
  wire T53;
  reg  stages_18;
  wire T212;
  wire T54;
  wire T55;
  wire T56;
  reg  stages_19;
  wire T213;
  wire T57;
  wire T58;
  wire T59;
  reg  stages_20;
  wire T214;
  wire T60;
  wire T61;
  wire T62;
  reg  stages_21;
  wire T215;
  wire T63;
  wire T64;
  wire T65;
  reg  stages_22;
  wire T216;
  wire T66;
  wire T67;
  wire T68;
  reg  stages_23;
  wire T217;
  wire T69;
  wire T70;
  wire T71;
  reg  stages_24;
  wire T218;
  wire T72;
  wire T73;
  wire T74;
  reg  stages_25;
  wire T219;
  wire T75;
  wire T76;
  wire T77;
  reg  stages_26;
  wire T220;
  wire T78;
  wire T79;
  wire T80;
  reg  stages_27;
  wire T221;
  wire T81;
  wire T82;
  wire T83;
  reg  stages_28;
  wire T222;
  wire T84;
  wire T85;
  wire T86;
  reg  stages_29;
  wire T223;
  wire T87;
  wire T88;
  wire T89;
  reg  stages_30;
  wire T224;
  wire T90;
  wire T91;
  wire T92;
  reg  stages_31;
  wire T225;
  wire T93;
  wire T94;
  wire T95;
  reg  stages_32;
  wire T226;
  wire T96;
  wire T97;
  wire T98;
  reg  stages_33;
  wire T227;
  wire T99;
  wire T100;
  wire T101;
  reg  stages_34;
  wire T228;
  wire T102;
  wire T103;
  wire T104;
  reg  stages_35;
  wire T229;
  wire T105;
  wire T106;
  wire T107;
  reg  stages_36;
  wire T230;
  wire T108;
  wire T109;
  wire T110;
  reg  stages_37;
  wire T231;
  wire T111;
  wire T112;
  wire T113;
  reg  stages_38;
  wire T232;
  wire T114;
  wire T115;
  wire T116;
  reg  stages_39;
  wire T233;
  wire T117;
  wire T118;
  wire T119;
  reg  stages_40;
  wire T234;
  wire T120;
  wire T121;
  wire T122;
  reg  stages_41;
  wire T235;
  wire T123;
  wire T124;
  wire T125;
  reg  stages_42;
  wire T236;
  wire T126;
  wire T127;
  wire T128;
  reg  stages_43;
  wire T237;
  wire T129;
  wire T130;
  wire T131;
  reg  stages_44;
  wire T238;
  wire T132;
  wire T133;
  wire T134;
  reg  stages_45;
  wire T239;
  wire T135;
  wire T136;
  wire T137;
  reg  stages_46;
  wire T240;
  wire T138;
  wire T139;
  wire T140;
  reg  stages_47;
  wire T241;
  wire T141;
  wire T142;
  wire T143;
  reg  stages_48;
  wire T242;
  wire T144;
  wire T145;
  wire T146;
  reg  stages_49;
  wire T243;
  wire T147;
  wire T148;
  wire T149;
  reg  stages_50;
  wire T244;
  wire T150;
  wire T151;
  wire T152;
  reg  stages_51;
  wire T245;
  wire T153;
  wire T154;
  wire T155;
  reg  stages_52;
  wire T246;
  wire T156;
  wire T157;
  wire T158;
  reg  stages_53;
  wire T247;
  wire T159;
  wire T160;
  wire T161;
  reg  stages_54;
  wire T248;
  wire T162;
  wire T163;
  wire T164;
  reg  stages_55;
  wire T249;
  wire T165;
  wire T166;
  wire T167;
  reg  stages_56;
  wire T250;
  wire T168;
  wire T169;
  wire T170;
  reg  stages_57;
  wire T251;
  wire T171;
  wire T172;
  wire T173;
  reg  stages_58;
  wire T252;
  wire T174;
  wire T175;
  wire T176;
  reg  stages_59;
  wire T253;
  wire T177;
  wire T178;
  wire T179;
  reg  stages_60;
  wire T254;
  wire T180;
  wire T181;
  wire T182;
  reg  stages_61;
  wire T255;
  wire T183;
  wire T184;
  wire T185;
  reg  stages_62;
  wire T256;
  wire T186;
  wire T187;
  wire T188;
  reg  stages_63;
  wire T257;
  wire T189;
  wire T190;
  wire T191;
  wire T192;
  wire T193;

`ifndef SYNTHESIS
  integer initvar;
  initial begin
    #0.002;
    stages_0 = {1{$random}};
    stages_1 = {1{$random}};
    stages_2 = {1{$random}};
    stages_3 = {1{$random}};
    stages_4 = {1{$random}};
    stages_5 = {1{$random}};
    stages_6 = {1{$random}};
    stages_7 = {1{$random}};
    stages_8 = {1{$random}};
    stages_9 = {1{$random}};
    stages_10 = {1{$random}};
    stages_11 = {1{$random}};
    stages_12 = {1{$random}};
    stages_13 = {1{$random}};
    stages_14 = {1{$random}};
    stages_15 = {1{$random}};
    stages_16 = {1{$random}};
    stages_17 = {1{$random}};
    stages_18 = {1{$random}};
    stages_19 = {1{$random}};
    stages_20 = {1{$random}};
    stages_21 = {1{$random}};
    stages_22 = {1{$random}};
    stages_23 = {1{$random}};
    stages_24 = {1{$random}};
    stages_25 = {1{$random}};
    stages_26 = {1{$random}};
    stages_27 = {1{$random}};
    stages_28 = {1{$random}};
    stages_29 = {1{$random}};
    stages_30 = {1{$random}};
    stages_31 = {1{$random}};
    stages_32 = {1{$random}};
    stages_33 = {1{$random}};
    stages_34 = {1{$random}};
    stages_35 = {1{$random}};
    stages_36 = {1{$random}};
    stages_37 = {1{$random}};
    stages_38 = {1{$random}};
    stages_39 = {1{$random}};
    stages_40 = {1{$random}};
    stages_41 = {1{$random}};
    stages_42 = {1{$random}};
    stages_43 = {1{$random}};
    stages_44 = {1{$random}};
    stages_45 = {1{$random}};
    stages_46 = {1{$random}};
    stages_47 = {1{$random}};
    stages_48 = {1{$random}};
    stages_49 = {1{$random}};
    stages_50 = {1{$random}};
    stages_51 = {1{$random}};
    stages_52 = {1{$random}};
    stages_53 = {1{$random}};
    stages_54 = {1{$random}};
    stages_55 = {1{$random}};
    stages_56 = {1{$random}};
    stages_57 = {1{$random}};
    stages_58 = {1{$random}};
    stages_59 = {1{$random}};
    stages_60 = {1{$random}};
    stages_61 = {1{$random}};
    stages_62 = {1{$random}};
    stages_63 = {1{$random}};
  end
`endif

  assign io_serOut = stages_0;
  assign T194 = reset ? 1'h0 : T0;
  assign T0 = T192 ? stages_1 : T1;
  assign T1 = io_parWrEn ? T2 : stages_0;
  assign T2 = io_parIn[1'h0:1'h0];
  assign T195 = reset ? 1'h0 : T3;
  assign T3 = T192 ? stages_2 : T4;
  assign T4 = io_parWrEn ? T5 : stages_1;
  assign T5 = io_parIn[1'h1:1'h1];
  assign T196 = reset ? 1'h0 : T6;
  assign T6 = T192 ? stages_3 : T7;
  assign T7 = io_parWrEn ? T8 : stages_2;
  assign T8 = io_parIn[2'h2:2'h2];
  assign T197 = reset ? 1'h0 : T9;
  assign T9 = T192 ? stages_4 : T10;
  assign T10 = io_parWrEn ? T11 : stages_3;
  assign T11 = io_parIn[2'h3:2'h3];
  assign T198 = reset ? 1'h0 : T12;
  assign T12 = T192 ? stages_5 : T13;
  assign T13 = io_parWrEn ? T14 : stages_4;
  assign T14 = io_parIn[3'h4:3'h4];
  assign T199 = reset ? 1'h0 : T15;
  assign T15 = T192 ? stages_6 : T16;
  assign T16 = io_parWrEn ? T17 : stages_5;
  assign T17 = io_parIn[3'h5:3'h5];
  assign T200 = reset ? 1'h0 : T18;
  assign T18 = T192 ? stages_7 : T19;
  assign T19 = io_parWrEn ? T20 : stages_6;
  assign T20 = io_parIn[3'h6:3'h6];
  assign T201 = reset ? 1'h0 : T21;
  assign T21 = T192 ? stages_8 : T22;
  assign T22 = io_parWrEn ? T23 : stages_7;
  assign T23 = io_parIn[3'h7:3'h7];
  assign T202 = reset ? 1'h0 : T24;
  assign T24 = T192 ? stages_9 : T25;
  assign T25 = io_parWrEn ? T26 : stages_8;
  assign T26 = io_parIn[4'h8:4'h8];
  assign T203 = reset ? 1'h0 : T27;
  assign T27 = T192 ? stages_10 : T28;
  assign T28 = io_parWrEn ? T29 : stages_9;
  assign T29 = io_parIn[4'h9:4'h9];
  assign T204 = reset ? 1'h0 : T30;
  assign T30 = T192 ? stages_11 : T31;
  assign T31 = io_parWrEn ? T32 : stages_10;
  assign T32 = io_parIn[4'ha:4'ha];
  assign T205 = reset ? 1'h0 : T33;
  assign T33 = T192 ? stages_12 : T34;
  assign T34 = io_parWrEn ? T35 : stages_11;
  assign T35 = io_parIn[4'hb:4'hb];
  assign T206 = reset ? 1'h0 : T36;
  assign T36 = T192 ? stages_13 : T37;
  assign T37 = io_parWrEn ? T38 : stages_12;
  assign T38 = io_parIn[4'hc:4'hc];
  assign T207 = reset ? 1'h0 : T39;
  assign T39 = T192 ? stages_14 : T40;
  assign T40 = io_parWrEn ? T41 : stages_13;
  assign T41 = io_parIn[4'hd:4'hd];
  assign T208 = reset ? 1'h0 : T42;
  assign T42 = T192 ? stages_15 : T43;
  assign T43 = io_parWrEn ? T44 : stages_14;
  assign T44 = io_parIn[4'he:4'he];
  assign T209 = reset ? 1'h0 : T45;
  assign T45 = T192 ? stages_16 : T46;
  assign T46 = io_parWrEn ? T47 : stages_15;
  assign T47 = io_parIn[4'hf:4'hf];
  assign T210 = reset ? 1'h0 : T48;
  assign T48 = T192 ? stages_17 : T49;
  assign T49 = io_parWrEn ? T50 : stages_16;
  assign T50 = io_parIn[5'h10:5'h10];
  assign T211 = reset ? 1'h0 : T51;
  assign T51 = T192 ? stages_18 : T52;
  assign T52 = io_parWrEn ? T53 : stages_17;
  assign T53 = io_parIn[5'h11:5'h11];
  assign T212 = reset ? 1'h0 : T54;
  assign T54 = T192 ? stages_19 : T55;
  assign T55 = io_parWrEn ? T56 : stages_18;
  assign T56 = io_parIn[5'h12:5'h12];
  assign T213 = reset ? 1'h0 : T57;
  assign T57 = T192 ? stages_20 : T58;
  assign T58 = io_parWrEn ? T59 : stages_19;
  assign T59 = io_parIn[5'h13:5'h13];
  assign T214 = reset ? 1'h0 : T60;
  assign T60 = T192 ? stages_21 : T61;
  assign T61 = io_parWrEn ? T62 : stages_20;
  assign T62 = io_parIn[5'h14:5'h14];
  assign T215 = reset ? 1'h0 : T63;
  assign T63 = T192 ? stages_22 : T64;
  assign T64 = io_parWrEn ? T65 : stages_21;
  assign T65 = io_parIn[5'h15:5'h15];
  assign T216 = reset ? 1'h0 : T66;
  assign T66 = T192 ? stages_23 : T67;
  assign T67 = io_parWrEn ? T68 : stages_22;
  assign T68 = io_parIn[5'h16:5'h16];
  assign T217 = reset ? 1'h0 : T69;
  assign T69 = T192 ? stages_24 : T70;
  assign T70 = io_parWrEn ? T71 : stages_23;
  assign T71 = io_parIn[5'h17:5'h17];
  assign T218 = reset ? 1'h0 : T72;
  assign T72 = T192 ? stages_25 : T73;
  assign T73 = io_parWrEn ? T74 : stages_24;
  assign T74 = io_parIn[5'h18:5'h18];
  assign T219 = reset ? 1'h0 : T75;
  assign T75 = T192 ? stages_26 : T76;
  assign T76 = io_parWrEn ? T77 : stages_25;
  assign T77 = io_parIn[5'h19:5'h19];
  assign T220 = reset ? 1'h0 : T78;
  assign T78 = T192 ? stages_27 : T79;
  assign T79 = io_parWrEn ? T80 : stages_26;
  assign T80 = io_parIn[5'h1a:5'h1a];
  assign T221 = reset ? 1'h0 : T81;
  assign T81 = T192 ? stages_28 : T82;
  assign T82 = io_parWrEn ? T83 : stages_27;
  assign T83 = io_parIn[5'h1b:5'h1b];
  assign T222 = reset ? 1'h0 : T84;
  assign T84 = T192 ? stages_29 : T85;
  assign T85 = io_parWrEn ? T86 : stages_28;
  assign T86 = io_parIn[5'h1c:5'h1c];
  assign T223 = reset ? 1'h0 : T87;
  assign T87 = T192 ? stages_30 : T88;
  assign T88 = io_parWrEn ? T89 : stages_29;
  assign T89 = io_parIn[5'h1d:5'h1d];
  assign T224 = reset ? 1'h0 : T90;
  assign T90 = T192 ? stages_31 : T91;
  assign T91 = io_parWrEn ? T92 : stages_30;
  assign T92 = io_parIn[5'h1e:5'h1e];
  assign T225 = reset ? 1'h0 : T93;
  assign T93 = T192 ? stages_32 : T94;
  assign T94 = io_parWrEn ? T95 : stages_31;
  assign T95 = io_parIn[5'h1f:5'h1f];
  assign T226 = reset ? 1'h0 : T96;
  assign T96 = T192 ? stages_33 : T97;
  assign T97 = io_parWrEn ? T98 : stages_32;
  assign T98 = io_parIn[6'h20:6'h20];
  assign T227 = reset ? 1'h0 : T99;
  assign T99 = T192 ? stages_34 : T100;
  assign T100 = io_parWrEn ? T101 : stages_33;
  assign T101 = io_parIn[6'h21:6'h21];
  assign T228 = reset ? 1'h0 : T102;
  assign T102 = T192 ? stages_35 : T103;
  assign T103 = io_parWrEn ? T104 : stages_34;
  assign T104 = io_parIn[6'h22:6'h22];
  assign T229 = reset ? 1'h0 : T105;
  assign T105 = T192 ? stages_36 : T106;
  assign T106 = io_parWrEn ? T107 : stages_35;
  assign T107 = io_parIn[6'h23:6'h23];
  assign T230 = reset ? 1'h0 : T108;
  assign T108 = T192 ? stages_37 : T109;
  assign T109 = io_parWrEn ? T110 : stages_36;
  assign T110 = io_parIn[6'h24:6'h24];
  assign T231 = reset ? 1'h0 : T111;
  assign T111 = T192 ? stages_38 : T112;
  assign T112 = io_parWrEn ? T113 : stages_37;
  assign T113 = io_parIn[6'h25:6'h25];
  assign T232 = reset ? 1'h0 : T114;
  assign T114 = T192 ? stages_39 : T115;
  assign T115 = io_parWrEn ? T116 : stages_38;
  assign T116 = io_parIn[6'h26:6'h26];
  assign T233 = reset ? 1'h0 : T117;
  assign T117 = T192 ? stages_40 : T118;
  assign T118 = io_parWrEn ? T119 : stages_39;
  assign T119 = io_parIn[6'h27:6'h27];
  assign T234 = reset ? 1'h0 : T120;
  assign T120 = T192 ? stages_41 : T121;
  assign T121 = io_parWrEn ? T122 : stages_40;
  assign T122 = io_parIn[6'h28:6'h28];
  assign T235 = reset ? 1'h0 : T123;
  assign T123 = T192 ? stages_42 : T124;
  assign T124 = io_parWrEn ? T125 : stages_41;
  assign T125 = io_parIn[6'h29:6'h29];
  assign T236 = reset ? 1'h0 : T126;
  assign T126 = T192 ? stages_43 : T127;
  assign T127 = io_parWrEn ? T128 : stages_42;
  assign T128 = io_parIn[6'h2a:6'h2a];
  assign T237 = reset ? 1'h0 : T129;
  assign T129 = T192 ? stages_44 : T130;
  assign T130 = io_parWrEn ? T131 : stages_43;
  assign T131 = io_parIn[6'h2b:6'h2b];
  assign T238 = reset ? 1'h0 : T132;
  assign T132 = T192 ? stages_45 : T133;
  assign T133 = io_parWrEn ? T134 : stages_44;
  assign T134 = io_parIn[6'h2c:6'h2c];
  assign T239 = reset ? 1'h0 : T135;
  assign T135 = T192 ? stages_46 : T136;
  assign T136 = io_parWrEn ? T137 : stages_45;
  assign T137 = io_parIn[6'h2d:6'h2d];
  assign T240 = reset ? 1'h0 : T138;
  assign T138 = T192 ? stages_47 : T139;
  assign T139 = io_parWrEn ? T140 : stages_46;
  assign T140 = io_parIn[6'h2e:6'h2e];
  assign T241 = reset ? 1'h0 : T141;
  assign T141 = T192 ? stages_48 : T142;
  assign T142 = io_parWrEn ? T143 : stages_47;
  assign T143 = io_parIn[6'h2f:6'h2f];
  assign T242 = reset ? 1'h0 : T144;
  assign T144 = T192 ? stages_49 : T145;
  assign T145 = io_parWrEn ? T146 : stages_48;
  assign T146 = io_parIn[6'h30:6'h30];
  assign T243 = reset ? 1'h0 : T147;
  assign T147 = T192 ? stages_50 : T148;
  assign T148 = io_parWrEn ? T149 : stages_49;
  assign T149 = io_parIn[6'h31:6'h31];
  assign T244 = reset ? 1'h0 : T150;
  assign T150 = T192 ? stages_51 : T151;
  assign T151 = io_parWrEn ? T152 : stages_50;
  assign T152 = io_parIn[6'h32:6'h32];
  assign T245 = reset ? 1'h0 : T153;
  assign T153 = T192 ? stages_52 : T154;
  assign T154 = io_parWrEn ? T155 : stages_51;
  assign T155 = io_parIn[6'h33:6'h33];
  assign T246 = reset ? 1'h0 : T156;
  assign T156 = T192 ? stages_53 : T157;
  assign T157 = io_parWrEn ? T158 : stages_52;
  assign T158 = io_parIn[6'h34:6'h34];
  assign T247 = reset ? 1'h0 : T159;
  assign T159 = T192 ? stages_54 : T160;
  assign T160 = io_parWrEn ? T161 : stages_53;
  assign T161 = io_parIn[6'h35:6'h35];
  assign T248 = reset ? 1'h0 : T162;
  assign T162 = T192 ? stages_55 : T163;
  assign T163 = io_parWrEn ? T164 : stages_54;
  assign T164 = io_parIn[6'h36:6'h36];
  assign T249 = reset ? 1'h0 : T165;
  assign T165 = T192 ? stages_56 : T166;
  assign T166 = io_parWrEn ? T167 : stages_55;
  assign T167 = io_parIn[6'h37:6'h37];
  assign T250 = reset ? 1'h0 : T168;
  assign T168 = T192 ? stages_57 : T169;
  assign T169 = io_parWrEn ? T170 : stages_56;
  assign T170 = io_parIn[6'h38:6'h38];
  assign T251 = reset ? 1'h0 : T171;
  assign T171 = T192 ? stages_58 : T172;
  assign T172 = io_parWrEn ? T173 : stages_57;
  assign T173 = io_parIn[6'h39:6'h39];
  assign T252 = reset ? 1'h0 : T174;
  assign T174 = T192 ? stages_59 : T175;
  assign T175 = io_parWrEn ? T176 : stages_58;
  assign T176 = io_parIn[6'h3a:6'h3a];
  assign T253 = reset ? 1'h0 : T177;
  assign T177 = T192 ? stages_60 : T178;
  assign T178 = io_parWrEn ? T179 : stages_59;
  assign T179 = io_parIn[6'h3b:6'h3b];
  assign T254 = reset ? 1'h0 : T180;
  assign T180 = T192 ? stages_61 : T181;
  assign T181 = io_parWrEn ? T182 : stages_60;
  assign T182 = io_parIn[6'h3c:6'h3c];
  assign T255 = reset ? 1'h0 : T183;
  assign T183 = T192 ? stages_62 : T184;
  assign T184 = io_parWrEn ? T185 : stages_61;
  assign T185 = io_parIn[6'h3d:6'h3d];
  assign T256 = reset ? 1'h0 : T186;
  assign T186 = T192 ? stages_63 : T187;
  assign T187 = io_parWrEn ? T188 : stages_62;
  assign T188 = io_parIn[6'h3e:6'h3e];
  assign T257 = reset ? 1'h0 : T189;
  assign T189 = T192 ? io_serIn : T190;
  assign T190 = io_parWrEn ? T191 : stages_63;
  assign T191 = io_parIn[6'h3f:6'h3f];
  assign T192 = T193 & io_shiftEn;
  assign T193 = io_parWrEn ^ 1'h1;

  always @(posedge clk) begin
    if(reset) begin
      stages_0 <= 1'h0;
    end else if(T192) begin
      stages_0 <= stages_1;
    end else if(io_parWrEn) begin
      stages_0 <= T2;
    end
    if(reset) begin
      stages_1 <= 1'h0;
    end else if(T192) begin
      stages_1 <= stages_2;
    end else if(io_parWrEn) begin
      stages_1 <= T5;
    end
    if(reset) begin
      stages_2 <= 1'h0;
    end else if(T192) begin
      stages_2 <= stages_3;
    end else if(io_parWrEn) begin
      stages_2 <= T8;
    end
    if(reset) begin
      stages_3 <= 1'h0;
    end else if(T192) begin
      stages_3 <= stages_4;
    end else if(io_parWrEn) begin
      stages_3 <= T11;
    end
    if(reset) begin
      stages_4 <= 1'h0;
    end else if(T192) begin
      stages_4 <= stages_5;
    end else if(io_parWrEn) begin
      stages_4 <= T14;
    end
    if(reset) begin
      stages_5 <= 1'h0;
    end else if(T192) begin
      stages_5 <= stages_6;
    end else if(io_parWrEn) begin
      stages_5 <= T17;
    end
    if(reset) begin
      stages_6 <= 1'h0;
    end else if(T192) begin
      stages_6 <= stages_7;
    end else if(io_parWrEn) begin
      stages_6 <= T20;
    end
    if(reset) begin
      stages_7 <= 1'h0;
    end else if(T192) begin
      stages_7 <= stages_8;
    end else if(io_parWrEn) begin
      stages_7 <= T23;
    end
    if(reset) begin
      stages_8 <= 1'h0;
    end else if(T192) begin
      stages_8 <= stages_9;
    end else if(io_parWrEn) begin
      stages_8 <= T26;
    end
    if(reset) begin
      stages_9 <= 1'h0;
    end else if(T192) begin
      stages_9 <= stages_10;
    end else if(io_parWrEn) begin
      stages_9 <= T29;
    end
    if(reset) begin
      stages_10 <= 1'h0;
    end else if(T192) begin
      stages_10 <= stages_11;
    end else if(io_parWrEn) begin
      stages_10 <= T32;
    end
    if(reset) begin
      stages_11 <= 1'h0;
    end else if(T192) begin
      stages_11 <= stages_12;
    end else if(io_parWrEn) begin
      stages_11 <= T35;
    end
    if(reset) begin
      stages_12 <= 1'h0;
    end else if(T192) begin
      stages_12 <= stages_13;
    end else if(io_parWrEn) begin
      stages_12 <= T38;
    end
    if(reset) begin
      stages_13 <= 1'h0;
    end else if(T192) begin
      stages_13 <= stages_14;
    end else if(io_parWrEn) begin
      stages_13 <= T41;
    end
    if(reset) begin
      stages_14 <= 1'h0;
    end else if(T192) begin
      stages_14 <= stages_15;
    end else if(io_parWrEn) begin
      stages_14 <= T44;
    end
    if(reset) begin
      stages_15 <= 1'h0;
    end else if(T192) begin
      stages_15 <= stages_16;
    end else if(io_parWrEn) begin
      stages_15 <= T47;
    end
    if(reset) begin
      stages_16 <= 1'h0;
    end else if(T192) begin
      stages_16 <= stages_17;
    end else if(io_parWrEn) begin
      stages_16 <= T50;
    end
    if(reset) begin
      stages_17 <= 1'h0;
    end else if(T192) begin
      stages_17 <= stages_18;
    end else if(io_parWrEn) begin
      stages_17 <= T53;
    end
    if(reset) begin
      stages_18 <= 1'h0;
    end else if(T192) begin
      stages_18 <= stages_19;
    end else if(io_parWrEn) begin
      stages_18 <= T56;
    end
    if(reset) begin
      stages_19 <= 1'h0;
    end else if(T192) begin
      stages_19 <= stages_20;
    end else if(io_parWrEn) begin
      stages_19 <= T59;
    end
    if(reset) begin
      stages_20 <= 1'h0;
    end else if(T192) begin
      stages_20 <= stages_21;
    end else if(io_parWrEn) begin
      stages_20 <= T62;
    end
    if(reset) begin
      stages_21 <= 1'h0;
    end else if(T192) begin
      stages_21 <= stages_22;
    end else if(io_parWrEn) begin
      stages_21 <= T65;
    end
    if(reset) begin
      stages_22 <= 1'h0;
    end else if(T192) begin
      stages_22 <= stages_23;
    end else if(io_parWrEn) begin
      stages_22 <= T68;
    end
    if(reset) begin
      stages_23 <= 1'h0;
    end else if(T192) begin
      stages_23 <= stages_24;
    end else if(io_parWrEn) begin
      stages_23 <= T71;
    end
    if(reset) begin
      stages_24 <= 1'h0;
    end else if(T192) begin
      stages_24 <= stages_25;
    end else if(io_parWrEn) begin
      stages_24 <= T74;
    end
    if(reset) begin
      stages_25 <= 1'h0;
    end else if(T192) begin
      stages_25 <= stages_26;
    end else if(io_parWrEn) begin
      stages_25 <= T77;
    end
    if(reset) begin
      stages_26 <= 1'h0;
    end else if(T192) begin
      stages_26 <= stages_27;
    end else if(io_parWrEn) begin
      stages_26 <= T80;
    end
    if(reset) begin
      stages_27 <= 1'h0;
    end else if(T192) begin
      stages_27 <= stages_28;
    end else if(io_parWrEn) begin
      stages_27 <= T83;
    end
    if(reset) begin
      stages_28 <= 1'h0;
    end else if(T192) begin
      stages_28 <= stages_29;
    end else if(io_parWrEn) begin
      stages_28 <= T86;
    end
    if(reset) begin
      stages_29 <= 1'h0;
    end else if(T192) begin
      stages_29 <= stages_30;
    end else if(io_parWrEn) begin
      stages_29 <= T89;
    end
    if(reset) begin
      stages_30 <= 1'h0;
    end else if(T192) begin
      stages_30 <= stages_31;
    end else if(io_parWrEn) begin
      stages_30 <= T92;
    end
    if(reset) begin
      stages_31 <= 1'h0;
    end else if(T192) begin
      stages_31 <= stages_32;
    end else if(io_parWrEn) begin
      stages_31 <= T95;
    end
    if(reset) begin
      stages_32 <= 1'h0;
    end else if(T192) begin
      stages_32 <= stages_33;
    end else if(io_parWrEn) begin
      stages_32 <= T98;
    end
    if(reset) begin
      stages_33 <= 1'h0;
    end else if(T192) begin
      stages_33 <= stages_34;
    end else if(io_parWrEn) begin
      stages_33 <= T101;
    end
    if(reset) begin
      stages_34 <= 1'h0;
    end else if(T192) begin
      stages_34 <= stages_35;
    end else if(io_parWrEn) begin
      stages_34 <= T104;
    end
    if(reset) begin
      stages_35 <= 1'h0;
    end else if(T192) begin
      stages_35 <= stages_36;
    end else if(io_parWrEn) begin
      stages_35 <= T107;
    end
    if(reset) begin
      stages_36 <= 1'h0;
    end else if(T192) begin
      stages_36 <= stages_37;
    end else if(io_parWrEn) begin
      stages_36 <= T110;
    end
    if(reset) begin
      stages_37 <= 1'h0;
    end else if(T192) begin
      stages_37 <= stages_38;
    end else if(io_parWrEn) begin
      stages_37 <= T113;
    end
    if(reset) begin
      stages_38 <= 1'h0;
    end else if(T192) begin
      stages_38 <= stages_39;
    end else if(io_parWrEn) begin
      stages_38 <= T116;
    end
    if(reset) begin
      stages_39 <= 1'h0;
    end else if(T192) begin
      stages_39 <= stages_40;
    end else if(io_parWrEn) begin
      stages_39 <= T119;
    end
    if(reset) begin
      stages_40 <= 1'h0;
    end else if(T192) begin
      stages_40 <= stages_41;
    end else if(io_parWrEn) begin
      stages_40 <= T122;
    end
    if(reset) begin
      stages_41 <= 1'h0;
    end else if(T192) begin
      stages_41 <= stages_42;
    end else if(io_parWrEn) begin
      stages_41 <= T125;
    end
    if(reset) begin
      stages_42 <= 1'h0;
    end else if(T192) begin
      stages_42 <= stages_43;
    end else if(io_parWrEn) begin
      stages_42 <= T128;
    end
    if(reset) begin
      stages_43 <= 1'h0;
    end else if(T192) begin
      stages_43 <= stages_44;
    end else if(io_parWrEn) begin
      stages_43 <= T131;
    end
    if(reset) begin
      stages_44 <= 1'h0;
    end else if(T192) begin
      stages_44 <= stages_45;
    end else if(io_parWrEn) begin
      stages_44 <= T134;
    end
    if(reset) begin
      stages_45 <= 1'h0;
    end else if(T192) begin
      stages_45 <= stages_46;
    end else if(io_parWrEn) begin
      stages_45 <= T137;
    end
    if(reset) begin
      stages_46 <= 1'h0;
    end else if(T192) begin
      stages_46 <= stages_47;
    end else if(io_parWrEn) begin
      stages_46 <= T140;
    end
    if(reset) begin
      stages_47 <= 1'h0;
    end else if(T192) begin
      stages_47 <= stages_48;
    end else if(io_parWrEn) begin
      stages_47 <= T143;
    end
    if(reset) begin
      stages_48 <= 1'h0;
    end else if(T192) begin
      stages_48 <= stages_49;
    end else if(io_parWrEn) begin
      stages_48 <= T146;
    end
    if(reset) begin
      stages_49 <= 1'h0;
    end else if(T192) begin
      stages_49 <= stages_50;
    end else if(io_parWrEn) begin
      stages_49 <= T149;
    end
    if(reset) begin
      stages_50 <= 1'h0;
    end else if(T192) begin
      stages_50 <= stages_51;
    end else if(io_parWrEn) begin
      stages_50 <= T152;
    end
    if(reset) begin
      stages_51 <= 1'h0;
    end else if(T192) begin
      stages_51 <= stages_52;
    end else if(io_parWrEn) begin
      stages_51 <= T155;
    end
    if(reset) begin
      stages_52 <= 1'h0;
    end else if(T192) begin
      stages_52 <= stages_53;
    end else if(io_parWrEn) begin
      stages_52 <= T158;
    end
    if(reset) begin
      stages_53 <= 1'h0;
    end else if(T192) begin
      stages_53 <= stages_54;
    end else if(io_parWrEn) begin
      stages_53 <= T161;
    end
    if(reset) begin
      stages_54 <= 1'h0;
    end else if(T192) begin
      stages_54 <= stages_55;
    end else if(io_parWrEn) begin
      stages_54 <= T164;
    end
    if(reset) begin
      stages_55 <= 1'h0;
    end else if(T192) begin
      stages_55 <= stages_56;
    end else if(io_parWrEn) begin
      stages_55 <= T167;
    end
    if(reset) begin
      stages_56 <= 1'h0;
    end else if(T192) begin
      stages_56 <= stages_57;
    end else if(io_parWrEn) begin
      stages_56 <= T170;
    end
    if(reset) begin
      stages_57 <= 1'h0;
    end else if(T192) begin
      stages_57 <= stages_58;
    end else if(io_parWrEn) begin
      stages_57 <= T173;
    end
    if(reset) begin
      stages_58 <= 1'h0;
    end else if(T192) begin
      stages_58 <= stages_59;
    end else if(io_parWrEn) begin
      stages_58 <= T176;
    end
    if(reset) begin
      stages_59 <= 1'h0;
    end else if(T192) begin
      stages_59 <= stages_60;
    end else if(io_parWrEn) begin
      stages_59 <= T179;
    end
    if(reset) begin
      stages_60 <= 1'h0;
    end else if(T192) begin
      stages_60 <= stages_61;
    end else if(io_parWrEn) begin
      stages_60 <= T182;
    end
    if(reset) begin
      stages_61 <= 1'h0;
    end else if(T192) begin
      stages_61 <= stages_62;
    end else if(io_parWrEn) begin
      stages_61 <= T185;
    end
    if(reset) begin
      stages_62 <= 1'h0;
    end else if(T192) begin
      stages_62 <= stages_63;
    end else if(io_parWrEn) begin
      stages_62 <= T188;
    end
    if(reset) begin
      stages_63 <= 1'h0;
    end else if(T192) begin
      stages_63 <= io_serIn;
    end else if(io_parWrEn) begin
      stages_63 <= T191;
    end
  end
endmodule

module AXIStreamDownsizer(input clk, input reset,
    output wide_TREADY,
    input  wide_TVALID,
    input [63:0] wide_TDATA,
    input  narrow_TREADY,
    output narrow_TVALID,
    output narrow_TDATA
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
  reg [5:0] regShiftCount;
  wire[5:0] T23;
  wire[5:0] T10;
  wire[5:0] T11;
  wire[5:0] T12;
  wire[5:0] T13;
  wire T14;
  wire T15;
  wire T16;
  wire T17;
  wire T18;
  wire T19;
  wire T20;
  wire T21;
  wire shiftReg_io_serOut;

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
  assign T9 = regShiftCount == 6'h3e;
  assign T23 = reset ? 6'h0 : T10;
  assign T10 = T14 ? 6'h0 : T11;
  assign T11 = T0 ? T13 : T12;
  assign T12 = T7 ? 6'h0 : regShiftCount;
  assign T13 = regShiftCount + 6'h1;
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
  ParallelInSerialOut shiftReg(.clk(clk), .reset(reset),
       .io_parIn( wide_TDATA ),
       .io_parWrEn( T19 ),
       .io_serIn( 1'h0 ),
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
      regShiftCount <= 6'h0;
    end else if(T14) begin
      regShiftCount <= 6'h0;
    end else if(T0) begin
      regShiftCount <= T13;
    end else if(T7) begin
      regShiftCount <= 6'h0;
    end
  end
endmodule

module FrontendControllerTurbo(input clk, input reset,
    input [31:0] io_ctrl,
    input [31:0] io_colCount,
    input [31:0] io_rowCount,
    output[31:0] io_state,
    output[31:0] io_processedColCount,
    output[31:0] io_processedNZCount,
    output[31:0] io_updateCount,
    output colLengths_TREADY,
    input  colLengths_TVALID,
    input [31:0] colLengths_TDATA,
    output rowIndices_TREADY,
    input  rowIndices_TVALID,
    input [63:0] rowIndices_TDATA,
    output dvWords_TREADY,
    input  dvWords_TVALID,
    input [63:0] dvWords_TDATA,
    output[19:0] io_resMemPort1_addr,
    input [31:0] io_resMemPort1_dataRead,
    output io_resMemPort1_writeEn,
    output io_resMemPort1_dataWrite,
    output[19:0] io_resMemPort2_addr,
    input [31:0] io_resMemPort2_dataRead,
    output io_resMemPort2_writeEn,
    output io_resMemPort2_dataWrite,
    input  resultVector_TREADY,
    output resultVector_TVALID,
    output[63:0] resultVector_TDATA,
    input  writeIndices_TREADY,
    output writeIndices_TVALID,
    output[31:0] writeIndices_TDATA
);

  wire T0;
  wire T1;
  wire T2;
  wire T3;
  wire T4;
  reg [31:0] regColCount;
  wire[31:0] T103;
  wire[31:0] T5;
  wire[31:0] T6;
  wire T7;
  wire T8;
  wire T9;
  wire enableResultDump;
  wire start;
  wire T10;
  reg [2:0] regState;
  wire[2:0] T104;
  wire[2:0] T11;
  wire[2:0] T12;
  wire[2:0] T13;
  wire[2:0] T14;
  wire[2:0] T15;
  wire[2:0] T16;
  wire[2:0] T17;
  wire[2:0] T18;
  wire[2:0] T19;
  wire[2:0] T20;
  wire[2:0] T21;
  wire[2:0] T22;
  wire[2:0] T23;
  wire T24;
  wire T25;
  wire T26;
  wire T27;
  wire T28;
  wire T29;
  wire T30;
  wire T31;
  wire T32;
  wire T33;
  wire T34;
  reg [31:0] regProcessedNZCount;
  wire[31:0] T105;
  wire[31:0] T35;
  wire[31:0] T36;
  wire[31:0] T37;
  wire[31:0] T38;
  wire[31:0] T39;
  wire T40;
  wire T41;
  wire T42;
  wire T43;
  reg [31:0] regCurrentColLen;
  wire[31:0] T106;
  wire[31:0] T44;
  wire[31:0] T45;
  wire[31:0] T46;
  wire[31:0] T47;
  wire[31:0] T48;
  wire[31:0] T49;
  wire[31:0] T50;
  wire[31:0] T51;
  wire T52;
  wire[31:0] T53;
  wire T54;
  wire T55;
  wire T56;
  wire T57;
  wire T58;
  wire T59;
  wire T60;
  wire[31:0] T61;
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
  wire T75;
  wire T76;
  wire[31:0] T77;
  wire T78;
  wire T79;
  wire T80;
  reg  regStartDump;
  wire T107;
  wire T81;
  wire T82;
  wire T83;
  wire[31:0] T108;
  wire[15:0] resWordCount;
  wire T84;
  wire T85;
  wire T86;
  reg  regDenseVec;
  wire T109;
  wire T87;
  wire T88;
  wire T89;
  wire[19:0] T110;
  wire[31:0] T90;
  wire[31:0] rowIndUpper;
  wire[31:0] T111;
  wire T91;
  wire T92;
  wire T93;
  wire T94;
  wire[19:0] T112;
  wire[31:0] T95;
  wire[31:0] rowIndLower;
  wire[31:0] T113;
  wire T96;
  wire T97;
  wire T98;
  wire T99;
  wire T100;
  wire T101;
  wire[31:0] T102;
  wire[31:0] T114;
  wire resDump_io_finished;
  wire[19:0] resDump_io_readAddr1;
  wire[19:0] resDump_io_readAddr2;
  wire resDump_resultVector_TVALID;
  wire[63:0] resDump_resultVector_TDATA;
  wire resDumpQueue_io_enq_ready;
  wire resDumpQueue_io_deq_valid;
  wire[63:0] resDumpQueue_io_deq_bits;
  wire[4:0] resDumpQueue_io_count;
  wire levelGenerator_io_finished;
  wire[31:0] levelGenerator_io_writeCount;
  wire levelGenerator_io_oldData_ready;
  wire levelGenerator_io_newData_ready;
  wire levelGenerator_io_writeIndices_valid;
  wire[31:0] levelGenerator_io_writeIndices_bits;
  wire levelGenerator_io_newDataCopy_valid;
  wire[63:0] levelGenerator_io_newDataCopy_bits;
  wire dvDownsizer_wide_TREADY;
  wire dvDownsizer_narrow_TVALID;
  wire dvDownsizer_narrow_TDATA;

`ifndef SYNTHESIS
  integer initvar;
  initial begin
    #0.002;
    regColCount = {1{$random}};
    regState = {1{$random}};
    regProcessedNZCount = {1{$random}};
    regCurrentColLen = {1{$random}};
    regStartDump = {1{$random}};
    regDenseVec = {1{$random}};
  end
`endif

  assign T0 = T78 & T1;
  assign T1 = T3 & T2;
  assign T2 = colLengths_TVALID & dvDownsizer_narrow_TVALID;
  assign T3 = T4 ^ 1'h1;
  assign T4 = regColCount == 32'h0;
  assign T103 = reset ? 32'h0 : T5;
  assign T5 = T0 ? T77 : T6;
  assign T6 = T7 ? io_colCount : regColCount;
  assign T7 = T10 & T8;
  assign T8 = start & T9;
  assign T9 = enableResultDump ^ 1'h1;
  assign enableResultDump = io_ctrl[1'h1:1'h1];
  assign start = io_ctrl[1'h0:1'h0];
  assign T10 = 3'h0 == regState;
  assign T104 = reset ? 3'h0 : T11;
  assign T11 = T74 ? 3'h0 : T12;
  assign T12 = T72 ? 3'h1 : T13;
  assign T13 = T70 ? 3'h1 : T14;
  assign T14 = T69 ? 3'h1 : T15;
  assign T15 = T67 ? 3'h3 : T16;
  assign T16 = T65 ? 3'h1 : T17;
  assign T17 = T64 ? 3'h1 : T18;
  assign T18 = T62 ? 3'h2 : T19;
  assign T19 = T32 ? 3'h3 : T20;
  assign T20 = T31 ? 3'h4 : T21;
  assign T21 = T28 ? 3'h4 : T22;
  assign T22 = T24 ? 3'h5 : T23;
  assign T23 = T7 ? 3'h1 : regState;
  assign T24 = T10 & T25;
  assign T25 = T27 & T26;
  assign T26 = start & enableResultDump;
  assign T27 = T8 ^ 1'h1;
  assign T28 = T30 & T29;
  assign T29 = resDump_io_finished & levelGenerator_io_finished;
  assign T30 = 3'h5 == regState;
  assign T31 = T78 & T4;
  assign T32 = T0 & T33;
  assign T33 = T34 == 1'h0;
  assign T34 = regProcessedNZCount[1'h0:1'h0];
  assign T105 = reset ? 32'h0 : T35;
  assign T35 = T72 ? T61 : T36;
  assign T36 = T54 ? T53 : T37;
  assign T37 = T40 ? T39 : T38;
  assign T38 = T7 ? 32'h0 : regProcessedNZCount;
  assign T39 = regProcessedNZCount + 32'h1;
  assign T40 = T52 & T41;
  assign T41 = T42 & rowIndices_TVALID;
  assign T42 = T43 ^ 1'h1;
  assign T43 = regCurrentColLen == 32'h0;
  assign T106 = reset ? 32'h0 : T44;
  assign T44 = T72 ? T51 : T45;
  assign T45 = T54 ? T50 : T46;
  assign T46 = T40 ? T49 : T47;
  assign T47 = T0 ? colLengths_TDATA : T48;
  assign T48 = T7 ? 32'h0 : regCurrentColLen;
  assign T49 = regCurrentColLen - 32'h1;
  assign T50 = regCurrentColLen - 32'h2;
  assign T51 = regCurrentColLen - 32'h1;
  assign T52 = 3'h2 == regState;
  assign T53 = regProcessedNZCount + 32'h2;
  assign T54 = T56 & T55;
  assign T55 = 32'h2 <= regCurrentColLen;
  assign T56 = T60 & T57;
  assign T57 = T58 & rowIndices_TVALID;
  assign T58 = T59 ^ 1'h1;
  assign T59 = regCurrentColLen == 32'h0;
  assign T60 = 3'h3 == regState;
  assign T61 = regProcessedNZCount + 32'h1;
  assign T62 = T0 & T63;
  assign T63 = T33 ^ 1'h1;
  assign T64 = T52 & T43;
  assign T65 = T40 & T66;
  assign T66 = regCurrentColLen == 32'h1;
  assign T67 = T40 & T68;
  assign T68 = T66 ^ 1'h1;
  assign T69 = T60 & T59;
  assign T70 = T54 & T71;
  assign T71 = regCurrentColLen == 32'h2;
  assign T72 = T56 & T73;
  assign T73 = T55 ^ 1'h1;
  assign T74 = T76 & T75;
  assign T75 = start ^ 1'h1;
  assign T76 = 3'h4 == regState;
  assign T77 = regColCount - 32'h1;
  assign T78 = 3'h1 == regState;
  assign T79 = dvWords_TVALID & T80;
  assign T80 = regStartDump ^ 1'h1;
  assign T107 = reset ? 1'h0 : T81;
  assign T81 = T28 ? 1'h0 : T82;
  assign T82 = T30 ? 1'h1 : regStartDump;
  assign T83 = dvWords_TVALID & regStartDump;
  assign T108 = {27'h0, resDumpQueue_io_count};
  assign resWordCount = io_ctrl[5'h1f:5'h10];
  assign writeIndices_TDATA = levelGenerator_io_writeIndices_bits;
  assign writeIndices_TVALID = levelGenerator_io_writeIndices_valid;
  assign resultVector_TDATA = levelGenerator_io_newDataCopy_bits;
  assign resultVector_TVALID = levelGenerator_io_newDataCopy_valid;
  assign io_resMemPort2_dataWrite = 1'h1;
  assign io_resMemPort2_writeEn = T84;
  assign T84 = T54 ? T89 : T85;
  assign T85 = T40 ? T86 : 1'h0;
  assign T86 = regDenseVec;
  assign T109 = reset ? 1'h0 : T87;
  assign T87 = T0 ? dvDownsizer_narrow_TDATA : T88;
  assign T88 = T7 ? 1'h0 : regDenseVec;
  assign T89 = regDenseVec;
  assign io_resMemPort2_addr = T110;
  assign T110 = T90[5'h13:1'h0];
  assign T90 = regStartDump ? T111 : rowIndUpper;
  assign rowIndUpper = rowIndices_TDATA[6'h3f:6'h20];
  assign T111 = {12'h0, resDump_io_readAddr2};
  assign io_resMemPort1_dataWrite = 1'h1;
  assign io_resMemPort1_writeEn = T91;
  assign T91 = T72 ? T94 : T92;
  assign T92 = T54 ? T93 : 1'h0;
  assign T93 = regDenseVec;
  assign T94 = regDenseVec;
  assign io_resMemPort1_addr = T112;
  assign T112 = T95[5'h13:1'h0];
  assign T95 = regStartDump ? T113 : rowIndLower;
  assign rowIndLower = rowIndices_TDATA[5'h1f:1'h0];
  assign T113 = {12'h0, resDump_io_readAddr1};
  assign dvWords_TREADY = T96;
  assign T96 = regStartDump ? levelGenerator_io_oldData_ready : dvDownsizer_wide_TREADY;
  assign rowIndices_TREADY = T97;
  assign T97 = T60 ? T100 : T98;
  assign T98 = T52 ? T99 : 1'h0;
  assign T99 = T43 ^ 1'h1;
  assign T100 = T101 & T55;
  assign T101 = T59 ^ 1'h1;
  assign colLengths_TREADY = T0;
  assign io_updateCount = levelGenerator_io_writeCount;
  assign io_processedNZCount = regProcessedNZCount;
  assign io_processedColCount = T102;
  assign T102 = io_colCount - regColCount;
  assign io_state = T114;
  assign T114 = {29'h0, regState};
  ResultDumper resDump(.clk(clk), .reset(reset),
       .io_start( regStartDump ),
       .io_wordCount( resWordCount ),
       .io_finished( resDump_io_finished ),
       .io_readAddr1( resDump_io_readAddr1 ),
       .io_readAddr2( resDump_io_readAddr2 ),
       .io_readData1( io_resMemPort1_dataRead ),
       .io_readData2( io_resMemPort2_dataRead ),
       .resultVector_TREADY( resDumpQueue_io_enq_ready ),
       .resultVector_TVALID( resDump_resultVector_TVALID ),
       .resultVector_TDATA( resDump_resultVector_TDATA ),
       .io_fifoDataCount( T108 )
  );
  Queue resDumpQueue(.clk(clk), .reset(reset),
       .io_enq_ready( resDumpQueue_io_enq_ready ),
       .io_enq_valid( resDump_resultVector_TVALID ),
       .io_enq_bits( resDump_resultVector_TDATA ),
       .io_deq_ready( levelGenerator_io_newData_ready ),
       .io_deq_valid( resDumpQueue_io_deq_valid ),
       .io_deq_bits( resDumpQueue_io_deq_bits ),
       .io_count( resDumpQueue_io_count )
  );
  LevelGenerator levelGenerator(.clk(clk), .reset(reset),
       .io_start( regStartDump ),
       .io_bitCount( io_rowCount ),
       .io_finished( levelGenerator_io_finished ),
       .io_writeCount( levelGenerator_io_writeCount ),
       .io_oldData_ready( levelGenerator_io_oldData_ready ),
       .io_oldData_valid( T83 ),
       .io_oldData_bits( dvWords_TDATA ),
       .io_newData_ready( levelGenerator_io_newData_ready ),
       .io_newData_valid( resDumpQueue_io_deq_valid ),
       .io_newData_bits( resDumpQueue_io_deq_bits ),
       .io_writeIndices_ready( writeIndices_TREADY ),
       .io_writeIndices_valid( levelGenerator_io_writeIndices_valid ),
       .io_writeIndices_bits( levelGenerator_io_writeIndices_bits ),
       .io_newDataCopy_ready( resultVector_TREADY ),
       .io_newDataCopy_valid( levelGenerator_io_newDataCopy_valid ),
       .io_newDataCopy_bits( levelGenerator_io_newDataCopy_bits )
  );
  AXIStreamDownsizer dvDownsizer(.clk(clk), .reset(reset),
       .wide_TREADY( dvDownsizer_wide_TREADY ),
       .wide_TVALID( T79 ),
       .wide_TDATA( dvWords_TDATA ),
       .narrow_TREADY( T0 ),
       .narrow_TVALID( dvDownsizer_narrow_TVALID ),
       .narrow_TDATA( dvDownsizer_narrow_TDATA )
  );

  always @(posedge clk) begin
    if(reset) begin
      regColCount <= 32'h0;
    end else if(T0) begin
      regColCount <= T77;
    end else if(T7) begin
      regColCount <= io_colCount;
    end
    if(reset) begin
      regState <= 3'h0;
    end else if(T74) begin
      regState <= 3'h0;
    end else if(T72) begin
      regState <= 3'h1;
    end else if(T70) begin
      regState <= 3'h1;
    end else if(T69) begin
      regState <= 3'h1;
    end else if(T67) begin
      regState <= 3'h3;
    end else if(T65) begin
      regState <= 3'h1;
    end else if(T64) begin
      regState <= 3'h1;
    end else if(T62) begin
      regState <= 3'h2;
    end else if(T32) begin
      regState <= 3'h3;
    end else if(T31) begin
      regState <= 3'h4;
    end else if(T28) begin
      regState <= 3'h4;
    end else if(T24) begin
      regState <= 3'h5;
    end else if(T7) begin
      regState <= 3'h1;
    end
    if(reset) begin
      regProcessedNZCount <= 32'h0;
    end else if(T72) begin
      regProcessedNZCount <= T61;
    end else if(T54) begin
      regProcessedNZCount <= T53;
    end else if(T40) begin
      regProcessedNZCount <= T39;
    end else if(T7) begin
      regProcessedNZCount <= 32'h0;
    end
    if(reset) begin
      regCurrentColLen <= 32'h0;
    end else if(T72) begin
      regCurrentColLen <= T51;
    end else if(T54) begin
      regCurrentColLen <= T50;
    end else if(T40) begin
      regCurrentColLen <= T49;
    end else if(T0) begin
      regCurrentColLen <= colLengths_TDATA;
    end else if(T7) begin
      regCurrentColLen <= 32'h0;
    end
    if(reset) begin
      regStartDump <= 1'h0;
    end else if(T28) begin
      regStartDump <= 1'h0;
    end else if(T30) begin
      regStartDump <= 1'h1;
    end
    if(reset) begin
      regDenseVec <= 1'h0;
    end else if(T0) begin
      regDenseVec <= dvDownsizer_narrow_TDATA;
    end else if(T7) begin
      regDenseVec <= 1'h0;
    end
  end
endmodule

