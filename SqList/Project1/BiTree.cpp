#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include "BiTree.h"
#include "Stack.h"
using namespace std;

//二叉树的二叉链表表示
typedef struct BiTNode {
    TElemType data;
    BiTNode* lchild, * rchild;	//左右孩子指针
}BiTNode, * BiTree;

//栈的表示
typedef struct
{
    int* base;
    int* top;
    int stacksize;
}SqStack;

int InitStack(SqStack &S)        //初始化栈
{
    S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S.base)exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

int Push(SqStack& S, SElemType e)       //将元素入栈
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

int Pop(SqStack& S, SElemType& e)       //将元素出栈
{
    if (S.top == S.base)return ERROR;
    e = *--S.top;
    return OK;
}

bool StackEmpty(SqStack S) {                //判断栈空
    if (S.top == S.base)return true;//为空
    else return false;//不为空
}

int GetTop(SqStack S, SElemType& e)     //获得栈顶元素
{
    if (S.top == S.base) return ERROR;
    e = *(S.top - 1);
    return OK;
}

void InitBiTree(BiTree& T)      //构造空二叉树T
{ 
    T = NULL;
}
void DestroyBiTree(BiTree& T)   // 初始条件：二叉树T存在。操作结果：销毁二叉树T
{ 
    if (T) // 非空树
    {
        if (T->lchild) // 有左孩子
            DestroyBiTree(T->lchild); // 销毁左孩子子树
        if (T->rchild) // 有右孩子
            DestroyBiTree(T->rchild); // 销毁右孩子子树
        free(T); // 释放根结点
        T = NULL; // 空指针赋0
    }
}
void PreOrderTraverse(BiTree T)
{ // 初始条件：二叉树T存在
// 操作结果：先序递归遍历T，对每个结点调用函数printf一次且仅一次
    if (T) // T不空
    {
        printf("%d ", T->data); // 先访问根结点
        PreOrderTraverse(T->lchild); // 再先序遍历左子树
        PreOrderTraverse(T->rchild); // 最后先序遍历右子树
    }
}

void InOrderTraverse(BiTree T)
{ // 初始条件：二叉树T存在
// 操作结果：中序递归遍历T，对每个结点调用函数printf一次且仅一次
    if (T)
    {
        InOrderTraverse(T->lchild); // 先中序遍历左子树
        printf("%d ",T->data); // 再访问根结点
        InOrderTraverse(T->rchild); // 最后中序遍历右子树
    }
}

void CreateBiTree(BiTree& T)
{ // 算法6.4：按先序次序输入二叉树中结点的值(可为字符型或整型，在主程中定义)，
// 构造二叉链表表示的二叉树T。变量NULL表示空(子)树。
    TElemType ch;
    scanf("%d", &ch);
    if (ch == NULL) // 空
        T = NULL;
    else
    {
        T = (BiTree)malloc(sizeof(BiTNode)); // 生成根结点
        if (!T)
            exit(OVERFLOW);
        T->data = ch;
        CreateBiTree(T->lchild); // 构造左子树
        CreateBiTree(T->rchild); // 构造右子树
    }
}

TElemType BiTreeEmpty(BiTree T)
{ // 初始条件：二叉树T存在。操作结果：若T为空二叉树，则返回TRUE；否则FALSE
    if (T)
        return FALSE;
    else
        return TRUE;
}
TElemType BiTreeDepth(BiTree T)
{ // 初始条件：二叉树T存在。操作结果：返回T的深度
    int i, j;
    if (!T)
        return 0; // 空树深度为0
    if (T->lchild)
        i = BiTreeDepth(T->lchild); // i为左子树的深度
    else
        i = 0;
    if (T->rchild)
        j = BiTreeDepth(T->rchild); // j为右子树的深度
    else
        j = 0;
    return i > j ? i + 1 : j + 1; // T的深度为其左右子树的深度中的大者+1
}

TElemType Root(BiTree T)
{ // 初始条件：二叉树T存在。操作结果：返回T的根
    if (BiTreeEmpty(T))
        return NULL;
    else
        return T->data;
}
TElemType Value(BiTree p)
{ // 初始条件：二叉树T存在，p指向T中某个结点。操作结果：返回p所指结点的值
    return p->data;
}
void Assign(BiTree p, TElemType value)
{ // 给p所指结点赋值为value
    p->data = value;
}

Status PrintData(BiTree T,int k)    //输出树中大于等于k的元素
{
    BiTree p=T;
    int p1,i=0;
    int datas[MAX_TREE_SIZE],ref=0;   //ref 0未找到不小于k的最小元素 1找到
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
    cout << "请输入树的结点个数：";
    scanf("%d", &n);
    //输入n个数并创建这个树
    cout << "（若为叶子结点请输入0 0）"<<endl;
    cout << "请输入树的各结点(先序输入)：";
    CreateBiTree(T);
    cout << "先序遍历的结果为：";
    PreOrderTraverse(T);    //先序遍历
    cout << endl;
    cout << "中序遍历的结果为：";
    InOrderTraverse(T);//中序遍历
    cout << endl;
    cout << "请输入k值：";
    cin >> k;
    PrintData(T, k);
    return 0;
}
