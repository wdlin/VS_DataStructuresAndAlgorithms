#include "Search.h"
/*
斐波那契查找的核心是：
1）当key=a[mid]时，查找成功；
2）当key<a[mid]时，新的查找范围是第low个到第mid-1个，此时范围个数为F[k-1] - 1个，即数组左边的长度，所以要在[low, F[k - 1] - 1]范围内查找；
3）当key>a[mid]时，新的查找范围是第mid+1个到第high个，此时范围个数为F[k-2] - 1个，即数组右边的长度，所以要在[F[k - 2] - 1]范围内查找。
与二分查找相比，斐波那契查找算法的明显优点在于它只涉及加法和减法运算，而不用除法。

斐波那契数列
0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233，377，610，987，1597，2584
*/
#define MAXSIZE 20

void fibonacci(int *f)    //构建斐波那契序列
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
	while (size > F[k] - 1) //计算出n在斐波那契中的位置
		++k;
	for (int i = size; i < F[k] - 1; ++i) //把数组补全，使用a[n-1]
		a[i] = a[high];
	while (low <= high){
		mid = low + F[k - 1] - 1;  //根据斐波那契数列进行黄金分割
		if (a[mid] > key){
			high = mid - 1;
			k = k - 1;
		}
		else if (a[mid] < key){
			low = mid + 1;
			k = k - 2;
		}
		else{
			if (mid <= high) //如果为真则找到相应的位置
				return mid;
			else
				return -1;
		}
	}
	return -1;
}

