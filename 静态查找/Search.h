#ifndef _SEARCH_H_
#define _SEARCH_H_

int sequential_search(int* array,int size, int key);
int sequential_search2(int* array, int size, int key);

int binary_search(int* array, int size, int key);
int binary_search_recursion(int* array, int left,int right, int key);

int insert_search(int* array, int size, int key);

int fibonacci_search(int* array, int size, int key);


#endif