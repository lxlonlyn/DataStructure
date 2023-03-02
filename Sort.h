#pragma once
class Sort {
public:
	Sort(int r[], int n);
	~Sort();
	void InsertSort();
	void ShellSort();
	void BubbleSort();
	void QuickSort(int first,int last);
	void SelectSort();
	void HeapSort();
	void MergeSort1(int first, int last);
	void MergeSort2();
	void Print();

private:
	int Partition(int first, int last);
	void Sift(int k, int last);
	void Merge(int first1, int last1, int last2);
	void MergePass(int h);
	int* data;
	int length;
};

Sort::Sort(int r[],int n) {
	data = new int[n];
	for (int i = 0; i < n; i++) data[i] = r[i];
	length = n;
}

Sort::~Sort() { delete[] data; }

void Sort::Print() {
	std::cout << "Sort: ";
	for (int i = 0; i < length; i++) std::cout << data[i] << " ";
	std::cout << std::endl;
}

void Sort::InsertSort() {
	int i, j, temp;
	for (i = 0; i < length; i++) {
		temp = data[i];
		for (j = i - 1; j >= 0 && temp < data[j]; j--) data[j + 1] = data[j];
		data[j + 1] = temp;
	}
}

void Sort::ShellSort() {
	int d, i, j, temp;
	for (d = length / 2; d >= 1; d /= 2) {
		for (i = d; i < length; i++) {
			temp = data[i];
			for (j = i - d; j >= 0 && temp < data[j]; j -= d)
				data[j + d] = data[j];
			data[j + d] = temp;
		}
	}
}

void Sort::BubbleSort() {
	int j, exchange, bound, temp;
	exchange = length - 1;
	while (exchange != 0) {
		bound = exchange; exchange = 0;
		for (j = 0; j < bound; j++) {
			if (data[j] > data[j + 1]) {
				temp = data[j]; data[j] = data[j + 1]; data[j + 1] = temp;
				exchange = j;
			}
		}
	}
}

int Sort::Partition(int first, int last) {
	//求轴值区间:[first,last]
	int i = first, j = last, temp;
	while (i < j) {
		while (i < j && data[i] <= data[j]) j--;
		if (i < j) {
			temp = data[i]; data[i] = data[j]; data[j] = temp;
			i++;
		}
		while (i < j && data[i] <= data[j]) i++;
		if (i < j) {
			temp = data[i]; data[i] = data[j]; data[j] = temp;
			j--;
		}
	}
	return i;
}

void Sort::QuickSort(int first, int last) {
	//排序区间:[first,last]
	if (first >= last)return;
	else {
		int pivot = Partition(first, last);
		QuickSort(first, pivot - 1);
		QuickSort(pivot + 1, last);
	}
}

void Sort::SelectSort() {
	int i, j, index, temp;
	for (i = 0; i < length - 1; i++) {
		index = i;
		for (j = i + 1; j < length; j++) 
			if (data[j] < data[index]) index = j;
		if (index != i) {
			temp = data[i]; data[i] = data[index]; data[index] = temp;
		}
	}
}

void Sort::Sift(int k,int last) {
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

void Sort::HeapSort() {
	int i, temp;
	for (i = (length+1)/ 2 - 1; i >= 0; i--) {
		Sift(i, length - 1);
	}
	for (i = 1; i < length; i++) {
		temp = data[0]; data[0] = data[length - i]; data[length - i] = temp;
		Sift(0, length - i - 1);
	}
}

void Sort::Merge(int first1, int last1, int last2) {
	//两段范围:[first1,last1)，[last1,last2)
	int i = first1, j = last1, k = first1;
	int* temp = new int[length]();
	while (i < last1 && j < last2) {
		if (data[i] <= data[j]) temp[k++] = data[i++];
		else temp[k++] = data[j++];
	}
	while (i < last1) temp[k++] = data[i++];
	while (j < last2) temp[k++] = data[j++];
	for (i = first1; i < last2; i++) data[i] = temp[i];
	delete [] temp;
}

void Sort::MergeSort1(int first, int last) {
	//排序区间:[first,last)
	int size = last - first;
	if (size == 0 || size == 1) return;
	else {
		int mid = (first + last) / 2;
		MergeSort1(first, mid);
		MergeSort1(mid, last);
		Merge(first,mid,last);
	}
}

void Sort::MergePass(int h) {
	int i = 0;
	while (i + 2 * h <= length) {
		Merge(i, i + h, i + 2 * h );
		i = i + 2 * h;
	}
	if (i + h < length) Merge(i, i + h, length);
}

void Sort::MergeSort2() {
	int h = 1;
	while (h < length) {
		MergePass(h);
		h = 2 * h;
	}
}