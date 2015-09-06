#ifndef _LINEAR_PROBE_HASH_TABLE_H_
#define _LINEAR_PROBE_HASH_TABLE_H_
#include <vector>
#include <iostream>
#include <cassert>
/*
线性探测
即使表相对较空，这样占据的单元也会开始形成一些区块，称为一次聚集
*/
template<class HashObj>
class LinearProbeHashTable
{
public:
	explicit LinearProbeHashTable(int size = 101, double lambda = 0.5);
	~LinearProbeHashTable();
	int contains(const HashObj & x);//搜索元素	
	bool insert(const HashObj & x);//插入元素
	bool remove(const HashObj & x);//移除元素
	void slim();//清除DELETED的元素，以存放更多元素
	void makeEmpty();//清空元素
	void print() const;//打印

private:
	enum EntryStatus{ACTIVE,EMPTY,DELETED};//必须定义三种状态，不能是有和无两种，否则如果有元素被删除后会出错
	struct HashEntry
	{
		HashObj element;
		EntryStatus status;
		HashEntry(const HashObj& obj = HashObj(), EntryStatus sta = EMPTY):element(obj),status(sta){}
	};
	
	std::vector<HashEntry> array;//存放链表的数组
	int _currentSize;//当前元素个数
	int _size;//数组大小
	double _lambda;//填充因子的上限
	int findPos(const HashObj& x);
	void rehash();//再散列（超过填充因子后进行再散列）
	int hashCode(const HashObj & x) const;//取得元素的哈希地址
};
template<class HashObj>
LinearProbeHashTable<HashObj>::LinearProbeHashTable(int size, double lambda)
:_currentSize(0), _size(size), _lambda(lambda)
{
	assert(size > 0, "size must larger than 0!");
	assert(lambda <= 1 && lambda > 0, "lambda is illegal!");
	array.resize(size);
}

template<class HashObj>
LinearProbeHashTable<HashObj>::~LinearProbeHashTable()
{
}

//搜索元素
template<class HashObj>
int LinearProbeHashTable<HashObj>::contains(const HashObj & x)
{
	int pos = findPos(x);
	if (array[pos].status == ACTIVE)
		return pos;
	else
		return -1;
}
//插入元素
template<class HashObj>
bool LinearProbeHashTable<HashObj>::insert(const HashObj & x)
{
	int pos = findPos(x);
	if (array[pos].status == ACTIVE)
		return false;

	if (array[pos].status == EMPTY)
	{
		_currentSize++;
	}
	else//优化：在曾经删除相同的元素位置添加元素，不增加_currenSize
		;
	array[pos] = HashEntry(x, ACTIVE);

	if (_currentSize >= _size*_lambda)
	{
		rehash();
	}
	return true;
}
//移除元素
template<class HashObj>
bool LinearProbeHashTable<HashObj>::remove(const HashObj & x)
{
	int pos = contains(x);
	if (pos == -1)
		return false;
	else
	{
		array[pos].status = DELETED;
		return true;
	}

}

//清除DELETED的元素，以存放更多元素
template<class HashObj>
void LinearProbeHashTable<HashObj>::slim()
{
	std::vector<HashEntry> oldArray = array;
	for (int i = 0; i < _size; i++)
		array[i].status = EMPTY;
	_currentSize = 0;
	for (int i = 0; i < oldArray.size(); i++)
	{
		if (oldArray[i].status == ACTIVE)
			insert(oldArray[i].element);
	}
}

//清空元素
template<class HashObj>
void LinearProbeHashTable<HashObj>::makeEmpty()
{
	_currentSize = 0;
	for (int i = 0; i < _size; i++)
	{
		array[i].status = EMPTY;
	}
}

//找到适合x的位置或者x已经存在的位置
template<class HashObj>
int LinearProbeHashTable<HashObj>::findPos(const HashObj& x)
{
	int pos = hashCode(x);
	while (array[pos].status != EMPTY && array[pos].element != x)
	{
		pos++;//线性探测
		if (pos >= _size)
			pos -= _size;
	}
	return pos;
}

//再散列（超过填充因子后进行再散列）
template<class HashObj>
void LinearProbeHashTable<HashObj>::rehash()
{
	std::vector<HashEntry> oldArray = array;
	_size = 2 * _size;
	array.resize(_size);
	for (int i = 0; i < _size; i++)
		array[i].status = EMPTY;
	_currentSize = 0;
	for (int i = 0; i < oldArray.size(); i++)
	{
		if (oldArray[i].status == ACTIVE)
			insert(oldArray[i].element);
	}
}
//取得元素的哈希地址
template<class HashObj>
int LinearProbeHashTable<HashObj>::hashCode(const HashObj & x) const
{
	int hashcode = x.hashCode() % _size;
	if (hashcode < 0)
		hashcode += _size;
	return hashcode;
}

//打印
template<class HashObj>
void LinearProbeHashTable<HashObj>::print() const
{
	using namespace std;
	for (int i = 0; i < _size; i++)
	{
		cout << "pos: " << i<<" : ";
		if (array[i].status == EMPTY)
			cout << "Empty";
		else if (array[i].status == DELETED)
			cout << "Deleted";
		else
			cout << array[i].element;
		cout << endl;
	}
}

#endif

#ifndef _CLASS_HASHABLE_
#define _CLASS_HASHABLE_
//哈希接口类
class Hashable
{
	virtual int hashCode()const = 0;
};

#endif