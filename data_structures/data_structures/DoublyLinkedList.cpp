#include <iostream>
#include <vld.h>
using namespace std;

typedef struct _DbLinkedList {
	int data;
	struct _DbLinkedList* pre;
	struct _DbLinkedList* nxt;
}DbLinkedList, DbLinkedNode;

void listInit(DbLinkedList*& L) {
	L = new DbLinkedList;
	if (!L) {
		cerr << "Failed to allocate space to double linked list!" << endl; return;
	}
	L->nxt = NULL;
	L->pre = NULL;
}

void listInsert_front(DbLinkedList*& L, DbLinkedNode*& N) {
	if (!L || !N) {
		cerr << "List or node is NULL!" << endl; return;
	}

	if (!L->nxt) {
		L->nxt = N;
		N->pre = L;
		N->nxt = NULL;
	}
	else {
		L->nxt->pre = N;
		N->nxt = L->nxt;

		L->nxt = N;
		N->pre = L;

	}

}
void listInsert_back(DbLinkedList*& L, DbLinkedNode*& N) {
	if (!L || !N) {
		cerr << "List or node is NULL!" << endl; return;
	}
	DbLinkedList* last = L;
	while (last->nxt) {
		last = last->nxt;
	}
	last->nxt = N;
	N->pre = last;
	N->nxt = NULL;//记得置零
}
void listInsert(DbLinkedList*& L, int pos, DbLinkedNode*& N) {
	if (!L || !N) {
		cerr << "List or node is NULL!" << endl; return;
	}
	if (pos <= 0) {
		cerr << "Input position must be more than 0 !" << endl; return;
	}
	DbLinkedList* p = L;
	int i = 0;
	while (p->nxt) {
		i++;
		if (pos == i) {//p为i的前一元素
			N->nxt = p->nxt;
			p->nxt->pre = N;
			p->nxt = N;
			N->pre = p;
			return;
		}
		p = p->nxt;
	}
	cerr << "Input position out of range!" << endl;
}
void listPrint(DbLinkedList*& L) {
	if (!L || !L->nxt) {
		cerr << "List is empty!" << endl; return;
	}
	DbLinkedList* p = L;
	while (p->nxt) {
		p = p->nxt;
		cout << p->data << " ";
	}cout << endl;
	cout << "reverse output:" << endl;
	cout << p->data << " ";
	while (p->pre && p->pre != L) {
		p = p->pre;
		cout << p->data << " ";
	}cout << endl;
}
void listDel(DbLinkedList*& L, int pos) {
	if (!L || !L->nxt) {
		cerr << "List is empty!" << endl; return;
	}
	if (pos <= 0) {
		cerr << "Input position must be more than 0 !" << endl; return;
	}
	DbLinkedList* p = L;
	int i = 0;
	while (p->nxt) {
		i++;
		if (pos == i) {//p为该位置前一元素
			if (p->nxt->nxt) {
				p->nxt = p->nxt->nxt;
				p->nxt->pre = p;
				return;
			}
			else {
				p->nxt->pre = NULL;
				p->nxt = NULL;
				return;
			}
		}
		p = p->nxt;
	}
	cerr << "Input position out of range!" << endl;
}
void listDestroy(DbLinkedList*& L) {
	if (!L || !L->nxt) {
		cerr << "List is empty!" << endl; return;
	}
	DbLinkedList* p = L;
	while (L->nxt) {
		L = L->nxt;
		delete p;
		p = L;
	}
}
int main() {
	DbLinkedList* l;
	DbLinkedNode* n;
	listInit(l);
	int i, x;

	cout << "Please input the number of elements you want to input:";
	cin >> i;

	cout << "Please input numbers:";
	while (i-- > 0) {
		cin >> x;
		n = new DbLinkedNode;
		n->data = x;
		listInsert_back(l, n);
	}
	listDestroy(l);
	listPrint(l);
	delete l;
	return 0;
}