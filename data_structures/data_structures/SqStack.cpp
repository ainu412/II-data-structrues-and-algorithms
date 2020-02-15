#include <iostream>
#include <vld.h>
using namespace std;
//ָ�����:���Ԫ�ظ���

//��ʼ��,��ջ,��ջ,��ȡջ��Ԫ��,��ȡջ��С,����ջ
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

	S.top = S.base;//Ҫ�ѷ����ڴ���Ǹ���ֵ����δ�������һ��!!
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
void stackPush(SqStack& S, ElemType E) {//������ָ��,������Ԫ��Ϊָ��,�ʴ��ݷ�ָ�����ü���
	if (isFull(S))return;

	*(S.top++) = E;
}
bool stackPop(SqStack& S, ElemType& E) {//������ָ��,������Ԫ��Ϊָ��,�ʴ��ݷ�ָ�����ü���
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
int GetSize(SqStack& S) {//����ջ��Ԫ�ظ���
	return (S.top - S.base);
}
void DestoryStack(SqStack& S) {//����ջ
	if (S.base) {
		free(S.base);
	}
	S.base = S.top = NULL;
}
int main() {
	int n, x; SqStack S;
	stackInit(S);//��ʼ��һ��˳��ջ S 
	cout << "������Ԫ�ظ��� n��" << endl;
	cin >> n;
	cout << "���������� n ��Ԫ�أ�������ջ��" << endl;
	while (n--)
	{
		cin >> x; //����Ԫ��
		stackPush(S, x);
	}
	stackPrint(S);

	cout << " Ԫ �� �� �� �� ջ ��" << endl;
	while (!isEmpty(S))//���ջ���գ������γ�ջ
	{
		cout << getTop(S) << "\t";//���ջ��Ԫ��
		stackPop(S, x); //ջ��Ԫ�س�ջ
	}
	cout << endl;
	stackPrint(S);

	DestoryStack(S);
	return 0;
}