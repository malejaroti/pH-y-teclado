
module keypad(data, int, column, row);

input [3:0] row;
output wire [3:0] data;
output wire int;
output wire [3:0] column;

wire clk1Khz;

 
keypad_1 kp (.clk1(clk1Khz), .keypad_data(data), .interrupt(int), .column(column), .row(row));

endmodule
