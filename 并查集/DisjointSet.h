#ifndef _DISJOINT_SET_H_
#define _DISJOINT_SET_H_
/*
���鼯�ֳƲ��ཻ�������������ֵ�ԭ��������ԭ����������ͬ��Ӣ��
���֣�Disjoint sets��Union-find set��

Ϊ�˷����ʵ�ֺ�����������һ���ļ��С�
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
//��򵥵� ����find
int DisjointSet::find(int x)
{
	assert(x < number && x >= 0);
	if (array[x] < 0)//С��0���Ǹ�
		return x;
	else
		return find(array[x]);//���ظ��ڵ�ĸ�
}
*/

//·��ѹ��
//�ڲ��ҵĹ����У�ʹ�ò��ҵ�·���ϵ����нڵ㶼ָ����ڵ�
int DisjointSet::find(int x)
{
	assert(x < number && x >= 0);
	if (array[x] < 0)//
		return x;
	else
		return array[x] = find(array[x]);//
}

/*
//��򵥵Ĳ����������ڶ��������ӵ���һ�����ϣ������γɸ������
void DisjointSet::unionSets(int root1, int root2)
{
	assert(root1 < number && root1 >= 0);
	assert(root2 < number && root2 >= 0);
	assert(array[root1] < 0 && array[root2] < 0);
	array[root2] = root1;
}
*/
/*

//��Ԫ�ظ������н��кϲ���ԭʼʱ��-1����ʾһ��Ԫ�أ���Ԫ�ظ����ĸ�ֵ
//��Ԫ���ٵ�����ΪԪ�ض����������
void DisjointSet::unionSets(int root1, int root2)
{
	assert(root1 < number && root1 >= 0);
	assert(root2 < number && root2 >= 0);
	assert(array[root1] < 0 && array[root2] < 0);
	if (array[root2] < array[root1])//root2Ԫ�ض�
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
//���ո߶��󲢣�ֻ�е��������ĸ߶�һ����ʱ�򣬸߶�����1
//�洢���Ǹ߶ȵĸ�ֵ����ȥ���ӵ�1
void DisjointSet::unionSets(int root1,int root2)
{
	assert(root1 < number && root1 >= 0);
	assert(root2 < number && root2 >= 0);
	assert(array[root1] < 0 && array[root2] < 0);
	if (array[root2] < array[root1])//root2���root2��Ϊ�µĸ�
		array[root1] = root2;
	else
	{
		if (array[root1] == array[root2])//�߶�һ��
			array[root1]--;
		array[root2] = root1;//root1��Ϊ�µĸ�
	}
}

#endif
