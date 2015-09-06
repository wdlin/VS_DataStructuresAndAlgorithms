#include <iostream>
#include "AVLTree.h"
using namespace std;

int main()
{
	AVLTree<int> tree;
	for (int i = 0; i < 10; i++)
	{
		tree.insert(rand() % 100);
	}
	
	tree.print();
	system("pause");
	return 0;
}

/*
Tree:
41,
24,67,
0,34,62,69,
NL,NL,NL,NL,58,64,NL,78,
请按任意键继续. . .
*/