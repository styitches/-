`timescale 1ns / 1ps
module cu(
    input wire [3:0] operate,    //4λָ�������
    output reg stop, uct, acc_wr, dataMem_wr, //ͣ���źš�������ת��uct��acc��д���ơ����ݴ洢����д����
    output reg [3:0] alu_op //alu����ѡ��
);
    initial 
    begin
      stop = 0;
      uct = 0;
      acc_wr = 0;
      dataMem_wr = 0;
      alu_op = 4'b1111;
    end

    always @(operate) 
    begin
      case(operate)
        4'b0000: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00100000;   //����ۼ���ָ��CLA
        4'b0001: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00100001;   //�ۼ���ȡ��ָ��COM    
        4'b0010: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00100010;   //��������һλָ��SHR
        4'b0011: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00100011;   //ѭ������һλָ��CSL
        4'b0100: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00100100;   //�ӷ�ָ��ADD
        4'b0101: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00010101;   //����ָ��STA
        4'b0110: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00100110;   //ȡ��ָ��LDA
        4'b0111: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b01000111;   //������ת��ָ��JMP
        4'b1000: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b00001000;   //������ת��BAN
        4'b1001: {stop,uct,acc_wr,dataMem_wr,alu_op} = 8'b10000000;   //ͣ��STOP
        endcase
    end

endmodule