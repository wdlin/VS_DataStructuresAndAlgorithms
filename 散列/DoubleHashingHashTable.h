#ifndef _DOUBLE_HASHING_HASH_TABLE_H_
#define _DOUBLE_HASHING_HASH_TABLE_H_
#include <vector>
#include <string>

/*
˫ɢ�У�һ�����е������Ƿ�f(i) = i*hash2(x);
������õĵڶ�����ϣ�� hash2(x) = R- (x mod R)��R��С��TableSize������
*/
template<class HashObj>
class DoubleHashingHashTable
{
public:
	explicit DoubleHashingHashTable(int k = 10, double lambda = 0.5);
	~DoubleHashingHashTable();
	int contains(const HashObj & x);//����Ԫ��	
	bool insert(const HashObj & x);//����Ԫ��
	bool remove(const HashObj & x);//�Ƴ�Ԫ��
	void slim();//���DELETED��Ԫ�أ��Դ�Ÿ���Ԫ��
	void makeEmpty();//���Ԫ��
	void print() const;//��ӡ
private:
	enum EntryStatus{ ACTIVE, EMPTY, DELETED };//���붨������״̬���������к������֣����������Ԫ�ر�ɾ��������
	struct HashEntry
	{
		HashObj element;
		EntryStatus status;
		HashEntry(const HashObj& obj = HashObj(), EntryStatus sta = EMPTY) :element(obj), status(sta){}
	};

	std::vector<HashEntry> array;//������������
	int _currentSize;//��ǰԪ�ظ���
	int _size;//�����С
	int _k;
	double _lambda;//������ӵ�����
	int findPos(const HashObj& x);
	void rehash();//��ɢ�У�����������Ӻ������ɢ�У�
	int hashCode(const HashObj & x) const;//ȡ��Ԫ�صĹ�ϣ��ַ
	int hashCode2(const HashObj & x);//�ڶ�ɢ�к���

};



template<class HashObj>
DoubleHashingHashTable<HashObj>::DoubleHashingHashTable(int k = 10, double lambda = 0.5)
:_currentSize(0),_k(k), _size( 4*k + 3), _lambda(lambda)
{
	assert(k >= 0, "size must larger than or equal to 0!");
	assert(lambda <= 0.5 && lambda > 0, "lambda is illegal!");
	array.resize(_size);
}

template<class HashObj>
DoubleHashingHashTable<HashObj>::~DoubleHashingHashTable()
{
}
//����Ԫ��
template<class HashObj>
int DoubleHashingHashTable<HashObj>::contains(const HashObj& x)
{
	int pos = findPos(x);
	if (array[pos].status == ACTIVE)
		return pos;
	else
		return -1;
}
//����Ԫ��
template<class HashObj>
bool DoubleHashingHashTable<HashObj>::insert(const HashObj& x)
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
bool DoubleHashingHashTable<HashObj>::remove(const HashObj & x)
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
void DoubleHashingHashTable<HashObj>::slim()
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
void DoubleHashingHashTable<HashObj>::makeEmpty()
{
	_currentSize = 0;
	for (int i = 0; i < _size; i++)
	{
		array[i].status = EMPTY;
	}
}

//�ҵ��ʺ�x��λ�û���x�Ѿ����ڵ�λ��
template<class HashObj>
int DoubleHashingHashTable<HashObj>::findPos(const HashObj& x)
{
	int pos = hashCode(x);
	int offset = 1;
	int hash = hashCode2(x);//˫ɢ��
	while (array[pos].status != EMPTY && array[pos].element != x)
	{
		pos = pos + offset*hash;//˫ɢ��
		offset++;
		if (pos >= _size)
			pos %= _size;
	}
	return pos;
}

//��ɢ�У�����������Ӻ������ɢ�У�
template<class HashObj>
void DoubleHashingHashTable<HashObj>::rehash()
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

//ȡ��Ԫ�صĹ�ϣ��ַ
template<class HashObj>
int DoubleHashingHashTable<HashObj>::hashCode(const HashObj & x) const
{
	int hashcode = x.hashCode() % _size;
	if (hashcode < 0)
		hashcode += _size;
	return hashcode;
}

//�ڶ�ɢ�к���
template<class HashObj>
int DoubleHashingHashTable<HashObj>::hashCode2(const HashObj & x)
{
	int temp;//һ����ɢ�б�С������
	if (_k == 0)
		temp = 2;
	else
		temp = 4 * (_k - 1) + 3;
	int hashcode = temp - x.hashCode() % temp;
	if (hashcode > temp)
		hashcode -= temp;
	return hashcode;
}

//��ӡ
template<class HashObj>
void DoubleHashingHashTable<HashObj>::print() const
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
//��ϣ�ӿ���
class Hashable
{
	virtual int hashCode()const = 0;
};

#endif