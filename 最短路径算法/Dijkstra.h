#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

/*
��Դ���·���㷨 dijkstra
ʱ�临�Ӷ� O(n^2)
˼��:
��ͼG�����еĶ���V�ֳ��������㼯��S��T����vΪԴ���Ѿ�ȷ�������·�����յ㲢��S�����У�S��ʼʱֻ������v,T������δȷ����Դ��v���·���Ķ��㼯�ϡ�
Ȼ��ÿ�δ�T������ѡ��S���ϵ��е�T·����̵��Ǹ��㣬�����뵽����S�У����������Ӽ���Tɾ����ֱ��T����Ϊ��Ϊֹ��

�㷨���裺
1. ѡһ����vΪԴ�㣬���Ӵ�Դ��v���������б�Ϊ������������·����ȷ�����ݽṹ����Ϊ��������·�������Ԣپ�Ҫ
��һ����¼��Դ��v�������������·����������dist[],��ʼʱ��dist��Դ��v������i��ֱ�ӱ߳��ȣ���dist�м�¼�����ڽ�
��ĵ�v�С�����һ��������¼��Դ�㵽���������·������path[],path�д��·���ϵ�i�������ǰ�����㣩��
2. �����������·��dist[]��ѡһ����̵ģ��������յ㣨��<v,k>��k���뵽����s�С�
3. ����T�и����㵽Դ��v�����·���� ��Ϊ������k���뵽����s�к�Դ��v��T��ʣ�����������j���������˾�������k��
��j��·��,����·������Ҫ��Դ��v��jԭ������̵Ļ�Ҫ�̡����������ǱȽ�dist[k]+g[k,j]��dist[j]��ȡ���еĽ�С�ߡ�
4. ��ѡ��һ����Դ��v·��������С�Ķ���k,��T��ɾȥ�����S�У��ٻ�ȥ��������������ظ���ֱ������S�еİ���ͼG�����ж��㡣

������
num���ڵ�����
src��Ҫ�����Դ�ڵ�
distance[i]�����Դ�ڵ㵽�ڵ�i�ľ���
previous[i]����ŵ��ڵ�i��̾���Ϊdistance[i]��ǰһ���ڵ�
weight[i][j]���ڵ�i��j֮���·��Ȩ�أ�����Ϊ��ֵ
*/
#ifndef MaxWeight
#define MaxWeight 10000
#endif

template<class T>
void dijkstra(int num,int src,T distance[],int previous[],T** weight)
{

	bool * knowedSetFlag = new bool[num];//S���ϱ�־
	for (int i = 0; i < num; i++)//��ʼ��
	{
		distance[i] = weight[src][i];
		knowedSetFlag[i] = false;
		if (distance[i] >= MaxWeight)
			previous[i] = -1;
		else previous[i] = src;//��ʼ��ʱ��ֱ�����ڵ����
	}
	distance[src] = 0;//�������Ϊ0
	knowedSetFlag[src] = true;//�ɵ�����

	for (int i = 0; i < num; i++)
	{
		T temp = MaxWeight;
		int node = src;
		for (int j = 0; j < num; j++)
		{
			if ((!knowedSetFlag[j]) && distance[j] < temp)//�ڲ�����S�������·��
			{
				node = j;
				temp = distance[j];
			}
		}
		knowedSetFlag[node] = true;//����S����
		for (int j = 0; j < num; j++)//����distance[]
		{
			if ((!knowedSetFlag[j]) && weight[node][j] < MaxWeight)
			{
				T newDistance = distance[node] + weight[node][j];
				if (newDistance < distance[j])
				{
					distance[j] = newDistance;
					previous[j] = node;//��������˾��룬����ǰ���ڵ�
				}
			}
		}

	}
}

#endif