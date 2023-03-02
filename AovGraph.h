#pragma once
#include <iostream>
template <class T>
class AovGraph {
public:
	AovGraph(T a[], int n, int e, int edges[][2]);
	void TopSort();
private:
	VertexNode<T> adjlist[MaxVertex];
	int vertexNum, edgeNum;
};


template <typename T>
AovGraph<T>::AovGraph(T a[], int n, int e, int edges[][2]) {
	int i, j, k;
	EdgeNode* s = nullptr,* t = nullptr;
	vertexNum = n; edgeNum = e;
	for (int m = 0; m < vertexNum; m++) {
		adjlist[m].vertex = a[m];
		adjlist[m].firstEdge = nullptr;
		adjlist[m].firstTail = nullptr;
		adjlist[m].in = 0;
	}
	for (k = 0; k < edgeNum; k++) {
		i = edges[k][0];
		j = edges[k][1];//由i指向j
		s = new EdgeNode;
		s->adjvex = j;
		s->next = adjlist[i].firstEdge;
		adjlist[i].firstEdge = s;
		t = new EdgeNode;
		t->adjvex = i;
		t->last = adjlist[j].firstTail;
		adjlist[j].firstTail = t;
		adjlist[j].in++;
	}
}

template <typename T>
void AovGraph<T>::TopSort() {
	int i, j, k, count = 0;
	int S[MaxVertex], top = -1;
	EdgeNode* p = nullptr;
	for (i = 0; i < vertexNum; i++)
		if (adjlist[i].in == 0)S[++top] = i;
	while (top != -1) {
		j = S[top--];
		std::cout << adjlist[j].vertex << "->";
		count++;
		p = adjlist[j].firstEdge;
		while (p != nullptr) {
			k = p->adjvex;
			adjlist[k].in--;
			if (adjlist[k].in == 0)S[++top] = k;
			p = p->next;
		}
	}
	if (count < vertexNum) std::cout << "有回路\n";
	else std::cout << "#\n";
}