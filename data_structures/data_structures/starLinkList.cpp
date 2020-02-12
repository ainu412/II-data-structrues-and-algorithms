#include <iostream>
#include <vld.h>
#include "star.h"
using namespace std;

void listInit(LinkList*& linkList) {//�ǵ���ָ������!!��������ȫ����ָ��!!��Ϊ������!!ֻ���ַ��ָ��!!
	if (linkList) {
		cerr << "����ʼ��ͷ��㲻Ϊ��!" << endl; return;
	}

	linkList = new LinkList;
	if (!linkList) {
		cerr << "Failed to allocate space to link list!" << endl; return;
	}

	linkList->nxt = NULL;
}

void listInsert_back(LinkList*& linkList, LinkNode* linkNode) {//

	if (!linkList || !linkNode) {//ȷ��ΪlistInit��node����ռ���ٲ���!!
		cerr << "Link list or link node is empty!" << endl; return;
	}

	LinkList* p = linkList;//ע����ʱ������Ҫ������,��Ϊ���ı䱾��ֵ!!
	while (p->nxt) {//�˴�������nxt,������p,��Ϊ������Ը���p�ĵ�ַ,��ǰһ����nxt����,���޷��ҵ���!
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
	p->nxt = s->nxt;//ǰһ����д
	s->nxt = NULL;//�Լ�ҲҪ�ǵ�����Ŷ!

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