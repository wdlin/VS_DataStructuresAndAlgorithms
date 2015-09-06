#include <iostream>
#include "ChainHashTable.h"
#include "LinearProbeHashTable.h"
#include "QuadraticProbeHashTable.h"
#include "DoubleHashingHashTable.h"
#include <string>
using namespace std;

class Person:public Hashable
{
public:
	Person() :_name(""),_age(0){}
	Person(string name) :_name(name), _age(0){}
	Person(string name,int age) :_name(name), _age(age){}
	string getName()const{ return _name; }
	int getAge()const{ return _age; }
	bool operator==(const Person& rhs) const
	{
		return _name == rhs.getName();
	}
	bool operator!=(const Person& rhs) const
	{
		return !(_name == rhs.getName());
	}
	friend ostream& operator<<(ostream& os, const Person& rhs)
	{
		os << "name:" << rhs.getName() << ",age:" << rhs.getAge();
		return os;
	}
	virtual int hashCode()const
	{
		int hashcode = 0;
		for (int i = 0; i < _name.length(); i++)
		{
			hashcode = 37 * hashcode + _name[i];
			//hashcode += _name[i];
		}
		return hashcode;
	}
private:
	string _name;
	int _age;
};

void testChainHashTable()
{
	ChainHashTable<Person> chainHashTable(3);
	chainHashTable.insert(Person("Bob", 10)); 
	chainHashTable.insert(Person("Alice", 10));
	chainHashTable.insert(Person("wdlin", 10));
	chainHashTable.insert(Person("lin", 10));
	chainHashTable.print();

	cout << "******" << endl;
	chainHashTable.remove(Person("Bob"));
	chainHashTable.print();

	cout << "******" << endl;
	chainHashTable.makeEmpty();
	chainHashTable.print();
}

void testLinearProbeHashTable()
{
	LinearProbeHashTable<Person> linearhashTable(11, 0.5);
	linearhashTable.insert(Person("Bob", 10));
	linearhashTable.insert(Person("wlind", 10));
	linearhashTable.insert(Person("wdlin", 10));
	linearhashTable.insert(Person("dlinw", 10));
	linearhashTable.print();

	cout << "******" << endl;
	linearhashTable.remove(Person("Bob"));
	linearhashTable.print();
	cout << "******" << endl;
	linearhashTable.insert(Person("Bob", 10));
	linearhashTable.print();

	cout << "******" << endl;
	for (int i = 0; i < 100; i++)
	{
		linearhashTable.insert(Person("Alice", 10));
		linearhashTable.remove(Person("Alice", 10));
	}
	linearhashTable.print();
	cout << "******" << endl;
	linearhashTable.slim();
	linearhashTable.print();
}

void testQuadraticProbeHashTable()
{
	QuadraticProbeHashTable<Person> quadraticProbeHashTable(0,0.5);
	quadraticProbeHashTable.insert(Person("Bob", 10));
	quadraticProbeHashTable.insert(Person("wlind", 10));
	quadraticProbeHashTable.insert(Person("wdlin", 10));
	quadraticProbeHashTable.insert(Person("dlinw", 10));
	quadraticProbeHashTable.print();

	cout << "******" << endl;
	quadraticProbeHashTable.remove(Person("Bob"));
	quadraticProbeHashTable.print();
	cout << "******" << endl;
	quadraticProbeHashTable.insert(Person("Bob", 10));
	quadraticProbeHashTable.print();

	cout << "******" << endl;
	for (int i = 0; i < 100; i++)
	{
		quadraticProbeHashTable.insert(Person("Alice", 10));
		quadraticProbeHashTable.remove(Person("Alice", 10));
	}
	quadraticProbeHashTable.print();
	cout << "******" << endl;
	quadraticProbeHashTable.slim();
	quadraticProbeHashTable.print();
}

void testDoubleHashingHashTable()
{
	DoubleHashingHashTable<Person> doubleHashingHashTable(0, 0.5);
	doubleHashingHashTable.insert(Person("Bob", 10));
	doubleHashingHashTable.insert(Person("wlind", 10));
	doubleHashingHashTable.insert(Person("wdlin", 10));
	doubleHashingHashTable.insert(Person("dlinw", 10));
	doubleHashingHashTable.print();

	cout << "******" << endl;
	doubleHashingHashTable.remove(Person("Bob"));
	doubleHashingHashTable.print();
	cout << "******" << endl;
	doubleHashingHashTable.insert(Person("Bob", 10));
	doubleHashingHashTable.print();

	cout << "******" << endl;
	for (int i = 0; i < 100; i++)
	{
		doubleHashingHashTable.insert(Person("Alice", 10));
		doubleHashingHashTable.remove(Person("Alice", 10));
	}
	doubleHashingHashTable.print();
	cout << "******" << endl;
	doubleHashingHashTable.slim();
	doubleHashingHashTable.print();
}

int main()
{
	//testChainHashTable();
	//testLinearProbeHashTable();
	//testQuadraticProbeHashTable();
	testDoubleHashingHashTable();
	system("pause"); 
	return 0;
}