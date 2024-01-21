`timescale 1ns / 1ps
module dataMem(
    input wire dataMem_wr, clk, //dataMemʹ�ܡ�ʱ��
    input wire [11:0] addr, //12λָ���ַ
    input wire [15:0] data_in,  //16λ��������
    output wire [15:0] data_out //16λ�������
);
    reg [15:0] dataMem[4096:0]; //2^12���洢��Ԫ,ÿ���洢��Ԫ16λ

    assign data_out = dataMem[addr];

    initial 
    begin
      dataMem[0] = 16'b0010000000100001;    //��ʼ��1
      dataMem[1] = 16'b0100011100010000;    //��ʼ��2
    end

    always @(negedge clk) 
    begin
      if(dataMem_wr == 1)
        dataMem[addr] = data_in;
    end

endmodule