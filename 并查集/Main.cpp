#include <iostream>
#include<vector>
#include <string>
#include <ctime>
#include "DisjointSet.h"
using namespace std;

struct Wall
{
	//墙左右+1-1，上下+length -length
	int a;
	int b;
	Wall(int aa, int bb) :a(aa), b(bb){}
	bool operator==(const Wall& rhs)
	{
		if ((a == rhs.a&&b == rhs.b) || (a == rhs.b&&b == rhs.a))
			return true;
		else
			return false;
	}
};

void testDisjointSet(unsigned int length,unsigned int width)
{
	assert(length > 1 && width > 1);
	//生成一个迷宫
	int sum = length*width;//总共的方格数
	DisjointSet ds(sum);
	int setsCount = sum;//集合数计数
	int num;//用于存放一个方格
	int direction;//存放方向
	int other;//另一个方格
	vector<Wall> walls;//存放要消除的墙
	walls.reserve(sum * 4);
	while (true)
	{
		num = rand() % sum;//随机一个方格
		direction = rand() % 4;//随机一个方向
		switch (direction)//计算另一个方格
		{
		case 0://上
			other = num - length;
			break;
		case 1://右
			other = num + 1;
			break;
		case 2://下
			other = num + length;
			break;
		case 3://左
			other = num - 1;
			break;
		default:
			break;
		}
		//检测墙的有效性
		if (other < 0 || other >= sum)
			continue;
		if ((num%length) == (length - 1))//右边缘
		{
			if (other == num + 1)
				continue;
		}
		if ((num%length) == 0)//左边缘
		{
			if (other == num - 1)
				continue;
		}

		Wall wall(num,other);
		bool flag = true;//检测是否已经删除
		for (int i = 0; i < walls.size(); i++)
		{
			if (walls[i] == wall)
			{
				flag = false;
				break;
			}
		}
		if (!flag)
			continue;
		else
		{
			int root1 = ds.find(num);
			int root2 = ds.find(other);
			if (root1 == root2)//检测是否已经在一个集合中
				continue;
			else//不在一个集合中，删除这个墙
			{
				ds.unionSets(root1, root2);
				setsCount--;//减少集合数
				walls.push_back(wall);
				if (setsCount == 1)//如果集合数变成1，结束删除循环
					break;
			}				
		}
		
	}
	
	ds.print();

    //打印一个迷宫
	walls.push_back(Wall(-1, 0));//开始
	walls.push_back(Wall(sum - 1, sum));//结束
	int widthCount = 0;
	int lengthCount = 0;
	string up = "****";
	string right = "|";
	string down = "****";
	string left = "|  ";
	for (widthCount = 0; widthCount < width; widthCount++)
	{
		for (int i = 0; i < length; i++)//打印上
		{
			num = widthCount*length + i;
			other = num - length;
			Wall wall(num, other);
			bool flag = true;
			for (int i = 0; i < walls.size(); i++)
			{
				if (walls[i] == wall)
				{
					flag = false;
					break;
				}
			}
			if (flag)
				cout << up;
			else
				cout << "    ";
		}
		cout<<endl;
		for (int i = 0; i < length; i++)//打印左右
		{
			num = widthCount*length + i;
			other = num - 1;
			Wall wall1(num, other);
			bool flag = true;
			for (int i = 0; i < walls.size(); i++)
			{
				if (walls[i] == wall1)
				{
					flag = false;
					break;
				}
			}
			if (flag)
				cout << left;
			else
				cout << "   ";

			other = num + 1;
			Wall wall2(num, other);
			flag = true;
			for (int i = 0; i < walls.size(); i++)
			{
				if (walls[i] == wall2)
				{
					flag = false;
					break;
				}
			}
			if (flag)
				cout << right;
			else
				cout << " ";
		}
		cout << endl;
		for (int i = 0; i < length; i++)//打印下
		{
			num = widthCount*length + i;
			other = num + length;
			Wall wall(num, other);
			bool flag = true;
			for (int i = 0; i < walls.size(); i++)
			{
				if (walls[i] == wall)
				{
					flag = false;
					break;
				}
			}
			if (flag)
				cout << down;
			else
				cout << "    ";
		}
		cout << endl;

	}

}

int main()
{
	srand(time(NULL));
	testDisjointSet(12,12);
	system("pause");
	return 0;
}



/*
  0
 ****
3|  |1
 ****
   2 

*/
