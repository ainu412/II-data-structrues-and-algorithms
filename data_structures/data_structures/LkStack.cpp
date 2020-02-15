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
	Node* base;//指向第一个节点
	Node* top;//指向最后一个节点
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
	cout << "请输入元素个数：" << endl;
	cin >> m;
	cout << "请依次输入" << m << "个元素，依次入栈：";
	while (m--)
	{
		n = new Node;
		cin >> n->data; //输入元素
		stackPush(s, n);
	}

	cout << " 元 素 依 次 出 栈 ：" << endl;
	while (!isEmpty(s))//如果栈不空，则依次出栈
	{
		cout << getTop(s) << "\t";//输出栈顶元素
		stackPop(s); //栈顶元素出栈
	}
	cout << endl;
	delete s;

	return 0;
}