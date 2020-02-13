#include <iostream>
#include <vld.h>
using namespace std;

#define MAX_SIZE 5

//使用数组存储队列
typedef struct _SqQueue {
	int queue[MAX_SIZE];
	int front;
	int rear;
}SqQueue;

void sqInit(SqQueue*& Q) {//sequence queue initialize
	if (!Q)return;

	Q->front = Q->rear = 0;
}

bool isFull(SqQueue*& Q) {
	if (!Q)return false;

	if (Q->front == Q->rear + 1) {
		cerr << "Queue is full!" << endl;
		return true;
	}

	else return false;
}
bool isEmpty(SqQueue*& Q) {
	if (!Q)return false;

	if (Q->rear == Q->front) {
		cerr << "Queue is empty!" << endl;
		return true;
	}
	else return false;
}
void sqEnter(SqQueue*& Q, int data) {//直接存入拷贝一份,不用指针或引用
	if (isFull(Q))return;

	Q->queue[Q->rear] = data;
	Q->rear = (Q->rear + 1) % MAX_SIZE;
}

//出队方式:front变为1,打印时不再打印第一位
bool sqDel(SqQueue*& Q, int* data) {
	if (isEmpty(Q))return false;
	if (!data)return false;

	*data = Q->queue[Q->front];//趁还没覆盖掉队首,取走队首数据

	Q->front = (Q->front + 1) % MAX_SIZE;
	return true;
}

void sqPrint(SqQueue*& Q) {
	if (isEmpty(Q))return;

	for (int i = Q->front; i != Q->rear; i = (i + 1) % MAX_SIZE) {
		cout << Q->queue[i] << " ";
	}cout << endl;
}

int main() {
	SqQueue* q;
	q = new SqQueue;
	sqInit(q);
	sqEnter(q, 1);
	sqEnter(q, 2);
	sqEnter(q, 3);
	sqEnter(q, 4);
	cout << "enter 4:";sqPrint(q);

	int* delData = new int;
	for (int i = 0; i < 3; i++) {
		sqDel(q, delData);
	} cout << "delete 3:"; sqPrint(q);

	sqEnter(q, 5);
	sqEnter(q, 6);
	sqEnter(q, 7);
	cout << "reEnter 3:"; sqPrint(q);
	//if (sqDel(q, delData)) {
	//	cout << "deleted data:" << *delData << endl;
	//}
	//sqPrint(q);

	delete delData;
	delete q;
	return 0;
}