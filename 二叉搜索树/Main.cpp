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
	cout << "------" << endl;
	root = remove(root, 4);
	root = remove(root, 5);
	root = remove(root, 3);
	inOrder(root);

	BSTNode* res = search(root,6);
	cout << res << endl;
	if (res!=NULL)
		cout << res->key << endl;

	res = search_nonrecursion(root, 3);
	cout << res << endl;
	if (res != NULL)
		cout << res->key << endl;

	res = findMax(root);
	cout << res << endl;
	if (res != NULL)
		cout << res->key << endl;

	res = findMin(root);
	cout << res << endl;
	if (res != NULL)
		cout << res->key << endl;

	system("pause");
}