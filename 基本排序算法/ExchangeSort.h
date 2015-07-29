#ifndef _EXCHANGE_SORT_H_
#define _EXCHANGE_SORT_H_

/*1.冒泡排序  2.快速排序  3.非递归实现的快速排序 */

/*
冒泡排序
冒泡排序算法的运作如下：
1.比较相邻的元素。如果第一个比第二个大，就交换他们两个。
2.对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对。在这一点，最后的元素应该会是最大的数。
3.针对所有的元素重复以上的步骤，除了最后一个。
4.持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。

*/

template<typename T>
void bubbleSort(T array[],int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (array[j]>array[j + 1])
			{
				T temp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = temp;
			}
		}
	}
}

/*
快速排序
1.选择一个基准元素,通常选择第一个元素或者最后一个元素
2.通过一趟排序讲待排序的记录分割成独立的两部分，其中一部分记录的元素值均比基准元素值小。另一部分记录的 元素值比基准值大。
3.此时基准元素在其排好序后的正确位置
4.然后分别对这两部分记录用同样的方法继续进行排序，直到整个序列有序。
*/
template<typename T>
void printQ(T* array, int left,int right)//辅助输出排序信息
{
	for (int i = left; i <= right; i++)
	{
		cout << array[i] << ",";
	}
	cout << endl;
}
template<typename T>
void quickSort(T array[],int left,int right)
{
	if (left >= right)//递归终止条件
		return;

	int i = left;
	int j = right;
	T key = array[left];

	while (i < j)
	{
		while (i < j && key <= array[j])
		{
			j--;
		}
		array[i] = array[j];
		while (i < j && key >= array[i])
		{
			i++;
		}
		array[j] = array[i];
	}
	array[i] = key;
	printQ(array,left,right);//辅助输出排序信息
	quickSort(array,left,i-1);
	quickSort(array,i+1,right);
}


//将分区提取出来,变成一个函数
template<typename T>
int partition(T array[],int left,int right)
{
	T key = array[left];

	while (left < right)
	{
		while (left < right && key <= array[right])
		{
			right--;
		}
		array[left] = array[right];
		while (left < right && key >= array[left])
		{
			left++;
		}
		array[right] = array[left];
	}
	array[left] = key;
	return left;
}

template<typename T>
void quickSort2(T array[],int left,int right)
{
	if (left < right)
	{
		int pos = partition(array,left,right);
		quickSort2(array, left, pos - 1);
		quickSort2(array, pos + 1, right);
	}
}

/*
快速排序：非递归实现
*/
#include <stack>
typedef struct Section
{
	int left;
	int right;
}Section;

template<typename T>
void nonRecursionQuickSort(T array[],int size)
{
	stack<Section> sectionStack;//定义一个区间的栈变量
	Section section;
	section.left = 0;
	section.right = size - 1;
	sectionStack.push(section);

	while (!sectionStack.empty())
	{
		section = sectionStack.top();
		sectionStack.pop();
		int pos = partition(array,section.left,section.right);
		if (pos - 1 > section.left)
		{
			Section newSection;
			newSection.left = section.left;
			newSection.right = pos - 1;
			sectionStack.push(newSection);
		}
		if (pos + 1 < section.right)
		{
			Section newSection;
			newSection.left = pos + 1;
			newSection.right = section.right;
			sectionStack.push(newSection);
		}
	}
}

#endif