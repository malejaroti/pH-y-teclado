/*

Desing name: camera OV7670
File Name: camera.v

*/

module camera_1 #(
	parameter 	h_frame = 1536/2, // 240 en ov7670
	parameter	v_frame = 2048/2, //320 en ov7670
	parameter	e0 =3'b000,
	parameter	e1 =3'b001,
	parameter	e2 =3'b010,
	parameter	e3 =3'b011,
	parameter	e4 =3'b100,
	parameter	e5_captura =3'b101,
	parameter	e6_endrow =3'b110,
	parameter	e7 =3'b111
) (
	input vsync,
	input href,
	input [7:0] data,
	input pclk,
//	input enable,

	output reg we,
	output reg [16:0] addr,
	output reg [7:0] dataHI,
	output reg [7:0] dataLO,
	output reg ready

);


reg [7:0] row=0;
reg [8:0] col=0; 

reg [2:0] state = e0;
/*reg [4:0] red;
reg [4:0] green;
reg [4:0] blue;
*/
// pclk -> we
// xclk -> pclk


// PREGUNTAR address<=std_logic_vector(to_unsigned(addr,address'length));



always @(negedge pclk) begin
	if (state==e5_captura || state==e6_endrow) 
	begin
		we=1'b1;
	end 
	else 
	begin
		we=0;
	end
end
always @(posedge pclk) begin
	case (state)
		     e0: begin	if (vsync==1) begin
					state=e1;
					ready=0;
				end
				else begin
					dataHI = dataHI;
					state=e0;
				end
                         col = 0;
                         row = 0;
			 end
		     e1: begin	if (vsync==0) begin
					state=e2;
				end
				else begin
					dataHI = dataHI;
					state=e1;
				end
                         col = col;
                         row = row;
			 end
		     e2: begin	if (href==1) begin
					state=e3;
				end
				else begin
					dataHI = dataHI;
					state=e2;
				end
                         col = col;
                         row = row;
			 end			
		     e3: begin	
			 dataHI = data;
			 state = e4;
                         col = col;
                         row = row;

			 end
		     e4: begin	dataLO = data;
				if (col==h_frame-1) begin
					col	=0;
					state	=e6_endrow;
				end else begin
					state	=e5_captura;
				end
                         col = col;
                         row = row;
			 end
		     e5_captura: begin	dataHI = data;	
				col	=col+1;
				addr	=addr+1;
				state	=e4;
				col = col;
				row = row;
			 end		
		e6_endrow: begin	if (href==0) begin
				state	= e7;
				end
			 	col = col;
				row = row;
			 end
		     e7: begin	if (row==v_frame-1) begin
					addr	=0;
					row	=0;
					state	=e0;
					ready   =1;
				end else begin
					row	=row + 1;
					addr	= addr + 1;
					state	=e2;
				end
			 end
	endcase
end
endmodule
