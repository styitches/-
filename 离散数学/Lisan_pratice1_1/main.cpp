#include <iostream>
using namespace std;

int And(int a,int b) {
    int res = a * b;
    return res;
}

int Or (int a, int b) {
    int res = a + b;
    res = res > 0 ? 1 : res;
    return res;
}
int Not(int a) {
    int res = a == 1 ? 0 : 1;
    return res;
}

int If(int a, int b) { //����
    int res = (b == 1 && a == 0) ? 0 : 1;
    return res;
}

int Iif(int a, int b) {//˫����
    int res = (b == a) ? 1 : 0;
    return res;
}
int main() {
    int a, b, c;
    cout << "���������������Ԫ����ֵ��" << endl;
    cin >> a >> b;
    cout << "��ȡ��������" << And(a, b) << endl;
    cout << "��ȡ��������" << Or(a, b) <<endl;
    cout << "��������������" << If(a, b) <<endl;
    cout << "˫������������" << Iif(a, b) <<endl;

    cout << "������ȡ�������Ԫ����ֵ��" << endl;
    cin >> c;
    cout << "ȡ����������" << Not(c) << endl;
}
