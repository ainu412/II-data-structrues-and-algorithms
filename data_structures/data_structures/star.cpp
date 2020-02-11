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
	solidcircle(L.elems[i].x, L.elems[i].y, L.elems[i].radius);//�ޱ߿�Բ
}

void initStars(star_t& star) {
	//��������
	//����һ�������,ȷ���������ǵ���ɫ(��Ҫ��ʱ����ȫ�����rand()ǰ�����������srand(time(NULL))��time.h
	//���б���,������ɫ���
	//Ϊ��ʵ�����ǵ��ƶ�,��Ҫ�������д������ǵ���Ϣ
	star.x = rand() % SCREEN_WIDTH;
	star.y = rand() % STARS_HEIGHT;
	star.radius = rand() % MAX_RADIUS + 1;
	int whiteness = rand() % MAX_WHITENESS + 1;//����Ϊ0,Ϊ0���Ǻ�ɫ��,1-5
	int rgb = 255 * whiteness / MAX_WHITENESS;//(0,255]
	star.color = RGB(rgb, rgb, rgb);//��ֵ��ͬ��Ϊ��(��ȫΪ0Ϊ��)
}

int main() {
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);//Ĭ��640*480����
	sqlist starL;
	initSqlist(starL);
	star_t star;

	for (int i = 0; i < MAX_NUM; i++) {
		initStars(star);
		listAppend(starL, star);
	}

	for (int i = 0; i < starL.length; i++) {
		setfillcolor(starL.elems[i].color);
		solidcircle(starL.elems[i].x, starL.elems[i].y, starL.elems[i].radius);//�ޱ߿�Բ
	}

	while (starL.length) {
		for (int i = 0; i < starL.length; i++) {
			moveStars(DIR::UP, i, starL);
		}
		Sleep(50);
	}

	settextcolor(WHITE);
	RECT r = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	drawtext(_T("���ǻ���ʧ,���һ�������~"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	Sleep(1000);
	closegraph();

	listDestroy(starL);
	return 0;
}