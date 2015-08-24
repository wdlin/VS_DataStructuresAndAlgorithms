#ifndef _LIST_QUEUE_H_
#define _LIST_QUEUE_H_

template<class T> class ListQueue;

template<class T>
class ListQueueNode
{
	friend class ListQueue<T>;
private:
	T data;
	ListQueueNode<T>* next;
};

template<class T>
class ListQueue
{
public:
	ListQueue();
	~ListQueue();
	bool isEmpty()const;//判断是否为空
	int size()const;//返回队列元素个数
	T front()const;//返回队头元素，不删除
	T back()const;//返回队尾元素，不删除
	void push(const T& t);//添加元素到队列
	void pop();//删除队首元素
private:
	int nowSize;//目前大小
	ListQueueNode<T>* pFront;//队头指针
	ListQueueNode<T>* pRear;//队尾指针
};


template<class T>
ListQueue<T>::ListQueue() :nowSize(0), pFront(nullptr), pRear(nullptr)
{
}

template<class T>
ListQueue<T>::~ListQueue()
{
	ListQueueNode<T>* next;
	while (pFront!= nullptr)
	{
		next = pFront->next;
		delete pFront;
		pFront = next;
	}
}

template<class T>
bool ListQueue<T>::isEmpty()const
{
	if (nowSize == 0)
		return true;
	else
		return false;
}

template<class T>
int ListQueue<T>::size()const
{
	return nowSize;
}

template<class T>
T ListQueue<T>::front()const
{
	return pFront->data;
}

template<class T>
T ListQueue<T>::back()const
{
	return pRear->data;
}

template<class T>
void ListQueue<T>::push(const T& t)
{
	if (isEmpty())
	{
		pFront = new ListQueueNode<T>;
		pFront->data = t;
		pFront->next = nullptr;
		pRear = pFront;
	}
	else
	{
		pRear->next = new ListQueueNode<T>;
		pRear = pRear->next;
		pRear->data = t;
		pRear->next = nullptr;
	}
	nowSize++;
}

template<class T>
void ListQueue<T>::pop()
{
	if (isEmpty())
		return;
	ListQueueNode<T>* next = pFront->next;
	delete pFront;
	pFront = next;
	nowSize--;
}
#endif