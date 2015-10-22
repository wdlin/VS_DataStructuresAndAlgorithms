#include <iostream>
#include "MatchMethods.h"
using namespace std;

int main()
{
	char *text = "ababxbababcadfdsss";
	char *find = "abab";
	//int pos = simple_match(text,find);
	int pos = KMP(text, find);
	if (pos == -1)
		cout << "not find" << endl;
	else
		cout << pos << " : " << (char*)(text+pos) << endl;
	system("pause");
	return 0;
}