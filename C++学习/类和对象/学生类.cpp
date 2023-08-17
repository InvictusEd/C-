#include <iostream>
#include<string>
using namespace std;

class Student
{
public:	//访问权限为公共
	//类中的属性和行为统一称为 成员
	// 属性 成员属性 成员变量
	// 行为 成员函数 成员方法
	//属性
	string number;	//学号
	string name;		//姓名
	
	//行为
	//输入学生信息
	void Input_info()
	{
		cout << "学号：";
		cin >> number;
		cout << "姓名：";
		cin >> name;
	}
	
	//显示学生信息
	void Print_s()
	{
		cout << "学号：" << number << endl;
		cout << "姓名：" << name << endl;
	}
};

int main()
{
	Student s1;
	s1.Input_info();
	s1.Print_s();

	system("pause");

	return 0;
}