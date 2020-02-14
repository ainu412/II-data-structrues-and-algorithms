#include <iostream>
#include <vld.h>
using namespace std;
//size是正数
//arr下标是含0的

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
	if (!H.arr)return;//数组为NULL连空间都没

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
	dataType cur = H.arr[parent];//当前待调整父亲
	int child;
	for (; parent * 2 + 1 < H.size; parent = child) {
		child = parent * 2 + 1;
		if (child + 1 < H.size && isPrior2(H.arr[child + 1], H.arr[child])) {//选出孩子里最大的和父亲交换
			child++;
		}
		if (isPrior2(H.arr[child], cur)) {//沿着被交换掉的孩子的位置,一路向下
			H.arr[parent] = H.arr[child];
			H.arr[child] = cur;//并没有完成交换!!,因为指针指的上一个位置所存地址(同步变!)
		}
		else break;
	}
}
bool popMax(Heap& H, dataType& max) {
	if (!H.arr || !H.size)return false;

	max = H.arr[0];
	H.arr[0] = H.arr[--H.size];
	//H.arr[H.size+1]因size已减小不会再打印它
	heapDown(H, 0);
	return true;
}
void heapInit(Heap& H, int size) {//arr不能传引用??,为啥Heap传的不是指针了??
	H.capacity = DEFAULT_CAPACITY > size ? DEFAULT_CAPACITY : size;

	H.arr = new dataType[H.capacity];
	if (!H.arr)return;

	if (size <= 0) {
		H.size = 0;
		return;
	}

	//H.size = size;

	//法一:直接初始化从上至下调整
	//memcpy(H.arr, arr, size * sizeof(int));

	//for (int i = 0; i < size; i++) {//此时arr为指针,sizeof(arr)=1;
	//	cout << "Num " << i << ". " << arr[i] << endl;
	//}

	//for (int i = size / 2 - 1; i >= 0; i--) {
	//	heapDown(H, i);
	//}
	//法二:一次一个插入
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
	while (popMax(h, max)) {//注意顺序!!首先进行m--判断,若不成立再pop max
		cout << "Num " << i++ << ". " << max.data
			<< "[" << max.priority << "]" << endl;
	}

	delete h.arr;
	return 0;
}