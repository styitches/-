﻿#include<iostream>
#include<cstring>
using namespace std;
#pragma warning (disable:4996)
#define maxSize 100
/*
赫夫曼树的存储结构，它也是一种二叉树结构，
这种存储结构既适合表示树，也适合表示森林。
*/
typedef struct Node
{
	int weight;                //权值  
	int parent;                //父节点的序号，为-1的是根节点  
	int lchild, rchild;         //左右孩子节点的序号，为-1的是叶子节点  
}HTNode, * HuffmanTree;          //用来存储赫夫曼树中的所有节点  
typedef char** HuffmanCode;    //用来存储每个叶子节点的赫夫曼编码  

HuffmanTree create_HuffmanTree(int* wet, int n);
void select_minium(HuffmanTree HT, int k, int& min1, int& min2);
int min(HuffmanTree HT, int k);
void HuffmanCoding1(HuffmanTree HT, HuffmanCode& HC, int n);
void HuffmanCoding2(HuffmanTree HT, HuffmanCode& HC, int n);
int countWPL1(HuffmanTree HT, int n);
int countWPL2(HuffmanTree HT, int n);
int main()
{
	int  w[] = { 5,4,3,2,1 };//用数组w存储各个权值
	int n = 5;//表示数组w中的个数

	HuffmanCode HC = NULL;
	HuffmanTree hTree = create_HuffmanTree(w, n);
	int wpl1 = countWPL1(hTree, n);
	printf("从叶子结点开始遍历二叉树求最小带权路径长度WPL=%d\n", wpl1);

	int wpl2 = countWPL2(hTree, n);
	printf("从根结点开始遍历二叉树求最小带权路径长度WPL=%d\n", wpl2);

	printf("\n从叶子到根结点编码结果为：\n");
	HuffmanCoding1(hTree, HC, n);

	printf("\n从根结点到叶子结点编码结果为：\n");
	HuffmanCoding2(hTree, HC, n);

	system("pause");
	return 0;
}

/*根据给定的n个权值构造一棵赫夫曼树,wet中存放n个权值*/
HuffmanTree create_HuffmanTree(int* wet, int n)
{
	//一棵有n个叶子节点的赫夫曼树共有2n-1个节点  
	int total = 2 * n - 1;
	HuffmanTree HT = (HuffmanTree)malloc(total * sizeof(HTNode));
	if (!HT)
	{
		printf("HuffmanTree malloc faild!");
		exit(-1);
	}
	int i;

	//以下初始化序号全部用-1表示，  
	//这样在编码函数中进行循环判断parent或lchild或rchild的序号时，  
	//不会与HT数组中的任何一个下标混淆  

	//HT[0],HT[1]...HT[n-1]中存放需要编码的n个叶子节点  
	for (i = 0; i < n; i++)
	{
		HT[i].parent = -1;
		HT[i].lchild = -1;
		HT[i].rchild = -1;
		HT[i].weight = *wet;
		wet++;
	}

	//HT[n],HT[n+1]...HT[2n-2]中存放的是中间构造出的每棵二叉树的根节点  
	for (; i < total; i++)
	{
		HT[i].parent = -1;
		HT[i].lchild = -1;
		HT[i].rchild = -1;
		HT[i].weight = 0;
	}

	int min1, min2; //用来保存每一轮选出的两个weight最小且parent为0的节点  
//每一轮比较后选择出min1和min2构成一课二叉树,最后构成一棵赫夫曼树  
	for (i = n; i < total; i++)
	{
		select_minium(HT, i, min1, min2);
		HT[min1].parent = i;
		HT[min2].parent = i;
		//这里左孩子和右孩子可以反过来，构成的也是一棵赫夫曼树，只是所得的编码不同  
		HT[i].lchild = min1;
		HT[i].rchild = min2;
		HT[i].weight = HT[min1].weight + HT[min2].weight;
	}
	return HT;
}
/*
从HT数组的前k个元素中选出weight最小且parent为-1的两个，分别将其序号保存在min1和min2中
*/
void select_minium(HuffmanTree HT, int k, int& min1, int& min2)
{
	min1 = min(HT, k);
	min2 = min(HT, k);
}
/*
从HT数组的前k个元素中选出weight最小且parent为-1的元素，并将该元素的序号返回
*/
int min(HuffmanTree HT, int k)
{
	int i = 0;
	int min;        //用来存放weight最小且parent为-1的元素的序号  
	int min_weight; //用来存放weight最小且parent为-1的元素的weight值  

//先将第一个parent为-1的元素的weight值赋给min_weight,留作以后比较用。  
//注意，这里不能按照一般的做法，先直接将HT[0].weight赋给min_weight，  
//因为如果HT[0].weight的值比较小，那么在第一次构造二叉树时就会被选走，  
//而后续的每一轮选择最小权值构造二叉树的比较还是先用HT[0].weight的值来进行判断，  
//这样又会再次将其选走，从而产生逻辑上的错误。  
	while (HT[i].parent != -1)
		i++;
	min_weight = HT[i].weight;
	min = i;

	//选出weight最小且parent为-1的元素，并将其序号赋给min  
	for (; i < k; i++)
	{
		if (HT[i].weight < min_weight && HT[i].parent == -1)
		{
			min_weight = HT[i].weight;
			min = i;
		}
	}

	//选出weight最小的元素后，将其parent置1，使得下一次比较时将其排除在外。  
	HT[min].parent = 1;

	return min;
}
/*
从叶子节点到根节点逆向求赫夫曼树HT中n个叶子节点的赫夫曼编码，并保存在HC中
*/
void HuffmanCoding1(HuffmanTree HT, HuffmanCode& HC, int n)
{
	//用来保存指向每个赫夫曼编码串的指针
	HC = (HuffmanCode)malloc(n * sizeof(char*));
	if (!HC)
	{
		printf("HuffmanCode malloc faild!");
		exit(-1);
	}

	//临时空间，用来保存每次求得的赫夫曼编码串
	//对于有n个叶子节点的赫夫曼树，各叶子节点的编码长度最长不超过n-1
	//外加一个'\0'结束符，因此分配的数组长度最长为n即可
	char* code = (char*)malloc(n * sizeof(char));
	if (!code)
	{
		printf("code malloc faild!");
		exit(-1);
	}

	code[n - 1] = '\0';  //编码结束符，亦是字符数组的结束标志
						 //求每个字符的赫夫曼编码
	int i;
	for (i = 0; i < n; i++)
	{
		int current = i;           //定义当前访问的节点
		int father = HT[i].parent; //当前节点的父节点
		int start = n - 1;           //每次编码的位置，初始为编码结束符的位置
									 //从叶子节点遍历赫夫曼树直到根节点
		while (father != -1)
		{
			if (HT[father].lchild == current)   //如果是左孩子，则编码为0
				code[--start] = '0';
			else                              //如果是右孩子，则编码为1       
				code[--start] = '1';
			current = father;
			father = HT[father].parent;
		}

		//为第i个字符的编码串分配存储空间
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		if (!HC[i])
		{
			printf("HC[i] malloc faild!");
			exit(-1);
		}
		//将编码串从code复制到HC
		strcpy(HC[i], code + start);
	}
	for (int i = 0; i < n; ++i) {
		printf("%s\n", HC[i]);
	}
	free(code); //释放保存编码串的临时空间
}

/*
从根节点到叶子节点无栈非递归遍历赫夫曼树HT，求其中n个叶子节点的赫夫曼编码，并保存在HC中
*/
void HuffmanCoding2(HuffmanTree HT, HuffmanCode& HC, int n)
{
	//用来保存指向每个赫夫曼编码串的指针  
	HC = (HuffmanCode)malloc(n * sizeof(char*));
	if (!HC)
	{
		printf("HuffmanCode malloc faild!");
		exit(-1);
	}

	//临时空间，用来保存每次求得的赫夫曼编码串  
	//对于有n个叶子节点的赫夫曼树，各叶子节点的编码长度最长不超过n-1  
	//外加一个'\0'结束符，因此分配的数组长度最长为n即可  
	char* code = (char*)malloc(n * sizeof(char));
	if (!code)
	{
		printf("code malloc faild!");
		exit(-1);
	}

	int cur = 2 * n - 2;    //当前遍历到的节点的序号，初始时为根节点序号  
	int code_len = 0;   //定义编码的长度  

//构建好赫夫曼树后，把weight用来当做遍历树时每个节点的状态标志  
//weight=0表明当前节点的左右孩子都还没有被遍历  
//weight=1表示当前节点的左孩子已经被遍历过，右孩子尚未被遍历  
//weight=2表示当前节点的左右孩子均被遍历过  
	int i;
	for (i = 0; i < cur + 1; i++)
	{
		HT[i].weight = 0;
	}

	//从根节点开始遍历，最后回到根节点结束  
	//当cur为根节点的parent时，退出循环  
	while (cur != -1)
	{
		//左右孩子均未被遍历，先向左遍历  
		if (HT[cur].weight == 0)
		{
			HT[cur].weight = 1;    //表明其左孩子已经被遍历过了  
			if (HT[cur].lchild != -1)
			{   //如果当前节点不是叶子节点，则记下编码，并继续向左遍历  
				code[code_len++] = '0';
				cur = HT[cur].lchild;
			}
			else
			{   //如果当前节点是叶子节点，则终止编码，并将其保存起来  
				code[code_len] = '\0';
				HC[cur] = (char*)malloc((code_len + 1) * sizeof(char));
				if (!HC[cur])
				{
					printf("HC[cur] malloc faild!");
					exit(-1);
				}
				strcpy(HC[cur], code);  //复制编码串  
			}
		}

		//左孩子已被遍历，开始向右遍历右孩子  
		else if (HT[cur].weight == 1)
		{
			HT[cur].weight = 2;   //表明其左右孩子均被遍历过了  
			if (HT[cur].rchild != -1)
			{   //如果当前节点不是叶子节点，则记下编码，并继续向右遍历  
				code[code_len++] = '1';
				cur = HT[cur].rchild;
			}
		}

		//左右孩子均已被遍历，退回到父节点，同时编码长度减1  
		else
		{
			HT[cur].weight = 0;
			cur = HT[cur].parent;
			--code_len;
		}

	}
	for (int i = 0; i < n; ++i) {
		printf("%s\n", HC[i]);
	}
	free(code);
}
/*
从叶子结点开始遍历二叉树直到根结点，根结点为HT[2n-1],且HT[2n-1].parent=-1;
各叶子结点为HT[0]、HT[1]...HT[n-1]。
关键步骤是求出各个叶子结点的路径长度，用此路径长度*此结点的权值就是
此结点带权路径长度，最后将各个叶子结点的带权路径长度加起来即可。
*/
int countWPL1(HuffmanTree HT, int n)
{
	int i, countRoads, WPL = 0;
	/*
	由creat_huffmanTree（）函数可知，HT[0]、HT[1]...HT[n-1]存放的就是各个叶子结点，
	所以挨个求叶子结点的带权路径长度即可
	*/
	for (i = 0; i < n; i++)
	{
		int father = HT[i].parent; //当前节点的父节点
		countRoads = 0;//置当前路径长度为0
		//从叶子节点遍历赫夫曼树直到根节点
		while (father != -1)
		{
			countRoads++;
			father = HT[father].parent;
		}
		WPL += countRoads * HT[i].weight;
	}
	return WPL;
}
/*
以下是从根结点开始遍历二叉树，求最小带权路径长度。关键步骤是求出各个叶子
结点的路径长度，用此路径长度*此结点的权值就是此结点带权路径长度，最后将
各个叶子结点的带权路径长度加起来即可。
*/
int countWPL2(HuffmanTree HT, int n)
{
	int cur = 2 * n - 2;    //当前遍历到的节点的序号，初始时为根节点序号  
	int countRoads = 0, WPL = 0;//countRoads保存叶子结点的路径长度

//构建好赫夫曼树后，把visit[]用来当做遍历树时每个节点的状态标志  
//visit[cur]=0表明当前节点的左右孩子都还没有被遍历  
//visit[cur]=1表示当前节点的左孩子已经被遍历过，右孩子尚未被遍历  
//visit[cur]=2表示当前节点的左右孩子均被遍历过  
	int visit[maxSize] = { 0 };//visit[]是标注数组,初始化为0

	//从根节点开始遍历，最后回到根节点结束  
	//当cur为根节点的parent时，退出循环  
	while (cur != -1)
	{
		//左右孩子均未被遍历，先向左遍历  
		if (visit[cur] == 0)
		{
			visit[cur] = 1;    //表明其左孩子已经被遍历过了  
			if (HT[cur].lchild != -1)
			{   //如果当前节点不是叶子节点，则路径长度+1，并继续向左遍历  
				countRoads++;
				cur = HT[cur].lchild;
			}
			else
			{   //如果当前节点是叶子节点，则计算此结点的带权路径长度，并将其保存起来  
				WPL += countRoads * HT[cur].weight;
			}
		}

		//左孩子已被遍历，开始向右遍历右孩子  
		else if (visit[cur] == 1)
		{
			visit[cur] = 2;
			if (HT[cur].rchild != -1)
			{   //如果当前节点不是叶子节点，则记下编码，并继续向右遍历  
				countRoads++;
				cur = HT[cur].rchild;
			}
		}

		//左右孩子均已被遍历，退回到父节点，同时路径长度-1 
		else
		{
			visit[cur] = 0;
			cur = HT[cur].parent;
			--countRoads;
		}

	}
	return WPL;
}
