#include <iostream>
using namespace std;
//�������߹��ص�����,���ڻ���

typedef struct _Pos {
	int c;
	int r;
}Pos;
//��ʼ��,��ջ,��ջ,��ȡջ��Ԫ��(top-1)
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
		&&  pos.r != entrance_r)//����ڲ�����һ��
		return true;
	else return false;
}

void stackInit() {
	s.base = new ElemType[MAX_SIZE];

	if (!s.base) {
		cerr << "Failed to allocate space to S.base" << endl; return;
	}

	s.top = s.base;//Ҫ�ѷ����ڴ���Ǹ���ֵ����δ�������һ��!!
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
void stackPush(ElemType E) {//������ָ��,������Ԫ��Ϊָ��,�ʴ��ݷ�ָ�����ü���
	if (isFull())return;

	*(s.top++) = E;
}
bool stackPop() {//������ָ��,������Ԫ��Ϊָ��,�ʴ��ݷ�ָ�����ü���
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
	
	stackPop();//pop����������λ��
	if (isEmpty()) {
		cerr << "Maze without solution!" << endl;
		printMy(my);
		delete my;
		delete[] s.base;
		exit(0);
	}
	getTop(cur);//cur��Ϊ��һλ��
}
//�߹��ĵط���ջ,�����еĵط���ջ
int main() {
	stackInit();

	int map[ROW][COL] = {	//�ö�ά��������Թ���1 ����ͨ·��0 ����ǽ0,0,1,0,0,0,
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