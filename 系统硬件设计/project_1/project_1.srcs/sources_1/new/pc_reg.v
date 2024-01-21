
`include "define.vh"
module pc_reg(
	clk,
	rst_n,
	pc_new,
	pc_out,
	load_use_flag
    );
	input clk;
	input rst_n;
	input [31:0]pc_new;
	input load_use_flag;
	
	output reg [31:0]pc_out;
	
	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			pc_out<=`zeroword;
		else if(load_use_flag)  //����д���г�ͻ��ǰһ����Ȼ�ڷô棬��һ����ִ�У���Ҫ��ǰһ���õ�����Ȼ��ǰ�ƣ�����pc����
			pc_out<=pc_out;
		else
			pc_out<=pc_new;
	end	

endmodule


