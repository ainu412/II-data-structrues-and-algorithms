#include <iostream>
#include <assert.h>
using namespace std;
#define DEFAULT_SIZE 16
#define MAX_LENGTH 100

typedef string ElemType;

typedef struct _SHList {
	ElemType member[MAX_LENGTH];
}SHList;

typedef struct _SHTable {//LinkedHashTable
	int size;//索引值个数
	SHList** lists; //SHList* lists[size];实际是这样实现的,,但是因为size是变量,无法预先分配,不能写成数组,只能写指针
}SHTable;

void shInit(SHTable& H, int size) {
	if (size <= 0) {
		size = DEFAULT_SIZE;
	}
	H.size = size;
	//记得分配指针数组!!记得乘以数目!!
	H.lists = (SHList**)calloc(size, sizeof(SHList*));//一次性分够
	if (!H.lists) {
		cerr << "Failed to malloc to lists!" << endl; return;
	}

	//分配空表头位置
	for (int l = 0; l < size; l++) {//list
		H.lists[l] = (SHList*)calloc(1, sizeof(SHList));//calloc初始化为0了!!
		for (int m = 0; m < MAX_LENGTH; m++) {//member
			H.lists[l]->member[m] = "\t\0";//calloc也不管用...只有new宝宝可以了qwq
		}
	}
}
int Hash(SHTable& H, int key) {
	if (key < 0) {
		cerr << "The value of key must be more than or equal to 0!" << endl; return 1;
	}
	return key % H.size;//对应所在索引值(0-size-1)
}
void shInsert(SHTable& H, int key, ElemType data) {

	int i = Hash(H, key);
	int j = key / H.size;
	if (key > H.size * MAX_LENGTH) {
		cerr << "The value of key mustn't be more than " << (H.size * MAX_LENGTH) << " !"; return;
	}
	if ("\t\0" != H.lists[i]->member[j]) {
		cerr << "The key already exists!" << endl; return;
	}

	H.lists[i]->member[j] = data;
}
void shDel(SHTable& H, int key) {
	int i = Hash(H, key);
	int j = key / H.size;
	if (key > H.size* MAX_LENGTH) {
		cerr << "The value of key mustn't be more than " << (H.size * MAX_LENGTH) << " !"; return;
	}
	if ("\t\0" == H.lists[i]->member[j]) {
		cerr << "The key doesn't exist!" << endl; return;
	}

	H.lists[i]->member[j] = "\t\0";

}
ElemType retrieve(SHTable& H, int key) {
	return H.lists[Hash(H, key)]->member[key / H.size];//因NULL可为任意类型指针,data为void*
}
int main() {

	SHTable h;
	string names[] = { "larry","jessica","dogs" };
	shInit(h, 2);
	shInsert(h, 1, names[0]);
	shInsert(h, 2, names[1]);
	shInsert(h, 3, names[2]);
	shDel(h, 1);

	ElemType data;
	for (int i = 0; i < 4; i++) {
		data = retrieve(h, i);
		if (data!="\t\0") {
			cout << data << " ";//记得类型强转且不带解引(若解引,只打印一个字母)
		}
	}
	return 0;
}