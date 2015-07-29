#ifndef _RADIX_SORT_H_
#define _RADIX_SORT_H_
/*��������*/
int getLoopTime(int array[], int size)//��ȡѭ��������������λ��
{
	int max = array[0];
	for (int i = 1; i < size; i++)//�����ֵ
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
	for (int i = 1; i <= loopTime; i++)//����loopTime������
	{
		for (int j = 0; j < 10; j++)//ÿ��������ռ�����
		{
			count[j] = 0;
		}
		for (int j = 0; j < size; j++)//ͳ��ÿ��Ͱ�еļ�¼��
		{
			int k = (array[j] / radix) % 10;
			count[k]++;
		}
		for (int j = 1; j < 10; j++)//��temp�е�λ�����η����ÿ��Ͱ
		{
			count[j] = count[j - 1] + count[j];
		}
		for (int j = size -1; j >=0; j--)//��Ͱ�еļ�¼�����ռ���temp��
		{//һ��Ҫ�Ӻ��濪ʼ���ƣ���Ϊcount��¼�������һ��Ԫ�ص�λ��,Ҫ�Ѵ��Ԫ�ظ��Ƶ������λ��
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