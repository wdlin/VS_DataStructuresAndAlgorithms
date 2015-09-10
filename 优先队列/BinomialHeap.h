#ifndef _BINOMIAL_HEAP_H_
#define _BINOMIAL_HEAP_H_
#include <vector>
/*
二项堆（二项队列） BinomialHeap
二项堆是二项树的集合（森林）
二项树：
二项树的递归定义：
二项树的第0棵树只有一个结点；
二项树的第K棵树通过将一棵B k-1连接到另一颗树B k-1的根构成。
也可以这样定义：
度数为0的二项树只包含一个结点
度数为k的二项树有一个根结点，根结点下有k个子女，每个子女分别是度数为k-1,k-2,…,0的二项树的根

时间复杂度
insert：log(n)
findMin：log(n)
deleteMin：log(n)
delete(node)：log(n)
decreaseKey(node)：log(n) (可以通过增加父节点的链接指针)
merge(heap1,heap)：log(n)

*/
template<class Comparable>
class BinomialHeap
{
public:
	BinomialHeap(unsigned int treesNum = 5);//构造函数，参数为数组大小（最多容纳树的棵数）
	BinomialHeap(const Comparable& item, unsigned int treesNum = 5);//构造函数，加入第一个元素
	BinomialHeap(const BinomialHeap& rhs);//拷贝构造函数
	~BinomialHeap();//析构函数
	BinomialHeap& operator=(const BinomialHeap& rhs);//赋值操作符
	bool isEmpty() const;//是否为空
	Comparable getMin() const;//获取最小值
	void deleteMin();//删除最小值
	void insert(const Comparable & item);//插入元素
	void makeEmpty();//清空所有元素
	void merge(BinomialHeap& rhs);//合并接口函数
	void print();
private:
	struct BinomialNode
	{
		Comparable element;//元素
		BinomialNode* leftChild;//儿子
		BinomialNode* nextSibling;//兄弟

		BinomialNode(const Comparable& theElement,BinomialNode* lc,BinomialNode* ns)
			:element(theElement),leftChild(lc),nextSibling(ns){}
	};

	int currentSize;//元素个数
	std::vector<BinomialNode*> trees;//所有树的根节点

	int findMinIndex() const;//找出最小的节点所在的树
	int capacity()const;//获取当前可以容纳的元素个数
	BinomialNode* combineTrees(BinomialNode* node1,BinomialNode* node2);//合并两个高度相同的树，返回合并后的树根
	void makeEmpty(BinomialNode*& node);//清空一棵树
	BinomialNode* clone(BinomialNode* node) const;//复制一棵树
};
//构造函数，参数为数组大小（最多容纳树的棵数）
template<class Comparable>
BinomialHeap<Comparable>::BinomialHeap(unsigned int treesNum) :currentSize(0)
{
	trees.resize(treesNum);
	for (int i = 0; i < treesNum; i++)
		trees[i] = nullptr;
}
//构造函数，加入第一个元素
template<class Comparable>
BinomialHeap<Comparable>::BinomialHeap(const Comparable& item, unsigned int treesNum) :currentSize(1)
{
	trees.resize(treesNum);
	for (int i = 0; i < treesNum; i++)
		trees[i] = nullptr;

	trees[0] = new BinomialNode(item, nullptr, nullptr);

}
//拷贝构造函数
template<class Comparable>
BinomialHeap<Comparable>::BinomialHeap(const BinomialHeap& rhs)
{
	currentSize = rhs.currentSize;
	trees.resize(rhs.trees.size());
	for (int i = 0; i < rhs.trees.size(); i++)
	{
		if (rhs.trees[i] != nullptr)
		{
			trees[i] = clone(rhs.trees[i]);
		}
	}
}
//赋值操作符
template<class Comparable>
typename BinomialHeap<Comparable>& BinomialHeap<Comparable>::operator=(const BinomialHeap& rhs)
{
	makeEmpty();
	currentSize = rhs.currentSize;
	trees.resize(rhs.trees.size());
	for (int i = 0; i < rhs.trees.size(); i++)
	{
		if (rhs.trees[i] != nullptr)
		{
			trees[i] = clone(rhs.trees[i]);
		}
	}
	return *this;
}
//析构函数
template<class Comparable>
BinomialHeap<Comparable>::~BinomialHeap()
{
	makeEmpty();
}
//是否为空
template<class Comparable>
bool BinomialHeap<Comparable>::isEmpty() const
{
	return currentSize == 0;
}
//获取最小值
template<class Comparable>
Comparable BinomialHeap<Comparable>::getMin() const
{
	if (isEmpty())
		throw std::runtime_error("Heap is Empty!");
	int index = findMinIndex();
	return trees[index]->element;
}
//删除最小值
template<class Comparable>
void BinomialHeap<Comparable>::deleteMin()
{
	if (isEmpty())
		throw std::runtime_error("Heap is Empty!");
	int minIndex = findMinIndex();
	//删除最小节点后，最小节点所在的树变成minIndex - 1棵小树（看成一个新的二项堆）
	BinomialNode* deletedTrees = trees[minIndex]->leftChild;
	delete trees[minIndex];
	trees[minIndex] = nullptr;
	currentSize -= (1 << minIndex);

	BinomialHeap tempHeap(minIndex - 1);
	tempHeap.currentSize = (1 << minIndex) - 1;
	for (int i = minIndex - 1; i >= 0; i--)
	{
		tempHeap.trees[i] = deletedTrees;
		deletedTrees = deletedTrees->nextSibling;
		tempHeap.trees[i]->nextSibling = nullptr;
	}
	//将遗留树的合并回去
	merge(tempHeap);
}
//插入元素
template<class Comparable>
void BinomialHeap<Comparable>::insert(const Comparable & item)
{
	BinomialHeap tempHeap(item, 1);
	merge(tempHeap);
}
//清空所有元素
template<class Comparable>
void BinomialHeap<Comparable>::makeEmpty()
{
	for (int i = 0; i < trees.size(); i++)
	{
		if (trees[i] != nullptr)
			makeEmpty(trees[i]);
		trees[i] = nullptr;
	}
	currentSize = 0;
}

//合并接口函数
template<class Comparable>
void BinomialHeap<Comparable>::merge(BinomialHeap& rhs)
{
	if (this == &rhs)
		return;

	currentSize += rhs.currentSize;

	if (currentSize > capacity())
	{
		int oldTreesNum = trees.size();
		int newTreesNum = (oldTreesNum > rhs.trees.size() ? oldTreesNum : rhs.trees.size()) + 1;
		trees.resize(newTreesNum);
		for (int i = oldTreesNum; i < newTreesNum; i++)
			trees[i] = nullptr;
	}
	BinomialNode* carry = nullptr;
	for (int i = 0; i < trees.size(); i++)
	{
		//因为经过上面处理，本堆的size肯定 >= rhs的size
		BinomialNode* node1 = trees[i];
		BinomialNode* node2 = (i < rhs.trees.size()) ? rhs.trees[i] : nullptr;

		int whichCase = (node1 == nullptr) ? 0 : 1;
		whichCase += (node2 == nullptr) ? 0 : 2;
		whichCase += (carry == nullptr) ? 0 : 4;
		switch (whichCase)
		{
		case 0://没有树
		case 1://只有自己有树
			break; 
		case 2://只有rhs有树
			trees[i] = node2;
			break;
		case 3://自己和rhs有树
			carry = combineTrees(node1, node2);
			trees[i] = nullptr;
			break;
		case 4://只有carry有树
			trees[i] = carry;
			carry = nullptr;
			break;
		case 5://自己和carry有树
			carry = combineTrees(node1, carry);
			trees[i] = nullptr;
			break;
		case 6://rhs和carry有树
			carry = combineTrees(node2, carry);
			break;
		case 7://自己、rhs和carry都有树
			trees[i] = carry;
			carry = combineTrees(node1, node2);
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < rhs.trees.size(); i++)
		rhs.trees[i] = nullptr;
	rhs.currentSize = 0;

}

template<class Comparable>
void BinomialHeap<Comparable>::print()
{
	//很难打印
}
//找出最小的节点所在的树
template<class Comparable>
int BinomialHeap<Comparable>::findMinIndex() const
{
	if (currentSize == 0)
		return -1;
	int i;
	int minIndex;
	for (i = 0; trees[i] == nullptr; i++)
		;
	
	for (minIndex = i; i < trees.size(); i++)
	{
		if (trees[i] != nullptr && trees[i]->element < trees[minIndex]->element)
			minIndex = i;
	}
	return minIndex;
}
//获取当前可以容纳的元素个数
template<class Comparable>
int BinomialHeap<Comparable>::capacity()const
{
	//2^0 + 2^1+ 2^2 ... = 2^n - 1
	int cap = (1 << trees.size()) - 1;
	return cap;
}
//合并两个高度相同的树，返回合并后的树根
template<class Comparable>
typename BinomialHeap<Comparable>::BinomialNode* BinomialHeap<Comparable>::combineTrees(BinomialNode* node1, BinomialNode* node2)
{
	//大的节点成为小的节点的儿子
	if (node2->element < node1->element)
		return combineTrees(node2, node1);
	node2->nextSibling = node1->leftChild;
	node1->leftChild = node2;
	return node1;
}
//清空一棵树
template<class Comparable>
void BinomialHeap<Comparable>::makeEmpty(BinomialNode*& node)
{
	if (node == nullptr)
		return;
	makeEmpty(node->leftChild);
	node->leftChild = nullptr;
	makeEmpty(node->nextSibling);
	node->nextSibling = nullptr;
	delete node;
	node = nullptr;
}
//复制一棵树
template<class Comparable>
typename BinomialHeap<Comparable>::BinomialNode* BinomialHeap<Comparable>::clone(BinomialNode* node) const
{
	if (node == nullptr)
		return nullptr;
	return new BinomialNode(node->element, clone(node->leftChild), clone(node->nextSibling));
}



#endif