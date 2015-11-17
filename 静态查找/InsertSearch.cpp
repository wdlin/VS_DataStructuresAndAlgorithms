
/*
插值查找法

从时间复杂度上来看，它也是o(n)，但是对于表长较大，而关键字分布又比较均匀的查找表来说，
插值查找算法的平均性能比折半查找要好的多。反之，数组中如果分布非常不均匀，
那么差值查找未必是很合适的选择。
算法中使用了乘除法，那么在以下情况比较好：每一次对数据的访问与通常的指令相比，费用都是相当昂贵的。例如，
待查找的表一定是在磁盘而非内存中，因而每一次比较都要进行磁盘访问。
*/

int insert_search(int* array, int size, int key)
{
	int pos, low, high;
	low = 0;
	high = size - 1;
	while (low <= high)
	{
		pos = ((key - array[low])*(high - low)) / (array[high] - array[low]) + low;
		if (array[pos] == key)
			return pos;
		if (array[pos] < key)
			low = pos + 1;
		else
			high = pos - 1;
	}
	return -1;
}