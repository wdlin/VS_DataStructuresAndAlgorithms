#ifndef _CHAIN_HASH_TABLE_H_
#define _CHAIN_HASH_TABLE_H_
#include <vector>
#include <list>
#include <cassert>
#include <iostream>
/*
���ӷ���ϣ�� ChainHashTable
��ϣ�ӿ��� Hashable��ChainHashTable��Ԫ�ر���ʵ��Hashable�ӿڣ�

*/
template<class HashObj>
class ChainHashTable
{
public:
	explicit ChainHashTable(int size = 101,double lambda = 1);//��ϣ���Ĭ�ϴ�С����װ����
	~ChainHashTable();//��������
	bool contains(const HashObj & x);//����Ԫ��	
	bool insert(const HashObj & x);//����Ԫ��
	bool remove(const HashObj & x);//�Ƴ�Ԫ��
	void makeEmpty();//���Ԫ��
	void print() const;//��ӡ
private:
	std::vector<std::list<HashObj>> listsArray;//������������
	int _currentSize;//��ǰԪ�ظ���
	int _size;//�����С
	double _lambda;//������ӵ�����
	void rehash();//��ɢ�У�����������Ӻ������ɢ�У�
	int hashCode(const HashObj & x) const;//ȡ��Ԫ�صĹ�ϣ��ַ
};
//��ϣ���Ĭ�ϴ�С����װ����
template<class HashObj>
ChainHashTable<HashObj>::ChainHashTable(int size = 101, double lambda = 1) :_currentSize(0), _size(size), _lambda(lambda)
{
	assert(size > 0, "size must larger than 0!");
	assert(lambda > 0, "lambda is illegal!");
	listsArray.resize(size);
}
//��������
template<class HashObj>
ChainHashTable<HashObj>::~ChainHashTable()
{
	for (int i = 0; i < listsArray.size(); i++)
	{
		listsArray[i].clear();
	}
}
//����Ԫ��
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
//����Ԫ��
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
//�Ƴ�Ԫ��
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
//���Ԫ��
template<class HashObj>
void ChainHashTable<HashObj>::makeEmpty()
{
	for (int i = 0; i < listsArray.size(); i++)
		listsArray[i].clear();
}

//��ɢ�У�����������Ӻ������ɢ�У�
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
//ȡ��Ԫ�صĹ�ϣ��ַ
template<class HashObj>
int ChainHashTable<HashObj>::hashCode(const HashObj & x) const
{
	int hashcode = x.hashCode() % _size;
	if (hashcode < 0)
		hashcode += _size;
	return hashcode;
}
//��ӡ
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
//��ϣ�ӿ���
class Hashable
{
	virtual int hashCode()const = 0;
};

#endif