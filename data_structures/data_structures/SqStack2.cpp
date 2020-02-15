#include <iostream>
using namespace std;
//��ʼ��,��ջ,��ջ,��ȡջ��Ԫ��
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
void stackPush(SqStack2& S, ElemType E) {//������ָ��,������Ԫ��Ϊָ��,�ʴ��ݷ�ָ�����ü���
	if (isFull(S))return;	

	*(S.base + S.top++) = E;
}
bool stackPop(SqStack2& S) {//������ָ��,������Ԫ��Ϊָ��,�ʴ��ݷ�ָ�����ü���
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
	stackInit(S);//��ʼ��һ��˳��ջ S 
	cout << "������Ԫ�ظ��� n��" << endl;
	cin >> n;
	cout << "���������� n ��Ԫ�أ�������ջ��" << endl;
	while (n--)
	{
		cin >> x; //����Ԫ��
		stackPush(S, x);
	}

	cout << " Ԫ �� �� �� �� ջ ��" << endl;
	while (!isEmpty(S))//���ջ���գ������γ�ջ
	{
		cout << getTop(S) << "\t";//���ջ��Ԫ��
		stackPop(S); //ջ��Ԫ�س�ջ
	}
	cout << endl;

	return 0;
}