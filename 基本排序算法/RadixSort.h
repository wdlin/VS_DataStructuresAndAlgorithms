#ifndef _RADIX_SORT_H_
#define _RADIX_SORT_H_
/*基数排序*/
int getLoopTime(int array[], int size)//获取循环次数，即最大的位数
{
	int max = array[0];
	for (int i = 1; i < size; i++)//求最大值
	{
		if (array[i] > max)
		{
			max = array[i];
		}
	}
	int count = 1;
	int temp = max / 10;
	while (temp != 0)
	{
		count++;
		temp = temp / 10;
	}

	return count;
}


void radixSort(int array[],int size)
{
	int loopTime = getLoopTime(array, size);
	int *temp = new int[size];
	int *count = new int[10];
	int radix = 1;
	for (int i = 1; i <= loopTime; i++)//进行loopTime次排序
	{
		for (int j = 0; j < 10; j++)//每次排序清空计数器
		{
			count[j] = 0;
		}
		for (int j = 0; j < size; j++)//统计每个桶中的记录数
		{
			int k = (array[j] / radix) % 10;
			count[k]++;
		}
		for (int j = 1; j < 10; j++)//将temp中的位置依次分配给每个桶
		{
			count[j] = count[j - 1] + count[j];
		}
		for (int j = size -1; j >=0; j--)//将桶中的记录依次收集到temp中
		{//一定要从后面开始复制，因为count记录的是最后一个元素的位置,要把大的元素复制到后面的位置
			int k = (array[j] / radix) % 10;
			temp[count[k] - 1] = array[j];
			count[k]--;
		}
		for (int j = 0; j < size; j++)
		{
			array[j] = temp[j];
		}
		radix = radix * 10;
	}
	delete[]temp;
	delete[]count;
}



#endif