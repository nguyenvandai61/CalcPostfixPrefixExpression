#include "Stack.h"



Stack::Stack() {
	top = -1;
	data = new double[MAX_STACK];
}
inline Stack::~Stack()
{
	delete data;
}
;


void Stack::init() {
	top = -1;
}

void Stack::setTop(int n) {
	top = n;
}

int Stack::isEmpty() {
	return (top == -1) ? 1 : 0;
}

double Stack::topValue() {
	return data[top];
}

void Stack::push(double n) {
	if (top == MAX_STACK - 1) {
		printf("Stack is full");
		return;
	}

	top++;
	data[top] = n;
}

double Stack::pop() {
	double ret = -1;
	if (top == -1) {
		printf("Stack is empty");
	}
	else {
		ret = data[top--];
	}
	return ret;
}

