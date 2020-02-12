#include <iostream>
#include <vld.h>
#include "star.h"
using namespace std;

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

void listInsert_back(LinkList*& linkList, LinkNode* linkNode) {//

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


void listDel(LinkList*& linkList, int pos) {
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
	s->nxt = NULL;//自己也要记得清零哦!

	delete s;//
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