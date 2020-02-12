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

//���ǵĵ�������:
typedef struct _LinkNode {
	star_t data;
	struct _LinkNode* nxt;
}LinkList, LinkNode;

void listInit(LinkList*& linkList);
void listInsert_back(LinkList*& linkList, LinkNode* linkNode);
void listDel(LinkList*& linkList, int pos);
void listDestroy(LinkList*& linklist);