#pragma once
#include <iostream>
#include <string>
//邻接矩阵，无向图
template <class T>
class MGraph {
public:
	MGraph(T a[], int n, int e);
	MGraph(T a[], int n, int e, int edgedata[][MaxVertex]);
	~MGraph() {};//析构函数为空
	void DFTraverse(int v);
	void BFTraverse(int v);
	void Print(void);
	void Prim(int v);
	void Dijkstra(int v);
	void Floyd(void);
private:
	T vertex[MaxVertex];//存顶点名称，例如A,B,C
	int edge[MaxVertex][MaxVertex];//边矩阵
	int vertexNum, edgeNum;//图属性，顶点数、边数
	int visited[MaxVertex] = { 0 };
};

template <typename T>
MGraph<T>::MGraph(T a[], int n, int e) {
	int i, j, k;
	vertexNum = n; edgeNum = e;
	for (i = 0; i < vertexNum; i++) vertex[i] = a[i];
	for (i = 0; i < vertexNum; i++) for (j = 0; j < vertexNum; j++)edge[i][j] = 0;
	for (k = 0; k < edgeNum; k++) {
		std::cout << "请输入第" << k + 1 << "条边的两个端点:\n";
		std::cin >> i >> j;
		edge[i][j] = 1; edge[j][i] = 1;
	}
}

template <typename T>
MGraph<T>::MGraph(T a[], int n, int e, int edgedata[][MaxVertex]) {
	int i, j;
	vertexNum = n; edgeNum = e;
	for (i = 0; i < vertexNum; i++) vertex[i] = a[i];
	for (i = 0; i < vertexNum; i++)
		for (j = 0; j < vertexNum; j++)
			edge[i][j] = edgedata[i][j];
}

template <typename T>
void MGraph<T>::Print(void) {
	int i, j;
	for (i = 0; i < vertexNum; i++) {
		for (j = 0; j < vertexNum; j++) std::cout << edge[i][j] << ' ';
		std::cout << std::endl;
	}
}

template <typename T>
void MGraph<T>::DFTraverse(int v) {
	std::cout << vertex[v];
	visited[v] = 1;
	for (int j = 0; j < vertexNum; j++)
		if (edge[v][j] == 1 && visited[j] == 0) DFTraverse(j);
}

template <typename T>
void MGraph<T>::BFTraverse(int v) {
	int w, j, Q[MaxVertex];
	int front = -1, rear = -1;
	std::cout << vertex[v];
	visited[v] = 1;
	Q[++rear] = v;
	while (front != rear) {
		w = Q[++front];
		for (j = 0; j < vertexNum; j++) {
			if (edge[w][j] == 1 && visited[j] == 0) {
				std::cout << vertex[j];
				visited[j] = 1;
				Q[++rear] = j;
			}
		}
	}
}

int MinEdge(int lowcost[MaxVertex], int vertexNum) {
	int min = MAX;
	int index = 0;
	int flag = 0;//是否找到
	for (int i = 0; i < vertexNum; i++) {
		if (lowcost[i] < min && lowcost[i] != 0) {
			min = lowcost[i];
			index = i;
			flag = 1;
		}
	}
	if (flag == 1) return index;
	else return -1;
	
}

template <typename T>
void MGraph<T>::Prim(int v) {
	int i, j, k;
	int adjvex[MaxVertex], lowcost[MaxVertex];
	for (i = 0; i < vertexNum; i++) {
		lowcost[i] = edge[v][i];
		adjvex[i] = v;
	}
	lowcost[v] = 0;
	for (k = 0; k < vertexNum; k++) {
		j = MinEdge(lowcost, vertexNum);
		if (j != -1) {
			std::cout << vertex[j] << "->" << vertex[adjvex[j]]
				<< " cost:" << lowcost[j] << std::endl;
			lowcost[j] = 0;
			for (i = 0; i < vertexNum; i++) {
				if (edge[i][j] < lowcost[i]) {
					lowcost[i] = edge[i][j];
					adjvex[i] = j;
				}
			}
		}
	}
}

int Min(int lowcost[MaxVertex], int vertexNum) {
	int min = MAX;
	int index = 0;
	for (int i = 0; i < vertexNum; i++) {
		if (lowcost[i] < min && lowcost[i] != 0) {
			min = lowcost[i];
			index = i;
		}
	}
	return index;
}

template <typename T>
void MGraph<T>::Dijkstra(int v) {
	int i, k, num, dist[MaxVertex];
	std::string path[MaxVertex];
	std::string a, b, c;
	for (i = 0; i < vertexNum; i++) {
		dist[i] = edge[v][i];
		if (dist[i] != MAX) {
			a = vertex[v]; b = vertex[i];
			path[i] = a + b;
		}
		else path[i] = "";
	}
	for (num = 1; num < vertexNum; num++) {
		k = Min(dist, vertexNum);
		std::cout << path[k] << "\tDistance=" << dist[k] << std::endl;
		for (i = 0; i < vertexNum; i++)
			if (dist[i] > dist[k] + edge[k][i]) {
				dist[i] = dist[k] + edge[k][i];
				c = vertex[i];
				path[i] = path[k] + c;
			}
		dist[k] = 0;
	}
}

template <typename T>
void MGraph<T>::Floyd(void) {
	int i, j, k, dist[MaxVertex][MaxVertex];
	std::string path[MaxVertex][MaxVertex];
	//初始化，只包含长度为1的路径
	//最终最优值也是由此，对路径进行组合得出的
	for (i = 0; i < vertexNum; i++)
		for (j = 0; j < vertexNum; j++) {
			dist[i][j] = edge[i][j];
			if (i == j) path[i][j] = "";//自己到自己，无需路径
			else if (dist[i][j] != MAX) {
				path[i][j] = vertex[j];//只记录路径终点，输出时加入起点
			}
			else path[i][j] = "";//不可达
		}
	for (k = 0; k < vertexNum; k++)
		for (i = 0; i < vertexNum; i++)
			for (j = 0; j < vertexNum; j++)
				if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[i][k] + path[k][j];
				}
	for (i = 0; i < vertexNum; i++) {
		for (j = 0; j < vertexNum; j++) {
			if (i == j) std::cout << vertex[i] << '\t';
			else if (path[i][j] == "") std::cout << "NULL" << '\t';
			else {
				std::cout << vertex[i]+path[i][j] << '\t';
			}
		}
		std::cout << std::endl;
	}
	return;
}