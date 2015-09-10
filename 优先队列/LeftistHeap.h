#ifndef _LEFTIST_HEAP_H_
#define _LEFTIST_HEAP_H_

/*
��ʽ�ѣ����е��κνڵ㣬������ӵ���·����>=�Ҷ��ӵ���·�����Ķ���ѡ�
��·���� Npl��null path length������X��һ���������������ӵĽ������·���ĳ���
���ʣ�
1. ��һ������·��������������ӽ�����·��������Сֵ��1
2. ���е��κνڵ㣬������ӵ���·����>=�Ҷ��ӵ���·�����Ķ���ѡ�
��1��2֪����ʽ���������NplΪ�Һ��ӵ�Npl+1.
3. ����·������r���ڵ����ʽ��������2^r - 1���ڵ㡣

ʱ�临�Ӷȣ�
���������Ĳ��������ںϲ������ϲ�������·���ϲ�������·��������Ϊ�������Ķ�����ϵ��
������ʽ�ѵ���������������ʱ��ΪO(logN).

��ʽ�ѵĺϲ������Ĳ���
1.�����һ�����ǿ������򷵻���һ������
����ϲ��������ѣ��Ƚ����ǵĸ����ݹ�ؽ����нϴ��ֵ�Ķ� �� ���н��ٸ�ֵ�Ķѵ����ӶѺϲ���
2.ʹ�γɵ��¶���Ϊ��С��ֵ�ѵ���������
3.���Υ������ʽ�ѵ����ԣ���������������λ�á�
4.����Npl��
��ʽ�ѵĲ��루Insert���ܼ򵥣���ʵҲ����һ��������ԭ�ѵĺϲ���
��ʽ�ѵ�DleteMinҲ�ܼ򵥣����ǰѸ����ɾ���������������ϲ�����ʽ�ѵ�ɾ�����Կ�������ɾ����Lazy Delete����
*/
#include <stdexcept>
#include <queue>

template<class Comparable>
class LeftistHeap
{
public:
	LeftistHeap();
	LeftistHeap(const LeftistHeap& rhs);
	~LeftistHeap();
	LeftistHeap& operator=(const LeftistHeap& rhs);
	bool isEmpty() const;//�Ƿ�Ϊ��
	Comparable getMin() const;//��ȡ��Сֵ
	void deleteMin();//ɾ����Сֵ
	void insert(const Comparable & item);//����Ԫ��
	void makeEmpty();//�������Ԫ��
	void merge(LeftistHeap& rhs);//�ϲ��ӿں���
	void print(int layer);//��ӡ,����Ϊ��ӡ���ٲ�,��Ϊ�ǲ�ƽ�����������п��ܴ���˻��ߴ�С�ˡ�
private:
	struct LeftistNode
	{
		Comparable element;
		LeftistNode* left;
		LeftistNode* right;
		int npl;//�ڵ����·��
		LeftistNode(const Comparable& theElement,LeftistNode* lt = nullptr,LeftistNode* rt = nullptr,int theNpl = 0)
		:element(theElement),left(lt),right(rt),npl(theNpl){}
	};
	LeftistNode* root;//�ѵĸ�
	LeftistNode* merge(LeftistNode* node1, LeftistNode* node2);//�ϲ���������
	LeftistNode* actualMerge(LeftistNode* smallerNode, LeftistNode* largerNode);//ʵ�ʺϲ�����
	int getNpl(LeftistNode* node);//��ȡһ���ڵ����·��
	void swapChildren(LeftistNode* node);//�����ڵ����������
	void reclaimMemory(LeftistNode* node);//�ͷŶѵ��ڴ�
	LeftistNode* clone(LeftistNode* node);//��¡����

};
template<class Comparable>
LeftistHeap<Comparable>::LeftistHeap() :root(nullptr)
{
}
template<class Comparable>
LeftistHeap<Comparable>::LeftistHeap(const LeftistHeap<Comparable>& rhs)
{
	root = clone(rhs.root);
}
template<class Comparable>
LeftistHeap<Comparable>& LeftistHeap<Comparable>::operator=(const LeftistHeap<Comparable>& rhs)
{
	if (this != &rhs)
	{
		makeEmpty();
		root = clone(rhs.root);
	}
	return *this;
}
template<class Comparable>
LeftistHeap<Comparable>::~LeftistHeap()
{
	reclaimMemory(root);
}
//�Ƿ�Ϊ��
template<class Comparable>
bool LeftistHeap<Comparable>::isEmpty() const
{
	return root == nullptr;
}

//��ȡ��Сֵ
template<class Comparable>
Comparable LeftistHeap<Comparable>::getMin() const
{
	if (isEmpty())
		throw std::runtime_error("Heap is Empty!");
	return root->element;
}
//ɾ����Сֵ
template<class Comparable>
void LeftistHeap<Comparable>::deleteMin()
{
	if (isEmpty())
		return;
	LeftistNode* oldRoot = root;
	root = merge(root->left, root->right);
	delete oldRoot;
}
//����Ԫ��
template<class Comparable>
void LeftistHeap<Comparable>::insert(const Comparable & item)
{
	root = merge(new LeftistNode(item), root);
}

//�������Ԫ��
template<class Comparable>
void LeftistHeap<Comparable>::makeEmpty()
{
	reclaimMemory(root);
	root = nullptr;
}
//�ϲ��ѵĽӿں���
template<class Comparable>
void LeftistHeap<Comparable>::merge(LeftistHeap& rhs)
{
	if (this == &rhs)//���⸴���Լ�
		return;
	root = merge(root, rhs.root);
	rhs.root = nullptr;
}

//�ϲ���������
template<class Comparable>
typename LeftistHeap<Comparable>::LeftistNode* LeftistHeap<Comparable>::merge(LeftistNode* node1, LeftistNode* node2)
{
	if (node1 == nullptr)
		return node2;
	if (node2 == nullptr)
		return node1;
	if (node1->element < node2->element)
		return actualMerge(node1, node2);
	else
		return actualMerge(node2, node1);
}
template<class Comparable>
typename LeftistHeap<Comparable>::LeftistNode* LeftistHeap<Comparable>::actualMerge(LeftistNode* smallerNode, LeftistNode* largerNode)
{
	//����ĸ�ֵ�Ķ� �� С��ֵ�Ķѵ����Ӷѣ� �ϲ�����¶� ��Ϊ С��ֵ�Ķѵ��Ҷ��� 
	smallerNode->right = merge(smallerNode->right, largerNode);
	if (getNpl(smallerNode->left) < getNpl(smallerNode->right))
		swapChildren(smallerNode);
	smallerNode->npl = getNpl(smallerNode->right) + 1;

	return smallerNode;
}
//��ȡ�ڵ��npl
template<class Comparable>
int LeftistHeap<Comparable>::getNpl(LeftistNode* node)
{
	if (node == nullptr)
		return -1;
	else
		return node->npl;
}

//�����������ӽڵ�
template<class Comparable>
void LeftistHeap<Comparable>::swapChildren(LeftistNode* node)
{
	LeftistNode* temp = node->left;
	node->left = node->right;
	node->right = temp;
}

//�ͷŶѵ��ڴ�
template<class Comparable>
void LeftistHeap<Comparable>::reclaimMemory(LeftistNode* node)
{
	if (node == nullptr)
		return;
	reclaimMemory(node->left);
	reclaimMemory(node->right);
	delete node;
}

//��¡����
template<class Comparable>
typename LeftistHeap<Comparable>::LeftistNode* LeftistHeap<Comparable>::clone(LeftistNode* node)
{
	if (node == nullptr)
		return nullptr;
	return new LeftistNode(node->element, clone(node->left), clone(node->right),node->npl);
}
//��ӡ,����Ϊ��ӡ���ٲ�,��Ϊ�ǲ�ƽ�����������п��ܴ���˻��ߴ�С�ˡ�
template<class Comparable>
void LeftistHeap<Comparable>::print(int layer)
{
	using namespace std;
	if (isEmpty())
	{
		cout << "Heap is empty!" << endl;
		return;
	}
	cout << "Heap:" << endl;
	queue<LeftistNode*> queue;
	queue.push(root);
	int maxnum = pow(2,layer) - 1;
	int addCount = 1;
	int layerCount = 1;
	int outCount = 0;
	LeftistNode* p;
	while (!queue.empty())
	{
		p = queue.front();
		queue.pop();
		if (p == nullptr)
		{
			cout << "NL" <<"("<<getNpl(p)<<")"<< ",";
			if (addCount + 2 <= maxnum)
			{
				queue.push(nullptr);
				queue.push(nullptr);
				addCount = addCount + 2;
			}
		}
		else
		{
			cout << p->element << "(" << getNpl(p) << ")" << ",";
			if (addCount + 2 <= maxnum)
			{
				queue.push(p->left);
				queue.push(p->right);
				addCount = addCount + 2;
			}
		}
		outCount++;
		if (outCount == pow(2, layerCount) - 1)
		{
			layerCount++;
			cout << endl;
		}
	}
}

#endif
