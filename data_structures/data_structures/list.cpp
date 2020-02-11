#pragma once
#include "star.h"
//#include <vld.h>

#define MAX_NUM 100

/*顺序表
1.尾部追加元素
2.插入元素
3.删除(抽出/去尾)元素
4.销毁顺序表
*/

bool initSqlist(sqlist& s) {//初始化一个顺序表s
	s.elems = new star_t[MAX_NUM];
	if (!s.elems) {
		return false;
	}
	else {
		s.length = 0;
		s.size = MAX_NUM;
		return true;
	}
}

//向其中追加一个元素e
bool listAppend(sqlist& s, star_t e) {
	if (s.length != s.size) {
		s.elems[s.length] = e;
		s.length++;
		return true;
	}
	else {
		cout << "顺序表已满!" << endl;
		return false;
	}
}
//在第pos[0,length)个位置,插入一个元素e
//必须在已有位置插入,因顺序表不能隔空存元素
//不能在尾部插入!
//bool listInsert(sqlist& s, int pos, star_t e) {
//	if (pos < 0 || pos >= s.length) {
//		cout << "插入位置错误,不在[0,length)!" << endl;
//		return false;
//	}
//	else if (pos >= s.size) {
//		cout << "插入位置超过容量!" << endl;
//		return false;
//	}
//	else {
//		for (int j = s.length; j > pos; j--) {
//			s.elems[j] = s.elems[j - 1];
//		}
//		s.elems[pos] = e;
//		s.length++;
//
//		return true;
//	}
//}
//删除位置pos的元素
bool listDel(sqlist& s, int pos) {
	if (pos < 0 || pos >= s.length) {//当length为0时一定成立(<0∪>=0)==true
		cout << "删除位置未存元素!" << endl;
		return false;
	}
	else if (s.length - 1 == pos) {//去尾
		s.length--;//不需要从新赋值为0或释放空间
		return true;
	}
	else {
		for (int i = pos; i < s.length - 1; i++) {
			s.elems[i] = s.elems[i + 1];
		}
		s.length--;
		return true;
	}
}

//顺序表销毁
void listDestroy(sqlist& s) {
	if (!s.elems) {
		return;
	}
	else {
		delete[] s.elems;
	}
}
//int main() {
//	sqlist s;
//	initSqlist(s);
//	listAppend(s, 0);
//	listAppend(s, 1);
//	listAppend(s, 2);
//	listAppend(s, 3);
//	listAppend(s, 4);
//	listPrint(s);
//	listInsert(s, 0, 66);
//	listPrint(s);
//	listDel(s, 0);
//	listPrint(s);
//
//	listDestroy(s);
//	return 0;
//}