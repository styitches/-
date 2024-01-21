`timescale 1ns / 1ps
module pc(
    input wire clk, rst, stop, ct, uct, //ʱ�ӡ����á�ͣ��������ת�ơ�������ת��
    input wire [11:0] offset,  //12λת��ָ��ƫ����
    output reg [11:0] pc  //12λָ���ַ��  
);

    assign stop = 0;  //��ʼ������״̬
    // assign clk = (stop==1)?1'bz:0; //ͣ����clk��0

    always@(posedge clk) begin
      if(rst == 1)
        pc = 0;
      else
        pc = pc + 1;
    end

    always@(negedge clk) begin
      if(uct == 1)  //������ת��
        pc = offset-1;
      if(ct == 1)  //����ת��
        pc = pc+offset-1;
    end

endmodule