#include <iostream>
#include "AdjacencyList.h"
#include "TopologySort.h"
using namespace std;

void testTraverse()
{
	//这个图在 严蔚敏p168
	int *nodes = new int[8];
	for (int i = 0; i < 8; i++)
		nodes[i] = i;
	int** matrix = new int*[8];
	for (int i = 0; i < 8; i++)
		matrix[i] = new int[8];
	for (int i = 0; i < 8; i++)
	for (int j = 0; j < 8; j++)
		matrix[i][j] = 0;
	matrix[0][1] = 1;
	matrix[0][2] = 1;
	matrix[1][0] = 1;
	matrix[1][3] = 1;
	matrix[1][4] = 1;
	matrix[2][0] = 1;
	matrix[2][5] = 1;
	matrix[2][6] = 1;
	matrix[3][1] = 1;
	matrix[3][7] = 1;
	matrix[4][1] = 1;
	matrix[4][7] = 1;
	matrix[5][2] = 1;
	matrix[5][6] = 1;
	matrix[6][2] = 1;
	matrix[6][5] = 1;
	matrix[7][3] = 1;
	matrix[7][4] = 1;

	AdjacencyList<int> al(8, 0, nodes, matrix);

	al.DFS();
	cout << "***********" << endl;
	al.BFS();
	cout << "***********" << endl;
	al.print();
}

void testTopologySort()
{
	//这个图在 严蔚敏 p182
	int *nodes = new int[6];
	for (int i = 0; i < 6; i++)
		nodes[i] = i;
	int** matrix = new int*[6];
	for (int i = 0; i < 6; i++)
		matrix[i] = new int[6];
	for (int i = 0; i < 6; i++)
	for (int j = 0; j < 6; j++)
		matrix[i][j] = 0;
	matrix[0][1] = 1;
	matrix[0][2] = 1;
	matrix[0][3] = 1;
	matrix[2][1] = 1;
	matrix[2][4] = 1;
	matrix[3][4] = 1;
	matrix[5][3] = 1;
	matrix[5][4] = 1;

	AdjacencyList<int> al(6, 1, nodes, matrix);

	cout << topology_sort<int>(al) << endl;
}


int main()
{

	//testTraverse();
	testTopologySort();
	

	system("pause");
	return 0;
}

