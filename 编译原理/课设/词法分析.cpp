#include "data.h"
/*
��1  ��ʶ����1-id
��2  ������2
��3  С����3
��4  �����֣�41-program 42-if 43-else 44-while 45-integer 46-float 47-input 48-output
��5  ���������  51-�� 52-�� 53-*  54-/  55-=  56-<  57->
��6  ˫�������  61-<=  62->=  63-<>  64-==
��7  �����������71-and  72-or
��8  �����81-{  82-}  83-(  84-)  85-,  86-;
*/
int isAlpha(char ch)
{
	return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
}
int isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}
//4������ program  if  else  while  integer  float   input   output
int isKey(char* Key)
{
	bool flag = 1;
	flag = strcmp(Key, "program");
	if (flag == 0) return 1;
	flag = strcmp(Key, "if");
	if (flag == 0) return 2;
	flag = strcmp(Key, "else");
	if (flag == 0) return 3;
	flag = strcmp(Key, "while");
	if (flag == 0) return 4;
	flag = strcmp(Key, "integer");
	if (flag == 0) return 5;
	flag = strcmp(Key, "float");
	if (flag == 0) return 6;
	flag = strcmp(Key, "input");
	if (flag == 0) return 7;
	flag = strcmp(Key, "output");
	if (flag == 0) return 8;
	else return 0;
}
//��������� and  or
int isBool(char* Key)
{
	int flag = 1;
	flag = strcmp(Key, "and");
	if (flag == 0) return 1;
	flag = strcmp(Key, "or");
	if (flag == 0) return 2;
	else return 0;
}

Token getNextToken()
{
	int flag = 0;
	char id[10]; //�����q�з������ı���������(�ַ�����ʽ)
	//char temp;//*p=*q; //ֱ�Ӳ�������ָ���鷳��������p������*q
	Token t; //t����������ĵ�����Ϣ
	//temp=fgetc(fp);
	while (temp == ' ' || temp == '\t' || temp == '\n')
	{
		if (temp == '\n') row++;
		temp = fgetc(fp);// ����ǰ���ո�
	}
	if ((isAlpha(temp)) || temp == '_')//��ǰ�ַ�����ĸ������ʶ������ʶ��
	{
		int i = 0;
		id[i++] = temp;
		temp = fgetc(fp);
		while (isAlpha(temp) || isDigit(temp))
		{
			id[i++] = temp;
			temp = fgetc(fp);
		}
		id[i] = '\0';
		flag = isKey(id);
		if (flag) //�ؼ��� 41-program 42-if 43-else 44-while 45-integer 46-float 47-input 48-output
		{
			t.type = 4 * 10 + flag;
			strcpy(t.key, id);
		}
		else if (isBool(id)) //��������� 71-and  72-or
		{
			flag = isBool(id);
			t.type = 7 * 10 + flag;
			strcpy(t.key, id);
		}
		else
		{
			t.type = 1; //��ʶ�� 1
			strcpy(t.varname, id);
			//Check(t);
		}
	}
	else if (isDigit(temp)) // ��ǰ�ַ������֣�������С������ʶ��
	{
		int i = 0;
		while (isDigit(temp))
		{
			id[i++] = temp;
			temp = fgetc(fp);
		}
		if (temp == '.')
		{
			id[i++] = '.';
			temp = fgetc(fp);
			while (isDigit(temp))
			{
				id[i++] = temp;
				temp = fgetc(fp);
			}
			t.type = 3; // С�� 3
			id[i] = '\0';
			t.decimal = atof(id);
		}
		else
		{
			t.type = 2; // ���� 2
			id[i] = '\0';
			t.integer = atoi(id);
		}
		strcpy(t.varname, id);
	}
	/*
	��5  ���������  51-�� 52-�� 53-*  54-/  55-=  56-<  57->
	��6  ˫�������  61-<=  62->=  63-<>  64-==
	��7  �����������and  or
	��8  �����      {   }  (  )  ��  ��
	*/
	else if (temp == '+') { strcpy(t.varname, "+"); t.type = 51; temp = fgetc(fp); }
	else if (temp == '-') { strcpy(t.varname, "-"); t.type = 52; temp = fgetc(fp); }
	else if (temp == '*') { strcpy(t.varname, "*"); t.type = 53; temp = fgetc(fp); }
	else if (temp == '/') { strcpy(t.varname, "/"); t.type = 54; temp = fgetc(fp); }
	else if (temp == '=') {
		temp = fgetc(fp);
		if (temp == '=')
		{
			strcpy(t.varname, "=="); t.type = 64; temp = fgetc(fp);
		}
		else
		{
			strcpy(t.varname, "="); t.type = 55;
		}
	}
	else if (temp == '<') {
		temp = fgetc(fp);
		if (temp == '=')
		{
			strcpy(t.varname, "<="); t.type = 61; temp = fgetc(fp);
		}
		else if (temp == '>')
		{
			strcpy(t.varname, "<>"); t.type = 63; temp = fgetc(fp);
		}
		else
		{
			strcpy(t.varname, "<"); t.type = 56;
		}
	}
	else if (temp == '>') {
		temp = fgetc(fp);
		if (temp == '=')
		{
			strcpy(t.varname, ">="); t.type = 62; temp = fgetc(fp);
		}
		else
		{
			strcpy(t.varname, ">"); t.type = 57;
		}
	}
	else if (temp == '{') { strcpy(t.varname, "{"); t.type = 81; temp = fgetc(fp); }
	else if (temp == '}') { strcpy(t.varname, "}"); t.type = 82; temp = fgetc(fp); }
	else if (temp == '(') { strcpy(t.varname, "("); t.type = 83; temp = fgetc(fp); }
	else if (temp == ')') { strcpy(t.varname, ")"); t.type = 84; temp = fgetc(fp); }
	else if (temp == ',') { strcpy(t.varname, ","); t.type = 85; temp = fgetc(fp); }
	else if (temp == ';') { strcpy(t.varname, ";"); t.type = 86; temp = fgetc(fp); }
	else if (temp == EOF) { strcpy(t.varname, "#"); t.type = 0; }     //t.type=0��ʾ���봮�������
	else { strcpy(t.varname, "#");  t.type = -1; temp = fgetc(fp); }      //t.type=-1��ʾ��ǰ�ַ��������; p++�����ô����ַ�

	//*q=p;//�޸�����ָ��,ʹ��ָ���������
	//cout<<t.type<<endl;
	//cp_Sym->Next=(Symbol*)malloc(sizeof(Symbol));
	//cp_Sym=cp_Sym->Next;

	return t;
}
