#include <iostream>
#include <assert.h>
using namespace std;
#define DEFAULT_SIZE 16
typedef struct _HNode {
	void* data;
	int key;
	struct _HNode* nxt;
}HNode;

typedef struct _LHTable {//LinkedHashTable
	int size;//����ֵ����
	HNode** list; //HNode HList[size];ʵ��������ʵ�ֵ�,,������Ϊsize�Ǳ���,�޷�Ԥ�ȷ���,����д������,ֻ��дָ��
}LHTable;

void lhInit(LHTable*& H, int size) {
	if (H)return;

	H = (LHTable*)malloc(sizeof(LHTable));
	if (!H) {
		cerr << "Failed to malloc to Hash table!" << endl; return;
	}

	if (size <= 0) {
		size = DEFAULT_SIZE;
	}
	H->size = size;
	//�ǵ÷���ָ������!!�ǵó�����Ŀ!!
	H->list = (HNode**)malloc(sizeof(HNode*) * size);

	//����ձ�ͷλ��
	for (int i = 0; i < size; i++) {
		H->list[i] = (HNode*)malloc(sizeof(HNode));
		if(!H->list[i]) {
			cerr << "Failed to malloc to lists!" << endl; return;
		}
		memset(H->list[i], 0, sizeof(HNode));//��sizeof(*H->list[0]),Ϊָ�븳ֵ0==NULL,ȷ�����һ��Ԫ�ص���һ��Ԫ��Ϊ��
		//memset,����copy
	}
}
int Hash(LHTable*& H, int key) {
	if (key < 0) {
		cerr << "The value of key must be more than or equal to 0!" << endl; return 1;
	}
	return key % H->size;//��Ӧ��������ֵ(0-size-1)
}
HNode* lhFind(LHTable*& H, int key) {
	assert(H);

	HNode* n = H->list[Hash(H, key)]->nxt;
	//�ǵõ�һ�β����Ԫ�ص�nxtֵΪNULL

	while (n && n->key!=key) {//��nΪ��,��δ�ҵ�
		n = n->nxt;
	}
	return n;
}
void lhInsert(LHTable*& H, int key, const char* data) {
	if (!H)return;

	if (lhFind(H, key)) {
		cerr << "The key already exists!" << endl; return;
	}

	//�´���
	HNode* n = new HNode;
	//strcpy_s((char*)n->data, sizeof(data), (char*)data);//?data����ֱ�Ӹ�ֵ??,Ŷ����Ϊ�Ǳ���������ָ���Ѿ����˿ռ�,ֱ�ӿ�����ȥ����(�����������ַ����)
	n->data = (void*)data;
	n->key = key;

	//ͷ�巨
	int i = Hash(H, key);
	n->nxt = H->list[i]->nxt;
	H->list[i]->nxt = n;//��ȷ�������һ��Ԫ�ص���һԪ��Ϊ��

}
void lhDel(LHTable*& H, int key) {
	if (!H)return;

	HNode* n = H->list[Hash(H, key)]->nxt;
	HNode* last = H->list[Hash(H, key)];
	while (n && n->key != key) {//��nΪ��,��δ�ҵ�
		last = n;
		n = n->nxt;
	}

	if (n) {
		last->nxt = n->nxt;
		delete n;
	}
}
void* retrieve(HNode* N) {
	return N ? N->data : NULL;//��NULL��Ϊ��������ָ��,dataΪvoid*
}
int main() {
	LHTable* h = NULL;
	int size = 2;
	int del = 0;
	const char* names[] = { "larry","jessica","dogs" };
	lhInit(h, size);
	lhInsert(h, 1, names[0]);
	lhInsert(h, 2, names[1]);
	lhInsert(h, 3, names[2]);
	lhDel(h, 1);

	HNode* data;
	for (int i = 0; i < 3; i++) {
		data = lhFind(h, i);
		if (data) {
			cout << (const char*)retrieve(data) << " ";//�ǵ�����ǿת�Ҳ�������(������,ֻ��ӡһ����ĸ)
		}
	}

	return 0;
}