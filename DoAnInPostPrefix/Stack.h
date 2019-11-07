#pragma once
#include <stdio.h>

#define MAX_STACK 100
#define MAX 100
class Stack
{
private:
	double* data;
	int top;

public:
	Stack();
	virtual ~Stack();
	void init();
	void setTop(int n);
	int isEmpty();
	double topValue();
	void push(double data);
	double pop();
};



