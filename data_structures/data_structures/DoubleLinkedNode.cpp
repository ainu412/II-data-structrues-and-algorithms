#include <iostream>
#include <vld.h>
using namespace std;

typedef struct _DbLinkNode {
	struct _DbLinkNode* nxt;
	struct _DbLinkNode* pre;
}DbLinkedNode;

typedef struct _User {
	int fd;
	time_t timeout;
	DbLinkedNode node;//ע�ⲻ��ָ��!node�ǹ̶���!
}User;

void listInit(DbLinkedNode& L) {

	L.nxt = NULL;
	L.pre = NULL;
}

void listInsert_back(DbLinkedNode& L, DbLinkedNode& N) {

	DbLinkedNode* last = &L;
	while (last->nxt) {
		last = last->nxt;
	}
	last->nxt = &N;
	N.pre = last;
	N.nxt = NULL;//�ǵ�����
}
int main() {
	////1.ͨ���ڵ���ʽڵ��е�����
	//User* user = new User;
	//DbLinkedNode* p = &(user->node);//p�ǰ�ռԪ�ظ���,����Ҫ�Ȱ�pתΪint

	//cout << "Please input the fd of the node:";
	//cin >> user->fd;
	//int offset = offsetof(User, node);//node���׵�ַ��ƫ��:16���ֽ�
	//
	//User* tmp = (User*)((int)p - offset);//ֻ��User����Է��ʳ�Ա
	//cout << tmp->fd << endl;

	//2.����˫������������,ʵ�����ù���˫�������������Ԫ��
	//��ʼ���յ�˫������
	User* user = NULL, * u = NULL;
	user = new User;
	listInit(user->node);
	//β������Ԫ��
	int m;
	cout << "Please input the number of elements you want to input:";
	cin >> m;
	cout << "Plese input data/value of elements:";
	while (m-- > 0) {
		u = new User;	
		listInit(u->node);
		cin >> u->fd;
		printf("u�ĵ�ַ:%p	node: %p\n", u, &(u->node));

		listInsert_back(user->node, u->node);
	}


	//���ʴ�ӡ������Ԫ��
	DbLinkedNode* p = &(user->node);
	int offset = offsetof(User, node);
	u = (User*)((int)p - offset);
	p = p->nxt;
	delete u;
	while (p) {
		u = (User*)((int)p - offset);
		cout << u->fd << " ";
		p = p->nxt;
		delete u;
	}cout << endl;


	return 0;
}
