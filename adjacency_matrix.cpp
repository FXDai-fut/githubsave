//模拟邻接矩阵的初始化和增删改查
#include<iostream>
using namespace std;
#define inf -1

//邻接矩阵类
class Graph {
private:
	int vertices;
	int** edges;

public:
	Graph(int vertices);
	~Graph();
	void addedge(int u, int v, int w);
	void printgraph();
};


//有参构造
Graph::Graph(int vertices) {
	this->vertices = vertices;
	edges = new int* [vertices];
	for (int i = 0; i < vertices; i++) {
		edges[i] = new int[vertices];//不能写成edges[i] = new int[vertices](inf)
		for (int j = 0;j < vertices;j++) {
			edges[i][j] = inf;
		}
	}
}

//析构
Graph::~Graph() {
	for (int i = 0;i < vertices;i++) {
		delete[] edges[i];
	}
	delete[]edges;
}

//添加元素
void Graph::addedge(int u, int v, int w) {
	edges[u][v] = w;
}

//输出矩阵
void Graph::printgraph() {
	for (int i = 0;i < vertices;i++) {
		for (int j = 0;j < vertices;j++) {
			cout << edges[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	int vertices = 5;
	Graph s(vertices);
	s.addedge(0, 0, 5);
	s.addedge(0, 1, 4);
	s.addedge(1, 2, 3);
	s.addedge(2, 3, 2);
	s.addedge(3, 4, 1);
	s.addedge(4, 3, 7);
	s.printgraph();
	return 0;
}