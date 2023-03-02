#pragma once
#include<iostream>
template <typename T>
struct BiNode {
	T data;
	BiNode<T>* lchild, * rchild;
};

template <class T>
class BiTree {
public:
	BiTree() { root = Create(); }
	BiTree(T*& ch) { root = Create(ch); }
	~BiTree() { Release(root); }
	void SubRelease(T x) { SubRelease(root,x); };
	void PreOrder() { std::cout << "BiTree:" << ' '; PreOrder(root); }
	void InOrder() { std::cout << "BiTree:" << ' '; InOrder(root); }
	void PostOrder() { std::cout << "BiTree:" << ' '; PostOrder(root); }
	void LevelOrder();
	void NRPreOrder() { std::cout << "BiTree:" << ' '; NRPreOrder(root); }
	void NRInOrder() { std::cout << "BiTree:" << ' '; NRInOrder(root); }
	void NRPostOrder() { std::cout << "BiTree:" << ' '; NRPostOrder(root); }
	BiNode<T>* Search(T x) { BiNode<T>* bt = Search(x, root); return bt; }
private:
	BiNode<T>* Create();
	BiNode<T>* Create(T*& ch);
	void Release(BiNode<T>*& bt);
	void SubRelease(BiNode<T>*& bt,T x);
	void PreOrder(BiNode<T>* bt);
	void InOrder(BiNode<T>* bt);
	void PostOrder(BiNode<T>* bt);
	void NRPreOrder(BiNode<T>* bt);
	void NRInOrder(BiNode<T>* bt);
	void NRPostOrder(BiNode<T>* bt);
	BiNode<T>* Search(T x, BiNode<T>* bt);
	BiNode<T>* root;
};

template <typename T>
BiNode<T>* BiTree<T>::Create() {
	BiNode<T>* bt = new BiNode<T>;
	char ch;
	std::cin >> ch;
	if (ch == '#') bt = nullptr;
	else {
		bt->data = ch;
		bt->lchild = Create();
		bt->rchild = Create();
	}
	return bt;
}

template <typename T>
BiNode<T>* BiTree<T>::Create(T*& ch) {
	BiNode<T>* bt = new BiNode<T>;
	if (*ch == '#') {
		bt = nullptr;
		ch += 1;
	}
	else {
		bt->data = *ch;
		ch += 1;
		bt->lchild = Create(ch);
		bt->rchild = Create(ch);
	}
	return bt;
}

template <typename T>
BiNode<T>* BiTree<T>::Search(T x,BiNode<T>* bt) {
	if (bt == nullptr)return nullptr;
	if (bt->data == x)return bt;
	else {
		Search(x, bt->lchild);
		Search(x, bt->rchild);
	}
}

template <typename T>
void BiTree<T>::Release(BiNode<T>*& bt) {
	if (bt == nullptr)return;
	else {
		Release(bt->lchild);
		Release(bt->rchild);
		delete bt;
		bt = nullptr;
	}
}

template <typename T>
void BiTree<T>::SubRelease(BiNode<T>*& bt, T x) {
	if (bt == nullptr) return;
	if (bt->data == x) Release(bt);
	else {
		SubRelease(bt->lchild, x);
		SubRelease(bt->rchild, x);
	}
}

template <typename T>
void BiTree<T>::PreOrder(BiNode<T>* bt) {
	if (bt == nullptr)return;
	else {
		std::cout << bt->data << "\t";
		PreOrder(bt->lchild);
		PreOrder(bt->rchild);
	}
}

template <typename T>
void BiTree<T>::InOrder(BiNode<T>* bt) {
	if (bt == nullptr)return;
	else {
		InOrder(bt->lchild);
		std::cout << bt->data << "\t";
		InOrder(bt->rchild);
	}
}

template <typename T>
void BiTree<T>::PostOrder(BiNode<T>* bt) {
	if (bt == nullptr) return;
	else {
		PostOrder(bt->lchild);
		PostOrder(bt->rchild);
		std::cout << bt->data << "\t";
	}
}

template <typename T>
void BiTree<T>::LevelOrder() {
	std::cout << "BiTree:" << ' ';
	BiNode<T>* Q[MaxSize], * p = nullptr;
	int front = -1, rear = -1;
	if (root == nullptr)return;
	Q[++rear] = root;
	while (front != rear) {
		p = Q[++front];
		std::cout << p->data << ' ';
		if (p->lchild != nullptr) Q[++rear] = p->lchild;
		if (p->rchild != nullptr) Q[++rear] = p->rchild;
	}
}

template <typename T>
void BiTree<T>::NRPreOrder(BiNode<T>* bt) {
	//BiNode<T>** S = new BiNode<T>*[MaxSize];
	BiNode<T>* S[MaxSize];
	int top = -1;
	while (bt != nullptr || top != -1) {
		while (bt != nullptr) {
			std::cout << bt->data << " ";//前序序列
			S[++top] = bt;
			bt = bt->lchild;
		}
		if (top != -1) {
			bt = S[top--];
			//std::cout << bt->data << " ";//中序序列
			bt = bt->rchild;
		}
	}
}

template <typename T>
void BiTree<T>::NRInOrder(BiNode<T>* bt) {
	BiNode<T>* S[MaxSize];
	int top = -1;
	while (bt != nullptr || top != -1) {
		while (bt != nullptr) {
			//std::cout << bt->data << " ";//前序序列
			S[++top] = bt;
			bt = bt->lchild;
		}
		if (top != -1) {
			bt = S[top--];
			std::cout << bt->data << " ";//中序序列
			bt = bt->rchild;
		}
	}
}

template <typename T>
void BiTree<T>::NRPostOrder(BiNode<T>* bt) {
	BiNode<T>* S[MaxSize];
	int top = -1,flag[MaxSize];
	while (top != -1 || bt != nullptr) {
		while (bt != nullptr) {
			S[++top] = bt;
			flag[top] = 1;
			bt = bt->lchild;
		}
		while (top != -1 && flag[top] == 2) {
			bt = S[top--];
			std::cout << bt->data << " ";
		}
		if (bt == root) break;
		if (top != -1) {
			flag[top] = 2;
			bt = S[top]->rchild;
		}
	}
}