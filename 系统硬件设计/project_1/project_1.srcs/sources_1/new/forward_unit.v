
//���Ͼ����������ٵ�����ð�յķ��������ܽ����£�
//a.��һ�����ڿ�ʼ��EX �׶�Ҫʹ����һ������ EX �׶�ָ���ִ�н������ʱ���ǽ� EX/MEM �Ĵ���������ǰ�ݡ�
//b.��һ�����ڿ�ʼ��EX �׶�Ҫʹ����һ������ MEM �׶�ָ���ִ�н������ʱ���ǽ� MEM/WB �Ĵ���������ǰ�ݡ�
//c.��һ�����ڿ�ʼ��EX �׶�Ҫʹ����һ������ WB �׶�ָ���ִ�н������ʱ����Ҫǰ�ݣ��Ĵ�����ǰ�ݻ��ƣ�
//d.�ڵ�һ������£��������һ���Ƿô�ָ�����������-ʹ����ð�ա�����Ҫͣ��һ�����ڡ�
//e.�ڷ�������--ʹ����ð�յ�ʱ�������load�����storeָ�����loadָ���rd��storeָ���rs1 ��ͬ����rs2��ͬ������Ҫͣ�٣�ֻ��Ҫ��MEM/WB �Ĵ���������ǰ�ݵ�MEM�׶Ρ�

module forward_unit(
	input [4:0]Rs1_id_ex_o,
	input [4:0]Rs2_id_ex_o,
	input [4:0]Rd_ex_mem_o,
	input [4:0]Rd_mem_wb_o,
	input RegWrite_ex_mem_o,
	input RegWrite_mem_wb_o,
	input MemWrite_id_ex_o,
	input MemRead_ex_mem_o,
	
	output  [1:0]forwardA,
	output  [1:0]forwardB,
	output forwardC,
	
	
	input [4:0]Rs1_id_ex_i,
	input [4:0]Rs2_id_ex_i,
	input [4:0]Rd_id_ex_o,
	input MemRead_id_ex_o,
	input MemWrite_id_ex_i,
	input RegWrite_id_ex_o,
	
	output load_use_flag
	
    );
	
	assign forwardA[1]=(RegWrite_ex_mem_o &&(Rd_ex_mem_o!=5'd0)&&(Rd_ex_mem_o==Rs1_id_ex_o));
	assign forwardA[0]=(RegWrite_mem_wb_o && (Rd_mem_wb_o !=5'd0) &&(Rd_mem_wb_o==Rs1_id_ex_o));
	
	assign forwardB[1]=(RegWrite_ex_mem_o &&(Rd_ex_mem_o!=5'd0)&&(Rd_ex_mem_o==Rs2_id_ex_o));
	assign forwardB[0]=(RegWrite_mem_wb_o && (Rd_mem_wb_o !=5'd0) &&(Rd_mem_wb_o==Rs2_id_ex_o));
	
	
	//load�����sw���ǲ���Ҫͣ��
	assign forwardC=(RegWrite_ex_mem_o &&(Rd_ex_mem_o!=5'd0)&&(Rd_ex_mem_o!=Rs1_id_ex_o)&& (Rd_ex_mem_o==Rs2_id_ex_o)&& MemWrite_id_ex_o && MemRead_ex_mem_o );
	
	
	//load-use
	assign load_use_flag= 	MemRead_id_ex_o & RegWrite_id_ex_o & (Rd_id_ex_o!=5'd0)   //load
							&(!MemWrite_id_ex_i)     //��store
							& ((Rd_id_ex_o ==Rs1_id_ex_i) | (Rd_id_ex_o ==Rs2_id_ex_i))
							|
							MemRead_id_ex_o & RegWrite_id_ex_o & (Rd_id_ex_o!=5'd0)     //load
							&(MemWrite_id_ex_i)     //store
							& (Rd_id_ex_o ==Rs1_id_ex_i);
							

endmodule




