#include <iostream>
#include "Dijkstra.h"
#include "Bellman_Ford.h"
#include "Floyd_Warshall.h"
using namespace std;

void testDijkstra()
{
	int* distance = new int[5];
	int* previous = new int[5];
	int **weight = new int*[5];
	int src = 0;
	weight[0] = new int[5]{0, 10, MaxWeight, 30, 100};
	weight[1] = new int[5]{10, 0, 50, MaxWeight, MaxWeight };
	weight[2] = new int[5]{MaxWeight, 50, 0, 20, 10};
	weight[3] = new int[5]{30, MaxWeight, 20, 0, 60};
	weight[4] = new int[5]{100, MaxWeight, 10, 60, 0};

	dijkstra<int>(5, src, distance, previous, weight);
	cout << "Dijkstra" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << src << "->" << i << ": ";
		cout << "previous node:" << previous[i];
		cout << "  distance:" << distance[i] << endl;
	}

	delete[] distance;
	delete[] previous;
	for (int i = 0; i < 5; i++)
		delete[] weight[i];
	delete[] weight;
}


void test_Bellman_Ford()
{
	Edge<int>* edge = new Edge<int>[14]{{ 0, 1, 10 }, { 1, 0, 10 },
	{ 1, 2, 50 }, { 2, 1, 50 }, 
	{ 2, 3, 20 },  {3 ,2 ,20 },
	{ 3, 4, 60 }, {4 ,3 ,60 },
	{ 4, 0, 100 }, { 0,4 , 100},
	{ 0, 3, 30 }, { 3,0 ,30 },
	{ 2, 4, 10 },{4,2 ,10 }, };

	int* distance = new int[5];
	int* previous = new int[5];
	int src = 0;

	bool flag = bellman_ford(5, 14, src, distance, previous, edge);
	cout << "Bellman_Ford" << endl;
	cout << (flag ? "计算正常" : "有负值回路") << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << src << "->" << i << ": ";
		cout << "previous node:" << previous[i];
		cout << "  distance:" << distance[i] << endl;
	}

	delete[] distance;
	delete[] previous;
	delete[] edge;
}

void test_Floyd_Warshall()
{
	int** distance = new int*[5];
	int** path = new int*[5];
	for (int i = 0; i < 5; i++)
	{
		distance[i] = new int[5];
		path[i] = new int[5];
	}
	int **weight = new int*[5];
	weight[0] = new int[5]{0, 10, MaxWeight, 30, 100};
	weight[1] = new int[5]{10, 0, 50, MaxWeight, MaxWeight };
	weight[2] = new int[5]{MaxWeight, 50, 0, 20, 10};
	weight[3] = new int[5]{30, MaxWeight, 20, 0, 60};
	weight[4] = new int[5]{100, MaxWeight, 10, 60, 0};
	
	floyd_warshall(5,distance,path,weight);

	cout << "path:" << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << path[i][j]<<"  ";
		}
		cout << endl;
	}

	cout << "distance:" << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << distance[i][j]<<"  ";
		}
		cout << endl;
	}

	int src = 0;
	int des = 4;
	print_path(5,src,des,distance,path);

	delete[] distance;
	delete[] path;
	for (int i = 0; i < 5; i++)
		delete[] weight[i];
	delete[] weight;
}
int main()
{
	testDijkstra();
	cout << "***************" << endl;
	test_Bellman_Ford();
	cout << "***************" << endl;
	test_Floyd_Warshall();
	system("pause");
	return 0;
}