#include <iostream>
#include <ctime>
#include "AVLTree.h"
using namespace std;

int main()
{
	srand(time(NULL));
	AVLTree<int> tree;
	for (int i = 0; i < 25; i++)
	{
		tree.insert(rand() % 10);
	}
	tree.print();
	for (int i = 0; i < 15; i++)
	{
		tree.remove(rand() % 10);
	}

	system("pause");
	return 0;
}

/*
Tree:
4(3),
2(1),8(2),
1(0),3(0),6(1),9(0),
NL,NL,NL,NL,5(0),7(0),NL,NL,
请按任意键继续. . .
*/