#pragma once
template <typename T>
struct OrthNode {
	int row;
	int col;
	T data;
	OrthNode* down;
	OrthNode* right;
};
template <class T>
class OrthList {
private:
	OrthNode<T>* HA[MaxSize];
	OrthNode<T>* HB[MaxSize];
	int rows;
	int cols;
public:
	OrthList(int r, int c);
	void Insert(int a,int b,T c);
	T Delete(int a, int b);
	void Print();
	void PrintRow(int a);
	void InsertTriple(int triple[][3], int size);//三元组构造十字链表
};

template <typename T>
OrthList<T>::OrthList(int r,int c) {
	for (int i = 0; i < MaxSize; i++) {
		HA[i] = nullptr;
		HB[i] = nullptr;
	}
	rows = r;
	cols = c;
}

template <typename T>
void OrthList<T>::Insert(int a, int b, T c) {
	OrthNode<T>* newOrthNode = new OrthNode<T>;
	newOrthNode->row = a;
	newOrthNode->col = b;
	newOrthNode->data = c;
	newOrthNode->right = nullptr;
	newOrthNode->down = nullptr;
	OrthNode<T>* p = HA[a];
	OrthNode<T>* q = HB[b];
	OrthNode<T>* p0 = HA[a];
	OrthNode<T>* q0 = HB[b];
	int rowfound = 0;
	int colfound = 0;
	
	//以下注释中n为HA[a]或HB[b]插入元素之前的长度
	if (HA[a] == nullptr) { HA[a] = newOrthNode; rowfound = 1; }//HA[a]原先为空，n=0
	else if (b < HA[a]->col) {//横坐标最小，n!=0
		newOrthNode->right = HA[a];
		HA[a] = newOrthNode;
		rowfound = 1;
	}
	if (HB[b] == nullptr) { HB[b] = newOrthNode; colfound = 1; }
	else if (a < HB[b]->row) {
		newOrthNode->down = HB[b];
		HB[b] = newOrthNode;
		colfound = 1;
	}

	//横坐标最大，n=1
	if (p0 != nullptr && p->right == nullptr && b > HA[a]->col) {
		HA[a]->right = newOrthNode;
		rowfound = 1;
	}
	else {
		while (p0 != nullptr && p->right != nullptr) {
			//横坐标既不最大，也不最小，n!=0&&n!=1
			if ((b > p->col) && (b < p->right->col)) {
				newOrthNode->right = p->right;
				p->right = newOrthNode;
				rowfound = 1;
			}
			p = p->right;
		}
		if (p0 != nullptr && rowfound == 0) {//若p0为nullptr，说明HA[a]原先就为空
			if (p0->right != nullptr && p->right == nullptr) {//横坐标最大，n!=0&&n!=1
				newOrthNode->right = nullptr;
				p->right = newOrthNode;
			}
		}
	}
	
	//纵坐标最大，n=1
	if (q0 != nullptr && q->down == nullptr && a > HB[b]->row) {
		HB[b]->down = newOrthNode;
		colfound = 1;
	}
	else {
		while (q0 != nullptr && q->down != nullptr) {//纵坐标既不最大，也不最小，n!=0&&n!=1
			if ((a > q->row) && (a < q->down->row)) {
				newOrthNode->down = q->down;
				q->down = newOrthNode;
				colfound = 1;
			}
			q = q->down;
		}
		if (q0 != nullptr && colfound == 0) {
			if (q0->down != nullptr && q->down == nullptr) {//纵坐标最大，n!=0&&n!=1
				newOrthNode->down = nullptr;
				q->down = newOrthNode;
			}
		}
	}
}

template <typename T>
T OrthList<T>::Delete(int a, int b) {
	OrthNode<T>* p = HA[a];
	OrthNode<T>* q = HB[b];
	int found = 0;
	T ret = 0;//未找到即返回0 

	//更新HA[a]指向的链表
	while (p != nullptr) {
		if (HA[a]->col == b) {//HA[a]首元素即为所求
			ret = p->data;
			HA[a] = p->right;
			found = 1;
		}
		else if (p->right != nullptr)
			if(p->right->col == b) {
			ret = p->right->data;
			p->right = p->right->right;
			found = 1;
		}
		p = p->right;
	}
	//若找到该元素，继续更新HB[b]指向的链表
	if(found == 1)
		while (q != nullptr) {
			if (HB[b]->row == a) {//HB[b]首元素即为所求
				HB[b] = q->down;
			}
			else if (q->down != nullptr)
				if (q->down->row == b) {
					q->down = q->down->down;
				}
			q = q->down;
		}

	delete p;
	return ret;
}

template <typename T>
void OrthList<T>::Print() {
	std::cout << "OrthList:" << std::endl;
	OrthNode<T>* p = new OrthNode<T>;
	T matrix[MaxSize][MaxSize] = { 0 };
	for (int i = 0; i < MaxSize; i++) {
		p = HA[i];
		while (p != nullptr) {
			matrix[i][p->col] = p->data;
			p = p->right;
		}
	}
	for (int j = 0; j < rows; j++) {
		for (int k = 0; k < cols; k++) 
			std::cout << matrix[j][k] <<' ';
		std::cout << std::endl;
	}
}

template <typename T>
void OrthList<T>::PrintRow(int a) {
	OrthNode<T>* p = new OrthNode<T>;
	p = HA[a];
	while (p != nullptr) {
		std::cout << '(' << a << ',' << p->col << "):" << p->data << std::endl;
		p = p->right;
	}
}

template <typename T>
void OrthList<T>::InsertTriple(int triple[][3], int size) {
	for(int i = 0;i<size;i++)
		Insert(triple[i][0], triple[i][1], triple[i][2]);
}