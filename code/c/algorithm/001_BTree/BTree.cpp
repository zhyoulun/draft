#include <stdio.h>

struct BTree_Node{
	int n;
	int *key;
	int leaf;
	BTree *c;
};

typedef struct BTree_Node *BTree;

int BTree_Search(BTree x, int k, BTree x_out)
{
	int i=0;
	while(i < x->n && k > x->key[i]) i++;
	if(i < x->n && k == x->key[i]){
		x_out = x;
		return i;
	}else if(x->leaf==1){
		x_out = NULL;
		return 0;
	} else{
	}
}

int main()
{
	printf("hello\n");
	return 0;
}