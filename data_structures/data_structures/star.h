#pragma once
#include <graphics.h>
#include <iostream>

using namespace std;

#define SCREEN_WIDTH  840//����
#define SCREEN_HEIGHT 580//����
#define MAX_RADIUS	  3//�������뾶,��
#define MAX_WHITENESS	  5//�������������
#define MAX_NUM		  100//˳������ռ�,���洢������Ǹ���
#define STARS_HEIGHT  420//����
#define STAR_STEP	  5//ÿ50ms�����ƶ�����

typedef struct {
	int x;
	int y;
	unsigned radius;
	int color;
}star_t;

enum class DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ALL
};

//���ǵ�˳���:
typedef struct _sqlist {
	star_t* elems;//˳���Ļ���ַ
	int size;
	int length;
}sqlist;

bool initSqlist(sqlist& s);
bool listAppend(sqlist& s, star_t e);
bool listDel(sqlist& s, int pos);
void listDestroy(sqlist& s);