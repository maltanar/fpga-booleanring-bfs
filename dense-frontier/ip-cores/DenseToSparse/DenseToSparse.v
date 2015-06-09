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

module Queue32(input clk, input reset,
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

module DenseToSparse(input clk, input reset,
    input [31:0] io_denseBasePtr,
    input [31:0] io_sparseBasePtr,
    input [31:0] io_denseCount,
    input [31:0] io_lookFor,
    output[31:0] io_sparseCount,
    input  io_start,
    output io_finished,
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
    input [1:0] aximm32_RRESP
);

  wire[7:0] T56;
  wire[3:0] T0;
  wire[3:0] T1;
  wire[3:0] T2;
  wire T3;
  reg [31:0] regReadReqsLeft;
  wire[31:0] T57;
  wire[31:0] T4;
  wire[31:0] T5;
  wire T6;
  wire T7;
  reg [1:0] regState;
  wire[1:0] T58;
  wire[1:0] T8;
  wire[1:0] T9;
  wire[1:0] T10;
  wire[1:0] T11;
  wire[1:0] T12;
  wire[1:0] T13;
  wire[1:0] T14;
  wire[1:0] T15;
  wire T16;
  wire T17;
  wire T18;
  wire T19;
  wire T20;
  wire T21;
  wire T22;
  wire T23;
  wire T24;
  wire T25;
  wire T26;
  reg [31:0] regWriteReqCnt;
  wire[31:0] T59;
  wire[31:0] T27;
  wire[31:0] T28;
  wire[31:0] T29;
  wire T30;
  wire T31;
  wire T32;
  wire T33;
  wire T34;
  wire T35;
  wire T36;
  wire T37;
  wire T38;
  wire T39;
  wire T40;
  wire T41;
  wire[31:0] T42;
  wire[31:0] T60;
  wire T43;
  wire T44;
  wire T45;
  wire T46;
  reg [31:0] regReadReqPtr;
  wire[31:0] T61;
  wire[31:0] T47;
  wire[31:0] T48;
  wire[31:0] T49;
  wire[31:0] T62;
  wire[6:0] T50;
  wire T51;
  wire T52;
  reg [31:0] regWriteReqPtr;
  wire[31:0] T63;
  wire[31:0] T53;
  wire[31:0] T54;
  wire[31:0] T55;
  wire frontierFilter_io_finished;
  wire[31:0] frontierFilter_io_frontierSize;
  wire frontierFilter_distVecIn_TREADY;
  wire frontierFilter_frontierOut_TVALID;
  wire[31:0] frontierFilter_frontierOut_TDATA;
  wire sparseQueue_io_enq_ready;
  wire sparseQueue_io_deq_valid;
  wire[31:0] sparseQueue_io_deq_bits;
  wire denseQueue_io_enq_ready;
  wire denseQueue_io_deq_valid;
  wire[31:0] denseQueue_io_deq_bits;
  wire[5:0] denseQueue_io_count;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    regReadReqsLeft = {1{$random}};
    regState = {1{$random}};
    regWriteReqCnt = {1{$random}};
    regReadReqPtr = {1{$random}};
    regWriteReqPtr = {1{$random}};
  end
// synthesis translate_on
`endif

  assign aximm32_RREADY = denseQueue_io_enq_ready;
  assign aximm32_ARQOS = 4'h0;
  assign aximm32_ARPROT = 3'h0;
  assign aximm32_ARCACHE = 4'h2;
  assign aximm32_ARLOCK = 1'h0;
  assign aximm32_ARID = 2'h0;
  assign aximm32_ARBURST = 2'h1;
  assign aximm32_ARLEN = T56;
  assign T56 = {4'h0, T0};
  assign T0 = T44 ? T1 : 4'h0;
  assign T1 = T2 - 4'h1;
  assign T2 = T3 ? 4'h1 : 4'h8;
  assign T3 = regReadReqsLeft < 32'h8;
  assign T57 = reset ? 32'h0 : T4;
  assign T4 = T43 ? T42 : T5;
  assign T5 = T6 ? io_denseCount : regReadReqsLeft;
  assign T6 = T7 & io_start;
  assign T7 = 2'h0 == regState;
  assign T58 = reset ? 2'h0 : T8;
  assign T8 = T39 ? 2'h0 : T9;
  assign T9 = T36 ? 2'h1 : T10;
  assign T10 = T31 ? 2'h1 : T11;
  assign T11 = T24 ? 2'h3 : T12;
  assign T12 = T43 ? 2'h2 : T13;
  assign T13 = T19 ? 2'h2 : T14;
  assign T14 = T16 ? 2'h2 : T15;
  assign T15 = T6 ? 2'h1 : regState;
  assign T16 = T18 & T17;
  assign T17 = regReadReqsLeft == 32'h0;
  assign T18 = 2'h1 == regState;
  assign T19 = T18 & T20;
  assign T20 = T23 & T21;
  assign T21 = T22 ^ 1'h1;
  assign T22 = denseQueue_io_count < 6'h8;
  assign T23 = T17 ^ 1'h1;
  assign T24 = T30 & T25;
  assign T25 = T26 & frontierFilter_io_finished;
  assign T26 = regWriteReqCnt == frontierFilter_io_frontierSize;
  assign T59 = reset ? 32'h0 : T27;
  assign T27 = T31 ? T29 : T28;
  assign T28 = T6 ? 32'h0 : regWriteReqCnt;
  assign T29 = regWriteReqCnt + 32'h1;
  assign T30 = 2'h2 == regState;
  assign T31 = T32 & aximm32_AWREADY;
  assign T32 = T30 & T33;
  assign T33 = T35 & T34;
  assign T34 = T26 ^ 1'h1;
  assign T35 = T25 ^ 1'h1;
  assign T36 = T30 & T37;
  assign T37 = T38 ^ 1'h1;
  assign T38 = T25 | T34;
  assign T39 = T41 & T40;
  assign T40 = io_start ^ 1'h1;
  assign T41 = 2'h3 == regState;
  assign T42 = regReadReqsLeft - T60;
  assign T60 = {28'h0, T2};
  assign T43 = T44 & aximm32_ARREADY;
  assign T44 = T18 & T45;
  assign T45 = T46 ^ 1'h1;
  assign T46 = T17 | T21;
  assign aximm32_ARSIZE = 3'h2;
  assign aximm32_ARADDR = regReadReqPtr;
  assign T61 = reset ? 32'h0 : T47;
  assign T47 = T43 ? T49 : T48;
  assign T48 = T6 ? io_denseBasePtr : regReadReqPtr;
  assign T49 = regReadReqPtr + T62;
  assign T62 = {25'h0, T50};
  assign T50 = 3'h4 * T2;
  assign aximm32_ARVALID = T44;
  assign aximm32_BREADY = T51;
  assign T51 = T52 ^ 1'h1;
  assign T52 = regState == 2'h0;
  assign aximm32_WLAST = 1'h1;
  assign aximm32_WSTRB = 4'hf;
  assign aximm32_WDATA = sparseQueue_io_deq_bits;
  assign aximm32_WVALID = sparseQueue_io_deq_valid;
  assign aximm32_AWQOS = 4'h0;
  assign aximm32_AWPROT = 3'h0;
  assign aximm32_AWCACHE = 4'h2;
  assign aximm32_AWLOCK = 1'h0;
  assign aximm32_AWID = 2'h0;
  assign aximm32_AWBURST = 2'h1;
  assign aximm32_AWLEN = 8'h0;
  assign aximm32_AWSIZE = 3'h2;
  assign aximm32_AWADDR = regWriteReqPtr;
  assign T63 = reset ? 32'h0 : T53;
  assign T53 = T31 ? T55 : T54;
  assign T54 = T6 ? io_sparseBasePtr : regWriteReqPtr;
  assign T55 = regWriteReqPtr + 32'h4;
  assign aximm32_AWVALID = T32;
  assign io_finished = T41;
  assign io_sparseCount = frontierFilter_io_frontierSize;
  FrontierFilter frontierFilter(.clk(clk), .reset(reset),
       .io_start( io_start ),
       .io_finished( frontierFilter_io_finished ),
       .io_distVecCount( io_denseCount ),
       .io_currentLevel( io_lookFor ),
       .io_frontierSize( frontierFilter_io_frontierSize ),
       .distVecIn_TREADY( frontierFilter_distVecIn_TREADY ),
       .distVecIn_TVALID( denseQueue_io_deq_valid ),
       .distVecIn_TDATA( denseQueue_io_deq_bits ),
       .frontierOut_TREADY( sparseQueue_io_enq_ready ),
       .frontierOut_TVALID( frontierFilter_frontierOut_TVALID ),
       .frontierOut_TDATA( frontierFilter_frontierOut_TDATA )
  );
  Queue32 sparseQueue(.clk(clk), .reset(reset),
       .io_enq_ready( sparseQueue_io_enq_ready ),
       .io_enq_valid( frontierFilter_frontierOut_TVALID ),
       .io_enq_bits( frontierFilter_frontierOut_TDATA ),
       .io_deq_ready( aximm32_WREADY ),
       .io_deq_valid( sparseQueue_io_deq_valid ),
       .io_deq_bits( sparseQueue_io_deq_bits )
       //.io_count(  )
  );
  Queue32 denseQueue(.clk(clk), .reset(reset),
       .io_enq_ready( denseQueue_io_enq_ready ),
       .io_enq_valid( aximm32_RVALID ),
       .io_enq_bits( aximm32_RDATA ),
       .io_deq_ready( frontierFilter_distVecIn_TREADY ),
       .io_deq_valid( denseQueue_io_deq_valid ),
       .io_deq_bits( denseQueue_io_deq_bits ),
       .io_count( denseQueue_io_count )
  );

  always @(posedge clk) begin
    if(reset) begin
      regReadReqsLeft <= 32'h0;
    end else if(T43) begin
      regReadReqsLeft <= T42;
    end else if(T6) begin
      regReadReqsLeft <= io_denseCount;
    end
    if(reset) begin
      regState <= 2'h0;
    end else if(T39) begin
      regState <= 2'h0;
    end else if(T36) begin
      regState <= 2'h1;
    end else if(T31) begin
      regState <= 2'h1;
    end else if(T24) begin
      regState <= 2'h3;
    end else if(T43) begin
      regState <= 2'h2;
    end else if(T19) begin
      regState <= 2'h2;
    end else if(T16) begin
      regState <= 2'h2;
    end else if(T6) begin
      regState <= 2'h1;
    end
    if(reset) begin
      regWriteReqCnt <= 32'h0;
    end else if(T31) begin
      regWriteReqCnt <= T29;
    end else if(T6) begin
      regWriteReqCnt <= 32'h0;
    end
    if(reset) begin
      regReadReqPtr <= 32'h0;
    end else if(T43) begin
      regReadReqPtr <= T49;
    end else if(T6) begin
      regReadReqPtr <= io_denseBasePtr;
    end
    if(reset) begin
      regWriteReqPtr <= 32'h0;
    end else if(T31) begin
      regWriteReqPtr <= T55;
    end else if(T6) begin
      regWriteReqPtr <= io_sparseBasePtr;
    end
  end
endmodule

