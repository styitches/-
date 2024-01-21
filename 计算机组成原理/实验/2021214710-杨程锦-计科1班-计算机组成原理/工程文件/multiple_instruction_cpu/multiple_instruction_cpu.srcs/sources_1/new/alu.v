`timescale 1ns / 1ps
module alu(
    input wire [15:0] in1, in2,   //������in1��in2
    input wire [3:0] alu_op,  //����ѡ���ź�alu_op
    output reg ct, //����ת��ct
    output reg [15:0] Z   //Z
);
    initial 
    begin
      ct = 0;
      Z = 0;  //��ʼ�����ZΪ0
    end
    
    always @(*) 
    begin
      case (alu_op)
          4'b0000: Z = 0;   //����ۼ���ָ��CLA
          4'b0001: Z = ~in1;    //�ۼ���ȡ��ָ��COM    
          4'b0010: Z = in1[15] == 1 ? {1'b1, in1[15:1]} : {1'b0, in1[15:1]};    //��������һλָ��SHR
          4'b0011: Z = {in1[14:0], in1[15]};    //ѭ������һλָ��CSL
          4'b0100: Z = in1 + in2;   //�ӷ�ָ��ADD
          4'b0101: Z = in1;    //����ָ��STA
          4'b0110: Z = in2;   //ȡ��ָ��LDA
          4'b1000: ct = in1[15]==1?1:0;   //������ת��BAN
          4'b1001: ;    //ͣ��ָ��
      endcase
    end

endmodule