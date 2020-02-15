#include <iostream>
using namespace std;
//保存已走过地点坐标,便于回溯

typedef struct _Pos {
	int c;
	int r;
}Pos;
//初始化,出栈,入栈,获取栈顶元素(top-1)
#define ROW 5
#define COL 6

#define MAX_SIZE 128
#define ElemType Pos

int entrance_r = 0;
int entrance_c = 2;

typedef struct _MyMap {
	int map[ROW][COL];
}MyMap;

typedef struct _SqStack {
	ElemType* top;
	ElemType* base;
}SqStack;
static SqStack s;
void initMy(MyMap*& my, int maze[ROW][COL]) {
	for (int r = 0; r < ROW; r++) {
		for (int c = 0; c < COL; c++) {
			my->map[r][c] = maze[r][c];
		}
	}
}
void printMy(MyMap*& my) {
	for (int r = 0; r < ROW; r++) {
		for (int c = 0; c < COL; c++) {
			cout << my->map[r][c] << " ";
		}cout << endl;
	}
}
bool isValidNxt(MyMap*& my, Pos& nxt) {
	if (nxt.c >= 0 && nxt.c < COL && nxt.r >= 0 &&
		nxt.r < ROW && 1 == my->map[nxt.r][nxt.c]) {
		return true;
	}
	else return false;
}
bool isValidEntrance(MyMap*& my, Pos& pos) {
	 if ((!pos.c || COL - 1 == pos.c || 
		  !pos.r || ROW - 1 == pos.r)
		 &&  1 == my->map[pos.r][pos.c])
		return true;
	else return false;
}
bool isValidExit(MyMap*& my, Pos& pos) {
	if ((!pos.c || COL - 1 == pos.c ||
		 !pos.r || ROW - 1 == pos.r)
		&&  pos.r != entrance_r)//和入口不能在一行
		return true;
	else return false;
}

void stackInit() {
	s.base = new ElemType[MAX_SIZE];

	if (!s.base) {
		cerr << "Failed to allocate space to S.base" << endl; return;
	}

	s.top = s.base;//要把分配内存的那个的值赋给未分配的那一个!!
}
bool isEmpty() {
	if (s.top == s.base) {
		cerr << "Stack is empty!" << endl;
		return true;
	}
	return false;
}
bool isFull() {
	if (MAX_SIZE == s.top - s.base) {
		cerr << "Stack is full!" << endl;
		return true;
	}
	else return false;
}
void stackPush(ElemType E) {//因本身不是指针,是其内元素为指针,故传递非指针引用即可
	if (isFull())return;

	*(s.top++) = E;
}
bool stackPop() {//因本身不是指针,是其内元素为指针,故传递非指针引用即可
	if (!s.base || isEmpty())return false;

	--s.top;
	return true;
}
void getTop(ElemType& E){
	if (isEmpty())return;
	E = *(s.top - 1);
}
void findPass(MyMap*& my, Pos& cur) {
	Pos nxt;

	nxt = cur;
	nxt.r -= 1;
	if (isValidNxt(my, nxt)) {
		my->map[nxt.r][nxt.c] = my->map[cur.r][cur.c] + 1;
		stackPush(nxt);
		cur = nxt;
		return;
	}

	nxt = cur;
	nxt.r += 1;
	if (isValidNxt(my, nxt)) {
		my->map[nxt.r][nxt.c] = my->map[cur.r][cur.c] + 1;
		stackPush(nxt);
		cur = nxt;
		return;
	}

	nxt = cur;
	nxt.c -= 1;
	if (isValidNxt(my, nxt)) {
		my->map[nxt.r][nxt.c] = my->map[cur.r][cur.c] + 1;
		stackPush(nxt);
		cur = nxt;
		return;
	}

	nxt = cur;
	nxt.c += 1;
	if (isValidNxt(my, nxt)) {
		my->map[nxt.r][nxt.c] = my->map[cur.r][cur.c] + 1;
		stackPush(nxt);
		cur = nxt;
		return;
	}
	
	stackPop();//pop掉现在所在位置
	if (isEmpty()) {
		cerr << "Maze without solution!" << endl;
		printMy(my);
		delete my;
		delete[] s.base;
		exit(0);
	}
	getTop(cur);//cur变为上一位置
}
//走过的地方入栈,不可行的地方出栈
int main() {
	stackInit();

	int map[ROW][COL] = {	//用二维数组描绘迷宫：1 代表通路，0 代表墙0,0,1,0,0,0,
	0,0,1,1,1,0,
	0,0,1,0,0,0,
	0,1,1,1,1,0,
	0,0,1,0,1,0,
	0,0,0,0,0,0 };
	MyMap* my = new MyMap;
	initMy(my, map);
	printMy(my);

	Pos cur;
	cur.r = entrance_r;
	cur.c = entrance_c;
	if (!isValidEntrance(my, cur)) {
		cerr << "Entrance is wrong!" << endl; exit(-1);
	}
	stackPush(cur);
	my->map[cur.r][cur.c] = 2;

	while (!isValidExit(my, cur)) {
		findPass(my, cur);
	}

	cout << "Find pass:" << endl;
	printMy(my);

	delete my;
	delete[] s.base;
	return 0;
}