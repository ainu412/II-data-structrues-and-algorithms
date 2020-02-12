#include <iostream>
#include <vld.h>
using namespace std;
/*
Joseph ����
�� 10 ��С���Ѱ����˳�� 1��2����������10 ˳ʱ�뷽��Χ��һȦ��
�� 1 �ſ�ʼ˳ʱ�뷽�� 1��2����������9 ������������ 9�ı��� �߳��У���Ȼ����һ����ȦΪ��� 9 �ߣ���
���һ����Ȧ�ߵı���Ƕ��٣��� 5 ����Ȧ�ߵı���Ƕ��٣�

nΪ���(1-����)

*/

typedef struct _LoopLinkNode {
	int data;//�����Լ��ı��,1-10
	struct _LoopLinkNode* nxt;
}LpLinkList, LpLinkNode;

void listInit(LpLinkList*& L) {
	L = new LpLinkList;
	if (!L) {
		cerr << "Failed to allocate space to loop link list!" << endl; return;
	}
	L->nxt = L;
	L->data = 0;
}

void listInsert_back(LpLinkList*& L, LpLinkNode*& N) {
	//�ҵ����һ��,������������һ��ΪL
	LpLinkList* p = L;
	while (p->nxt != L) {
		p = p->nxt;
	}
	p->nxt = N;
	N->nxt = L;
}

void listPrint(LpLinkList*& L) {

	if (!L || L->nxt==L || !L->nxt) {
		cerr << "Loop link list is empty!" << endl; return;
	}

	LpLinkList* p = L;
	while (p->nxt != L && p) {
		p = p->nxt;
		cout << p->data << "\t";
	}cout << endl;
}

//nΪ������,ͷ�ڵ㲻�ܱ���(��Ϊͷ��㲻�ܴ�����)
//timesΪ��times����Ȧ��
void Joseph(LpLinkList*& L, int interval) {
	int i = 0, j = 0;
	int times = 0, num;
	LpLinkList* p = L;
	LpLinkList* q;
	do {
		i += interval;
		while ((p->nxt)) //���ҵ� i ����㣬p ָ��ý�����һ���ڵ�
		{
			if (p->nxt != L) j++; //��ǰ+1
			if (j >= i) break;
			p = p->nxt;
		}

		times++;
		q = p->nxt; 
		num = q->data;

		p->nxt = q->nxt; 
		listPrint(L);
		delete q; 

	} while (L->nxt != L);//����Ϊ�գ���������
	//delete L;
	cout << "���һ����Ȧ�ı���ǣ�" << num << endl;
}
int main() {
	LpLinkList* l;
	//β�巨����Ԫ��
	LpLinkNode* n;
	listInit(l);

	for (int i = 1; i <= 10; i++) {
		n = new LpLinkNode;
		n->data = i;
		listInsert_back(l, n);
	}

	listPrint(l);

	//���Joseph����
	Joseph(l, 9);

	delete l;
	return 0;
}