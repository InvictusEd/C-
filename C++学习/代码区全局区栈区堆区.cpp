#include <iostream>
using namespace std;

int* func()
{
	int* p = new int(10);
	return p;
}

//new的基本语法
void test01()
{
	//在对去创建一个整型数据
	//new返回的是该数据类型的指针
	int* p = func();
	cout << *p << endl;
	delete p;
}

//在堆区利用new开辟数组
void test02()
{
	int* arr = new int[10];//10代表数组有10个元素

	for (int i = 0; i < 10; i++)
	{
		arr[i] = i + 100;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}
	//释放堆区数组
	delete[] arr;
}

int main()
{
	test01();
	test02();
	system("pause");
	
	return 0;
}