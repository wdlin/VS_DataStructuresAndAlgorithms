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
	bool isEmpty()const;//�ж��Ƿ�Ϊ��
	int size()const;//���ض���Ԫ�ظ���
	T front()const;//���ض�ͷԪ�أ���ɾ��
	T back()const;//���ض�βԪ�أ���ɾ��
	void push(const T& t);//���Ԫ�ص�����
	void pop();//ɾ������Ԫ��
private:
	int nowSize;//Ŀǰ��С
	ListQueueNode<T>* pFront;//��ͷָ��
	ListQueueNode<T>* pRear;//��βָ��
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