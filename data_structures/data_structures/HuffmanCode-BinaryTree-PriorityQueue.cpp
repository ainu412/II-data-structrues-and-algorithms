#include <iostream>
#include <vld.h>
using namespace std;

#define MAX_SIZE 100
typedef struct _BNode {
	char data;//���char�͵�����ӡʱǿ������ת������
	struct _QNode* parent;
	struct _QNode* lchild;
	struct _QNode* rchild;
}BNode;

typedef BNode DataType;
typedef struct _QNode {
	DataType data;
	int priority;//=���ִ���
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
//��β�����½ڵ�(�ڴ˺����ڲ������½ڵ�ռ�)
void lqEnter(LkQueue*& Q, char data, int priority) {
	if (!Q) return;

	if (isFull(Q)) {
		cout << "�޷�����Ԫ�� " << data << ", ��������!" << endl; return;
	}

	QNode* qNode = new QNode; qNode->data.data = data;
	qNode->priority = priority; qNode->nxt = NULL;
	qNode->data.lchild = qNode->data.rchild = qNode->data.parent = NULL;

	if (isEmpty(Q)) {//�ն���
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
		cout << "�޷�����Ԫ��, ��������!" << endl; return;
	}

	QNode* qNode = q;
	if (isEmpty(Q)) {//�ն���
		Q->front = Q->rear = qNode;
	}
	else {
		Q->rear->nxt = qNode;
		Q->rear = qNode;
	}
	Q->length++;
	qNode->nxt = NULL;
}
//����,�����ҵ����ȼ���͵ĳ���,���س���Ԫ�ص�������data//��Ϊͬһ���ȼ�,����ȳ�
bool lqOut(LkQueue*& Q, QNode*& data) {
	if (!Q)return false;
	if (isEmpty(Q))return false;

	//���1:��ͷ����:����Ԫ��,���ȼ�2 3 1
	//���ȱ����ҵ����ȼ���ߵ�
	QNode* cur = NULL;
	QNode* super = NULL;//superlative-���е�ǰ������ȼ�QNode*�ĵ�ַ����һλ��
	cur = Q->front->nxt;
	if (!cur) {//ֻ�ж���һ��Ԫ��.��front����
		data = Q->front;
		Q->length = 0;
		Q->front = Q->rear = NULL;
		return true;
	}
	super = Q->front;

	//�Ӷӵڶ���λ�ÿ�ʼ��super
	while (cur->nxt && super->nxt) {
		if (cur->nxt->priority <= super->nxt->priority) {
			super = cur;
		}
		cur = cur->nxt;
	}
	//1.super�ڶ���
	if (Q->front->priority <= super->nxt->priority) {
		data = Q->front;
		super = Q->front;
		Q->front = Q->front->nxt;
		Q->length--;
		return true;
	}

	//2.super�ڶ�β(��һԪ�ز�Ϊ���Ҳ��Ƕ���)
	if (super->nxt == Q->rear) {
		data = super->nxt;
		Q->rear = super;
		Q->rear->nxt = NULL;
		Q->length--;
		return true;
	}

	//3.super�ڶ���
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