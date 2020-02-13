#include <iostream>
#include <vld.h>
using namespace std;

#define MAX_SIZE 10000
typedef struct _QNode {
	int data;
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
int isEmpty(LkQueue*& Q) {
	if (!Q) {
		cerr << "Queue is Null!" << endl;
		return -1;
	}else if (!Q->length || !Q->front || !Q->rear) {
		cerr << "Queue is empty!" << endl;
		return 1;
	}

	else return 0;
}
bool isFull(LkQueue*& Q) {
	if (!isEmpty(Q) &&
		MAX_SIZE == Q->length) {
		cerr << "Queue is full!" << endl;
		return true;
	}
	else return false;
}
void lqEnter(LkQueue*& Q, QNode*& N) {
	if (!Q || isFull(Q))return;


	if (1 == isEmpty(Q)) {
		Q->front = N;
		Q->rear = N;
		Q->length++;
		N->nxt = NULL;
		return;
	}

	Q->rear->nxt = N;
	Q->length++;
	Q->rear = N;
	N->nxt = NULL;
	return;
}
bool getHead(LkQueue*& Q, int* delData) {
	if (isEmpty(Q))return false;

	QNode* delNode = Q->front;
	*delData = delNode->data;

	return true;
}
bool lqDel(LkQueue*& Q, int* delData) {
	if (isEmpty(Q))return false;

	QNode* delNode = Q->front;
	*delData = delNode->data;


	if (!delNode->nxt) {
		Q->front = Q->rear = NULL;
		Q->length = 0;

	}
	else {
		Q->front = delNode->nxt;
		Q->length--;
	}

	delete delNode;
	return true;
}
void lqPrint(LkQueue*& Q) {
	if (isEmpty(Q))return;

	QNode* p = Q->front;

	while (p) {
		cout << p->data << " ";
		p = p->nxt;
	}cout << endl;
}
void lqClear(LkQueue*& Q) {//如果最后要打印的话,无法判断未为其分配内存而为空,故不能销毁,只能置空
	if (!Q)return;

	if (1 == isEmpty(Q))return;

	QNode* p = Q->front;
	while (p) {
		p = p->nxt;
		delete Q->front;
		Q->front = p;
	}
	Q->front = Q->rear = NULL;
	Q->length = 0;
}
int getLength(LkQueue*& Q) {//如果最后要打印的话,无法判断未为其分配内存而为空,故不能销毁,只能置空
	if (!Q)return -1;

	return Q->length;
}
int main() {
	LkQueue* q = NULL;
	lqInit(q);
	QNode* n;

	int m;
	cout << "Please input number of elements you want to input:";
	cin >> m;
	cout << "Please input value/data of " << m << " elements:";

	while (m-- > 0) {
		n = new QNode;
		cin >> n->data;
		lqEnter(q, n);
	}
	cout << "Before delete:";
	lqPrint(q);

	int* delData = new int;//别忘记分配内存
	if (lqDel(q, delData)) {
		cout << "deleted data:" << *delData << endl;
	}
	cout << "After delete:";
	lqPrint(q);
	if (getHead(q, delData)) {
		cout << "get head:" << *delData 
			 << ",get length:" << getLength(q) << endl;
	}

	lqClear(q);
	lqPrint(q);

	delete delData;
	delete q;
	return 0;
}