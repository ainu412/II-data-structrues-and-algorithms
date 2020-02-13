#include <iostream>
#include <vld.h>
using namespace std;

#define MAX_SIZE 100

typedef struct _QNode {
	int data;
	int priority;
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
	if (!Q->length && !Q->front && !Q->rear)return false;
	if (MAX_SIZE == Q->length) {
		cerr << "Queue is full!" << endl;
		return true;
	}
	else return false;
}
//队尾插入新节点(在此函数内部分配新节点空间)
void lqEnter(LkQueue*& Q, int data, int priority) {
	if (!Q) return;

	if (isFull(Q)) {
		cout << "无法插入元素 " << data << ", 队列已满!" << endl; return;
	}

	QNode* qNode = new QNode; qNode->data = data;
	qNode->priority = priority; qNode->nxt = NULL;

	if (isEmpty(Q)) {//空队列
		Q->front = Q->rear = qNode;
	}
	else {
		Q->rear->nxt = qNode;
		Q->rear = qNode;	
	}
	Q->length++;
}
//出队,遍历找到优先级最高的出队,返回出队元素的数据至data
bool lqOut(LkQueue*& Q, int* data) {
	if (!Q)return false;
	if (isEmpty(Q))return false;

	//情况1:队头依次:三个元素,优先级2 3 1
	//首先遍历找到优先级最高的
	QNode* cur = NULL;
	QNode* super = NULL;//superlative-存有当前最高优先级QNode*的地址的上一位置
	cur = Q->front->nxt;
	if (!cur) {//只有队首一个元素.则front出列
		*data = Q->front->data + Q->front->priority * 10;
		delete Q->front;
		Q->length = 0;
		Q->front = Q->rear = NULL;
		return true;
	}
	super = Q->front;

	//从队第二个位置开始的super
	while (cur->nxt && super->nxt) {
		if (cur->nxt->priority > super->nxt->priority) {
			super = cur;
		}		
		cur = cur->nxt;
	}
	//1.super在队首
	if (Q->front->priority >= super->nxt->priority) {
		*data = Q->front->data + Q->front->priority * 10;
		super = Q->front;
		Q->front = Q->front->nxt;
		delete super;
		Q->length--;
		return true;
	}

	//2.super在队尾(下一元素不为空且不是队首)
	if (super->nxt == Q->rear) {
		*data = super->nxt->data + super->nxt->priority * 10;
		delete super->nxt;
		Q->rear = super;
		Q->rear->nxt = NULL;
		Q->length--;
		return true;
	}

	//3.super在队中
	*data = super->nxt->data + super->nxt->priority * 10;
	Q->length--;
	cur = super->nxt;
	super->nxt = super->nxt->nxt;
	delete cur;
	return true;
}
void lqPrint(LkQueue*& Q) {
	if (!Q || isEmpty(Q))return;

	QNode* p = Q->front;
	while (p) {
		cout << p->data << "[" << p->priority << "]" << " ";
		p = p->nxt;
	}cout << endl;
}
void getHead(LkQueue*& Q, int* data) {
	if (!Q || isEmpty(Q))return;

	*data = Q->front->data + Q->front->priority * 10;
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
int main() {
	LkQueue* q = NULL;
	lqInit(q);
	QNode* n = NULL;

	for (int i = 1; i <= 3; i++) {
		lqEnter(q, i, i);//优先级及存有数据1-10的队列
	}
	lqEnter(q, 4, 1);
	lqPrint(q);

	int* data = new int;
	if (lqOut(q, data))
		cout << "out data:" << *data % 10 
		<< "[" << *data / 10 << "]" << endl;
	lqPrint(q);

	lqClr(q);
	lqPrint(q);

	delete data;
	delete q;
	return 0;
}