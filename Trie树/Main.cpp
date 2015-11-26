#include <iostream>
#include "Trie.h"
using namespace std;


int main()
{
	Trie trie;
	trie.insert("wdlin");
	trie.insert("lin");
	trie.insert("lin");
	cout << trie.search("wd") << endl;
	cout << trie.search("lin") << endl;

	system("pause");
	return 0;
}