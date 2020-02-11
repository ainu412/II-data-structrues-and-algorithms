#include <iostream>
#include <graphics.h>
using namespace std;

#define SCREEN_WIDTH  840//����
#define SCREEN_HEIGHT 580//����
#define MAX_RADIUS	  3//�������뾶,��
#define MAX_WHITENESS	  5//�������������
#define MAX_NUM		  100//˳������ռ�,���洢������Ǹ���
#define STARS_HEIGHT  420//����
#define STAR_STEP	  5//ÿ50ms�����ƶ�����

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
			return false;//ֻҪ��������������Ͳ��˳�
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
	//��������
	//����һ�������,ȷ���������ǵ���ɫ(��Ҫ��ʱ����ȫ�����rand()ǰ�����������srand(time(NULL))��time.h
	//���б���,������ɫ���
	//Ϊ��ʵ�����ǵ��ƶ�,��Ҫ�������д������ǵ���Ϣ
	star[i].x = rand() % SCREEN_WIDTH;
	star[i].y = rand() % STARS_HEIGHT;
	star[i].radius = rand() % MAX_RADIUS + 1;
	int whiteness = rand() % MAX_WHITENESS + 1;//����Ϊ0,Ϊ0���Ǻ�ɫ��,1-5
	int rgb = 255 * whiteness / MAX_WHITENESS;//(0,255]
	star[i].color = RGB(rgb, rgb, rgb);//��ֵ��ͬ��Ϊ��(��ȫΪ0Ϊ��)
}

int main() {
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);//Ĭ��640*480����

	for (int i = 0; i < MAX_NUM; i++) {
		initStars(i);//����
		setfillcolor(star[i].color);
		solidcircle(star[i].x, star[i].y, star[i].radius);//�ޱ߿�Բ
	}

	while (!isQuit()) {
		for (int i = 0; i < MAX_NUM; i++) {
			setfillcolor(BLACK);
			solidcircle(star[i].x, star[i].y, star[i].radius);
			moveStars(DIR::UP, i);
			setfillcolor(star[i].color);
			solidcircle(star[i].x, star[i].y, star[i].radius);//�ޱ߿�Բ
		}
		Sleep(50);
	}

	settextcolor(WHITE);
	RECT r = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	drawtext(_T("������ʧ��,���һ�������~"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	Sleep(1000);
	closegraph();
	return 0;
}