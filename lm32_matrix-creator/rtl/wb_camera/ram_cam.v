`timescale 1ns / 1ps

module ram_cam #(
    parameter mem_file_name = "none",
    parameter ram_width = 120,
    parameter ram_addwidth = 4
) (
    input ClkRd,
    input ClkWr,
    input [ram_addwidth-1:0] addw,
    input [ram_addwidth-1:0] addrd,
    input [3:0] dataIn,
    output reg [3:0] dataOut
);

  reg [119:0] BYTE[3:0];
 
  
  initial
     if (mem_file_name != "none")
          $readmemh (mem_file_name, BYTE);
  
 always @ (posedge ClkRd)begin
     dataOut <= BYTE[addrd];
     if(ClkWr)begin
       BYTE[addw] <= dataIn;
	end
      if(ClkRd)begin
       dataOut <= BYTE[addrd];
   	end
  end
      
endmodule
