#ifndef _MERGE_SORT_H_
#define _MERGE_SORT_H_
/*1.归并排序*/

/*
归并排序
将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，
再使子序列段间有序。若将两个有序表合并成一个有序表，称为二路归并。
O(nlogn)
*/
template<typename T>
void merge(T array[],T tempArr[],int startIndex,int midIndex,int endIndex)
{
	int i = startIndex;
	int j = midIndex + 1;
	int k = startIndex;
	while (i != midIndex + 1 && j != endIndex + 1)//比较复制
	{
		if (array[i] < array[j])
			tempArr[k++] = array[i++];
		else
			tempArr[k++] = array[j++];
	}
	while (i != midIndex + 1)//复制剩余的
	{
		tempArr[k++] = array[i++];
	}
	while (j != endIndex + 1)//复制剩余的
	{
		tempArr[k++] = array[j++];
	}

	for (int i = startIndex; i <= endIndex; i++)
	{
		array[i] = tempArr[i];
	}
}

template<typename T>
void mergeSort(T array[],T tempArr[],int startIndex,int endIndex)
{
	if (startIndex < endIndex)
	{
		int midIndex = (startIndex + endIndex) / 2;
		mergeSort(array, tempArr, startIndex, midIndex);
		mergeSort(array, tempArr, midIndex + 1, endIndex);
		merge(array,tempArr,startIndex,midIndex,endIndex);
	}
}



#endif