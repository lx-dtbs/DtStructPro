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
typedef  enum { DG, DN, AG, AN }  GraphKind;//有向图、有向网、无向图、无向网
typedef  struct  ArcNode {
    int        adjvex;                                        //该弧头的位置
    struct  ArcNode* nextarc;        //下一条出弧（弧尾相同的下一条弧）
    int                info;                                //附加信息(权值)
}ArcNode;        //弧结点

typedef  char  VertexType;
typedef  struct  VNode {
    VertexType  data;                        //顶点信息
    ArcNode* firstarc;        //第一条出弧
}VNode, AdjList[MAX_VERTEX_NUM];        //邻接表头指针向量

typedef  struct {
    AdjList  vertices;                //邻接表头指针向量
    int  vexnum, arcnum;                //顶点数目和弧的数目
    GraphKind  kind;                        //图的种类
}ALGraph;

//返回顶点u在图中的位置,未找到返回-1
int  LocateVex(ALGraph  G, VertexType  u)
{
    int  i;
    for (i = 0; i < G.vexnum; i++)
        if (G.vertices[i].data == u)  return  i;
    return  -1;
}

//创建有向图
void  CreateDG(ALGraph& G)
{
    int  i, j, k, info = 0;
    char  c;
    VertexType  v1, v2;
    ArcNode* p;

    //        printf("\n下面分步输入创建有向图的信息：");  G.kind  =  DG;
    //        printf("\n1.请输入图的顶点个数：");          
    scanf("%d", &G.vexnum);
    //            printf("\n2.请输入图的弧的个数：");          
    scanf("%d", &G.arcnum);
    //        printf("\n3.请连续输入%d个顶点（字符型）：",G.vexnum);
    scanf("%c", &c);        //滤掉换行字符
    for (k = 0; k < G.vexnum; k++)        //邻接表头指针向量初始化
    {
        scanf("%c", &G.vertices[k].data);
        G.vertices[k].firstarc = NULL;
    }

    for (k = 0; k < G.arcnum; k++)                //建立弧结点<v,w,info>
    {        //printf("\n建立弧%d,请输入弧的信息,格式为v,w,info：",k+1);  
        scanf("%c", &c);        //滤掉换行字符
        scanf("%c  %c  %d", &v1, &v2, &info);
        i = LocateVex(G, v1);  j = LocateVex(G, v2);        //确定v1,v2在图中的位置
        if (i == -1 || j == -1)
        {
            printf("\n输入弧信息非法，程序退出！");  break;
        }

        p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->info = info;
        p->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p;
    }
}


//按邻接表的形式输出有向图
void  PrintDG(ALGraph  G)
{
    ArcNode* p;
    printf("\n有向图G的邻接表形式：");
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

//用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及其带权路径长度D[v]
//若P[v][w]为真，则w是从v0到v的最短路径上的顶点，
//也即P[v]存放的是v->v0最短路径上的顶点，D[v]存放的是该最短路径的长度
//final[v]为真，表明已经求得v0->v的最短路径
typedef  enum { True, False }  Boolean;
typedef  Boolean  PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef  int  ShortPathTable[MAX_VERTEX_NUM];
#define  INFINITY  1000        //无穷大

//返回邻接表中顶点v到顶点w的权值
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
    //        {        printf("\n顶点%c到顶点%c的最短路径是：权值  =  %d,顶点序列  =  ",u,G.vertices[v].data,D[v]);
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

    //        printf("\n请输入顶点v0：");
    scanf("%c", &v0);
    scanf("%c", &v0);

    PathMatrix  P;
    ShortPathTable  D;

    ShortestPath_DIJ(G, v0, P, D);
    PrintShortPath(G, v0, P, D);

    printf("\n");
    return  OK;
}