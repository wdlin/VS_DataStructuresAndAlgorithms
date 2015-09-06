#ifndef _LINEAR_PROBE_HASH_TABLE_H_
#define _LINEAR_PROBE_HASH_TABLE_H_
#include <vector>
#include <iostream>
#include <cassert>
/*
����̽��
��ʹ����ԽϿգ�����ռ�ݵĵ�ԪҲ�Ὺʼ�γ�һЩ���飬��Ϊһ�ξۼ�
*/
template<class HashObj>
class LinearProbeHashTable
{
public:
	explicit LinearProbeHashTable(int size = 101, double lambda = 0.5);
	~LinearProbeHashTable();
	int contains(const HashObj & x);//����Ԫ��	
	bool insert(const HashObj & x);//����Ԫ��
	bool remove(const HashObj & x);//�Ƴ�Ԫ��
	void slim();//���DELETED��Ԫ�أ��Դ�Ÿ���Ԫ��
	void makeEmpty();//���Ԫ��
	void print() const;//��ӡ

private:
	enum EntryStatus{ACTIVE,EMPTY,DELETED};//���붨������״̬���������к������֣����������Ԫ�ر�ɾ��������
	struct HashEntry
	{
		HashObj element;
		EntryStatus status;
		HashEntry(const HashObj& obj = HashObj(), EntryStatus sta = EMPTY):element(obj),status(sta){}
	};
	
	std::vector<HashEntry> array;//������������
	int _currentSize;//��ǰԪ�ظ���
	int _size;//�����С
	double _lambda;//������ӵ�����
	int findPos(const HashObj& x);
	void rehash();//��ɢ�У�����������Ӻ������ɢ�У�
	int hashCode(const HashObj & x) const;//ȡ��Ԫ�صĹ�ϣ��ַ
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

//����Ԫ��
template<class HashObj>
int LinearProbeHashTable<HashObj>::contains(const HashObj & x)
{
	int pos = findPos(x);
	if (array[pos].status == ACTIVE)
		return pos;
	else
		return -1;
}
//����Ԫ��
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
	else//�Ż���������ɾ����ͬ��Ԫ��λ�����Ԫ�أ�������_currenSize
		;
	array[pos] = HashEntry(x, ACTIVE);

	if (_currentSize >= _size*_lambda)
	{
		rehash();
	}
	return true;
}
//�Ƴ�Ԫ��
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

//���DELETED��Ԫ�أ��Դ�Ÿ���Ԫ��
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

//���Ԫ��
template<class HashObj>
void LinearProbeHashTable<HashObj>::makeEmpty()
{
	_currentSize = 0;
	for (int i = 0; i < _size; i++)
	{
		array[i].status = EMPTY;
	}
}

//�ҵ��ʺ�x��λ�û���x�Ѿ����ڵ�λ��
template<class HashObj>
int LinearProbeHashTable<HashObj>::findPos(const HashObj& x)
{
	int pos = hashCode(x);
	while (array[pos].status != EMPTY && array[pos].element != x)
	{
		pos++;//����̽��
		if (pos >= _size)
			pos -= _size;
	}
	return pos;
}

//��ɢ�У�����������Ӻ������ɢ�У�
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
//ȡ��Ԫ�صĹ�ϣ��ַ
template<class HashObj>
int LinearProbeHashTable<HashObj>::hashCode(const HashObj & x) const
{
	int hashcode = x.hashCode() % _size;
	if (hashcode < 0)
		hashcode += _size;
	return hashcode;
}

//��ӡ
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
//��ϣ�ӿ���
class Hashable
{
	virtual int hashCode()const = 0;
};

#endif