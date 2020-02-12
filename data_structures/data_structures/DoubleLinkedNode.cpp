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
	DbLinkedNode node;//注意不是指针!node是固定的!
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
	N.nxt = NULL;//记得置零
}
int main() {
	////1.通过节点访问节点中的数据
	//User* user = new User;
	//DbLinkedNode* p = &(user->node);//p是按占元素个数,故需要先把p转为int

	//cout << "Please input the fd of the node:";
	//cin >> user->fd;
	//int offset = offsetof(User, node);//node与首地址的偏移:16个字节
	//
	//User* tmp = (User*)((int)p - offset);//只有User类可以访问成员
	//cout << tmp->fd << endl;

	//2.调用双向链表中内容,实现利用共享双向链表访问所有元素
	//初始化空的双向链表
	User* user = NULL, * u = NULL;
	user = new User;
	listInit(user->node);
	//尾部插入元素
	int m;
	cout << "Please input the number of elements you want to input:";
	cin >> m;
	cout << "Plese input data/value of elements:";
	while (m-- > 0) {
		u = new User;	
		listInit(u->node);
		cin >> u->fd;
		printf("u的地址:%p	node: %p\n", u, &(u->node));

		listInsert_back(user->node, u->node);
	}


	//访问打印并销毁元素
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
