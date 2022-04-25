#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 100	//线性表存储空间的初始分配量
#define LISTINCREMENT 10	//线性表存储空间的分配增量

typedef struct SqList {	
	int* elem;
	int length;
	int listsize;
}SqList;

int InitList_Sq(SqList& L)	//初始化线性表
{
	L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem)exit(0);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return 0;
}
int Assign(SqList& L){	//为顺序表L的各元素赋值
	int i, N;
	printf("Please input the Number of the SqList:");
	scanf("%d", &N);
	printf("Please input the elements:");
	for (i = 0; i < N; i++)
	{
		scanf("%d", &L.elem[i]);
		L.length++;
	}
	return 0;
}

int InsertX_B(SqList& L, int x)		//插入元素x
{
	int* q = NULL, * p = NULL;
	if (L.length >= L.listsize)
	{
		int* newbase;
		newbase = (int*)realloc(L.elem, L.listsize + LISTINCREMENT * sizeof(int));
		if (!newbase) exit(0);
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	for (int i = 1; i < L.length; i++)
	{
		if (x <= L.elem[i - 1]) {
			q = &L.elem[i - 1];
			break;
		}
	}	
	if (!q) {
		q = &L.elem[L.length];
		*q = x;
	}
	else {
		for (p = &(L.elem[L.length - 1]); p >= q; --p) *(p + 1) = *p;
		*q = x;
	}
	++L.length;
	return 0;
}

int ListTraverse(SqList L){	//遍历顺序表L
	int i;
	for (i = 0; i <= L.length - 1; i++)
		printf("%d    ", L.elem[i]);
	printf("\n");
	printf("the length is:%d\n", L.length);
	return 0;
}

int main() {
	int x;
	SqList Li;
	InitList_Sq(Li);
	Assign(Li);
	printf("Please insert your element:");
	scanf("%d", &x);
	InsertX_B(Li, x);
	ListTraverse(Li);
	return 0;
}