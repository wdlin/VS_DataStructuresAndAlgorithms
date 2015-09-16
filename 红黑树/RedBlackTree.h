#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_
/*
红黑树性质：
1.每个结点要么是红的，要么是黑的。
2.根结点是黑的。
3.每个叶结点，即空结点（NIL）是黑的。
4.如果一个结点是红的，那么它的子节点都是黑的。
5.从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点。

高度最多为2log（n+1），最长的红黑交错的，最短的是纯黑的
操作复杂度：最坏O(logn)

插入
我们首先以二叉查找树的方法增加节点并标记它为红色。（如果设为黑色，就会导致根到叶子的路径上有一条路上，
多一个额外的黑节点，这个是很难调整的。但是设为红色节点后，可能会导致出现两个连续红色节点的冲突，那么
可以通过颜色调换（color flips）和树旋转来调整。） 下面要进行什么操作取决于其他临近节点的颜色。同人类的
家族树中一样，我们将使用术语叔父节点来指一个节点的父节点的兄弟节点。
注意:
性质1 和 性质3 总是保持着。
性质4 只在增加红色节点、重绘黑色节点为红色，或做旋转时受到威胁。
性质5 只在增加黑色节点、重绘红色节点为黑色，或做旋转时受到威胁。

将要插入的节点标为N，N的父节点标为P，N的祖父节点标为G，N的叔父节点标为U。
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
	RedBlackTree();//默认构造函数，空树
	RedBlackTree(const Comparable& item);//构造函数，一个节点的树
	RedBlackTree(const RedBlackTree& rhs);//拷贝构造函数
	RedBlackTree& operator=(const RedBlackTree& rhs);//赋值操作符
	~RedBlackTree();//析构函数
	const Comparable& findMin()const;//找出最小值
	const Comparable& findMax()const;//找出最大值
	bool contains(const Comparable& item)const;//是否包含元素
	bool isEmpty()const;//是否为空
	void makeEmpty();//清空树
	void insert(const Comparable& item);//插入元素接口
	void remove(const Comparable& item);//删除元素接口
	void print();//打印树
	void check();//检测是否符合性质
private:
	enum Color{RED,BLACK};//颜色
	struct RedBlackNode//节点包装类
	{
		Comparable element;
		Color color;
		RedBlackNode* parent;
		RedBlackNode* left;
		RedBlackNode* right;			
		RedBlackNode(const Comparable& e = Comparable(),Color c = RED,RedBlackNode* p = nullptr,RedBlackNode* ln = nullptr,RedBlackNode* rn = nullptr)
		:element(e),color(c),parent(p),left(ln),right(rn){}
		
	};
	void leftRotate(RedBlackNode* node);//左旋
	void rightRotate(RedBlackNode* node);//右旋
	void insertFixup(RedBlackNode* node);//插入后调整函数
	void removeNode(RedBlackNode* node);//删除节点函数
	void removeFixup(RedBlackNode* node);//删除节点后调整函数
	RedBlackNode* find(const Comparable& item)const;//找出元素所在，返回节点指针
	RedBlackNode* findMin(RedBlackNode* subRoot)const;//找出子树最小元素，返回节点指针
	RedBlackNode* findMax(RedBlackNode* subRoot)const;//找出子树最大元素，返回元素指针
	void deleteTree(RedBlackNode* node);//释放内存，一般输入根节点，释放整棵树
	RedBlackNode* clone(RedBlackNode* node,RedBlackNode* theNullNode);//复制节点，输入根节点，返回整棵树
	RedBlackNode* root;//根节点
	RedBlackNode* nullNode;//空节点
	int currentSize;//元素个数

};


//默认构造函数，空树
RedBlackTree::RedBlackTree() :currentSize(0)
{
	nullNode = new RedBlackNode();
	nullNode->color = BLACK;
	root = nullNode;
}
//构造函数，一个节点的树
RedBlackTree::RedBlackTree(const Comparable& item) :currentSize(1)
{
	nullNode = new RedBlackNode();
	nullNode->color = BLACK;
	root = new RedBlackNode(item, BLACK, nullNode, nullNode, nullNode);
}
//拷贝构造函数
RedBlackTree::RedBlackTree(const RedBlackTree& rhs)
{
	nullNode = new RedBlackNode();
	nullNode->color = BLACK;
	root = clone(rhs.root, rhs.nullNode);
	currentSize = rhs.currentSize;
}
//赋值操作符
RedBlackTree& RedBlackTree::operator=(const RedBlackTree& rhs)
{
	if (root != nullNode)
		deleteTree(root);
	root = clone(rhs.root, rhs.nullNode);
	currentSize = rhs.currentSize;
	return *this;
}
//析构函数
RedBlackTree::~RedBlackTree()
{
	if (root != nullNode)
		deleteTree(root);
	delete nullNode;
}
//找出最小值
const Comparable& RedBlackTree::findMin()const
{
	RedBlackNode* min = findMin(root);
	if (min == nullNode)
		throw std::runtime_error("Tree is Empty!");
	else
		return min->element;
}
//找出最大值
const Comparable& RedBlackTree::findMax()const
{
	RedBlackNode* max = findMax(root);
	if (max == nullNode)
		throw std::runtime_error("Tree is Empty!");
	else
		return max->element;
}
//是否包含元素
bool RedBlackTree::contains(const Comparable& item)const
{
	return (find(item) == nullNode) ? false : true;
}
//是否为空
bool RedBlackTree::isEmpty()const
{
	return currentSize == 0 ? true : false;
}
//清空树
void RedBlackTree::makeEmpty()
{
	if (isEmpty())
		return;
	currentSize = 0;
	deleteTree(root);
	root = nullNode;
}
//插入元素接口
void RedBlackTree::insert(const Comparable& item)
{
	if (root == nullNode)//空树
	{
		root = new RedBlackNode(item,BLACK,nullNode,nullNode,nullNode);
		currentSize = 1;
		return;
	}
	RedBlackNode* temp = root;//插入点
	RedBlackNode* tempParent = nullptr;//插入点的父节点
	while (temp != nullNode)
	{
		tempParent = temp;
		if (item < temp->element)
			temp = temp->left;
		else
			temp = temp->right;
	}
	//若树非空，将节点设为红色并插入
	temp = new RedBlackNode(item, RED, tempParent, nullNode, nullNode);
	if (item < tempParent->element)
		tempParent->left = temp;
	else
		tempParent->right = temp;

	currentSize++;
	//插入后，进行修正，以符合红黑树的特点
	insertFixup(temp);
}
//插入后调整函数
void RedBlackTree::insertFixup(RedBlackNode* node)
{
	RedBlackNode *uncle = nullptr; //node的叔叔节点
	//循环直到node的父节点是黑色或node为根结点即可
	while (RED == node->parent->color)
	{
		//叔叔在爷爷的右子树上
		if (node->parent == node->parent->parent->left)
		{
			uncle = node->parent->parent->right;
			//叔叔节点为红色，（父亲和叔叔节点都是红色，都改成黑色，爷爷节点改成红色，检测爷爷节点）
			if (RED == uncle->color)
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			//叔叔节点为黑色，（父亲红色，叔叔黑色，所以要想办法将一个红色节点移到叔叔节点一侧，父亲变黑然后成为爷爷，爷爷变红然后成为叔叔）
			else
			{
				//node在右子树上，需要转换为node在左子树上
				if (node == node->parent->right)
				{
					node = node->parent;
					leftRotate(node);
				}
				//node在左子树上
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rightRotate(node->parent->parent);
			}
		}
		//叔叔在爷爷的左子树上，与上面算法基本相同，旋转方向需要改变
		else
		{
			uncle = node->parent->parent->left;
			if (RED == uncle->color)//叔叔节点为红色
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else//叔叔节点为黑色
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
		//一定要加这一句，因为可能最后node指向了root，且root的颜色可能被修改过，这时只要将根设为黑色即可
		root->color = BLACK;
	}

}

/*------------------------------------------------
   x              y
  / \    ==>     / \
 a   y          x   c
    / \        / \
    b  c       a  b

左旋
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

右旋
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
//找出元素所在，返回节点指针
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
//找出子树最小元素，返回节点指针
RedBlackTree::RedBlackNode* RedBlackTree::findMin(RedBlackNode* subRoot)const
{
	if (subRoot != nullNode)
	while (subRoot->left != nullNode)
		subRoot = subRoot->left;
	return subRoot;
	
}
//找出子树最大元素，返回元素指针
RedBlackTree::RedBlackNode* RedBlackTree::findMax(RedBlackNode* subRoot)const
{
	if (subRoot != nullNode)
	while (subRoot->right != nullNode)
		subRoot = subRoot->right;
	return subRoot;
}
//删除元素接口
void RedBlackTree::remove(const Comparable& item)
{
	RedBlackNode* node = find(item);
	if (node != nullNode)//找到才删除
	{
		removeNode(node);
		currentSize--;
	}
		
}
//删除节点函数
void RedBlackTree::removeNode(RedBlackNode* node)
{
	RedBlackNode* deleteChild;//删除后替代原来位置的元素，一般为孩子节点
	if (node->left != nullNode && node->right != nullNode)//具有两个孩子
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
	else if (node->left == nullNode && node->right == nullNode)//叶子节点
	{
		if (node == root)//特殊处理根节点
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
	else//有一个子节点
	{
		if (node->left != nullNode)
			deleteChild = node->left;
		else
			deleteChild = node->right;
		if (node == root)//特殊处理根节点
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
	if (node->color == BLACK)//如果真正删除的节点是黑色的，需要调整，因为删除了红色的，不会有影响
		removeFixup(deleteChild);
	delete node;//删除节点
}
/*
删除节点后调整函数
待调整在父节点左边，兄弟在右边：
情况1：node的兄弟sibling是红色的。
情况2：node的兄弟sibling是黑色的，且sibling的俩个孩子都是黑色的。
情况3：node的兄弟sibling是黑色的，sibling的左孩子是红色，sibling的右孩子是黑色。
情况4：node的兄弟sibling是黑色的，且sibling的右孩子时红色的。

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
			//情况1：node的兄弟sibling是红色的。将第1种情况转化成2、3、4
			因为兄弟是红的，所以父亲肯定是黑的。
			兄弟变黑，父亲变红，左旋（父亲）。红父亲进入左边，黑兄弟上升为父亲。
			然后左边还是缺一个，但是转化为其他情况了。此时node的兄弟变了（黑色的）。
			*/
			if (sibling->color == RED)
			{
				sibling->color = BLACK;
				node->parent->color = RED;
				leftRotate(node->parent);
				sibling = node->parent->right;
			}
			/*
			//情况2：node的兄弟sibling是黑色的，且sibling的俩个孩子都是黑色的。
			node一侧缺一个黑色，兄弟及其孩子都是黑的，所以可以将兄弟变红，node提为node的父亲，然后新的node也是缺一个黑
			*/
			if (sibling->left->color == BLACK && sibling->right->color == BLACK)
			{
				sibling->color = RED;
				node = node->parent;
			}
			/*
			//情况3：node的兄弟sibling是黑色的，sibling的左孩子是红色，sibling的右孩子是黑色。
			将兄弟的左孩子变成黑色，兄弟变成红色，右旋（兄弟），右边维持了红黑性质，
			但是转换成了情况4
			*/
			else if (sibling->right->color == BLACK)
			{
				sibling->left->color = BLACK;
				sibling->color = RED;
				rightRotate(sibling);
				sibling = node->parent->right;
			}
			/*
			//情况4：node的兄弟sibling是黑色的，且sibling的右孩子时红色的。
			将兄弟节点的颜色继承父亲的，父亲变黑，兄弟的右孩子变黑，左旋（父亲）
			那么黑色的父亲进入左侧，原来兄弟的右孩子替换了原来的兄弟（右边的开始（黑）），整个树平衡了。
			*/
			else
			{
				sibling->color = node->parent->color;
				node->parent->color = BLACK;
				sibling->right->color = BLACK;
				leftRotate(node->parent);
				node = root;//终止条件
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
//复制节点，输入根节点，返回整棵树
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
//释放内存，一般输入根节点，释放整棵
void RedBlackTree::deleteTree(RedBlackNode* node)
{
	if (node == nullptr || node == nullNode)
		return;
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}

//打印树
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

//检测是否符合性质
void RedBlackTree::check()
{
	using namespace std;
	if (isEmpty())
	{
		cout << "检测结果：树是空的！" << endl;
		return;
	}

	cout << "树的元素个数 : " <<currentSize<< endl;
	
	queue<RedBlackNode*> queue;
	queue.push(root);
	RedBlackNode* p;
	bool flag1 = true;
	bool flag2 = (root->color == BLACK) ? true : false;//性质2
	bool flag3 = true;
	bool flag4 = true;
	bool flag5 = true;
	int testNum = currentSize;
	while (!queue.empty())
	{
		p = queue.front();
		queue.pop();
		if (p->color != RED && p->color != BLACK)//性质1
			flag1 = false;
		if (p == nullNode)//性质3
		{
			if (p->color != BLACK)
				flag3 = false;
		}
		if (p->color == RED)//性质4
		{
			if (p->left->color == RED || p->right->color == RED)
				flag4 = false;
		}
		if (p != nullNode)//采用随机测试第5个性质，会漏报错，但是不会误报错
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
	cout << "性质1：每个节点都是红色或者黑色。-- 检测结果：";
	if (flag1)
		cout << "通过！" << endl;
	else
		cout << "不通过！" << endl;

	cout << "性质2：根节点是黑的。-- 检测结果：" ;
	if (flag2)
		cout << "通过！" << endl;
	else
		cout << "不通过！" << endl;

	cout << "性质3：每个叶节点（NIL）是黑的。-- 检测结果：";
	if (flag3)
		cout << "通过！" << endl;
	else
		cout << "不通过！" << endl;
	cout << "性质4：如果一个节点是红色的，两个子节点都是黑色。-- 检测结果：";
	if (flag4)
		cout << "通过！" << endl;
	else
		cout << "不通过！" << endl;
	
	cout << "性质5：对于每个节点，从该节点到所有后代叶节点的简单路径均包含数目相同的黑色节点。-- 检测结果：";
	if (flag5)
		cout << "通过！" << endl;
	else
		cout << "不通过！" << endl;
	
}

#endif
