//Ѱ�����ֵ,����,ɾ��,����ĳһ�ض�ֵ�Ƿ����
//����:ǰ��,����,����,����
//�ⲿ�����Ԫ���ڴ�����ͷ�
typedef int DataType;
#include <iostream>
#include <vld.h>
#include <assert.h>
using namespace std;
//ָ�����:���Ԫ�ظ���

//��ʼ��,��ջ,��ջ,��ȡջ��Ԫ��,��ȡջ��С,����ջ
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

	S.top = S.base;//Ҫ�ѷ����ڴ���Ǹ���ֵ����δ�������һ��!!
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
void stackPush(SqStack& S, ElemType E) {//������ָ��,������Ԫ��Ϊָ��,�ʴ��ݷ�ָ�����ü���
	if (isFull(S))return;

	*(S.top++) = E;
}
bool stackPop(SqStack& S, ElemType& E) {//������ָ��,������Ԫ��Ϊָ��,�ʴ��ݷ�ָ�����ü���
	if (!S.base || isEmpty(S))return false;

	E = *(--S.top);
	return true;
}
void stackDestroy(SqStack& S) {//����ջ
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
//����:���õݹ�:��ʱ
int findMax2(BNode* parent) {//����һ���µ�ָ��!���ܸı�ԭָ��ֵ!
	if (parent->rchild) {
		return findMax2(parent->rchild);//����������ķ���ֵ����
	}
	return parent->data;
}
void btreeInsert(BTree** root, BNode* node) {
	if (!root || !node) {
		cerr << "Root or node is empty!" << endl; return;
	}

	node->lchild = node->rchild = NULL;//����²�ڵ���ӽڵ�

	//�����Ϊ��,�������
	if (!*root) {
		*root = node;
		return;
	}

	//Ѱ�ҿս��
	BNode* p = *root;
	while (1) {
		if (node->data > p->data) {
			if (!p->rchild) {
				p->rchild = node;
				break;
			}
			p = p->rchild;//��ȥ���ҵ��Ҵ��ޱ�
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

	//�ҵ�ɾ�����!
		//1.�������ӽڵ�
		if (!parent->lchild && !parent->rchild) {
			del = parent;
			return NULL;//ֻ����ȵ��Ǹ���parent->child=NULL,������������parent
		}
		//2.ֻ���ҽ��
		if (!parent->rchild) {
			del = parent;
			return parent->lchild;
		}
		//3.ֻ������
		if (!parent->lchild) {
			del = parent;
			return parent->rchild;
		}
		//4.���ҽ�㶼��,����������(���Ҳ���С���)��ֵ��λ(����ֱ����λ,��Ϊ�������ƻ��㼶��ϵ)
		parent->data = findMax(parent->lchild)->data;
		//�ǵ�ɾ����������ԭ�ȵ�λ��
		parent->lchild = btreeDel(parent->lchild, parent->data, del);
		return parent;//�����޸ĺ�ֵ���parent
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
void preorderStack(BTree* root) {//ͬʱ�������
	if (!root)return;

	SqStack s;
	stackInit(s);

	BNode r;//��Ҫ���������ý�ֵ
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
//	BNode r;//��Ҫ���������ý�ֵ
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
//void btreeDstroy(BTree* root) {//ʹ���������ɾ��
//	if (!root)return;
//
//	SqStack s;
//	stackInit(s);//��Ϊsqstack�ڴ���ʱ���������ȫ���Ŀռ�,�ʲ���ʹ��ָ�봫ֵ
//
//	BNode p = *root;//�贴���µ�node����ջ
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