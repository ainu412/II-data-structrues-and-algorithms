#pragma once
#include <iostream>
using namespace std;
typedef struct _ngxQueue ngxQueue;
typedef struct _ngxQueue {
	struct _ngxQueue* pre;
	struct _ngxQueue* nxt;
}ngxQueue;

#define nqInit(Q) (Q)->nxt = Q;(Q)->pre = Q

#define isnotEmpty(Q) Q != (Q)->pre

#define nqInsert_front(Q, N) (N)->nxt = (Q)->nxt; (N)->nxt->pre = N; (Q)->nxt = N; (N)->pre = Q//�������ڴ���ٲ���,

#define nqInsert_back(Q, N) (Q)->pre->nxt = N; (N)->pre = (Q)->pre; (N)->nxt = Q; (Q)->pre = N//�Ⱥ����ȼ���,�����ڵȺ�һ��Ĳ��ü�()

#define nqHead(Q) Q->nxt 

#define nqLast(Q) Q->pre 

#define nqNxt(N) N->nxt

#define nqPre(N) N->pre

#define nqRemove(N) N->pre->nxt = N->nxt; N->nxt->pre = N->pre//; delete N

#define nqNodeP(Q, QNodeType, N) (QNodeType*)((size_t)Q - offsetof(QNodeType, N))