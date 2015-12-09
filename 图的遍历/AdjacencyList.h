#ifndef _ADJACENCY_LIST_H_
#define _ADJACENCY_LIST_H_

#include <vector>
#include <iostream>
#include <queue>
#define Data int

class AdjacencyList
{
public:
	//AdjacencyList();
	AdjacencyList(int nodeNum, int kind, Data* nodes_data, int** matrix);//�ڵ��������࣬�ڵ��������飬�ڵ���ڽӾ���0�����ӣ��������ӣ�
	~AdjacencyList();

	// ���������������ͼ
	void DFS();
	// ����������������������Ĳ�α�����
	void BFS();
	// ��ӡ�ڽӱ�ͼ
	void print();

private:
	struct Edge
	{
		int adjacent_node;//ָ��Ľڵ�
		Edge* nextEdge;//��һ����
		Edge(int in, Edge* ne) :adjacent_node(in), nextEdge(ne){}
	};

	struct Node
	{
		Data data;//�ڵ�����
		Edge* firstEdge;//��һ����
		Node(Data d, Edge* fe) :data(d), firstEdge(fe){}
	};

	// ���������������ͼ�ĵݹ�ʵ��
	void DFS(int i, bool *visited);

	void release(Edge* edge);
	void visit(int i);
	int node_num;//�ڵ���Ŀ
	int edge_num;//�ߵ���Ŀ
	std::vector<Node> nodes;//�ڵ�����
	int kind;//0:����ͼ��1������ͼ


};

AdjacencyList::AdjacencyList(int nodeNum, int kind, Data* nodes_data, int** matrix)//�ڵ��������࣬�ڵ��������飬�ڵ���ڽӾ���0�����ӣ��������ӣ�
{
	node_num = nodeNum;
	this->kind = kind;
	int temp_edge_num = 0;
	nodes.reserve(node_num);
	Edge* temp;
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

AdjacencyList::~AdjacencyList()
{
	for (int i = 0; i < node_num; i++)
	{
		if (nodes[i].firstEdge != nullptr)
			release(nodes[i].firstEdge);
	}

}


void AdjacencyList::release(Edge* edge)
{
	if (edge->nextEdge != nullptr)
		release(edge->nextEdge);
	delete edge;
}


void AdjacencyList::visit(int i)
{
	std::cout << nodes[i].data << std::endl;
}


// ���������������ͼ
void AdjacencyList::DFS()
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

void AdjacencyList::DFS(int i, bool *visited)
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

// ����������������������Ĳ�α�����
void AdjacencyList::BFS()
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
// ��ӡ�ڽӱ�ͼ
void AdjacencyList::print()
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


#endif

