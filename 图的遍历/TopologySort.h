#ifndef _TOPOLOGY_SORT_H_
#define _TOPOLOGY_SORT_H_
#include "AdjacencyList.h"
/*
对一个有向无环图(Directed Acyclic Graph简称DAG)G进行拓扑排序，是将G中所有顶点排成一个线性序列，
使得图中任意一对顶点u和v，若边(u,v)∈E(G)，则u在线性序列中出现在v之前。通常，这样的线性序列称
为满足拓扑次序(Topological Order)的序列，简称拓扑序列。
简单的说，由某个集合上的一个偏序得到该集合上的一个全序，这个操作称之为拓扑排序。
用顶点表示活动，弧表示活动之间的优先级关系的有向图称为（Activity On Vertex Network）AOV网
*/
#include <stack>
using std::stack;

template<class Data>
bool topology_sort(AdjacencyList<Data> &al)
{
	//al.print();
	if (al.getKind() != 1)
		throw "不是有向图";
	int node_num = al.getNodeNum();
	int *indegree = al.getIndegree();
	int count = 0;
	stack<int> stack;
	for (int i = 0; i < node_num; i++)
	{
		if (indegree[i] == 0)//入度为0的入栈
			stack.push(i);
	}
	while (!stack.empty())
	{
		int i = stack.top();
		stack.pop();
		std::cout << i << " -> " << std::endl;
		count++;
		AdjacencyList<Data>::Edge *edge = al.nodes[i].firstEdge;
		while (edge != nullptr)
		{
			if ((--indegree[edge->adjacent_node])==0)stack.push(edge->adjacent_node);//入度为0的入栈
			edge = edge->nextEdge;
		}
	}
	delete indegree;
	return count == node_num;//false表示有环
}







#endif