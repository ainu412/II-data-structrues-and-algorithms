#include <iostream>
#include <string>
#include <assert.h>
#include <vld.h>
using namespace std;

#define DEFAULT_SIZE 16
#define MAX_LENGTH 5

typedef string ElemType;

typedef struct _SHList {
	string member[MAX_LENGTH];
}SHList;

typedef struct _SHTable {//LinkedHashTable
	int size;//索引值个数
	SHList* lists; //HNode HList[size];实际是这样实现的,
				//但是因为size是变量,无法预先分配,不能写成数组,只能写指针
}SHTable;

void shInit(SHTable& H, int size) {
	if (size <= 0) {
		size = DEFAULT_SIZE;
	}

	H.size = size;
	H.lists = new SHList[size];//如果直接用malloc申请内存，string将不会被初始化

	//printf("%d\n", sizeof(*H.lists));

	if (!H.lists) {
		cerr << "Failed to malloc to lists!" << endl;
		return;
	}

	//H.lists[0].member[0] = "shit";
	//H.lists[1].member[0] = "fuck";
	//H.lists[2].member[0] = "ass";

	// 分配空表头位置
	for (int l = 0; l < size; l++) { //list
		/*string tmp = " ";
		H.lists[l].member[0] = tmp;*/
		for (int m = 0; m < MAX_LENGTH; m++) {//member
			//string tmp = " ";
			H.lists[l].member[m] = " ";
		}
	}
}

int Hash(SHTable& H, int key) {
	if (key < 0) {
		cerr << "The value of key must be >= 0!" << endl; return 1;
	}
	return key % H.size; //对应所在索引值(0-size-1)
}

void shInsert(SHTable& H, int key, ElemType data) {

	int i = Hash(H, key);
	int j = key / H.size;
	if (key > H.size * MAX_LENGTH) {
		cerr << "The value of key mustn't be more than " << (H.size * MAX_LENGTH) << " !"; return;
	}
	if (" " != H.lists[i].member[j]) {
		cerr << "The key already exists!" << endl; return;
	}

	H.lists[i].member[j] = data;
}

void shDel(SHTable& H, int key) {
	int i = Hash(H, key);
	int j = key / H.size;
	if (key > H.size* MAX_LENGTH) {
		cerr << "The value of key mustn't be more than " << (H.size * MAX_LENGTH) << " !"; return;
	}
	if (" " == H.lists[i].member[j]) {
		cerr << "The key doesn't exist!" << endl; return;
	}

	H.lists[i].member[j] = " ";

}
ElemType retrieve(SHTable& H, int key) {
	return H.lists[Hash(H, key)].member[key / H.size];//因NULL可为任意类型指针,data为void*
}

int main() {
	//SHList* lists = new SHList[5];
	/*lists[0].member = (string*)lists[0].member;*/
	//lists[0].member[0] = "shit";

	SHTable h;
	const char* names[] = { "larry","jessica","dogs" };
	shInit(h, 2);

	shInsert(h, 1, names[0]);
	shInsert(h, 2, names[1]);
	shInsert(h, 3, names[2]);
	shDel(h, 3);

	ElemType data;
	for (int i = 0; i < 4; i++) {
		data = retrieve(h, i);
		if (data != " ") {
			cout << data << " ";//记得类型强转且不带解引(若解引,只打印一个字母)
		}
	}cout << endl;

	delete[] h.lists;
	return 0;
}