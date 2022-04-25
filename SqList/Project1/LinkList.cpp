#include <stdio.h>
#include <stdlib.h>
#include <vector>
using std::vector; //vector矢量在std名空间，需要配套使用
typedef struct LNode {
	int data;
	struct LNode* next;
}LNode,*LinkList;

int CreateList_L(LinkList& L, int n)	//头插法输入元素
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	printf("Please input the elements:");
	for (int i = n; i > 0; --i)
	{
		LNode* p = (LinkList)malloc(sizeof(LNode));
		scanf("%d",&p->data);
		p->next = L->next; L->next = p;
	}
	return 0;
}

int MergeList_L(LinkList& Pa, LinkList& Pb, LinkList& Pc)	//两正序单链表逆序排列
{
	LinkList pa = Pa->next,pb=Pb->next,pc;
	Pc= pc = Pa;
	while (pa && pb)
	{
		if (pa->data <= pb->data) {
			pc->next = pa; 
			pc = pa;
			pa = pa->next;
		}
		else {
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	free(Pb);
	LNode* pre = NULL;    //通过三指针法对Pc链表进行逆序排列(升序到降序)，该为前驱节点
	LNode* cur = NULL;    //当前结点
	LNode* next = NULL;    //后继节点
	//把链表首节点变成尾节点
	cur = Pc->next;
	next = cur->next;
	cur->next = NULL;
	pre = cur;
	cur = next;
	//使当前遍历到的结点cur指向其前驱节点
	while (cur->next != NULL)
	{
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	//链表最后一个结点指向倒数第二个结点
	cur->next = pre;
	//链表的头结点指向原来链表的尾节点
	Pc->next = cur;
	return 0;
}
int DeleteList(LinkList& L, int mink, int maxk)		//删除大于等于mink，小于等于maxk的元素
{
	LinkList p = L;	//记录删除第一个结点的前一结点位置
	LinkList q = L;		//记录删除最后一个结点的位置
	LinkList r = NULL;			//做删除元素的移动指针
	LinkList del = NULL;		//做删除元素的记录指针(用于free)
	LinkList point = L;			//用于排除mink和maxk区间无元素情况的结点
	vector<int> nums;
	int i = 0;
	//一个元素都不删除的情况
	while(point->next!=NULL)
	{
		point = point->next;
	}
	if (L->next->data > maxk || point->data < mink)return NULL;
	//元素有删除的情况
	while (p->data < mink && p->next&&p->next->data < mink)
	{
		p = p->next;
	}
	while (q->data <= maxk && q->next&&q->next->data <= maxk)
	{
		q = q->next;
	}
	r = p->next;
	p->next = q->next;
	while (r->data >= mink && r->data <= q->data)
	{
		del = r;
		nums.push_back(r->data);
		if(r->next)r = r->next;
		free(del);
	}
	//打印删除结点
	printf("Delete elements are:");
	for (int j=0;j<nums.size(); j++)
		printf("%d ", nums[j]);
	printf("\n");
	return 0;
}

int PrintList(LinkList L)	//打印链表结点
{
	LNode* p = L->next;
	printf("The LinkList now is:");
	if (!p)return NULL;
	while (p->next!= NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("%d", p->data);
	return 0;
}
int main() {
	LinkList La,Lb,Lc;
	int m,n,mink,maxk;
	printf("Please input the length of LinkList:");
	scanf("%d", &m);
	CreateList_L(La,m);
	printf("Please input the length of LinkList:");
	scanf("%d",&n);
	CreateList_L(Lb, n);
	MergeList_L(La, Lb, Lc);
	PrintList(Lc);
	//PrintList(La);
	//printf("\nPlease input the mink and maxk:");
	//scanf("%d %d", &mink, &maxk);
	//DeleteList(La, mink, maxk);
	//PrintList(La);
	return 0;
}