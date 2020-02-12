#include <iostream>
using namespace std;

#define MAX_SIZE 10
typedef struct _Sqlist {
	int* elems;
	int length;
	int size;
}Sqlist;

void listInit(Sqlist& sqlist) {//既然含指针,记得分配内存空间!
	sqlist.elems = new int [MAX_SIZE];
	if (!sqlist.elems) {
		cerr << "Dynamic memory allocation failed!" << endl;
	}
	else {
		sqlist.length = 0;
		sqlist.size = MAX_SIZE;
	}
}

void listAppend(Sqlist& sqlist, int& e) {//加入对象记得使用别名!!
	if (sqlist.length != sqlist.size) {
		sqlist.elems[sqlist.length] = e;
		sqlist.length++;
	}
	else {
		cerr << "Sequence list is full!" << endl;
	}
}

void listInsert(Sqlist& sqlist, int pos, int& e) {
	if (pos >= sqlist.length) {
		cerr << "Insertion position must be less than the current length!" << endl;
	}
	else {
		for (int i = pos; i < sqlist.length; i++) {
			sqlist.elems[i + 1] = sqlist.elems[i];
		}

		sqlist.elems[pos] = e;
		sqlist.length++;
	}
}

void listDel(Sqlist& sqlist, int pos) {
	if (pos == sqlist.length - 1) {
		sqlist.length--;
	}
	else if (pos >= sqlist.length || pos < 0) 	{
		cerr << "There isn't element stored int the position you want to delete!" << endl;
	}
	else if (pos >= 0 && pos < sqlist.length) {
		for (int i = pos; i < sqlist.length - 1; i++) {
			sqlist.elems[i] = sqlist.elems[i + 1];
		}

		sqlist.length--;
	}
}

void listDestroy(Sqlist& sqlist) {
	delete[] sqlist.elems;
}

void listPrint(Sqlist&)