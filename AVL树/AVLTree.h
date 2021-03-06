#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_
#include <algorithm>
#include <iostream>
#include <cmath>
#include <queue>

/*
AVL树 最简单的平衡搜索二叉树
参考数据结构与算法分析（C++描述） P104 - P107
*/
template<class Comparable>
class AVLTree
{
public:
	AVLTree();
	~AVLTree();
	void print();
	void insert(const Comparable& x);
	bool remove(const Comparable& x);
	bool contains(const Comparable& x);
private:
	typedef struct AVLNode//树节点类型
	{
		Comparable element;
		AVLNode* left;
		AVLNode* right;
		int height;//节点的高度，没有孩子0，nullptr是-1
		AVLNode(const Comparable& theElement, AVLNode* lt, AVLNode* rt, int h = 0) :element(theElement), left(lt), right(rt),height(h){}
	}AVLNode;

	AVLNode* root;//根节点
	int height(AVLNode* node) const;//返回节点的高度
	void insert(const Comparable& x, AVLNode*& root);//插入节点
	AVLNode* remove(AVLNode* node , const Comparable& x);//移除节点，返回根
	AVLNode* find(const Comparable& x);//查找节点，返回节点
	AVLNode* findMin(AVLNode* node);//
	AVLNode* findMax(AVLNode* node);//
	void rotateWithLeftChild(AVLNode*& k2);//左左
	void rotateWithRightChild(AVLNode*& k1);//右右
	void doubleWithLeftChild(AVLNode*& k3);//左右
	void doubleWithRightChild(AVLNode*& k1);//右左
};

template<class Comparable>
AVLTree<Comparable>::AVLTree() :root(nullptr)
{}

template<class Comparable>
AVLTree<Comparable>::~AVLTree()
{
	if (root == nullptr)
		return;
	queue<AVLNode*> queue;
	queue.push(root);
	AVLNode* p;
	while (!queue.empty())
	{
		p = queue.front();
		queue.pop();
		if (p->left=nullptr)
			queue.push(p->left);
		if (p->right = nullptr)
			queue.push(p->right);
		delete p;
	}
}

template<class Comparable>
void AVLTree<Comparable>::insert(const Comparable& x)
{
	insert(x, root);
}

template<class Comparable>
int AVLTree<Comparable>::height(AVLNode* node) const
{
	return node == nullptr ? -1 : node->height;
}

template<class Comparable>
bool AVLTree<Comparable>::contains(const Comparable& x)
{
	return (find(x) == nullptr) ? false : true;
}

template<class Comparable>
void AVLTree<Comparable>::insert(const Comparable& x, AVLNode*& node)
{
	if (node == nullptr)
		node = new AVLNode(x, nullptr, nullptr);
	else if (x < node->element)//插入左子树
	{
		insert(x, node->left);
		if (height(node->left) - height(node->right) == 2)
		{
			if (x < node->left->element)//左左
				rotateWithLeftChild(node);
			else
				doubleWithLeftChild(node);//左右
		}
	}
	else if (x > node->element)//插入右子树
	{
		insert(x, node->right);
		if (height(node->right) - height(node->left) == 2)
		{
			if (x > node->right->element)//右右
				rotateWithRightChild(node);
			else
				doubleWithRightChild(node);//右左
		}
	}
	else
		;//重复，不操作
	node->height = std::max(height(node->left),height(node->right)) + 1;
}

template<class Comparable>
bool AVLTree<Comparable>::remove(const Comparable& x)
{
	if (find(x) == nullptr)
		return false;
	else
		root = remove(root, x);
	return true;
}

/*
删除节点的实际函数，输入树的根和要删除的值。返回删除后的树根。
由删除接口函数调用，默认是要删除的值一定在树中。
*/
template<class Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::remove(AVLNode* node, const Comparable& x)
{
	//要删除的节点就是当前的根
	if (x == node->element)
	{	//左右子树非空
		if (node->left != nullptr && node->right != nullptr)
		{	//如果左子树大，删除左子树中元素值最大的那个节点，同时将其值赋值给根节点 
			if (height(node->left) > height(node->right))
			{
				node->element = findMax(node->left)->element;
				node->left = remove(node->left, node->element);
			}//如果右子树大，删除右子树中元素值最小的那个节点，同时将其值赋值给根节点
			else
			{
				node->element = findMin(node->right)->element;
				node->right = remove(node->right, node->element);
			}
		}
		else//至少有一个孩子的空的，用空的孩子的另一个兄弟替换（可能也是空的）
		{
			AVLNode* oldNode = node;
			node = (node->left != nullptr) ? node->left : node->right;
			delete oldNode;
		}
		if(node!=nullptr)//更新高度，node可能是空的
			node->height = max(height(node->left), height(node->right)) + 1;
	}
	else if (x < node->element)//删除节点在左子树
	{	//在左子树中进行递归删除
		node->left = remove(node->left, x);
		if (height(node->right) - height(node->left)>1)//判断是否仍然平衡条件
		{
			if (height(node->right->left) > height(node->right->right))//右左
				doubleWithRightChild(node);
			else
				rotateWithRightChild(node);//右右
		}
		node->height = max(height(node->left), height(node->right)) + 1;//更新高度
	}
	else//删除节点在右子树
	{//在右子树中进行递归删除
		node->right = remove(node->right, x);
		if (height(node->left) - height(node->right)>1)//判断是否仍然平衡条件
		{
			if (height(node->left->right) > height(node->left->left))//左右
				doubleWithLeftChild(node);
			else
				rotateWithLeftChild(node);//右右
		}
		node->height = max(height(node->left), height(node->right)) + 1;
	}
	return node;
}

template<class Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::findMin(AVLNode* node)
{
	if (node != nullptr)
	while (node->left != nullptr)
		node = node->left;
	return node;
}

template<class Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::findMax(AVLNode* node)
{
	if (node!=nullptr)
	while (node->right != nullptr)
		node = node->right;
	return node;
}
template<class Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::find(const Comparable& x)
{
	if (root == nullptr)
		return nullptr;
	AVLNode* temp = root;
	while (temp != nullptr)
	{
		if (x == temp->element)
			return temp;
		if (x < temp->element)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return nullptr;
}

template<class Comparable>
void AVLTree<Comparable>::rotateWithLeftChild(AVLNode*& k2)
{
	AVLNode* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = std::max(height(k2->left), height(k2->right)) + 1;
	k1->height = std::max(height(k1->left), k2->height) + 1;
	k2 = k1;
}

template<class Comparable>
void AVLTree<Comparable>::rotateWithRightChild(AVLNode*& k1)
{
	AVLNode* k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = std::max(height(k1->right), height(k1->right)) + 1;
	k2->height = std::max(k1->height, height(k2->right)) + 1;
	k1 = k2;
}

template<class Comparable>
void AVLTree<Comparable>::doubleWithLeftChild(AVLNode*& k3)
{
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

template<class Comparable>
void AVLTree<Comparable>::doubleWithRightChild(AVLNode*& k1)
{
	rotateWithLeftChild(k1->right);
	rotateWithRightChild(k1);
}

template<class Comparable>
void AVLTree<Comparable>::print()
{
	using namespace std;
	int h = height(root);
	if (h == -1)
	{
		cout << "tree is empty!" << endl;
		return;
	}
	cout << "Tree:" << endl;
	if (h == 0)
	{
		cout << root->element << endl;
		return;
	}
	int maxnum = pow(2, h + 1) - 1;
	int addCount = 1;
	int outCount = 0;
	int layer = 0;
	queue<AVLNode*> queue;
	queue.push(root);
	AVLNode* p;
	while (!queue.empty())
	{
		p = queue.front();
		queue.pop();
		if (p == nullptr)
		{
			cout << "NL"<<",";
			if (addCount + 2 <= maxnum)
			{
				queue.push(nullptr);
				queue.push(nullptr);
				addCount = addCount + 2;
			}
		}
		else
		{
			cout << p->element<<"("<<p->height<<")"<<",";
			if (addCount + 2 <= maxnum)
			{
				queue.push(p->left);
				queue.push(p->right);
				addCount = addCount + 2;
			}
		}
		outCount++;
		if (outCount == pow(2, layer + 1) - 1)
		{
			layer++;
			cout << endl;
		}
	}
	
}

#endif



