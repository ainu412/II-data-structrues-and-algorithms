#include <iostream>
#include <assert.h>
using namespace std;
#define DEFAULT_SIZE 16
#define MAX_LENGTH 100

typedef string ElemType;

typedef struct _SHList {
	ElemType member[MAX_LENGTH];
}SHList;

typedef struct _SHTable {//LinkedHashTable
	int size;//����ֵ����
	SHList** lists; //SHList* lists[size];ʵ��������ʵ�ֵ�,,������Ϊsize�Ǳ���,�޷�Ԥ�ȷ���,����д������,ֻ��дָ��
}SHTable;

void shInit(SHTable& H, int size) {
	if (size <= 0) {
		size = DEFAULT_SIZE;
	}
	H.size = size;
	//�ǵ÷���ָ������!!�ǵó�����Ŀ!!
	H.lists = (SHList**)calloc(size, sizeof(SHList*));//һ���Էֹ�
	if (!H.lists) {
		cerr << "Failed to malloc to lists!" << endl; return;
	}

	//����ձ�ͷλ��
	for (int l = 0; l < size; l++) {//list
		H.lists[l] = (SHList*)calloc(1, sizeof(SHList));//calloc��ʼ��Ϊ0��!!
		for (int m = 0; m < MAX_LENGTH; m++) {//member
			H.lists[l]->member[m] = "\t\0";//callocҲ������...ֻ��new����������qwq
		}
	}
}
int Hash(SHTable& H, int key) {
	if (key < 0) {
		cerr << "The value of key must be more than or equal to 0!" << endl; return 1;
	}
	return key % H.size;//��Ӧ��������ֵ(0-size-1)
}
void shInsert(SHTable& H, int key, ElemType data) {

	int i = Hash(H, key);
	int j = key / H.size;
	if (key > H.size * MAX_LENGTH) {
		cerr << "The value of key mustn't be more than " << (H.size * MAX_LENGTH) << " !"; return;
	}
	if ("\t\0" != H.lists[i]->member[j]) {
		cerr << "The key already exists!" << endl; return;
	}

	H.lists[i]->member[j] = data;
}
void shDel(SHTable& H, int key) {
	int i = Hash(H, key);
	int j = key / H.size;
	if (key > H.size* MAX_LENGTH) {
		cerr << "The value of key mustn't be more than " << (H.size * MAX_LENGTH) << " !"; return;
	}
	if ("\t\0" == H.lists[i]->member[j]) {
		cerr << "The key doesn't exist!" << endl; return;
	}

	H.lists[i]->member[j] = "\t\0";

}
ElemType retrieve(SHTable& H, int key) {
	return H.lists[Hash(H, key)]->member[key / H.size];//��NULL��Ϊ��������ָ��,dataΪvoid*
}
int main() {

	SHTable h;
	string names[] = { "larry","jessica","dogs" };
	shInit(h, 2);
	shInsert(h, 1, names[0]);
	shInsert(h, 2, names[1]);
	shInsert(h, 3, names[2]);
	shDel(h, 1);

	ElemType data;
	for (int i = 0; i < 4; i++) {
		data = retrieve(h, i);
		if (data!="\t\0") {
			cout << data << " ";//�ǵ�����ǿת�Ҳ�������(������,ֻ��ӡһ����ĸ)
		}
	}
	return 0;
}