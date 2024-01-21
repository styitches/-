`include "define.vh"
module data_memory(
	clk,
	rst_n,
	W_en,
	R_en,
	addr,
	RW_type,
	din,
	dout
    );
	
	
	input clk;
	input rst_n;
	
	input W_en;
	input R_en;
	
	input [31:0]addr;
	input [2:0]RW_type;

	input [31:0]din;
	output [31:0]dout;


	reg [31:0]ram[255:0];
	
    initial begin
        ram[0]=32'd0;
    end
	
	wire [31:0]Rd_data;
	
	reg [31:0]Wr_data_B;//�ֽ�ƴ��
	wire [31:0]Wr_data_H;//����ƴ��
	
	wire [31:0]Wr_data;
	
	
	assign Rd_data=ram[addr[31:2]];//����׼

    //��din����ƫ�ƶ��ٸ��ֽ�֮����д���datamemory
    always@(*)
	begin
		case(addr[1:0])
			2'b00:Wr_data_B={Rd_data[31:8],din[7:0]};
			2'b01:Wr_data_B={Rd_data[31:16],din[7:0],Rd_data[7:0]};
			2'b10:Wr_data_B={Rd_data[31:24],din[7:0],Rd_data[15:0]};
			2'b11:Wr_data_B={din[7:0],Rd_data[23:0]};
		endcase
	end

assign Wr_data_H=(addr[1]) ? {din[15:0],Rd_data[15:0]} : {Rd_data[31:16],din[15:0]} ;
	
///////////////////////////////////////////////////////////////////////////////����д���ͣ�ѡ��д�������
//�����00 д���ֽ�ƴ�� 01д�����ƴ�� 10/11д��din
assign Wr_data=(RW_type[1:0]==2'b00) ? Wr_data_B :( (RW_type[1:0]==2'b01) ? Wr_data_H : din   );

///////////////////////////////////////////������д������

always@(posedge clk)
begin
	if(W_en)
		ram[addr[9:2]]<=Wr_data;
end

 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////������


reg [7:0]Rd_data_B;
wire [15:0]Rd_data_H;

wire [31:0] Rd_data_B_ext;  //�ֽ�ƴ��
wire [31:0] Rd_data_H_ext;  //����ƴ��

////////////////////////////////////////////����д��ַ��ʵ��д����
always@(*)
begin
	case(addr[1:0])
		2'b00:Rd_data_B=Rd_data[7:0];
		2'b01:Rd_data_B=Rd_data[15:8];
		2'b10:Rd_data_B=Rd_data[23:16];
		2'b11:Rd_data_B=Rd_data[31:24];
	endcase
end
		
assign Rd_data_H=(addr[1])? Rd_data[31:16]:Rd_data[15:0];

///////////////////////////////////////////////////////////////////////////////////////��չΪ32λ
assign Rd_data_B_ext=(RW_type[2]) ? {24'd0,Rd_data_B} : {{24{Rd_data_B[7]}},Rd_data_B};

assign Rd_data_H_ext=(RW_type[2]) ? {16'd0,Rd_data_H} : {{16{Rd_data_H[15]}},Rd_data_H};


/////////////////////////////////////////////
assign dout=(RW_type[1:0]==2'b00) ? Rd_data_B_ext : ((RW_type[1:0]==2'b01) ? Rd_data_H_ext : Rd_data );


endmodule