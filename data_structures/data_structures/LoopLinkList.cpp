#include <iostream>
#include <vld.h>
using namespace std;
/*
Joseph 问题
有 10 个小朋友按编号顺序 1，2，。。。，10 顺时针方向围成一圈。
从 1 号开始顺时针方向 1，2，。。。，9 报数，凡报数 9的倍数 者出列（显然，第一个出圈为编号 9 者）。
最后一个出圈者的编号是多少？第 5 个出圈者的编号是多少？

n为编号(1-无穷)

*/

typedef struct _LoopLinkNode {
	int data;//存有自己的编号,1-10
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
	//找到最后一节,特征是它的下一节为L
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

//n为报的数,头节点不能报数(因为头结点不能存数据)
//times为第times个出圈者
void Joseph(LpLinkList*& L, int interval) {
	int i = 0, j = 0;
	int times = 0, num;
	LpLinkList* p = L;
	LpLinkList* q;
	do {
		i += interval;
		while ((p->nxt)) //查找第 i 个结点，p 指向该结点的上一个节点
		{
			if (p->nxt != L) j++; //提前+1
			if (j >= i) break;
			p = p->nxt;
		}

		times++;
		q = p->nxt; 
		num = q->data;

		p->nxt = q->nxt; 
		listPrint(L);
		delete q; 

	} while (L->nxt != L);//链表不为空，继续报数
	//delete L;
	cout << "最后一个出圈的编号是：" << num << endl;
}
int main() {
	LpLinkList* l;
	//尾插法插入元素
	LpLinkNode* n;
	listInit(l);

	for (int i = 1; i <= 10; i++) {
		n = new LpLinkNode;
		n->data = i;
		listInsert_back(l, n);
	}

	listPrint(l);

	//解决Joseph问题
	Joseph(l, 9);

	delete l;
	return 0;
}