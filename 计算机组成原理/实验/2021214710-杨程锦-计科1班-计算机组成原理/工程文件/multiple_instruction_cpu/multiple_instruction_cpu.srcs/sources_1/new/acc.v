`timescale 1ns / 1ps
module acc(
    input wire clk, acc_wr, //ʱ�ӡ�acc��д����
    input wire [15:0] data_in,  //16λ��������
    output wire [15:0] data_out //16λ�������
);
    reg [15:0] acc; //16λacc

    initial 
    begin
        acc = 1;  //acc��ʼ��1
    end

    assign data_out = acc; 

    always@(negedge clk) 
    begin
      if(acc_wr == 1)
        acc = data_in;
    end

endmodule