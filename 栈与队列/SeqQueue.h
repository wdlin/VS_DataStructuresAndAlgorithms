/*
利用循环数组构建队列
*/
#ifndef _SEQ_QUEUE_H_
#define _SEQ_QUEUE_H_

template<class T>
class SeqQueue
{
public:
	SeqQueue(int max = 10);//指定队列大小
	~SeqQueue();//析构
	bool isEmpty()const;//判断是否为空
	bool isFull()const;//判断是否队列已满
	int size()const;//返回队列元素个数
	T front()const;//返回队头元素，不删除
	T back()const;//返回队尾元素，不删除
	bool push(const T& t);//添加元素到队列
	void pop();//删除队首元素

private:
	int maxSize;//记录队列最大数目
	int nowFront;//nowfront + 1就是目前的队头
	int nowRear;//队尾
	int nowSize;//目前大小
	T * array;//队列动态数组
};

#endif

template<class T>
SeqQueue<T>::SeqQueue(int max = 10) :maxSize(max), nowFront(-1), nowRear(-1), nowSize(0)
{
	array = new T[max];
}

template<class T>
SeqQueue<T>::~SeqQueue()
{
	delete[] array;
}

template<class T>
bool SeqQueue<T>::isEmpty()const
{
	if (nowSize == 0)
		return true;
	else
		return false;
}

template<class T>
bool SeqQueue<T>::isFull()const
{
	if (nowSize == maxSize)
		return true;
	else
		return false;
}

template<class T>
int SeqQueue<T>::size()const
{
	return nowSize;
}


template<class T>
T SeqQueue<T>::front()const
{
	if (!isEmpty())
	{
		return array[nowFront + 1];
	}	
}

template<class T>
T SeqQueue<T>::back()const
{
	if (!isEmpty())
	return array[nowRear];
}

template<class T>
bool SeqQueue<T>::push(const T& t)
{
	if (isFull())
		return false;
	else
	{
		nowSize++;
		nowRear = (++nowRear) % maxSize;//++一定要在前面
		array[nowRear] = t;
		return true;
	}
}

template<class T>
void SeqQueue<T>::pop()
{
	if (isEmpty())
		return;
	else
	{
		nowFront = (++nowFront) % maxSize;
		nowSize--;
		T t;
		array[nowFront] = t;//重置原来的元素，这样也许可以将智能指针引用减一。
		return;
	}
}