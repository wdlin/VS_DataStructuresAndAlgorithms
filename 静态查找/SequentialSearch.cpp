#include "Search.h"

int sequential_search(int* array, int size, int key)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == key)
			return i;
	}
	return -1;
}


/*
�����һ��Ԫ����Ϊ�ڱ�(���洢��Ч����)�����Լ����ж�����Խ��ıȽϣ���߲����ٶȣ���ʱ0Ϊû���ҵ���
*/
int sequential_search2(int* array, int size, int key)
{
	array[0] = key;
	int i;
	for (i = size - 1; array[i] != array[0]; i--);
	return i;
}
