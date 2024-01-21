#include<iostream>
using namespace std;
#define max 100


//��λ����
int locates(char *g, char ch,int number)
{
    int i;
    for(i = 0; i <number; i++)
    {
        if(g[i] == ch)
        {
            break;
        }
    }
    if(i >= number)
    {
        return-1;
    }

    return i;
}

//���뺯��
void inputc(char *c,int number){
    for(int i=0;i<number;i++){
        cin>>c[i];
    }
}


//�������
void inputl(int ling[max][max],int number){

    for(int i=0;i<number;i++){
        for(int j=0;j<number;j++){
            cout<<ling[i][j]<<"\t";
        }
        cout<<endl;
    }
}


//�ж��Ƿ�Ϊ�ȼ۹�ϵ
bool judge(int ling[max][max],int number){
    bool zifan,duichen=true,chuandi=true;;
//�ж��Է���
    int total=0;
    for(int i=0;i<number;i++){
        if(ling[i][i]==1){
            total++;
        }
    }
    zifan=(number==total);

//�ж϶Գ���
    for(int m=0;m<number;m++){
        for(int n=0;n<number;n++){
            if(ling[m][n]==1 && ling[n][m]!=1){
                duichen=false;
            }
        }
    }

//�жϴ�����
    for(int p=0;p<number;p++){
        for(int q=0;q<number;q++){
            for(int s=0;s<number;s++){
                if(ling[p][q]==1 && ling[q][s]==1&& ling[p][s]!=1){
                    chuandi=false;
                }
            }
        }
    }

    return(zifan&duichen)&chuandi;


}

//���̼�

void shangji(int ling[max][max],int number,char c[max]){
    bool visited[max];
    for(int p=0;p<number;p++){
        visited[p]=false;
    }

    for(int i=0;i<number;i++){
        if(visited[i]==false){
            visited[i]=true;
            cout<<"{";
            cout<<c[i]<<",";
            for(int j=0;j<number;j++){
                if(ling[i][j]==1&& visited[j]==false){
                    visited[j]=true;
                    cout<<c[j]<<",";
                }
            }
            cout<<"\b"<<"}";
            cout<<"  ";
        }
    }

}

int main(){
    char c[max],a,b;
    int ling[max][max];
    int number,edge;
    cout<<"������Ԫ�ظ����Լ���ϵ����:";
    cin>>number>>edge;
    cout<<"������Ԫ��:";
    inputc(c,number);

    for(int i=0;i<number;i++){
        for(int j=0;j<number;j++){
            ling[i][j]=0;
        }
    }

    //�����Ԫ��ϵ
    cout<<"�������Ԫ��ϵ: "<<endl;
    for(int p=0;p<edge;p++){
        cin>>a>>b;
        ling[locates(c,a,number)][locates(c,b,number)]=1;
    }

//�����Ԫ��ϵ
    inputl(ling,number);
    if(judge(ling,number)){
        cout<<"��������ȼ۹�ϵ"<<endl;
        shangji(ling,number,c);
    }
    else cout<<"��������ȼ۹�ϵ"<<endl;

    return 0;
}
