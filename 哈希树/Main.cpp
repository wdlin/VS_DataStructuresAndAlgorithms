#include <iostream>
#include <string>
#include "HashTree.h"
using namespace std;


int main()
{
	HashTree<int,string> htree;
	htree.insertNode(2,"lin");
	htree.insertNode(7, "wei");
	htree.insertNode(4, "dong");

	cout << htree.removeNode(2, "lin") << endl;
	cout << htree.findNode(7, "wei") << endl;
	cout << htree.findNode(4, "dong") << endl;
	cout << htree.findNode(5, "ii") << endl;
	
	system("pause");
	return 0;
}