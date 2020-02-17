#include <iostream>
using namespace std;

#define ROWS 3
#define COLS 4
bool isVisited[ROWS][COLS];
int length = 0;
const char *matrix = "ABTGCFCSJDEH" ;
bool hasPath(const char* str,int r, int c) {
	if ('\0' == str[length]) {
		return true;
	}
	bool has = false;
	if (r >= 0 && r < ROWS && c >= 0 && c < COLS &&
		matrix[r * COLS + c] == str[length] && !isVisited[r][c]) {
		isVisited[r][c] = true;
		length++;

		has =   hasPath(str, r + 1, c) || hasPath(str, r, c - 1) ||
		    	hasPath(str, r - 1, c) || hasPath(str, r, c + 1);


		if (!has) {
			length--;//全局变量记得恢复
			isVisited[r][c] = false;
		}
	}
	return has;
}
bool getPath(const char* str) {
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			if (hasPath(str, r, c))return true;
		}
	}
	return false;
}
int main() {

	const char* str = "ABTG" ;
	if (getPath(str)) {
		cout << "Found string!" << endl;
	}
	else {
		cout << "Not found!" << endl;
	}
	return 0;
}