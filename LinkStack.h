#pragma once
template <typename T>
struct StackNode {
	T data;
	StackNode<T>* next;
};

template <class T>
class LinkStack {
public:
	LinkStack();
	~LinkStack();
	void Push(T x);
	T Pop();
	void Print();
private:
	StackNode<T>* top;
};

template <typename T>
LinkStack<T>::LinkStack() {
	top = nullptr;
}

template <typename T>
LinkStack<T>::~LinkStack() {
	StackNode<T>* p = new StackNode<T>;
	while (top != nullptr) {
		p = top;
		top = top->next;
		delete p;
	}
}

template <typename T>
void LinkStack<T>::Push(T x) {
	StackNode<T>* p = new StackNode<T>;
	p->data = x;
	p->next = top;
	top = p;
}

template <typename T>
T LinkStack<T>::Pop() {
	StackNode<T>* p = top;
	T x = p->data;
	top = p->next;
	return x;
}

template <typename T>
void LinkStack<T>::Print() {
	StackNode<T>* p = top;
	while (p != nullptr) {
		std::cout << p->data << std::endl;
		p = p->next;
	}
}