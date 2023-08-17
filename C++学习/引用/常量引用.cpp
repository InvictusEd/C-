#include <iostream>
using namespace std;

void showValue(const int& v)
{
	//v += 10; 不可以修改
	cout << v << endl;
}

int main()
{
	//常量引用
	//使用场景，用来修饰形参，防止误操作
	const int& ref = 10;
	//加入const后不可以修改变量
	cout << ref << endl;

	//函数中利用常量引用防止误操作修改实参
	int a = 10;
	showValue(a);
	

	system("pause");

	return 0;
}