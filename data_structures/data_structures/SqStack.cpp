#include <iostream>
#include <vld.h>
using namespace std;
//指针减法:相隔元素个数

//初始化,出栈,入栈,获取栈顶元素,获取栈大小,销毁栈
#define MAX_SIZE 128
#define ElemType int
typedef struct _SqStack {
	ElemType* top;
	ElemType* base;
}SqStack;

void stackInit(SqStack& S) {
	S.base = new ElemType[MAX_SIZE];

	if (!S.base) {
		cerr << "Failed to allocate space to S.base" << endl; return;
	}

	S.top = S.base;//要把分配内存的那个的值赋给未分配的那一个!!
}
bool isEmpty(SqStack& S) {
	if (S.top == S.base) {
		cerr << "Stack is empty!" << endl;
		return true;
	}
	return false;
}
bool isFull(SqStack& S) {
	if (MAX_SIZE == S.top - S.base) {
		cerr << "Stack is full!" << endl;
		return true;
	}
	else return false;
}
void stackPush(SqStack& S, ElemType E) {//因本身不是指针,是其内元素为指针,故传递非指针引用即可
	if (isFull(S))return;

	*(S.top++) = E;
}
bool stackPop(SqStack& S, ElemType& E) {//因本身不是指针,是其内元素为指针,故传递非指针引用即可
	if (!S.base || isEmpty(S))return false;

	E = *(--S.top);
	return true;
}
void stackPrint(SqStack& S) {
	if (isEmpty(S))return;
	ElemType* p = S.top - 1;
	while (p != S.base - 1) {
		cout << *p-- << " ";
	}cout << endl;
}
ElemType getTop(SqStack& S) {
	if (S.top == S.base)return -1;

	return *(S.top - 1);
}
int GetSize(SqStack& S) {//返回栈中元素个数
	return (S.top - S.base);
}
void DestoryStack(SqStack& S) {//销毁栈
	if (S.base) {
		free(S.base);
	}
	S.base = S.top = NULL;
}
int main() {
	int n, x; SqStack S;
	stackInit(S);//初始化一个顺序栈 S 
	cout << "请输入元素个数 n：" << endl;
	cin >> n;
	cout << "请依次输入 n 个元素，依次入栈：" << endl;
	while (n--)
	{
		cin >> x; //输入元素
		stackPush(S, x);
	}
	stackPrint(S);

	cout << " 元 素 依 次 出 栈 ：" << endl;
	while (!isEmpty(S))//如果栈不空，则依次出栈
	{
		cout << getTop(S) << "\t";//输出栈顶元素
		stackPop(S, x); //栈顶元素出栈
	}
	cout << endl;
	stackPrint(S);

	DestoryStack(S);
	return 0;
}