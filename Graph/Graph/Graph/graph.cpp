#include <iostream>
#include <cstdbool>
#define MAX_VERTEX_NUM 20
#define FALSE 0
#define TRUE 1
using namespace std;
//使用枚举类型定义图的四种基本类型 
typedef enum {

	//（有向图=0，有向网=1，无向图=2，无向网=3）
	DG, DN, UDG, UDN
} kind;
//----图的邻接表表示----
typedef struct ArcNode {		//表结点
	int adjvex;								//该弧所指向的顶点的位置
	struct ArcNode* nextarc;		//指向下一条弧的指针
	int* into;								//该弧相关信息的指针
}Arcnode;
typedef struct VNode {			//顶点结点
	int data;								//顶点信息
	ArcNode* firstarc;					//指向第一条依附该顶点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct {						//图的定义
	AdjList vertices;
	int vexnum, arcnum;				//图的当前顶点数和弧数
	int kind;								//图的种类标志 
}ALGraph;

//顶点定位函数，在图G中查找顶点v的位置
int LocateVex(ALGraph G, int v) {
	int i;
	for (i = 0; i < G.vexnum && G.vertices[i].data != v; i++);
	if (i == G.vexnum) return -1; //不存在该顶点
	else return i;
}

// 创建邻接表
void createALGraph(ALGraph& G) {
	printf("请输入邻接表的顶点数和边的数目：\n");
	cin >> G.vexnum >> G.arcnum;
	printf("请输入邻接表的顶点：\n");
	for (int i = 0; i < G.vexnum; i++) {
		cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL; //初始化邻接点
	}
	printf("请以vi vj的形式输入给边:\n");
	for (int i = 0; i < G.vexnum; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		int l1 = LocateVex(G, v1);
		int l2 = LocateVex(G, v2);
		// 使用头插法添加邻接点
		ArcNode* ptr = new ArcNode;
		ptr->adjvex = l2;
		ptr->nextarc = G.vertices[l1].firstarc;
		G.vertices[l1].firstarc = ptr;
		/*若是无向图，则还需要对称建立边
		ArcNode* temp;
		temp->adjvex = l1;
		temp->nextarc = G.vertex[l2].firstarc;
		G.vertex[l2].firstarc = temp->nextarc;
		*/
	}
}

//打印图
void print(const ALGraph g)
{
	ArcNode* p;
	for (int k = 0; k < g.vexnum; k++)
	{
		cout << "顶点" << k << ": ";
		for (p = g.vertices[k].firstarc; p; p = p->nextarc)
			cout << p->adjvex << " ";
		if (p == NULL)
			cout << endl;
	}
}

//求顶点v在图G中的第一个邻接点
int FirstAdjVex(ALGraph G, int v) {
	int index = LocateVex(G, v);
	if (index == -1) {
		printf("图中不存在顶点%c\n", v); 
		return -1;
	}
	else if (G.vertices[index].firstarc == NULL) {
		printf("%c没有邻接点\n", v); 
		return -1;
	}
	else return G.vertices[index].firstarc->adjvex;
}

//求顶点v在图G中相对于邻接点w的下一个邻接点
int NextAdjVex(ALGraph G, int v, int w) {
	int index = LocateVex(G, v);
	int index2 = LocateVex(G, w);
	if (index == -1) return -1;
	else {
		ArcNode* ptr = G.vertices[index].firstarc;
		while (ptr && ptr->adjvex != index2) ptr = ptr->nextarc;
		if (!(ptr->nextarc)) {
			//printf("%c是%c的最后一个邻接点", v, G.vertex[index].data);
			return -1;
		}
		else return ptr->nextarc->adjvex;
	}
}

//DFS深度遍历
void DFS(ALGraph G, int v, int* visited) {
	// 先访问本结点
	visited[v] = 1;
	cout << G.vertices[v].data << " ";
	ArcNode* w = new ArcNode;
	for (w = G.vertices[v].firstarc; w != NULL; w = w->nextarc) {
		if (!visited[w->adjvex]) DFS(G, w->adjvex, visited);
	}
	delete w;
	/* 也可以用先前定义的函数，但是操作复杂
	int w1;
	for (w1 = FirstAdjVex(G, G.vertex[v].data); w1 >= 0; w1 = NextAdjVex(G, G.vertex[v].data, G.vertex[w1].data)) {
	if (!visited[w1]) DFS(G, w1, visited);
	}
	*/
}
void DFSTraverse(ALGraph G) {
	int* visited = new int[G.vexnum];
	for (int i = 0; i < G.vexnum; i++) visited[i] = 0;
	// 递归进行深度优先遍历
	for (int i = 0; i < G.vexnum; i++) {
		if (!visited[i]) DFS(G, i, visited);
	}
	delete[] visited;
}


int main() {
	ALGraph G;
	createALGraph(G);
	print(G);
	DFSTraverse(G);
	return 0;
}