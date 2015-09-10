#ifndef _BINOMIAL_HEAP_H_
#define _BINOMIAL_HEAP_H_
#include <vector>
/*
����ѣ�������У� BinomialHeap
������Ƕ������ļ��ϣ�ɭ�֣�
��������
�������ĵݹ鶨�壺
�������ĵ�0����ֻ��һ����㣻
�������ĵ�K����ͨ����һ��B k-1���ӵ���һ����B k-1�ĸ����ɡ�
Ҳ�����������壺
����Ϊ0�Ķ�����ֻ����һ�����
����Ϊk�Ķ�������һ������㣬���������k����Ů��ÿ����Ů�ֱ��Ƕ���Ϊk-1,k-2,��,0�Ķ������ĸ�

ʱ�临�Ӷ�
insert��log(n)
findMin��log(n)
deleteMin��log(n)
delete(node)��log(n)
decreaseKey(node)��log(n) (����ͨ�����Ӹ��ڵ������ָ��)
merge(heap1,heap)��log(n)

*/
template<class Comparable>
class BinomialHeap
{
public:
	BinomialHeap(unsigned int treesNum = 5);//���캯��������Ϊ�����С������������Ŀ�����
	BinomialHeap(const Comparable& item, unsigned int treesNum = 5);//���캯���������һ��Ԫ��
	BinomialHeap(const BinomialHeap& rhs);//�������캯��
	~BinomialHeap();//��������
	BinomialHeap& operator=(const BinomialHeap& rhs);//��ֵ������
	bool isEmpty() const;//�Ƿ�Ϊ��
	Comparable getMin() const;//��ȡ��Сֵ
	void deleteMin();//ɾ����Сֵ
	void insert(const Comparable & item);//����Ԫ��
	void makeEmpty();//�������Ԫ��
	void merge(BinomialHeap& rhs);//�ϲ��ӿں���
	void print();
private:
	struct BinomialNode
	{
		Comparable element;//Ԫ��
		BinomialNode* leftChild;//����
		BinomialNode* nextSibling;//�ֵ�

		BinomialNode(const Comparable& theElement,BinomialNode* lc,BinomialNode* ns)
			:element(theElement),leftChild(lc),nextSibling(ns){}
	};

	int currentSize;//Ԫ�ظ���
	std::vector<BinomialNode*> trees;//�������ĸ��ڵ�

	int findMinIndex() const;//�ҳ���С�Ľڵ����ڵ���
	int capacity()const;//��ȡ��ǰ�������ɵ�Ԫ�ظ���
	BinomialNode* combineTrees(BinomialNode* node1,BinomialNode* node2);//�ϲ������߶���ͬ���������غϲ��������
	void makeEmpty(BinomialNode*& node);//���һ����
	BinomialNode* clone(BinomialNode* node) const;//����һ����
};
//���캯��������Ϊ�����С������������Ŀ�����
template<class Comparable>
BinomialHeap<Comparable>::BinomialHeap(unsigned int treesNum) :currentSize(0)
{
	trees.resize(treesNum);
	for (int i = 0; i < treesNum; i++)
		trees[i] = nullptr;
}
//���캯���������һ��Ԫ��
template<class Comparable>
BinomialHeap<Comparable>::BinomialHeap(const Comparable& item, unsigned int treesNum) :currentSize(1)
{
	trees.resize(treesNum);
	for (int i = 0; i < treesNum; i++)
		trees[i] = nullptr;

	trees[0] = new BinomialNode(item, nullptr, nullptr);

}
//�������캯��
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
//��ֵ������
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
//��������
template<class Comparable>
BinomialHeap<Comparable>::~BinomialHeap()
{
	makeEmpty();
}
//�Ƿ�Ϊ��
template<class Comparable>
bool BinomialHeap<Comparable>::isEmpty() const
{
	return currentSize == 0;
}
//��ȡ��Сֵ
template<class Comparable>
Comparable BinomialHeap<Comparable>::getMin() const
{
	if (isEmpty())
		throw std::runtime_error("Heap is Empty!");
	int index = findMinIndex();
	return trees[index]->element;
}
//ɾ����Сֵ
template<class Comparable>
void BinomialHeap<Comparable>::deleteMin()
{
	if (isEmpty())
		throw std::runtime_error("Heap is Empty!");
	int minIndex = findMinIndex();
	//ɾ����С�ڵ����С�ڵ����ڵ������minIndex - 1��С��������һ���µĶ���ѣ�
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
	//���������ĺϲ���ȥ
	merge(tempHeap);
}
//����Ԫ��
template<class Comparable>
void BinomialHeap<Comparable>::insert(const Comparable & item)
{
	BinomialHeap tempHeap(item, 1);
	merge(tempHeap);
}
//�������Ԫ��
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

//�ϲ��ӿں���
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
		//��Ϊ�������洦�����ѵ�size�϶� >= rhs��size
		BinomialNode* node1 = trees[i];
		BinomialNode* node2 = (i < rhs.trees.size()) ? rhs.trees[i] : nullptr;

		int whichCase = (node1 == nullptr) ? 0 : 1;
		whichCase += (node2 == nullptr) ? 0 : 2;
		whichCase += (carry == nullptr) ? 0 : 4;
		switch (whichCase)
		{
		case 0://û����
		case 1://ֻ���Լ�����
			break; 
		case 2://ֻ��rhs����
			trees[i] = node2;
			break;
		case 3://�Լ���rhs����
			carry = combineTrees(node1, node2);
			trees[i] = nullptr;
			break;
		case 4://ֻ��carry����
			trees[i] = carry;
			carry = nullptr;
			break;
		case 5://�Լ���carry����
			carry = combineTrees(node1, carry);
			trees[i] = nullptr;
			break;
		case 6://rhs��carry����
			carry = combineTrees(node2, carry);
			break;
		case 7://�Լ���rhs��carry������
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
	//���Ѵ�ӡ
}
//�ҳ���С�Ľڵ����ڵ���
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
//��ȡ��ǰ�������ɵ�Ԫ�ظ���
template<class Comparable>
int BinomialHeap<Comparable>::capacity()const
{
	//2^0 + 2^1+ 2^2 ... = 2^n - 1
	int cap = (1 << trees.size()) - 1;
	return cap;
}
//�ϲ������߶���ͬ���������غϲ��������
template<class Comparable>
typename BinomialHeap<Comparable>::BinomialNode* BinomialHeap<Comparable>::combineTrees(BinomialNode* node1, BinomialNode* node2)
{
	//��Ľڵ��ΪС�Ľڵ�Ķ���
	if (node2->element < node1->element)
		return combineTrees(node2, node1);
	node2->nextSibling = node1->leftChild;
	node1->leftChild = node2;
	return node1;
}
//���һ����
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
//����һ����
template<class Comparable>
typename BinomialHeap<Comparable>::BinomialNode* BinomialHeap<Comparable>::clone(BinomialNode* node) const
{
	if (node == nullptr)
		return nullptr;
	return new BinomialNode(node->element, clone(node->leftChild), clone(node->nextSibling));
}



#endif