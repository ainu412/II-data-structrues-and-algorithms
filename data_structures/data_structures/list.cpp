#pragma once
#include "star.h"
//#include <vld.h>

#define MAX_NUM 100

/*˳���
1.β��׷��Ԫ��
2.����Ԫ��
3.ɾ��(���/ȥβ)Ԫ��
4.����˳���
*/

bool initSqlist(sqlist& s) {//��ʼ��һ��˳���s
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

//������׷��һ��Ԫ��e
bool listAppend(sqlist& s, star_t e) {
	if (s.length != s.size) {
		s.elems[s.length] = e;
		s.length++;
		return true;
	}
	else {
		cout << "˳�������!" << endl;
		return false;
	}
}
//�ڵ�pos[0,length)��λ��,����һ��Ԫ��e
//����������λ�ò���,��˳����ܸ��մ�Ԫ��
//������β������!
//bool listInsert(sqlist& s, int pos, star_t e) {
//	if (pos < 0 || pos >= s.length) {
//		cout << "����λ�ô���,����[0,length)!" << endl;
//		return false;
//	}
//	else if (pos >= s.size) {
//		cout << "����λ�ó�������!" << endl;
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
//ɾ��λ��pos��Ԫ��
bool listDel(sqlist& s, int pos) {
	if (pos < 0 || pos >= s.length) {//��lengthΪ0ʱһ������(<0��>=0)==true
		cout << "ɾ��λ��δ��Ԫ��!" << endl;
		return false;
	}
	else if (s.length - 1 == pos) {//ȥβ
		s.length--;//����Ҫ���¸�ֵΪ0���ͷſռ�
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

//˳�������
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