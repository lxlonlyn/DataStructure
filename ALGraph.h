#pragma once
#include <iostream>
#include <stack>
//邻接表，无向图
struct EdgeNode {//边表结点，邻接表链表项
	int adjvex; //终点在adjlist中的索引(起点为链表表头在adjlist中的索引)
	//逆邻接表中adjvex为起点
	int weight; //带权图使用
	EdgeNode* next;
	EdgeNode* last; //逆邻接表使用
};

template <typename T>
struct VertexNode {//顶点表结点，邻接表表头项
	T vertex; //顶点名称，例如A,B,C
	EdgeNode* firstEdge;//链表头结点指向链表第一项
	EdgeNode* firstTail;//逆邻接表用
	int in;//入度，拓扑排序用
};

template <class T>
class ALGraph {
public:
	ALGraph(T a[], int n, int e, int edgedata[][2], int digraph);//无权图
	ALGraph(T a[], int n, int e, int edgedata[][3], int digraph);//带权图
	~ALGraph();
	void DFTraverseNR(int v);
	void DFTraverse(int v) { 
		std::cout << "Graph:" << ' '; 
		__DFTraverse(v); 
		RestoreVisit(); 
	}
	void BFTraverse(int v) {
		std::cout << "Graph:" << ' ';
		__BFTraverse(v);
		RestoreVisit();
	}
	MGraph<T>* AL2M();
private:
	void __ALGraph(T a[], int n, int e, int edgedata[][2]);
	void __DALGraph(T a[], int n, int e, int edgedata[][2]);
	void __WALGraph(T a[], int n, int e, int edgedata[][3]);
	void __WDALGraph(T a[], int n, int e, int edgedata[][3]);
	void __DFTraverse(int v);
	void __BFTraverse(int v);
	void RestoreVisit();
	T data[MaxVertex];//存顶点名称，例如A,B,C
	VertexNode<T> adjlist[MaxVertex];//邻接表表头数组
	int vertexNum, edgeNum;//图属性，顶点数、边数
	int visited[MaxVertex] = { 0 };
};

template <typename T>
ALGraph<T>::ALGraph(T a[], int n, int e, int edges[][2], int digraph) {
	if (digraph == 0) __ALGraph(a, n, e, edges);
	if (digraph == 1) __DALGraph(a, n, e, edges);
}

template <typename T>
ALGraph<T>::ALGraph(T a[], int n, int e, int edges[][3], int digraph) {
	if (digraph == 0) __WALGraph(a, n, e, edges);
	if (digraph == 1) __WDALGraph(a, n, e, edges);
}

template <typename T>
void ALGraph<T>::__ALGraph(T a[], int n, int e, int edges[][2]) {
	int i, j;
	vertexNum = n; edgeNum = e;
	for (int m = 0; m < vertexNum; m++) {
		adjlist[m].vertex = a[m];
		this->data[m] = a[m];
		adjlist[m].firstEdge = nullptr;
	}
	for (int k = 0; k < edgeNum; k++) {
		i = edges[k][0];
		j = edges[k][1];
		EdgeNode* s = new EdgeNode;
		s->adjvex = j;
		s->next = adjlist[i].firstEdge;
		s->weight = 1;
		adjlist[i].firstEdge = s;
		EdgeNode* t = new EdgeNode;
		t->adjvex = i;
		t->next = adjlist[j].firstEdge;
		t->weight = 1;
		adjlist[j].firstEdge = t;
	}
}

template <typename T>
void ALGraph<T>::__DALGraph(T a[], int n, int e, int edges[][2]) {
	int i, j, k;
	EdgeNode* s = nullptr;
	vertexNum = n; edgeNum = e;
	for (int m = 0; m < vertexNum; m++) {
		adjlist[m].vertex = a[m];
		data[m] = a[m];
		adjlist[m].firstEdge = nullptr;
	}
	for (k = 0; k < edgeNum; k++) {
		i = edges[k][0];
		j = edges[k][1];
		s = new EdgeNode;
		s->adjvex = j;
		s->weight = 1;
		s->next = adjlist[i].firstEdge;
		s->last = adjlist[j].firstTail;
		adjlist[i].firstEdge = s;
		adjlist[j].firstTail = s;
	}
}

template <typename T>
void ALGraph<T>::__WALGraph(T a[], int n, int e, int edges[][3]) {
	int i, j, w;
	vertexNum = n; edgeNum = e;
	for (int m = 0; m < vertexNum; m++) {
		adjlist[m].vertex = a[m];
		this->data[m] = a[m];
		adjlist[m].firstEdge = nullptr;
	}
	for (int k = 0; k < edgeNum; k++) {
		i = edges[k][0];
		j = edges[k][1];
		w = edges[k][2];
		EdgeNode* s = new EdgeNode;
		s->adjvex = j;
		s->next = adjlist[i].firstEdge;
		s->weight = w;
		adjlist[i].firstEdge = s;
		EdgeNode* t = new EdgeNode;
		t->adjvex = i;
		t->next = adjlist[j].firstEdge;
		t->weight = w;
		adjlist[j].firstEdge = t;
	}
}

template <typename T>
void ALGraph<T>::__WDALGraph(T a[], int n, int e, int edges[][3]) {
	int i, j, k, w;
	EdgeNode* s = nullptr;
	vertexNum = n; edgeNum = e;
	for (int m = 0; m < vertexNum; m++) {
		adjlist[m].vertex = a[m];
		data[m] = a[m];
		adjlist[m].firstEdge = nullptr;
	}
	for (k = 0; k < edgeNum; k++) {
		i = edges[k][0];
		j = edges[k][1];
		w = edges[k][2];
		s = new EdgeNode;
		s->adjvex = j;
		s->weight = w;
		s->next = adjlist[i].firstEdge;
		s->last = adjlist[j].firstTail;
		adjlist[i].firstEdge = s;
		adjlist[j].firstTail = s;
	}
}

template <typename T>
ALGraph<T>::~ALGraph() {
	EdgeNode* p = nullptr, * q = nullptr;
	for (int i = 0; i < vertexNum; i++) {
		p = q = adjlist[i].firstEdge;
		while (p != nullptr) {
			p = p->next;
			delete q;
			q = p;
		}
	}
}

template <typename T>
void ALGraph<T>::RestoreVisit() {
	for (int i = 0; i < MaxVertex; i++) visited[i] = 0;
}

template <typename T>
void ALGraph<T>::__DFTraverse(int v) {
	int j;
	EdgeNode* p = nullptr;
	std::cout << adjlist[v].vertex << " ";
	visited[v] = 1;
	p = adjlist[v].firstEdge;
	while (p != nullptr) {
		j = p->adjvex;
		if (visited[j] == 0)__DFTraverse(j);
		p = p->next;
	}
}

template<typename T>
void ALGraph<T>::__BFTraverse(int v) {
	int Q[MaxSize], j = v, rear = -1, front = -1;
	std::cout << adjlist[j].vertex << ' ';
	visited[j] = 1;
	Q[++rear] = j;
	EdgeNode* p = nullptr;
	while (front != rear) {
		j = Q[++front]; p = adjlist[j].firstEdge;
		while (p != nullptr) {
			j = p->adjvex;
			if (visited[j] == 0) {
				std::cout << adjlist[j].vertex << " ";
				visited[j] = 1;
				Q[++rear] = j;
			}
			else p = p->next;
		}
	}
}

template<typename T>
void ALGraph<T>::DFTraverseNR(int v) {//v与p要成对更新
	int top = -1, S[MaxSize];
	EdgeNode* p = adjlist[v].firstEdge;
	while (top != -1 || p != nullptr) {
		if (visited[v] == 0) {
			std::cout << adjlist[v].vertex << ' ';
			visited[v] = 1; 
			S[++top] = v;
			if (p != nullptr) {
				v = p->adjvex;
				p = adjlist[v].firstEdge;
			}
		}
		else {
			while (p != nullptr) {
				p = p->next;//此段时间v不变
				if (p != nullptr && visited[p->adjvex] == 0) {
					S[++top] = v;//还有结点可访问，因此要再次入栈
					v = p->adjvex;
					p = adjlist[v].firstEdge;
					break;
				}
			}
		}
		if (p == nullptr && top != -1) { 
			v = S[top--]; 
			p = adjlist[v].firstEdge; 
		}
	}
}

template <typename T>
MGraph<T>* ALGraph<T>::AL2M() {
	EdgeNode* p = new EdgeNode{ 0, 0, nullptr };//工作指针，用于遍历邻接表
	int matrix[MaxVertex][MaxVertex] = { 0 };
	for (int j = 0; j < vertexNum; j++)
		for (int k = 0; k < vertexNum; k++) {
			if (j == k)matrix[j][k] = 0;//自己到自己，距离为0
			else matrix[j][k] = MAX;//不可达
		}
	for (int i = 0; i < vertexNum; i++) {
		if (adjlist[i].firstEdge != nullptr) {
			p = adjlist[i].firstEdge;
			matrix[i][p->adjvex] = p->weight;
		}
		while (p != nullptr && p->next != nullptr) {
			matrix[i][p->next->adjvex] = p->weight;
			p = p->next;
		}
	}
	MGraph<T>* mg = new MGraph<T>(this->data, this->vertexNum, this->edgeNum, matrix);
	return mg;
}