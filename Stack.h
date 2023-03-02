#pragma once
#include <iostream>
#include <cmath>
class Stack {
private:
	int top;
	int data[MaxSize] = { 0 };
public:
	void PushStack(int x);
	int PopStack();
	void Print();
	Stack(int* data, int n);
	Stack();
};
Stack::Stack() {
	this->top = 0;
}
Stack::Stack(int* data, int n) {
	top = 0; 
	for (int i = 0; i < n; i++) {
		PushStack(data[i]);
	}
}
void Stack::PushStack(int x) {
	data[top]= x;
	top += 1;
}
int Stack::PopStack() {
	if (top >= 1) {
		int x = data[top - 1];
		top -= 1;
		return x;
	}
	return 0;
}
void Stack::Print() {
	std::cout << "Stack:" << ' ';
	if (top >= 1) {
		for (int i = 0; i < top; i++) {
			std::cout << data[i] << ' ';
		}
		std::cout << std::endl;
	}
}