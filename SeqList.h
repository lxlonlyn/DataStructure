#pragma once
#include <iostream>
template <class T>
class SeqList
{
private:
	T data[MaxSize];
	int length;
public:
	SeqList();
	~SeqList() {}
	SeqList(T a[], int n);
	int Length();
	T Get(int i);
	int Locate(T x);
	void Insert(int i, T x);
	T Delete(int i);
	int Empty();
	void Print();
};

template <typename T>
SeqList<T>::SeqList() { length = 0; }

template <typename T>
SeqList<T>::SeqList(T a[], int n) 
{
	if (n > MaxSize) throw"Error";
	for (int i = 0; i < n; i++) data[i] = a[i];
	length = n;
}

template <typename T>
int SeqList<T>::Length() { return this->length; }

template <typename T>
int SeqList<T>::Empty() 
{
	if (length == 0) return 1;
	if (length != 0) return 0;
}

template <typename T>
void SeqList<T>::Print() 
{
	std::cout << "SeqList:" << ' ';
	for (int i = 0; i < length; i++) std::cout << data[i] << ' ';
	std::cout << std::endl;
}

template <typename T>
T SeqList<T>::Get(int i) 
{
	if (i < 1 || i > length) throw"Error";
	else return this->data[i - 1];
}

template <typename T>
int SeqList<T>::Locate(T x) 
{
	for (int i = 0; i < length; i++) { if (data[i] == x) return i + 1; }
	return 0;
}

template <typename T>
void SeqList<T>::Insert(int i, T x) 
{
	if (length == MaxSize) throw"Error";
	if (i < 1 || i > length + 1) throw"Error";
	for (int j = length; j >= 1; j--) data[j] = data[j - 1];
	data[i - 1] = x;
	length++;
}

template <typename T>
T SeqList<T>::Delete(int i) 
{
	T x;
	if (length == 0) throw"Error";
	if (i < 1 || i > length) throw"Error";
	x = data[i - 1];
	for (int j = i; j < length; j++) data[j - 1] = data[j];
	length--;
	return x;
}