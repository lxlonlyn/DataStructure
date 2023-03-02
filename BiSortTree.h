#pragma once
class BiSortTree{
public:
    BiSortTree(int a[], int n);
    ~BiSortTree() { Release(root); }
    BiNode<int>* InsertBST(int x) { return InsertBST(root, x); }
    void DeleteBST(BiNode<int>* p, BiNode<int>* f);
    BiNode<int>* SearchBST(int k) { return SearchBST(root, k); }
    void PreOrder() { PreOrder(root); }
    void InOrder() { InOrder(root); }
private:
    BiNode<int>* InsertBST(BiNode<int>* bst, int x);
    BiNode<int>* SearchBST(BiNode<int>* bst, int k);
    void Release(BiNode<int>* bst);
    void PreOrder(BiNode<int>* bst);
    void InOrder(BiNode<int>* bst);
    BiNode<int>* root;
};

BiNode<int>* BiSortTree::SearchBST(BiNode<int>* bst, int k) {
    if (bst == nullptr) return nullptr;
    if (bst->data == k) return bst;
    else if (bst->data > k) return SearchBST(bst->lchild, k);
    else return SearchBST(bst->rchild, k);
}

BiNode<int>* BiSortTree::InsertBST(BiNode<int>* bst, int x) {
    if (bst == nullptr) {
        BiNode<int>* s = new BiNode<int>;
        s->data = x;
        s->lchild = s->rchild = nullptr;
        bst = s;
    }
    else if (bst->data > x) bst->lchild = InsertBST(bst->lchild, x);
    else bst->rchild = InsertBST(bst->rchild, x);
    return bst;
}

void BiSortTree::DeleteBST(BiNode<int>* p, BiNode<int>* f) {
    if ((p->lchild == nullptr) && (p->rchild == nullptr)) {
        f->lchild = nullptr; delete p; return;
    }
    if (p->rchild == nullptr) {
        f->lchild = p->lchild; delete p; return;
    }
    if (p->lchild == nullptr) {
        f->lchild = p->rchild; delete p; return;
    }
    BiNode<int>* par = p, * s = p->rchild;
    while (s->lchild != nullptr) {
        par = s;
        s = s->lchild;
    }
    p->data = s->data;
    if (par == p)par->rchild = s->rchild;
    else par->lchild = s->rchild;
    delete s;
}

BiSortTree::BiSortTree(int a[], int n) {
    root = nullptr;
    for (int i = 0; i < n; i++) root = InsertBST(root, a[i]);
}

void BiSortTree::Release(BiNode<int>* bst) {
    if (bst == nullptr)return;
    else {
        Release(bst->lchild);
        Release(bst->rchild);
        delete bst;
    }
}

void BiSortTree::PreOrder(BiNode<int>* bst) {
    if (bst == nullptr) return;
    else {
        std::cout << bst->data << "\t";
        PreOrder(bst->lchild);
        PreOrder(bst->rchild);
    }
}

void BiSortTree::InOrder(BiNode<int>* bst) {
    if (bst == nullptr) return;
    else {
        InOrder(bst->lchild);
        std::cout << bst->data << "\t";
        InOrder(bst->rchild);
    }
}