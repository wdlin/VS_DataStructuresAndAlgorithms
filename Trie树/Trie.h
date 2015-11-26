#ifndef _TRIE_H_
#define _TRIE_H_

/*
Trie�����ֳƵ��ʲ��������������һ�����νṹ����һ�ֹ�ϣ���ı��֡�����Ӧ��������ͳ�ƺ���
��������ַ����������������ַ����������Ծ�������������ϵͳ�����ı���Ƶͳ�ơ������ŵ��ǣ�
����޶ȵؼ�����ν���ַ����Ƚϣ���ѯЧ�ʱȹ�ϣ��ߡ�
Trie�ĺ���˼���ǿռ任ʱ�䡣�����ַ����Ĺ���ǰ׺�����Ͳ�ѯʱ��Ŀ����Դﵽ���Ч�ʵ�Ŀ�ġ�

Trie���Ļ������ʿ��Թ���Ϊ��
��1�����ڵ㲻�����ַ��������ڵ�����ÿ���ڵ�ֻ����һ���ַ���
��2���Ӹ��ڵ㵽ĳһ���ڵ㣬·���Ͼ������ַ�����������Ϊ�ýڵ��Ӧ���ַ�����
��3��ÿ���ڵ�������ӽڵ�������ַ�������ͬ��

*/


#define ChildrenSize 26

int char2index(char ch)
{
	return ch - 'a';
}

class Trie
{
public:
	Trie();
	~Trie();
	void insert(char* word);
	int search(char* word);

private:
	struct TrieNode{
		int count;
		TrieNode** children;
		bool exist;
		TrieNode():count(0),exist(false){
			children = new TrieNode*[ChildrenSize];
			for (int i = 0; i < ChildrenSize; i++)
				children[i] = nullptr;
		}
	};
	TrieNode* root;//
	int childrenSize;//
	void release(TrieNode* node);//

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
		//temp->count++;//���Լ�¼ÿ��ǰ׺���ֵĴ��������������ʣ�
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