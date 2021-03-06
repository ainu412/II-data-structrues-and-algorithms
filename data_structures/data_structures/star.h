#pragma once
#include <graphics.h>
#include <iostream>

using namespace std;

#define SCREEN_WIDTH  840//不含
#define SCREEN_HEIGHT 580//不含
#define MAX_RADIUS	  3//星星最大半径,含
#define MAX_WHITENESS	  5//星星最大亮度数
#define MAX_NUM		  100//顺序表最大空间,即存储最多星星个数
#define STARS_HEIGHT  420//不含
#define STAR_STEP	  5//每50ms星星移动距离

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

//星星的单向链表:
typedef struct _LinkNode {
	star_t data;
	struct _LinkNode* nxt;
}LinkList, LinkNode;

void listInit(LinkList*& linkList);
void listInsert_back(LinkList*& linkList, LinkNode* linkNode);
void listDel(LinkList*& linkList, int pos);
void listDestroy(LinkList*& linklist);