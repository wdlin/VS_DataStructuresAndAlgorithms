#include <iostream>
#include "Search.h"

using namespace std;

int main()
{
	int a[] = {1,2,3,4,5,6,7,8,9,10};
	int pos;
	//pos = sequential_search(a, 10, 8);
	//pos = binary_search(a, 10, 11);
	//pos = binary_search_recursion(a, 0,9, 8);
	//pos = insert_search(a, 10, 8);
	pos = fibonacci_search(a, 7, 66);
	cout << pos << endl;
	system("pause");
	return 0;
}