#include <iostream>
#include<vector>
#include <string>
#include <ctime>
#include "DisjointSet.h"
using namespace std;

struct Wall
{
	//ǽ����+1-1������+length -length
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
	//����һ���Թ�
	int sum = length*width;//�ܹ��ķ�����
	DisjointSet ds(sum);
	int setsCount = sum;//����������
	int num;//���ڴ��һ������
	int direction;//��ŷ���
	int other;//��һ������
	vector<Wall> walls;//���Ҫ������ǽ
	walls.reserve(sum * 4);
	while (true)
	{
		num = rand() % sum;//���һ������
		direction = rand() % 4;//���һ������
		switch (direction)//������һ������
		{
		case 0://��
			other = num - length;
			break;
		case 1://��
			other = num + 1;
			break;
		case 2://��
			other = num + length;
			break;
		case 3://��
			other = num - 1;
			break;
		default:
			break;
		}
		//���ǽ����Ч��
		if (other < 0 || other >= sum)
			continue;
		if ((num%length) == (length - 1))//�ұ�Ե
		{
			if (other == num + 1)
				continue;
		}
		if ((num%length) == 0)//���Ե
		{
			if (other == num - 1)
				continue;
		}

		Wall wall(num,other);
		bool flag = true;//����Ƿ��Ѿ�ɾ��
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
			if (root1 == root2)//����Ƿ��Ѿ���һ��������
				continue;
			else//����һ�������У�ɾ�����ǽ
			{
				ds.unionSets(root1, root2);
				setsCount--;//���ټ�����
				walls.push_back(wall);
				if (setsCount == 1)//������������1������ɾ��ѭ��
					break;
			}				
		}
		
	}
	
	ds.print();

    //��ӡһ���Թ�
	walls.push_back(Wall(-1, 0));//��ʼ
	walls.push_back(Wall(sum - 1, sum));//����
	int widthCount = 0;
	int lengthCount = 0;
	string up = "****";
	string right = "|";
	string down = "****";
	string left = "|  ";
	for (widthCount = 0; widthCount < width; widthCount++)
	{
		for (int i = 0; i < length; i++)//��ӡ��
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
		for (int i = 0; i < length; i++)//��ӡ����
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
		for (int i = 0; i < length; i++)//��ӡ��
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
