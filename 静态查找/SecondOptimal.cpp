#include "Search.h"

/*
�����ѯ�������ȸ��ʣ���ô����ʹ�þ�̬���Ų�����������������
���ڹ���Ĵ��۱Ƚϴ󣬴ﵽO(n^3)��һ�㲻ʹ�á�

����ʹ�ô��Ų�����
���츴�Ӷ�O(nlogn)

P[i]=|sum(w[l]+w[l+1]....w[i-1])-sum(w[i+1]+w[i+2]+w[i+3].....+w[h])|
ȡֵ��С��P[i],��iΪ���ڵ㣬�ٷֱ���{r[l],r[l+1],r[l+2]....r[i-1]}��{r[i+1],[i+2].....r[h]}�ݹ齨�����Ŷ�����

�ο� ��ε�� ���ݽṹ P222-P223
*/
#include <cmath>
#include <cstdlib>
typedef struct Node
{
	int value;
	Node* left;
	Node* right;
}Node;

//sw���ۼ�Ȩֵ sw[i] = sum(w[l]+w[l+1]....w[i])
void contruct_second_optimal(Node*& root,int values[],float sw[],int low,int high)
{
	int i = low;
	float min = sw[high] - sw[low], dw = sw[high];
	for (int j = low + 1; j < high; j++)
	{
		float temp = abs(dw - sw[j] - sw[j - 1]);//dw-sw[j]= sum(w[i+1]+...+w[h]),sw[j-1] =sum(w[l]...w[i-1])
		if (temp < min)
		{
			i = j;
			min = temp;
		}
	}

	root = (Node*)malloc(sizeof(Node));
	root->value = values[i];

	if (i == low)root->left = nullptr;
	else contruct_second_optimal(root->left, values, sw, low, i - 1);
	if (i == high)root->right = nullptr;
	else contruct_second_optimal(root->right, values, sw, i + 1, high);

}