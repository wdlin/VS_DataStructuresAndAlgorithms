#ifndef _BINARY_TREE_VISIT_H_
#define _BINARY_TREE_VISIT_H_
/*����������*/

/* �ݹ� 1.�������  2.�������  3.�������*/
/* �ǵݹ� 1.�ǵݹ��������  2.�ǵݹ��������  */

/* 1.��ȱ��� */
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

typedef struct TreeNode
{
	char data;
	TreeNode* left;
	TreeNode* right;
}TreeNode;

/* �ݹ� 1.�������  2.�������  3.�������*/
/* ���ʺ��� */
void visit(TreeNode* p)
{
	if (p!=NULL)
	cout << p->data << endl;
}

/* �ݹ� 1.������� */
void preOrder(TreeNode* p)
{
	if (p != NULL)
	{
		visit(p);
		preOrder(p->left);
		preOrder(p->right);
	}
}

/* �ݹ� 2.������� */
void inOrder(TreeNode* p)
{
	if (p != NULL)
	{
		inOrder(p->left);
		visit(p);
		inOrder(p->right);
	}
}

/* �ݹ�  3.������� */
void postOrder(TreeNode* p)
{
	if (p != NULL)
	{
		postOrder(p->left);
		postOrder(p->right);
		visit(p);
	}
}

/* �ǵݹ� 1.�ǵݹ��������
���Ƚ����ڵ�ѹջ
ջ��Ϊ�գ���ջ
��ջ�Ľڵ�����к��ӣ���ѹ���Һ��ӣ���ѹ������
*/

void preOrder_nonRecursion(TreeNode* root)
{
	if (root == NULL)
		return;
	stack<TreeNode*> stack;
	stack.push(root);
	while (!stack.empty())
	{
		TreeNode* p = stack.top();
		visit(p);
		stack.pop();
		if (p->right != NULL)
			stack.push(p->right);
		if (p->left != NULL)
			stack.push(p->left);

	}
}

/* �ǵݹ� 1.�ǵݹ�������� 
���Ƚ����ڵ�ѹջ
Ȼ������ѹջ��������ӻ������Ӽ���ѹջ��
����..�ڵ㶼ѹջ�����󣬿�ʼ��ջ
1.���ջ�գ���������
2.���ʳ����Ľڵ�
3.��������Ľڵ����Һ��ӣ�ѹջ��Ȼ�����������ӻ�������..���ӣ�����ѹջ
4.��������Ľڵ�û���Һ��ӣ�p = NULL��������ջ
*/
void inOrder_nonRecursion(TreeNode* root)
{
	if (root == NULL)
		return;
	stack<TreeNode*> stack;
	stack.push(root);
	TreeNode* p = root;
	while (1)
	{
		if (p != NULL && p->left != NULL)
		{
			stack.push(p->left);
			p = p->left;
		}
		else
		{
			if (stack.empty())
				return;
			p = stack.top();
			stack.pop();
			visit(p);
			if (p->right != NULL)
			{
				stack.push(p->right);
				p = p->right;
			}
			else
			{
				p = NULL;
			}
		}

	}
}

/* 1.��ȱ��� 
���ö��б���
*/
void layer(TreeNode* root)
{
	if (root == NULL)
		return;
	queue<TreeNode*> queue;
	queue.push(root);
	TreeNode* p;
	while (!queue.empty())
	{
		p = queue.front();
		queue.pop();
		visit(p);
		if (p->left != NULL)
			queue.push(p->left);
		if (p->right != NULL)
			queue.push(p->right);
	}
}



#endif