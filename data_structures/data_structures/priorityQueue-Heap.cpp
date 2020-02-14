#include <iostream>
#include <vld.h>
using namespace std;
//size������
//arr�±��Ǻ�0��

#define dataType QNode
#define DEFAULT_CAPACITY 50
typedef struct _QNode {
	int data;
	int priority;
}QNode;

typedef struct _Heap {
	dataType* arr = NULL;
	int size;
	int capacity;
}Heap;
#define isPrior(x, y) (x)->priority > (y).priority
#define isPrior2(x, y) (x).priority > (y).priority
#define isPrior3(x, y) (x).priority > (y)->priority

void heapInsert(Heap& H, dataType*& data) {
	if (!H.arr)return;//����ΪNULL���ռ䶼û

	if (H.size == H.capacity) {
		cerr << "Heap is full!" << endl; return;
	}
	if (H.size < 0)return;


	int cur = H.size;
	H.arr[H.size++] = *data;
	if (!H.size) {
		return;
	}
	int parent;
	for (; (cur - 1) / 2 >= 0; cur = parent) {
		parent = (cur - 1) / 2;
		if (isPrior(data, H.arr[parent])) {
			H.arr[cur] = H.arr[parent];
			H.arr[parent] = *data;
		}
		else break;
	}
}
void heapDown(Heap& H, int parent) {
	dataType cur = H.arr[parent];//��ǰ����������
	int child;
	for (; parent * 2 + 1 < H.size; parent = child) {
		child = parent * 2 + 1;
		if (child + 1 < H.size && isPrior2(H.arr[child + 1], H.arr[child])) {//ѡ�����������ĺ͸��׽���
			child++;
		}
		if (isPrior2(H.arr[child], cur)) {//���ű��������ĺ��ӵ�λ��,һ·����
			H.arr[parent] = H.arr[child];
			H.arr[child] = cur;//��û����ɽ���!!,��Ϊָ��ָ����һ��λ�������ַ(ͬ����!)
		}
		else break;
	}
}
bool popMax(Heap& H, dataType& max) {
	if (!H.arr || !H.size)return false;

	max = H.arr[0];
	H.arr[0] = H.arr[--H.size];
	//H.arr[H.size+1]��size�Ѽ�С�����ٴ�ӡ��
	heapDown(H, 0);
	return true;
}
void heapInit(Heap& H, int size) {//arr���ܴ�����??,ΪɶHeap���Ĳ���ָ����??
	H.capacity = DEFAULT_CAPACITY > size ? DEFAULT_CAPACITY : size;

	H.arr = new dataType[H.capacity];
	if (!H.arr)return;

	if (size <= 0) {
		H.size = 0;
		return;
	}

	//H.size = size;

	//��һ:ֱ�ӳ�ʼ���������µ���
	//memcpy(H.arr, arr, size * sizeof(int));

	//for (int i = 0; i < size; i++) {//��ʱarrΪָ��,sizeof(arr)=1;
	//	cout << "Num " << i << ". " << arr[i] << endl;
	//}

	//for (int i = size / 2 - 1; i >= 0; i--) {
	//	heapDown(H, i);
	//}
	//����:һ��һ������
	H.size = 0;	
	QNode* n;
	for (int i = 0; i < size; i++) {
		n = new QNode;
		n->data = i;
		n->priority = rand() % 10;
		heapInsert(H, n);
		delete n;
	}
}

int main() {
	Heap h;
	int size = 6;
	heapInit(h, size);

	cout << "Heap members:" << endl;
	for (int i = 0; i < h.size; i++) {
		cout << "Num " << i << ". " << h.arr[i].data
			<< "[" << h.arr[i].priority << "]" << endl;
	}

	cout << "After insert 6[10]:" << endl;
	QNode* n = new QNode;
	n->data = 6;
	n->priority = 10;
	heapInsert(h, n);
	delete n;
	for (int i = 0; i < h.size; i++) {
		cout << "Num " << i << ". " << h.arr[i].data
			<< "[" << h.arr[i].priority << "]" << endl;
	}

	int i = 0;
	QNode max;
	cout << "Pop max:" << endl;
	while (popMax(h, max)) {//ע��˳��!!���Ƚ���m--�ж�,����������pop max
		cout << "Num " << i++ << ". " << max.data
			<< "[" << max.priority << "]" << endl;
	}

	delete h.arr;
	return 0;
}