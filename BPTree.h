#pragma once
const int degree = 4;
struct BPNode {
	int key[degree];
	BPNode* ptr[degree];//非叶子节点的孩子指针
	BPNode* parent;
	int cluster[degree];//叶子节点指向的磁盘簇
	int size;//节点中数据个数
	bool isLeaf;
};

class BPTree {
public:
	BPTree() { root = nullptr; }
	void Insert(int x);
private:
	BPNode* root;
};

void BPTree::Insert(int x) {
	if (root == nullptr) {
		root = new BPNode;
		root->key[0] = x;
		root->isLeaf = true;
		root->size = 1;
		root->parent = nullptr;
	}
	else {

	}
}