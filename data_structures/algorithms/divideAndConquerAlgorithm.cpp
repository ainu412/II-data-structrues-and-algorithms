#include <iostream>
using namespace std;

int binarySearch(int* arr, int min, int max, int target) {
	int mid = (min + max) / 2;//��ֻʣ��������Ԫ��,��ֻ���Ų鵽��С��,�����һ����

	if (target == arr[mid])return mid;
	if (target == arr[mid + 1])return mid + 1;
	if (target > arr[mid])return binarySearch(arr, mid, max, target);
	return binarySearch(arr, min, mid, target);

	cerr << "Not found!" << endl;
	return -1;
}

int main() {

	int arr[5]= { 1, 3, 7, 9, 11 };
	cout << binarySearch(arr, 0, 4, 11) << endl;

	return 0;
}