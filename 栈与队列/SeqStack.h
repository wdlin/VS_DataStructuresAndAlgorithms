/*
顺序栈
*/
#ifndef _SEQ_STACK_H_
#define _SEQ_STACK_H_
#include <iostream>
using namespace std;

template<class T>
class SeqStack
{
public:
	SeqStack(unsigned int maxSize = 10);//栈最大值
	~SeqStack();//析构函数
	bool isEmpty() const;//是否为空
	bool isFull() const;//是否满了
	int size() const;//目前占大小
	T top()const;//返回栈顶元素，不删除
	bool push(const T& t);//入栈
	void pop();//出栈，不返回元素
	friend ostream& operator<<<>(ostream& out, const SeqStack<T>& s);//输出栈的友员函数
private:
	int nowTop;//目前栈顶
	int maxTop;//栈的最大值
	T* stack;//存储元素的动态数组

};

template<class T>
SeqStack<T>::SeqStack(unsigned int maxSize)
{
	stack = new T[maxSize];//如果new失败，抛出异常，malloc则是返回NULL
	maxTop = maxSize - 1;
	nowTop = -1;
}

template<class T>
SeqStack<T>::~SeqStack()
{
	delete[] stack;//删除指针
}

template<class T>
bool SeqStack<T>::isEmpty() const
{
	if (nowTop == -1)return true;
	else return false;
}

template<class T>
bool SeqStack<T>::isFull() const
{
	if (nowTop == maxTop)
		return true;
	else 
		return false;
}

template<class T>
int SeqStack<T>::size()const
{
	return nowTop + 1;
}

template<class T>
T SeqStack<T>::top()const
{
	if (!isEmpty())
		return stack[nowTop];
}

template<class T>
bool SeqStack<T>::push(const T& t)//用引用，避免了一次不必要的拷贝操作
{
	if (isFull())
		return false;
	stack[++nowTop] = t;//还是要复制一次
	return true;
}

template<class T>
void SeqStack<T>::pop()
{
	if (!isEmpty())
	{
		T t;
		stack[nowTop] = t;//重置原来的元素，这样也许可以将智能指针引用减一。
		nowTop--;
	}
}

template<class T>
ostream& operator<<(ostream& out, const SeqStack<T>& s)//
{
	for (int i = s.nowTop; i > -1; i--)
		out << s.stack[i] << endl;
	return out;
}



#endif