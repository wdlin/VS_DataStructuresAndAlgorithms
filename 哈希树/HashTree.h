#ifndef _HASH_TREE_H_
#define _HASH_TREE_H_

/*
我们选择质数分辨算法来建立一棵哈希树。
选择从2开始的连续质数来建立一个十层的哈希树。第一层结点为根结点，根结点下有2个结点；
第二层的每个结点下有3个结点；依此类推，即每层结点的子节点数目为连续的质数。到第十层，
每个结点下有29个结点。

同一结点中的子结点，从左到右代表不同的余数结果。
例如：第二层结点下有三个子节点。那么从左到右分别代表：除3余0，除3余1，除3余2.
对质数进行取余操作得到的余数决定了处理的路径。
结点：结点的关键字(在整个树中是唯一的)，结点的数据对象，结点是否被占据的标志位(标志
位为真时，关键字才被认为是有效的)，和结点的子结点数组。

特点：
1.哈希树的结构是动态的，也不像某些哈希算法那样需要长时间的初始化过程，只需要初始化根
结点就可以开始工作。哈希树也没有必要为不存在的关键字提前分配空间。
2.查找迅速，最多只需要10次取余和比较操作，就可知道这个对象是否存在。哈希树的查找次数
和元素个数没有关系。
3.结构不变，哈希树在删除的时候并不做任何结构调整。这也是它的一个非常好的优点。常规树
结构在增加元素和删除元素的时候都要做一定的结构调整。
4.非排序性，哈希树不支持排序，没有顺序特性。
需要注意的是：哈希树是一个单向增加的结构，即随着所需要存储的数据量增加而增大。即使数
据量减少到原来的数量，但是哈希树的总结点树不会减少。这样做的目的是为了避免结构的调整带来的额外消耗。


key是不可以重复的，但是这个实现是可以少量重复，最多可以重复数为树的高度即primeNum。
*/


//#define KeyType int
//#define ValueType int


template<class KeyType,class ValueType>
class HashTree
{
public:
	HashTree();//默认构造函数
	HashTree(KeyType key,ValueType value);//输入第一个值作为根
	HashTree(int childSize, int primes[], int primeNum);//输入子树的大小，一个质数数组，数组大小，childSize必须大于prime[primeNum - 1]的值
	~HashTree();//析构函数
	void insertNode(const KeyType& key, const ValueType& value);//插入一个节点
	bool findNode(const KeyType& key, const ValueType& value);//查找节点
	bool removeNode(const KeyType& key, const ValueType& value);//移除一个节点

private:
	typedef struct HashNode//哈希树的节点类
	{
		KeyType key;//键
		ValueType value;//值
		bool occupied;//是否有效
		HashNode** children;//子节点指针
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
	int childSize;//子树个数
	int *primes;//质数数组
	int primeNum;//质数数组的大小
	HashNode* root;//根

	void insert(HashNode* node, int level, const KeyType& key, const ValueType& value);//插入节点的实际函数
	HashNode* find(HashNode* node, int level, const KeyType& key, const ValueType& value);//查找节点的实际函数
	void release(HashNode* node);//释放内存的函数
	//bool remove(HashNode* node, int level, const KeyType& key, const ValueType& value);

};

//默认构造函数
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
//输入第一个值作为根
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
//输入子树的大小，一个质数数组，数组大小，childSize必须大于prime[primeNum - 1]的值
template<class KeyType, class ValueType>
HashTree<KeyType, ValueType>::HashTree(int childSize, int primes[], int primeNum)
{
	this->childSize = childSize;
	this->primeNum = primeNum;
	this->primes = new int[primeNum];
	for (int i = 0; i < primeNum; i++)
		this->primes[i] = primes[i];
}
//析构函数
template<class KeyType, class ValueType>
HashTree<KeyType, ValueType>::~HashTree()
{
	release(root);
	delete primes;
}
//插入一个节点
template<class KeyType, class ValueType>
void HashTree<KeyType, ValueType>::insertNode(const KeyType& key, const ValueType& value)
{
	return insert(root, 0, key, value);
}
//查找节点
template<class KeyType, class ValueType>
bool HashTree<KeyType, ValueType>::findNode(const KeyType& key, const ValueType& value)
{
	return find(root, 0, key, value) != nullptr;
}
//移除一个节点
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

//插入节点的实际函数
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
		throw "插入失败，超过了限制。";
	insert(node->children[index], level, key, value);

}
//查找节点的实际函数
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

//释放内存的函数
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