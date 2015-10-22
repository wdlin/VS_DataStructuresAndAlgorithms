#include "MatchMethods.h"
#include <cstring>
#include <iostream>
using namespace std;

//O(m+n)
//严蔚敏 数据结构 p82-84
//简单的next函数
void build_next(const char* find,int* next)
{
	int i = 0;
	next[0] = -1;
	int j = -1;
	while (find[i] != '\0')
	{
		if (j == -1 || find[i] == find[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else
			j = next[j];
	}

	for (int h = 0; h < strlen(find); h++)
		cout <<h<<" : "<< next[h] << endl;
}

//优化的next函数
void build_nextval(const char* find, int* next)
{
	int i = 0;
	next[0] = -1;
	int j = -1;
	while (find[i] != '\0')
	{
		if (j == -1 || find[i] == find[j])
		{
			i++;
			j++;
			if (find[i] == find[j]) next[i] = j;
			else
				next[i] = next[j];
		}
		else
			j = next[j];
	}

	for (int h = 0; h < strlen(find); h++)
		cout << h << " : " << next[h] << endl;
}

int KMP(const char*text, const char * find)
{
	int find_len = strlen(find);
	int text_len = strlen(text);
	if (find_len > text_len)
		return -1;
	if (find_len == 0)
		return -1;

	int *next = new int[find_len];
	build_next(find, next);

	int i = 0, j = 0;
	while (i < text_len && j < find_len)
	{
		if (j == -1 || text[i] == find[j])
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if (j == find_len)
		return i - j;
	else
		return -1;
}
