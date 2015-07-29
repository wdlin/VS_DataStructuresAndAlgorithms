#ifndef _EXCHANGE_SORT_H_
#define _EXCHANGE_SORT_H_

/*1.ð������  2.��������  3.�ǵݹ�ʵ�ֵĿ������� */

/*
ð������
ð�������㷨���������£�
1.�Ƚ����ڵ�Ԫ�ء������һ���ȵڶ����󣬾ͽ�������������
2.��ÿһ������Ԫ����ͬ���Ĺ������ӿ�ʼ��һ�Ե���β�����һ�ԡ�����һ�㣬����Ԫ��Ӧ�û�����������
3.������е�Ԫ���ظ����ϵĲ��裬�������һ����
4.����ÿ�ζ�Խ��Խ�ٵ�Ԫ���ظ�����Ĳ��裬ֱ��û���κ�һ��������Ҫ�Ƚϡ�

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
��������
1.ѡ��һ����׼Ԫ��,ͨ��ѡ���һ��Ԫ�ػ������һ��Ԫ��
2.ͨ��һ�����򽲴�����ļ�¼�ָ�ɶ����������֣�����һ���ּ�¼��Ԫ��ֵ���Ȼ�׼Ԫ��ֵС����һ���ּ�¼�� Ԫ��ֵ�Ȼ�׼ֵ��
3.��ʱ��׼Ԫ�������ź�������ȷλ��
4.Ȼ��ֱ���������ּ�¼��ͬ���ķ���������������ֱ��������������
*/
template<typename T>
void printQ(T* array, int left,int right)//�������������Ϣ
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
	if (left >= right)//�ݹ���ֹ����
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
	printQ(array,left,right);//�������������Ϣ
	quickSort(array,left,i-1);
	quickSort(array,i+1,right);
}


//��������ȡ����,���һ������
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
�������򣺷ǵݹ�ʵ��
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
	stack<Section> sectionStack;//����һ�������ջ����
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