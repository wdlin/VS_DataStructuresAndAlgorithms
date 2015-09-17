#include <iostream>
#include <ctime>
using namespace std;
typedef struct ListNode
{
	int data;
	ListNode* next;
}ListNode;

//循环解法
ListNode* reverse(ListNode* head)
{
	if (head == NULL || head->next == NULL)
		return head;
	ListNode* newHead;
	ListNode* temp;
	ListNode* tempNext;
	
	newHead = head;
	temp = head->next;
	head->next = NULL;
	while (temp != NULL)
	{
		tempNext = temp->next;
		temp->next = newHead;
		newHead = temp;
		temp = tempNext;
	}
	return newHead;
}

//递归解法
ListNode* reverse_recursion(ListNode* head)
{
	if (head == NULL || head->next == NULL)
		return head;
	else
	{
		ListNode* newHead = reverse_recursion(head->next);
		head->next->next = head;
		head->next = NULL;
		return newHead;
	}
}
void print(ListNode* head)
{
	ListNode* temp = head;
	while (temp != NULL)
	{
		cout << temp->data << ",";
		temp = temp->next;
	}
	cout << endl;
}
void main()
{
	srand(time(NULL));
	int size = rand() % 100; //size = 10;
	//构建链表
	ListNode* head = new ListNode;
	head->data = 1;
	ListNode* temp = head;
	for (int i = 0; i < size; i++)
	{	
		temp->next = new ListNode;
		temp = temp->next;
		temp->data = rand() % 1000;		
	}
	temp->next = NULL;

	print(head);
	//ListNode * newHead = reverse(head);
	ListNode * newHead = reverse_recursion(head);
	print(newHead);
	
	//清除指针
	temp = newHead;
	while (temp != NULL)
	{
		newHead = newHead->next;
		delete temp;
		temp = newHead;
	}
	system("pause");
}




