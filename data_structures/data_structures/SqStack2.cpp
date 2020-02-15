#include <iostream>
using namespace std;
//初始化,出栈,入栈,获取栈顶元素
#define MAX_SIZE 128
#define ElemType int

typedef struct _SqStack2 {
	int top;
	ElemType* base;
}SqStack2;

void stackInit(SqStack2& S) {
	S.base = new ElemType[MAX_SIZE];
	if (!S.base) {
		cerr << "Failed to allocate space to S.base" << endl; return;
	}

	S.top = 0;
}
bool isEmpty(SqStack2& S) {

	if (!S.top) {
		cerr << "Stack is empty!" << endl;
		return true;
	}
	else return false;
}
bool isFull(SqStack2& S) {

	if (MAX_SIZE == S.top) {
		cerr << "Stack is full!" << endl;
		return true;
	}
	else return false;
}
void stackPush(SqStack2& S, ElemType E) {//因本身不是指针,是其内元素为指针,故传递非指针引用即可
	if (isFull(S))return;	

	*(S.base + S.top++) = E;
}
bool stackPop(SqStack2& S) {//因本身不是指针,是其内元素为指针,故传递非指针引用即可
	if (isEmpty(S))return false;

	S.top--;
	return true;
}

int getTop(SqStack2& S) {
	if (!S.top)return -1;

	return *(S.base + S.top - 1);
}
int main() {
	int n; 
	ElemType x;
	SqStack2 S;
	stackInit(S);//初始化一个顺序栈 S 
	cout << "请输入元素个数 n：" << endl;
	cin >> n;
	cout << "请依次输入 n 个元素，依次入栈：" << endl;
	while (n--)
	{
		cin >> x; //输入元素
		stackPush(S, x);
	}

	cout << " 元 素 依 次 出 栈 ：" << endl;
	while (!isEmpty(S))//如果栈不空，则依次出栈
	{
		cout << getTop(S) << "\t";//输出栈顶元素
		stackPop(S); //栈顶元素出栈
	}
	cout << endl;

	return 0;
}