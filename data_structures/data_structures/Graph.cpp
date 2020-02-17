#include <iostream>
#include <queue>
#include <assert.h>
using namespace std;

bool* isVisited;//访问过顶点
typedef struct _EdgeNode {
	int adjNum;//邻接顶点值(所属顶点值)indexNum
	int weight;//权重(算法时再填入)-最短路径算法时:选择:和最小的
	struct _EdgeNode* nxt;
}EdgeNode;

typedef struct _VertexNode {
	char index;//顶点索引数据/符号
	EdgeNode* firstAdjVex;
}VertexNode;

typedef struct _AdjListGraph {//邻接列表图
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
	//遍历与每一顶点索引数据比较
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

	//创建顶点
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
		 cin >> G->vertexes[i].index;//自动跳过空格,一次只能读一个字母
		 G->vertexes[i].firstAdjVex = NULL;
	}

	char ver, adj;
	int verNum = -1, adjNum = -1, weight;
	EdgeNode* n;

	//添加边,插在头部节点的前面
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

int minWeight = 0x7FFFFFFF;//int类型最大整数:2的31次方-1
int curPath[100];
int minPath[100];
int minSteps;
int steps = 0;
void DFS(AdjListGraph*& G, int vertexIndex) {

	if (isVisited[vertexIndex])return;//若一节点已遍历过,则其下所有节点都已遍历过

	isVisited[vertexIndex] = true;//一开始就要设为true,防止互相循环访问
	cout << G->vertexes[vertexIndex].index << " ";//一开始就要打印,防止互相循环打印

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
			//curPath = new int;//可以每次扩一点内存吗?
			curPath[steps++] = n->adjNum;
			DFS(G, n->adjNum, end, n->weight + weights);//不能走回头点

			isVisited[n->adjNum] = false;//其他路线还可以走这个点
			curPath[--steps] = 0;
		}
		n = n->nxt;
	}
}void BFS(AdjListGraph*& G, int index) {
	queue<int> q;//将一顶点的所有邻接索引值存入队列,利用其先进先出

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

/*测试代码:
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