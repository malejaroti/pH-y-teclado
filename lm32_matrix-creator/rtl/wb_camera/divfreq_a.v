module divfreq_cam(clkOut, clk, reset);

parameter divFactor = 50000;
parameter maxCount =  25000;

output reg clkOut;
input clk;
input reset;

always @(posedge clk) 
 begin
	if(reset)
          clkOut <= 1'b0;
	else
      	  clkOut <= ~clkOut;
 end

endmodule
