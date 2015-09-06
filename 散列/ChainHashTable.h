#ifndef _CHAIN_HASH_TABLE_H_
#define _CHAIN_HASH_TABLE_H_
#include <vector>
#include <list>
#include <cassert>
#include <iostream>
/*
链接法哈希表 ChainHashTable
哈希接口类 Hashable（ChainHashTable的元素必须实现Hashable接口）

*/
template<class HashObj>
class ChainHashTable
{
public:
	explicit ChainHashTable(int size = 101,double lambda = 1);//哈希表的默认大小，填装因子
	~ChainHashTable();//析构函数
	bool contains(const HashObj & x);//搜索元素	
	bool insert(const HashObj & x);//插入元素
	bool remove(const HashObj & x);//移除元素
	void makeEmpty();//清空元素
	void print() const;//打印
private:
	std::vector<std::list<HashObj>> listsArray;//存放链表的数组
	int _currentSize;//当前元素个数
	int _size;//数组大小
	double _lambda;//填充因子的上限
	void rehash();//再散列（超过填充因子后进行再散列）
	int hashCode(const HashObj & x) const;//取得元素的哈希地址
};
//哈希表的默认大小，填装因子
template<class HashObj>
ChainHashTable<HashObj>::ChainHashTable(int size = 101, double lambda = 1) :_currentSize(0), _size(size), _lambda(lambda)
{
	assert(size > 0, "size must larger than 0!");
	assert(lambda > 0, "lambda is illegal!");
	listsArray.resize(size);
}
//析构函数
template<class HashObj>
ChainHashTable<HashObj>::~ChainHashTable()
{
	for (int i = 0; i < listsArray.size(); i++)
	{
		listsArray[i].clear();
	}
}
//搜索元素
template<class HashObj>
bool ChainHashTable<HashObj>::contains(const HashObj & x)
{
	auto& list = listsArray[hashCode(x)];
	bool flag = false;
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		if ((*it) == x)
		{
			flag = true;
			break;
		}
	}
	return flag;
}
//插入元素
template<class HashObj>
bool ChainHashTable<HashObj>::insert(const HashObj & x)
{	
	if (contains(x))
		return false;
    std::list<HashObj>& list = listsArray[hashCode(x)];
	list.push_front(x);
	
	_currentSize++;
	if (_currentSize > _size*_lambda)
	{
		rehash();
	}
	return true;
}
//移除元素
template<class HashObj>
bool ChainHashTable<HashObj>::remove(const HashObj & x)
{
	auto& list = listsArray[hashCode(x)];
	std::list<HashObj>::iterator it;
	for (it = list.begin(); it != list.end(); ++it)
	{
		if ((*it) == x)
			break;
	}
	if (it == list.end())
		return false;
	list.erase(it);
	--_currentSize;
	return true;
}
//清空元素
template<class HashObj>
void ChainHashTable<HashObj>::makeEmpty()
{
	for (int i = 0; i < listsArray.size(); i++)
		listsArray[i].clear();
}

//再散列（超过填充因子后进行再散列）
template<class HashObj>
void ChainHashTable<HashObj>::rehash()
{
	std::vector<std::list<HashObj>> oldListsArray = listsArray;

	_size = _size * 2;
	listsArray.resize(_size);
	for (int i = 0; i < _size; i++)
		listsArray[i].clear();

	_currentSize = 0;
	for (int i = 0; i < oldListsArray.size(); i++)
	{
		for (auto& it = oldListsArray[i].begin(); it != oldListsArray[i].end(); ++it)
			insert(*it);
	}

}
//取得元素的哈希地址
template<class HashObj>
int ChainHashTable<HashObj>::hashCode(const HashObj & x) const
{
	int hashcode = x.hashCode() % _size;
	if (hashcode < 0)
		hashcode += _size;
	return hashcode;
}
//打印
template<class HashObj>
void ChainHashTable<HashObj>::print() const
{
	using namespace std;
	for (int i = 0; i < _size; i++)
	{
		cout << "pos: " << i << " : ";
		for (auto& it = listsArray[i].begin(); it != listsArray[i].end(); ++it)
		{
			cout<<(*it)<<" -> ";
		}
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