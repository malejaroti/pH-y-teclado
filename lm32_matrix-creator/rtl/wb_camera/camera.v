
module camera(clk50MHz, reset, vsync, data, href, dataOut, ready, pclk, clkOut);

parameter ram_addwidth = 4;
input wire clk50MHz;
input wire reset;
input wire vsync;
input wire [7:0]data;
input wire href;
output wire clkOut;
input wire pclk;


//cam
wire we;
wire [18:0] addr;
wire [7:0] dataHI;
wire [7:0] dataLO;
output ready;
//ram

//input ClkRd;
//input ClkWr;
//input [ram_addwidth-1:0] add;
//input [3:0] dataIn;
output wire [3:0] dataOut;


divfreq_cam div (.clkOut(clkOut), .clk(clk50MHz), .reset(reset));
 
camera_1 cm (.data(data), .vsync(vsync), .href(href), .pclk(pclk), .ready(ready), .we(we), .dataHI(dataHI), .addr(addr));

ram_cam #(.ram_addwidth(ram_addwidth)) 

ram_cam (.ClkRd(clk1Khz), .ClkWr(we), .add(addr), .dataIn(dataHI[7:4]), .dataOut(dataOut));

endmodule


