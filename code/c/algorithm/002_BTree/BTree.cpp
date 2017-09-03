#include <stdio.h>
#include <stdlib.h>

#define t 2//��С������ÿ���ڲ�������ٺ���t�����ӣ����ຬ��2t������

typedef struct BTree_Node* BTree;	//ָ��B������ָ��

//B����㶨��
struct BTree_Node {
	int n;				//�����key�ĸ���
	int *key;			//key���飬����Ϊ2*t-1��ʵ�ʴ���n��
	BTree *c;			//�ӽ��ָ�����飬����Ϊ2*t��ʵ�ʴ���n+1��
	int leaf;			//�Ƿ�ΪҶ�ӽ��
};

//����һ�����
BTree BTree_AlocateNode();
//����һ������
BTree BTree_CreateEmpty();
//����һ��������������
BTree BTree_CreateExample();
//��ӡ������
void BTree_Print(BTree T, int depth);
//����һ������ֵ
void BTree_Search(BTree T, int find, BTree* resultTree, int* resultIndex);
//����һ�����
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
	//y������
	BTree y = x->c[index];

	//��ʼ��z�����y�ĺ���
	BTree z = BTree_AlocateNode();
	//z�Ƿ�ΪҶ�Ӻ�yһ��
	z->leaf = y->leaf;
	z->n = t - 1;
	//����y�ĺ��ε�z
	for (j = 0; j < t - 1; j++) {
		z->key[j] = y->key[j+t];
	}
	if (y->leaf == 0) {
		for (j = 0; j < t; j++) {
			z->c[j] = y->c[j+t];
		}
	}
	//����y
	y->n = t - 1;
	//����������
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