
`include "define.vh"

module if_id_regs(
	input clk,
	input rst_n,
	input jump_flag,  //����exstage �жϾ������ĸ���תָ��
	input [31:0]pc_if_id_i,
	input [31:0]instr_if_id_i,
	output reg [31:0]pc_if_id_o,
	output reg [31:0]instr_if_id_o,
	input load_use_flag
    );

	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			pc_if_id_o<=`zeroword;
		else
			pc_if_id_o<=pc_if_id_i;
	end
	
	always@(posedge clk or negedge rst_n)
	begin
		if(!rst_n)
			instr_if_id_o<=`zeroword;
		else if(jump_flag)
			instr_if_id_o<=`zeroword;  //���� ��Ϊ����ָ���Ѿ�����
		else if(load_use_flag)
			instr_if_id_o<=instr_if_id_o;
		else
			instr_if_id_o<=instr_if_id_i;
	end

endmodule






