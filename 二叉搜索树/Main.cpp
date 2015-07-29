#include <iostream>
#include "BinarySearchTree.h"
#include <ctime>
#include <queue>
using namespace std;

void preOrder(BSTNode* p)
{
	if (p != NULL)
	{
		cout << p->key << endl;
		preOrder(p->left);
		preOrder(p->right);
	}
}

/* µÝ¹é 2.ÖÐÐò±éÀú */
void inOrder(BSTNode* p)
{
	if (p != NULL)
	{
		inOrder(p->left);
		cout << p->key << endl;
		inOrder(p->right);
	}
}

void main()
{
	srand(time(NULL));
	BSTNode* root = NULL;
	for (int i = 0; i < 10; i++)
	{
		int key = rand() % 10;
		//insert(root, key);
		insert_nonRecursion(root, key);
	}
	preOrder(root);
	cout << "------" << endl;
	inOrder(root);

	BSTNode* res1 = search(root,3);
	cout << res1 << endl;
	BSTNode* res2 = search_nonrecursion(root,3);
	cout << res2 << endl;
	system("pause");
}