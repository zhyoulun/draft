#include <stdio.h>
#include <stdlib.h>

#define t 2//最小度数：每个内部结点至少含有t个孩子，至多含有2t个孩子

typedef struct BTree_Node* BTree;	//指向B树结点的指针

//B树结点定义
struct BTree_Node {
	int n;				//结点中key的个数
	int *key;			//key数组，容量为2*t-1，实际存有n个
	BTree *c;			//子结点指针数组，容量为2*t，实际存有n+1个
	int leaf;			//是否为叶子结点
};

//分配一个结点
BTree BTree_AlocateNode();
//创建一个空树
BTree BTree_CreateEmpty();
//创建一个二叉树的例子
BTree BTree_CreateExample();
//打印二叉树
void BTree_Print(BTree T, int depth);
//搜索一个结点的值
void BTree_Search(BTree T, int find, BTree* resultTree, int* resultIndex);
//分裂一个结点
void BTree_SplidChild(BTree x, int index);

BTree BTree_CreateExample()
{
	BTree T = BTree_AlocateNode();
	T->leaf = 0;
	T->n = 3;
	int i,j;
	for (i = 0; i < T->n; i++) {
		T->key[i] = (i + 1)*10;
	}

	for (i = 0; i < 2 * t; i++) {
		T->c[i] = BTree_AlocateNode();
	}

	for (i = 0; i < T->n + 1; i++) {
		T->c[i]->leaf = 1;
		T->c[i]->n = 3;
		for (j = 0; j < T->c[i]->n; j++) {
			T->c[i]->key[j] = (j+1) + i * 10;
		}
	}

	return T;
}


void BTree_Print(BTree T, int depth=0)
{
	if (T == NULL) {
		return;
	}
	int i;
	for (i = 0; i < depth; i++) {
		printf(" ");
	}
	printf("[");
	for (i = 0; i < T->n; i++) {
		printf("%d ", T->key[i]);
	}
	printf("]\n");

	if (T->leaf==0) {
		for (i = 0; i < T->n + 1; i++) {
			BTree_Print(T->c[i], depth+1);
		}
	}
}


void BTree_Search(BTree T, int find, BTree* resultTree, int* resultIndex)
{
	int i = 0;
	while (i<T->n && find>T->key[i]) i++;
	if (i <= T->n - 1 && T->key[i] == find) {
		*resultTree = T;
		*resultIndex = i;
	}
	else if(T->leaf){
		resultTree = NULL;
	}
	else {
		BTree_Search(T->c[i], find, resultTree, resultIndex);
	}
}


BTree BTree_CreateEmpty()
{
	BTree T = BTree_AlocateNode();
	T->leaf = 1;
	T->n = 0;
	return T;
}


BTree BTree_AlocateNode()
{
	BTree T = (BTree)malloc(sizeof(struct BTree_Node));
	T->leaf = 1;
	T->n = 0;
	T->key = (int *)malloc(sizeof(int)*(2*t-1));
	T->c = (BTree *)malloc(sizeof(BTree)*(2 * t));
	return T;
}

void BTree_SplidChild(BTree x, int index)
{
	int j;
	//y是满的
	BTree y = x->c[index];

	//初始化z，存放y的后半段
	BTree z = BTree_AlocateNode();
	//z是否为叶子和y一致
	z->leaf = y->leaf;
	z->n = t - 1;
	//复制y的后半段到z
	for (j = 0; j < t - 1; j++) {
		z->key[j] = y->key[j+t];
	}
	if (y->leaf == 0) {
		for (j = 0; j < t; j++) {
			z->c[j] = y->c[j+t];
		}
	}
	//整理y
	y->n = t - 1;
	//提升到父级
	for (j = x->n; j >= index; j--) {
		x->c[j + 1] = x->c[j];
	}
	x->c[index + 1] = z;
	for (j = x->n - 1; j >= index; j--) {
		x->key[j + 1] = x->key[j];
	}
	x->n++;
}


void main(void)
{
	BTree T = BTree_CreateExample();
	BTree_Print(T);

	BTree* temp = (BTree*)malloc(sizeof(BTree));
	int *index = (int *)malloc(sizeof(int));
	BTree_Search(T, 12, temp, index);
	printf("%d, %d\n",(*temp)->key[0], *index);

	BTree_SplidChild(T, 1);

	T = BTree_CreateEmpty();
	BTree_Print(T);
}