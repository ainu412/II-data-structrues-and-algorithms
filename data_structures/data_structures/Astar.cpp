#pragma once

#include <list>
#include <vector>
#include <iostream>
#include <vld.h>
using namespace std;
//二维数组的存储方式:先行再列
//可通过一维数组方式访问二维数组:
//第c行第r列存在:c*ROWS+r
typedef struct _Point {
	int r;		//row行
	int c;		//column列
	int F;
	int H;
	int G;
	struct _Point* parent;//父节点地址
}Point;
list<Point*> openlist;
list<Point*> closelist;
int* myMap;
int rows;
int cols;
//斜着走to do

Point* AllocPoint(int r, int c) {
	Point* tmp = new Point;

	memset(tmp, 0, sizeof(Point));//将父节点地址设为NULL,FGH都设为0
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
void getAdjPoint(Point*& p, vector<Point*>& adjPoints) {//p的邻接四个点
	for (int r = p->r - 1; r <= p->r + 1; r++) {
		for (int c = p->c - 1; c <= p->c + 1; c++) {
			if (((p->c != c && p->r == r) ||//或者写abs(p->c - c) + abs(p->r -r) ==1
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
static Point* findPath(Point*& start, Point*& end) {//内部方法,得到(含前一节点的)终点节点;start和end记得提前分配好

	openlist.push_back(start);

	while (!openlist.empty()) {
		//1.寻找openlist中F值最小的点
		Point* cur = getLeastFpoint();

		//2.将cur转至关闭列表
		openlist.remove(cur);
		closelist.push_back(cur);

		//3.寻找cur的邻接点p,并计算其FGH
		vector<Point*> adjPoints;
		getAdjPoint(cur, adjPoints);
		if (adjPoints.empty()) {
			cerr << "Adjacent point doesn't exist!" << endl;//to do
		}

		for (auto it = adjPoints.begin(); it != adjPoints.end(); it++) {
			Point* adj = *it;
			adj->parent = cur;
			adj->G = abs(end->c - adj->c) + abs(end->r - adj->r);
			adj->H = abs(cur->c - adj->c) + abs(cur->r - adj->r) + cur->H;//H值累加
			adj->F = adj->H + adj->G;

			Point* exist = isInList(openlist, adj->r, adj->c);
			//若不存在,直接添加
			if (!exist) {
				openlist.push_back(adj);//指向同一块内存,不能删adj
			}
			else {
				//若存在,且原F值大,则更新(不能直接exist=adj拷贝更新,因为若如此,会指向新的adj,adj就不能delete了,与原来申请的重合没法??删...
				if (exist->F > adj->F) {
					exist->G = adj->G;
					exist->F = adj->F;
					exist->parent = adj->parent;
				}
				delete adj;
			}

		}

		adjPoints.clear();//clr并不会帮忙释放指针,最后由openlist释放推入的!

		Point* result = isInList(openlist, end->r, end->c);
		if (result) {
			return result;
		}
	}
	return NULL;
}

list<Point*> getPath(Point*& start, Point*& end) {//要返回他自己,续命,不能返回引用,因为这块结束他就消亡了
	Point* last = findPath(start, end);

	list<Point*> list;
	while (last) {//若没有找到终点,则last为NULL,list中没有元素为空if(list.empty()){cerr<<"Can't get there!"<<endl
		list.push_front(last);
		last = last->parent;
	}
	return list;
}
void initMap() {
	//rows
	//columns
	//每个坐标的值
	//1和2代表是墙/终点,不能经过
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
//vector中是拷贝还是直接指向同一块内存呢??
//指向同一块内存,需要在最后把vector销毁的同时释放内存!


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

	initMap(&map[0][0], 13, 13);//调首地址

	list<Point*> list = getPath(start, end);

	cout << "Pathfinding result:" << endl;
	for (auto it = list.begin(); it != list.end(); it++) {
		cout << "(" << (*it)->c << ", " << rows - (*it)->r << ")" << endl;
	}
	listsClr();
	//delete start;start地址存入list了,故一同释放,end只是做了比较,并未存入list,故需要在外部删除!
	delete end;
}
int main() {

	Astar();
	return 0;
}