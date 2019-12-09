#pragma once
#include <stdio.h>


#define MAX_STACK 100
#define MAX 100

template<typename T>
class Stack
{
private:
	T* data;
	int top;

public:
	Stack();
	virtual ~Stack();
	void init();
	void setTop(int n);
	int isEmpty();
	T topValue();
	void push(T data);
	T pop();
};



