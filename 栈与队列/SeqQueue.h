/*
����ѭ�����鹹������
*/
#ifndef _SEQ_QUEUE_H_
#define _SEQ_QUEUE_H_

template<class T>
class SeqQueue
{
public:
	SeqQueue(int max = 10);//ָ�����д�С
	~SeqQueue();//����
	bool isEmpty()const;//�ж��Ƿ�Ϊ��
	bool isFull()const;//�ж��Ƿ��������
	int size()const;//���ض���Ԫ�ظ���
	T front()const;//���ض�ͷԪ�أ���ɾ��
	T back()const;//���ض�βԪ�أ���ɾ��
	bool push(const T& t);//���Ԫ�ص�����
	void pop();//ɾ������Ԫ��

private:
	int maxSize;//��¼���������Ŀ
	int nowFront;//nowfront + 1����Ŀǰ�Ķ�ͷ
	int nowRear;//��β
	int nowSize;//Ŀǰ��С
	T * array;//���ж�̬����
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
		nowRear = (++nowRear) % maxSize;//++һ��Ҫ��ǰ��
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
		array[nowFront] = t;//����ԭ����Ԫ�أ�����Ҳ����Խ�����ָ�����ü�һ��
		return;
	}
}