#include <iostream>
using namespace std;

#define MAX_SIZE 1000

typedef struct _QNode {
	int id;
	void (*handle)();//指向任务函数地址的指针
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
	Q->length = 0;
	Q->front = Q->rear = NULL;
}
bool isEmpty(LkQueue*& Q) {
	if (!Q)return false;
	if (!Q->front) {
		cout << "Queue is empty!" << endl;
		return true;
	}
	return false;
}
bool isFull(LkQueue*& Q) {
	if (!Q || isEmpty(Q))return false;
	if (MAX_SIZE == Q->length) {
		cout << "Queue is full!" << endl;
		return true;
	}
	return false;
}
//分配线程执行的任务节点
QNode* threadTaskAlloc() {
	QNode* task = (QNode * )calloc(1, sizeof(QNode));//也可用malloc(sizeof(QNode))
	if (!task) {
		cerr << "Failed to malloc to task!" << endl; return NULL;
	}
	return task;
}
bool lqEnter(LkQueue*& Q, QNode*& N) {
	if (!Q)return false;
	if (isFull(Q)) {
		cout << "id=" << N->id << "can't enter queue!" << endl; return false;
	}
	if (isEmpty(Q)) {
		Q->front = N;
		Q->rear = N;
		Q->length = 1;
		N->nxt = NULL;//记得!!
		return true;
	}

	Q->rear->nxt = N;
	Q->rear = N;
	Q->length++;
	N->nxt = NULL;
	return true;
}
QNode* lqPop(LkQueue*& Q) {//返回出队的原头节点
	if (!Q || isEmpty(Q))return NULL;

	QNode* p = Q->front;
	if (!Q->front->nxt) {
		Q->front = Q->rear = NULL;
		Q->length = 0;
		return p;
	}

	Q->front = Q->front->nxt;
	Q->length--;
	return p;
}
int getLength(LkQueue*& Q) {
	if (!Q)return -1;
	return Q->length;
}
void lqPrint(LkQueue*& Q) {
	if (!Q || isEmpty(Q))return;

	QNode* p = Q->front;

	cout << "id:";
	while (p) {
		cout << p->id << " ";
		p = p->nxt;
	}cout << endl;
}
void task1() {
	cout << "I'm studying happily!" << endl;
}
void task2() {
	cout << "I'm working joyfully!" << endl;
}
int main() {
	LkQueue* q = NULL;
	lqInit(q);

	QNode* task = NULL;

	task = threadTaskAlloc();
	task->id = 1;
	task->handle = &task1;
	lqEnter(q, task);

	task = threadTaskAlloc();
	task->id = 2;
	task->handle = &task2;
	lqEnter(q, task);

	while (task = lqPop(q)) {//执行出队的头结点
		cout << "On task " << task->id << " :";
		task->handle();
	}


	cout << "get length:" << getLength(q) << endl;
	lqPrint(q);
	return 0;
}