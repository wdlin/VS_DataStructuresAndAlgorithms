#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_
#include <algorithm>
#include <iostream>
#include <cmath>
#include <queue>

/*
AVL�� ��򵥵�ƽ������������
�ο����ݽṹ���㷨������C++������ P104 - P107
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
	typedef struct AVLNode//���ڵ�����
	{
		Comparable element;
		AVLNode* left;
		AVLNode* right;
		int height;//�ڵ�ĸ߶ȣ�û�к���0��nullptr��-1
		AVLNode(const Comparable& theElement, AVLNode* lt, AVLNode* rt, int h = 0) :element(theElement), left(lt), right(rt),height(h){}
	}AVLNode;

	AVLNode* root;//���ڵ�
	int height(AVLNode* node) const;//���ؽڵ�ĸ߶�
	void insert(const Comparable& x, AVLNode*& root);//����ڵ�
	AVLNode* remove(AVLNode* node , const Comparable& x);//�Ƴ��ڵ㣬���ظ�
	AVLNode* find(const Comparable& x);//���ҽڵ㣬���ؽڵ�
	AVLNode* findMin(AVLNode* node);//
	AVLNode* findMax(AVLNode* node);//
	void rotateWithLeftChild(AVLNode*& k2);//����
	void rotateWithRightChild(AVLNode*& k1);//����
	void doubleWithLeftChild(AVLNode*& k3);//����
	void doubleWithRightChild(AVLNode*& k1);//����
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
	else if (x < node->element)//����������
	{
		insert(x, node->left);
		if (height(node->left) - height(node->right) == 2)
		{
			if (x < node->left->element)//����
				rotateWithLeftChild(node);
			else
				doubleWithLeftChild(node);//����
		}
	}
	else if (x > node->element)//����������
	{
		insert(x, node->right);
		if (height(node->right) - height(node->left) == 2)
		{
			if (x > node->right->element)//����
				rotateWithRightChild(node);
			else
				doubleWithRightChild(node);//����
		}
	}
	else
		;//�ظ���������
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
ɾ���ڵ��ʵ�ʺ������������ĸ���Ҫɾ����ֵ������ɾ�����������
��ɾ���ӿں������ã�Ĭ����Ҫɾ����ֵһ�������С�
*/
template<class Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::remove(AVLNode* node, const Comparable& x)
{
	//Ҫɾ���Ľڵ���ǵ�ǰ�ĸ�
	if (x == node->element)
	{	//���������ǿ�
		if (node->left != nullptr && node->right != nullptr)
		{	//�����������ɾ����������Ԫ��ֵ�����Ǹ��ڵ㣬ͬʱ����ֵ��ֵ�����ڵ� 
			if (height(node->left) > height(node->right))
			{
				node->element = findMax(node->left)->element;
				node->left = remove(node->left, node->element);
			}//�����������ɾ����������Ԫ��ֵ��С���Ǹ��ڵ㣬ͬʱ����ֵ��ֵ�����ڵ�
			else
			{
				node->element = findMin(node->right)->element;
				node->right = remove(node->right, node->element);
			}
		}
		else//������һ�����ӵĿյģ��ÿյĺ��ӵ���һ���ֵ��滻������Ҳ�ǿյģ�
		{
			AVLNode* oldNode = node;
			node = (node->left != nullptr) ? node->left : node->right;
			delete oldNode;
		}
		if(node!=nullptr)//���¸߶ȣ�node�����ǿյ�
			node->height = max(height(node->left), height(node->right)) + 1;
	}
	else if (x < node->element)//ɾ���ڵ���������
	{	//���������н��еݹ�ɾ��
		node->left = remove(node->left, x);
		if (height(node->right) - height(node->left)>1)//�ж��Ƿ���Ȼƽ������
		{
			if (height(node->right->left) > height(node->right->right))//����
				doubleWithRightChild(node);
			else
				rotateWithRightChild(node);//����
		}
		node->height = max(height(node->left), height(node->right)) + 1;//���¸߶�
	}
	else//ɾ���ڵ���������
	{//���������н��еݹ�ɾ��
		node->right = remove(node->right, x);
		if (height(node->left) - height(node->right)>1)//�ж��Ƿ���Ȼƽ������
		{
			if (height(node->left->right) > height(node->left->left))//����
				doubleWithLeftChild(node);
			else
				rotateWithLeftChild(node);//����
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



