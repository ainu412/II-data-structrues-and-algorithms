#include <iostream>
#include <vld.h>
using namespace std;
/*
1.һ�ο����� 1 ��̨�ף�Ҳ����һ���� 2 ��̨�ס����� n ��̨���ܹ��ж������߷���
2.һ������Ϊ n �Ľ�������ѽ������� m �� (m �� n ����������n>1 ���� m>1)ÿ�ν����ĳ��ȼ�Ϊ k[0],k[1],��,k[m].
  ���� k[0]*k[1]*.....*k[m]���ܵ����˻��Ƕ��٣�

  f(2,2)=1<2
  f(3,2)=1*2<3
  f(4,2)=2*2<=4
  f(4=2*2,3)=2*1*1<4

  f(5,2)=2*3
  f(6,2)=3*3

  �������εĳ˻���Զ���:����!,14=7*7,��7=3*4
*/
void goldBar(int n) {
	if (n <= 1) {
		cerr << "Number of steps must be more than 0 !" << endl; return;
	}

	if (n < 5) {
		cout << n << "'s maximum product: " << endl;
		switch (n) {
		case 2:
			cout << 1;
			return;
		case 3:
			cout << 2;
			return;
		case 4:
			cout << 4;
			return;
		}
	}

	int* goldBars = new int[n + 1];//0��1�ĵط����������,��ʵ���Բ��ô�,��Ϊ>4����û��һ������2=0/1��,?234�����ڷִ��Լ�
	int i = 2;
	for (; i <= 4; i++) {
		goldBars[i] = i;
	}
	for (; i <= n; i++) {
		goldBars[i] = goldBars[i / 2] * goldBars[i - i / 2];
	}
	for (int i = 2; i <= n; i++) {
		cout << i << "'s maximum product: " << goldBars[i] << endl;
	}

	delete[]goldBars;
}
int walk1(int n) {
	if (n <= 0)return 0;

	if (n <= 2)return n;
	return walk1(n - 1) + walk1(n - 2);
}
void walk(int n) {
	if (n <= 0) {
		cerr << "Number of steps must be more than 0 !" << endl; return;
	}
	if (n < 3) {
		for (int i = 1; i <= n; i++) {
			cout << "ways to climb " << i << " steps:" << i << endl;
		}return;
	}
	int* walks = new int[n + 1];
	//int walks2[n + 1];�����ǳ���,,

	int i = 0;

	for (; i < 3; i++) {
		walks[i] = i;
	}
	//ʹ��ѭ������
	for (; i <= n; i++) {
		walks[i] = walks[i - 1] + walks[i - 2];
	}

	//��ӡ
	for (int i = 1; i <= n; i++) {
		cout << "ways to climb " << i << " steps:" << walks[i] << endl;
	}
	delete[] walks;
}

//���Ѿ���õĴ�������
int main() {

	walk(5);
	goldBar(14);
	return 0;
}