#include <stdio.h>
#include <stdlib.h>

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

	BTree T = (BTree)malloc(sizeof(struct BTree_Node));
	T->n = 2;
	T->leaf = 0;
	T->key = (int *)malloc(T->n * sizeof(int));
	for (i = 0; i < T->n; i++) {
		T->key[i] = 100 * (i + 1);
	}
	T->c = (BTree *)malloc((1 + T->n) * sizeof(BTree));
	for (i = 0; i < 1 + T->n; i++) {
		BTree tempT = (BTree)malloc(sizeof(struct BTree_Node));
		tempT->n = 2;
		tempT->leaf = 1;
		tempT->key = (int *)malloc(tempT->n * sizeof(int));
		for (j = 0; j < tempT->n; j++) {
			tempT->key[j] = 100 * i + (j + 1) * 45;
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

int main()
{
	BTree T = BTree_Sample();

	BTree_Print(T);

	BTree *pT_out = (BTree *)malloc(sizeof(BTree));
	int *pi_out = (int *)malloc(sizeof(int));
	BTree_Search(T, 190, pT_out, pi_out);

	if (pT_out != NULL) {
		BTree_Print(*pT_out);
		printf("i_out=%d\n",*pi_out);
	}

	return 0;
}