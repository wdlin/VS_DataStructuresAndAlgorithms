#ifndef _BINARY_TREE_VISIT_H_
#define _BINARY_TREE_VISIT_H_
/*二叉树遍历*/

/* 递归 1.先序遍历  2.中序遍历  3.后序遍历*/
/* 非递归 1.非递归先序遍历  2.非递归中序遍历  */

/* 1.广度遍历 */
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

/* 递归 1.先序遍历  2.中序遍历  3.后序遍历*/
/* 访问函数 */
void visit(TreeNode* p)
{
	if (p!=NULL)
	cout << p->data << endl;
}

/* 递归 1.先序遍历 */
void preOrder(TreeNode* p)
{
	if (p != NULL)
	{
		visit(p);
		preOrder(p->left);
		preOrder(p->right);
	}
}

/* 递归 2.中序遍历 */
void inOrder(TreeNode* p)
{
	if (p != NULL)
	{
		inOrder(p->left);
		visit(p);
		inOrder(p->right);
	}
}

/* 递归  3.后序遍历 */
void postOrder(TreeNode* p)
{
	if (p != NULL)
	{
		postOrder(p->left);
		postOrder(p->right);
		visit(p);
	}
}

/* 非递归 1.非递归先序遍历
首先将根节点压栈
栈不为空，出栈
出栈的节点如果有孩子，先压入右孩子，在压入左孩子
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

/* 非递归 1.非递归中序遍历 
首先将根节点压栈
然后将左孩子压栈，如果左孩子还有左孩子继续压栈。
左左..节点都压栈结束后，开始出栈
1.如果栈空，遍历结束
2.访问出来的节点
3.如果出来的节点有右孩子，压栈，然后如果这个孩子还有左左..孩子，继续压栈
4.如果出来的节点没有右孩子，p = NULL，继续出栈
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

/* 1.广度遍历 
利用队列遍历
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