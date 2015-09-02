#ifndef _FLOYD_WARSHALL_H_
#define _FLOYD_WARSHALL_H_
/*
多源最短路径算法 floyd_warshall
时间复杂度:O(n^3)
空间复杂度:O(n^2)

算法过程：
1. 从任意一条单边路径开始。所有两点之间的距离是边的权，如果两点之间没有边相连，则权为无穷大。
2. 对于每一对顶点 u 和 v，看看是否存在一个顶点 w 使得从 u 到 w 再到 v 比已知的路径更短。如果是更新它。
把图用邻接矩阵G表示出来，如果从Vi到Vj有路可达，则G[i,j]=d，d表示该路的长度；否则G[i,j]=无穷大。
定义一个矩阵D用来记录所插入点的信息，D[i,j]表示从Vi到Vj需要经过的点，初始化D[i,j]=i。
把各个顶点插入图中，比较插点后的距离与原来的距离，G[i,j] = min( G[i,j], G[i,k]+G[k,j] )，
如果G[i,j]的值变小，则D[i,j]=k。在G中包含有两点之间最短路径的距离信息，而在D中则包含了最短路径必须经过的中间节点信息。
比如，要寻找从V5到V1的路径。根据D，假如D(5,1)=3则说明从V5到V1经过V3，路径为{V5,V3,V1}，
如果D(5,3)=5，说明V5与V3直接相连，如果D(3,1)=3，说明V3与V1直接相连。

优缺点：
Floyd算法适用于APSP(All Pairs Shortest Paths，多源最短路径)，是一种动态规划算法，稠密图效果最佳，边权可正可负（但是不能有负值环路）。
此算法简单有效，由于三重循环结构紧凑，对于稠密图，效率要高于执行|V|次Dijkstra算法，也要高于执行V次SPFA算法。
优点：容易理解，可以算出任意两个节点之间的最短距离，代码编写简单。
缺点：时间复杂度比较高，不适合计算大量数据。

参数：
nodeNum：节点数量
distance[i][j]：节点i和j的最短路径值
path[i][j]：节点i和j最短路径要经过的中间节点
weight[i][j]：邻接矩阵
*/
#include <stack>
#include <vector>

#ifndef MaxWeight
#define MaxWeight 10000
#endif

template<class T>
void floyd_warshall(int nodeNum,T ** distance,int ** path,T** weight)
{
	for (int i = 0; i < nodeNum; i++)//初始化
	{
		for (int j = 0; j < nodeNum; j++)
		{
			distance[i][j] = weight[i][j];
			if (weight[i][j] < MaxWeight)
				path[i][j] = i;
			else path[i][j] = -1;
		}
	}
	for (int i = 0; i < nodeNum; i++)
	{
		for (int j = 0; j < nodeNum; j++)
		{
			for (int k = 0; k < nodeNum; k++)
			{
				if (distance[j][k]>distance[j][i] + distance[i][k])
				{
					distance[j][k] = distance[j][i] + distance[i][k];
					path[j][k] = i;
				}
			}
		}
	}
}

//打印src->des的完整路径
template<class T>
void print_path(int nodeNum, int src,int des,T ** distance, int ** path)
{
	cout << src << "->" << des << ": distance:" << distance[src][des] << endl;
	
	Node* head = construct_path(nodeNum,src,des,distance,path);
	
	if (head == nullptr)
	{
		cout << "no path" << endl;
		return;
	}
	Node* temp = head;
	while (temp != nullptr)
	{
		cout << temp->node;
		temp = temp->next;
		if (temp != nullptr)
			cout << "->";
	}
	cout << endl;
//清理
	while (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}
//路径辅助节点类
typedef struct Node
{
	int node;
	Node* next;
}Node;
//构建完整路径
template<class T>
Node* construct_path(int nodeNum, int src, int des, T ** distance, int ** path)
{
	if (distance[src][des] >= MaxWeight)
		return nullptr;

	using namespace std;
	Node* head = nullptr;

	stack<int> stack;
	stack.push(src);
	stack.push(path[src][des]);
	stack.push(des);

	while (true)
	{
		int mDes = stack.top();//读取
		stack.pop();//出栈
		if (stack.empty())//如果是最后一个节点，插入链表后退出循环
		{
			Node* newHead = new Node;
			newHead->node = mDes;
			newHead->next = head;
			head = newHead;
			break;
		}
		int mSrc = stack.top();//读取但不出栈
		if (path[mSrc][mDes] == mSrc)//查找中间节点，如果中间节点就是源节点，表明只有一跳，将终点插入链表
		{
			Node* newHead = new Node;
			newHead->node = mDes;
			newHead->next = head;
			head = newHead;
		}
		else//如果还有中间节点，将找到的中间节点和目的节点压栈
		{
			stack.push(path[mSrc][mDes]);
			stack.push(mDes);
		}
	}
	return head;

}

#endif



//using namespace std;
//void getRoute(int sr, int des, int ** path, vector<int>& ve){
//	int temp = path[sr][des];
//	if (temp != sr){
//		auto it = find(ve.begin(), ve.end(), des);
//		ve.insert(it, temp);
//		getRoute(sr, temp, path, ve);
//		getRoute(temp, des, path, ve);
//	}
//}
//
//void print(int sr, int des, int ** path){
//	vector<int> shortestRoute;
//	shortestRoute.push_back(sr);
//	shortestRoute.push_back(des);
//	getRoute(sr, des, path, shortestRoute);
//	for (int s : shortestRoute)
//		cout << s << "->";
//	cout << endl;
//}
