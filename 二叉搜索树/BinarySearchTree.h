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

/*  �ݹ������� */
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
/* �ǵݹ� �������*/
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

/* �ݹ��ѯ */
BSTNode* search(BSTNode* root,int key)
{
	if (root == NULL || key == root->key)
		return root;
	if (key < root->key)
		return search(root->left, key);
	else
		return search(root->right, key);
}

/* �ǵݹ� ��ѯ */

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
/* �ҳ���С�ڵ� */
BSTNode* findMin(BSTNode* root)
{
	if (root == NULL)
		return root;
	if (root->left == NULL)
		return root;
	return findMin(root->left);

}
/*
�ҳ���С�ڵ� �ǵݹ�汾
*/
BSTNode* findMin__nonrecursion(BSTNode* root)
{
	if (root != NULL)
	while (root->left != NULL)
		root = root->left;
	return root;
}


/* �ҳ����ڵ� */
BSTNode* findMax(BSTNode* root)
{
	if (root == NULL)
		return root;
	if (root->right == NULL)
		return root;
	return findMax(root->right);
}

/* �ҳ����ڵ� �ǵݹ�汾 */
BSTNode* findMax__nonrecursion(BSTNode* root)
{
	if (root != NULL)
	while (root->right != NULL)
		root = root->right;
	return root;
}
/* ɾ������ */
BSTNode* remove(BSTNode* root, int key)
{
	if (root == NULL)
		return root;
	if (root->key == key)
	{
		if (root->left != NULL && root->right != NULL)//����������
		{

			BSTNode* rightMin = findMin(root->right);
			root->key = rightMin->key;
			root->right = remove(root->right, rightMin->key);
			return root;
		}
		else if(root->left!=NULL)//��һ�����ӻ���û�к��ӽڵ�
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
	if (current == NULL)//û�ҵ�
		return root;
	if (current->left != NULL&&current->right != NULL)//����������
	{

		BSTNode* rightMin = findMin(current->right);
		current->key = rightMin->key;
		current->right = remove(current->right, rightMin->key);
		return root;
	}
	else//��һ�����ӻ���û�к��ӽڵ�
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