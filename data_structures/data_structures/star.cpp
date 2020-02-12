#pragma once
#include "star.h"

void moveStars(DIR dir,LinkList*& L) {
	if (!L)return;
	LinkList* p = L->nxt;
	int i = 1;
	while (p) {
		setfillcolor(BLACK);
		solidcircle(p->data.x, p->data.y, p->data.radius);
		switch (dir) {
		case DIR::UP:
			p->data.y -= STAR_STEP;
			if (p->data.y < 0) {
				listDel(L, i);
				p = L->nxt;
				i = 1;
			}
			break;
		case DIR::DOWN:
			p->data.y += STAR_STEP;
			if (p->data.y > STARS_HEIGHT) {
				listDel(L, i);
				p = L->nxt;
				i = 1;
			}
			break;
		case DIR::LEFT:
			p->data.x -= STAR_STEP;
			if (p->data.x < 0) {
				listDel(p, i);
				p = L->nxt;
				i = 1;
			}
			break;
		case DIR::RIGHT:
			p->data.x += STAR_STEP;
			if (p->data.x > SCREEN_WIDTH) {
				listDel(L, i);
				p = L->nxt;
				i = 1;
			}
			break;
		}

		if (p) {
			setfillcolor(p->data.color);
			solidcircle(p->data.x, p->data.y, p->data.radius);//无边框圆
			p = p->nxt;
			i++;
		}
	}
}

void initStars(LinkNode* & node) {
	node = new LinkNode;
	//安插星星
	//产生一组随机数,确定安插星星的颜色(若要随时间完全随机在rand()前加上随机种子srand(time(NULL))和time.h
	//行列遍历,星星颜色随机
	//为了实现星星的移动,需要在数组中存下星星的信息
	node->data.x = rand() % SCREEN_WIDTH;
	node->data.y = rand() % STARS_HEIGHT;
	node->data.radius = rand() % MAX_RADIUS + 1;
	int whiteness = rand() % MAX_WHITENESS + 1;//不能为0,为0就是黑色了,1-5
	int rgb = 255 * whiteness / MAX_WHITENESS;//(0,255]
	node->data.color = RGB(rgb, rgb, rgb);//三值相同则为白(除全为0为黑)
	setfillcolor(node->data.color);
	solidcircle(node->data.x, node->data.y, node->data.radius);//无边框圆
}

int main() {
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);//默认640*480即可
	LinkList* starL = NULL;
	LinkNode* starN = NULL;
	listInit(starL);

	for (int i = 1; i <= MAX_NUM; i++) {
		initStars(starN);
		listInsert_back(starL, starN);
	}

	while (starL->nxt) {
		moveStars(DIR::UP, starL);

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