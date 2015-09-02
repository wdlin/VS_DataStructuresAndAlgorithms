#include <iostream>
#include <ctime>
#include "BinaryHeap.h"
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
int main()
{
	srand(time(NULL));
	try{
		testBinaryHeap();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

	system("pause");
	return 0;
}

/*
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
*/