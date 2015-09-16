#ifndef _DISJOINT_SET_H_
#define _DISJOINT_SET_H_
/*
并查集又称不相交集，有两个名字的原因在于它原就有两个不同的英文
名字，Disjoint sets和Union-find set。

为了方便把实现和声明放在了一个文件中。
*/
//#include <stdexcept>
#include <cassert>
class DisjointSet
{
public:
	explicit DisjointSet(int num);//
	~DisjointSet();//
	int find(int x);//
	void unionSets(int root1, int root2);//
private:
	int *array;//
	int number;//
};

DisjointSet::DisjointSet(int num) :number(num)
{
	assert(number > 0);
	array = new int[number];
	for (int i = 0; i < number; i++)
		array[i] = -1;
}

DisjointSet::~DisjointSet()
{
	delete array;
}
/*
//最简单的 查找find
int DisjointSet::find(int x)
{
	assert(x < number && x >= 0);
	if (array[x] < 0)//小于0就是根
		return x;
	else
		return find(array[x]);//返回父节点的根
}
*/

//路径压缩
//在查找的过程中，使得查找的路径上的所有节点都指向根节点
int DisjointSet::find(int x)
{
	assert(x < number && x >= 0);
	if (array[x] < 0)//
		return x;
	else
		return array[x] = find(array[x]);//
}

/*
//最简单的并操作，将第二个根连接到第一个根上，容易形成更深的树
void DisjointSet::unionSets(int root1, int root2)
{
	assert(root1 < number && root1 >= 0);
	assert(root2 < number && root2 >= 0);
	assert(array[root1] < 0 && array[root2] < 0);
	array[root2] = root1;
}
*/
/*

//按元素个数进行进行合并，原始时是-1（表示一个元素），元素个数的负值
//将元素少的树成为元素多的树的子树
void DisjointSet::unionSets(int root1, int root2)
{
	assert(root1 < number && root1 >= 0);
	assert(root2 < number && root2 >= 0);
	assert(array[root1] < 0 && array[root2] < 0);
	if (array[root2] < array[root1])//root2元素多
	{
		array[root2] += array[root1];
		array[root1] = root2;
	}
	else
	{
		array[root1] += array[root2];
		array[root2] = root1;
	}
}
*/
//按照高度求并，只有当两个树的高度一样的时候，高度增加1
//存储的是高度的负值，减去附加的1
void DisjointSet::unionSets(int root1,int root2)
{
	assert(root1 < number && root1 >= 0);
	assert(root2 < number && root2 >= 0);
	assert(array[root1] < 0 && array[root2] < 0);
	if (array[root2] < array[root1])//root2更深，root2成为新的根
		array[root1] = root2;
	else
	{
		if (array[root1] == array[root2])//高度一样
			array[root1]--;
		array[root2] = root1;//root1成为新的根
	}
}

#endif
