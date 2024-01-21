`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/06/15 01:55:45
// Design Name: 
// Module Name: cu
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module cu(
    input wire [6:0] opcode,
    input wire clk,
    output reg we,
    output reg re1,
    output reg re2,
    output reg [2:0] alu_op
    );
    
    always @(posedge clk)
    begin
        alu_op <= 3'b000;  //һ���ӷ�ָ��
        we <= 1'b0; //�͵�ƽд
        re1 <= 1'b0; //�͵�ƽ��
        re2 <= 1'b0; //�͵�ƽ��
    end
endmodule
