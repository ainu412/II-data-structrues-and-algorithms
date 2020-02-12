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
			solidcircle(p->data.x, p->data.y, p->data.radius);//�ޱ߿�Բ
			p = p->nxt;
			i++;
		}
	}
}

void initStars(LinkNode* & node) {
	node = new LinkNode;
	//��������
	//����һ�������,ȷ���������ǵ���ɫ(��Ҫ��ʱ����ȫ�����rand()ǰ�����������srand(time(NULL))��time.h
	//���б���,������ɫ���
	//Ϊ��ʵ�����ǵ��ƶ�,��Ҫ�������д������ǵ���Ϣ
	node->data.x = rand() % SCREEN_WIDTH;
	node->data.y = rand() % STARS_HEIGHT;
	node->data.radius = rand() % MAX_RADIUS + 1;
	int whiteness = rand() % MAX_WHITENESS + 1;//����Ϊ0,Ϊ0���Ǻ�ɫ��,1-5
	int rgb = 255 * whiteness / MAX_WHITENESS;//(0,255]
	node->data.color = RGB(rgb, rgb, rgb);//��ֵ��ͬ��Ϊ��(��ȫΪ0Ϊ��)
	setfillcolor(node->data.color);
	solidcircle(node->data.x, node->data.y, node->data.radius);//�ޱ߿�Բ
}

int main() {
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);//Ĭ��640*480����
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
	drawtext(_T("���ǻ���ʧ,���һ�������~"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	Sleep(1000);
	closegraph();

	listDestroy(starL);
	return 0;
}