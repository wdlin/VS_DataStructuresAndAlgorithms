#ifndef _SELECTION_SORT_
#define _SELECTION_SORT_
/*1.简单选择排序  2.堆排序  */

/*
简单选择排序
在待排序中，选择最小的（或者最大）的一个数与第一个位置交换；
剩下的数继续选择最小的与第二位置的数交换，直到第n-1个与第n个
元素比较为止。
O(n^2)
*/
template<typename T>
int minIndex(int array[],int begin,int end)
{
	int index = begin;
	for (int i = begin + 1; i <= end; i++)
	{
		if (array[i] < array[index])
		{
			index = i;
		}
	}
	return index;
}
template<typename T>
void selectionSort(T array[],int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int index = minIndex<T>(array, i + 1, size - 1);
		if (array[i] > array[index])
		{
			T temp = array[i];
			array[i] = array[index];
			array[index] = temp;
		}
	}
}

//只用一个函数
template<typename T>
void selectionSort2(T array[],int size)
{
	for (int i = 0; i < size; i++)
	{
		int minIndex = i;//找出最小的位置
		for (int j = i + 1; j < size; j++)
		{
			if (array[minIndex] > array[j])
			{
				minIndex = j;
			}
		}

		if (minIndex != i)//如果不是当前位置，则交换位置
		{
			T temp = array[i];
			array[i] = array[minIndex];
			array[minIndex] = temp;
		}
	}
}

/*
堆排序
初始时把要排序的n个数的序列看作是一棵顺序存储的二叉树（一维数组存储二叉树），
调整它们的存储序，使之成为一个堆，将堆顶元素输出，得到n 个元素中最小(或最大)的元素，
这时堆的根节点的数最小（或者最大）。然后对前面(n-1)个元素重新调整使之成为堆，
输出堆顶元素，得到n 个元素中次小(或次大)的元素。依此类推，直到只有两个节点的堆，
并对它们作交换，最后得到有n个节点的有序序列。称这个过程为堆排序。
O(nlogn)
*/
//size数组的大小 pos有孩子的要进行堆调整的位置点
template<typename T>
void heapAdjust(T array[], int size, int pos)
{
	int childPos = 2 * pos + 1;//左孩子位置，右孩子（childPos++）
	while (childPos < size)
	{
		if (childPos + 1 < size && array[childPos] < array[childPos + 1])//选出较大的孩子
		{
			childPos++;
		}
		if (array[pos] < array[childPos])//如果需要调整，那么孩子的值就会变化，那么就需要重新调整孩子子树
		{
			T temp = array[pos];
			array[pos] = array[childPos];
			array[childPos] = temp;

			pos = childPos;
			childPos = 2 * pos + 1;
		}
		else//如果不需要调整，那么也不需要调整孩子子树，退出循环
		{
			break;
		}
	}
}



template<typename T>
void heapSort(T array[],int size)
{
	//初始化堆
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		heapAdjust<T>(array,size,i);
	}
	//开始排序，每次将堆顶交换至末尾，然后继续调整堆，最后排序完成
	for (int i = size - 1; i > 0; --i)
	{
		T temp = array[i];
		array[i] = array[0];
		array[0] = temp;
		heapAdjust<T>(array,i,0);
	}
}


#endif