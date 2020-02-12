#include <time.h>
#include "webserver_sqlist.h"

//endָ���Գ���������е�ʱ��:60s
//��ʱ����:��i��5+2i��(Ϊ������������ʱʱ����)forÿ����һ������2s??������������ֹ����,�����������now��end�Ĳ��5+2i����
//fd:file id����id
//ע��id�ĸı�!

time_t now;

void checkTimeout(Sqlist& sqlist) {
	if (!sqlist.length) {
		return;
	}
	for (int pos = 0; pos < sqlist.length; pos++) {
		time(&now);
		if (now >= sqlist.elems[pos].timeout) {
			cout << "����û����ӳɹ�:";
			listPrint(sqlist, pos);
			listDel(sqlist, pos);
			pos--;//�ǵ�λ�ü���1
		}
	}
}

int main() {
	time_t start, end;
	time(&start);
	end = start + 60;//60s��������
	time_t last_timeout = start;

	Sqlist sqlist;
	listInit(sqlist);

	User user;
	user.fd = 0;

	//��ʼ������������
	for (int pos = 0; pos < sqlist.size; pos++)
	{
		time(&now);
		user.fd++;
		user.timeout = now + 5 + 2 * pos;//��ʱ5����ʱ��(����ÿ2s����һ��)
		
		listAppend(sqlist, user);
		listPrint(sqlist, pos);
	}

	//ȫ�������1s�ټ���Ƿ�ʱ
	do {
		time(&now);
		if (now >= last_timeout + 1) {//ÿ1s���һ��
			checkTimeout(sqlist);
		}

		time_t last_timeout = now;
	} while (now < end);


}