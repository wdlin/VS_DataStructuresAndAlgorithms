#ifndef _BELLMAN_FORD_H_
#define _BELLMAN_FORD_H_


/*
单源最短路径算法 Bellman_Ford （可用于边的权值为负）
时间复杂度: O(V*E)

适用条件&范围
1.单源最短路径(从源点s到其它所有顶点v);
2.有向图&无向图(无向图可以看作(u,v),(v,u)同属于边集E的有向图);
3.边权可正可负(如有负权回路输出错误提示);
4.差分约束系统;
描述：
1.初始化：将除源点外的所有顶点的最短距离估计值 d[v]←+∞, d[s]←0;
2.迭代求解：反复对边集E中的每条边进行松弛操作，使得顶点集V中的每个顶点v的最短距离估计值逐步逼近其最短距离；（运行|v|-1次）
3.检验负权回路：判断边集E中的每一条边的两个端点是否收敛。如果存在未收敛的顶点，则算法返回false，表明问题无解；否则算法返回true，并且从源点可达的顶点v的最短距离保存在 d[v]中。
证明：
首先指出，图的任意一条最短路径既不能包含负权回路，也不会包含正权回路，因此它最多包含|v|-1条边。
其次，从源点s可达的所有顶点如果 存在最短路径，则这些最短路径构成一个以s为根的最短路径树。Bellman-Ford算法的迭代松弛操作，实际上就是按顶点距离s的层次，逐层生成这棵最短路径树的过程。
在对每条边进行第1遍松弛的时候，生成了从s出发，层次至多为1的那些树枝。也就是说，找到了与s至多有1条边相联的那些顶点的最短路径；对每条边进行第2遍松弛的时候，生成了第2层次的树枝，就是说找到了经过2条边相连的那些顶点的最短路径……。因为最短路径最多只包含|v|-1 条边，所以，只需要循环|v|-1 次。
每实施一次松弛操作，最短路径树上就会有一层顶点达到其最短距离，此后这层顶点的最短距离值就会一直保持不变，不再受后续松弛操作的影响。（但是，每次还要判断松弛，这里浪费了大量的时间，怎么优化？单纯的优化是否可行？）
注意：上述只对正权图有效。如果存在负权不一定第i次就能确定最短路，且与边的顺序有关。
如果没有负权回路，由于最短路径树的高度最多只能是|v|-1，所以最多经过|v|-1遍松弛操作后，所有从s可达的顶点必将求出最短距离。如果 d[v]仍保持 +∞，则表明从s到v不可达。
如果有负权回路，那么第 |v| 遍松弛操作仍然会成功，这时，负权回路上的顶点不会收敛。

参数：
nodeNum：节点数量
edgeNum：边的数量
src：要计算的源节点
distance[i]：存放源节点到节点i的距离
previous[i]：存放到节点i最短距离为distance[i]的前一个节点
edge[i]：边i
*/

#ifndef MaxCost
#define MaxCost 10000
#endif

//边
template<class T>
struct Edge
{
	int u, v;//起点和终点
	T cost;//边权值
	Edge(int mu, int mv, int mcost) :u(mu),v(mv),cost(mcost){};
};

template<class T>
bool bellman_ford(int nodeNum,int edgeNum,int src,T distance[],int previous[],Edge<T> edge[])
{
	previous[src] = src;
	for (int i = 0; i < nodeNum; i++)//初始化
		distance[i] = (i == src) ? 0 : MaxCost;
	for (int i = 1; i < nodeNum - 1; i++)
	{
		for (int j = 0; j < edgeNum; j++)
		{
			if (distance[edge[j].v] > distance[edge[j].u] + edge[j].cost)//松弛操作
			{
				distance[edge[j].v] = distance[edge[j].u] + edge[j].cost;
				previous[edge[j].v] = edge[j].u;
			}
		}
	}

	bool flag = true;//判断是否有负值回路
	for (int i = 0; i < edgeNum; i++)
	{
		if (distance[edge[i].v]>distance[edge[i].u] + edge[i].cost)
		{
			flag = false;
			break;
		}
	}

	return flag;
}


#endif