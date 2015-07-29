/*
¡¥±Ì’ª
*/
#ifndef _LIST_STACK_H_
#define _LIST_STACK_H_

template<class T>class ListStack;
template<class T>
class ListStackNode
{
	friend ListStack<T>;
private:
	T data;
	ListStackNode<T> * link;
};


template<class T>
class ListStack
{
public:
	ListStack();
	~ListStack();
	bool isEmpty()const;
	int size()const;
	T top()const;
	void pop();
	bool push(const T& t);

private:
	ListStackNode<T> *nowTop;
	int nowSize;
};

template<class T>
ListStack<T>::ListStack() :nowTop(nullptr), nowSize(0)
{
}

template<class T>
ListStack<T>::~ListStack()
{
	ListStackNode<T>* next;
	while (nowTop != nullptr)
	{
		next = nowTop->link;
		delete nowTop;
		nowTop = next;
	}
}

template<class T>
bool ListStack<T>::isEmpty()const
{
	if (nowSize == 0)
		return true;
	else
		return false;
}

template<class T>
int ListStack<T>::size()const
{
	return nowSize;
}

template<class T>
T ListStack<T>::top()const
{
	if (!isEmpty())
	{
		return nowTop->data;
	}
}


template<class T>
void ListStack<T>::pop()
{
	ListStackNode<T>* next = nowTop->link;
	delete nowTop;
	nowTop = next;
	nowSize--;
}

template<class T>
bool ListStack<T>::push(const T& t)
{
	ListStackNode<T> *p = new ListStackNode<T>;
	p->data = t;
	p->link = nowTop;
	nowTop = p;
	nowSize++;
	return true;
}


#endif