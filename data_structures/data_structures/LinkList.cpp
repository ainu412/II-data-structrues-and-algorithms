#include <iostream>
#include <vld.h>
using namespace std;

typedef struct _LinkNode {
	int data;
	struct _LinkNode* nxt;
}LinkList, LinkNode;//ͷ�ڵ�����Ľڵ�,��������ָ�Ķ��� struct _LinkList��,�ʿɻ�ָ����

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

void listInsert_front(LinkList*& linkList, LinkNode*& linkNode) {//�������г�ʼ���õ�Ԫ��!!

	if (!linkList || !linkNode) {//ȷ��ΪlistInit��node����ռ���ٲ���!!
		cerr << "Link list or link node is empty!" << endl; return;
	}

	linkNode->nxt = linkList->nxt;
	linkList->nxt = linkNode;
}
void listInsert_back(LinkList*& linkList, LinkNode*& linkNode) {

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
void listInsert(LinkList*& linkList, int pos, LinkNode*& linkNode) {

	if (!linkList || !linkNode) {//ȷ��ΪlistInit��node����ռ���ٲ���!!
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
	p->nxt = s->nxt;//ǰһ����д

	delete s;//�ǵ�ɾ���Լ�!
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
			delete s;//�ǵ�ɾ���Լ�!
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

	////1.ͷ������m��Ԫ��
	//cout << "Please input insert elements' number:";
	//cin >> m;
	//cout << "Please input " << m << " integer(s)[seperated by spaces/enter key]:";
	//int x;
	//while (m-- > 0) {
	//	cin >> x;
	//	n = new LinkNode;//����ÿ�ζ������µĿռ�,��Ϊ������һ�μ�һ��,����˳���һ��ʼ�ͷֹ��ռ�ֱ�ӿ�������		
	//	n->data = x;//�Ȱ����ݴ���node,�ٰ�node����
	//	listInsert_front(l, n);
	//}

	//2.β������m��Ԫ��
	cout << "Please input insert elements' number:";
	cin >> m;
	cout << "Please input " << m << " integer(s)[seperated by spaces/enter key]:";
	int x;
	while (m-- > 0) {
		cin >> x;
		n = new LinkNode;//����ÿ�ζ������µĿռ�,��Ϊ������һ�μ�һ��,����˳���һ��ʼ�ͷֹ��ռ�ֱ�ӿ�������		
		n->data = x;//�Ȱ����ݴ���node,�ٰ�node����
		listInsert_back(l, n);
	}

	////3.������λ��y����Ԫ��x(����β��)
	//cout << "Please input one integer:";
	//cin >> x;
	//n = new LinkNode;//����ÿ�ζ������µĿռ�,��Ϊ������һ�μ�һ��,����˳���һ��ʼ�ͷֹ��ռ�ֱ�ӿ�������		
	//n->data = x;//�Ȱ����ݴ���node,�ٰ�node����

	//cout << "and the position you want to insert it:";
	//int y;
	//cin >> y;

	//listInsert(l, y, n);

	////4.���ҵ�x��λ����������
	//cout << "Please input the position of the element:";
	//cin >> x;
	//int e;
	//if (getElemValue(l, x, e)) {
	//cout << "value=" << e << endl;
	//}

	////5.���ҵ�һ������Ϊx��Ԫ������λ��
	//cout << "Please input the data/value of the element:";
	//cin >> x;
	//if (getElemPos(l, m, x)) {
	//	cout << "pos=" << m << endl;
	//}

	////6.ɾ��λ��Ϊm��Ԫ��
	//cout << "Please input the position of the element you want to delete:";
	//cin >> m;
	//listDelPos(l, m);

	////7.ɾ��ֵΪm��Ԫ��
	//cout << "Please input the data/value of the element you want to delete:";
	//cin >> m;
	//listDelVal(l, m);

	//8.��ӡ
	listPrint(l);

	//9.����
	listDestroy(l);
	return 0;
}