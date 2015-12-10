#ifndef _TOPOLOGY_SORT_H_
#define _TOPOLOGY_SORT_H_
#include "AdjacencyList.h"
/*
��һ�������޻�ͼ(Directed Acyclic Graph���DAG)G�������������ǽ�G�����ж����ų�һ���������У�
ʹ��ͼ������һ�Զ���u��v������(u,v)��E(G)����u�����������г�����v֮ǰ��ͨ�����������������г�
Ϊ�������˴���(Topological Order)�����У�����������С�
�򵥵�˵����ĳ�������ϵ�һ��ƫ��õ��ü����ϵ�һ��ȫ�����������֮Ϊ��������
�ö����ʾ�������ʾ�֮������ȼ���ϵ������ͼ��Ϊ��Activity On Vertex Network��AOV��
*/
#include <stack>
using std::stack;

template<class Data>
bool topology_sort(AdjacencyList<Data> &al)
{
	//al.print();
	if (al.getKind() != 1)
		throw "��������ͼ";
	int node_num = al.getNodeNum();
	int *indegree = al.getIndegree();
	int count = 0;
	stack<int> stack;
	for (int i = 0; i < node_num; i++)
	{
		if (indegree[i] == 0)//���Ϊ0����ջ
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
			if ((--indegree[edge->adjacent_node])==0)stack.push(edge->adjacent_node);//���Ϊ0����ջ
			edge = edge->nextEdge;
		}
	}
	delete indegree;
	return count == node_num;//false��ʾ�л�
}







#endif