#include <iostream>
using namespace std;
#include <string.h>
#include <ctime>

struct Student {
	string sName;
	int score;
};

struct Teacher {
	string tName;
	Student sArray[5];
};

void allocateSpace(Teacher tArray[], int len)
{
	string nameSeed = "ABCDE";
	for (int i = 0; i < len; i++)
	{
		tArray[i].tName = "Teacher_";
		tArray[i].tName += nameSeed[i];

		for (int j = 0; j < 5; j++)
		{
			tArray[i].sArray[j].sName = "Stydent_";
			tArray[i].sArray[j].sName += nameSeed[j];
			int random = rand() % 61 + 40;
			tArray[i].sArray[j].score = random;
		}
	}
}

void printInfo(Teacher tArray[], int len)
{

	for (int i = 0; i < len; i++)
	{
		cout << "老师姓名：" << tArray[i].tName << endl;
		for (int j = 0; j < 5; j++)
		{
			cout << "\t学生姓名：" << tArray[i].sArray[j].sName <<
				"考试分数：" << tArray[i].sArray[j].score << endl;
		}
	}
}

int main()
{
	srand((unsigned int)time(NULL));

	Teacher tArray[3];
	
	int len = sizeof(tArray) / sizeof(tArray[0]);
	allocateSpace(tArray, len);

	printInfo(tArray, len);

	system("pause");
	
	return 0;
}