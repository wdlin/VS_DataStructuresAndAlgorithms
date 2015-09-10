#include <iostream>
#include <ctime>
#include "BinaryHeap.h"
#include "DHeap.h"
#include "LeftistHeap.h"
#include "BinomialHeap.h"
using namespace std;

void testBinaryHeap()
{
	BinaryHeap<int> bh1;
	int count = rand() % 15;
	for (int i = 0; i < count; i++)
	{
		int n = rand() % 100;
		bh1.insert(n);
	}
	cout << "Min: " << bh1.getMin() << endl;
	bh1.print();
	bh1.deleteMin();
	bh1.print();
	bh1.makeEmpty();
	bh1.print();
	cout << "*************" << endl;
	vector<int> vec{10,12,5,19,7,28,23,15,12,36,7,3};
	BinaryHeap<int> bh2(vec);
	bh2.print();
	bh2.insert(8);
	bh2.print();
}

void testDHeap()
{
	DHeap<int, 3> dh1;
	int count = rand() % 100;
	for (int i = 0; i < count; i++)
	{
		int n = rand() % 100;
		dh1.insert(n);
	}
	cout << "Min: " << dh1.getMin() << endl;
	dh1.print();
	dh1.deleteMin();
	dh1.print();
	dh1.makeEmpty();
	dh1.print();
	cout << "*************" << endl;
	vector<int> vec{ 10, 12, 5, 19, 7, 28, 23, 15, 12, 36, 7, 3 };
	DHeap<int, 3> dh2(vec);
	dh2.print();
	dh2.insert(8);
	dh2.print();
}

void testLeftistHeap()
{
	LeftistHeap<int> lh1;
	int count = rand() % 17;
	for (int i = 0; i < count; i++)
	{
		int n = rand() % 100;
		lh1.insert(n);
	}
	cout << "Min: " << lh1.getMin() << endl;
	lh1.print(4);
	lh1.deleteMin();
	lh1.print(4);

	cout << "*************" << endl;
	LeftistHeap<int> lh2(lh1);
	lh2.print(4);
	lh2.insert(8);
	lh2.print(4);

}

void testBinomialHeap()
{
	BinomialHeap<int> bh1;
	int count = rand() % 10;
	for (int i = 0; i < count; i++)
	{
		int n = rand() % 100;
		bh1.insert(n);
	}
	BinomialHeap<int> bh2(4,1);
	bh2.insert(15);
	bh2.insert(17);

	cout << bh1.getMin() << endl;
	cout << bh2.getMin() << endl;
	bh1.merge(bh2);
	cout << bh1.getMin() << endl;
	bh1.deleteMin();
	cout << bh1.getMin() << endl;
}
int main()
{
	srand(time(NULL));
	try{
		//testBinaryHeap();
		//testDHeap();
		//testLeftistHeap();
		testBinomialHeap();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

	system("pause");
	return 0;
}

/*
testBinaryHeap()

Min: 17
Height: 4
              17
      27              48
  81      71      69      81
98  93  96
Height: 4
              27
      71              48
  81      96      69      81
98  93
print: Heap is empty!
*************
Height: 4
               3
       7              5
  12      7      10      23
15  19  36  12  28
Height: 4
            3
    7              5
12      7      8      23
15  19  36  12  28  10

***************************************
testDHeap();

Min: 11
Height: 3
11 ,
33 , 15 , 31 ,
91 , 75 , 65 , 23 , 16 , 47 ,
Height: 3
15 ,
33 , 16 , 31 ,
91 , 75 , 65 , 23 , 47 ,
print: Heap is empty!
*************
Height: 3
3 ,
7 , 5 , 7 ,
12 , 28 , 23 , 15 , 12 , 36 , 10 , 19 ,
Height: 3
3 ,
7 , 5 , 7 ,
12 , 28 , 23 , 15 , 12 , 36 , 10 , 19 , 8 ,

*****************************************
testLeftistHeap
Min: 3
Heap:
3(1),
16(1),37(0),
96(0),42(0),40(0),NL(-1),
NL(-1),NL(-1),NL(-1),NL(-1),71(0),NL(-1),NL(-1),NL(-1),
Heap:
16(1),
37(1),96(0),
40(0),42(0),NL(-1),NL(-1),
71(0),NL(-1),NL(-1),NL(-1),NL(-1),NL(-1),NL(-1),NL(-1),
*************
Heap:
16(1),
37(1),96(0),
40(0),42(0),NL(-1),NL(-1),
71(0),NL(-1),NL(-1),NL(-1),NL(-1),NL(-1),NL(-1),NL(-1),
Heap:
8(0),
16(1),NL(-1),
37(1),96(0),NL(-1),NL(-1),
40(0),42(0),NL(-1),NL(-1),NL(-1),NL(-1),NL(-1),NL(-1),

******************************************
testBinomialHeap
(不太好输出，所以建议用断点查看内容)
0
4
0
3
请按任意键继续. . .

*/