#include "Search.h"

/*
如果查询次数不等概率，那么可以使用静态最优查找树，但是最优树
由于构造的代价比较大，达到O(n^3)，一般不使用。

所以使用次优查找树
构造复杂度O(nlogn)

P[i]=|sum(w[l]+w[l+1]....w[i-1])-sum(w[i+1]+w[i+2]+w[i+3].....+w[h])|
取值最小的P[i],以i为根节点，再分别以{r[l],r[l+1],r[l+2]....r[i-1]}和{r[i+1],[i+2].....r[h]}递归建立次优二叉树

参考 严蔚敏 数据结构 P222-P223
*/
#include <cmath>
#include <cstdlib>
typedef struct Node
{
	int value;
	Node* left;
	Node* right;
}Node;

//sw是累计权值 sw[i] = sum(w[l]+w[l+1]....w[i])
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