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
如果第一个元素作为哨兵(不存储有效数据)，可以减少判断数组越界的比较，提高查找速度，此时0为没有找到。
*/
int sequential_search2(int* array, int size, int key)
{
	array[0] = key;
	int i;
	for (i = size - 1; array[i] != array[0]; i--);
	return i;
}
