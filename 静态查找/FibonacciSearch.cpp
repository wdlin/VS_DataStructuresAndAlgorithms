#include "Search.h"
/*
쳲��������ҵĺ����ǣ�
1����key=a[mid]ʱ�����ҳɹ���
2����key<a[mid]ʱ���µĲ��ҷ�Χ�ǵ�low������mid-1������ʱ��Χ����ΪF[k-1] - 1������������ߵĳ��ȣ�����Ҫ��[low, F[k - 1] - 1]��Χ�ڲ��ң�
3����key>a[mid]ʱ���µĲ��ҷ�Χ�ǵ�mid+1������high������ʱ��Χ����ΪF[k-2] - 1�����������ұߵĳ��ȣ�����Ҫ��[F[k - 2] - 1]��Χ�ڲ��ҡ�
����ֲ�����ȣ�쳲����������㷨�������ŵ�������ֻ�漰�ӷ��ͼ������㣬�����ó�����

쳲���������
0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233��377��610��987��1597��2584
*/
#define MAXSIZE 20

void fibonacci(int *f)    //����쳲���������
{
	f[0] = 1;
	f[1] = 1;
	for (int i = 2; i < MAXSIZE; ++i)
		f[i] = f[i - 2] + f[i - 1];
}

int fibonacci_search(int *a,int size, int key )
{
	int low = 0, high = size - 1;
	int mid = 0;
	int k = 0;
	int F[MAXSIZE];
	fibonacci(F);
	while (size > F[k] - 1) //�����n��쳲������е�λ��
		++k;
	for (int i = size; i < F[k] - 1; ++i) //�����鲹ȫ��ʹ��a[n-1]
		a[i] = a[high];
	while (low <= high){
		mid = low + F[k - 1] - 1;  //����쳲��������н��лƽ�ָ�
		if (a[mid] > key){
			high = mid - 1;
			k = k - 1;
		}
		else if (a[mid] < key){
			low = mid + 1;
			k = k - 2;
		}
		else{
			if (mid <= high) //���Ϊ�����ҵ���Ӧ��λ��
				return mid;
			else
				return -1;
		}
	}
	return -1;
}

