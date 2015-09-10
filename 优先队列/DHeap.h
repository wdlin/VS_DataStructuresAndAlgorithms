#ifndef _D_HEAP_H_
#define _D_HEAP_H_

#include <vector>
#include <exception>
#include <iostream>
#include <cmath>
/*
D-��(d���)������ѵļ��ƹ㣬d������
����insert��deleteMin������
��1��ʼ������
����i����һ�����ӣ�first = D*(i - 1) + 2�����һ�����ӣ�first + D - 1��
����i�����ڵ�Ϊ(int) ((i - 2 + D)/D)
insert��O(log d N)
deleteMin��O(d*log d N)
merge���ϲ������ѵĸ��Ӷ���O(n log d n)
*/
template<class Comparable,size_t D = 4>
class DHeap
{
public:
	explicit DHeap(int capacity = 100);
	explicit DHeap(const std::vector<Comparable>& items);

	bool isEmpty() const;//�Ƿ�Ϊ��
	int size() const;//��Ԫ�ظ���
	Comparable getMin() const;//��ȡ��Сֵ
	void deleteMin();//ɾ����Сֵ
	void insert(const Comparable & item);//����Ԫ��
	void makeEmpty();//�������Ԫ��
	void slim();//���������С
	void print();//��ӡ
private:
	int currentSize;//��Ԫ�ظ���
	std::vector<Comparable> array;//���ڴ�Ŷ�Ԫ�أ���һ��λ�ò���
	void buildHeap();//������
	void percolateDown(int hole);//���˲���
	void percolateUp(int hole);//���˲���

};


template<class Comparable, size_t D>
DHeap<Comparable,D>::DHeap(int capacity = 100) :currentSize(0)
{
	array.resize(capacity + 1);//��һ��λ�ò���
}

template<class Comparable,  size_t D>
DHeap<Comparable,D>::DHeap(const std::vector<Comparable>& items)
{
	array.resize(items.size() + 1);//��һ��λ�ò���
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
	for (int i = (currentSize - 2 + D / D); i > 0; i--)//�к��ӵĽڵ���Ҫ���жѵ�����λ�õ�
		percolateDown(i);
}

template<class Comparable,  size_t D>
void DHeap<Comparable,D>::percolateDown(int hole)
{
	Comparable temp = array[hole];
	int child;
	while (D*(hole - 1) + 2 <= currentSize)
	{
		child = D*(hole - 1) + 2;//��һ������
		int offset = 0;//�ҳ���С�ĺ��ӽڵ�
		for (int i = 1; i < D; i++)
		{
			if (child + i > currentSize)//�Ƿ�Խ��
				break;
			else
			{
				if (array[child + offset] > array[child + i])
					offset = i;
			}
		}

		if (array[child + offset] < temp)//����ȶ��ӽڵ�����ƶ��ӽڵ�
		{
			array[hole] = array[child + offset];
			hole = child + offset;//�µķ���λ�ã����������µ�λ���Ƿ�����
		}
		else
			break;//���ȶ��ӽڵ��������������ֹѭ��
	}
	array[hole] = temp;//���յ�λ��

}
template<class Comparable,  size_t D>
void DHeap<Comparable,D>::percolateUp(int hole)
{
	Comparable temp = array[hole];
	while (hole > 1)
	{
		int parent = (hole - 2 + D) / D;
		if (temp < array[parent])//����ȸ��ڵ��
		{
			array[hole] = array[parent];
			hole = parent;
		}
		else//���ȸ��ڵ�󣬽���ѭ��
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