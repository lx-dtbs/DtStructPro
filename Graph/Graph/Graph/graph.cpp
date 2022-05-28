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

#define  MAX_VERTEX_NUM  20
typedef  enum { DG, DN, AG, AN }  GraphKind;//����ͼ��������������ͼ��������
typedef  struct  ArcNode {
    int        adjvex;                                        //�û�ͷ��λ��
    struct  ArcNode* nextarc;        //��һ����������β��ͬ����һ������
    int                info;                                //������Ϣ(Ȩֵ)
}ArcNode;        //�����

typedef  char  VertexType;
typedef  struct  VNode {
    VertexType  data;                        //������Ϣ
    ArcNode* firstarc;        //��һ������
}VNode, AdjList[MAX_VERTEX_NUM];        //�ڽӱ�ͷָ������

typedef  struct {
    AdjList  vertices;                //�ڽӱ�ͷָ������
    int  vexnum, arcnum;                //������Ŀ�ͻ�����Ŀ
    GraphKind  kind;                        //ͼ������
}ALGraph;

//���ض���u��ͼ�е�λ��,δ�ҵ�����-1
int  LocateVex(ALGraph  G, VertexType  u)
{
    int  i;
    for (i = 0; i < G.vexnum; i++)
        if (G.vertices[i].data == u)  return  i;
    return  -1;
}

//��������ͼ
void  CreateDG(ALGraph& G)
{
    int  i, j, k, info = 0;
    char  c;
    VertexType  v1, v2;
    ArcNode* p;

    //        printf("\n����ֲ����봴������ͼ����Ϣ��");  G.kind  =  DG;
    //        printf("\n1.������ͼ�Ķ��������");          
    scanf("%d", &G.vexnum);
    //            printf("\n2.������ͼ�Ļ��ĸ�����");          
    scanf("%d", &G.arcnum);
    //        printf("\n3.����������%d�����㣨�ַ��ͣ���",G.vexnum);
    scanf("%c", &c);        //�˵������ַ�
    for (k = 0; k < G.vexnum; k++)        //�ڽӱ�ͷָ��������ʼ��
    {
        scanf("%c", &G.vertices[k].data);
        G.vertices[k].firstarc = NULL;
    }

    for (k = 0; k < G.arcnum; k++)                //���������<v,w,info>
    {        //printf("\n������%d,�����뻡����Ϣ,��ʽΪv,w,info��",k+1);  
        scanf("%c", &c);        //�˵������ַ�
        scanf("%c  %c  %d", &v1, &v2, &info);
        i = LocateVex(G, v1);  j = LocateVex(G, v2);        //ȷ��v1,v2��ͼ�е�λ��
        if (i == -1 || j == -1)
        {
            printf("\n���뻡��Ϣ�Ƿ��������˳���");  break;
        }

        p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->info = info;
        p->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p;
    }
}


//���ڽӱ����ʽ�������ͼ
void  PrintDG(ALGraph  G)
{
    ArcNode* p;
    printf("\n����ͼG���ڽӱ���ʽ��");
    for (int i = 0; i < G.vexnum; i++)
    {
        printf("\n  %c", G.vertices[i].data);
        if (G.vertices[i].firstarc)
        {
            printf("-->");
            for (p = G.vertices[i].firstarc; p; p = p->nextarc)
            {
                printf("%c  %d", G.vertices[p->adjvex].data, p->info);
                if (p->nextarc)  printf("-->");
            }
        }
    }
    printf("\n");
}

//��Dijkstra�㷨��������G��v0���㵽���ඥ��v�����·��P[v]�����Ȩ·������D[v]
//��P[v][w]Ϊ�棬��w�Ǵ�v0��v�����·���ϵĶ��㣬
//Ҳ��P[v]��ŵ���v->v0���·���ϵĶ��㣬D[v]��ŵ��Ǹ����·���ĳ���
//final[v]Ϊ�棬�����Ѿ����v0->v�����·��
typedef  enum { True, False }  Boolean;
typedef  Boolean  PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef  int  ShortPathTable[MAX_VERTEX_NUM];
#define  INFINITY  1000        //�����

//�����ڽӱ��ж���v������w��Ȩֵ
int  GetInfo(ALGraph  G, int  v, int  w)
{
    ArcNode* p;

    p = G.vertices[v].firstarc;
    while (p)
    {
        if (p->adjvex == w)        return  p->info;
        p = p->nextarc;
    }
    return  INFINITY;
}

void  ShortestPath_DIJ(ALGraph  G, VertexType  u, PathMatrix& P, ShortPathTable& D)
{
    Boolean  final[MAX_VERTEX_NUM];
}

void  PrintShortPath(ALGraph  G, VertexType  u, PathMatrix  P, ShortPathTable  D)
{
    //        for(int  v  =  0;  v  <  G.vexnum;  v++)
    //        {        printf("\n����%c������%c�����·���ǣ�Ȩֵ  =  %d,��������  =  ",u,G.vertices[v].data,D[v]);
    //                for(int  w  =  0  ;  w  <  G.vexnum;  w++)
    //                        if(P[v][w]  ==  True)  printf("%c",G.vertices[w].data);
    //        }
    for (int v = 1; v < G.vexnum; v++)
        printf("%d\n", D[v]);
}
int  main()
{
    VertexType  v0;
    ALGraph  G;
    CreateDG(G);
    //          PrintDG(G);  

    //        printf("\n�����붥��v0��");
    scanf("%c", &v0);
    scanf("%c", &v0);

    PathMatrix  P;
    ShortPathTable  D;

    ShortestPath_DIJ(G, v0, P, D);
    PrintShortPath(G, v0, P, D);

    printf("\n");
    return  OK;
}