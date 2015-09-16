#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_
/*
��������ʣ�
1.ÿ�����Ҫô�Ǻ�ģ�Ҫô�Ǻڵġ�
2.������Ǻڵġ�
3.ÿ��Ҷ��㣬���ս�㣨NIL���Ǻڵġ�
4.���һ������Ǻ�ģ���ô�����ӽڵ㶼�Ǻڵġ�
5.����һ�ڵ㵽��ÿ��Ҷ�ӵ����м�·����������ͬ��Ŀ�ĺ�ɫ�ڵ㡣

�߶����Ϊ2log��n+1������ĺ�ڽ���ģ���̵��Ǵ��ڵ�
�������Ӷȣ��O(logn)

����
���������Զ���������ķ������ӽڵ㲢�����Ϊ��ɫ���������Ϊ��ɫ���ͻᵼ�¸���Ҷ�ӵ�·������һ��·�ϣ�
��һ������ĺڽڵ㣬����Ǻ��ѵ����ġ�������Ϊ��ɫ�ڵ�󣬿��ܻᵼ�³�������������ɫ�ڵ�ĳ�ͻ����ô
����ͨ����ɫ������color flips��������ת���������� ����Ҫ����ʲô����ȡ���������ٽ��ڵ����ɫ��ͬ�����
��������һ�������ǽ�ʹ�������常�ڵ���ָһ���ڵ�ĸ��ڵ���ֵܽڵ㡣
ע��:
����1 �� ����3 ���Ǳ����š�
����4 ֻ�����Ӻ�ɫ�ڵ㡢�ػ��ɫ�ڵ�Ϊ��ɫ��������תʱ�ܵ���в��
����5 ֻ�����Ӻ�ɫ�ڵ㡢�ػ��ɫ�ڵ�Ϊ��ɫ��������תʱ�ܵ���в��

��Ҫ����Ľڵ��ΪN��N�ĸ��ڵ��ΪP��N���游�ڵ��ΪG��N���常�ڵ��ΪU��
*/
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <string>
#include <queue>
#define Comparable int

class RedBlackTree
{
public:
	RedBlackTree();//Ĭ�Ϲ��캯��������
	RedBlackTree(const Comparable& item);//���캯����һ���ڵ����
	RedBlackTree(const RedBlackTree& rhs);//�������캯��
	RedBlackTree& operator=(const RedBlackTree& rhs);//��ֵ������
	~RedBlackTree();//��������
	const Comparable& findMin()const;//�ҳ���Сֵ
	const Comparable& findMax()const;//�ҳ����ֵ
	bool contains(const Comparable& item)const;//�Ƿ����Ԫ��
	bool isEmpty()const;//�Ƿ�Ϊ��
	void makeEmpty();//�����
	void insert(const Comparable& item);//����Ԫ�ؽӿ�
	void remove(const Comparable& item);//ɾ��Ԫ�ؽӿ�
	void print();//��ӡ��
	void check();//����Ƿ��������
private:
	enum Color{RED,BLACK};//��ɫ
	struct RedBlackNode//�ڵ��װ��
	{
		Comparable element;
		Color color;
		RedBlackNode* parent;
		RedBlackNode* left;
		RedBlackNode* right;			
		RedBlackNode(const Comparable& e = Comparable(),Color c = RED,RedBlackNode* p = nullptr,RedBlackNode* ln = nullptr,RedBlackNode* rn = nullptr)
		:element(e),color(c),parent(p),left(ln),right(rn){}
		
	};
	void leftRotate(RedBlackNode* node);//����
	void rightRotate(RedBlackNode* node);//����
	void insertFixup(RedBlackNode* node);//������������
	void removeNode(RedBlackNode* node);//ɾ���ڵ㺯��
	void removeFixup(RedBlackNode* node);//ɾ���ڵ���������
	RedBlackNode* find(const Comparable& item)const;//�ҳ�Ԫ�����ڣ����ؽڵ�ָ��
	RedBlackNode* findMin(RedBlackNode* subRoot)const;//�ҳ�������СԪ�أ����ؽڵ�ָ��
	RedBlackNode* findMax(RedBlackNode* subRoot)const;//�ҳ��������Ԫ�أ�����Ԫ��ָ��
	void deleteTree(RedBlackNode* node);//�ͷ��ڴ棬һ��������ڵ㣬�ͷ�������
	RedBlackNode* clone(RedBlackNode* node,RedBlackNode* theNullNode);//���ƽڵ㣬������ڵ㣬����������
	RedBlackNode* root;//���ڵ�
	RedBlackNode* nullNode;//�սڵ�
	int currentSize;//Ԫ�ظ���

};


//Ĭ�Ϲ��캯��������
RedBlackTree::RedBlackTree() :currentSize(0)
{
	nullNode = new RedBlackNode();
	nullNode->color = BLACK;
	root = nullNode;
}
//���캯����һ���ڵ����
RedBlackTree::RedBlackTree(const Comparable& item) :currentSize(1)
{
	nullNode = new RedBlackNode();
	nullNode->color = BLACK;
	root = new RedBlackNode(item, BLACK, nullNode, nullNode, nullNode);
}
//�������캯��
RedBlackTree::RedBlackTree(const RedBlackTree& rhs)
{
	nullNode = new RedBlackNode();
	nullNode->color = BLACK;
	root = clone(rhs.root, rhs.nullNode);
	currentSize = rhs.currentSize;
}
//��ֵ������
RedBlackTree& RedBlackTree::operator=(const RedBlackTree& rhs)
{
	if (root != nullNode)
		deleteTree(root);
	root = clone(rhs.root, rhs.nullNode);
	currentSize = rhs.currentSize;
	return *this;
}
//��������
RedBlackTree::~RedBlackTree()
{
	if (root != nullNode)
		deleteTree(root);
	delete nullNode;
}
//�ҳ���Сֵ
const Comparable& RedBlackTree::findMin()const
{
	RedBlackNode* min = findMin(root);
	if (min == nullNode)
		throw std::runtime_error("Tree is Empty!");
	else
		return min->element;
}
//�ҳ����ֵ
const Comparable& RedBlackTree::findMax()const
{
	RedBlackNode* max = findMax(root);
	if (max == nullNode)
		throw std::runtime_error("Tree is Empty!");
	else
		return max->element;
}
//�Ƿ����Ԫ��
bool RedBlackTree::contains(const Comparable& item)const
{
	return (find(item) == nullNode) ? false : true;
}
//�Ƿ�Ϊ��
bool RedBlackTree::isEmpty()const
{
	return currentSize == 0 ? true : false;
}
//�����
void RedBlackTree::makeEmpty()
{
	if (isEmpty())
		return;
	currentSize = 0;
	deleteTree(root);
	root = nullNode;
}
//����Ԫ�ؽӿ�
void RedBlackTree::insert(const Comparable& item)
{
	if (root == nullNode)//����
	{
		root = new RedBlackNode(item,BLACK,nullNode,nullNode,nullNode);
		currentSize = 1;
		return;
	}
	RedBlackNode* temp = root;//�����
	RedBlackNode* tempParent = nullptr;//�����ĸ��ڵ�
	while (temp != nullNode)
	{
		tempParent = temp;
		if (item < temp->element)
			temp = temp->left;
		else
			temp = temp->right;
	}
	//�����ǿգ����ڵ���Ϊ��ɫ������
	temp = new RedBlackNode(item, RED, tempParent, nullNode, nullNode);
	if (item < tempParent->element)
		tempParent->left = temp;
	else
		tempParent->right = temp;

	currentSize++;
	//����󣬽����������Է��Ϻ�������ص�
	insertFixup(temp);
}
//������������
void RedBlackTree::insertFixup(RedBlackNode* node)
{
	RedBlackNode *uncle = nullptr; //node������ڵ�
	//ѭ��ֱ��node�ĸ��ڵ��Ǻ�ɫ��nodeΪ����㼴��
	while (RED == node->parent->color)
	{
		//������үү����������
		if (node->parent == node->parent->parent->left)
		{
			uncle = node->parent->parent->right;
			//����ڵ�Ϊ��ɫ�������׺�����ڵ㶼�Ǻ�ɫ�����ĳɺ�ɫ��үү�ڵ�ĳɺ�ɫ�����үү�ڵ㣩
			if (RED == uncle->color)
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			//����ڵ�Ϊ��ɫ�������׺�ɫ�������ɫ������Ҫ��취��һ����ɫ�ڵ��Ƶ�����ڵ�һ�࣬���ױ��Ȼ���Ϊүү��үү���Ȼ���Ϊ���壩
			else
			{
				//node���������ϣ���Ҫת��Ϊnode����������
				if (node == node->parent->right)
				{
					node = node->parent;
					leftRotate(node);
				}
				//node����������
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rightRotate(node->parent->parent);
			}
		}
		//������үү���������ϣ��������㷨������ͬ����ת������Ҫ�ı�
		else
		{
			uncle = node->parent->parent->left;
			if (RED == uncle->color)//����ڵ�Ϊ��ɫ
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else//����ڵ�Ϊ��ɫ
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					rightRotate(node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				leftRotate(node->parent->parent);
			}
		}
		//һ��Ҫ����һ�䣬��Ϊ�������nodeָ����root����root����ɫ���ܱ��޸Ĺ�����ʱֻҪ������Ϊ��ɫ����
		root->color = BLACK;
	}

}

/*------------------------------------------------
   x              y
  / \    ==>     / \
 a   y          x   c
    / \        / \
    b  c       a  b

����
------------------------------------------------*/
void RedBlackTree::leftRotate(RedBlackNode* x)
{
	RedBlackNode* y = x->right;
	x->right = y->left;
	if (x->right != nullNode)
		x->right->parent = x;
	y->left = x;
	y->parent = x->parent;
	
	if (x == root)
		root = y;
	else
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	x->parent = y;
}
/*------------------------------------------------
    x              y
   / \            / \
  y   c   ==>    a   x
 / \                / \
a   b              b   c

����
-------------------------------------------------*/
void RedBlackTree::rightRotate(RedBlackNode* x)
{
	RedBlackNode* y = x->left;
	x->left = y->right;
	if (x->left != nullNode)
		x->left->parent = x;
	y->right = x;
	y->parent = x->parent;
	if (x == root)
		root = y;
	else
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	x->parent = y;
}
//�ҳ�Ԫ�����ڣ����ؽڵ�ָ��
RedBlackTree::RedBlackNode* RedBlackTree::find(const Comparable& item)const
{
	RedBlackNode* temp = root;
	assert(root!=nullptr);
	while (temp != nullNode)
	{
		if (item == temp->element)
			return temp;
		if (item < temp->element)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return temp;
}
//�ҳ�������СԪ�أ����ؽڵ�ָ��
RedBlackTree::RedBlackNode* RedBlackTree::findMin(RedBlackNode* subRoot)const
{
	if (subRoot != nullNode)
	while (subRoot->left != nullNode)
		subRoot = subRoot->left;
	return subRoot;
	
}
//�ҳ��������Ԫ�أ�����Ԫ��ָ��
RedBlackTree::RedBlackNode* RedBlackTree::findMax(RedBlackNode* subRoot)const
{
	if (subRoot != nullNode)
	while (subRoot->right != nullNode)
		subRoot = subRoot->right;
	return subRoot;
}
//ɾ��Ԫ�ؽӿ�
void RedBlackTree::remove(const Comparable& item)
{
	RedBlackNode* node = find(item);
	if (node != nullNode)//�ҵ���ɾ��
	{
		removeNode(node);
		currentSize--;
	}
		
}
//ɾ���ڵ㺯��
void RedBlackTree::removeNode(RedBlackNode* node)
{
	RedBlackNode* deleteChild;//ɾ�������ԭ��λ�õ�Ԫ�أ�һ��Ϊ���ӽڵ�
	if (node->left != nullNode && node->right != nullNode)//������������
	{
		RedBlackNode* rightMin = findMin(node->right);
		node->element = rightMin->element;
		if (rightMin->parent->left == rightMin)
			rightMin->parent->left = rightMin->right;
		else
			rightMin->parent->right = rightMin->right;
		node = rightMin;
		deleteChild = rightMin->right;
		deleteChild->parent = rightMin->parent;
	}
	else if (node->left == nullNode && node->right == nullNode)//Ҷ�ӽڵ�
	{
		if (node == root)//���⴦����ڵ�
		{
			delete root;
			root = nullNode;
			return;
		}
		else
		{
			if (node == node->parent->left)
				node->parent->left = nullNode;
			else
				node->parent->right = nullNode;
			deleteChild = nullNode;
			deleteChild->parent = node->parent;
		}
	}
	else//��һ���ӽڵ�
	{
		if (node->left != nullNode)
			deleteChild = node->left;
		else
			deleteChild = node->right;
		if (node == root)//���⴦����ڵ�
		{
			if (root->left == nullNode)
			{
				root = node->right;
				node->right->parent = nullNode;
			}
			else
			{
				root = node->left;
				node->left->parent = nullNode;
			}
		}
		else
		{
			if (node->parent->left == node)
			{
				node->parent->left = deleteChild;
				deleteChild->parent = node->parent;
			}
			else
			{
				node->parent->right = deleteChild;
				deleteChild->parent = node ->parent;
			}
		}
	
	}
	if (node->color == BLACK)//�������ɾ���Ľڵ��Ǻ�ɫ�ģ���Ҫ��������Ϊɾ���˺�ɫ�ģ�������Ӱ��
		removeFixup(deleteChild);
	delete node;//ɾ���ڵ�
}
/*
ɾ���ڵ���������
�������ڸ��ڵ���ߣ��ֵ����ұߣ�
���1��node���ֵ�sibling�Ǻ�ɫ�ġ�
���2��node���ֵ�sibling�Ǻ�ɫ�ģ���sibling���������Ӷ��Ǻ�ɫ�ġ�
���3��node���ֵ�sibling�Ǻ�ɫ�ģ�sibling�������Ǻ�ɫ��sibling���Һ����Ǻ�ɫ��
���4��node���ֵ�sibling�Ǻ�ɫ�ģ���sibling���Һ���ʱ��ɫ�ġ�

*/
void RedBlackTree::removeFixup(RedBlackNode* node)
{
	RedBlackNode* sibling;
	while (node != root && node->color == BLACK)
	{
		if (node == node->parent->left)
		{
			sibling = node->parent->right;
			/*
			//���1��node���ֵ�sibling�Ǻ�ɫ�ġ�����1�����ת����2��3��4
			��Ϊ�ֵ��Ǻ�ģ����Ը��׿϶��Ǻڵġ�
			�ֵܱ�ڣ����ױ�죬���������ף����츸�׽�����ߣ����ֵ�����Ϊ���ס�
			Ȼ����߻���ȱһ��������ת��Ϊ��������ˡ���ʱnode���ֵܱ��ˣ���ɫ�ģ���
			*/
			if (sibling->color == RED)
			{
				sibling->color = BLACK;
				node->parent->color = RED;
				leftRotate(node->parent);
				sibling = node->parent->right;
			}
			/*
			//���2��node���ֵ�sibling�Ǻ�ɫ�ģ���sibling���������Ӷ��Ǻ�ɫ�ġ�
			nodeһ��ȱһ����ɫ���ֵܼ��亢�Ӷ��Ǻڵģ����Կ��Խ��ֵܱ�죬node��Ϊnode�ĸ��ף�Ȼ���µ�nodeҲ��ȱһ����
			*/
			if (sibling->left->color == BLACK && sibling->right->color == BLACK)
			{
				sibling->color = RED;
				node = node->parent;
			}
			/*
			//���3��node���ֵ�sibling�Ǻ�ɫ�ģ�sibling�������Ǻ�ɫ��sibling���Һ����Ǻ�ɫ��
			���ֵܵ����ӱ�ɺ�ɫ���ֵܱ�ɺ�ɫ���������ֵܣ����ұ�ά���˺�����ʣ�
			����ת���������4
			*/
			else if (sibling->right->color == BLACK)
			{
				sibling->left->color = BLACK;
				sibling->color = RED;
				rightRotate(sibling);
				sibling = node->parent->right;
			}
			/*
			//���4��node���ֵ�sibling�Ǻ�ɫ�ģ���sibling���Һ���ʱ��ɫ�ġ�
			���ֵܽڵ����ɫ�̳и��׵ģ����ױ�ڣ��ֵܵ��Һ��ӱ�ڣ����������ף�
			��ô��ɫ�ĸ��׽�����࣬ԭ���ֵܵ��Һ����滻��ԭ�����ֵܣ��ұߵĿ�ʼ���ڣ�����������ƽ���ˡ�
			*/
			else
			{
				sibling->color = node->parent->color;
				node->parent->color = BLACK;
				sibling->right->color = BLACK;
				leftRotate(node->parent);
				node = root;//��ֹ����
			}
		}
		else
		{
			sibling = node->parent->left;
			if (sibling->color == RED)
			{
				sibling->color = BLACK;
				node->parent->color = RED;
				rightRotate(node->parent);
				sibling = node->parent->left;
			}
			if (sibling->left->color == BLACK && sibling->right->color == BLACK)
			{
				sibling->color = RED;
				node = node->parent;
			}
			else if (sibling->left->color == BLACK)
			{
				sibling->right->color = BLACK;
				sibling->color = RED;
				leftRotate(sibling);
				sibling = node->parent->left;
			}
			else
			{
				sibling->color = node->parent->color;
				node->parent->color = BLACK;
				sibling->left->color = BLACK;
				rightRotate(node->parent);
				node = root;
			}
		}
	}
	node->color = BLACK;
}
//���ƽڵ㣬������ڵ㣬����������
RedBlackTree::RedBlackNode* RedBlackTree::clone(RedBlackNode* node,RedBlackNode* theNullNode)
{
	if (node == nullptr)
		return nullptr;
	if (node == theNullNode)
		return nullNode;
	
	RedBlackNode* leftChild = clone(node->left, theNullNode);
	RedBlackNode* rightChild = clone(node->right, theNullNode);
	RedBlackNode* newNode = new RedBlackNode(node->element, node->color, nullNode, leftChild, rightChild);
	leftChild->parent = newNode;
	rightChild->parent = newNode;
	return newNode;
}
//�ͷ��ڴ棬һ��������ڵ㣬�ͷ�����
void RedBlackTree::deleteTree(RedBlackNode* node)
{
	if (node == nullptr || node == nullNode)
		return;
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}

//��ӡ��
void RedBlackTree::print()
{
	int layer = 2 * log2(currentSize + 1);
	using namespace std;
	if (isEmpty())
	{
		cout << "Tree is empty!" << endl;
		return;
	}
	cout << "Tree:" << endl;
	queue<RedBlackNode*> queue;
	queue.push(root);
	int maxnum = pow(2, layer) - 1;
	int addCount = 1;
	int layerCount = 1;
	int outCount = 0;
	RedBlackNode* p;
	while (!queue.empty())
	{
		p = queue.front();
		queue.pop();
		if (p == nullNode)
		{
			string color = (p->color == RED) ? "r" : "b";
			cout << "NL" << "(" << color << ")" << ",";
			if (addCount + 2 <= maxnum)
			{
				queue.push(nullNode);
				queue.push(nullNode);
				addCount = addCount + 2;
			}
		}
		else
		{
			string color = (p->color == RED) ? "r" : "b";
			cout << p->element << "(" << color << ")" << ",";
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

//����Ƿ��������
void RedBlackTree::check()
{
	using namespace std;
	if (isEmpty())
	{
		cout << "����������ǿյģ�" << endl;
		return;
	}

	cout << "����Ԫ�ظ��� : " <<currentSize<< endl;
	
	queue<RedBlackNode*> queue;
	queue.push(root);
	RedBlackNode* p;
	bool flag1 = true;
	bool flag2 = (root->color == BLACK) ? true : false;//����2
	bool flag3 = true;
	bool flag4 = true;
	bool flag5 = true;
	int testNum = currentSize;
	while (!queue.empty())
	{
		p = queue.front();
		queue.pop();
		if (p->color != RED && p->color != BLACK)//����1
			flag1 = false;
		if (p == nullNode)//����3
		{
			if (p->color != BLACK)
				flag3 = false;
		}
		if (p->color == RED)//����4
		{
			if (p->left->color == RED || p->right->color == RED)
				flag4 = false;
		}
		if (p != nullNode)//����������Ե�5�����ʣ���©�������ǲ����󱨴�
		{
			RedBlackNode* temp = p;
			int sum = 0;
			while (true)
			{
				if (temp->color == BLACK)
					sum++;
				if (temp == nullNode)
					break;
				if (rand() % 2 == 0)
					temp = temp->left;
				else
					temp = temp->right;
			}
			int count = 0;
			
			for (int i = 0; i < testNum; i++)
			{
				temp = p;
				count = 0;
				while (true)
				{
					if (temp->color == BLACK)
						count++;
					if (temp == nullNode)
						break;
					if (rand() % 2 == 0)
						temp = temp->left;
					else
						temp = temp->right;
				}
				if (count != sum)
					flag5 = false;
			}
			testNum--;
		}
		if (p == nullNode)
			;
		else
		{
			queue.push(p->left);
			queue.push(p->right);
		}
	}
	cout << "����1��ÿ���ڵ㶼�Ǻ�ɫ���ߺ�ɫ��-- �������";
	if (flag1)
		cout << "ͨ����" << endl;
	else
		cout << "��ͨ����" << endl;

	cout << "����2�����ڵ��Ǻڵġ�-- �������" ;
	if (flag2)
		cout << "ͨ����" << endl;
	else
		cout << "��ͨ����" << endl;

	cout << "����3��ÿ��Ҷ�ڵ㣨NIL���Ǻڵġ�-- �������";
	if (flag3)
		cout << "ͨ����" << endl;
	else
		cout << "��ͨ����" << endl;
	cout << "����4�����һ���ڵ��Ǻ�ɫ�ģ������ӽڵ㶼�Ǻ�ɫ��-- �������";
	if (flag4)
		cout << "ͨ����" << endl;
	else
		cout << "��ͨ����" << endl;
	
	cout << "����5������ÿ���ڵ㣬�Ӹýڵ㵽���к��Ҷ�ڵ�ļ�·����������Ŀ��ͬ�ĺ�ɫ�ڵ㡣-- �������";
	if (flag5)
		cout << "ͨ����" << endl;
	else
		cout << "��ͨ����" << endl;
	
}

#endif
