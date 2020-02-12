#include <iostream>
#include <vld.h>
using namespace std;

typedef struct _LinkNode {
	int data;
	struct _LinkNode* nxt;
}LinkList, LinkNode;//头节点和其后的节点,因两名字指的都是 struct _LinkList类,故可互指互传

void listInit(LinkList*& linkList) {//记得是指针引用!!链表里面全部是指针!!因为不相邻!!只存地址的指针!!
	if (linkList) {
		cerr << "待初始化头结点不为空!" << endl; return;
	}

	linkList = new LinkList;
	if (!linkList) {
		cerr << "Failed to allocate space to link list!" << endl; return;
	}

	linkList->nxt = NULL;
}

void listInsert_front(LinkList*& linkList, LinkNode*& linkNode) {//插入已有初始化好的元素!!

	if (!linkList || !linkNode) {//确保为listInit和node分配空间后再插入!!
		cerr << "Link list or link node is empty!" << endl; return;
	}

	linkNode->nxt = linkList->nxt;
	linkList->nxt = linkNode;
}
void listInsert_back(LinkList*& linkList, LinkNode*& linkNode) {

	if (!linkList || !linkNode) {//确保为listInit和node分配空间后再插入!!
		cerr << "Link list or link node is empty!" << endl; return;
	}

	LinkList* p = linkList;//注意临时变量不要加引用,因为不改变本身值!!
	while (p->nxt) {//此处必须是nxt,不能是p,因为如果擅自改了p的地址,而前一个的nxt不改,就无法找到它!
		p = p->nxt;
	}

	p->nxt = linkNode;
	linkNode->nxt = NULL;
}
void listInsert(LinkList*& linkList, int pos, LinkNode*& linkNode) {

	if (!linkList || !linkNode) {//确保为listInit和node分配空间后再插入!!
		cerr << "Link list or link node is empty!" << endl; return;
	}

	if (pos <= 0) {
		cerr << "Input position must be more than 0!" << endl; return;
	}

	LinkList* p = linkList;
	for (int i = 0; i < pos - 1; i++) {
		p = p->nxt;
	}

	if (!p) {
		cerr << "Input position out of range!" << endl; return;
	}

	if (!p->nxt) {
		p->nxt = linkNode;
		linkNode->nxt = NULL;
	}
	else {
		linkNode->nxt = p->nxt;
		p->nxt = linkNode;
	}
}
void listPrint(LinkList*& linkList) {
	if (!linkList || !linkList->nxt) {
		cerr << "Link list is empty!" << endl; return;
	}

	LinkList* p = linkList->nxt;
	do
	{
		cout << p->data << "\t";
		p = p->nxt;
	} while (p); cout << endl;
}
bool getElemValue(LinkList*& linkList, int pos, int& e) {
	if (!linkList || !linkList->nxt) {
		cerr << "Link list is empty!" << endl; return false;
	}
	if (pos <= 0) {
		cerr << "Input position must be more than 0!" << endl; return false;
	}
	LinkList* p = linkList->nxt;
	int i = 1;
	for (; i < pos; i++) {
		p = p->nxt;
	}

	if (!p) {
		cerr << "Input position out of range!" << endl; return false;
	}

	e = p->data;
	return true;
}
bool getElemPos(LinkList*& linkList, int& pos, int e) {
	if (!linkList || !linkList->nxt) {
		cerr << "Link list is empty!" << endl; return false;
	}

	LinkList* p = linkList->nxt;
	int i = 1;

	while (p) {
		if (e == p->data) {
			pos = i;
			return true;
		}
		i++;
		p = p->nxt;
	}

	cerr << "Don't have element whose value = " << e << " !";
	return false;
}
void listDelPos(LinkList*& linkList, int pos) {
	if (!linkList || !linkList->nxt) {
		cerr << "Link list is empty!" << endl; return;
	}
	if (pos <= 0) {
		cerr << "Input position must be more than 0!" << endl; return;
	}

	LinkList* p = linkList;
	for (int i = 0; i < pos - 1; i++) {
		p = p->nxt;
	}
	LinkList* s = p->nxt;
	if (!s) {
		cerr << "Input position out of range!" << endl; return;
	}
	p->nxt = s->nxt;//前一个重写

	delete s;//记得删除自己!
}
void listDelVal(LinkList*& linkList, int value) {
	if (!linkList || !linkList->nxt) {
		cerr << "Link list is empty!" << endl; return;
	}

	LinkList* p = linkList;
	LinkList* s = p->nxt;

	while (s) {
		if (value == s->data) {
			p->nxt = s->nxt;
			delete s;//记得删除自己!
			return;
		}
		p = p->nxt;
		s = p->nxt;
	}

	cerr << "Don't have element whose value = " << value << " !";
	return;
}

void listDestroy(LinkList*& linklist) {
	if (!linklist) {
		cerr << "Link list is empty!" << endl; return;
	}

	LinkList* p = linklist;

	while (p) {
		linklist = linklist->nxt;
		delete p;
		p = linklist;
	}
}

int main() {
	LinkList* l = NULL;
	LinkNode* n = NULL;

	listInit(l);
	int m;

	////1.头部插入m个元素
	//cout << "Please input insert elements' number:";
	//cin >> m;
	//cout << "Please input " << m << " integer(s)[seperated by spaces/enter key]:";
	//int x;
	//while (m-- > 0) {
	//	cin >> x;
	//	n = new LinkNode;//必须每次都分配新的空间,因为链表是一次加一个,不像顺序表一开始就分够空间直接拷贝就行		
	//	n->data = x;//先把数据存入node,再把node插入
	//	listInsert_front(l, n);
	//}

	//2.尾部插入m个元素
	cout << "Please input insert elements' number:";
	cin >> m;
	cout << "Please input " << m << " integer(s)[seperated by spaces/enter key]:";
	int x;
	while (m-- > 0) {
		cin >> x;
		n = new LinkNode;//必须每次都分配新的空间,因为链表是一次加一个,不像顺序表一开始就分够空间直接拷贝就行		
		n->data = x;//先把数据存入node,再把node插入
		listInsert_back(l, n);
	}

	////3.在任意位置y插入元素x(包括尾部)
	//cout << "Please input one integer:";
	//cin >> x;
	//n = new LinkNode;//必须每次都分配新的空间,因为链表是一次加一个,不像顺序表一开始就分够空间直接拷贝就行		
	//n->data = x;//先把数据存入node,再把node插入

	//cout << "and the position you want to insert it:";
	//int y;
	//cin >> y;

	//listInsert(l, y, n);

	////4.查找第x个位置所存数据
	//cout << "Please input the position of the element:";
	//cin >> x;
	//int e;
	//if (getElemValue(l, x, e)) {
	//cout << "value=" << e << endl;
	//}

	////5.查找第一个数据为x的元素所在位置
	//cout << "Please input the data/value of the element:";
	//cin >> x;
	//if (getElemPos(l, m, x)) {
	//	cout << "pos=" << m << endl;
	//}

	////6.删除位置为m的元素
	//cout << "Please input the position of the element you want to delete:";
	//cin >> m;
	//listDelPos(l, m);

	////7.删除值为m的元素
	//cout << "Please input the data/value of the element you want to delete:";
	//cin >> m;
	//listDelVal(l, m);

	//8.打印
	listPrint(l);

	//9.销毁
	listDestroy(l);
	return 0;
}