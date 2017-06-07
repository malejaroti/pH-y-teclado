
module camera(vsync, data, href, dataOut, ready, pclk, clkOut,rd, add_rd);

parameter ram_addwidth = 4;
input wire vsync;
input wire [7:0]data;
input wire href;
input pclk;
input rd;
input [3:0] add_rd;
output wire clkOut;

//cam
wire we;
wire [18:0] addr;
wire [7:0] dataHI;
wire [7:0] dataLO;
output ready;
//ram

output wire [3:0] dataOut;


 
camera_1 cm (.data(data), .vsync(vsync), .href(href), .pclk(pclk), .ready(ready), .we(we), .dataHI(dataHI), .addr(addr));

ram_cam #(.ram_addwidth(ram_addwidth)) 

ram_cam (.ClkWr(we),.ClkRd(rd), .addw(addr), .addrd(add_rd), .dataIn(dataHI[7:4]), .dataOut(dataOut));

endmodule


