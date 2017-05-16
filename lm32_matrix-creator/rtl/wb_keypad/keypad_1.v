module keypad_1(reset, clk1, row, column, interrupt, keypad_data);

// INPUTS & OUTPUTS 

	input reset;
	input clk1;
	input [3:0] row;

	output reg [3:0] column;
	output reg interrupt;
	output reg [3:0] keypad_data;
	
	reg [1:0] sel;

//contador de 2bits

always @(posedge clk1 or posedge reset)
  begin
	if(reset)
	  sel = 0;
	else if (row == 4'b1111)
	  sel = sel + 1;
	else 
	 sel = sel;
  end

//keypad driver
//stops scanning if a key press is detected ( by column returning a 0 anywhere )

always @(*) // PREGUNTAR POR EL *
 begin
	begin
	 case(sel)
	 0 : column = 4'b0111;
	 1 : column = 4'b1011;
	 2 : column = 4'b1101;
	 3 : column = 4'b1110;
	 default : column = 4'bxxxx;
	 endcase
	end

 end

always @(posedge clk1) 
 begin
	if (row == 4'b1111) begin
	  interrupt = 0;
	end else begin
	  interrupt = 1;
	end

 end 



always@(*)
 begin
	case({sel,row})
	6'b001110 : keypad_data <= 4'hA; // A
	6'b001101 : keypad_data <= 4'hB; // B
	6'b001011 : keypad_data <= 4'hC; // C
	6'b000111 : keypad_data <= 4'hD; // D
	6'b011110 : keypad_data <= 4'h3; // 3
	6'b011101 : keypad_data <= 4'h6; // 6
	6'b011011 : keypad_data <= 4'h9; // 9
	6'b010111 : keypad_data <= 4'hE; // E#
	6'b101110 : keypad_data <= 4'h2; // 2
	6'b101101 : keypad_data <= 4'h5; // 5
	6'b101011 : keypad_data <= 4'h8; // 8
	6'b100111 : keypad_data <= 4'h0; // 0
	6'b111110 : keypad_data <= 4'h1; // 1
	6'b111101 : keypad_data <= 4'h4; // 4
	6'b111011 : keypad_data <= 4'h7; // 7
	6'b110111 : keypad_data <= 4'hF; // F*
	default   : keypad_data <= 4'bXXXX;
	endcase
 end
endmodule
