#include <time.h>
#include "webserver_sqlist.h"

//end指测试程序结束运行的时间:60s
//超时界限:第i个5+2i秒(为了清晰看出超时时间差别)for每运行一次休眠2s??服务器不能终止运行,且休眠两面后now与end的差还是5+2i不变
//fd:file id档案id
//注意id的改变!

time_t now;

void checkTimeout(Sqlist& sqlist) {
	if (!sqlist.length) {
		return;
	}
	for (int pos = 0; pos < sqlist.length; pos++) {
		time(&now);
		if (now >= sqlist.elems[pos].timeout) {
			cout << "清除用户连接成功:";
			listPrint(sqlist, pos);
			listDel(sqlist, pos);
			pos--;//记得位置减掉1
		}
	}
}

int main() {
	time_t start, end;
	time(&start);
	end = start + 60;//60s后程序结束
	time_t last_timeout = start;

	Sqlist sqlist;
	listInit(sqlist);

	User user;
	user.fd = 0;

	//初始化并填入数据
	for (int pos = 0; pos < sqlist.size; pos++)
	{
		time(&now);
		user.fd++;
		user.timeout = now + 5 + 2 * pos;//超时5秒后的时间(假设每2s接入一个)
		
		listAppend(sqlist, user);
		listPrint(sqlist, pos);
	}

	//全部接入后1s再检查是否超时
	do {
		time(&now);
		if (now >= last_timeout + 1) {//每1s检查一次
			checkTimeout(sqlist);
		}

		time_t last_timeout = now;
	} while (now < end);


}