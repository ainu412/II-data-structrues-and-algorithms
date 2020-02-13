#include "nginxDoubleCirculerQueue.h"

typedef struct _nCachedFile {
	int fd;
	ngxQueue node;
}nCachedFile;

typedef struct _nOpenFileCache {
	ngxQueue expireQueue;
}nOpenFileCache;

int main() {
	nOpenFileCache* q = new nOpenFileCache;
	ngxQueue* p;

	nqInit(&q->expireQueue);
	//头插法加入节点
	for (int i = 1; i <= 3; i++) {
		nCachedFile* n = new nCachedFile;
		n->fd = i;
		nqInsert_front(&q->expireQueue, &n->node);
	}

	//遍历打印节点
	cout << "Enqueue:" << endl;
	for (p = q->expireQueue.nxt;
		 p != &q->expireQueue; p = p->nxt) {
		int i = (nqNodeP(p, nCachedFile, node))->fd;
		cout << i << " ";
	}cout << endl;

	//打印出队节点并执行出队操作(因为是头插法,故最先插入的在尾部,从尾部开始出队)
	cout << "Dequeue:" << endl;
	while (isnotEmpty(&q->expireQueue)) {
		p = q->expireQueue.pre;
		nCachedFile* tmp = nqNodeP(p, nCachedFile, node);
		cout << tmp->fd << " ";
		nqRemove(p);
		delete tmp;
	}cout << endl;

	delete q;
	return 0;
}