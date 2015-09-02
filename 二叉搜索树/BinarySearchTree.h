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

/*  递归插入操作 */
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
/* 非递归 插入操作*/
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

/* 递归查询 */
BSTNode* search(BSTNode* root,int key)
{
	if (root == NULL || key == root->key)
		return root;
	if (key < root->key)
		return search(root->left, key);
	else
		return search(root->right, key);
}

/* 非递归 查询 */

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
/* 找出最小节点 */
BSTNode* findMin(BSTNode* root)
{
	if (root == NULL)
		return root;
	if (root->left == NULL)
		return root;
	return findMin(root->left);

}
/*
找出最小节点 非递归版本
*/
BSTNode* findMin__nonrecursion(BSTNode* root)
{
	if (root != NULL)
	while (root->left != NULL)
		root = root->left;
	return root;
}


/* 找出最大节点 */
BSTNode* findMax(BSTNode* root)
{
	if (root == NULL)
		return root;
	if (root->right == NULL)
		return root;
	return findMax(root->right);
}

/* 找出最大节点 非递归版本 */
BSTNode* findMax__nonrecursion(BSTNode* root)
{
	if (root != NULL)
	while (root->right != NULL)
		root = root->right;
	return root;
}
/* 删除操作 */
BSTNode* remove(BSTNode* root, int key)
{
	if (root == NULL)
		return root;
	if (root->key == key)
	{
		if (root->left != NULL && root->right != NULL)//有两个孩子
		{

			BSTNode* rightMin = findMin(root->right);
			root->key = rightMin->key;
			root->right = remove(root->right, rightMin->key);
			return root;
		}
		else if(root->left!=NULL)//有一个孩子或者没有孩子节点
		{
			BSTNode* temp = root;
			root = root->left;
			delete temp;
			return root;
		}
		else
		{
			root = root->right;
			return root;
		}
		
	}
	BSTNode* parent = root;
	BSTNode* current = (key < root->key) ? root->left : root->right;
	while (current != NULL && parent != NULL)
	{
		if (key == current->key)
		{
			break;
		}
		else if (key < current->key)
		{
			parent = current;
			current = current->left;
		}
		else
		{
			parent = current;
			current = current->right;
		}
	}
	if (current == NULL)//没找到
		return root;
	if (current->left != NULL&&current->right != NULL)//有两个孩子
	{

		BSTNode* rightMin = findMin(current->right);
		current->key = rightMin->key;
		current->right = remove(current->right, rightMin->key);
		return root;
	}
	else//有一个孩子或者没有孩子节点
	{
		if (parent->left == current)
			parent->left = NULL;
		else
			parent->right = NULL;
		delete current;
		return root;
	}
}


#endif