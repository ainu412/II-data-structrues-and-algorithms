#include "expressionEvaluate-stack.h"

int calculate(int l, int op, int r) {
	switch (op) {
	case '+':
		return l + r;
		break;
	case '-':
		return l - r;
		break;
	case '*':
		return l * r;
		break;
	case '/':
		return l / r;
		break;
	default:
		break;
	}
}
bool isPrior(const int& cur, const int& last) {
	if (('*' == cur || '/' == cur) &&
		('+' == last || '-' == last))
		return true;
	else return false;
}
bool operate(string input, int& final) {
	SqStack dataS, opS;
	stackInit(dataS);
	stackInit(opS);

	int type = 0;
	int l = 0, r = 0, op = 0, result;

	for (unsigned int i = 0; i < input.length(); i++) {
		if (isspace(input[i]))continue;//跳过空白符

		//0:取左操作数,1:取运算符,2:取右操作数
		switch (type) {
		case 0:
			if (isdigit(input[i])) {
				l *= 10;
				l += input[i] - '0';
			}
			else {
				stackPush(dataS, l);
				i--;
				type = 1;
			}
			break;
		case 1:
			if ('+' == input[i] || '-' == input[i] || '*' == input[i] || '/' == input[i]) {
				if (isEmpty(opS)) {
					stackPush(opS, input[i]);
					type = 2;
					break;
				}
				if (isPrior(input[i], getTop(opS))) {
					stackPush(opS, input[i]);
					type = 2;
					r = 0;
					break;
				}
				else {
					while (!isEmpty(opS) && !isPrior(input[i],getTop(opS))) {
						stackPop(dataS, r);
						stackPop(dataS, l);
						stackPop(opS, op);
						result = calculate(l, op, r);
						stackPush(dataS, result);
					}
					stackPush(opS, input[i]);
					type = 2;
					r = 0;
					break;
				}
			}
			else if ('=' == input[i]) {
				while (!isEmpty(opS)) {
					stackPop(dataS, r);
					stackPop(dataS, l);
					stackPop(opS, op);
					result = calculate(l, op, r);
					stackPush(dataS, result);
				}
				stackPop(dataS, final);
				return true;//返回最终运算结果!
			}
			else {
				cerr << "Input operator error!" << endl;
				exit(1);
			}
		case 2:
			if (isdigit(input[i])) {
				r *= 10;
				r += input[i] - '0';
			}
			else {
				stackPush(dataS, r);
				i--;
				type = 1;
			}
			break;
		}
	}
	return false;
}

int main() {
	int final;

	string str = "12+3*6/3+4*5="; //38
	while (!operate(str, final)) {}

	cout << "Final result = " << final << endl;
	return 0;
}