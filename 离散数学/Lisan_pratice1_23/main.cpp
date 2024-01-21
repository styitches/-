#include<iostream>
#include<string>

using namespace std;

class SeqStack {
public:
    SeqStack(int mSize);
    ~SeqStack();
    bool Push(char x);
    bool Pop();
    char Top();
    bool Empty();
private:
    int top;
    char *stack;
    int maxtop;
};
SeqStack::SeqStack(int mSize) {
    maxtop = mSize - 1;
    stack = new char[mSize];
    top = -1;
}
SeqStack::~SeqStack() {
    delete[]stack;
}
bool SeqStack::Push(char x) {
    if (top == maxtop)
        return false;
    stack[++top] = x;
    return true;
}
bool SeqStack::Pop() {
    if (-1==top )return false;
    top--;
    return true;
}
bool SeqStack::Empty() {
    if (-1==top)return true;
    return false;
}
char SeqStack::Top() {
    return stack[top];
}
bool IsLegal(const string orgin) {
    for (unsigned int i = 0; i < orgin.length(); i++) {
        if (orgin[i] != '(' && orgin[i] != ')' && orgin[i] != 'P' && orgin[i] != 'Q' && orgin[i] != 'R' && orgin[i] != '&' && orgin[i] != '|' && orgin[i] != '=' && orgin[i] != '>'&&orgin[i]!='!')return false;
    }
    return true;
}


int And(int a,int b, SeqStack &stack) {
    int res = a * b;
    stack.Push(res);
    return res;
}

int Or (int a, int b, SeqStack &stack) {
    int res = a + b;
    res = res > 0 ? 1 : res;
    stack.Push(res);
    return res;
}
int Not(int a, SeqStack &stack) {
    a = stack.Top();
    stack.Pop();
    int res = a == 1 ? 0 : 1;
    stack.Push(res);
    return res;
}

int If(int a, int b, SeqStack &stack) { //����
    int res = (b == 1 && a == 0) ? 0 : 1;
    stack.Push(res);
    return res;
}

int Iif(int a, int b, SeqStack &stack) {//˫����
    int res = (b == a) ? 1 : 0;
    stack.Push(res);
    return res;
}

bool CanIn(char out,SeqStack &stack) {        //�ȼ������ȼ���Ȼ���ж��ܷ��ջ
    char in = stack.Top();
    int i=0, o=0;  //�ֱ��ʾջ��������������ȼ�
    switch (in) {
        case '#':i = 0; break;
        case '(':i = 1; break;
        case '=':i = 3; break;
        case '>':i = 5; break;
        case '|':i = 7; break;
        case '&':i = 9; break;
        case '!':i = 11; break;
        case ')':i = 12; break;
    }

    switch (out) {
        case '#':o = 0; break;
        case '(':o = 12; break;
        case '=':o = 2; break;
        case '>':o = 4; break;
        case '|':o = 6; break;
        case '&':o = 8; break;
        case '!':o = 10; break;
        case ')':o = 1; break;
    }
    if (i < o)      //ջ�����ȼ���ջ�ڸ߾ͽ�ջ
        return true;
    else
        return false;
}

void InfixToPostfix(string &orgin ,SeqStack &stack) {  //ת��Ϊ��׺���ʽ
    string tmp;                //�����׺���ʽ
    stack.Push('#');
    for (int i = 0; (unsigned)i <orgin.length(); i++) {
        if (orgin[i] == 'P' || orgin[i] == 'Q' || orgin[i] == 'R' ) {
            tmp = tmp + orgin[i];
            continue;
        }
        if (CanIn(orgin[i],stack))
            stack.Push(orgin[i]);
        else if (orgin[i] == ')'){
            while (stack.Top() != '('){
                tmp = tmp + stack.Top();
                stack.Pop();
            }
            stack.Pop();
        }
        else{
            do{
                tmp = tmp + stack.Top();
                stack.Pop();
            } while (!CanIn(orgin[i],stack));
            stack.Push(orgin[i]);
        }
    }
    while (stack.Top() != '#'){
        tmp = tmp + stack.Top();
        stack.Pop();
    }
    stack.Pop();                // '#' ��ջ
    orgin = tmp;
}


int Calculate(int number,string &org,SeqStack &stack, int p, int q, int r){
    int value=0,a=0,b=0,res=0;
    if (number == 3){
        for (int i = 0; (unsigned)i <org.length(); i++){
            if (org[i] == 'P' || org[i] == 'Q' || org[i] == 'R'){
                value = org[i] == 'P' ? p : org[i] == 'Q' ? q : r;
                stack.Push(value);
                continue;
            }
            if (org[i] != '!'){
                a = stack.Top();
                stack.Pop();
                b = stack.Top();
                stack.Pop();
            }
            switch (org[i]){
                case '=':res=Iif(a,b,stack); break;
                case '>':res=If(a, b, stack); break;
                case '|':res=Or(a, b, stack); break;
                case '&':res=And(a, b, stack); break;
                case '!':res=Not(a, stack); break;
            }
        }
    }
    if (number == 2){
        for (int i = 0;(unsigned)i <org.length(); i++){
            if (org[i] == 'P' || org[i] == 'Q'){
                value = org[i] == 'P' ? p : q;
                stack.Push(value);
                continue;
            }
            if (org[i] != '!'){
                a = stack.Top();
                stack.Pop();
                b = stack.Top();
                stack.Pop();
            }
            switch (org[i]) {
                case '=':res = Iif(a, b, stack); break;
                case '>':res = If(a, b, stack); break;
                case '|':res = Or(a, b, stack); break;
                case '&':res = And(a, b, stack); break;
                case '!':res = Not(a, stack); break;
            }
        }
    }
    return res;
}
char num2bool(int t) {
    if (1 == t)return 'T';
    else return 'F';
}


void Print(int number, string &orgin, SeqStack &stack) {
    int p, q, r, res;
    string pcnf;    //����ȡ��ʽ
    string pdnf;    //����ȡ��ʽ
    if (number == 3) {
        cout << "P\t" << "Q\t" << "R\t" << "Z" << endl;
        for (p = 1; p >= 0; p--) {
            for (q = 1; q >= 0; q--) {
                for (r = 1; r >= 0; r--) {
                    res = Calculate(3, orgin, stack, p, q, r);
                    if (res == 1)
                        pdnf = pdnf + "(" + (p == 1 ? "P" : "!P") + "&" + (q == 1 ? "Q" : "!Q") + "&"    //����ȡ��ʽ
                               + (r == 1 ? "R" : "!R") + ")" + " | ";
                    else
                        pcnf = pcnf + "(" + (p == 0 ? "P" : "!P") + "|" + (q == 0 ? "Q" : "!Q") + "|"    //����ȡ��ʽ
                               + (r == 0 ? "R" : "!R") + ")" + " & ";
                    char cp, cq, cr, cres;
                    cp = num2bool(p);
                    cq = num2bool(q);
                    cr = num2bool(r);
                    cres = num2bool(res);
                    cout << cp << "\t" << cq << "\t" << cr << "\t" << cres << endl;
                }
            }
        }
    }
    if (number == 2) {
        cout << "P\t" << "Q\t" << "Z" << endl;
        for (p = 1; p >= 0; p--) {
            for (q = 1; q >= 0; q--) {
                res=Calculate(2, orgin, stack, p, q, 0);
                if (res == 1)
                    pdnf = pdnf + "(" + (p == 1 ? "P" : "!P") + "&" + (q == 1 ? "Q" : "!Q") + ")" + " | ";
                else
                    pcnf = pcnf + "(" + (p == 0 ? "P" : "!P") + "|" + (q == 0 ? "Q" : "!Q") + ")" + " & ";
                char cp, cq, cres;
                cp = num2bool(p);
                cq = num2bool(q);
                cres = num2bool(res);
                cout << cp << "\t" << cq << "\t" << cres << endl;
            }
        }
    }
    //��������ٵ�����³���Ϊ0
    if (pdnf.length() != 0)
        pdnf.erase(pdnf.length() - 2);
    if (pcnf.length() != 0)
        pcnf.erase(pcnf.length() - 2);
    cout << "����ȡ��ʽ��" << pdnf << endl << endl;
    cout << "����ȡ��ʽ��" << pcnf << endl << endl;

}
int main() {
    SeqStack stack(200);
    int cnt = 0;
    string orgin;
    int number;

    cout << "****************************************" << endl;
    cout << "*               ! ��                  *" << endl;
    cout << "*               | ��ȡ                  *" << endl;
    cout << "*               & ��ȡ                  *" << endl;
    cout << "*               > ����                  *" << endl;
    cout << "*               = ˫����                *" << endl;
    cout << "****************************************" << endl;
    cout << "�������Ԫ���� (2 �� 3)" << endl;

    loop:cin >> number;
    if(2==number)
        cout << endl << "��Ԫ����P��Q��ʾ" << endl ;
    else if (3==number)
        cout << endl << "��Ԫ����P��Q��R��ʾ" << endl;
    else {
        cout << "������2��3��  " << endl;
        goto loop;
    }
    cout << "�������⣺";
    int flag = 0;

    do {
        if (flag != 0) {
            cout << "����������Ϸ��ַ�������ϸ�Ķ�������ʾ����������\n��������ʹ�ð��Ӣ�ķ��ţ�" << endl;
            cout << "�������⣺";
        }
        cin >> orgin;
        flag = 1;
    } while (!IsLegal(orgin));
    InfixToPostfix(orgin,stack);
    Print(number,orgin,stack);
    return 0;
}