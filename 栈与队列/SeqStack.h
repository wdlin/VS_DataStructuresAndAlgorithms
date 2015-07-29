/*
˳��ջ
*/
#ifndef _SEQ_STACK_H_
#define _SEQ_STACK_H_
#include <iostream>
using namespace std;

template<class T>
class SeqStack
{
public:
	SeqStack(unsigned int maxSize = 10);//ջ���ֵ
	~SeqStack();//��������
	bool isEmpty() const;//�Ƿ�Ϊ��
	bool isFull() const;//�Ƿ�����
	int size() const;//Ŀǰռ��С
	T top()const;//����ջ��Ԫ�أ���ɾ��
	bool push(const T& t);//��ջ
	void pop();//��ջ��������Ԫ��
	friend ostream& operator<<<>(ostream& out, const SeqStack<T>& s);//���ջ����Ա����
private:
	int nowTop;//Ŀǰջ��
	int maxTop;//ջ�����ֵ
	T* stack;//�洢Ԫ�صĶ�̬����

};

template<class T>
SeqStack<T>::SeqStack(unsigned int maxSize)
{
	stack = new T[maxSize];//���newʧ�ܣ��׳��쳣��malloc���Ƿ���NULL
	maxTop = maxSize - 1;
	nowTop = -1;
}

template<class T>
SeqStack<T>::~SeqStack()
{
	delete[] stack;//ɾ��ָ��
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
bool SeqStack<T>::push(const T& t)//�����ã�������һ�β���Ҫ�Ŀ�������
{
	if (isFull())
		return false;
	stack[++nowTop] = t;//����Ҫ����һ��
	return true;
}

template<class T>
void SeqStack<T>::pop()
{
	if (!isEmpty())
	{
		T t;
		stack[nowTop] = t;//����ԭ����Ԫ�أ�����Ҳ����Խ�����ָ�����ü�һ��
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