//---------------------------------------------------------------------------
//
// Wishbone camera
//
// Register Description:
//
//    0x0000 data : Dato que sale de la cámara
//
//---------------------------------------------------------------------------

module wb_camera (

   input              clk,
   input              reset, //reset
   // Wishbone interface
   input              wb_stb_i,
   input              wb_cyc_i,
   output             wb_ack_o,
   input              wb_we_i,
   input       [31:0] wb_adr_i,
   input       [3:0] wb_sel_i,
   input       [31:0] wb_dat_i,
   output reg  [31:0] wb_dat_o,
   // Camera data

   input vsync,
   input href,
   input pclk,
   input [7:0] data,
   output ready,

   //ram data
    output [3:0] dataOut,
    output clkOut
);
//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
reg  ack;
assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;

wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;
wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;


camera_1 camera_1(
  .vsync(vsync), 
  .pclk(pclk),
  .data(data), 
  .href(href), 
  .we(we),
  .addr(addr),
  .dataHI(dataHI),
  .dataLO(dataLO)
);

ram_cam ram_cam(
  .ClkRd(ClkRd),
  .ClkWr(ClkWr),
  .add(add),
  .dataIn(dataIn),
  .dataOut(dataOut)
);

divfreq_cam divfreq_cam(
  .clkOut(clkOut),
  .clk(clk),
  .reset(reset)
);


always @(posedge clk)
begin
	if (reset) begin
		ack      <= 0;
	end else begin

		// Handle WISHBONE access
		ack    <= 0;

		if (wb_rd & ~ack) begin           // read cycle
			ack <= 1;

			case (wb_adr_i[3:0])
			'h0: wb_dat_o <= {31'h0,ready};
			'h4: wb_dat_o <= {24'h0,data};
			endcase
		end else if (wb_wr & ~ack ) begin // write cycle
			ack <= 1;

			end
	end
end


endmodule


