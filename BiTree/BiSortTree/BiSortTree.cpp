//�����������������Ķ������Ƿ�Ϊ����������
//
//����������1���������У�10 5 4 - 1 - 1 - 1 30 - 1 - 1
//���������1����
//����������2���������У�10 5 6 - 1 - 1 - 1 30 - 1 - 1
//���������2������
//
//����������3���������У�10 - 1 - 1
//���������3����
//
//����������4���������У� - 1
//���������4����

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

//�����������У�����������
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
    int top = -1, datas[20], i = 0;    //ջ�������ʶ
    BiTNode* S[20];     //���ڵ�������ջ
    S[++top] = T;   //���ڵ��ջ
    while (top != -1)   
    {   
        while ((pre = S[top]) && pre)  S[++top] = pre->lchild;      //�����ӵײ�
        //��NULL��ջ
        if (top == -1) return;
        top--;
        if (top != -1) {
            pre = S[top];       //ȡջ��Ԫ��
            //��ջ
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
    //        printf("�������������д�����������");

    CreateBiTree(T);

    IsBST(T, pre, isBST);
    if (isBST)
        printf("��");
    else
        printf("����");

    printf("\n");
    return  1;
}
