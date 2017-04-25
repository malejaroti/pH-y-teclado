module divfreq(clkOut, clk, reset);

parameter divFactor = 50000;
parameter maxCount =  25000;
parameter counterWidth = 16; //edit

output reg clkOut;
input clk;
input reset;

reg [counterWidth-1: 0] Q;

always @(posedge clk, negedge reset) 
 begin
	if(~reset) begin
          Q <= 0;
          clkOut <= 1'b0;
	end else if (Q == (maxCount -1)) begin
     	  Q <= 0;
      	  clkOut <= ~clkOut;
     	end else begin
	  Q <= Q + 1;
     	end
 end

endmodule
