#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	srand((unsigned int)time(NULL));
	int num = rand() % 100 + 1;
	int count = 0;
	int a = 0;
	cout << "请输入一个数";
	do {
		cin >> a;
		if (a < num) {
			cout << "你猜小了" << endl;
		}
		else if (a > num) {
			cout << "你猜大了" << endl;
		}
		count++;
	} while (a != num);
	cout << "恭喜你猜对了\n" << "用了" << count << "次" << endl;

	system("pause");

	return 0;
}