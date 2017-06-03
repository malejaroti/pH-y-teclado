`timescale 1ns / 1ps

module ram_cam #(
    parameter mem_file_name = "none",
//    parameter ram_width = 120,
    parameter ram_addwidth = 4
) (
    input ClkRd,
    input ClkWr,
    input [ram_addwidth-1:0] add,
    input [3:0] dataIn,
    output reg [3:0] dataOut
);

  reg [7:0] BYTE[3:0];
  
  initial
     if (mem_file_name != "none")
          $readmemh (mem_file_name, BYTE);
  
  always @ (posedge ClkRd)begin
     dataOut   <= BYTE[add];
     if(ClkWr)begin
       BYTE[add] <= dataIn;
    end
  end
      
endmodule
