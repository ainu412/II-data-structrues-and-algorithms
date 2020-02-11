#pragma once
#include "star.h"

void moveStars(DIR dir, int i, sqlist& L) {
	setfillcolor(BLACK);
	solidcircle(L.elems[i].x, L.elems[i].y, L.elems[i].radius);
	switch (dir) {
	case DIR::UP:
		L.elems[i].y -= STAR_STEP;
		if (L.elems[i].y < 0) {
			listDel(L, i);
		}
		break;
	case DIR::DOWN:
		L.elems[i].y += STAR_STEP;
		if (L.elems[i].y > STARS_HEIGHT) {
			listDel(L, i);
		}
		break;
	case DIR::LEFT:
		L.elems[i].x -= STAR_STEP;
		if (L.elems[i].x < 0) {
			listDel(L, i);
		}
		break;
	case DIR::RIGHT:
		L.elems[i].x += STAR_STEP;
		if (L.elems[i].x > SCREEN_WIDTH) {
			listDel(L, i);
		}
		break;
	}
	setfillcolor(L.elems[i].color);
	solidcircle(L.elems[i].x, L.elems[i].y, L.elems[i].radius);//无边框圆
}

void initStars(star_t& star) {
	//安插星星
	//产生一组随机数,确定安插星星的颜色(若要随时间完全随机在rand()前加上随机种子srand(time(NULL))和time.h
	//行列遍历,星星颜色随机
	//为了实现星星的移动,需要在数组中存下星星的信息
	star.x = rand() % SCREEN_WIDTH;
	star.y = rand() % STARS_HEIGHT;
	star.radius = rand() % MAX_RADIUS + 1;
	int whiteness = rand() % MAX_WHITENESS + 1;//不能为0,为0就是黑色了,1-5
	int rgb = 255 * whiteness / MAX_WHITENESS;//(0,255]
	star.color = RGB(rgb, rgb, rgb);//三值相同则为白(除全为0为黑)
}

int main() {
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);//默认640*480即可
	sqlist starL;
	initSqlist(starL);
	star_t star;

	for (int i = 0; i < MAX_NUM; i++) {
		initStars(star);
		listAppend(starL, star);
	}

	for (int i = 0; i < starL.length; i++) {
		setfillcolor(starL.elems[i].color);
		solidcircle(starL.elems[i].x, starL.elems[i].y, starL.elems[i].radius);//无边框圆
	}

	while (starL.length) {
		for (int i = 0; i < starL.length; i++) {
			moveStars(DIR::UP, i, starL);
		}
		Sleep(50);
	}

	settextcolor(WHITE);
	RECT r = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	drawtext(_T("星星会消失,可我还在身旁~"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	Sleep(1000);
	closegraph();

	listDestroy(starL);
	return 0;
}