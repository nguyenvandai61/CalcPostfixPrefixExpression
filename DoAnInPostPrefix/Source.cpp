#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "Stack.h"

///////////////////////////////////////
// Functions
bool isOperator(char c) {
	const char* operators = "+-*/%^\0";
	int length = strlen(operators);
	for (int i = 0; i < length; i++) {
		if (operators[i] == c) {
			return true;
		}
	}
	return false;
}
int getPrecedence(char c) {
	if (c == '^') 
		return 3;
	if (c == '*' || c == '/' || c == '%')
		return 2;
	if (c == '+' || c == '-')
		return 1;
	return 0;
}

///////////////////////////////////////
// Convert
void infix2Postfix(char infix[], char postfix[], bool isPrefix = false) {
	Stack* s = new Stack();
	s->init();
	// Duyet tat ca cac ky tu trong infix
	int i = 0;
	int j = 0;
	while (infix[i] != '\0') {
		int token = infix[i];
		// Neu la alpha hoac num
		if (isalnum(token)) {
			postfix[j++] = token;
			// Tach cac so voi nhau bang ' '
			if (isOperator(infix[i + 1]) && isdigit(infix[i])) {
				postfix[j++] = ' ';
			}
		}
		else {
			// Neu la dau .
			if (token == '.') {
				postfix[j++] = token;
			}
			else
			// Neu la dau ngoac mo
			if (token == '(') {
				s->push('(');
			}

			else {
				// Neu la ngoac dong va data trong stack
				if (token == ')' && !s->isEmpty()) {
					char c;
					while ((c = s->pop()) != '(' && s->isEmpty()) {
						postfix[j++] = c;
					}
				}
				else {
					// Neu la phep tinh
						// Neu la phep tinh co muc uu tien cao hoac bang
					if (!isPrefix) {
						while (getPrecedence(token) <= getPrecedence(s->topValue())) {
							postfix[j++] = s->pop();
						}
					}
					else {
						while (getPrecedence(token) < getPrecedence(s->topValue())) {
							postfix[j++] = s->pop();
						}
					}
					s->push(token);
				}
			}
		}
		i++;
	}

	double x;
	while (!s->isEmpty())
	{
		x = s->pop();
		postfix[j++] = x;
	}

	// Ket thuc Postfix
	postfix[j] = '\0';
}

void infix2Prefix(char infix[], char prefix[]) {
	int infixLength = strlen(infix);
	// Dao chuoi
	char temp;

	for (int i = 0; i < infixLength / 2; i++) {
		temp = infix[i];
		infix[i] = infix[infixLength - 1 - i];
		infix[infixLength - 1 - i] = temp;
	}

	// Doi ngoac
	for (int i = 0; i < infixLength; i++)
		if (infix[i] == '(')
			infix[i] = ')';
		else if (infix[i] == ')')
			infix[i] = '(';
	// Chuyen sang hau to
	infix2Postfix(infix, prefix, true);

	// Dao nguoc lai
	int prefixLength = strlen(prefix);
	for (int i = 0; i < prefixLength / 2; i++) {
		temp = prefix[i];
		prefix[i] = prefix[prefixLength - 1 - i];
		prefix[prefixLength - 1 - i] = temp;
	}
}
//////////////////////////////
// Evaluate
float evaluatePostfix(char* postfix) {
	Stack* s = new Stack();
	s->init();
	char* p = &postfix[0];
	double a, b, res;

	while (*p != '\0') {
		while (*p == ' ') {
			p++;
		}
		if (isalnum(*p)) {
			// Xet truong hop so
			if (isdigit(*p))
			{
				double num = 0;
				while (isdigit(*p)) {
					num *= 10;
					num += *p - '0';
					p++;
				}
				if (*p == '.') {
					p++;
					int n = 0;
					while (isdigit(*p)) {
						n++;
						num += (*p - '0')*pow(10, -n);
						p++;
					}
				}
				p--;
				s->push(num);
			}
			// Xet la chu
			else
			{
				printf("Khong tinh duoc!!");
				return 0;
			}
		}
		// xet la toan tu
		else
		{
			a = s->pop();
			b = s->pop();

			switch (*p)
			{
			case '+':
				res = b + a;
				break;
			case '-':
				res = b - a;
				break;
			case '*':
				res = b * a;
				break;
			case '/':
				res = b / a;
				break;
			case '%':
				res = (int)b % (int)a;
				break;
			case '^':
				res = pow(b, a);
				break;
			default:
				printf("\nLoi ky tu");
				return 0;
			}
			s->push(res);
		}
		p++;
	}
	res = s->pop();
	return res;

}

float evaluatePrefix(char* prefix)
{
	Stack* s = new Stack();
	char* p;
	double a, b, res;
	int prefixLength = strlen(prefix);
	s->setTop(-1);
	p = &prefix[prefixLength - 1];

	while (p >= &prefix[0])
	{

		// Xet truong hop dau " "
		while (*p == ' ' || *p == '\t')
		{
			p--;
		}

		if (isalnum(*p)) {
			// Xet truong hop so
			if (isdigit(*p))
			{
				int i = 0;
				int product;
				double num = 0;
				// Kiem tra xem co phai so thap phan
				char* p1 = p;
				bool isReal = false;
				int nAfterDot = 0;
				while (!isOperator(*p1) && *p1 != ' ') {
					if (*p1 == '.') {
						isReal = true;
						break;
					}
					nAfterDot++;
					p1--;
				};

				// Phan thap phan
				if (isReal) {
					int n = nAfterDot;
					while (isdigit(*p)) {
						num += (*p - '0') * pow(10, -n);
						n--;
						p--;
					}
					p--;
				}

				while (isdigit(*p)) {
					product = pow(10, i++);
					num += product * (*p - '0');
					p--;
				}
				
				p++;
				s->push(num);
			}
			// Xet la chu
			else
			{
				printf("Khong the tinh duoc!");
				return 0;
			}
		}
		// xet la toan tu
		else
		{
			a = s->pop();
			b = s->pop();

			switch (*p)
			{
			case '+':
				res = a + b;
				break;
			case '-':
				res = a - b;
				break;
			case '*':
				res = a * b;
				break;
			case '/':
				res = (double)a / b;
				break;
			case '%':
				res = (int)a % (int)b;
				break;
			case '^':
				res = pow(a, b);
				break;
			default:
				printf("\nLoi ky tu");
				return 0;
			}
			s->push(res);
		}
		p--;
	}
	res = s->pop();
	return res;
}

//////////////////
// MAIN	 ////////
////////////////
int main() {
	char A[MAX], B[MAX], C[MAX], D[MAX];
	printf("Infix : ");
	//	const char* word = "2+6*9-7+5";

	//	const char* word = "4+5*3-2";
	//	const char* word = "2-3*5+4"; 
	//	const char* word = "2+3*5+4";
	//	const char* word = "5*7-4*2*3";
	//	const char* word = "4%3+3*2%5-5";
	//	const char* word = "((5+3)+31)/2+2"; 

	//	const char* word = "A+B*C-D+E";
	//const char* word = "23+3*6-19*2+6^2";
	const char* word = "23.3+4.7*2";

	printf("%s\n", word);
	// Chuyen const char ve char array
	strncpy_s(A, word, MAX);
	infix2Prefix(A, B);
	printf("Chuoi Prefix: %s\n", B);
	printf("Ket qua la %f\n", evaluatePrefix(&B[0]));

	strncpy_s(C, word, MAX);
	infix2Postfix(C, D);
	printf("Postfix: %s\n", D);
	printf("Ket qua la %f\n", evaluatePostfix(&D[0]));
}