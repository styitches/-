
#include "data.h"


int sysnum; //��ǰ��Ԫʽ����
int wrong;  //���� 1-���� 0-δ����
char temp;  //
Token Next; //
FILE* fp;  //���ļ�ָ��
FILE* fw;  //д�ļ�ָ��
int row;    //��ǰɨ������

Symbol* Sym;     //�����б���ָ��
Symbol* cp_Sym;  //�����б�ָ̬��

int var_count;    //��Ԫʽ����ʱ������ǰ����
char* op1;
char* op2;
char* op3;
char* op4;
Four FourList;     //��Ԫʽ�б���ָ��   
Four* cp_FourList;//��Ԫʽ�б�ָ̬��
Link* Ture;       //�����
Link* False;      //�ٳ���
Link* cp_Ture;       //�����
Link* cp_False;      //�ٳ���
int grade;
LinkStack Sign;    //����ջ
LinkStack Var;     //����ջ

void initial()     //��ʼ��
{
	op1 = (char*)malloc(10);
	op2 = (char*)malloc(10);
	op3 = (char*)malloc(10);
	op4 = (char*)malloc(10);


	sysnum = 0;
	var_count = 0;
	row = 1;

	Sym = (Symbol*)malloc(sizeof(Symbol));
	cp_Sym = Sym;
	Sym->Next = NULL;

	cp_FourList = &FourList;
	cp_FourList->Next = NULL;

	Ture = (Link*)malloc(sizeof(Link));       //�����
	Ture->Next = NULL;
	False = (Link*)malloc(sizeof(Link));      //�ٳ���
	False->Next = NULL;
	cp_Ture = Ture;
	cp_False = False;
	grade = 0;

	InitStack(&Sign);
	InitStack(&Var);

}

void main()
{
	initial();
	cout << "Compiling..." << endl;
	fp = fopen("pro.txt", "r");
	if (fp == NULL)
	{
		printf("�ļ�����");
		exit(0);
	}
	temp = fgetc(fp);
	Next = getNextToken();
	program();
	if (wrong == 0 && temp == EOF)
	{
		cout << "Compiled!" << endl;
	}
	//PrintSignForm();
	fw = fopen("por.txt", "w");
	PrintFour();
}
