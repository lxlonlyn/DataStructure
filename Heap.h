#pragma once
#include <iostream>
class Heap {
public:
	Heap(int* data, int n);
	void HeapSort();
	void Print();
private:
	int* data;
	int count;
	void Shift(int k, int last);
};

Heap::Heap(int* data,int n) {
	count = n;
	this->data = new int[count];
	for (int i = 0; i < count; i++) {
		this->data[i] = data[i];
	}
	HeapSort();
}

void Heap::HeapSort() {
	//½¨¶Ñ
	int i, temp;
	for (i = (count+1)/2 - 1; i >= 0; i--) {
		Shift(i, count - 1);
	}
	std::cout << "MaxHeap: ";
	Print();
	//ÅÅÐò
	for (i = 1; i < count; i++) {
		temp = data[0]; data[0] = data[count - i]; data[count - i] = temp;
		Shift(0, count - i - 1);
	}
}

void Heap::Shift(int k, int last) {
	int i, j, temp;
	i = k; j = 2 * i + 1;
	while (j <= last) {
		if (j < last && data[j] < data[j + 1]) j++;
		if (data[i] > data[j]) break;
		else {
			temp = data[i]; data[i] = data[j]; data[j] = temp;
			i = j; j = 2 * i + 1;
		}
	}
}

void Heap::Print() {
	for (int i = 0; i < count; i++) std::cout << data[i] << ' ';
	std::cout << std::endl;
}