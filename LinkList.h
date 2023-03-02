#pragma once
#include <iostream>
template <typename T>
struct Node
{
	T data;
	Node<T>* next;
};

template <class T>
class LinkList
{
private:
	Node<T>* first;
public:
	LinkList();
	~LinkList();
	LinkList(T a[],int n);
	int Length();
	T Get(int i);
	int Locate(T x);
	void Insert(int i, T x);
	T Delete(int i);
	int Empty();
	void Print();
};

template <typename T>
LinkList<T>::LinkList() 
{
	first = new Node<T>;
	first->next = nullptr;
}

template <typename T>
LinkList<T>::~LinkList() 
{
	Node<T>* p = first;
	while (first != nullptr)
	{
		first = first->next;
		delete p;
		p = first;
	}
}

template <typename T>
int LinkList<T>::Empty() 
{
	if (first->next == nullptr)return 1;
	if (first->next != nullptr)return 0;
}

template <typename T>
void LinkList<T>::Print() 
{
	std::cout << "LinkList:" << ' ';
	Node<T>* p = first->next;
	while (p != nullptr) 
	{
		std::cout << p->data << ' ';
		p = p->next;
	}
	std::cout << std::endl;
}

template <typename T>
int LinkList<T>::Length() 
{
	Node<T>* p = first->next;
	int count = 0;
	while (p != nullptr) 
	{
		p = p->next;
		count++;
	}
	return count;
}

template <typename T>
T LinkList<T>::Get(int i) 
{
	Node<T>* p = first->next;
	int count = 1;
	while (p != nullptr && count < i) 
	{
		p = p->next;
		count++;
	}
	if (p == nullptr) throw"Error";
	else return p->data;
}

template <typename T>
int LinkList<T>::Locate(T x) 
{
	Node<T>* p = first->next;
	int count = 1;
	while (p != nullptr)
	{
		if (p->data == x)return count;
		p = p->next;
		count++;
	}
	return 0;
}

template <typename T>
void LinkList<T>::Insert(int i,T x) 
{
	Node<T>* p = first, *s = nullptr;
	int count = 0;
	while (p != nullptr && count < i - 1) 
	{
		p = p->next;
		count++;
	}
	if (p == nullptr) throw"Error";
	else 
	{
		s = new Node<T>;
		s->data = x;
		s->next = p->next;
		p->next = s;
	}
}

//ͷ�巨
//template <typename T>
//LinkList<T>::LinkList(T a[], int n) 
//{
//	first = new Node<T>;
//	first->next = nullptr;
//	for (int i = 0; i < n; i++) 
//	{
//		Node<T>* s = nullptr;
//		s = new Node<T>;
//		s->data = a[i];
//		s->next = first->next;
//		first->next = s;
//	}
//}

//β�巨
template <typename T>
LinkList<T>::LinkList(T a[], int n)
{
	first = new Node<T>;
	Node<T>* r = first, * s = nullptr;
	for (int i = 0; i < n; i++)
	{
		s = new Node<T>;
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = nullptr;
}

template <typename T>
T LinkList<T>::Delete(int i) 
{
	T x;
	Node<T>* p = first, * q = nullptr;
	int count = 0;
	while (p != nullptr && count < i - 1)
	{
		p = p->next;
		count++;
	}
	if (p == nullptr || p->next == nullptr) throw"Error";
	else 
	{
		q = p->next; x = q->data;
		p->next = q->next;
		delete q;
		return x;
	}
}