#pragma once
#include <iostream>
using namespace std;
#define MAX_SIZE 10//测试接入10个用户

typedef struct _User {
	int fd;			//file id 档案id
	time_t timeout;//超时时刻(接入时间加5s)
}User;

typedef struct _Sqlist {
	User* elems;
	int length;
	int size;
}Sqlist;

void listInit(Sqlist& sqlist) {//既然含指针,记得分配内存空间!
	sqlist.elems = new User [MAX_SIZE];
	if (!sqlist.elems) {
		cerr << "Dynamic memory allocation failed!" << endl;
	}
	else {
		sqlist.length = 0;
		sqlist.size = MAX_SIZE;
	}
}

void listAppend(Sqlist& sqlist, User& user) {
	if (sqlist.length != sqlist.size) {
		sqlist.elems[sqlist.length] = user;
		sqlist.length++;
	}
	else {
		cerr << "Sequence list is full!" << endl;
	}
}

void listDel(Sqlist& sqlist, int pos) {
	if (pos == sqlist.length - 1) {
		sqlist.length--;
	}
	else if (pos >= sqlist.length || pos < 0) {
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

void listPrint(Sqlist& sqlist, int pos) {
	cout << "user fd:" << sqlist.elems[pos].fd << " "
		 << "user timeout:" << sqlist.elems[pos].timeout << endl;
}