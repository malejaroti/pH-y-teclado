
module keypad(clk, reset, data, int, column, row);

input wire clk;
input wire reset;
input [3:0] row;

output wire [3:0] data;
output wire int;
output wire [3:0] column;

wire clk1Khz;

divfreq div1 (.clkOut(clk1Khz), .clk(clk), .reset(1'b1));
 
keypad_1 kp (.clk1(clk1Khz), .reset(1'b0), .keypad_data(data), .interrupt(int), .column(column), .row(row));

endmodule
