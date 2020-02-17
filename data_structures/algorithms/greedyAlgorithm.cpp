#include <iostream>
using namespace std;

/*
����1,2,5,10,20,50,100Ԫ��ֽ�ҷֱ���c0-c6��,����Ҫ����ЩǮ��֧��kԪ,����Ҫ�ö�����ֽ��?

-1��ʾ�Ҳ���
����:������ֵ�����Ǯ
�õ���������
*/
#define N 7
int value[N] = { 1,2,5,10,20,50,100 };
int num[N]   = { 10,1,2,3,5,5,5 };

int getChange(int amount) {
	for (int i = N - 1; i >= 0; i--) {
		int c = amount / value[i];
		if (c > num[i])return -1;

		num[i] = c;
		amount -= c * value[i];

		if (!amount)return i;
	}
	return -2;
}
int main() {
	int i = getChange(184);

	if (i >= 0) {
		for (int j = N - 1; j >= i; j--) {
			cout << value[j] << " num: " << num[j] << endl;
		}
	}
	else {
		cout << "Can't pay!" << endl;
	}

	return 0;
}