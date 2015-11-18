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



*/

//template<class keyType,class valueType>
#define KeyType int
#define ValueType int



class HashTree
{
public:
	HashTree();
	HashTree(KeyType key,ValueType value);
	HashTree(int childSize, int primes[], int primeNum);//childSize必须大于prime[primeNum - 1]的值
	~HashTree();
	void insertNode(const KeyType& key, const ValueType& value);
	bool findNode(const KeyType& key, const ValueType& value);
	bool removeNode(const KeyType& key, const ValueType& value);

private:
	struct HashNode
	{
		KeyType key;
		ValueType value;
		bool occupied;
		HashNode** children;
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

	};
	int childSize;
	int *primes;
	int primeNum;
	HashNode* root;

	void insert(HashNode* node, int level, const KeyType& key, const ValueType& value);
	HashNode* find(HashNode* node, int level, const KeyType& key, const ValueType& value);
	void release(HashNode* node);
	//bool remove(HashNode* node, int level, const KeyType& key, const ValueType& value);

};


HashTree::HashTree() :childSize(32), primeNum(10)
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

HashTree::HashTree(KeyType key, ValueType value) :childSize(32), primeNum(10)
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
}

HashTree::HashTree(int childSize, int primes[], int primeNum)//childSize必须大于prime[primeNum - 1]的值
{
	this->childSize = childSize;
	this->primeNum = primeNum;
	this->primes = new int[primeNum];
	for (int i = 0; i < primeNum; i++)
		this->primes[i] = primes[i];
}

HashTree::~HashTree()
{
	release(root);
	delete primes;
}
void HashTree::insertNode(const KeyType& key, const ValueType& value)
{
	return insert(root, 0, key, value);
}
bool HashTree::findNode(const KeyType& key, const ValueType& value)
{
	return find(root, 0, key, value) != nullptr;
}
bool HashTree::removeNode(const KeyType& key, const ValueType& value)
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


void HashTree::insert(HashNode* node, int level, const KeyType& key, const ValueType& value)
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
HashTree::HashNode* HashTree::find(HashNode* node, int level, const KeyType& key, const ValueType& value)
{
	if (node->occupied == true && node->key == key&&node->value == value)
		return node;
	int index = key%primes[level];
	if (node->children[index] == nullptr)
		return nullptr;
	level++;
	return find(node->children[index], level, key, value);
}

void HashTree::release(HashNode* node)
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