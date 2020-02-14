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
bool popMax(Heap& H, int& max) {
	if (!H.arr || !H.size)return false;

	max = H.arr[0];
	H.arr[0] = H.arr[--H.size];
	//H.arr[H.size+1]因size已减小不会再打印它
	heapDown(H, 0);
	return true;
}
void heapInit(Heap& H, int* arr, int size) {//arr不能传引用??,为啥Heap传的不是指针了??
	H.capacity = DEFAULT_CAPACITY > size ? DEFAULT_CAPACITY : size;

	H.arr = new int[H.capacity];
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
	for (int i = 0; i < size; i++) {
		heapInsert(H, i * 10 + 10);
	}
}

int main() {
	Heap h;
	int arr[] = { 20,94,36,47,84,54,2,41 };
	int length = sizeof(arr) / sizeof(arr[0]);
	int size = 6;
	heapInit(h, arr, size);

	cout << "Heap members:" << endl;
	for (int i = 0; i < h.size; i++){
		cout << "Num " << i << ". " << h.arr[i] << endl;
	}

	cout << "After insert 86:" << endl;
	int data = 86;
	heapInsert(h, data);
	for (int i = 0; i < h.size; i++) {
		cout << "Num " << i << ". " << h.arr[i] << endl;
	}

	cout << "Pop max:" << endl;
	int max;
	int m = 2;

	while(m-- > 0 && popMax(h, max))//注意顺序!!首先进行m--判断,若不成立再pop max
		cout << max << " ";


	cout << endl << "After pop two max:" << endl;
	for (int i = 0; i < h.size; i++) {
		cout << "Num " << i << ". " << h.arr[i] << endl;
	}
	return 0;
}