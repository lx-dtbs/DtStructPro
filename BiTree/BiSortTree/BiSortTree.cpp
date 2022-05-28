//【问题描述】给定的二叉树是否为二叉排序树
//
//【样例输入1】先序序列：10 5 4 - 1 - 1 - 1 30 - 1 - 1
//【样例输出1】是
//【样例输入2】先序序列：10 5 6 - 1 - 1 - 1 30 - 1 - 1
//【样例输出2】不是
//
//【样例输入3】先序序列：10 - 1 - 1
//【样例输出3】是
//
//【样例输入4】先序序列： - 1
//【样例输出4】是

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <assert.h>
#include  <stddef.h>
#define  TRUE  1
#define  FALSE  0
#define  OK  1
#define  ERROR  0
#define  INFEASIBLE  -1
#define  OVERFLOW  -2
#define  LIST_INIT_SIZE  100
#define  STACK_INIT_SIZE  100
typedef  int  Status;

typedef  struct  BiTNode {
    int        data;
    struct  BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

//输入先序序列，创建二叉树
void  CreateBiTree(BiTree& T)
{
    int  ch;
    scanf_s("%d", &ch);
    if (ch == -1)  T = NULL;
    else
    {
        T = (BiTNode*)malloc(sizeof(BiTNode));
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

void  IsBST(BiTree  T, BiTree& pre, int& isBST)
{
    if (T == NULL || (T->lchild == NULL && T->rchild == NULL))  return;
    int top = -1, datas[20], i = 0;    //栈顶数组标识
    BiTNode* S[20];     //树节点型数组栈
    S[++top] = T;   //根节点进栈
    while (top != -1)   
    {   
        while ((pre = S[top]) && pre)  S[++top] = pre->lchild;      //到左孩子底部
        //将NULL弹栈
        if (top == -1) return;
        top--;
        if (top != -1) {
            pre = S[top];       //取栈顶元素
            //弹栈
            if (top == -1)return;   
            top--;
            datas[i++] = pre->data;
            if (i > 1 && datas[i - 2] > datas[i - 1])
            {
                isBST = FALSE;
                return;
            }
            S[++top] = pre->rchild;
        }
    }
}


int  main()
{
    BiTree  T, pre = NULL;
    int  isBST = TRUE;
    //        printf("请输入先序序列创建二叉树：");

    CreateBiTree(T);

    IsBST(T, pre, isBST);
    if (isBST)
        printf("是");
    else
        printf("不是");

    printf("\n");
    return  1;
}
