#include "Stack.h"


template<typename T>
Stack<T>::Stack() {
	top = -1;
	data = new T[MAX_STACK];
}

template<typename T>
Stack<T>::~Stack()
{
	delete data;
};

template<typename T>
void Stack<T>::init() {
	top = -1;
}

template<typename T>
void Stack<T>::setTop(int n) {
	top = n;
}

template<typename T>
int Stack<T>::isEmpty() {
	return (top == -1) ? 1 : 0;
}

template<typename T>
T Stack<T>::topValue() {
	return data[top];
}

template<typename T>
void Stack<T>::push(T n) {
	if (top == MAX_STACK - 1) {
		printf("Stack is full");
		return;
	}

	top++;
	data[top] = n;
}

template<typename T>
T Stack<T>::pop() {
	double ret = -1;
	if (top == -1) {
		printf("Stack is empty");
	}
	else {
		ret = data[top--];
	}
	return ret;
}

