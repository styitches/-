#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
using namespace std;

bool isVN(char a) {
    if (a >= 'A' && a <= 'Z')
        return true;
    else
        return false;
}

int LL_1(string grammar, string stc) {
    char start = grammar[0];          //��¼��ʼ��
    int a[10][10] = { 0 };
    vector<char> vn;
    vector<string> drived;
    vector<char> vt;
    int i = 0;
    while (i < grammar.length()) {          //��ȡ���ս��
        if (isVN(grammar[i])) {
            vn.push_back(grammar[i]);
        }
        i++;
    }
    i = 0;

    while (i < grammar.length()) {          //��ȡ�����Ƶ�ʽ
        string tmp = "";
        while (grammar[i] != '\n' && i < grammar.length()) {
            tmp += grammar[i];
            i++;
        }
        i++;
        drived.push_back(tmp);
    }

    i = 0;
    while (i < grammar.length()) {          //��ȡ�ս��
        if (grammar[i] != '\n' && !isVN(grammar[i]) && grammar[i] != '|' && grammar[i] != '?' && grammar[i] != ' ') {
            vt.push_back(grammar[i]);
        }
        i++;
    }

    sort(vn.begin(), vn.end());          //���ս��ȥ��
    auto pos = unique(vn.begin(), vn.end());     //�����ڵ��ظ�Ԫ�طŵ�������ĩβ��������ָ���һ���ظ�Ԫ�صĵ�����
    vn.erase(pos, vn.end());                                            //ɾ��ָ���һ���ظ�Ԫ�صĵ�����������ĩβ������Ԫ��

    sort(vt.begin(), vt.end());          //���ս��ȥ��
    auto pos2 = unique(vt.begin(), vt.end());
    vt.erase(pos2, vt.end());

    int f_size = vn.size();   //sizeof FIRST and FOLLOW

    //��ʼ��first���� �ҵ��������first����
    set<char> first[10];
    for (int i = 0; i < f_size; i++) {               //init first[]
        for (int j = 0; j < drived.size(); j++) {
            for (int k = 2; k < drived[j].size(); k++) {
                if (vn[i] == drived[j][0]) {
                    if ((drived[j][k - 1] == '|' && !isVN(drived[j][k])) || (drived[j][k - 1] == ' ' && !isVN(drived[j][k]))) {
                        first[i].insert(drived[j][k]);
                    }
                }
            }
        }
    }

    for (int j = 0; j < drived.size(); j++) {           //�þ����¼����E->T T->S�ķ��ս��ͨ·
        for (int k = 0; k < f_size; k++) {
            if (drived[j][0] == vn[k]) {
                for (int l = 2; l < drived[j].size(); l++) {
                    if (isVN(drived[j][l])) {
                        for (int m = 0; m < f_size; m++) {
                            if (drived[j][l] == vn[m] && (drived[j][l - 1] == '|' || drived[j][l - 1] == ' ')) {
                                a[k][m] = 1;

                            }


                        }
                    }
                }
                break;
            }

        }
    }

    //��ʼ����־���� ��¼first�ĸı�
    int flag[10] = { 0 };
    for (int j = 0; j < 10; j++) {
        flag[j] = first[j].size();
    }
    int sig = 0;
    for (int j = 0; j < f_size; j++) {     //��ͨ·�еķ��ս��first��������
        for (int k = 0; k < f_size; k++) {
            if (a[j][k] == 1) {
                for (set<char>::iterator it = first[k].begin(); it != first[k].end(); it++) {
                    first[j].insert(*it);
                }
            }
        }
    }
    do {
        for (int j = 0; j < f_size; j++) {
            for (int k = 0; k < f_size; k++) {
                if (a[j][k] == 1) {
                    for (set<char>::iterator it = first[k].begin(); it != first[k].end(); it++) {
                        first[j].insert(*it);
                    }
                }
            }
        }
        for (int j = 0; j < 10; j++) {
            if (flag[j] != first[j].size()) {           //��first���Ϸ����ı�ʱ���͵�ִ��ѭ����ֱ�����ı�Ϊֹ
                sig = 1;
                flag[j] = first[j].size();
                break;
            }
            if (j == 9) {
                sig = 0;
            }
        }
    } while (sig);

    set<char> follow[10];
    for (int j = 0; j < f_size; j++) {
        if (vn[j] == start) {
            follow[j].insert('#');
            break;
        }
    }

    //�����Ƶ�ʽ�Ӷ�λ��ʼ 1����������д���� �����first����ǰ���follow 2������д��������ս����������follow
    for (int j = 0; j < drived.size(); j++) {
        for (int k = 2; k < drived[j].size() - 1; k++) {
            if (isVN(drived[j][k]) && isVN(drived[j][k + 1])) {         //�����������ս��
                for (int l = 0; l < f_size; l++) {
                    if (drived[j][k + 1] == vn[l]) {
                        for (int m = 0; m < f_size; m++) {
                            if (drived[j][k] == vn[m]) {
                                for (set<char>::iterator it = first[l].begin(); it != first[l].end(); it++) {
                                    if (*it != '?') {
                                        follow[m].insert(*it);    //��first-�� ����ǰfollow
                                    }

                                }
                                break;
                            }
                        }
                        break;
                    }
                }
            }

            if (isVN(drived[j][k]) && !isVN(drived[j][k + 1]) && drived[j][k + 1] != '|' && drived[j][k + 1] != '?') {    //��д��������ս��
                for (int l = 0; l < f_size; l++) {
                    if (drived[j][k] == vn[l]) {
                        follow[l].insert(drived[j][k + 1]);  //����ս��ֱ�Ӳ���follow
                        break;
                    }
                }
            }
        }
    }

    int flag2[10] = { 0 };
    for (int j = 0; j < 10; j++) {
        flag2[j] = follow[j].size();
    }
    sig = 0;

    //follow���������� E->anyH follow E = follow H
    do {
        for (int j = 0; j < drived.size(); j++) {
            for (int k = 2; k < drived[j].size() - 1; k++) {
                if (k == drived[j].size() - 2 && isVN(drived[j][k + 1])) {
                    for (int l = 0; l < f_size; l++) {
                        if (drived[j][k + 1] == vn[l]) {
                            for (int m = 0; m < f_size; m++) {
                                if (drived[j][0] == vn[m]) {
                                    for (set<char>::iterator it = follow[l].begin(); it != follow[l].end(); it++) {
                                        follow[m].insert(*it);                                                                      //H�Ĳ���E��
                                    }
                                    for (set<char>::iterator it = follow[m].begin(); it != follow[m].end(); it++) {
                                        follow[l].insert(*it);
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }

                if (isVN(drived[j][k]) && drived[j][k + 1] == '|') {     //��|��ߵķ��ս����follow�������һ�����ϵ�follow
                    for (int l = 0; l < f_size; l++) {
                        if (drived[j][k] == vn[l]) {
                            for (int m = 0; m < f_size; m++) {
                                if (drived[j][0] == vn[m]) {
                                    for (set<char>::iterator it = follow[l].begin(); it != follow[l].end(); it++) {
                                        follow[m].insert(*it);
                                    }
                                    for (set<char>::iterator it = follow[m].begin(); it != follow[m].end(); it++) {
                                        follow[l].insert(*it);
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }

        for (int j = 0; j < 10; j++) {
            if (flag2[j] != follow[j].size()) {           //��follow���Ϸ����ı�ʱ���͵�ִ��ѭ����ֱ�����ı�Ϊֹ
                sig = 1;
                flag2[j] = follow[j].size();
                break;
            }
            if (j == 9) {
                sig = 0;
            }
        }
    } while (sig);

    // ����M[A,a]

    //��д��ͷ
    string m[10][10];
    for (int i = 0; i < vt.size(); i++) {
        string tmp = "";
        tmp += vt[i];
        m[0][i + 1] = tmp;
    }

    for (int i = 0; i < vn.size(); i++) {
        string tmp = "";
        tmp += vn[i];
        m[i + 1][0] = tmp;
    }


    //����first������д
    for (int i = 1; i < vt.size() + 1; i++) {
        for (int j = 1; j < vn.size() + 1; j++) {
            auto pos = first[j - 1].find(m[0][i][0]);
            auto pos2 = first[j - 1].find('?');
            if (pos != first[j - 1].end()) {
                m[j][i] = "o";
                for (int k = 0; k < drived.size(); k++) {
                    if (drived[k][0] == m[j][0][0]) {
                        if (drived[k][2] == m[0][i][0]) {
                            m[j][i] = drived[k];
                        }
                    }
                }

            }

            else if (pos2 != first[j - 1].end()) {         //FIRST�����а����մ�����鿴���ս���Ƿ��ڸ÷��ս����FOLLOW������
                auto pos3 = follow[j - 1].find(m[0][i][0]);
                if (pos3 != follow[j - 1].end()) {
                    m[j][i] = "?";
                }
                else m[j][i] = "$";
            }
            else m[j][i] = "$";
        }
    }


    //������ʽ����
    for (int i = 1; i < vt.size() + 1; i++) {
        for (int j = 1; j < vn.size() + 1; j++) {
            if (m[j][i][0] == 'o') {
                for (int k = 0; k < drived.size(); k++) {
                    if (drived[k][0] == m[j][0][0]) {
                        if (isVN(drived[k][2])) {
                            m[j][i] = drived[k];
                        }
                    }
                }
            }
        }
    }

    //���� ���ұ������
    string st = "";
    st += start;
    st += '#';

    while (stc.length() > 1) {
        char a, b;
        a = stc[0];
        b = st[0];
        int flag = 0;
        if (a == b) {
            cout << "��ǰ�����ַ�������ͬ��ɾȥ" << a << endl;
            stc.erase(0, 1);
            st.erase(0, 1);
            cout << endl;

        }

        else {
            for (int i = 1; i < vt.size() + 1; i++) {
                if (flag)
                    break;
                for (int j = 1; j < vn.size() + 1; j++) {
                    if (a == m[0][i][0] && b == m[j][0][0]) {
                        string tmp = m[j][i];
                        flag = 1;
                        if (tmp[0] == '?') {
                            cout << "ƥ��ʽ:  " << st<<'	';
                            cout << "���:  " << stc<<'	';
                            st.erase(0, 1);
                            cout << "��:  ->?" ;
                            cout << endl; cout << endl;
                        }
                        else {
                            cout << "ƥ��ʽ:  " << st << '	';
                            cout << "���:  " << stc << '	';
                            tmp.insert(1, "->");
                            cout << "�ù�ʽ:  " << tmp << '	';
                            tmp.erase(0, 4);
                            st.erase(0, 1);
                            st.insert(0, tmp);

                            cout << endl; cout << endl;
                        }
                        break;
                    }

                }
            }
        }

    }

    while (st.length() > 1) {
        cout << "��->������" << st[0] << endl;
        st.erase(0, 1);
    }

    return 0;
}

int main() {
    string s = "E#";
    string
            wenfa = "E TG\nG +TG\nG -TG\nG ?\nT FS\nS *FS\nS /FS\nS ?\nF (E)\nF i"; //�ķ�����
    string s_in = "i+i*i#";            //���������
    LL_1(wenfa, s_in);
    return 0;
}