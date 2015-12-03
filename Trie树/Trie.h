#ifndef _TRIE_H_
#define _TRIE_H_

/*
Trie树，又称单词查找树或键树，是一种树形结构，是一种哈希树的变种。典型应用是用于统计和排
序大量的字符串（但不仅限于字符串），所以经常被搜索引擎系统用于文本词频统计。它的优点是：
最大限度地减少无谓的字符串比较，查询效率比哈希表高。
Trie的核心思想是空间换时间。利用字符串的公共前缀来降低查询时间的开销以达到提高效率的目的。

Trie树的基本性质可以归纳为：
（1）根节点不包含字符，除根节点意外每个节点只包含一个字符。
（2）从根节点到某一个节点，路径上经过的字符连接起来，为该节点对应的字符串。
（3）每个节点的所有子节点包含的字符串不相同。

*/


#define ChildrenSize 26
//将字符转换成下标的映射函数
int char2index(char ch)
{
	return ch - 'a';
}

class Trie
{
public:
	Trie();//构造函数
	~Trie();//析构函数
	void insert(char* word);//插入节点
	int search(char* word);//查询节点

private:
	struct TrieNode{//Trie树的内部节点类
		int count;//字符串计数
		TrieNode** children;//子树
		bool exist;//该节点是否是存在的完整字符串节点
		TrieNode():count(0),exist(false){
			children = new TrieNode*[ChildrenSize];
			for (int i = 0; i < ChildrenSize; i++)
				children[i] = nullptr;
		}
	};
	TrieNode* root;//根
	int childrenSize;//子树的大小
	void release(TrieNode* node);//释放内存

};


Trie::Trie() :childrenSize(ChildrenSize)
{
	root = new TrieNode();
}

Trie::~Trie()
{
	release(root);
}

void Trie::insert(char* word)
{
	TrieNode* temp = root;
	char* p = word;
	int index;
	while (*p)
	{
		index = char2index(*p);
		if (temp->children[index] == nullptr)
		{
			temp->children[index] = new TrieNode();
		}
		temp = temp->children[index];
		++p;	
		//temp->count++;//可以记录每个前缀出现的次数（包含本单词）
	}
	temp->count++;
	temp->exist = true;
}

int Trie::search(char* word)
{
	TrieNode* temp = root;
	char* p = word;
	int index;
	while (*p)
	{
		index = char2index(*p);
		if (temp->children[index] == nullptr)
			return 0;
		temp = temp->children[index];
		++p;
	}
	if (temp->exist)
		return temp->count;
	else return 0;
}

void Trie::release(Trie::TrieNode* node)
{
	for (int i = 0; i < childrenSize; i++)
	{
		if (node->children[i] != nullptr)
			release(node->children[i]);
	}
	delete node;
}
#endif