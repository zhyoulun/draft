#include <stdio.h>
#include <stdlib.h>

#define t 2

typedef struct BTree_Node *BTree;

struct BTree_Node {
	int n;
	int leaf;
	int *key;
	BTree *c;
};

void BTree_Print(BTree T);
void BTree_PrintCore(BTree T, int depth);
void BTree_Search(BTree T, int k, BTree *pT_out, int *pi_out);
BTree BTree_Sample();
BTree BTree_SampleRandom(int n, int depth);
void BTree_Delete(BTree T);
BTree BTree_CreateEmpty();
void BTree_SplitChild(BTree x, int i);
BTree BTree_AlocateNode();
int BTree_CheckNode(BTree T);

BTree BTree_AlocateNode()
{
	BTree T = (BTree)malloc(sizeof(struct BTree_Node));
	//printf("t=%d\n",t);
	T->key = (int *)malloc((2 * t - 1)*sizeof(int));//键
	T->c = (BTree *)malloc((2 * t)*sizeof(BTree));//指针
	T->leaf = 1;//是否为叶子结点
	T->n = 0;//当前键的个数
	return T;
}

int BTree_CheckNode(BTree T)
{
}

BTree BTree_CreateEmpty()
{
	BTree T = BTree_AlocateNode();
	T->leaf = 1;
	T->n = 0;
	return T;
}

void BTree_Search(BTree T, int k, BTree *pT_out, int *pi_out)
{
	int i = 0;
	while (i < T->n && k>T->key[i]) {
		i++;
	}
	if (i<T->n && k == T->key[i]) {
		*pT_out = T;
		*pi_out = i;
		return;
	}
	else if (T->leaf == 1) {
		free(pT_out);
		pT_out = NULL;
		*pi_out = -1;
	}
	else {
		BTree_Search(T->c[i], k, pT_out, pi_out);
	}
}

void BTree_Print(BTree T)
{
	printf("-----start-----\n");
	BTree_PrintCore(T, 0);
	printf("------end------\n");
}

void BTree_PrintCore(BTree T, int depth)
{
	int i, j;
	for (j = 0; j < depth; j++) {
		printf(" ");
	}
	printf("[ ");
	for (i = 0; i < T->n; i++) {
		printf("%d ", T->key[i]);
	}
	printf("]\n");

	if (T->n == 0) {
		return;
	}

	for (i = 0; i < T->n + 1; i++) {
		for (j = 0; j < depth; j++) {
			printf(" ");
		}
		if (T->c[i] == NULL) {
			printf(" [ null ]\n");
		}
		else {
			BTree_PrintCore(T->c[i], depth + 1);
		}
	}
}

BTree BTree_Sample()
{
	int i, j;

	BTree T = BTree_AlocateNode();
	T->n = 4;
	T->leaf = 0;
	for (i = 0; i < T->n; i++) {
		T->key[i] = 100 * (i + 1);
	}
	for (i = 0; i < 1 + T->n; i++) {
		BTree tempT = BTree_AlocateNode();
		tempT->n = 4;
		tempT->leaf = 1;
		tempT->key = (int *)malloc(tempT->n * sizeof(int));
		for (j = 0; j < tempT->n; j++) {
			tempT->key[j] = 100 * i + (j + 1) * 25;
		}
		tempT->c = (BTree *)malloc((1 + tempT->n) * sizeof(BTree));
		for (j = 0; j < 1 + tempT->n; j++) {
			tempT->c[j] = NULL;
		}
		T->c[i] = tempT;//NULL;//(BTree)malloc(sizeof(struct BTree_Node));
	}
	return T;
}

BTree BTree_SampleRandom(int n, int depth)
{
	BTree T = (BTree)malloc(sizeof(struct BTree_Node));
	return T;
}

void BTree_Delete(BTree T)
{
	if (T == NULL) {
		return;
	}

	int i;
	for (i = 0; i < 1+T->n; i++) {
		BTree_Delete(T->c[i]);
	}
	free(T->key);
	free(T);
}

void BTree_SplitChild(BTree x, int i)
{
	int j;

	BTree z = BTree_AlocateNode();
	BTree y = x->c[i];
	
	//将y的后半部分复制给z
	z->leaf = y->leaf;
	z->n = t - 1;
	for (j = 0; j < t - 1; j++) {
		z->key[j] = y->key[t+j];
	}
	if (!y->leaf) {
		for (j = 0; j < t; j++) {
			z->c[j] = y->c[t+j];
		}
	}

	for (j = x->n; j >= i + 1; j--) {
		x->c[j + 1] = x->c[j];
	}
	x->c[i + 1] = z;
	for (j = x->n - 1; j >= i; j--) {
		x->key[j + 1] = x->key[j];
	}

	x->key[i] = y->key[t];
	x->n = x->n + 1;
}

int main()
{
	BTree T = BTree_Sample();

	BTree_Print(T);
	//printf("%d\n", T->c[0]->key[1]);
	//BTree_SplitChild(T->c[1], 1);

	return 0;

	BTree *pT_out = (BTree *)malloc(sizeof(BTree));
	int *pi_out = (int *)malloc(sizeof(int));
	BTree_Search(T, 190, pT_out, pi_out);

	if (pT_out != NULL) {
		BTree_Print(*pT_out);
		printf("i_out=%d\n",*pi_out);
	}





	free(T);
	free(pT_out);

	T = BTree_CreateEmpty();
	BTree_Print(T);

	return 0;
}