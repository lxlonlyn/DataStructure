#pragma once
//边集数组，无向图
struct EdgeGraphNode{//边集数组项，起点终点权重
	int from;
	int to;
	int weight;
};

template<class T>
class EdgeGraph {
public:
	EdgeGraph(T a[], int n, int e);
	EdgeGraph(T a[], int n, int e, int edges[][3]);
	~EdgeGraph() {};
	ALGraph<T>* E2AL(int digraph, int weighted);
	void EdgeSort();
	void Kruskal();
private:
	int FindRoot(int parent[], int v);//并查集寻根
	T vertex[MaxVertex];//存顶点名称，例如A,B,C
	EdgeGraphNode edge[MaxEdge];//边集数组
	int vertexNum, edgeNum;//图属性，顶点数、边数
};

template<typename T>
EdgeGraph<T>::EdgeGraph(T a[], int n, int e) {
	vertexNum = n; edgeNum = e;
	for (int m = 0; m < vertexNum; m++) {
		vertex[m] = a[m];
	}
}

template<typename T>
EdgeGraph<T>::EdgeGraph(T a[], int n, int e, int edges[][3]) {
	vertexNum = n; edgeNum = e;
	for (int m = 0; m < vertexNum; m++) {
		vertex[m] = a[m];
	}
	for (int k = 0; k < edgeNum; k++) {
		edge[k].from = edges[k][0];
		edge[k].to = edges[k][1];
		edge[k].weight = edges[k][2];
	}
}

template<typename T>
ALGraph<T>* EdgeGraph<T>::E2AL(int digraph, int weighted) {
	if (weighted == 1) {
		int edges[MaxEdge][3];
		for (int i = 0; i < edgeNum; i++) {
			edges[i][0] = edge[i].from;
			edges[i][1] = edge[i].to;
			edges[i][2] = edge[i].weight;
		}
		ALGraph<char>* ALG = new ALGraph<char>(vertex, vertexNum, edgeNum, edges, digraph);
		return ALG;
	}
	else {
		int edges[MaxEdge][2];
		for (int i = 0; i < edgeNum; i++) {
			edges[i][0] = edge[i].from;
			edges[i][1] = edge[i].to;
		}
		ALGraph<char>* ALG = new ALGraph<char>(vertex, vertexNum, edgeNum, edges, digraph);
		return ALG;
	}
	
}

template<typename T>
void EdgeGraph<T>::EdgeSort() {//插入排序
	int i, j;
	EdgeGraphNode temp;
	for (i = 0; i < edgeNum; i++) {
		temp = edge[i];
		for (j = i - 1; j >= 0 && temp.weight < edge[j].weight; j--) edge[j + 1] = edge[j];
		edge[j + 1] = temp;
	}
}

template<typename T>
void EdgeGraph<T>::Kruskal() {//不含将边按权重排序的程序，要用EdgeSort排好
	EdgeSort();
	int num = 0, i, vex1, vex2;
	int parent[MaxVertex];
	for (i = 0; i < vertexNum; i++) parent[i] = -1;
	for (num = 0, i = 0; num < vertexNum - 1; i++) {
		vex1 = FindRoot(parent, edge[i].from);
		vex2 = FindRoot(parent, edge[i].to);
		if (vex1 != vex2) {
			std::cout << '(' << edge[i].from << ',' << 
				edge[i].to << ") " << edge[i].weight<< std::endl;
			parent[vex2] = vex1;
			num++;
		}
	}
}

template<typename T>
int EdgeGraph<T>::FindRoot(int parent[], int v) {
	int t = v;
	while (parent[t] > -1) t = parent[t];
	return t;
}