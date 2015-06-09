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
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    R1 = {1{$random}};
    R4 = {1{$random}};
    maybe_full = {1{$random}};
    for (initvar = 0; initvar < 16; initvar = initvar+1)
      ram[initvar] = {2{$random}};
  end
// synthesis translate_on
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
    output[63:0] resultVector_TDATA
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
  wire resDumpQueue_io_deq_valid;
  wire[63:0] resDumpQueue_io_deq_bits;
  wire[4:0] resDumpQueue_io_count;

`ifndef SYNTHESIS
// synthesis translate_off
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
// synthesis translate_on
`endif

  assign T0 = {io_readData2, io_readData1};
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
  assign hasRoom = resDumpQueue_io_count < 5'h9;
  assign T28 = T15 ^ 1'h1;
  assign T46 = {28'h0, T29};
  assign T29 = regReqCount - 4'h1;
  assign T30 = 2'h2 == regState;
  assign resultVector_TDATA = resDumpQueue_io_deq_bits;
  assign resultVector_TVALID = resDumpQueue_io_deq_valid;
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
  Queue resDumpQueue(.clk(clk), .reset(reset),
       //.io_enq_ready(  )
       .io_enq_valid( regValid3 ),
       .io_enq_bits( T0 ),
       .io_deq_ready( resultVector_TREADY ),
       .io_deq_valid( resDumpQueue_io_deq_valid ),
       .io_deq_bits( resDumpQueue_io_deq_bits ),
       .io_count( resDumpQueue_io_count )
  );

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

module SparseFrontierFrontend(input clk, input reset,
    input [31:0] io_ctrl,
    output[31:0] io_state,
    input [31:0] io_rowCount,
    output[31:0] io_frontierSize,
    input [31:0] io_expectedFrontierSize,
    output[31:0] io_processedNZCount,
    output rowIndData_TREADY,
    input  rowIndData_TVALID,
    input [63:0] rowIndData_TDATA,
    output rowIndMetadata_TREADY,
    input  rowIndMetadata_TVALID,
    input [31:0] rowIndMetadata_TDATA,
    output[19:0] io_resMemPort1_addr,
    input [31:0] io_resMemPort1_dataRead,
    output io_resMemPort1_writeEn,
    output io_resMemPort1_dataWrite,
    output[19:0] io_resMemPort2_addr,
    input [31:0] io_resMemPort2_dataRead,
    output io_resMemPort2_writeEn,
    output io_resMemPort2_dataWrite,
    input  resultVectorOut_TREADY,
    output resultVectorOut_TVALID,
    output[63:0] resultVectorOut_TDATA
);

  wire[15:0] T0;
  reg [31:0] regRowCount;
  wire[31:0] T87;
  wire[31:0] T1;
  wire T2;
  reg [2:0] regState;
  wire[2:0] T88;
  wire[2:0] T3;
  wire[2:0] T4;
  wire[2:0] T5;
  wire[2:0] T6;
  wire[2:0] T7;
  wire[2:0] T8;
  wire[2:0] T9;
  wire[2:0] T10;
  wire[2:0] T11;
  wire T12;
  wire enableBRAMReset;
  wire T13;
  wire startAccel;
  wire T14;
  wire T15;
  wire enableBRAMDump;
  wire T16;
  wire T17;
  wire T18;
  wire T19;
  wire T20;
  wire T21;
  wire[31:0] T89;
  reg [19:0] regResetAddr;
  wire[19:0] T90;
  wire[19:0] T22;
  wire[19:0] T23;
  wire[19:0] T24;
  wire T25;
  wire T26;
  wire[31:0] T27;
  wire T28;
  wire T29;
  wire T30;
  wire T31;
  wire T32;
  reg [31:0] regFrontierSize;
  wire[31:0] T91;
  wire[31:0] T33;
  wire[31:0] T34;
  wire[31:0] T35;
  wire T36;
  wire T37;
  wire T38;
  wire T39;
  wire T40;
  wire T41;
  reg [30:0] regRowIndsLeftInCol;
  wire[30:0] T92;
  wire[30:0] T42;
  wire[30:0] T43;
  wire[30:0] T44;
  wire[30:0] T45;
  wire[30:0] T46;
  wire[30:0] T47;
  wire T48;
  wire T49;
  reg  regAligned;
  wire T93;
  wire T50;
  wire T51;
  wire T52;
  wire T53;
  wire T54;
  wire T55;
  wire T56;
  wire[30:0] T57;
  wire T58;
  wire T59;
  wire T60;
  wire T61;
  wire[30:0] T62;
  wire T63;
  wire T64;
  wire T65;
  wire T66;
  wire T67;
  wire T68;
  reg  regStartDump;
  wire T94;
  wire T69;
  wire T70;
  wire T71;
  wire T72;
  wire T73;
  wire[19:0] T95;
  wire[31:0] T74;
  wire[31:0] T75;
  wire[31:0] rowIndUpper;
  wire[31:0] T96;
  wire[31:0] T97;
  wire[19:0] T76;
  wire T77;
  wire[19:0] T98;
  wire[31:0] T78;
  wire[31:0] T79;
  wire[31:0] rowIndLower;
  wire[31:0] T99;
  wire[31:0] T100;
  reg [31:0] regNZCount;
  wire[31:0] T101;
  wire[31:0] T80;
  wire[31:0] T81;
  wire[31:0] T82;
  wire[31:0] T83;
  wire[31:0] T84;
  wire[31:0] T85;
  wire[31:0] T86;
  wire[31:0] T102;
  wire resDump_io_finished;
  wire[19:0] resDump_io_readAddr1;
  wire[19:0] resDump_io_readAddr2;
  wire resDump_resultVector_TVALID;
  wire[63:0] resDump_resultVector_TDATA;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    regRowCount = {1{$random}};
    regState = {1{$random}};
    regResetAddr = {1{$random}};
    regFrontierSize = {1{$random}};
    regRowIndsLeftInCol = {1{$random}};
    regAligned = {1{$random}};
    regStartDump = {1{$random}};
    regNZCount = {1{$random}};
  end
// synthesis translate_on
`endif

  assign T0 = regRowCount[5'h15:3'h6];
  assign T87 = reset ? 32'h0 : T1;
  assign T1 = T2 ? io_rowCount : regRowCount;
  assign T2 = 3'h0 == regState;
  assign T88 = reset ? 3'h0 : T3;
  assign T3 = T66 ? 3'h0 : T4;
  assign T4 = T40 ? 3'h3 : T5;
  assign T5 = T37 ? 3'h4 : T6;
  assign T6 = T31 ? 3'h5 : T7;
  assign T7 = T29 ? 3'h5 : T8;
  assign T8 = T20 ? 3'h5 : T9;
  assign T9 = T17 ? 3'h3 : T10;
  assign T10 = T14 ? 3'h2 : T11;
  assign T11 = T12 ? 3'h1 : regState;
  assign T12 = T13 & enableBRAMReset;
  assign enableBRAMReset = io_ctrl[2'h2:2'h2];
  assign T13 = T2 & startAccel;
  assign startAccel = io_ctrl[1'h0:1'h0];
  assign T14 = T13 & T15;
  assign T15 = T16 & enableBRAMDump;
  assign enableBRAMDump = io_ctrl[1'h1:1'h1];
  assign T16 = enableBRAMReset ^ 1'h1;
  assign T17 = T13 & T18;
  assign T18 = T19 ^ 1'h1;
  assign T19 = enableBRAMReset | enableBRAMDump;
  assign T20 = T28 & T21;
  assign T21 = T27 <= T89;
  assign T89 = {12'h0, regResetAddr};
  assign T90 = reset ? 20'h0 : T22;
  assign T22 = T25 ? T24 : T23;
  assign T23 = T2 ? 20'h0 : regResetAddr;
  assign T24 = regResetAddr + 20'h2;
  assign T25 = T28 & T26;
  assign T26 = T21 ^ 1'h1;
  assign T27 = regRowCount - 32'h1;
  assign T28 = 3'h1 == regState;
  assign T29 = T30 & resDump_io_finished;
  assign T30 = 3'h2 == regState;
  assign T31 = T36 & T32;
  assign T32 = regFrontierSize == io_expectedFrontierSize;
  assign T91 = reset ? 32'h0 : T33;
  assign T33 = T37 ? T35 : T34;
  assign T34 = T17 ? 32'h0 : regFrontierSize;
  assign T35 = regFrontierSize + 32'h1;
  assign T36 = 3'h3 == regState;
  assign T37 = T38 & rowIndMetadata_TVALID;
  assign T38 = T36 & T39;
  assign T39 = T32 ^ 1'h1;
  assign T40 = T65 & T41;
  assign T41 = regRowIndsLeftInCol == 31'h0;
  assign T92 = reset ? 31'h0 : T42;
  assign T42 = T63 ? T62 : T43;
  assign T43 = T58 ? T57 : T44;
  assign T44 = T48 ? T47 : T45;
  assign T45 = T38 ? T46 : regRowIndsLeftInCol;
  assign T46 = rowIndMetadata_TDATA[5'h1e:1'h0];
  assign T47 = regRowIndsLeftInCol - 31'h1;
  assign T48 = T54 & T49;
  assign T49 = regAligned == 1'h0;
  assign T93 = reset ? 1'h0 : T50;
  assign T50 = T58 ? 1'h0 : T51;
  assign T51 = T48 ? 1'h1 : T52;
  assign T52 = T38 ? T53 : regAligned;
  assign T53 = rowIndMetadata_TDATA[5'h1f:5'h1f];
  assign T54 = T55 & rowIndData_TVALID;
  assign T55 = T65 & T56;
  assign T56 = T41 ^ 1'h1;
  assign T57 = regRowIndsLeftInCol - 31'h1;
  assign T58 = T60 & T59;
  assign T59 = regRowIndsLeftInCol == 31'h1;
  assign T60 = T54 & T61;
  assign T61 = T49 ^ 1'h1;
  assign T62 = regRowIndsLeftInCol - 31'h2;
  assign T63 = T60 & T64;
  assign T64 = T59 ^ 1'h1;
  assign T65 = 3'h4 == regState;
  assign T66 = T68 & T67;
  assign T67 = startAccel ^ 1'h1;
  assign T68 = 3'h5 == regState;
  assign T94 = reset ? 1'h0 : T69;
  assign T69 = T29 ? 1'h0 : T70;
  assign T70 = T14 ? 1'h1 : T71;
  assign T71 = T2 ? 1'h0 : regStartDump;
  assign resultVectorOut_TDATA = resDump_resultVector_TDATA;
  assign resultVectorOut_TVALID = resDump_resultVector_TVALID;
  assign io_resMemPort2_dataWrite = T65;
  assign io_resMemPort2_writeEn = T72;
  assign T72 = T63 ? 1'h1 : T73;
  assign T73 = T48 ? 1'h1 : T25;
  assign io_resMemPort2_addr = T95;
  assign T95 = T74[5'h13:1'h0];
  assign T74 = T25 ? T97 : T75;
  assign T75 = regStartDump ? T96 : rowIndUpper;
  assign rowIndUpper = rowIndData_TDATA[6'h3f:6'h20];
  assign T96 = {12'h0, resDump_io_readAddr2};
  assign T97 = {12'h0, T76};
  assign T76 = regResetAddr + 20'h1;
  assign io_resMemPort1_dataWrite = T65;
  assign io_resMemPort1_writeEn = T77;
  assign T77 = T60 ? 1'h1 : T25;
  assign io_resMemPort1_addr = T98;
  assign T98 = T78[5'h13:1'h0];
  assign T78 = T25 ? T100 : T79;
  assign T79 = regStartDump ? T99 : rowIndLower;
  assign rowIndLower = rowIndData_TDATA[5'h1f:1'h0];
  assign T99 = {12'h0, resDump_io_readAddr1};
  assign T100 = {12'h0, regResetAddr};
  assign rowIndMetadata_TREADY = T38;
  assign rowIndData_TREADY = T55;
  assign io_processedNZCount = regNZCount;
  assign T101 = reset ? 32'h0 : T80;
  assign T80 = T63 ? T86 : T81;
  assign T81 = T58 ? T85 : T82;
  assign T82 = T48 ? T84 : T83;
  assign T83 = T17 ? 32'h0 : regNZCount;
  assign T84 = regNZCount + 32'h1;
  assign T85 = regNZCount + 32'h1;
  assign T86 = regNZCount + 32'h2;
  assign io_frontierSize = regFrontierSize;
  assign io_state = T102;
  assign T102 = {29'h0, regState};
  ResultDumper resDump(.clk(clk), .reset(reset),
       .io_start( regStartDump ),
       .io_wordCount( T0 ),
       .io_finished( resDump_io_finished ),
       .io_readAddr1( resDump_io_readAddr1 ),
       .io_readAddr2( resDump_io_readAddr2 ),
       .io_readData1( io_resMemPort1_dataRead ),
       .io_readData2( io_resMemPort2_dataRead ),
       .resultVector_TREADY( resultVectorOut_TREADY ),
       .resultVector_TVALID( resDump_resultVector_TVALID ),
       .resultVector_TDATA( resDump_resultVector_TDATA )
  );

  always @(posedge clk) begin
    if(reset) begin
      regRowCount <= 32'h0;
    end else if(T2) begin
      regRowCount <= io_rowCount;
    end
    if(reset) begin
      regState <= 3'h0;
    end else if(T66) begin
      regState <= 3'h0;
    end else if(T40) begin
      regState <= 3'h3;
    end else if(T37) begin
      regState <= 3'h4;
    end else if(T31) begin
      regState <= 3'h5;
    end else if(T29) begin
      regState <= 3'h5;
    end else if(T20) begin
      regState <= 3'h5;
    end else if(T17) begin
      regState <= 3'h3;
    end else if(T14) begin
      regState <= 3'h2;
    end else if(T12) begin
      regState <= 3'h1;
    end
    if(reset) begin
      regResetAddr <= 20'h0;
    end else if(T25) begin
      regResetAddr <= T24;
    end else if(T2) begin
      regResetAddr <= 20'h0;
    end
    if(reset) begin
      regFrontierSize <= 32'h0;
    end else if(T37) begin
      regFrontierSize <= T35;
    end else if(T17) begin
      regFrontierSize <= 32'h0;
    end
    if(reset) begin
      regRowIndsLeftInCol <= 31'h0;
    end else if(T63) begin
      regRowIndsLeftInCol <= T62;
    end else if(T58) begin
      regRowIndsLeftInCol <= T57;
    end else if(T48) begin
      regRowIndsLeftInCol <= T47;
    end else if(T38) begin
      regRowIndsLeftInCol <= T46;
    end
    if(reset) begin
      regAligned <= 1'h0;
    end else if(T58) begin
      regAligned <= 1'h0;
    end else if(T48) begin
      regAligned <= 1'h1;
    end else if(T38) begin
      regAligned <= T53;
    end
    if(reset) begin
      regStartDump <= 1'h0;
    end else if(T29) begin
      regStartDump <= 1'h0;
    end else if(T14) begin
      regStartDump <= 1'h1;
    end else if(T2) begin
      regStartDump <= 1'h0;
    end
    if(reset) begin
      regNZCount <= 32'h0;
    end else if(T63) begin
      regNZCount <= T86;
    end else if(T58) begin
      regNZCount <= T85;
    end else if(T48) begin
      regNZCount <= T84;
    end else if(T17) begin
      regNZCount <= 32'h0;
    end
  end
endmodule
