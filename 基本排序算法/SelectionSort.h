#ifndef _SELECTION_SORT_
#define _SELECTION_SORT_
/*1.��ѡ������  2.������  */

/*
��ѡ������
�ڴ������У�ѡ����С�ģ�������󣩵�һ�������һ��λ�ý�����
ʣ�µ�������ѡ����С����ڶ�λ�õ���������ֱ����n-1�����n��
Ԫ�رȽ�Ϊֹ��
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

//ֻ��һ������
template<typename T>
void selectionSort2(T array[],int size)
{
	for (int i = 0; i < size; i++)
	{
		int minIndex = i;//�ҳ���С��λ��
		for (int j = i + 1; j < size; j++)
		{
			if (array[minIndex] > array[j])
			{
				minIndex = j;
			}
		}

		if (minIndex != i)//������ǵ�ǰλ�ã��򽻻�λ��
		{
			T temp = array[i];
			array[i] = array[minIndex];
			array[minIndex] = temp;
		}
	}
}

/*
������
��ʼʱ��Ҫ�����n���������п�����һ��˳��洢�Ķ�������һά����洢����������
�������ǵĴ洢��ʹ֮��Ϊһ���ѣ����Ѷ�Ԫ��������õ�n ��Ԫ������С(�����)��Ԫ�أ�
��ʱ�ѵĸ��ڵ������С��������󣩡�Ȼ���ǰ��(n-1)��Ԫ�����µ���ʹ֮��Ϊ�ѣ�
����Ѷ�Ԫ�أ��õ�n ��Ԫ���д�С(��δ�)��Ԫ�ء��������ƣ�ֱ��ֻ�������ڵ�Ķѣ�
�������������������õ���n���ڵ���������С����������Ϊ������
O(nlogn)
*/
//size����Ĵ�С pos�к��ӵ�Ҫ���жѵ�����λ�õ�
template<typename T>
void heapAdjust(T array[], int size, int pos)
{
	int childPos = 2 * pos + 1;//����λ�ã��Һ��ӣ�childPos++��
	while (childPos < size)
	{
		if (childPos + 1 < size && array[childPos] < array[childPos + 1])//ѡ���ϴ�ĺ���
		{
			childPos++;
		}
		if (array[pos] < array[childPos])//�����Ҫ��������ô���ӵ�ֵ�ͻ�仯����ô����Ҫ���µ�����������
		{
			T temp = array[pos];
			array[pos] = array[childPos];
			array[childPos] = temp;

			pos = childPos;
			childPos = 2 * pos + 1;
		}
		else//�������Ҫ��������ôҲ����Ҫ���������������˳�ѭ��
		{
			break;
		}
	}
}



template<typename T>
void heapSort(T array[],int size)
{
	//��ʼ����
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		heapAdjust<T>(array,size,i);
	}
	//��ʼ����ÿ�ν��Ѷ�������ĩβ��Ȼ����������ѣ�����������
	for (int i = size - 1; i > 0; --i)
	{
		T temp = array[i];
		array[i] = array[0];
		array[0] = temp;
		heapAdjust<T>(array,i,0);
	}
}


#endif