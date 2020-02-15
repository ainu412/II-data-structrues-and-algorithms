#include <iostream>
#include <vld.h>
using namespace std;
#define MAX_SIZE 1000
#define ElemType int
typedef struct _Node {
	ElemType data;
	struct _Node* nxt;
}Node;
typedef struct _LkStack {
	Node* base;//ָ���һ���ڵ�
	Node* top;//ָ�����һ���ڵ�
}LkStack;

void stackInit(LkStack*& S) {
	if (S)return;

	S = new LkStack;
	if (!S) {
		cerr << "Failed to allocate space to stack!" << endl; return;
	}

	S->base = S->top = NULL;
}
bool isEmpty(LkStack*& S) {
	if (!S)return false;

	if (S->base == NULL) {
		cerr << "Stack is empty!" << endl;
		return true;
	}
	else return false;
}
bool isFull(LkStack*& S) {
	if (!S)return false;

	if (MAX_SIZE == S->top - S->base) {
		cerr << "Stack is full!" << endl;
		return true;
	}
	else return false;
}
void stackPush(LkStack*& S, Node*& N) {
	if (!S || !N || isFull(S))return;

	if (isEmpty(S)) {
		S->base = S->top = N;
		return;
	}

	S->top->nxt = N;
	S->top = N;
	N->nxt = NULL;
}
void stackPop(LkStack*& S) {
	if (!S || isEmpty(S))return;

	Node* p = S->base;
	if (!p->nxt) {
		delete p;
		S->base = S->top = NULL;
		return;
	}
	while (p->nxt->nxt) {
		p = p->nxt;
	}
	delete p->nxt;

	p->nxt = NULL;
	S->top = p;
}
ElemType getTop(LkStack*& S) {
	if (isEmpty(S))return -1;

	return S->top->data;
}
int main() {
	LkStack* s = NULL;
	stackInit(s);

	int m;
	Node* n;
	cout << "������Ԫ�ظ�����" << endl;
	cin >> m;
	cout << "����������" << m << "��Ԫ�أ�������ջ��";
	while (m--)
	{
		n = new Node;
		cin >> n->data; //����Ԫ��
		stackPush(s, n);
	}

	cout << " Ԫ �� �� �� �� ջ ��" << endl;
	while (!isEmpty(s))//���ջ���գ������γ�ջ
	{
		cout << getTop(s) << "\t";//���ջ��Ԫ��
		stackPop(s); //ջ��Ԫ�س�ջ
	}
	cout << endl;
	delete s;

	return 0;
}