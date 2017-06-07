//---------------------------------------------------------------------------
//
// Wishbone keypad
//
// Register Description:
//
//    0x0000 keypad_data : Dato que sale del teclado
//
//---------------------------------------------------------------------------

module wb_keypad (
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
   // Keypad data
   input [3:0] row,
   output [3:0] column,
   output interrupt
);

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
reg  ack;
assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;

wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;
wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;

wire [3:0] keypad_data;

keypad_1 keypad_1(
  .reset(reset), 
  .clk1(clk),
  .row(row), 
  .column(column), 
  .interrupt(interrupt), 
  .keypad_data(keypad_data)
);

always @(posedge clk)
  begin
    if (reset) begin
      ack         <= 0;
    end else begin

      // Handle WISHBONE access
      ack    <= 0;

     if (wb_rd & ~ack) begin           // read cycle
       ack <= 1;
       case (wb_adr_i[3:0])
       'h0:  wb_dat_o           <= {28'h0,keypad_data};
       endcase
     end else if (wb_wr & ~ack ) begin // write cycle
       ack <= 1;
     end
    end
  end

endmodule
