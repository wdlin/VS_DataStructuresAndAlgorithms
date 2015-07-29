#ifndef _INSERTION_SORT_
#define _INSERTION_SORT_
/*1.ֱ�Ӳ�������   2.���ֲ�������   3.ϣ������*/
/*
ֱ�Ӳ�������
��Ϊ����õ�ǰ�벿�ֺ�û������ĺ�벿�֣�
���ϴӺ�벿��ȡһ��Ԫ�ز���ǰ�벿�֣�����
Ҫ�����Ԫ�أ��Ӵ�С��ǰ�벿�ֱȽϣ��ҵ�
�����λ�á�ǰ�벿�ֲ���λ�ú��Ԫ�غ���һλ��
O(n^2)
*/
template<typename T>
void insertSort(T array[],int size)
{
	for (int i = 1; i < size; i++)//�ӵڶ�����ʼ����һ�����������ǰ�벿��
	{	
		T temp = array[i];//�������ֵ
		int j = i - 1;
		while (j >= 0 && temp < array[j])
		{
			array[j + 1] = array[j];
			j--;
		}
		if (j != i - 1)//������ڴ���temp������룬�������ԭ��
		{
			array[j + 1] = temp;
		}
	}
}

/*
���ֲ�������
��ֱ�Ӳ����������ƣ�ֻ�ǲ���λ�õ�Ѱ��ʹ�ö��ֲ��ҡ�
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

		for (int j = i - 1; j >= left; j--)//left����Ҫ�����λ�ã���left�Ժ��λ��Ԫ��ȫ������
		{
			array[j + 1] = array[j];
		}
		array[left] = temp;
	}

}

/*
ϣ������
Ҳ�ǲ��������һ�֣�����Ч�Ĳ�������
����˼���ǣ����������������зָ�����������У������ĳ����������
�ֱ����ֱ�Ӳ�������Ȼ����������������ֱ������Ϊ1����ϣ������
���Դ������ƶ��Ĵ�����
һ������ȡ���д�С��һ�룬Ȼ�����μ��룬ֱ������Ϊ1��
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