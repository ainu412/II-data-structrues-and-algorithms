#include <iostream>
#include <graphics.h>
using namespace std;

#define SCREEN_WIDTH  840//不含
#define SCREEN_HEIGHT 580//不含
#define MAX_RADIUS	  3//星星最大半径,含
#define MAX_WHITENESS	  5//星星最大亮度数
#define MAX_NUM		  100//顺序表最大空间,即存储最多星星个数
#define STARS_HEIGHT  420//不含
#define STAR_STEP	  5//每50ms星星移动距离

struct star_t{
	int x;
	int y;
	int radius;
	int color;
}star[MAX_NUM];

enum class DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ALL
};

bool isQuit() {
	for (int i = 0; i < MAX_NUM; i++) {
		if (star[i].x >= 0 && star[i].x < SCREEN_WIDTH &&
			star[i].y >= 0 && star[i].y < STARS_HEIGHT) {
			return false;//只要还有星星在里面就不退出
		}
	}
	return true;
}

void moveStars(DIR dir,int i) {
	switch (dir) {
	case DIR::UP:
		star[i].y -= STAR_STEP;
		break;
	case DIR::DOWN:
		star[i].y += STAR_STEP;
		break;
	case DIR::LEFT:
		star[i].x -= STAR_STEP;
		break;
	case DIR::RIGHT:
		star[i].x += STAR_STEP;
		break;
	}
}

void initStars(int i) {
	//安插星星
	//产生一组随机数,确定安插星星的颜色(若要随时间完全随机在rand()前加上随机种子srand(time(NULL))和time.h
	//行列遍历,星星颜色随机
	//为了实现星星的移动,需要在数组中存下星星的信息
	star[i].x = rand() % SCREEN_WIDTH;
	star[i].y = rand() % STARS_HEIGHT;
	star[i].radius = rand() % MAX_RADIUS + 1;
	int whiteness = rand() % MAX_WHITENESS + 1;//不能为0,为0就是黑色了,1-5
	int rgb = 255 * whiteness / MAX_WHITENESS;//(0,255]
	star[i].color = RGB(rgb, rgb, rgb);//三值相同则为白(除全为0为黑)
}

int main() {
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);//默认640*480即可

	for (int i = 0; i < MAX_NUM; i++) {
		initStars(i);//输入
		setfillcolor(star[i].color);
		solidcircle(star[i].x, star[i].y, star[i].radius);//无边框圆
	}

	while (!isQuit()) {
		for (int i = 0; i < MAX_NUM; i++) {
			setfillcolor(BLACK);
			solidcircle(star[i].x, star[i].y, star[i].radius);
			moveStars(DIR::UP, i);
			setfillcolor(star[i].color);
			solidcircle(star[i].x, star[i].y, star[i].radius);//无边框圆
		}
		Sleep(50);
	}

	settextcolor(WHITE);
	RECT r = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	drawtext(_T("星星消失了,可我还在身旁~"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	Sleep(1000);
	closegraph();
	return 0;
}