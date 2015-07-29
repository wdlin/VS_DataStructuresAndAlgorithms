#include <iostream>
#include <ctime>
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "ExchangeSort.h"
#include "MergeSort.h"
#include "RadixSort.h"

using namespace std;

template<typename T>
void print(T* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << array[i] << ",";
	}
	cout << endl;
}

void main()
{
	srand(time(NULL));
	int size = rand() % 100; //size = 10;
	int * array = new int[size];
	for (int i = 0; i < size; i++)
	{
		array[i] = rand() % 1000;
	}
	print(array, size);
	//insertSort(array, size);
	//binaryInsertSort(array,size);
	//shellSort(array, size);
	//selectionSort2(array,size);
	//heapSort(array,size);
	//bubbleSort(array,size);
	//quickSort(array, 0, size - 1);
	//quickSort2(array, 0, size - 1);
	//nonRecursionQuickSort(array,size);
	//int *tempArr = new int[size];
	//mergeSort(array, tempArr, 0, size - 1);
	radixSort(array,size);
	print(array, size);
	delete[] array;
	system("pause");
}

