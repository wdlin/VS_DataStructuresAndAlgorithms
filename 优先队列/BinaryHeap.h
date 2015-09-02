#ifndef _BINARY_HEAP_H_
#define _BINARY_HEAP_H_

#include <vector>
#include <exception>
#include <iostream>
#include <cmath>
template<class Comparable>
class BinaryHeap
{
public:
	explicit BinaryHeap(int capacity = 100);
	explicit BinaryHeap(const std::vector<Comparable>& items);

	bool isEmpty() const;
	int size() const;
	Comparable getMin() const;
	void deleteMin();
	void insert(const Comparable & item);
	void makeEmpty();
	void slim();
	void print();
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
			hole = child;
		}		
		else
			break;
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