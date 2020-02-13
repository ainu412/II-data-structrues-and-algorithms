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
	//ͷ�巨����ڵ�
	for (int i = 1; i <= 3; i++) {
		nCachedFile* n = new nCachedFile;
		n->fd = i;
		nqInsert_front(&q->expireQueue, &n->node);
	}

	//������ӡ�ڵ�
	cout << "Enqueue:" << endl;
	for (p = q->expireQueue.nxt;
		 p != &q->expireQueue; p = p->nxt) {
		int i = (nqNodeP(p, nCachedFile, node))->fd;
		cout << i << " ";
	}cout << endl;

	//��ӡ���ӽڵ㲢ִ�г��Ӳ���(��Ϊ��ͷ�巨,�����Ȳ������β��,��β����ʼ����)
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