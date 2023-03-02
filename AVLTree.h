#pragma once
template <typename T>
struct AVLNode {
	T data;
	AVLNode<T>* lchild, * rchild;
	int factor;//平衡因子
};

class AVLTree {
public:
	AVLTree(int a[], int n);
	~AVLTree() { Release(root); }
	AVLNode<int>* Insert(int x) { return Insert(root, x); }
	void Delete(AVLNode<int>* p, AVLNode<int>* f);
	AVLNode<int>* Search(int k) { return Search(root, k); }
	void PreOrder() { std::cout << "AVLTree:" << ' '; PreOrder(root); std::cout << std::endl; }
	void InOrder() { std::cout << "AVLTree:" << ' '; InOrder(root); std::cout << std::endl; }
private:
	AVLNode<int>* Insert(AVLNode<int>* avlt, int x);
	AVLNode<int>* Search(AVLNode<int>* avlt, int k);
	void Release(AVLNode<int>* avlt);
	void PreOrder(AVLNode<int>* avlt);
	void InOrder(AVLNode<int>* avlt);
	int Depth(AVLNode<int>* avlt);
	int getFactor(AVLNode<int>* avlt);
	void refreshFactors(AVLNode<int>*& avlt);
	void FactorIsTwo(AVLNode<int>*& avlt, AVLNode<int>*& p);
	void getFather(AVLNode<int>*& avlt, AVLNode<int>*& f, int x);
	void LLAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f);
	void RRAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f);
	void LRAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f);
	void RLAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f);
	void treeAdjust(AVLNode<int>*& avlt);
	AVLNode<int>* root;
};


AVLTree::AVLTree(int a[], int n) {
	root = nullptr;
	for (int i = 0; i < n; i++) { root = Insert(root, a[i]); treeAdjust(root); }
}

void AVLTree::Release(AVLNode<int>* avlt) {
	if (avlt == nullptr)return;
	else {
		Release(avlt->lchild);
		Release(avlt->rchild);
		delete avlt;
	}
}

void AVLTree::PreOrder(AVLNode<int>* avlt) {
	if (avlt == nullptr) return;
	else {
		std::cout << avlt->data << " ";
		PreOrder(avlt->lchild);
		PreOrder(avlt->rchild);
	}
}

void AVLTree::InOrder(AVLNode<int>* avlt) {
	if (avlt == nullptr) return;
	else {
		InOrder(avlt->lchild);
		std::cout << avlt->data << " ";
		InOrder(avlt->rchild);
	}
}

AVLNode<int>* AVLTree::Search(AVLNode<int>* avlt, int k) {
	if (avlt == nullptr) return nullptr;
	if (avlt->data == k) return avlt;
	else if (avlt->data > k) return Search(avlt->lchild, k);
	else return Search(avlt->rchild, k);
}

AVLNode<int>* AVLTree::Insert(AVLNode<int>* avlt, int x) {
	if (avlt == nullptr) {
		AVLNode<int>* s = new AVLNode<int>;
		s->data = x;
		s->lchild = s->rchild = nullptr;
		avlt = s;
	}
	else if (avlt->data > x) avlt->lchild = Insert(avlt->lchild, x);
	else avlt->rchild = Insert(avlt->rchild, x);
	return avlt;
}

void AVLTree::Delete(AVLNode<int>* p, AVLNode<int>* f) {
	if ((p->lchild == nullptr) && (p->rchild == nullptr)) {
		f->lchild = nullptr; delete p; return;
	}
	if (p->rchild == nullptr) {
		f->lchild = p->lchild; delete p; return;
	}
	if (p->lchild == nullptr) {
		f->lchild = p->rchild; delete p; return;
	}
	AVLNode<int>* par = p, * s = p->rchild;
	while (s->lchild != nullptr) {
		par = s;
		s = s->lchild;
	}
	p->data = s->data;
	if (par == p)par->rchild = s->rchild;
	else par->lchild = s->rchild;
	delete s;
}

int AVLTree::Depth(AVLNode<int>* avlt){
	if (avlt == nullptr) return 0;
	else {
		int m = Depth(avlt->lchild);
		int n = Depth(avlt->rchild);
		if (m > n) return m + 1;
		else return n + 1;
	}
}
//求树中节点的平衡因子
int AVLTree::getFactor(AVLNode<int>* avlt){
	int m = 0, n = 0;
	if (avlt != nullptr){
		m = Depth(avlt->lchild);
		n = Depth(avlt->rchild);
	}
	return m - n;
}
//刷新树中的每个节点的平衡因子
void AVLTree::refreshFactors(AVLNode<int>*& avlt){
	if (avlt != nullptr){
		avlt->factor = getFactor(avlt);
		refreshFactors(avlt->lchild);
		refreshFactors(avlt->rchild);
	}
}
//获得平衡因子为2或-2的节点
void AVLTree::FactorIsTwo(AVLNode<int>*& avlt, AVLNode<int>*& p){
    if (avlt != nullptr){
		if (avlt->factor == 2 || avlt->factor == -2) {
			p = avlt;
		}
        FactorIsTwo(avlt->lchild, p);
        FactorIsTwo(avlt->rchild, p);
    }
}
//找到数据为x的结点的父节点并存储在f中
void AVLTree::getFather(AVLNode<int>*& avlt, AVLNode<int>*& f, int x){
	if (avlt != nullptr){
		if (avlt->lchild != nullptr){
			if (avlt->lchild->data == x) f = avlt;
		}
		if (avlt->rchild != nullptr){
			if (avlt->rchild->data == x) f = avlt;
		}
		getFather(avlt->lchild, f, x);
		getFather(avlt->rchild, f, x);
	}
}
//LL调整
void AVLTree::LLAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f){
    AVLNode<int>* r;
    if (avlt == p){				//根节点即为最小不平衡子树的根节点
        avlt = p->lchild;        //将p的左孩子提升为新的根节点
        r = avlt->rchild;
        avlt->rchild = p;        //将p降为其左孩子的右孩子
        p->lchild = r;			//将p原来的左孩子的右孩子连接其p的左孩子
    }
    else {//最小不平衡子树的根节点不是根节点
        if (f->lchild == p){    //f的左孩子是p
            f->lchild = p->lchild;        //将p的左孩子提升为新的根节点
            r = f->lchild->rchild;			//交换
            f->lchild->rchild = p;        //将p降为其左孩子的右孩子
            p->lchild = r;        //将p原来的左孩子的右孩子连接其p的左孩子
        }
        if (f->rchild == p){    //f的右孩子是p
            f->rchild = p->lchild;        //将p的左孩子提升为新的根节点
            r = f->rchild->rchild;			//交换
            f->rchild->rchild = p;        //将p降为其左孩子的右孩子
            p->lchild = r;        //将p原来的左孩子的右孩子连接其p的左孩子
        }
    }
}
//LR调整
void AVLTree::LRAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f) {
    AVLNode<int>* l, * r;
    if (avlt == p){					//avlt->factor==2 && avlt->lchild->factor!=2
        avlt = p->lchild->rchild;    //将p的左孩子的右孩子提升为新的根节点
        r = avlt->rchild;
        l = avlt->lchild;
        avlt->rchild = p;
        avlt->lchild = p->lchild;
        avlt->lchild->rchild = l;
        avlt->rchild->lchild = r;
    }
    else {
        if (f->rchild == p){    //f的右孩子是p
            f->rchild = p->lchild->rchild;    //将p的左孩子的右孩子提升为新的根节点
            r = f->rchild->rchild;
            l = f->rchild->lchild;
            f->rchild->rchild = p;
            f->rchild->lchild = p->lchild;
            f->rchild->lchild->rchild = l;
            f->rchild->rchild->lchild = r;
        }
        if (f->lchild == p) {     //f的左孩子是p
            f->lchild = p->lchild->rchild;    //将p的左孩子的右孩子提升为新的根节点
            r = f->lchild->rchild;
            l = f->lchild->lchild;
            f->lchild->rchild = p;
            f->lchild->lchild = p->lchild;
            f->lchild->lchild->rchild = l;
            f->lchild->rchild->lchild = r;
        }
    }
}
//RL调整
void AVLTree::RLAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f){
    AVLNode<int>* l, * r;
    if (avlt == p) {           //avlt->factor==-2 && avlt->rchild->factor!=-2
        avlt = p->rchild->lchild;
        r = avlt->rchild;
        l = avlt->lchild;
        avlt->lchild = p;
        avlt->rchild = p->rchild;
        avlt->lchild->rchild = l;
        avlt->rchild->lchild = r;
    }
    else {
        if (f->rchild == p){    //f的右孩子是p
            f->rchild = p->rchild->lchild;
            r = f->rchild->rchild;
            l = f->rchild->lchild;
            f->rchild->lchild = p;
            f->rchild->rchild = p->rchild;
            f->rchild->lchild->rchild = l;
            f->rchild->rchild->lchild = r;
        }
        if (f->lchild == p){     //f的左孩子是p
            f->lchild = p->rchild->lchild;
            r = f->lchild->rchild;
            l = f->lchild->lchild;
            f->lchild->lchild = p;
            f->lchild->rchild = p->rchild;
            f->lchild->lchild->rchild = l;
            f->lchild->rchild->lchild = r;
        }
    }
}
//RR调整
void AVLTree::RRAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f) {
    AVLNode<int>* l;
    if (avlt == p) {             //avlt->factor==-2 && avlt->rchild->factor!=-2
        avlt = p->rchild;        //将p的右孩子提升为新的根节点
        l = avlt->lchild;
        avlt->lchild = p;        //将p降为其右孩子的左孩子
        p->rchild = l;        //将p原来的右孩子的左孩子连接其p的右孩子
    //注意:p->rchild->factor==0插入节点时用不上，删除节点时可用
    }
    else {
        if (f->rchild == p){     //f的右孩子是p
            f->rchild = p->rchild;        //将P的右孩子提升为新的根节点
            l = f->rchild->lchild;
            f->rchild->lchild = p;        //将p降为其右孩子的左孩子
            p->rchild = l;        //将p原来的右孩子的左孩子连接其p的右孩子
        }
        if (f->lchild == p){     //f的左孩子是p
            f->lchild = p->rchild;        //将p的左孩子提升为新的根节点
            l = f->lchild->lchild;
            f->lchild->lchild = p;        //将p降为其左孩子的左孩子
            p->rchild = l;        //将p原来的右孩子的左孩子连接其p的右孩子
        }
    }
}

void AVLTree::treeAdjust(AVLNode<int>*& avlt){
	AVLNode<int>* f = nullptr, * p = nullptr;
	refreshFactors(avlt);
	FactorIsTwo(avlt, p);
	if(p != nullptr) getFather(avlt,f, p->data);
	while (p != nullptr){
		refreshFactors(avlt);
		if (p->factor == 2 && (p->lchild->factor == 1 || p->lchild->factor == 0)) {
			LLAdjust(avlt, p, f);
			refreshFactors(avlt);
		}
		else if (p->factor == 2 && p->lchild->factor == -1){
			LRAdjust(avlt, p, f);
			refreshFactors(avlt);
		}
		else if (p->factor == -2 && p->rchild->factor == 1){
			RLAdjust(avlt, p, f);
			refreshFactors(avlt);
		}
		else if (p->factor == -2 && (p->rchild->factor == -1 || p->rchild->factor == 0)){
			RRAdjust(avlt, p, f);
			refreshFactors(avlt);
		}
		f = nullptr;
		p = nullptr;
		FactorIsTwo(avlt, p);
		if (p != nullptr) getFather(avlt, f, p->data);
	}
}