#include <iostream>
using namespace std;
#include <string>

struct Hero
{
	string name;
	int age;
	string gender;
};

void bubbleSort(Hero heroArray[], int len)
{
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - i - 1; j++) {
			if (heroArray[j].age > heroArray[j + 1].age) {
				struct Hero temp = heroArray[j];
				heroArray[j] = heroArray[j + 1];
				heroArray[j + 1] = temp;
			}
		}
	}
}

void printHero(Hero heroArray[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << "姓名：" << heroArray[i].name << " 年龄：" << heroArray[i].age
			<< " 性别：" << heroArray[i].gender << endl;
	}
}

int main()
{
	Hero heroArray[5] = { 
		{"刘备",23,"男"},
		{"关羽",22,"男"},
		{"张飞",20,"男"},
		{"赵云",21,"男"},
		{"貂蝉",19,"女"},
	};
	int len = sizeof(heroArray) / sizeof(heroArray[0]);
	cout << "排序前打印： " << endl;
	for (int i = 0; i < len; i++)
	{
		cout << "姓名：" << heroArray[i].name << " 年龄：" << heroArray[i].age
			<< " 性别：" << heroArray[i].gender << endl;
	}
	bubbleSort(heroArray, len);
	cout << "排序后打印： " << endl;
	printHero(heroArray, len);

	system("pause");

	return 0;
}