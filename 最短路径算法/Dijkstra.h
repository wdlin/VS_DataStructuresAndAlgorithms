#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

/*
单源最短路径算法 dijkstra
时间复杂度 O(n^2)
思想:
将图G中所有的顶点V分成两个顶点集合S和T。以v为源点已经确定了最短路径的终点并入S集合中，S初始时只含顶点v,T则是尚未确定到源点v最短路径的顶点集合。
然后每次从T集合中选择S集合点中到T路径最短的那个点，并加入到集合S中，并把这个点从集合T删除。直到T集合为空为止。

算法步骤：
1. 选一顶点v为源点，并视从源点v出发的所有边为到各顶点的最短路径（确定数据结构：因为求的是最短路径，所以①就要
用一个记录从源点v到其它各顶点的路径长度数组dist[],开始时，dist是源点v到顶点i的直接边长度，即dist中记录的是邻接
阵的第v行。②设一个用来记录从源点到其它顶点的路径数组path[],path中存放路径上第i个顶点的前驱顶点）。
2. 在上述的最短路径dist[]中选一条最短的，并将其终点（即<v,k>）k加入到集合s中。
3. 调整T中各顶点到源点v的最短路径。 因为当顶点k加入到集合s中后，源点v到T中剩余的其它顶点j就又增加了经过顶点k到
达j的路径,这条路径可能要比源点v到j原来的最短的还要短。调整方法是比较dist[k]+g[k,j]与dist[j]，取其中的较小者。
4. 再选出一个到源点v路径长度最小的顶点k,从T中删去后加入S中，再回去到第三步，如此重复，直到集合S中的包含图G的所有顶点。

参数：
num：节点数量
src：要计算的源节点
distance[i]：存放源节点到节点i的距离
previous[i]：存放到节点i最短距离为distance[i]的前一个节点
weight[i][j]：节点i和j之间的路径权重，不能为负值
*/
#ifndef MaxWeight
#define MaxWeight 10000
#endif

template<class T>
void dijkstra(int num,int src,T distance[],int previous[],T** weight)
{

	bool * knowedSetFlag = new bool[num];//S集合标志
	for (int i = 0; i < num; i++)//初始化
	{
		distance[i] = weight[src][i];
		knowedSetFlag[i] = false;
		if (distance[i] >= MaxWeight)
			previous[i] = -1;
		else previous[i] = src;//初始化时，直接相邻的情况
	}
	distance[src] = 0;//自身距离为0
	knowedSetFlag[src] = true;//可到自身

	for (int i = 0; i < num; i++)
	{
		T temp = MaxWeight;
		int node = src;
		for (int j = 0; j < num; j++)
		{
			if ((!knowedSetFlag[j]) && distance[j] < temp)//在不属于S中找最短路径
			{
				node = j;
				temp = distance[j];
			}
		}
		knowedSetFlag[node] = true;//加入S集合
		for (int j = 0; j < num; j++)//更新distance[]
		{
			if ((!knowedSetFlag[j]) && weight[node][j] < MaxWeight)
			{
				T newDistance = distance[node] + weight[node][j];
				if (newDistance < distance[j])
				{
					distance[j] = newDistance;
					previous[j] = node;//如果更新了距离，更新前驱节点
				}
			}
		}

	}
}

#endif