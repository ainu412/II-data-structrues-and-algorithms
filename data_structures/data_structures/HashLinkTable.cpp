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
	int size;//索引值个数
	HNode** list; //HNode HList[size];实际是这样实现的,,但是因为size是变量,无法预先分配,不能写成数组,只能写指针
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
	//记得分配指针数组!!记得乘以数目!!
	H->list = (HNode**)malloc(sizeof(HNode*) * size);

	//分配空表头位置
	for (int i = 0; i < size; i++) {
		H->list[i] = (HNode*)malloc(sizeof(HNode));
		if(!H->list[i]) {
			cerr << "Failed to malloc to lists!" << endl; return;
		}
		memset(H->list[i], 0, sizeof(HNode));//或sizeof(*H->list[0]),为指针赋值0==NULL,确保最后一个元素的下一个元素为空
		//memset,不是copy
	}
}
int Hash(LHTable*& H, int key) {
	if (key < 0) {
		cerr << "The value of key must be more than or equal to 0!" << endl; return 1;
	}
	return key % H->size;//对应所在索引值(0-size-1)
}
HNode* lhFind(LHTable*& H, int key) {
	assert(H);

	HNode* n = H->list[Hash(H, key)]->nxt;
	//记得第一次插入的元素的nxt值为NULL

	while (n && n->key!=key) {//若n为空,则未找到
		n = n->nxt;
	}
	return n;
}
void lhInsert(LHTable*& H, int key, const char* data) {
	if (!H)return;

	if (lhFind(H, key)) {
		cerr << "The key already exists!" << endl; return;
	}

	//新创建
	HNode* n = new HNode;
	//strcpy_s((char*)n->data, sizeof(data), (char*)data);//?data可以直接赋值??,哦对因为是被拷贝到的指针已经有了空间,直接拷贝过去即可(存人名数组地址不变)
	n->data = (void*)data;
	n->key = key;

	//头插法
	int i = Hash(H, key);
	n->nxt = H->list[i]->nxt;
	H->list[i]->nxt = n;//已确保插入第一个元素的下一元素为空

}
void lhDel(LHTable*& H, int key) {
	if (!H)return;

	HNode* n = H->list[Hash(H, key)]->nxt;
	HNode* last = H->list[Hash(H, key)];
	while (n && n->key != key) {//若n为空,则未找到
		last = n;
		n = n->nxt;
	}

	if (n) {
		last->nxt = n->nxt;
		delete n;
	}
}
void* retrieve(HNode* N) {
	return N ? N->data : NULL;//因NULL可为任意类型指针,data为void*
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
			cout << (const char*)retrieve(data) << " ";//记得类型强转且不带解引(若解引,只打印一个字母)
		}
	}

	return 0;
}