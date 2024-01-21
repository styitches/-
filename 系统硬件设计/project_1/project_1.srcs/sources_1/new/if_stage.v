
module if_stage(
	input clk,
	input rst_n,
	input [31:0]pc_if_i,
	output [31:0]pc_if_o,
	output [7:0]rom_addr,
    input load_use_flag
    );

	pc_reg pc_reg_inst (
    .clk(clk), 
    .rst_n(rst_n), 
    .pc_new(pc_if_i), 
    .pc_out(pc_if_o),
    .load_use_flag(load_use_flag)  //����exstage���ж��Ƿ���Ҫ����ͣ��һ���������ȴ�����loadָ�������ǰ��
    );
	
	assign rom_addr=pc_if_o[9:2];

endmodule
