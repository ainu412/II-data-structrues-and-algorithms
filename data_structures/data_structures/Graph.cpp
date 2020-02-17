#include <iostream>
#include <queue>
#include <assert.h>
using namespace std;

bool* isVisited;//���ʹ�����
typedef struct _EdgeNode {
	int adjNum;//�ڽӶ���ֵ(��������ֵ)indexNum
	int weight;//Ȩ��(�㷨ʱ������)-���·���㷨ʱ:ѡ��:����С��
	struct _EdgeNode* nxt;
}EdgeNode;

typedef struct _VertexNode {
	char index;//������������/����
	EdgeNode* firstAdjVex;
}VertexNode;

typedef struct _AdjListGraph {//�ڽ��б�ͼ
	int vertexNum;
	int edgeNum;
	VertexNode* vertexes;
}AdjListGraph;

void algInit(AdjListGraph*& G) {
	if (G)return;

	G = new AdjListGraph;
	assert(G);

	G->edgeNum = G->vertexNum = 0;
}

void algLocation(AdjListGraph*& G, char index, int& indexNum) {
	//������ÿһ�����������ݱȽ�
	for (int i = 0; i < G->vertexNum; i++) {
		if (index == G->vertexes[i].index) {
			indexNum = i;
			return;
		}
	}
	indexNum = -1;
}
void algCreate(AdjListGraph*& G) {
	assert(G);

	//��������
	int vertexes, edges;
	cout << "Please input the number of vertexes and number of edges(>0):";
	cin >> vertexes >> edges;
	if (vertexes <= 0 || edges <= 0) {
		cerr << "Number of vertexes and number of vertexes edges must be more than 0!"; return;
	}

	G->vertexes = new VertexNode[vertexes];
	G->vertexNum = vertexes;
	G->edgeNum = edges;
	isVisited = new bool[vertexes];
	memset(isVisited, 0, sizeof(bool) * vertexes);

	cout << "Please input index characters of " << vertexes << " vertexes:";
	for (int i = 0; i < vertexes; i++) {
		 cin >> G->vertexes[i].index;//�Զ������ո�,һ��ֻ�ܶ�һ����ĸ
		 G->vertexes[i].firstAdjVex = NULL;
	}

	char ver, adj;
	int verNum = -1, adjNum = -1, weight;
	EdgeNode* n;

	//��ӱ�,����ͷ���ڵ��ǰ��
	while (edges--) {
		cout << "Please input vertex value, its adjacent value, and their weight:";//value/character
		cin >> ver >> adj >> weight;
		assert(weight > 0);
		algLocation(G, ver, verNum);
		algLocation(G, adj, adjNum);
		if (-1 == verNum || -1 == adjNum) {
			cerr << "Vertex value or adjacent value not found!" << endl;
		}
		else {
			n = new EdgeNode;
			n->adjNum = adjNum;
			n->nxt = G->vertexes[verNum].firstAdjVex;
			G->vertexes[verNum].firstAdjVex = n;
			n->weight = weight;
		}
	}
}

int minWeight = 0x7FFFFFFF;//int�����������:2��31�η�-1
int curPath[100];
int minPath[100];
int minSteps;
int steps = 0;
void DFS(AdjListGraph*& G, int vertexIndex) {

	if (isVisited[vertexIndex])return;//��һ�ڵ��ѱ�����,���������нڵ㶼�ѱ�����

	isVisited[vertexIndex] = true;//һ��ʼ��Ҫ��Ϊtrue,��ֹ����ѭ������
	cout << G->vertexes[vertexIndex].index << " ";//һ��ʼ��Ҫ��ӡ,��ֹ����ѭ����ӡ

	EdgeNode* n = G->vertexes[vertexIndex].firstAdjVex;
	while (n) {
		if (!isVisited[n->adjNum]) {
			DFS(G, n->adjNum);
		}
		n = n->nxt;
	}
}
void algDFS(AdjListGraph*& G) {
	for (int i = 0; i < G->vertexNum; i++) {
		if (!isVisited[i]) {
			DFS(G, i);
		}
	}
}
int times = 0;
void DFS(AdjListGraph*& G, int vertexIndex, int end, int weights) {

	if (vertexIndex == end) {
		if (weights < minWeight) {
			minWeight = weights;

			assert(steps > 0);
			memcpy_s(minPath, steps * sizeof(int), curPath, steps * sizeof(int));

			minSteps = steps;
		}
		cout << "Route " << ++times << ". ";
		for (int i = 0; i < steps; i++) {
			cout << G->vertexes[curPath[i]].index << " ";
		}cout << weights << "min" << endl;
		return;

	}
	isVisited[vertexIndex] = true;

	EdgeNode* n = G->vertexes[vertexIndex].firstAdjVex;
	while (n) {
		if (!isVisited[n->adjNum]) {
			isVisited[n->adjNum] = true;
			//curPath = new int;//����ÿ����һ���ڴ���?
			curPath[steps++] = n->adjNum;
			DFS(G, n->adjNum, end, n->weight + weights);//�����߻�ͷ��

			isVisited[n->adjNum] = false;//����·�߻������������
			curPath[--steps] = 0;
		}
		n = n->nxt;
	}
}void BFS(AdjListGraph*& G, int index) {
	queue<int> q;//��һ����������ڽ�����ֵ�������,�������Ƚ��ȳ�

	isVisited[index] = true;
	cout << G->vertexes[index].index << " ";

	EdgeNode* p = G->vertexes[index].firstAdjVex;
	int cur = -1;
	q.push(index);

	while (!q.empty()) {
		cur = q.front();
		if (!isVisited[cur]) {
			cout << G->vertexes[cur].index << " ";
			isVisited[cur] = true;
		}
		q.pop();

		p = G->vertexes[cur].firstAdjVex;
		while (p) {
			q.push(p->adjNum);
			p = p->nxt;
		}
	}
}
void algBFS(AdjListGraph*& G) {

	for (int i = 0; i < G->vertexNum; i++) {
		if (!isVisited[i]) {
			BFS(G, i);
		}
	}
}
int main() {
	AdjListGraph* g = NULL;
	algInit(g);

	algCreate(g);

	DFS(g, 0, 3, 0);
	cout << "Shortest route:";
	for (int i = 0; i < minSteps; i++) {
		cout << g->vertexes[minPath[i]].index << " ";
	}cout << minWeight << "min" << endl;

	return 0;
}

/*���Դ���:
6 7
A B C D E F
F A 5
A B 2
B D 9
A C 3
C D 5
A E 2
E D 4

*/