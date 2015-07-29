#include <iostream>
#include "SeqStack.h"
#include <memory>
#include "ListStack.h"
#include "SeqQueue.h"
#include "ListQueue.h"

using namespace std;

class A
{
	static int count;
	int mCount;
public:
	A()
	{ 
		cout << ++count << "  A construct!" << endl;
		mCount = count; 
	}
	~A(){ cout << mCount << "  A destruct!" << endl; }

};
int A::count = 0;//静态变量要初始化
void testSeqStack()
{	
	SeqStack<shared_ptr<A>> mStack;
	mStack.push(make_shared<A>());
	mStack.push(make_shared<A>());
	mStack.pop();
	mStack.pop();
	mStack.push(make_shared<A>());
	cout << "test" << endl;
}
void testListStack()
{
	ListStack<shared_ptr<A>> mStack;
	mStack.push(make_shared<A>());
	mStack.push(make_shared<A>());
	mStack.pop();
	mStack.pop();
	mStack.push(make_shared<A>());
	cout << "test" << endl;
}

void testSeqQueue()
{
	SeqQueue<shared_ptr<A>> mQueue;
	for (int i = 0; i < 12; i++)
	{
		mQueue.push(make_shared<A>());
		mQueue.pop();
		cout << mQueue.size() << endl;
	}
}

void testListQueue()
{
	ListQueue<shared_ptr<A>> mQueue;
	for (int i = 0; i < 5; i++)
	{
		mQueue.push(make_shared<A>());
		//mQueue.pop();
		//cout << mQueue.size() << endl;
	}
	for (int i = 0; i < 7; i++)
	{
		//mQueue.push(make_shared<A>());
		mQueue.pop();
		//cout << mQueue.size() << endl;
	}
}
void main()
{	
	//testSeqStack();
	//testListStack();
	//testSeqQueue();
	testListQueue();
	system("pause");
}


