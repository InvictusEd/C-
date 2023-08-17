#include <iostream>
#include<string>
using namespace std;

//访问权限
//三种
//公共权限 public		成员 类内可以访问 类外可以访问
//保护权限 protected		成员 类内可以访问 类外不可以访问 儿子可以访问父亲中的保护内容
//私有权限 private		成员 类内可以访问 类外不可以访问 儿子不可以访问父亲的私有内容

class Person
{
	//姓名 公共权限
public:
	string m_Name;

	//汽车 保护权限
protected:
	string m_Car;

	//银行卡密码 私有权限
private:
	int m_Password;

public:
	void func()
	{
		m_Name = "张三";
		m_Car = "拖拉机";
		m_Password = 123456;
	}
};

int main()
{
	Person p;
	p.m_Name = "李四";

	system("pause");

	return 0;
}