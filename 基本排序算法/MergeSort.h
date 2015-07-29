#ifndef _MERGE_SORT_H_
#define _MERGE_SORT_H_
/*1.�鲢����*/

/*
�鲢����
��������������кϲ����õ���ȫ��������У�����ʹÿ������������
��ʹ�����жμ������������������ϲ���һ���������Ϊ��·�鲢��
O(nlogn)
*/
template<typename T>
void merge(T array[],T tempArr[],int startIndex,int midIndex,int endIndex)
{
	int i = startIndex;
	int j = midIndex + 1;
	int k = startIndex;
	while (i != midIndex + 1 && j != endIndex + 1)//�Ƚϸ���
	{
		if (array[i] < array[j])
			tempArr[k++] = array[i++];
		else
			tempArr[k++] = array[j++];
	}
	while (i != midIndex + 1)//����ʣ���
	{
		tempArr[k++] = array[i++];
	}
	while (j != endIndex + 1)//����ʣ���
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