#include<iostream>
using namespace std;
typedef int elementtype;
int E;
#define max 100
int inf = 99999;
bool visited[max];
typedef struct {
	int d;//����ĳ������·������ 
	int pre;//�����·���Ǿ����ĸ��㴫�����ģ�Դ�������ĳ���� 
}path;
class graph
{
public:
	elementtype node[max];     //����� 
	int distance[max][max];  //�ڽӾ���
	int n;       //��ǰ������
	int e = 0;//����
	int vis[max];//��ʾ���·���Ƿ��ҵ�
	path to[max];//��¼��ǰĳ��������·�������Ǹ��㴫����
	graph()
	{
		int i, j;
		for (i = 1; i <= max; i++)
			node[i] = -1;
	};
	void visite(elementtype v) { cout << node[v] << "  "; }
	//����ͼ
	void create()
	{
		int i, j, k;
		cout << "�����붥����" << endl;
		cin >> n;
		for (i = 1; i <= n; i++) {
			vis[i] = 0;
		}
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				distance[i][j] = inf;
			}
			to[i].d = inf;
		}
		cout << "������������ֵ" << endl;
		for (k = 1; k <= n; k++)
			cin >> node[k];
		cout << "������ߣ�i j��iΪ-1ʱ����" << endl;
		cin >> i >> j;
		while (i != -1)
		{
			distance[i][j] = distance[j][i] = 1;
			cin >> i >> j;
		}
	};
	////����ͼ(����)
	//void create()
	//{
	//	int i, j, k;
	//	cout << "�����붥����" << endl;
	//	cin >> n;
	//	for (i = 1; i <= n; i++) {
	//		vis[i] = 0;
	//	}
	//	for (i = 1; i <= n; i++) {
	//		for (j = 1; j <= n; j++) {
	//			distance[i][j] = inf;
	//		}
	//		to[i].d = inf;
	//	}
	//	cout << "������������ֵ" << endl;
	//	for (k = 1; k <= n; k++)
	//		cin >> node[k];
	//	cout << "������ߺͱߵ�ֵ��i j k��iΪ-1ʱ����" << endl;
	//	cin >> i >> j;
	//	while (i != -1)
	//	{
	//		cin >> distance[i][j];
	//		cin >> i >> j;
	//	}
	//};
	int firstadj(elementtype v)
	{
		if (v != -1)
		{
			for (int col = 1; col <= n; col++)
				if (distance[v][col] != inf && distance[v][col] != 0) return col;
		}
		return -1;
	};
	int nextadj(elementtype v, elementtype m)
	{
		if (v != -1 && m != -1)
		{
			for (int col = m + 1; col <= n; col++)
				if (distance[v][col] != inf && distance[v][col] != 0) return col;
		}
		return  -1;
	};
	void  dfs(int v)
	{
		int w;
		visited[v] = true;
		w = firstadj(v);
		while (w != -1)
		{
			e++;
			if (!visited[w])
				dfs(w);
			w = nextadj(v, w);
		}
	}
	void travel() {
		for (int i = 1; i <= n; i++) {
			visited[i] = false;
		}
		for (int i = 1; i <= n; i++) {
			if (visited[i] == false) {
				dfs(i);
			}
		}
	}
	void Enum() {
		travel();
		e = e / 2;
	}
	//�ж��Ƿ�����
	void istree() {
		int notrue = 0;
		for (int i = 1; i <= n; i++) {
			visited[i] = false;
		}
		e = 0;
		Enum();
		for (int i = 1; i <= n; i++) {
			if (!visited[i]) {
				notrue++;
			}
		}
		if (notrue != 0) {
			cout << "������ͼ����ͨ������һ����" << endl;
		}
		else if (notrue == 0 && e != n - 1) {
			cout << "������ͼͼ�л�·������һ����" << endl;
		}
		else {
			cout << "������ͼ��һ����" << endl;
		}
	}
	/*���������·��*/
	void path(int x, int y) {
		int i, min, j, k;
		for (i = 1; i <= n; i++) {
			to[i].d = distance[x][i]; //��ʼ��Դ�㵽i���Ȩֵ��֮������лᷢ���仯 
			if (distance[x][i] != inf && distance[x][i] != 0) {
				to[i].pre = x;
			}
		}
		vis[x] = 1;
		for (i = 1; i <= n; i++) {//��ѭ��n-1�Σ�ÿѭ��һ�Σ�ȷ��һ�����·���ٴ�ѭ��ʱ����·�Ͳ��ÿ����ˣ�ȥѰ����һ�����· 
			min = inf;
			for (j = 1; j <= n; j++) {//Ѱ����һ����ǰ���· 
				if (to[j].d < min && vis[j] == 0) {
					min = to[j].d;
					k = j;
				}
			}
			vis[k] = 1;//�ҵ��ˣ���k���·�ǵ�ǰ���·���������������Ѱ����һ�����· 
			for (j = 1; j <= n; j++) {
				if (to[j].d > to[k].d + distance[k][j] && vis[j] == 0) {//������k�㵽��j���·���Ƿ�С����������j���·�� 
					to[j].d = to[k].d + distance[k][j];
					to[j].pre = k;//�ı�j����˭�����ģ����ڵ�j������·���Ǿ���k��ģ���j�㴫�� 
				}
			}
		}
		cout << "����·��Ϊ��";
		cout << y;
		j = y;
		while (j != x) {
			j = to[j].pre;
			cout << "<-" << j;
		}
		cout << endl;
	}
	/*��ԭ�㵽����������·��*/
	//void path() {
	//	int i, min, j, k;
	//	for (i = 2; i <= n; i++) {
	//		to[i].d = distance[1][i]; //��ʼ��Դ�㵽i���Ȩֵ��֮������лᷢ���仯 
	//		if (distance[1][i] != inf) {
	//			to[i].pre = 1;
	//		}
	//	}
	//	vis[1] = 1;
	//	for (i = 2; i <= n; i++) {//��ѭ��n-1�Σ�ÿѭ��һ�Σ�ȷ��һ�����·���ٴ�ѭ��ʱ����·�Ͳ��ÿ����ˣ�ȥѰ����һ�����· 
	//		min = inf;
	//		for (j = 2; j <= n; j++) {//Ѱ����һ����ǰ���· 
	//			if (to[j].d < min && vis[j] == 0) {
	//				min = to[j].d;
	//				k = j;
	//			}
	//		}
	//		vis[k] = 1;//�ҵ��ˣ���k���·�ǵ�ǰ���·���������������Ѱ����һ�����· 
	//		for (j = 2; j <= n; j++) {
	//			if (to[j].d > to[k].d + distance[k][j] && vis[j] == 0) {//������k�㵽��j���·���Ƿ�С����������j���·�� 
	//				to[j].d = to[k].d + distance[k][j];
	//				to[j].pre = k;//�ı�j����˭�����ģ����ڵ�j������·���Ǿ���k��ģ���j�㴫�� 
	//			}
	//		}
	//	}
	//	for (i = 2; i <= n; i++) {//��������������·�� 
	//		cout << "ԭ�㵽�õ�����·������Ϊ��";
	//		cout << to[i].d << endl;
	//		cout << "����·��Ϊ��";
	//		cout << i;
	//		j = i;
	//		while (j != 1) {
	//			j = to[j].pre;
	//			cout << "<-" << j;
	//		}
	//		cout << endl;
	//	}
	//}
};