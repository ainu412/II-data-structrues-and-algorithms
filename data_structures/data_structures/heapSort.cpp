#include <iostream>
using namespace std;
//size是正数
//arr下标是含0的

#define DEFAULT_CAPACITY 50
typedef struct _Heap {
	int* arr = NULL;
	int size;
	int capacity;
}Heap;

void heapInsert(Heap& H, int data) {
	if (!H.arr)return;//数组为NULL连空间都没

	if (H.size == H.capacity) {
		cerr << "Heap is full!" << endl; return;
	}
	if (H.size < 0)return;


	int cur = H.size;
	H.arr[H.size++] = data;
	if (!H.size) {
		return;
	}
	int parent;
	for (; (cur - 1) / 2 >= 0; cur = parent) {
		parent = (cur - 1) / 2;
		if (data > H.arr[parent]) {
			H.arr[cur] = H.arr[parent];
			H.arr[parent] = data;
		}
		else break;
	}
}
void heapDown(Heap& H, int parent) {
	int cur = H.arr[parent];//当前待调整父亲
	int child;
	for (; parent * 2 + 1 < H.size; parent = child) {
		child = parent * 2 + 1;
		if (child + 1 < H.size && H.arr[child] < H.arr[child + 1]) {//选出孩子里最大的和父亲交换
			child++;
		}
		if (H.arr[child] > cur) {//沿着被交换掉的孩子的位置,一路向下
			H.arr[parent] = H.arr[child];
			H.arr[child] = cur;
		}
		else break;
	}
}

bool heapSort(Heap& H) {
	
	if (!H.arr)return false;

	if (!H.arr || !H.size)return false;

	int tmp = H.arr[0];
	H.arr[0] = H.arr[H.size - 1];
	H.arr[H.size - 1] = tmp;
	H.size--;
	heapDown(H, 0);
	return true;
}
void heapInit(Heap& H, int* arr, int size) {//arr不能传引用??,为啥Heap传的不是指针了??
	H.arr = arr;
	if (!H.arr)return;

	if (size <= 0) {
		H.size = 0;
		return;
	}

	H.size = size;

	for (int i = size / 2 - 1; i >= 0; i--) {
		heapDown(H, i);
	}
}

int main() {
	Heap h;
	int arr[] = { 20,94,36,47,84,54,2,41 };
	int length = sizeof(arr) / sizeof(arr[0]);
	heapInit(h, arr, length);
	while (heapSort(h)){}

	cout << "After heap sort:" << endl;
	for (size_t i = 0; i < length; i++){
		cout << "Num " << i << ". " << arr[i] << endl;
	}

	return 0;
}