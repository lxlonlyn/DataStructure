#pragma once
//常量
const int MaxSize = 20;
const int MaxVertex = 12;
const int MaxEdge = 20;
const int MAX = 114514;
//线性表
#include "SeqList.h"
#include "LinkList.h"
#include "HashTable.h"
#include "CirQueue.h"
#include "Stack.h"
#include "LinkQueue.h"
#include "LinkStack.h"
//树表
#include "BiTree.h"
#include "BiSortTree.h"
#include "AVLTree.h"
#include "Heap.h"
#include "BPTree.h"
//图表
#include "MGraph.h"
#include "ALGraph.h"
#include "EdgeGraph.h"
#include "AovGraph.h"
#include "AoeGraph.h"
#include "OrthList.h"
//二分查找
#include "BiSearch.h"
//排序
#include "Sort.h"

void SeqListDemo() {
	int data[5] = { 0,1,2,3,4 };
	SeqList<int>* sl = new SeqList<int>(data, 5);
	sl->Print();
}

void LinkListDemo() {
	int data[5] = { 1,2,3,4,5 };
	LinkList<int>* ll = new LinkList<int>(data, 5);
	ll->Print();
}

void QueueDemo() {
	int data[5] = { 1,3,5,7,9 };
	CirQueue<int>* q = new CirQueue<int>(data, 5);
	q->Print();
}

void StackDemo() {
	int data[5] = { 2,4,6,8,10 };
	Stack* s = new Stack(data, 5);
	s->Print();
}

void BiTreeDemo() {
	char ch[14] = "ABD###C#EF###";//前序序列
	char* chptr = ch;
	BiTree<char> bt(chptr);
	bt.NRPostOrder();
	std::cout << '\n';
}

void HeapDemo() {
	int data[8] = { 36,30,18,40,32,45,22,50 };
	Heap* heap = new Heap(data, 8);
	std::cout << "Ordered: ";
	heap->Print();
}

void AVLTreeDemo() {
	int data[6] = { 20,35,40,15,30,25 };
	AVLTree* avlt = new AVLTree(data, 6);
	avlt->PreOrder();
}

void GraphDemo() {
	char ch[11] = "ABCDEFGHIJ";
	int edgesW[9][3] = { {0,1,2},{0,2,4},{0,3,5},{0,4,6},{0,5,3},{0,6,7},{0,7,1},{0,8,9},{0,9,8} };
	EdgeGraph<char>* EG = new EdgeGraph<char>(ch, 10, 9, edgesW);//10个结点9条边
	EG->Kruskal();
	ALGraph<char>* ALG = EG->E2AL(0,1);//第一个参数0为无向图，第二个参数1为带权图
	ALG->DFTraverseNR(5);
	std::cout << std::endl;
	MGraph<char>* MG = ALG->AL2M();
	MG->Prim(1);
	MG->Dijkstra(0);
	MG->Floyd();
}


void OrthListDemo() {
	OrthList<int>* ol = new OrthList<int>(6,6);
	int triple[8][3] = { {0, 0, 1}, {1, 1, 2}, {2, 2, 3}, {3, 5, 4},
		{3, 4, 5}, {5, 3, 6}, {5, 5, 7}, {5, 0, 8} };
	ol->InsertTriple(triple, 8);
	ol->Print();
	ol->PrintRow(5);
}

void SortDemo() {
	int data[10] = { 36,99,18,40,32,45,22,50,75,11 };
	int length = 10;
	Sort* sort = new Sort(data, length);
	//插入排序
	//sort->InsertSort();
	//sort->ShellSort();
	//交换排序
	//sort->BubbleSort();
	//sort->QuickSort(0,length-1);
	//选择排序
	//sort->SelectSort();
	//sort->HeapSort();
	//归并排序
	sort->MergeSort1(0,length);
	//sort->MergeSort2();
	sort->Print();
}