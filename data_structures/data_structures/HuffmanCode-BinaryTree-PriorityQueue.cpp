#include <iostream>
#include <vld.h>
using namespace std;

#define MAX_SIZE 100
typedef struct _BNode {
	char data;//存的char型的最后打印时强制类型转换即可
	struct _QNode* parent;
	struct _QNode* lchild;
	struct _QNode* rchild;
}BNode;

typedef BNode DataType;
typedef struct _QNode {
	DataType data;
	int priority;//=出现次数
	struct _QNode* nxt;
}QNode;

typedef struct _LkQueue {
	int length;
	QNode* front;
	QNode* rear;
}LkQueue;

void lqInit(LkQueue*& Q) {
	if (Q)return;

	Q = new LkQueue;
	if (!Q) {
		cerr << "Failed to allocate space to linked queue!" << endl;
		return;
	}

	Q->length = 0;
	Q->front = Q->rear = NULL;
}
bool isEmpty(LkQueue*& Q) {
	if (!Q)return false;
	if (!Q->length && !Q->front && !Q->rear) {
		cerr << "Queue is empty!" << endl;
		return true;
	}
	else return false;
}
bool isFull(LkQueue*& Q) {
	if (!Q)return false;
	//if (!Q->length && !Q->front && !Q->rear)return false;
	if (MAX_SIZE == Q->length) {
		cerr << "Queue is full!" << endl;
		return true;
	}
	else return false;
}
//队尾插入新节点(在此函数内部分配新节点空间)
void lqEnter(LkQueue*& Q, char data, int priority) {
	if (!Q) return;

	if (isFull(Q)) {
		cout << "无法插入元素 " << data << ", 队列已满!" << endl; return;
	}

	QNode* qNode = new QNode; qNode->data.data = data;
	qNode->priority = priority; qNode->nxt = NULL;
	qNode->data.lchild = qNode->data.rchild = qNode->data.parent = NULL;

	if (isEmpty(Q)) {//空队列
		Q->front = Q->rear = qNode;
	}
	else {
		Q->rear->nxt = qNode;
		Q->rear = qNode;
	}
	Q->length++;
}
void lqEnter(LkQueue*& Q, QNode*& q) {
	if (!Q) return;

	if (isFull(Q)) {
		cout << "无法插入元素, 队列已满!" << endl; return;
	}

	QNode* qNode = q;
	if (isEmpty(Q)) {//空队列
		Q->front = Q->rear = qNode;
	}
	else {
		Q->rear->nxt = qNode;
		Q->rear = qNode;
	}
	Q->length++;
	qNode->nxt = NULL;
}
//出队,遍历找到优先级最低的出队,返回出队元素的数据至data//改为同一优先级,后进先出
bool lqOut(LkQueue*& Q, QNode*& data) {
	if (!Q)return false;
	if (isEmpty(Q))return false;

	//情况1:队头依次:三个元素,优先级2 3 1
	//首先遍历找到优先级最高的
	QNode* cur = NULL;
	QNode* super = NULL;//superlative-存有当前最高优先级QNode*的地址的上一位置
	cur = Q->front->nxt;
	if (!cur) {//只有队首一个元素.则front出列
		data = Q->front;
		Q->length = 0;
		Q->front = Q->rear = NULL;
		return true;
	}
	super = Q->front;

	//从队第二个位置开始的super
	while (cur->nxt && super->nxt) {
		if (cur->nxt->priority <= super->nxt->priority) {
			super = cur;
		}
		cur = cur->nxt;
	}
	//1.super在队首
	if (Q->front->priority <= super->nxt->priority) {
		data = Q->front;
		super = Q->front;
		Q->front = Q->front->nxt;
		Q->length--;
		return true;
	}

	//2.super在队尾(下一元素不为空且不是队首)
	if (super->nxt == Q->rear) {
		data = super->nxt;
		Q->rear = super;
		Q->rear->nxt = NULL;
		Q->length--;
		return true;
	}

	//3.super在队中
	data = super->nxt;
	Q->length--;
	cur = super->nxt;
	super->nxt = super->nxt->nxt;
	return true;
}
void lqPrint(LkQueue*& Q) {
	if (!Q || isEmpty(Q))return;

	QNode* p = Q->front;
	while (p) {
		cout << p->data.data << "[" << p->priority << "]" << " ";
		p = p->nxt;
	}cout << endl;
}
void getHead(LkQueue*& Q, int* data) {
	if (!Q || isEmpty(Q))return;

	*data = Q->front->data.data * 10 + Q->front->priority;
}
int getLength(LkQueue* Q) {
	if (!Q) return -1;

	return Q->length;
}
void lqClr(LkQueue*& Q) {
	if (!Q || isEmpty(Q))return;

	QNode* p = Q->front;
	while (Q->front->nxt) {
		p = Q->front;
		Q->front = Q->front->nxt;
		delete p;
	}
	delete Q->front;

	Q->front = Q->rear = NULL;
	Q->length = 0;
}
void preorderRec(QNode* p) {
	if (!p)return;

	cout << p->data.data << "[" << p->priority << "]" << " ";

	preorderRec(p->data.lchild);
	preorderRec(p->data.rchild);
	delete p;
}
void HuffmanTree() {
	LkQueue* q = NULL;
	lqInit(q);
	char y;
	int x, m;

	cout << "Please input the number of elements you want to input:";
	cin >> m;
	for (int i = 1; i <= m; i++) {
		cout << "Please input the character of " << i << "element and its priority:";
		cin >> y >> x;
		lqEnter(q, y, x);
	}

	QNode *n1,  *n2,* p;
	while (!isEmpty(q)) {
		lqOut(q, n1);
		lqOut(q, n2);
		p = new QNode;
		p->priority = n1->priority + n2->priority;
		p->data.data = ' ';
		p->data.lchild = n1;
		p->data.rchild = n2;
		n1->data.parent = p;
		n2->data.parent = p;
		if (isEmpty(q)) { 
			preorderRec(p);
			delete q;
			return; }
		lqEnter(q, p);
	}
}

int main() {

	HuffmanTree();

	return 0;
}