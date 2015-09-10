#ifndef _BINARY_HEAP_H_
#define _BINARY_HEAP_H_

#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>
/*
二叉堆 最常用的优先队列
从1开始计数。
对于i：左儿子：2i ，右儿子：2i+1
对于i：父节点为(int)(i/2)
insert：O(logn)
deleteMin：O(logn)
buildHeap：平均时间是O(n)
decreaseKey：减少元素的值，然后上滤调整堆
increaseKey：增加元素的值，然后下滤调整堆
remove：删除非最顶元素，remove需要减少元素的值至无穷小（需要类型的支持，例如定义一个最大值），上滤然后调用deleteMin。
merge：合并两个堆的复杂度是O(nlogn)
*/
template<class Comparable>
class BinaryHeap
{
public:
	explicit BinaryHeap(int capacity = 100);
	explicit BinaryHeap(const std::vector<Comparable>& items);

	bool isEmpty() const;//是否为空
	int size() const;//堆元素个数
	Comparable getMin() const;//获取最小值
	void deleteMin();//删除最小值
	void insert(const Comparable & item);//插入元素
	void makeEmpty();//清空所有元素
	void slim();//减少数组大小
	void print();//打印
private:
	int currentSize;//堆元素个数
	std::vector<Comparable> array;//用于存放堆元素，第一个位置不用
	void buildHeap();//构建堆
	void percolateDown(int hole);//下滤操作
	void percolateUp(int hole);//上滤操作
};

template<class Comparable>
BinaryHeap<Comparable>::BinaryHeap(int capacity = 100) :currentSize(0)
{
	array.resize(capacity + 1);//第一个位置不用
}

template<class Comparable>
BinaryHeap<Comparable>::BinaryHeap(const std::vector<Comparable>& items)
{
	array.resize(items.size()+1);//第一个位置不用
	int i = 1;
	for (auto it = items.begin(); it != items.end();  ++it)
	{
		array[i] = *it;
		++i;
	}
	currentSize = items.size();
	buildHeap();
}

template<class Comparable>
bool BinaryHeap<Comparable>::isEmpty() const
{
	return (currentSize == 0) ? true : false;
}
template<class Comparable>
int BinaryHeap<Comparable>::size()const
{
	return currentSize;
}
template<class Comparable>
Comparable BinaryHeap<Comparable>::getMin() const
{
	if (isEmpty())
		throw std::runtime_error("Heap is Empty!");
	return array[1];
}

template<class Comparable>
void BinaryHeap<Comparable>::insert(const Comparable & item)
{
	if (currentSize == array.size() - 1)
		array.resize(array.size() * 2);
	int hole = ++currentSize;
	array[hole] = item;
	percolateUp(hole);

}
template<class Comparable>
void BinaryHeap<Comparable>::deleteMin()
{
	if (isEmpty())
		throw std::runtime_error("Heap is Empty!");
	array[1] = array[currentSize--];
	percolateDown(1);
}

template<class Comparable>
void BinaryHeap<Comparable>::makeEmpty()
{
	array.resize(1);
	currentSize = 0;
}

template<class Comparable>
void BinaryHeap<Comparable>::slim()
{
	if (array.size() - 1 > currentSize)
	{
		array.resize(currentSize + 1);
	}
}

template<class Comparable>
void BinaryHeap<Comparable>::buildHeap()
{
	for (int i = currentSize / 2; i > 0; i--)//有孩子的节点是要进行堆调整的位置点
		percolateDown(i);
}
template<class Comparable>
void BinaryHeap<Comparable>::percolateDown(int hole)
{
	Comparable temp = array[hole];
	int child;
	while (hole * 2 <= currentSize)
	{
		child = hole * 2;
		if (child < currentSize)//找出最小的儿子节点
		{
			if (array[child + 1] < array[child])
				child++;
		}
		if (array[child] < temp)//如果比儿子大，上移儿子节点
		{
			array[hole] = array[child];
			hole = child;//新的放置位置，继续测试新的位置是否满足
		}		
		else
			break;//不比儿子节点大，满足条件，终止循环
	}
	array[hole] = temp;
}
template<class Comparable>
void BinaryHeap<Comparable>::percolateUp(int hole)
{

	Comparable temp = array[hole];
	while (hole > 1)
	{
		if (temp < array[hole / 2])//如果比父节点大
		{
			array[hole] = array[hole / 2];
			hole = hole / 2;
		}
		else
			break;
	}
	array[hole] = temp;
}

template<class Comparable>
void BinaryHeap<Comparable>::print()
{
	using namespace std;
	if (currentSize == 0)
	{
		cout << "print: Heap is empty!" << endl;
		return;
	}
	
	int height = log2(currentSize) + 1;
	cout << "Height: " << height << endl;
	for (int i = 0; i < height; i++)
	{
		int temp = pow(2, height - i-1) - 1;
		while (temp>0)
		{
			cout << "  ";
			temp--;
		}
		temp = pow(2,i);
		while (temp < pow(2, i + 1))
		{
			cout << array[temp];
			int j = pow(2, height - i) - 1;
			while (j>0)
			{
				cout << "  ";
				j--;
			}
			temp++;
			if (temp>currentSize)
				break;
		}
		cout << endl;
	}
}

#endif