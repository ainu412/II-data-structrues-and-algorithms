#pragma once

#include <list>
#include <vector>
#include <iostream>
#include <vld.h>
using namespace std;
//��ά����Ĵ洢��ʽ:��������
//��ͨ��һά���鷽ʽ���ʶ�ά����:
//��c�е�r�д���:c*ROWS+r
typedef struct _Point {
	int r;		//row��
	int c;		//column��
	int F;
	int H;
	int G;
	struct _Point* parent;//���ڵ��ַ
}Point;
list<Point*> openlist;
list<Point*> closelist;
int* myMap;
int rows;
int cols;
//б����to do

Point* AllocPoint(int r, int c) {
	Point* tmp = new Point;

	memset(tmp, 0, sizeof(Point));//�����ڵ��ַ��ΪNULL,FGH����Ϊ0
	tmp->c = c;
	tmp->r = r;
	return tmp;
}
Point* isInList(list<Point*>l, int r, int c) {
	list<Point*>::const_iterator it = l.begin();
	for (; it != l.end(); it++) {
		if (r == (*it)->r &&
			c == (*it)->c) {
			return *it;
		}
	}
	return NULL;
}
bool isReachable(int r, int c) {
	if (isInList(closelist, r, c) ||
		1 == myMap[r * rows + c] ||
		2 == myMap[r * rows + c] ||
		r<0 || r>=rows || c<0 || c>=cols
		)
		return false;
	else return true;
}
void getAdjPoint(Point*& p, vector<Point*>& adjPoints) {//p���ڽ��ĸ���
	for (int r = p->r - 1; r <= p->r + 1; r++) {
		for (int c = p->c - 1; c <= p->c + 1; c++) {
			if (((p->c != c && p->r == r) ||//����дabs(p->c - c) + abs(p->r -r) ==1
				(p->c == c && p->r != r)) &&
				isReachable(r, c)) {
				adjPoints.push_back(AllocPoint(r, c));
			}
		}
	}
}
static Point* getLeastFpoint() {
	list<Point*>::iterator it = openlist.begin();
	Point* minF = *it;
	for (; it != openlist.end(); it++) {
		if ((*it)->F < minF->F) {
			minF = *it;
		}
	}
	return minF;
}
static Point* findPath(Point*& start, Point*& end) {//�ڲ�����,�õ�(��ǰһ�ڵ��)�յ�ڵ�;start��end�ǵ���ǰ�����

	openlist.push_back(start);

	while (!openlist.empty()) {
		//1.Ѱ��openlist��Fֵ��С�ĵ�
		Point* cur = getLeastFpoint();

		//2.��curת���ر��б�
		openlist.remove(cur);
		closelist.push_back(cur);

		//3.Ѱ��cur���ڽӵ�p,��������FGH
		vector<Point*> adjPoints;
		getAdjPoint(cur, adjPoints);
		if (adjPoints.empty()) {
			cerr << "Adjacent point doesn't exist!" << endl;//to do
		}

		for (auto it = adjPoints.begin(); it != adjPoints.end(); it++) {
			Point* adj = *it;
			adj->parent = cur;
			adj->G = abs(end->c - adj->c) + abs(end->r - adj->r);
			adj->H = abs(cur->c - adj->c) + abs(cur->r - adj->r) + cur->H;//Hֵ�ۼ�
			adj->F = adj->H + adj->G;

			Point* exist = isInList(openlist, adj->r, adj->c);
			//��������,ֱ�����
			if (!exist) {
				openlist.push_back(adj);//ָ��ͬһ���ڴ�,����ɾadj
			}
			else {
				//������,��ԭFֵ��,�����(����ֱ��exist=adj��������,��Ϊ�����,��ָ���µ�adj,adj�Ͳ���delete��,��ԭ��������غ�û��??ɾ...
				if (exist->F > adj->F) {
					exist->G = adj->G;
					exist->F = adj->F;
					exist->parent = adj->parent;
				}
				delete adj;
			}

		}

		adjPoints.clear();//clr�������æ�ͷ�ָ��,�����openlist�ͷ������!

		Point* result = isInList(openlist, end->r, end->c);
		if (result) {
			return result;
		}
	}
	return NULL;
}

list<Point*> getPath(Point*& start, Point*& end) {//Ҫ�������Լ�,����,���ܷ�������,��Ϊ����������������
	Point* last = findPath(start, end);

	list<Point*> list;
	while (last) {//��û���ҵ��յ�,��lastΪNULL,list��û��Ԫ��Ϊ��if(list.empty()){cerr<<"Can't get there!"<<endl
		list.push_front(last);
		last = last->parent;
	}
	return list;
}
void initMap() {
	//rows
	//columns
	//ÿ�������ֵ
	//1��2������ǽ/�յ�,���ܾ���
}

#define start_r 12
#define start_c 4
#define end_r 0
#define end_c 0


void listsClr() {
	for (list<Point*>::iterator it = openlist.begin(); it != openlist.end();) {
		delete* it;
		it = openlist.erase(it);
	}
	for (list<Point*>::iterator it = closelist.begin(); it != closelist.end();) {
		delete* it;
		it = closelist.erase(it);
	}
}
void initMap(int* map, int c,int r) {
	myMap = map;
	rows = r;
	cols = c;
}
//vector���ǿ�������ֱ��ָ��ͬһ���ڴ���??
//ָ��ͬһ���ڴ�,��Ҫ������vector���ٵ�ͬʱ�ͷ��ڴ�!


int map[13][13]={
{ 0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0, },
{ 0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0, },
{ 0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0, },
{ 0,	1,	0,	1,	0,	1,	2,	1,	0,	1,	0,	1,	0, },
{ 0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0, },
{ 0,	1,	0,	1,	0,	0,	0,	1,	0,	1,	0,	1,	0, },
{ 0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0, },
{ 2,	0,	1,	1,	0,	0,	0,	1,	0,	1,	1,	0,	2, },
{ 0,	0,	0,	0,	0,	1,	1,	1,	0,	0,	0,	0,	0, },
{ 0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0, },
{ 0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0, },
{ 0,	1,	0,	1,	0,	0,	0,	0,	0,	1,	0,	1,	0, },
{ 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, }
};

void Astar() {
	Point* start = AllocPoint(start_r, start_c);
	Point* end = AllocPoint(end_r, end_c);

	initMap(&map[0][0], 13, 13);//���׵�ַ

	list<Point*> list = getPath(start, end);

	cout << "Pathfinding result:" << endl;
	for (auto it = list.begin(); it != list.end(); it++) {
		cout << "(" << (*it)->c << ", " << rows - (*it)->r << ")" << endl;
	}
	listsClr();
	//delete start;start��ַ����list��,��һͬ�ͷ�,endֻ�����˱Ƚ�,��δ����list,����Ҫ���ⲿɾ��!
	delete end;
}
int main() {

	Astar();
	return 0;
}