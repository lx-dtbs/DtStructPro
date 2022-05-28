#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include "BiTree.h"
#include "Stack.h"
using namespace std;

//�������Ķ��������ʾ
typedef struct BiTNode {
    TElemType data;
    BiTNode* lchild, * rchild;	//���Һ���ָ��
}BiTNode, * BiTree;

//ջ�ı�ʾ
typedef struct
{
    int* base;
    int* top;
    int stacksize;
}SqStack;

int InitStack(SqStack &S)        //��ʼ��ջ
{
    S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S.base)exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

int Push(SqStack& S, SElemType e)       //��Ԫ����ջ
{
    if (S.top - S.base >= S.stacksize)
    {
        S.base = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!S.base)exit(OVERFLOW);
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}

int Pop(SqStack& S, SElemType& e)       //��Ԫ�س�ջ
{
    if (S.top == S.base)return ERROR;
    e = *--S.top;
    return OK;
}

bool StackEmpty(SqStack S) {                //�ж�ջ��
    if (S.top == S.base)return true;//Ϊ��
    else return false;//��Ϊ��
}

int GetTop(SqStack S, SElemType& e)     //���ջ��Ԫ��
{
    if (S.top == S.base) return ERROR;
    e = *(S.top - 1);
    return OK;
}

void InitBiTree(BiTree& T)      //����ն�����T
{ 
    T = NULL;
}
void DestroyBiTree(BiTree& T)   // ��ʼ������������T���ڡ�������������ٶ�����T
{ 
    if (T) // �ǿ���
    {
        if (T->lchild) // ������
            DestroyBiTree(T->lchild); // ������������
        if (T->rchild) // ���Һ���
            DestroyBiTree(T->rchild); // �����Һ�������
        free(T); // �ͷŸ����
        T = NULL; // ��ָ�븳0
    }
}
void PreOrderTraverse(BiTree T)
{ // ��ʼ������������T����
// �������������ݹ����T����ÿ�������ú���printfһ���ҽ�һ��
    if (T) // T����
    {
        printf("%d ", T->data); // �ȷ��ʸ����
        PreOrderTraverse(T->lchild); // ���������������
        PreOrderTraverse(T->rchild); // ����������������
    }
}

void InOrderTraverse(BiTree T)
{ // ��ʼ������������T����
// �������������ݹ����T����ÿ�������ú���printfһ���ҽ�һ��
    if (T)
    {
        InOrderTraverse(T->lchild); // ���������������
        printf("%d ",T->data); // �ٷ��ʸ����
        InOrderTraverse(T->rchild); // ����������������
    }
}

void CreateBiTree(BiTree& T)
{ // �㷨6.4���������������������н���ֵ(��Ϊ�ַ��ͻ����ͣ��������ж���)��
// ������������ʾ�Ķ�����T������NULL��ʾ��(��)����
    TElemType ch;
    scanf("%d", &ch);
    if (ch == NULL) // ��
        T = NULL;
    else
    {
        T = (BiTree)malloc(sizeof(BiTNode)); // ���ɸ����
        if (!T)
            exit(OVERFLOW);
        T->data = ch;
        CreateBiTree(T->lchild); // ����������
        CreateBiTree(T->rchild); // ����������
    }
}

TElemType BiTreeEmpty(BiTree T)
{ // ��ʼ������������T���ڡ������������TΪ�ն��������򷵻�TRUE������FALSE
    if (T)
        return FALSE;
    else
        return TRUE;
}
TElemType BiTreeDepth(BiTree T)
{ // ��ʼ������������T���ڡ��������������T�����
    int i, j;
    if (!T)
        return 0; // �������Ϊ0
    if (T->lchild)
        i = BiTreeDepth(T->lchild); // iΪ�����������
    else
        i = 0;
    if (T->rchild)
        j = BiTreeDepth(T->rchild); // jΪ�����������
    else
        j = 0;
    return i > j ? i + 1 : j + 1; // T�����Ϊ����������������еĴ���+1
}

TElemType Root(BiTree T)
{ // ��ʼ������������T���ڡ��������������T�ĸ�
    if (BiTreeEmpty(T))
        return NULL;
    else
        return T->data;
}
TElemType Value(BiTree p)
{ // ��ʼ������������T���ڣ�pָ��T��ĳ����㡣�������������p��ָ����ֵ
    return p->data;
}
void Assign(BiTree p, TElemType value)
{ // ��p��ָ��㸳ֵΪvalue
    p->data = value;
}

Status PrintData(BiTree T,int k)    //������д��ڵ���k��Ԫ��
{
    BiTree p=T;
    int p1,i=0;
    int datas[MAX_TREE_SIZE],ref=0;   //ref 0δ�ҵ���С��k����СԪ�� 1�ҵ�
    SqStack S;
    S.base = nullptr;
    S.top = nullptr;
    InitStack(S);
    Push(S,T->data);
    while(!StackEmpty(S)){
        while (GetTop(S, p1) && p&&p->lchild) {
            Push(S, p->lchild->data);
            p = p->lchild;
        }
        Pop(S,p1);    
        if(!StackEmpty(S)&&p&&p->rchild){
            Pop(S,p1); 
            Push(S,p->rchild->data);            

        }                
        if(p1>=k)ref=1;
        if(ref==1)datas[i++]=p1;
    }
    for(int j=0;j<i;j++)printf("%d",datas[i-j-1]);
}

int main(){
    BiTree T;
    InitBiTree(T);
    int n,k;
    cout << "���������Ľ�������";
    scanf("%d", &n);
    //����n���������������
    cout << "����ΪҶ�ӽ��������0 0��"<<endl;
    cout << "���������ĸ����(��������)��";
    CreateBiTree(T);
    cout << "��������Ľ��Ϊ��";
    PreOrderTraverse(T);    //�������
    cout << endl;
    cout << "��������Ľ��Ϊ��";
    InOrderTraverse(T);//�������
    cout << endl;
    cout << "������kֵ��";
    cin >> k;
    PrintData(T, k);
    return 0;
}
