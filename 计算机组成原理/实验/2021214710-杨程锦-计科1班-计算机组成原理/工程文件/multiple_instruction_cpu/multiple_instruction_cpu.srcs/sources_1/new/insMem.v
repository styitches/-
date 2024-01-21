`timescale 1ns / 1ps
module insMem(
    input wire [11:0] addr,  //12λָ���ַ��
    output wire [15:0] Ins  
);
    reg[15:0] insMem[4096:0];  

    initial 
    begin
        insMem[0] = 16'b0100000000000001 ;   //�ӷ�ָ��ADD
        insMem[1] = 16'b0101000000000000;    //����ָ��STA
        insMem[2] = 16'b0110000000000000;    //ȡ��ָ��LDA
        insMem[3] = 16'b0000000000000000;    //����ۼ���ָ��CLA
        insMem[4] = 16'b0001000000000000;    //�ۼ���ȡ��ָ��COM
        insMem[5] = 16'b0010000000000000;    //��������һλָ��SHR
        insMem[6] = 16'b0011000000000000;    //ѭ������һλָ��CSL
        insMem[7] = 16'b0111000000001001;    //������ת��ָ��JMP
        insMem[9] = 16'b1000000000001001;    //������ת��BAN
        insMem[10] = 16'b100100000000000;    //ͣ��ָ��STP
    end

    assign Ins = insMem[addr];

endmodule