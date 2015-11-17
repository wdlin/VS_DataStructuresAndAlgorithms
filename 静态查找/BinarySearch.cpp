#include "Search.h"

/*
���ֲ���
���Ա��еļ�¼�����ǹؼ�������ͨ����С����
���Ӷ� O(logn)
*/
//�ǵݹ�汾
int binary_search(int* array, int size, int key)
{
	int left = 0, right = size - 1;
	int mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (array[mid] == key)
			return mid;
		if (array[mid] < key)
			left = mid + 1;
		else right = mid - 1;
	}
	return -1;
}

//�ݹ�汾
int binary_search_recursion(int* array, int left, int right, int key)
{
	if (left > right)
		return -1;
	int mid = (left + right) / 2;
	if (array[mid] == key)
		return mid;
	if (array[mid] < key)
		return binary_search_recursion(array, mid + 1, right, key);
	else
		return binary_search_recursion(array, left, mid - 1, key);
	return -1;
}
