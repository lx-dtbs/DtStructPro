#include <iostream>
#include <cstdbool>
#define MAX_VERTEX_NUM 20
#define FALSE 0
#define TRUE 1
using namespace std;
//ʹ��ö�����Ͷ���ͼ�����ֻ������� 
typedef enum {

	//������ͼ=0��������=1������ͼ=2��������=3��
	DG, DN, UDG, UDN
} kind;
//----ͼ���ڽӱ��ʾ----
typedef struct ArcNode {		//����
	int adjvex;								//�û���ָ��Ķ����λ��
	struct ArcNode* nextarc;		//ָ����һ������ָ��
	int* into;								//�û������Ϣ��ָ��
}Arcnode;
typedef struct VNode {			//������
	int data;								//������Ϣ
	ArcNode* firstarc;					//ָ���һ�������ö���Ļ���ָ��
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct {						//ͼ�Ķ���
	AdjList vertices;
	int vexnum, arcnum;				//ͼ�ĵ�ǰ�������ͻ���
	int kind;								//ͼ�������־ 
}ALGraph;

//���㶨λ��������ͼG�в��Ҷ���v��λ��
int LocateVex(ALGraph G, int v) {
	int i;
	for (i = 0; i < G.vexnum && G.vertices[i].data != v; i++);
	if (i == G.vexnum) return -1; //�����ڸö���
	else return i;
}

// �����ڽӱ�
void createALGraph(ALGraph& G) {
	printf("�������ڽӱ�Ķ������ͱߵ���Ŀ��\n");
	cin >> G.vexnum >> G.arcnum;
	printf("�������ڽӱ�Ķ��㣺\n");
	for (int i = 0; i < G.vexnum; i++) {
		cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL; //��ʼ���ڽӵ�
	}
	printf("����vi vj����ʽ�������:\n");
	for (int i = 0; i < G.vexnum; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		int l1 = LocateVex(G, v1);
		int l2 = LocateVex(G, v2);
		// ʹ��ͷ�巨����ڽӵ�
		ArcNode* ptr = new ArcNode;
		ptr->adjvex = l2;
		ptr->nextarc = G.vertices[l1].firstarc;
		G.vertices[l1].firstarc = ptr;
		/*��������ͼ������Ҫ�Գƽ�����
		ArcNode* temp;
		temp->adjvex = l1;
		temp->nextarc = G.vertex[l2].firstarc;
		G.vertex[l2].firstarc = temp->nextarc;
		*/
	}
}

//��ӡͼ
void print(const ALGraph g)
{
	ArcNode* p;
	for (int k = 0; k < g.vexnum; k++)
	{
		cout << "����" << k << ": ";
		for (p = g.vertices[k].firstarc; p; p = p->nextarc)
			cout << p->adjvex << " ";
		if (p == NULL)
			cout << endl;
	}
}

//�󶥵�v��ͼG�еĵ�һ���ڽӵ�
int FirstAdjVex(ALGraph G, int v) {
	int index = LocateVex(G, v);
	if (index == -1) {
		printf("ͼ�в����ڶ���%c\n", v); 
		return -1;
	}
	else if (G.vertices[index].firstarc == NULL) {
		printf("%cû���ڽӵ�\n", v); 
		return -1;
	}
	else return G.vertices[index].firstarc->adjvex;
}

//�󶥵�v��ͼG��������ڽӵ�w����һ���ڽӵ�
int NextAdjVex(ALGraph G, int v, int w) {
	int index = LocateVex(G, v);
	int index2 = LocateVex(G, w);
	if (index == -1) return -1;
	else {
		ArcNode* ptr = G.vertices[index].firstarc;
		while (ptr && ptr->adjvex != index2) ptr = ptr->nextarc;
		if (!(ptr->nextarc)) {
			//printf("%c��%c�����һ���ڽӵ�", v, G.vertex[index].data);
			return -1;
		}
		else return ptr->nextarc->adjvex;
	}
}

//DFS��ȱ���
void DFS(ALGraph G, int v, int* visited) {
	// �ȷ��ʱ����
	visited[v] = 1;
	cout << G.vertices[v].data << " ";
	ArcNode* w = new ArcNode;
	for (w = G.vertices[v].firstarc; w != NULL; w = w->nextarc) {
		if (!visited[w->adjvex]) DFS(G, w->adjvex, visited);
	}
	delete w;
	/* Ҳ��������ǰ����ĺ��������ǲ�������
	int w1;
	for (w1 = FirstAdjVex(G, G.vertex[v].data); w1 >= 0; w1 = NextAdjVex(G, G.vertex[v].data, G.vertex[w1].data)) {
	if (!visited[w1]) DFS(G, w1, visited);
	}
	*/
}
void DFSTraverse(ALGraph G) {
	int* visited = new int[G.vexnum];
	for (int i = 0; i < G.vexnum; i++) visited[i] = 0;
	// �ݹ����������ȱ���
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