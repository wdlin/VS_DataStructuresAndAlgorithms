#ifndef _FLOYD_WARSHALL_H_
#define _FLOYD_WARSHALL_H_
/*
��Դ���·���㷨 floyd_warshall
ʱ�临�Ӷ�:O(n^3)
�ռ临�Ӷ�:O(n^2)

�㷨���̣�
1. ������һ������·����ʼ����������֮��ľ����Ǳߵ�Ȩ���������֮��û�б���������ȨΪ�����
2. ����ÿһ�Զ��� u �� v�������Ƿ����һ������ w ʹ�ô� u �� w �ٵ� v ����֪��·�����̡�����Ǹ�������
��ͼ���ڽӾ���G��ʾ�����������Vi��Vj��·�ɴ��G[i,j]=d��d��ʾ��·�ĳ��ȣ�����G[i,j]=�����
����һ������D������¼����������Ϣ��D[i,j]��ʾ��Vi��Vj��Ҫ�����ĵ㣬��ʼ��D[i,j]=i��
�Ѹ����������ͼ�У��Ƚϲ���ľ�����ԭ���ľ��룬G[i,j] = min( G[i,j], G[i,k]+G[k,j] )��
���G[i,j]��ֵ��С����D[i,j]=k����G�а���������֮�����·���ľ�����Ϣ������D������������·�����뾭�����м�ڵ���Ϣ��
���磬ҪѰ�Ҵ�V5��V1��·��������D������D(5,1)=3��˵����V5��V1����V3��·��Ϊ{V5,V3,V1}��
���D(5,3)=5��˵��V5��V3ֱ�����������D(3,1)=3��˵��V3��V1ֱ��������

��ȱ�㣺
Floyd�㷨������APSP(All Pairs Shortest Paths����Դ���·��)����һ�ֶ�̬�滮�㷨������ͼЧ����ѣ���Ȩ�����ɸ������ǲ����и�ֵ��·����
���㷨����Ч����������ѭ���ṹ���գ����ڳ���ͼ��Ч��Ҫ����ִ��|V|��Dijkstra�㷨��ҲҪ����ִ��V��SPFA�㷨��
�ŵ㣺������⣬����������������ڵ�֮�����̾��룬�����д�򵥡�
ȱ�㣺ʱ�临�ӶȱȽϸߣ����ʺϼ���������ݡ�

������
nodeNum���ڵ�����
distance[i][j]���ڵ�i��j�����·��ֵ
path[i][j]���ڵ�i��j���·��Ҫ�������м�ڵ�
weight[i][j]���ڽӾ���
*/
#include <stack>
#include <vector>

#ifndef MaxWeight
#define MaxWeight 10000
#endif

template<class T>
void floyd_warshall(int nodeNum,T ** distance,int ** path,T** weight)
{
	for (int i = 0; i < nodeNum; i++)//��ʼ��
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

//��ӡsrc->des������·��
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
//����
	while (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}
//·�������ڵ���
typedef struct Node
{
	int node;
	Node* next;
}Node;
//��������·��
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
		int mDes = stack.top();//��ȡ
		stack.pop();//��ջ
		if (stack.empty())//��������һ���ڵ㣬����������˳�ѭ��
		{
			Node* newHead = new Node;
			newHead->node = mDes;
			newHead->next = head;
			head = newHead;
			break;
		}
		int mSrc = stack.top();//��ȡ������ջ
		if (path[mSrc][mDes] == mSrc)//�����м�ڵ㣬����м�ڵ����Դ�ڵ㣬����ֻ��һ�������յ��������
		{
			Node* newHead = new Node;
			newHead->node = mDes;
			newHead->next = head;
			head = newHead;
		}
		else//��������м�ڵ㣬���ҵ����м�ڵ��Ŀ�Ľڵ�ѹջ
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
