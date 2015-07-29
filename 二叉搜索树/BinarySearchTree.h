#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_
/* BST */
#include <iostream>
using namespace std;
typedef struct BSTNode
{
	int key;
	BSTNode* left;
	BSTNode* right;
}BSTNode;

/*  µÝ¹é²åÈë²Ù×÷ */
BSTNode* insert(BSTNode* &root, int key)
{
	if (root == NULL)
	{
		root = new BSTNode;
		root->key = key;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	if (key == root->key)
	{
		return root;
	}
	if (key < root->key)
	{
		insert(root->left, key);
	}
	else
	{
		insert(root->right, key);
	}
	return root;
}
/* ·ÇµÝ¹é ²åÈë²Ù×÷*/
void insert_nonRecursion(BSTNode* &root,int key)
{
	if (root == NULL)
	{
		root = new BSTNode;
		root->key = key;
		root->left = NULL;
		root->right = NULL;
		return;
	}
	BSTNode* p = root;
	BSTNode* parent = NULL;
	bool flag = true;
	while (p != NULL && p->key != key)
	{
		if (key < p->key)
		{
			parent = p;
			p = p->left;
			flag = true;
		}		
		else
		{
			parent = p;
			p = p->right;
			flag = false;
		}
			
	}
	if (p!=NULL && key == p->key)
	{
		return;
	}
	if (flag)
	{
		parent->left = new BSTNode;
		parent->left->key = key;
		parent->left->left = NULL;
		parent->left->right = NULL;
	}
	else
	{
		parent->right = new BSTNode;
		parent->right->key = key;
		parent->right->left = NULL;
		parent->right->right = NULL;
	}
	return;
}

/* µÝ¹é²éÑ¯ */
BSTNode* search(BSTNode* root,int key)
{
	if (root == NULL || key == root->key)
		return root;
	if (key < root->key)
		return search(root->left, key);
	else
		return search(root->right, key);
}

/* ·ÇµÝ¹é ²éÑ¯ */

BSTNode* search_nonrecursion(BSTNode* root,int key)
{
	while (root != NULL)
	{
		if (root->key == key)
			return root;
		if (key < root->key)
			root = root->left;
		else root = root->right;
	}
	return root;
}

#endif