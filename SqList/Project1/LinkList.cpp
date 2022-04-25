#include <stdio.h>
#include <stdlib.h>
#include <vector>
using std::vector; //vectorʸ����std���ռ䣬��Ҫ����ʹ��
typedef struct LNode {
	int data;
	struct LNode* next;
}LNode,*LinkList;

int CreateList_L(LinkList& L, int n)	//ͷ�巨����Ԫ��
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

int MergeList_L(LinkList& Pa, LinkList& Pb, LinkList& Pc)	//������������������
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
	LNode* pre = NULL;    //ͨ����ָ�뷨��Pc���������������(���򵽽���)����Ϊǰ���ڵ�
	LNode* cur = NULL;    //��ǰ���
	LNode* next = NULL;    //��̽ڵ�
	//�������׽ڵ���β�ڵ�
	cur = Pc->next;
	next = cur->next;
	cur->next = NULL;
	pre = cur;
	cur = next;
	//ʹ��ǰ�������Ľ��curָ����ǰ���ڵ�
	while (cur->next != NULL)
	{
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	//�������һ�����ָ�����ڶ������
	cur->next = pre;
	//�����ͷ���ָ��ԭ�������β�ڵ�
	Pc->next = cur;
	return 0;
}
int DeleteList(LinkList& L, int mink, int maxk)		//ɾ�����ڵ���mink��С�ڵ���maxk��Ԫ��
{
	LinkList p = L;	//��¼ɾ����һ������ǰһ���λ��
	LinkList q = L;		//��¼ɾ�����һ������λ��
	LinkList r = NULL;			//��ɾ��Ԫ�ص��ƶ�ָ��
	LinkList del = NULL;		//��ɾ��Ԫ�صļ�¼ָ��(����free)
	LinkList point = L;			//�����ų�mink��maxk������Ԫ������Ľ��
	vector<int> nums;
	int i = 0;
	//һ��Ԫ�ض���ɾ�������
	while(point->next!=NULL)
	{
		point = point->next;
	}
	if (L->next->data > maxk || point->data < mink)return NULL;
	//Ԫ����ɾ�������
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
	//��ӡɾ�����
	printf("Delete elements are:");
	for (int j=0;j<nums.size(); j++)
		printf("%d ", nums[j]);
	printf("\n");
	return 0;
}

int PrintList(LinkList L)	//��ӡ������
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