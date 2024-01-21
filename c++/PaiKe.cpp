#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cstring>
#include<ctime>
using namespace std;

int N, M; 
typedef struct tcnode
{
	char name[20];
	int  ipri;
}tclist,*ptclist;

typedef struct node
{
	char name[20];
	char num[20];
	int  work_time;
	tclist tc[1000];
    char cbuf[1000];
    struct node *next; 
}tlist,*ptlist;

typedef struct Node
{
	char name[20];
	char num[20];
	int week_time;
	int all_time;
	int priority;
	bool mc;		//�Ƿ�ѡ
	struct Node *next;
}clist,*pclist;
 
class teacher
{
public:
	 teacher();
    ~teacher();
	void initdata();
	void save();
	friend void print(teacher&,ptlist);
	tlist* pt;

};

class course
{
public:
	 course();
	 ~course();
	void initdata();
	void save();
	friend pclist convert(course&,char * s);
private:
	clist* pc;
};

 teacher::teacher()
{
	pt=NULL;
}
 teacher::~teacher()
{
	ptlist p;
	while(pt)
	{
       p=pt;
	   pt=pt->next;
	   delete p;
	}
	
}
void teacher::initdata()
{
	char tag;
	ptlist p=pt;
	ptlist s;
	int t=0;
	cout<<"�������ʦ��Ϣ:"<<endl;
	cout<<"����\t��ʦ��\t������"<<endl;
     do
	 {
		 if(t>=1)
		 {
			 cout<<"�������ʦ��Ϣ:"<<endl;
			 cout<<"����\t��ʦ��\t������"<<endl;
		 }
		 s = (ptlist)malloc(sizeof(tlist));
		 cin >> s->name >> s->num >> s->work_time;
		 cout << "��������Ӧ�γ���������ֵ:" << endl;
		 for(int i=0;i<M;i++)
			 cin>>s->tc[i].name>>s->tc[i].ipri;
		 fflush(stdin);
		 s->next=NULL;
		 if(!pt)
		 {
		   pt=s;
		   p=pt;
		 }
		 else
		 {
		  p->next=s;
		  p=p->next;
		 }
		 t++;
		 cout<<"�Ƿ����������Ϣ:"<<endl;
		 fflush(stdin);
		 cin>>tag; 
		 system("cls");
	 }while((tag=='y'||tag=='Y')&&t<N);

}

void teacher::save()
{
	ptlist p=pt;
	char path[20]="D:\\teacher.txt";
	char str[50]={'\0'};
	cout<<"��ѡ�񱣴��ʦ��Ϣ�ļ���·��:"<<endl;
	cin>>path;
	ofstream outfile(path);
	if(!outfile)
	{
		cerr<<"����ʧ��,������ѡ·���Ƿ���ȷ!"<<endl;
		return;
	}
	sprintf(str,"����\t��ʦ��\t������\n");
	outfile.write((char*)str,strlen(str));
	while(p)
	{
	sprintf(str,"%s\t%s\t%d\n",p->name,p->num,p->work_time);
	outfile.write((char*)str,strlen(str));
	sprintf(str,"����Ӧ�γ̵�����ֵ:\n");
	outfile.write((char*)str,strlen(str));
	for(int i=0;i<M;i++)
	{
     sprintf(str,"%s\t%d\n",p->tc[i].name,p->tc[i].ipri);
	 outfile.write((char*)str,strlen(str));
	}
	sprintf(str,"\n");
    outfile.write((char*)str,strlen(str));
	p=p->next;
	}
	outfile.close();
	cout<<"����ɹ�!"<<endl;

}


 course::course()
{
	pc=NULL;
}

 course::~course()
{
	pclist p;
	while(pc)
	{
		p=pc;
		pc=pc->next;
		delete p;
	}
}

void course::initdata()
{

	pclist p=pc;
	pclist s;
	char tag;
	int i=0;
	cout<<"������γ���Ϣ:"<<endl;
	cout<<"�γ���\t�γ̺�\t��ѧʱ\t��ѧʱ\t���ȼ�"<<endl;
	do{
		if(i>=1)
		{
			cout<<"������γ���Ϣ:"<<endl;
	        cout<<"�γ���\t�γ̺�\t��ѧʱ\t��ѧʱ\t���ȼ�"<<endl;
		}
		s=(pclist)malloc(sizeof(clist));
		cin>>s->name>>s->num>>s->week_time>>s->all_time>>s->priority;
		fflush(stdin);
		s->mc=true;
		s->next=NULL;
		i++;
		if(!pc)
		{
			pc=s;
			p=pc;
		}
	  else
	  {
		  p->next=s;
		  p=p->next;
	  }
	  cout<<"�Ƿ��������γ���Ϣ? y/Y"<<endl;
	  cin>>tag;
	  system("cls");
	}while(tag=='y'||tag=='Y');
}

void course::save()
{
	char path[20]="D:\\course.txt";
	pclist p=pc;
	char str[100]={'\0'};
	cout<<"�������ļ�����·��:"<<endl;
	cin>>path;
	ofstream outfile(path);
	if(!outfile)
	{
		cerr<<"����ʧ��,��������·���Ƿ���ȷ";
		return;
	}
	sprintf(str,"�γ���\t�γ̺�\t��ѧʱ\t��ѧʱ\t���ȼ�\n");
	outfile.write((char*)str,strlen(str));
    while(p)
	{
	    sprintf(str,"%s\t%s\t%d\t%d\t%d\n",p->name,p->num,p->week_time,p->all_time,p->priority);
		outfile.write((char*)str,strlen(str));
		p=p->next;

	}
	outfile.close();
	cout<<"����ɹ�!"<<endl;
}

void sort(teacher& t,course& c)
{
  
  ptlist q=t.pt;
  ptlist n=t.pt;
  ptlist m=n;
  int sum=0;
  int num=-1;
  srand(time(0)); 

  for(int i=0;i<M;i++)
  {
     while(m)  
	 {
		 m=n->next;
		 
		 if(m==NULL)
			 break;
		 for(int j=0;j<M;j++)
		 if((m->tc[i].ipri==n->tc[j].ipri)&&(0==strcmp(m->tc[i].name,n->tc[j].name)))
		 {
			 num=rand()%2;
			 switch(num)
			 {
			 case 0:
				 (convert(c,q->tc[num].name))->mc=false;
				 break;
			 case 1:
				 (convert(c,q->tc[num].name))->mc=false;
				 break;
			 default:
				 break;
			 }
		 }
        n=n->next;
	 }
  while(q)
  {

  for(int i=0;i<M;i++)
  {
	  if((convert(c,q->tc[i].name))->mc) 
	  {
		  sum+=(convert(c,q->tc[i].name))->all_time;
		  (convert(c,q->tc[i].name))->mc=false;
		  if(i==0)
		  strcpy(q->cbuf,q->tc[i].name);
		  else
		  {
		  strcat(q->cbuf," ");
	      strcat(q->cbuf,q->tc[i].name);
		  }
	 
	    if(sum>=q->work_time)
		  break;
	  }
  }
  sum=0;
  q=q->next;
  }
  }
cout<<"�γ����ź�!"<<endl;

}
//test
void print(teacher& t)
{
	ptlist p=t.pt;
	cout<<"�����ſ����:"<<endl;
	cout<<"��ʦ����\t������\t���ڿγ�"<<endl;
	while(p)
	{
	  cout<<p->name<<"\t\t"<<p->work_time<<"\t"<<p->cbuf<<endl;
	  p=p->next;
	}
}

pclist convert(course& c,char * s)
{
	pclist p=c.pc;
	while(p)
	{
		if(0==strcmp(p->name,s))
			return p;
		else
			p=p->next;
	}
	cout<<"Ӧ�ó������!"<<endl;
	return NULL;
}

teacher tea;
course  cou;

void menu()
{
    bool ttag=false;
	bool ctag=false;
	char tag;
	int choice=0;
	do{
		system("cls");
		cout<<">>>>>>>��ӭʹ�ý�ʦ�ſ�ϵͳ,�������ʾ�����ز���<<<<<<<<<<<<<<<<<<<<"<<endl;
		cout<<">>>>>>>1:�����ʦ��Ϣ"<<endl;
		cout<<">>>>>>>2:����γ���Ϣ"<<endl;
		cout<<">>>>>>>3:�洢��ʦ��Ϣ"<<endl;
		cout<<">>>>>>>4:�洢�γ���Ϣ"<<endl;
		cout<<">>>>>>>5:��ʦ�ſ�"<<endl;
		cout<<">>>>>>>6:��ӡ�ſν��"<<endl;
		cout<<">>>>>>>0:�˳�"<<endl;
		fflush(stdin);
		cout<<"������ѡ��:"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 1:
			system("cls");
			cout<<"***********��ʦ��Ϣ����******************"<<endl;
            tea.initdata();
			ttag=true;
			break;
		case 2:
			system("cls");
			cout<<"***********�γ���Ϣ����******************"<<endl;
			cou.initdata();
			ctag=true;
			break;
		case 3:
			system("cls");
			cout<<"***********��ʦ��Ϣ����******************"<<endl;
			if(!ttag)
				cout<<"���������ʦ��Ϣ"<<endl;
			else
				tea.save();
			break;
        case 4:
			system("cls");
			cout<<"***********�γ���Ϣ����******************"<<endl;
			if(!ctag)
			  cout<<"��������γ���Ϣ"<<endl;
			else
				cou.save();
			break;
		case 5:
			system("cls");
			cout<<"***********��ʦ�������*****************"<<endl;
			if(!ttag||!ctag)
				cout<<"�������������Ϣ"<<endl;
			else
				sort(tea,cou);
			break;
		case 6:
			system("cls");
			cout<<"***********�ſ���Ϣ��ӡ******************"<<endl;
			if(!ttag||!ctag)
				cout<<"�������������Ϣ"<<endl;
			else
				print(tea);
			break;
		default:
			system("cls");
			cout<<"\t****************THANKS FOR YOUR USE***********"<<endl;
			cout<<"\t*****************��лʹ�ñ�ϵͳ!*************"<<endl;
			exit(0);
		}
		cout<<"ϵͳʹ����........."<<endl;
		cout<<"�Ƿ������������? y/Y"<<endl;
		cin>>tag;
	}while(tag=='y'||tag=='Y');

}

int main()
{
	cout << "�������ʦ����: ";
	cin >> N;
	cout << "������γ���: ";
	cin >> M; 
	menu();
	return 0;
}
