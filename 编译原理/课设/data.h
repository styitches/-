#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
/*
��1  ��ʶ�������ַ�Ϊ��ĸ��'_'���������ĸ�����ֻ�'_'��ɡ����Ȳ�����8���ַ���
��2  ������
��3  С����
��4  �����֣�program  if  else  while  integer  float   input   output
��5  ���������  �� �� *  /  =  <  >
��6  ˫�������  <=  >=  <>  ==
��7  �����������and  or
��8  �����      {   }  (  )  ��  ��
*/

typedef struct SNode
{
	char data[10];
	SNode* Next;
}SNode, * StackPtr;

typedef struct
{
	StackPtr top;
	StackPtr base;
}LinkStack;

struct Token
{
	int type;//��������:  1:����  2:����  3:(   4:)  5:+  6: -  7:*  8: /  -1:����   0: ������� 
	int integer;//�������������,integer���������ֵ֮
	float decimal;//���������С��,decimal���������ֵ֮
	char varname[10];//��������Ǳ���,var���������
	char key[10];//��������ǹؼ���,key���������
};

struct Symbol // ���ű�
{
	bool type; //0-С����1-����
	char varname[10];
	int integer;
	float decimal;
	Symbol* Next;
};

struct Four //��Ԫʽ
{
	int num;
	char op1[10];
	char op2[10];
	char op3[10];
	char op4[10];
	Four* Next;
};

struct Link
{
	Four* x;
	int grade;
	Link* Next;
};

extern int sysnum; //��ǰ��Ԫʽ����
extern int wrong;  //���� 1-���� 0-δ����
extern char temp;  //
extern Token Next; //
extern FILE* fp;  //���ļ�ָ��
extern FILE* fw;  //д�ļ�ָ��
extern int row;    //��ǰɨ������

extern Symbol* Sym;     //�����б���ָ��
extern Symbol* cp_Sym;  //�����б�ָ̬��

extern int var_count;    //��Ԫʽ����ʱ������ǰ����
extern char* op1;
extern char* op2;
extern char* op3;
extern char* op4;
extern Four FourList;     //��Ԫʽ�б���ָ��   
extern Four* cp_FourList;//��Ԫʽ�б�ָ̬��
extern Link* Ture;       //�����
extern Link* False;      //�ٳ���
extern Link* cp_Ture;       //�����
extern Link* cp_False;      //�ٳ���
extern int grade;

extern LinkStack Sign;    //����ջ
extern LinkStack Var;     //����ջ

void initial();           //��ʼ��

Token getNextToken();     //�ʷ�����

//����Ϊ�﷨��������:

void program();
void Statementblock();
void Statement();
void Vardefstatement();
bool Datatype();
void Inputstatement();

void Outputstatement();
void Assignstatement();
void Branchstatement();
void Loopstatement();
void expression();

void item();
void factor();
void Boolexpression();
void Relatexpression();
void relation();

//����Ϊջ������

int InitStack(LinkStack* S);
int Push(LinkStack* S, char e[]);
int Pop(LinkStack* S, char* e[]);
int IsEmpty(LinkStack* S);

//����Ϊ������Ԫʽ�ͷ��ű����

bool Check(char* varname, bool type);
bool AddSymbol(char* varname, bool type);
void PrintSignForm();
void MakeFour(char* op1, char* op2, char* op3, char* op4);
void PrintFour();
void Back(Link* TF);
