#include <iostream>
#include <vld.h>
using namespace std;
/*
1.一次可以上 1 级台阶，也可以一次上 2 级台阶。求走 n 级台阶总共有多少种走法。
2.一根长度为 n 的金条，请把金条剪成 m 段 (m 和 n 都是整数，n>1 并且 m>1)每段金条的长度记为 k[0],k[1],…,k[m].
  请问 k[0]*k[1]*.....*k[m]可能的最大乘积是多少？

  f(2,2)=1<2
  f(3,2)=1*2<3
  f(4,2)=2*2<=4
  f(4=2*2,3)=2*1*1<4

  f(5,2)=2*3
  f(6,2)=3*3

  剪成两段的乘积永远最大:不对!,14=7*7,而7=3*4
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

	int* goldBars = new int[n + 1];//0和1的地方都存多少呢,其实可以不用存,因为>4的数没有一个除以2=0/1的,?234都不在分存自己
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
	//int walks2[n + 1];必须是常量,,

	int i = 0;

	for (; i < 3; i++) {
		walks[i] = i;
	}
	//使用循环计算
	for (; i <= n; i++) {
		walks[i] = walks[i - 1] + walks[i - 2];
	}

	//打印
	for (int i = 1; i <= n; i++) {
		cout << "ways to climb " << i << " steps:" << walks[i] << endl;
	}
	delete[] walks;
}

//将已经算好的存入数组
int main() {

	walk(5);
	goldBar(14);
	return 0;
}