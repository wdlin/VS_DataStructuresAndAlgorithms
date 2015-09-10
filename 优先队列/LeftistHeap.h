#ifndef _LEFTIST_HEAP_H_
#define _LEFTIST_HEAP_H_

/*
左式堆：堆中的任何节点，其左儿子的零路径长>=右儿子的零路径长的二叉堆。
零路径长 Npl（null path length）：从X到一个不具有两个儿子的结点的最短路径的长。
性质：
1. 任一结点的零路径长比他的诸儿子结点的零路径长的最小值多1
2. 堆中的任何节点，其左儿子的零路径长>=右儿子的零路径长的二叉堆。
由1和2知：左式堆任意结点的Npl为右孩子的Npl+1.
3. 在右路径上有r个节点的左式数至少有2^r - 1个节点。

时间复杂度：
由于上述的操作均基于合并，而合并仅对右路做合并，而右路结点的数量为总数量的对数关系，
所以左式堆的三个操作所花的时间为O(logN).

左式堆的合并共有四步：
1.如果有一棵树是空树，则返回另一棵树；
否则合并这两个堆，比较它们的根，递归地将具有较大根值的堆 与 具有较少根值的堆的右子堆合并。
2.使形成的新堆作为较小根值堆的右子树。
3.如果违反了左式堆的特性，交换两个子树的位置。
4.更新Npl。
左式堆的插入（Insert）很简单，其实也就是一个单结点和原堆的合并。
左式堆的DleteMin也很简单，就是把根结点删除，把两棵子树合并。左式堆的删除可以考虑懒惰删除（Lazy Delete）。
*/
#include <stdexcept>
#include <queue>

template<class Comparable>
class LeftistHeap
{
public:
	LeftistHeap();
	LeftistHeap(const LeftistHeap& rhs);
	~LeftistHeap();
	LeftistHeap& operator=(const LeftistHeap& rhs);
	bool isEmpty() const;//是否为空
	Comparable getMin() const;//获取最小值
	void deleteMin();//删除最小值
	void insert(const Comparable & item);//插入元素
	void makeEmpty();//清空所有元素
	void merge(LeftistHeap& rhs);//合并接口函数
	void print(int layer);//打印,参数为打印多少层,因为是不平衡树，所以有可能打多了或者打小了。
private:
	struct LeftistNode
	{
		Comparable element;
		LeftistNode* left;
		LeftistNode* right;
		int npl;//节点的零路长
		LeftistNode(const Comparable& theElement,LeftistNode* lt = nullptr,LeftistNode* rt = nullptr,int theNpl = 0)
		:element(theElement),left(lt),right(rt),npl(theNpl){}
	};
	LeftistNode* root;//堆的根
	LeftistNode* merge(LeftistNode* node1, LeftistNode* node2);//合并驱动函数
	LeftistNode* actualMerge(LeftistNode* smallerNode, LeftistNode* largerNode);//实际合并函数
	int getNpl(LeftistNode* node);//获取一个节点的零路长
	void swapChildren(LeftistNode* node);//交换节点的两个孩子
	void reclaimMemory(LeftistNode* node);//释放堆的内存
	LeftistNode* clone(LeftistNode* node);//克隆函数

};
template<class Comparable>
LeftistHeap<Comparable>::LeftistHeap() :root(nullptr)
{
}
template<class Comparable>
LeftistHeap<Comparable>::LeftistHeap(const LeftistHeap<Comparable>& rhs)
{
	root = clone(rhs.root);
}
template<class Comparable>
LeftistHeap<Comparable>& LeftistHeap<Comparable>::operator=(const LeftistHeap<Comparable>& rhs)
{
	if (this != &rhs)
	{
		makeEmpty();
		root = clone(rhs.root);
	}
	return *this;
}
template<class Comparable>
LeftistHeap<Comparable>::~LeftistHeap()
{
	reclaimMemory(root);
}
//是否为空
template<class Comparable>
bool LeftistHeap<Comparable>::isEmpty() const
{
	return root == nullptr;
}

//获取最小值
template<class Comparable>
Comparable LeftistHeap<Comparable>::getMin() const
{
	if (isEmpty())
		throw std::runtime_error("Heap is Empty!");
	return root->element;
}
//删除最小值
template<class Comparable>
void LeftistHeap<Comparable>::deleteMin()
{
	if (isEmpty())
		return;
	LeftistNode* oldRoot = root;
	root = merge(root->left, root->right);
	delete oldRoot;
}
//插入元素
template<class Comparable>
void LeftistHeap<Comparable>::insert(const Comparable & item)
{
	root = merge(new LeftistNode(item), root);
}

//清空所有元素
template<class Comparable>
void LeftistHeap<Comparable>::makeEmpty()
{
	reclaimMemory(root);
	root = nullptr;
}
//合并堆的接口函数
template<class Comparable>
void LeftistHeap<Comparable>::merge(LeftistHeap& rhs)
{
	if (this == &rhs)//避免复制自己
		return;
	root = merge(root, rhs.root);
	rhs.root = nullptr;
}

//合并驱动函数
template<class Comparable>
typename LeftistHeap<Comparable>::LeftistNode* LeftistHeap<Comparable>::merge(LeftistNode* node1, LeftistNode* node2)
{
	if (node1 == nullptr)
		return node2;
	if (node2 == nullptr)
		return node1;
	if (node1->element < node2->element)
		return actualMerge(node1, node2);
	else
		return actualMerge(node2, node1);
}
template<class Comparable>
typename LeftistHeap<Comparable>::LeftistNode* LeftistHeap<Comparable>::actualMerge(LeftistNode* smallerNode, LeftistNode* largerNode)
{
	//（大的根值的堆 与 小根值的堆的右子堆） 合并后的新堆 成为 小根值的堆的右儿子 
	smallerNode->right = merge(smallerNode->right, largerNode);
	if (getNpl(smallerNode->left) < getNpl(smallerNode->right))
		swapChildren(smallerNode);
	smallerNode->npl = getNpl(smallerNode->right) + 1;

	return smallerNode;
}
//获取节点的npl
template<class Comparable>
int LeftistHeap<Comparable>::getNpl(LeftistNode* node)
{
	if (node == nullptr)
		return -1;
	else
		return node->npl;
}

//交换两个儿子节点
template<class Comparable>
void LeftistHeap<Comparable>::swapChildren(LeftistNode* node)
{
	LeftistNode* temp = node->left;
	node->left = node->right;
	node->right = temp;
}

//释放堆的内存
template<class Comparable>
void LeftistHeap<Comparable>::reclaimMemory(LeftistNode* node)
{
	if (node == nullptr)
		return;
	reclaimMemory(node->left);
	reclaimMemory(node->right);
	delete node;
}

//克隆函数
template<class Comparable>
typename LeftistHeap<Comparable>::LeftistNode* LeftistHeap<Comparable>::clone(LeftistNode* node)
{
	if (node == nullptr)
		return nullptr;
	return new LeftistNode(node->element, clone(node->left), clone(node->right),node->npl);
}
//打印,参数为打印多少层,因为是不平衡树，所以有可能打多了或者打小了。
template<class Comparable>
void LeftistHeap<Comparable>::print(int layer)
{
	using namespace std;
	if (isEmpty())
	{
		cout << "Heap is empty!" << endl;
		return;
	}
	cout << "Heap:" << endl;
	queue<LeftistNode*> queue;
	queue.push(root);
	int maxnum = pow(2,layer) - 1;
	int addCount = 1;
	int layerCount = 1;
	int outCount = 0;
	LeftistNode* p;
	while (!queue.empty())
	{
		p = queue.front();
		queue.pop();
		if (p == nullptr)
		{
			cout << "NL" <<"("<<getNpl(p)<<")"<< ",";
			if (addCount + 2 <= maxnum)
			{
				queue.push(nullptr);
				queue.push(nullptr);
				addCount = addCount + 2;
			}
		}
		else
		{
			cout << p->element << "(" << getNpl(p) << ")" << ",";
			if (addCount + 2 <= maxnum)
			{
				queue.push(p->left);
				queue.push(p->right);
				addCount = addCount + 2;
			}
		}
		outCount++;
		if (outCount == pow(2, layerCount) - 1)
		{
			layerCount++;
			cout << endl;
		}
	}
}

#endif
