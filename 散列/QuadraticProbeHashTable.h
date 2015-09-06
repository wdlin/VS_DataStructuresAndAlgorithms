#ifndef _QUADRATIC_PROBE_HASH_TABLE_H_
#define _QUADRATIC_PROBE_HASH_TABLE_H_
#include <vector>
#include <iostream>
#include <cassert>
/*
定理：
平方探测，表的大小是素数，那么当表至少有一半是空的时候，总能插入一个新元素。
令表的大小 = 4*k+3  冲突解决是 +-i^2

虽然平方探测排除了一次聚集，但是散列到同一位置的那些元素将探测相同的备选单元，称为二次聚集。
*/
template<class HashObj>
class QuadraticProbeHashTable
{
public:
	explicit QuadraticProbeHashTable(int k = 10, double lambda = 0.5);
	~QuadraticProbeHashTable();
	int contains(const HashObj & x);//搜索元素	
	bool insert(const HashObj & x);//插入元素
	bool remove(const HashObj & x);//移除元素
	void slim();//清除DELETED的元素，以存放更多元素
	void makeEmpty();//清空元素
	void print() const;//打印
private:
	enum EntryStatus{ ACTIVE, EMPTY, DELETED };//必须定义三种状态，不能是有和无两种，否则如果有元素被删除后会出错
	struct HashEntry
	{
		HashObj element;
		EntryStatus status;
		HashEntry(const HashObj& obj = HashObj(), EntryStatus sta = EMPTY) :element(obj), status(sta){}
	};

	std::vector<HashEntry> array;//存放链表的数组
	int _currentSize;//当前元素个数
	int _size;//数组大小
	int _k;
	double _lambda;//填充因子的上限
	int findPos(const HashObj& x);
	void rehash();//再散列（超过填充因子后进行再散列）
	int hashCode(const HashObj & x) const;//取得元素的哈希地址

};

template<class HashObj>
QuadraticProbeHashTable<HashObj>::QuadraticProbeHashTable(int k = 10, double lambda = 0.5)
:_currentSize(0),_k(k), _size( 4*k + 3), _lambda(lambda)
{
	assert(k >= 0, "size must larger than or equal to 0!");
	assert(lambda <= 0.5 && lambda > 0, "lambda is illegal!");
	array.resize(_size);
}

template<class HashObj>
QuadraticProbeHashTable<HashObj>::~QuadraticProbeHashTable()
{
}
//搜索元素
template<class HashObj>
int QuadraticProbeHashTable<HashObj>::contains(const HashObj& x)
{
	int pos = findPos(x);
	if (array[pos].status == ACTIVE)
		return pos;
	else
		return -1;
}
//插入元素
template<class HashObj>
bool QuadraticProbeHashTable<HashObj>::insert(const HashObj& x)
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
bool QuadraticProbeHashTable<HashObj>::remove(const HashObj & x)
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
void QuadraticProbeHashTable<HashObj>::slim()
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
void QuadraticProbeHashTable<HashObj>::makeEmpty()
{
	_currentSize = 0;
	for (int i = 0; i < _size; i++)
	{
		array[i].status = EMPTY;
	}
}

//找到适合x的位置或者x已经存在的位置
template<class HashObj>
int QuadraticProbeHashTable<HashObj>::findPos(const HashObj& x)
{
	int pos = hashCode(x);
	int offset = 1;
	while (array[pos].status != EMPTY && array[pos].element != x)
	{
		pos = pos + offset*offset;//平方探测
		offset++;
		if (pos >= _size)
			pos %= _size;
	}
	return pos;
}

//再散列（超过填充因子后进行再散列）
template<class HashObj>
void QuadraticProbeHashTable<HashObj>::rehash()
{
	std::vector<HashEntry> oldArray = array;
	_k++;
	_size = 4 * _k + 3;
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
int QuadraticProbeHashTable<HashObj>::hashCode(const HashObj & x) const
{
	int hashcode = x.hashCode() % _size;
	if (hashcode < 0)
		hashcode += _size;
	return hashcode;
}

//打印
template<class HashObj>
void QuadraticProbeHashTable<HashObj>::print() const
{
	using namespace std;
	for (int i = 0; i < _size; i++)
	{
		cout << "pos: " << i << " : ";
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
