#include <iostream>
#include <ctime>
#include "BinaryTreeVisit.h"

using namespace std;

void createTree(TreeNode* &root)
{
	char c;
	cin >> c;
	if ('#' == c)
		root = NULL;
	else
	{
		root = new TreeNode;
		root->data = c;
		createTree(root->left);
		createTree(root->right);
	}

	return ;
}
void createTree2(TreeNode* &root)
{
	root = new TreeNode;
	root->data = 'a';
	root->left = new TreeNode;
	root->right = new TreeNode;
	root->left->data = 'b';
	root->right->data = 'c';

	root->left->left = new TreeNode;
	root->left->right = new TreeNode;
	root->left->left->data = 'd';
	root->left->right->data = 'e';
	root->left->right->left = NULL;
	root->left->right->right = NULL;
	root->left->left->left = NULL;
	root->left->left->right = NULL;

	root->right->left = new TreeNode;
	root->right->right = new TreeNode;
	root->right->left->data = 'f';
	root->right->right->data = 'g';
	root->right->right->left = NULL;
	root->right->right->right = NULL;
	root->right->left->left = NULL;
	root->right->left->right = NULL;
}

void main()
{
	TreeNode* root;
	//����abcdefg########
	createTree2(root);

	/*root = new TreeNode;
	root->data = 1;
	root->left = new TreeNode;
	root->left->data = 2;
	root->left->left = NULL;
	root->left->right = NULL;
	root->right = new TreeNode;
	root->right->data = 3;
	root->right->left = NULL;
	root->right->right = NULL;*/
	cout << "�ݹ�����-----" << endl;
	preOrder(root);
	cout << "�ݹ�����-----"<<endl;
	inOrder(root);
	cout << "�ݹ����-----" << endl;
	postOrder(root);
	cout << "�ǵݹ�����-----" << endl;
	preOrder_nonRecursion(root);
	cout << "�ǵݹ�����-----" << endl;
	inOrder_nonRecursion(root);
	cout << "��ȱ���-----" << endl;
	layer(root);
	system("pause");
}