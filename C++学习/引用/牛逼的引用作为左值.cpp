#include <iostream>
using namespace std;

//引用做函数的返回值
//1、不要返回局部变量的引用

int& test01()
{
	int a = 10;
	return a;
}

int& test02()
{
	static int a = 10;//静态变量，存放在全局区，全局区上的数据在程序结束后系统释放
	return a;
}

int main()
{	//不能返回局部变量的引用
	//int& ref = test01();
	//cout << "ref = " << ref << endl;

	int& ref2 = test02();
	cout << ref2 << endl;
	cout << ref2 << endl;

	test02() = 1000;//如果函数的返回值是引用，这个函数调用可以作为左值
	cout << ref2 << endl;
	cout << ref2 << endl;

	system("pause");
	return 0;
}

//引用的本质就是指针常量