#ifndef _HASH_TREE_H_
#define _HASH_TREE_H_

/*
����ѡ�������ֱ��㷨������һ�ù�ϣ����
ѡ���2��ʼ����������������һ��ʮ��Ĺ�ϣ������һ����Ϊ����㣬���������2����㣻
�ڶ����ÿ���������3����㣻�������ƣ���ÿ������ӽڵ���ĿΪ����������������ʮ�㣬
ÿ���������29����㡣

ͬһ����е��ӽ�㣬�����Ҵ���ͬ�����������
���磺�ڶ��������������ӽڵ㡣��ô�����ҷֱ������3��0����3��1����3��2.
����������ȡ������õ������������˴����·����
��㣺���Ĺؼ���(������������Ψһ��)���������ݶ��󣬽���Ƿ�ռ�ݵı�־λ(��־
λΪ��ʱ���ؼ��ֲű���Ϊ����Ч��)���ͽ����ӽ�����顣

�ص㣺
1.��ϣ���Ľṹ�Ƕ�̬�ģ�Ҳ����ĳЩ��ϣ�㷨������Ҫ��ʱ��ĳ�ʼ�����̣�ֻ��Ҫ��ʼ����
���Ϳ��Կ�ʼ��������ϣ��Ҳû�б�ҪΪ�����ڵĹؼ�����ǰ����ռ䡣
2.����Ѹ�٣����ֻ��Ҫ10��ȡ��ͱȽϲ������Ϳ�֪����������Ƿ���ڡ���ϣ���Ĳ��Ҵ���
��Ԫ�ظ���û�й�ϵ��
3.�ṹ���䣬��ϣ����ɾ����ʱ�򲢲����κνṹ��������Ҳ������һ���ǳ��õ��ŵ㡣������
�ṹ������Ԫ�غ�ɾ��Ԫ�ص�ʱ��Ҫ��һ���Ľṹ������
4.�������ԣ���ϣ����֧������û��˳�����ԡ�
��Ҫע����ǣ���ϣ����һ���������ӵĽṹ������������Ҫ�洢�����������Ӷ����󡣼�ʹ��
�������ٵ�ԭ�������������ǹ�ϣ�����ܽ����������١���������Ŀ����Ϊ�˱���ṹ�ĵ��������Ķ������ġ�


key�ǲ������ظ��ģ��������ʵ���ǿ��������ظ����������ظ���Ϊ���ĸ߶ȼ�primeNum��
*/


//#define KeyType int
//#define ValueType int


template<class KeyType,class ValueType>
class HashTree
{
public:
	HashTree();//Ĭ�Ϲ��캯��
	HashTree(KeyType key,ValueType value);//�����һ��ֵ��Ϊ��
	HashTree(int childSize, int primes[], int primeNum);//���������Ĵ�С��һ���������飬�����С��childSize�������prime[primeNum - 1]��ֵ
	~HashTree();//��������
	void insertNode(const KeyType& key, const ValueType& value);//����һ���ڵ�
	bool findNode(const KeyType& key, const ValueType& value);//���ҽڵ�
	bool removeNode(const KeyType& key, const ValueType& value);//�Ƴ�һ���ڵ�

private:
	typedef struct HashNode//��ϣ���Ľڵ���
	{
		KeyType key;//��
		ValueType value;//ֵ
		bool occupied;//�Ƿ���Ч
		HashNode** children;//�ӽڵ�ָ��
		HashNode(HashTree* tree) :occupied(false)
		{
			children = new HashNode*[tree->childSize];
			for (int i = 0; i < tree->childSize; i++)
				children[i] = nullptr;
		}
		HashNode(HashTree* tree, KeyType k, ValueType v) :key(k), value(v), occupied(false)
		{
			children = new HashNode*[tree->childSize];
			for (int i = 0; i < tree->childSize; i++)
				children[i] = nullptr;
		}
		~HashNode(){}

	}HashNode;
	int childSize;//��������
	int *primes;//��������
	int primeNum;//��������Ĵ�С
	HashNode* root;//��

	void insert(HashNode* node, int level, const KeyType& key, const ValueType& value);//����ڵ��ʵ�ʺ���
	HashNode* find(HashNode* node, int level, const KeyType& key, const ValueType& value);//���ҽڵ��ʵ�ʺ���
	void release(HashNode* node);//�ͷ��ڴ�ĺ���
	//bool remove(HashNode* node, int level, const KeyType& key, const ValueType& value);

};

//Ĭ�Ϲ��캯��
template<class KeyType, class ValueType>
HashTree<KeyType,ValueType>::HashTree() :childSize(32), primeNum(10)
{
	primes = new int[primeNum];
	primes[0] = 2;
	primes[1] = 3;
	primes[2] = 5;
	primes[3] = 7;
	primes[4] = 11;
	primes[5] = 13;
	primes[6] = 17;
	primes[7] = 19;
	primes[8] = 23;
	primes[9] = 29;
	root = new HashNode(this);
}
//�����һ��ֵ��Ϊ��
template<class KeyType, class ValueType>
HashTree<KeyType, ValueType>::HashTree(KeyType key, ValueType value) :childSize(32), primeNum(10)
{
	primes = new int[primeNum];
	primes[0] = 2;
	primes[1] = 3;
	primes[2] = 5;
	primes[3] = 7;
	primes[4] = 11;
	primes[5] = 13;
	primes[6] = 17;
	primes[7] = 19;
	primes[8] = 23;
	primes[9] = 29;
	root = new HashNode(this, key, value);
	root->occupied = true;
}
//���������Ĵ�С��һ���������飬�����С��childSize�������prime[primeNum - 1]��ֵ
template<class KeyType, class ValueType>
HashTree<KeyType, ValueType>::HashTree(int childSize, int primes[], int primeNum)
{
	this->childSize = childSize;
	this->primeNum = primeNum;
	this->primes = new int[primeNum];
	for (int i = 0; i < primeNum; i++)
		this->primes[i] = primes[i];
}
//��������
template<class KeyType, class ValueType>
HashTree<KeyType, ValueType>::~HashTree()
{
	release(root);
	delete primes;
}
//����һ���ڵ�
template<class KeyType, class ValueType>
void HashTree<KeyType, ValueType>::insertNode(const KeyType& key, const ValueType& value)
{
	return insert(root, 0, key, value);
}
//���ҽڵ�
template<class KeyType, class ValueType>
bool HashTree<KeyType, ValueType>::findNode(const KeyType& key, const ValueType& value)
{
	return find(root, 0, key, value) != nullptr;
}
//�Ƴ�һ���ڵ�
template<class KeyType, class ValueType>
bool HashTree<KeyType, ValueType>::removeNode(const KeyType& key, const ValueType& value)
{
	HashNode* node = find(root, 0, key, value);
	if (node == nullptr)
		return false;
	else
	{
		node->occupied = false;
		return true;
	}
}

//����ڵ��ʵ�ʺ���
template<class KeyType, class ValueType>
void HashTree<KeyType, ValueType>::insert(HashNode* node, int level, const KeyType& key, const ValueType& value)
{
	if (node->occupied == false)
	{
		node->key = key;
		node->value = value;
		node->occupied = true;
		return;
	}
	int index = key%primes[level];

	if (node->children[index] == nullptr)
		node->children[index] = new HashNode(this, key, value);

	level++;
	if (level == primeNum)
		throw "����ʧ�ܣ����������ơ�";
	insert(node->children[index], level, key, value);

}
//���ҽڵ��ʵ�ʺ���
template<class KeyType, class ValueType>
typename HashTree<KeyType, ValueType>::HashNode* HashTree<KeyType, ValueType>::find(HashNode* node, int level, const KeyType& key, const ValueType& value)
{
	if (node->occupied == true && node->key == key&&node->value == value)
		return node;
	int index = key%primes[level];
	if (node->children[index] == nullptr)
		return nullptr;
	level++;
	return find(node->children[index], level, key, value);
}

//�ͷ��ڴ�ĺ���
template<class KeyType, class ValueType>
void HashTree<KeyType, ValueType>::release(HashNode* node)
{
	for (int i = 0; i < primeNum; i++)
	{
		if (node->children[i] != nullptr)
			release(node->children[i]);
	}
	delete node->children;
	delete node;
}

#endif