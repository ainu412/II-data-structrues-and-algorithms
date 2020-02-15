//寻找最大值,插入,删除,查找某一特定值是否存在
//遍历:前序,中序,后序,层序
//外部申请的元素内存如何释放
typedef int DataType;
#include <iostream>
#include <vld.h>
#include <assert.h>
using namespace std;
//指针减法:相隔元素个数

//初始化,出栈,入栈,获取栈顶元素,获取栈大小,销毁栈
#define MAX_SIZE 128
#define ElemType BNode
typedef struct _BNode {
	int data;
	struct _BNode* lchild, * rchild;
}BTree, BNode;

typedef struct _SqStack {
	ElemType* top;
	ElemType* base;
}SqStack;

void stackInit(SqStack& S) {
	S.base = new ElemType[MAX_SIZE];

	if (!S.base) {
		cerr << "Failed to allocate space to S.base" << endl; return;
	}

	S.top = S.base;//要把分配内存的那个的值赋给未分配的那一个!!
}
bool isEmpty(SqStack& S) {
	if (S.top == S.base) {
		cerr << "Stack is empty!" << endl;
		return true;
	}
	return false;
}
bool isFull(SqStack& S) {
	if (MAX_SIZE == S.top - S.base) {
		cerr << "Stack is full!" << endl;
		return true;
	}
	else return false;
}
void stackPush(SqStack& S, ElemType E) {//因本身不是指针,是其内元素为指针,故传递非指针引用即可
	if (isFull(S))return;

	*(S.top++) = E;
}
bool stackPop(SqStack& S, ElemType& E) {//因本身不是指针,是其内元素为指针,故传递非指针引用即可
	if (!S.base || isEmpty(S))return false;

	E = *(--S.top);
	return true;
}
void stackDestroy(SqStack& S) {//销毁栈
	if (S.base) {
		free(S.base);
	}
	S.base = S.top = NULL;
}

BTree* findMax(BTree* parent) {
	while (parent->rchild) {
		parent = parent->rchild;
	}
	return parent;
}
//法二:利用递归:耗时
int findMax2(BNode* parent) {//建立一个新的指针!不能改变原指针值!
	if (parent->rchild) {
		return findMax2(parent->rchild);//将这个函数的返回值返回
	}
	return parent->data;
}
void btreeInsert(BTree** root, BNode* node) {
	if (!root || !node) {
		cerr << "Root or node is empty!" << endl; return;
	}

	node->lchild = node->rchild = NULL;//清空新插节点的子节点

	//如果根为空,则替代根
	if (!*root) {
		*root = node;
		return;
	}

	//寻找空结点
	BNode* p = *root;
	while (1) {
		if (node->data > p->data) {
			if (!p->rchild) {
				p->rchild = node;
				break;
			}
			p = p->rchild;//再去和我的右大娃比
		}
		else {
			if (!p->lchild) {
				p->lchild = node;
				break;
			}
			p = p->lchild;
		}
	}

}
BNode* btreeDel(BNode* parent, DataType data,BNode*& del) {
	assert(parent);

	if (parent->data > data) {
		parent->lchild = btreeDel(parent->lchild, data, del);
		return parent;
	}else if (parent->data < data) {
		parent->rchild = btreeDel(parent->rchild, data, del);
		return parent;
	}

	//找到删除结点!
		//1.无左右子节点
		if (!parent->lchild && !parent->rchild) {
			del = parent;
			return NULL;//只有相等的那个的parent->child=NULL,其他都返回至parent
		}
		//2.只无右结点
		if (!parent->rchild) {
			del = parent;
			return parent->lchild;
		}
		//3.只无左结点
		if (!parent->lchild) {
			del = parent;
			return parent->rchild;
		}
		//4.左右结点都有,则左侧最大结点(或右侧最小结点)的值替位(不能直接上位,因为这样会破坏层级关系)
		parent->data = findMax(parent->lchild)->data;
		//记得删除左侧最大结点原先的位置
		parent->lchild = btreeDel(parent->lchild, parent->data, del);
		return parent;//返回修改好值后的parent
}
BTree* queryByRec(BTree* root, DataType data) {
	if (!root || data == root->data) {
		return root;
	}
	if (data > root->data) {
		return queryByRec(root->rchild, data);
	}
	return queryByRec(root->lchild, data);
}
BTree* queryByLoop(BTree* root, DataType data) {
	while (root && data != root->data) {
		if (data > root->data)
			root = root->rchild, data;
		else root = root->lchild, data;
	}
	return root;
}
void preorderRec(BTree* root) {
	if (!root)return;

	cout << root->data << " ";
	preorderRec(root->lchild);
	preorderRec(root->rchild);
}
void inorderRec(BTree* root) {
	if (!root)return;
	inorderRec(root->lchild);
	cout << root->data << " ";
	inorderRec(root->rchild);
}
void postorderRec(BTree* root) {
	if (!root)return;

	postorderRec(root->lchild);
	postorderRec(root->rchild);
	cout << root->data << " ";
}
void preorderStack(BTree* root) {//同时遍历清空
	if (!root)return;

	SqStack s;
	stackInit(s);

	BNode r;//需要本类型引用接值
	stackPush(s, *root);
	delete root;
	while (!isEmpty(s)) {
		stackPop(s, r);
		cout << r.data << " ";
		if (r.rchild) {
			stackPush(s, *(r.rchild));
			delete r.rchild;
		}
		if (r.lchild) {
			stackPush(s, *(r.lchild));
			delete r.lchild;
		}
	}cout << endl;

	stackDestroy(s);
}
//void inorderStack(BTree* root) {
//	if (!root)return;
//
//	SqStack s;
//	stackInit(s);
//
//	BNode r;//需要本类型引用接值
//	stackPush(s, *root);
//	while (!isEmpty(s)) {
//		if (r.rchild)stackPush(s, *(r.rchild));
//		if (r.lchild) {
//			stackPush(s, r);
//			r = *(r.lchild);
//		}
//		else {
//			cout << r.data << " ";
//
//	}cout << endl;
//
//	stackDestroy(s);
//}
//void btreeDstroy(BTree* root) {//使用中序遍历删除
//	if (!root)return;
//
//	SqStack s;
//	stackInit(s);//因为sqstack在创建时就已申请好全部的空间,故不需使用指针传值
//
//	BNode p = *root;//需创建新的node塞入栈
//
//	do {
//		if (p.rchild)stackPush(s, *(p.rchild));
//		stackPush(s, p);
//		if (p.lchild)stackPush(s, *(p.lchild));
//		stackPop(s, p);
//
//	} while (!isEmpty(s));
//}
int main() {
	BTree* tree = NULL;
	BNode* n, *deleted;

	int m;
	cout << "Please input number of elements you want to input:";
	cin >> m;
	cout << "Please input value of " << m << " elements:";
	while (m--) {
		n = new BNode;
		cin >> n->data;
		btreeInsert(&tree, n);
	}
	inorderRec(tree);cout << endl;
	btreeDel(tree, 1, deleted); delete deleted;
	inorderRec(tree); cout << endl;
	preorderStack(tree);

	return 0;
}