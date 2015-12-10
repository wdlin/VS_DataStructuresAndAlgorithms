#ifndef _ADJACENCY_LIST_H_
#define _ADJACENCY_LIST_H_

#include <vector>
#include <iostream>
#include <queue>

template<class Data>
class AdjacencyList
{
public:
	//AdjacencyList();
	AdjacencyList(int nodeNum, int kind, Data* nodes_data, int** matrix);//节点数，种类，节点数据数组，节点的邻接矩阵（0不连接，非零连接）
	~AdjacencyList();

	// 深度优先搜索遍历图
	void DFS();
	// 广度优先搜索（类似于树的层次遍历）
	void BFS();
	// 打印邻接表图
	void print();
	int getNodeNum();
	int getEdgeNum();
	int getKind();
	int* getIndegree();

//private:
	//为了方便拓扑排序函数使用，放置为public
	struct Edge
	{
		int adjacent_node;//指向的节点
		Edge* nextEdge;//下一条边
		Edge(int in, Edge* ne) :adjacent_node(in), nextEdge(ne){}
	};

	struct Node
	{
		Data data;//节点数据
		Edge* firstEdge;//第一条边
		Node(Data d, Edge* fe) :data(d), firstEdge(fe){}
	};

	// 深度优先搜索遍历图的递归实现
	void DFS(int i, bool *visited);

	void release(Edge* edge);
	void visit(int i);//访问节点函数
	int node_num;//节点数目
	int edge_num;//边的数目
	
	int kind;//0:无向图，1：有向图
	std::vector<Node> nodes;//节点数组

};
template<class Data>
AdjacencyList<Data>::AdjacencyList(int nodeNum, int kind, Data* nodes_data, int** matrix)//节点数，种类，节点数据数组，节点的邻接矩阵（0不连接，非零连接）
{
	node_num = nodeNum;
	this->kind = kind;
	int temp_edge_num = 0;
	nodes.reserve(node_num);
	for (int i = 0; i < node_num; i++)
	{
		nodes.push_back(Node(nodes_data[i], nullptr));
		Edge* preEdge = nullptr;
		for (int j = 0; j < node_num; j++)
		{
			if (matrix[i][j] > 0)
			{
				temp_edge_num++;
				if (nodes[i].firstEdge == nullptr)
				{
					nodes[i].firstEdge = new Edge(j, nullptr);
					preEdge = nodes[i].firstEdge;
				}
				else
				{
					preEdge->nextEdge = new Edge(j, nullptr);
					preEdge = preEdge->nextEdge;
				}

			}
		}
	}

	if (kind == 0)
		edge_num = temp_edge_num/2;
	else
		edge_num = temp_edge_num;

}
template<class Data>
AdjacencyList<Data>::~AdjacencyList()
{
	for (int i = 0; i < node_num; i++)
	{
		if (nodes[i].firstEdge != nullptr)
			release(nodes[i].firstEdge);
	}

}

template<class Data>
void AdjacencyList<Data>::release(Edge* edge)
{
	if (edge->nextEdge != nullptr)
		release(edge->nextEdge);
	delete edge;
}

template<class Data>
void AdjacencyList<Data>::visit(int i)
{
	std::cout << nodes[i].data << std::endl;
}


// 深度优先搜索遍历图
template<class Data>
void AdjacencyList<Data>::DFS()
{
	bool *visited = new bool[node_num];
	for (int i = 0; i < node_num; i++)
		visited[i] = false;

	std::cout << "DFS:" << std::endl;
	for (int i = 0; i < node_num; i++)
	{
		if (!visited[i])
			DFS(i, visited);
	}
	std::cout << std::endl;
	delete[] visited;
}

template<class Data>
void AdjacencyList<Data>::DFS(int i, bool *visited)
{
	visited[i] = true;
	visit(i);
	Edge* edge = nodes[i].firstEdge;
	while (edge != nullptr)
	{
		if (!visited[edge->adjacent_node])
			DFS(edge->adjacent_node, visited);
		edge = edge->nextEdge;
	}
}

// 广度优先搜索（类似于树的层次遍历）
template<class Data>
void AdjacencyList<Data>::BFS()
{
	using namespace std;
	bool* visited = new bool[node_num];
	queue<int> queue;
	for (int i = 0; i < node_num; i++)
		visited[i] = false;
	for (int i = 0; i < node_num; i++)
	{
		if (!visited[i])
		{
			visited[i] = true;
			visit(i);
			queue.push(i);
			while (!queue.empty())
			{
				int nodeIndex = queue.front();
				queue.pop();

				Edge* temp_edge = nodes[nodeIndex].firstEdge;
				while (temp_edge != nullptr)
				{
					if (!visited[temp_edge->adjacent_node])
					{
						visited[temp_edge->adjacent_node] = true;
						visit(temp_edge->adjacent_node);
						queue.push(temp_edge->adjacent_node);	
					}
					temp_edge = temp_edge->nextEdge;
				}
			}


		}
	}

	delete[] visited;

}
// 打印邻接表图
template<class Data>
void AdjacencyList<Data>::print()
{
	using namespace std;
	for (int i = 0; i < node_num; i++)
	{
		cout << i << " : ";
		Edge* edge = nodes[i].firstEdge;
		while (edge != nullptr)
		{
			cout << edge->adjacent_node << " , ";
			edge = edge->nextEdge;
		}
		cout << endl;
	}
}

template<class Data>
int AdjacencyList<Data>::getNodeNum()
{
	return node_num;
}
template<class Data>
int AdjacencyList<Data>::getEdgeNum()
{
	return edge_num;
}

template<class Data>
int AdjacencyList<Data>::getKind()
{
	return kind;
}

template<class Data>
int* AdjacencyList<Data>::getIndegree()
{
	int * indegree = new int[node_num];
	for (int i = 0; i < node_num; i++)
		indegree[i] = 0;

	for (int i = 0; i < node_num; i++)
	{
		Edge* edge = nodes[i].firstEdge;
		while (edge != nullptr)
		{
			indegree[edge->adjacent_node]++;
			edge = edge->nextEdge;
		}
	}

	return indegree;
}



#endif

