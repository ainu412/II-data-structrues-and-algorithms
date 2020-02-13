#include <iostream>
#include <vld.h>
using namespace std;

#define MAX_SIZE 5

//ʹ������洢����
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

	if (MAX_SIZE == Q->rear) {
		cerr << "Queue is full!" << endl;
		return true;
	}

	else	return false;
}
bool isEmpty(SqQueue*& Q) {
	if (!Q)return false;

	if (Q->rear == Q->front) {
		cerr << "Queue is empty!" << endl;
		return true;
	}
	else 	return false;

}
void sqEnter(SqQueue*& Q, int data) {//ֱ�Ӵ��뿽��һ��,����ָ�������
	if (isFull(Q))return;

	Q->queue[Q->rear] = data;
	Q->rear++;
}
//���ӷ�ʽ1:ȫ��ǰ��һλ
bool sqDel1(SqQueue*& Q, int* data) {
	if (isEmpty(Q))return false;

	if (!data)return false;
	*data = Q->queue[Q->front];//�û�û���ǵ�����,ȡ�߶�������

	for (int i = Q->front + 1; i < Q->rear; i++) {
		Q->queue[i - 1] = Q->queue[i];
	}
	Q->rear--;
	return true;
}
//���ӷ�ʽ2:front��Ϊ1,��ӡʱ���ٴ�ӡ��һλ
bool sqDel2(SqQueue*& Q, int* data) {
	if (isEmpty(Q))return false;
	if (!data)return false;

	*data = Q->queue[Q->front];//�û�û���ǵ�����,ȡ�߶�������

	Q->front++;
	return true;
}


void sqPrint(SqQueue*& Q) {
	if (isEmpty(Q))return;

	for (int i = Q->front; i < Q->rear; i++) {
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
	sqEnter(q, 5);
	sqEnter(q, 6);
	sqEnter(q, 7);
	sqPrint(q);
	int* delData = new int;//�ǵ�Ϊ���ص�ָ������ڴ�!
	if (sqDel2(q, delData)) {
		cout << "deleted data:" << *delData << endl;
	}
	sqPrint(q);

	delete delData;
	delete q;
	return 0;
}