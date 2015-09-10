#ifndef _D_HEAP_H_
#define _D_HEAP_H_

#include <vector>
#include <exception>
#include <iostream>
#include <cmath>
/*
D-堆(d叉堆)：二叉堆的简单推广，d个儿子
用于insert比deleteMin次数多
从1开始计数。
对于i：第一个儿子：first = D*(i - 1) + 2，最后一个儿子：first + D - 1。
对于i：父节点为(int) ((i - 2 + D)/D)
insert：O(log d N)
deleteMin：O(d*log d N)
merge：合并两个堆的复杂度是O(n log d n)
*/
template<class Comparable,size_t D = 4>
class DHeap
{
public:
	explicit DHeap(int capacity = 100);
	explicit DHeap(const std::vector<Comparable>& items);

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


template<class Comparable, size_t D>
DHeap<Comparable,D>::DHeap(int capacity = 100) :currentSize(0)
{
	array.resize(capacity + 1);//第一个位置不用
}

template<class Comparable,  size_t D>
DHeap<Comparable,D>::DHeap(const std::vector<Comparable>& items)
{
	array.resize(items.size() + 1);//第一个位置不用
	int i = 1;
	for (auto it = items.begin(); it != items.end(); ++it)
	{
		array[i] = *it;
		++i;
	}
	currentSize = items.size();
	buildHeap();
}

template<class Comparable,  size_t D>
bool DHeap<Comparable, D>::isEmpty() const
{
	return (currentSize == 0) ? true : false;
}
template<class Comparable,  size_t D>
int DHeap<Comparable, D>::size()const
{
	return currentSize;
}
template<class Comparable,  size_t D>
Comparable DHeap<Comparable, D>::getMin() const
{
	if (isEmpty())
		throw std::runtime_error("Heap is Empty!");
	return array[1];
}

template<class Comparable,  size_t D>
void DHeap<Comparable, D>::insert(const Comparable & item)
{
	if (currentSize == array.size() - 1)
		array.resize(array.size() * 2);
	int hole = ++currentSize;
	array[hole] = item;
	percolateUp(hole);

}
template<class Comparable,  size_t D>
void DHeap<Comparable, D>::deleteMin()
{
	if (isEmpty())
		throw std::runtime_error("Heap is Empty!");
	array[1] = array[currentSize--];
	percolateDown(1);
}

template<class Comparable,  size_t D>
void DHeap<Comparable, D>::makeEmpty()
{
	array.resize(1);
	currentSize = 0;
}

template<class Comparable,  size_t D>
void DHeap<Comparable, D>::slim()
{
	if (array.size() - 1 > currentSize)
	{
		array.resize(currentSize + 1);
	}
}

template<class Comparable,  size_t D>
void DHeap<Comparable, D>::buildHeap()
{
	for (int i = (currentSize - 2 + D / D); i > 0; i--)//有孩子的节点是要进行堆调整的位置点
		percolateDown(i);
}

template<class Comparable,  size_t D>
void DHeap<Comparable,D>::percolateDown(int hole)
{
	Comparable temp = array[hole];
	int child;
	while (D*(hole - 1) + 2 <= currentSize)
	{
		child = D*(hole - 1) + 2;//第一个孩子
		int offset = 0;//找出最小的孩子节点
		for (int i = 1; i < D; i++)
		{
			if (child + i > currentSize)//是否越界
				break;
			else
			{
				if (array[child + offset] > array[child + i])
					offset = i;
			}
		}

		if (array[child + offset] < temp)//如果比儿子节点大，上移儿子节点
		{
			array[hole] = array[child + offset];
			hole = child + offset;//新的放置位置，继续测试新的位置是否满足
		}
		else
			break;//不比儿子节点大，满足条件，终止循环
	}
	array[hole] = temp;//最终的位置

}
template<class Comparable,  size_t D>
void DHeap<Comparable,D>::percolateUp(int hole)
{
	Comparable temp = array[hole];
	while (hole > 1)
	{
		int parent = (hole - 2 + D) / D;
		if (temp < array[parent])//如果比父节点大
		{
			array[hole] = array[parent];
			hole = parent;
		}
		else//不比父节点大，结束循环
			break;
	}
	array[hole] = temp;
}

template<class Comparable,  size_t D>
void DHeap<Comparable,D>::print()
{
	using namespace std;
	if (currentSize == 0)
	{
		cout << "print: Heap is empty!" << endl;
		return;
	}
	
	int height = log(currentSize)/log(D) + 1;
	cout << "Height: " << height << endl;
	int layer = 0;
	int count = 0;
	for (int i = 1; i <= currentSize; i++)
	{
		cout << array[i]<<" , ";
		count++;
		if (count == pow(D, layer))
		{
			count = 0;
			layer++;
			cout << endl;
		}
	}
	cout << endl;

}



#endif