#include <iostream>
#include <assert.h>
#include <vld.h>
using namespace std;
#define DEFAULT_SIZE 128

//��:��Ȼ��ͨ���ַ���ȷ��������,�Ǽ�ֵ�ǲ��ǲ���Ҫ�洢��??
//û��!!ͨ���ַ������Լ������ֵ,�ʼ�ֵ�ַ������ô���
//�����ڱȽϵ�ʱ��Ҫ��Ϊ�ַ����������ݱȽϲ���...
typedef struct _LHNode {
	void* data;
	struct _LHNode* nxt;
}LHNode;

typedef struct _LHTable {
	int size;
	LHNode** lists;//LHNode* list[i]ָ������
}LHTable;

unsigned int SDBMHash(void* key)
{
	unsigned int hash = 0; 
	char* str = (char*)key;

	while (*str)
	{
		// equivalent to: hash = 65599*hash + (*str++);
		hash = (*str++) + (hash << 6) + (hash << 16) - hash;
	}

	return (hash & 0x7FFFFFFF);
}
void lhInit(LHTable*& T, int size) {

	T = (LHTable*)malloc(sizeof(LHTable));
	assert(T);

	T->lists = (LHNode**)malloc(sizeof(LHNode*) * size);
	assert(T->lists);

	if (size <= 0)size = DEFAULT_SIZE;
	T->size = size;
	for (int l = 0; l < size; l++) {
		T->lists[l] = (LHNode*)malloc(sizeof(LHNode));
		memset(T->lists[l], 0, sizeof(LHNode));
	}
}
int Hash(LHTable*& T, void* key) {
	//return key % T->size;
	return SDBMHash(key) % T->size;
}
LHNode* lhFind(LHTable*& T, void* data) {
	int i = Hash(T, data);

	if (!T->lists[i]->nxt)return NULL;
	LHNode* p = T->lists[i]->nxt;
	while (p && strcmp((const char*)data, (const char*)p->data)) {//�ǵ�����ǿת
		p = p->nxt;
	}
	return p;//���pΪ����δ�ҵ�
}

void lhInsert(LHTable*& T, void* data) {
	LHNode* n = new LHNode;

	int i = Hash(T, data);
	//ͷ��
	if (!lhFind(T, data)) {
		n->data = (void*)data;
		n->nxt = T->lists[i]->nxt;
		T->lists[i]->nxt = n;
	}
}
void lhDel(LHTable*& T, void* data) {
	int i = Hash(T, data);

	LHNode* p = T->lists[i]->nxt;
	LHNode* last = T->lists[i];
	while (p && p->data != data) {
		last = p;
		p = p->nxt;
	}
	if (!p) {
		cerr << "Not found!" << endl; return;
	}
	last->nxt = p->nxt;
	delete p;
}
void lhDestroy(LHTable*& T) {
	if (!T)return;

	LHNode* p;
	for (int i = 0; i < T->size; i++) {
		p = T->lists[i];
		while (p->nxt) {
			T->lists[i] = T->lists[i]->nxt;
			delete p;
			p = T->lists[i];
		}
		delete T->lists[i];
	}
	delete T->lists;
	delete T;
}
int main() {
	//���char�����0,�����ַ�����������?
	//�����ַ���,����β���Զ�����'\0',�ʼǵó���Ҫ�����ַ������ȼ�1(1������'\0')
	const char* elems[] = { "ADBB","BDDC","CDBC","BDBB" };
	const char* tester = "ABDBBBAC";

	const char* test = "\0";
	cout << test;

	LHTable* t;
	lhInit(t, 2);
	//lhInsert(t, (void*)"larry");
	//lhInsert(t, (void*)"larry");
	//lhInsert(t, (void*)"je");
	//lhDel(t, (void*)"larry");

	for (unsigned int i = 0; i < sizeof(elems) / sizeof(elems[0]); i++) {
		lhInsert(t, (void*)elems[i]);
	}

	char tester_25[6];//���Բ���ʼ��,��Ϊ����´����ȥ = { "h" };
	strncpy_s(tester_25, 5, tester + 1, 4);//ò�Ʋ�����Ҽ����ַ���������������...
	//strncp_s�ĵڶ���������Ŀ�껺�����Ĵ�С,Ҫ�ȿ����ַ����ĳ��ȴ�1�����Զ���æ�����ַ���������'\0'

	LHNode* e;
	e = lhFind(t, (void*)tester_25);
	if (e) {
		cout << "Found color blindness gene:"
			<< (const char*)e->data << "!" << endl;
	}
	else {
		cout << "color blindness gene not found!" << endl;
	}

	lhDestroy(t);
	return 0;
}