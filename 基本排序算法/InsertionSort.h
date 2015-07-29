#ifndef _INSERTION_SORT_
#define _INSERTION_SORT_
/*1.直接插入排序   2.二分插入排序   3.希尔排序*/
/*
直接插入排序
分为排序好的前半部分和没有排序的后半部分，
不断从后半部分取一个元素插入前半部分，对于
要插入的元素，从大到小跟前半部分比较，找到
插入的位置。前半部分插入位置后的元素后移一位。
O(n^2)
*/
template<typename T>
void insertSort(T array[],int size)
{
	for (int i = 1; i < size; i++)//从第二个开始，第一个就是有序的前半部分
	{	
		T temp = array[i];//保存插入值
		int j = i - 1;
		while (j >= 0 && temp < array[j])
		{
			array[j + 1] = array[j];
			j--;
		}
		if (j != i - 1)//如果存在大于temp，则插入，否则待在原地
		{
			array[j + 1] = temp;
		}
	}
}

/*
二分插入排序
跟直接插入排序类似，只是插入位置的寻找使用二分查找。
*/
template<typename T>
void binaryInsertSort(T array[],int size)
{
	for (int i = 1; i < size; i++)
	{
		T temp = array[i];
		int left = 0;
		int right = i - 1;
		while (left <= right)
		{
			int middle = (left + right) / 2;
			if (temp >= array[middle])
			{
				left = middle + 1;
			}
			else
			{
				right = middle - 1;
			}
		}

		for (int j = i - 1; j >= left; j--)//left就是要插入的位置，将left以后的位置元素全部后移
		{
			array[j + 1] = array[j];
		}
		array[left] = temp;
	}

}

/*
希尔排序
也是插入排序的一种，更高效的插入排序
基本思想是，将整个待排序序列分割成若干子序列（由相隔某个增量），
分别进行直接插入排序，然后依次缩减增量（直到增量为1），希尔排序
可以大大减少移动的次数。
一般增量取序列大小的一半，然后依次减半，直到增量为1。
O(nlogn)
*/
template<typename T>
void shellSort(T array[],int size)
{
	for (int gap = size / 2; gap > 0; gap = gap / 2)
	{
		for (int i = 0; i < gap; i++)
		{
			for (int j = i + gap; j < size; j += gap)
			{
				if (array[j] < array[j - gap])
				{
					T temp = array[j];
					int k = j - gap;
					while (k >= 0 && temp < array[k])
					{
						array[k + gap] = array[k];
						k -= gap;
					}
					array[k + gap] = temp;
				}
			}
		}
	}

}
#endif