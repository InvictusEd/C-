/*****************************************************************//**
 * \file   main.cpp
 * \brief  This is a score management system for campus sports meeting.
 * \detail System functions include score entry, query, and ranking.
 * \author qqdas
 * \date   December 2022
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#define _CRT_SECURE_NO_WARNINGS		///防止由于使用scanf, strcpy等不安全函数导致报错
#define PMAX 10						///比赛项目最大数
#define FMAX 21						///院系数量最大数

/*定义比赛项目和院系名称的全局变量数组*/
string projectArray[PMAX] = { "50米","100米","200米","400米","1500米","接力赛","跳高","立定跳远","三级跳远","铅球" };
string facultyArray[FMAX] = { "农学与生物技术学院","植物保护学院","食品科学技术学院","水利学院","大数据学院",
							  "经济管理学院","体育学院","继续教育学院","动物科学技术学院","园林园艺学院","烟草学院",
						      "机电工程学院","建筑工程学院", "人文社会科学学院","国际学院","动物医学院","资源与环境学院",
							  "茶学院","理学院","马克思主义学院","外语学院" };


/*比赛项目数据结构*/
struct Project
{
	int p_Num = NULL;
	string p_Name;
	double score = NULL;
};

/*院系数据结构*/
struct Faculty
{
	int f_Num = NULL;
	string f_Name;
	Project projectArray[PMAX];		///1个院系有10个比赛项目，因此Faculty结构体嵌套Project结构体
	double total_score = NULL;
};

/*排序数据结构，用于排序，并不改变院系原本编号*/
struct Sort
{
	int s_Num = NULL;
	string s_Name;
	double total_score = NULL;
};


/*各项函数声明*/
void initFaculty(Faculty F[]);								///用于初始化院系数据结构的函数
void initSort(Faculty F[], Sort S[]);						///用于初始化排名数据结构的函数
void updataTotalScore(int s_Num, Faculty F[], Sort S[]);		///用于更新选中院系的总分
void showInfo();												///打印信息的函数，包括比赛项目编号和名称，院系编号和名称
void showScore(Faculty F[]);									///打印分数的函数，按照用户输入的院系编号打印
void addScore(Faculty F[], Sort S[]);						///加分函数，负责录入成绩
void totalScoreSort(Sort S[]);								///按照院系总分进行排名
void showSort(Sort S[]);										///打印排名，包括所有院系
void selection(char select, Faculty F[], Sort S[]);			///负责菜单的选项的跳转功能
void menu();													///主菜单


/**
 * @brief 对院系的结构体数组进行初始化并赋值
 * @param F F是Facult结构体数组
 * @return NULL
 * @attention 该赋值不包括院系的total_score
 */
void initFaculty(Faculty F[])
{
	for (int i = 0; i < FMAX; i++)
	{
		F[i].f_Num = i + 1;
		F[i].f_Name = facultyArray[i];
		for (int j = 0; j < PMAX; j++)
		{
			F[i].projectArray[j].p_Name = projectArray[j];
			F[i].projectArray[j].p_Num = j + 1;
		}
	}
}


/**
 * @brief 对Sort的结构体数组进行初始化和赋值
 * @param F F是Faculty结构体数组
 * @param S S是Sort结构体数组
 * @return NULL
 */
void initSort(Faculty F[], Sort S[])
{
	for (int i = 0; i < FMAX; i++)
	{
		S[i].s_Name = F[i].f_Name;
		S[i].s_Num = F[i].f_Num;
	}
}


/**
 * @brief 用于更新选中院系的总分，每录入一次成绩就执行一次，录入成绩的函数为addScore()
 * @param f_Num f_Num为需要更新的院系编号
 * @param F F是Faculty结构体数组
 * @param S S是Sort结构体数组
 * @return NULL
 */
void updataTotalScore(int f_Num, Faculty F[], Sort S[])
{
	for (int i = 0; i < FMAX; i++)
	{
		if (S[i].s_Num == F[f_Num].f_Num)
		{
			S[i].total_score = F[f_Num].total_score;
		}
	}
}


/**
 * @brief 显示比赛项目和院系设置，方便用户浏览操作
 * @return NULL
 * @note 它为了整洁的显示页面而生
 */
void showInfo()
{
	cout << "====================================================================================================================" << endl;
	cout << setiosflags(ios::right) << setw(70) << "运动会项目以及参赛学院名单" << endl;
	cout << "====================================================================================================================" << endl;
	cout << setiosflags(ios::left) << setw(20) << "运动会各项目编号：" << resetiosflags(ios::left)
		 << setiosflags(ios::right) << setw(38) << "各学院编号：" << resetiosflags(ios::right) << setw(40) << "各学院编号：" << endl;
	cout << "-------------------" << setiosflags(ios::right) << setw(43) << "---------------------" << resetiosflags(ios::right)
		 << setiosflags(ios::right) << setw(41) << "---------------------" << endl;
	for (int i = 0; i < PMAX; i++)
	{
		cout << setiosflags(ios::right) << setw(2) << i + 1 << "." << resetiosflags(ios::right)
			 << setiosflags(ios::left) << setw(38) << projectArray[i]
			 << setiosflags(ios::right) << setw(2) << i + 1 << "." << resetiosflags(ios::right)
			 << setiosflags(ios::left) << setw(38) << facultyArray[i]
			 << i + 11 << "." << facultyArray[i + 10] << endl;
		cout << "-------------------" << setiosflags(ios::right) << setw(43) << "---------------------" << resetiosflags(ios::right)
			 << setiosflags(ios::right) << setw(41) << "---------------------" << endl;
	}
	cout << setiosflags(ios::right) << setw(85) << "21." << facultyArray[20] << endl;
	cout << setiosflags(ios::right) << setw(103) << "---------------------" << endl;
}


/**
 * @brief 按照院系编号打印该院系的总分
 * @param F F为Faculty结构体数组
 * @return NULL
 */
void showScore(Faculty F[])
{
	string sSelect;
	char cSelect = NULL;
	int f_Num = 0;

	while (true)
	{
		system("cls");
		showInfo();
		cout << "总分查询" << endl;
		cout << "请输入您需要查询的学院编号：";
		cin >> f_Num;
		f_Num--;
		cout << F[f_Num].f_Name << "本届运动会的总分是：" << F[f_Num].total_score << "\n" << endl;
		cout << "☆输入1继续查询......☆" << endl;
		cout << "☆输入0回到主菜单......☆" << endl;
		cin >> sSelect;
		cSelect = sSelect.at(0);
		if (cSelect == '0')break;
	}
}


/**
 * @brief 为院系录入比赛项目成绩
 * @param F F是Faculty结构体数组
 * @param S S是Sort结构体数组，院系分数改变，Sort也随之而变
 * @return NULL
 */
void addScore(Faculty F[], Sort S[])
{
	double score = NULL;
	int f_Num = NULL;
	int p_Num = NULL;
	string sSelect;
	char cSelect = NULL;

	while (true)
	{
		system("cls");
		showInfo();
		cout << "请输入院系编号：";
		cin >> f_Num;
		// 因为数组由0开始，因此需要减1
		f_Num--;
		cout << "您选择的是：" << F[f_Num].f_Name << endl;
		cout << "请输入比赛项目编号：";
		cin >> p_Num;
		p_Num--;
		cout << "您选择的是：" << F[f_Num].projectArray[p_Num].p_Name << endl;
		cout << "请输入该项目的成绩：";
		cin >> score;
		// 为该院系的该项目成绩赋值
		F[f_Num].projectArray[p_Num].score = score;
		cout << "\n录入成功！" << endl;
		cout << F[f_Num].f_Name << F[f_Num].projectArray[p_Num].p_Name << "成绩是：" << F[f_Num].projectArray[p_Num].score << "分\n" << endl;
		F[f_Num].total_score = F[f_Num].projectArray[p_Num].score;
		// 每一次录入成绩都需要更新Score结构体数组变量S
		updataTotalScore(f_Num, F, S);
		cout << "☆输入1继续录入分数......☆" << endl;
		cout << "☆输入0回到主菜单......☆\n" << endl;
		cin >> sSelect;
		cSelect = sSelect.at(0);
		if (cSelect == '0')break;
	}
	return;
}


/**
 * @brief 按总分排名
 * @param S Sort结构体数组，用来排名的结构体数组
 * @return NULL
 * @note 使用S来排名而非F来排名，是为了保持F的数组下标和编号对应不变，避免混乱发生
 */
void totalScoreSort(Sort S[])
{
	for (int i = 0; i < FMAX - 1; i++) {
		for (int j = 0; j < FMAX - i - 1; j++) {
			if (S[j].total_score < S[j + 1].total_score) {
				Sort temp = S[j];
				S[j] = S[j + 1];
				S[j + 1] = temp;
			}
		}
	}
}


/**
 * @brief 输出排名，以排好序的学院顺序输出排名
 * @param S Sort结构体数组
 * @return NULL
 */
void showSort(Sort S[])
{
	string sSelect;
	char cSelect = NULL;

	totalScoreSort(S);
	cout << "排名                    " << "学院                        " << "总分" << endl;
	cout << "----            " << "--------------------                " << "----" << endl;
	for (int i = 0; i < FMAX; i++)
	{
		cout << setiosflags(ios::right) << setw(2) << i + 1 << resetiosflags(ios::right) << setiosflags(ios::left) << setw(15) << " "
			<< resetiosflags(ios::right) << setiosflags(ios::left) << setw(35) << S[i].s_Name << S[i].total_score << endl;
	}
	cout << "\n查询完成！" << endl;
	cout << "☆输入0回到主菜单......☆\n" << endl;
	cin >> sSelect;
	cSelect = sSelect.at(0);
	if (cSelect == '0')return;
}


/**
 * @brief 系统功能选择函数
 * @param select 由主函数传递而来，控制用户选项
 * @param F Faculty结构体数组
 * @param S Sort结构体数组
 * @return NULL
 * @note selection()相当于一座桥梁，以主函数和菜单连接着各个主要功能模块
 */
void selection(char select, Faculty F[], Sort S[])
{
	switch (select)
	{
	case '1':
		system("cls");
		addScore(F, S);
		break;
	case '2':
		showScore(F);
		break;
	case '3':
		system("cls");
		showSort(S);
		break;
	case '4':
		printf("欢迎您下次使用！\n");
		exit(0);
	}
}


/**
 * @brief 打印主菜单
 * @return NULL
 */
void menu()
{
	system("cls");
	printf("\n\n\n");
	printf("                                                欢迎进入校运动会成绩管理系统^-^\n\n");
	printf("                                             |===================================|\n");
	printf("                                             |            1.成绩录入             |\n");
	printf("                                             |            2.查询院系得分         |\n");
	printf("                                             |            3.查看排名             |\n");
	printf("                                             |            4.退出                 |\n");
	printf("                                             |===================================|\n\n");
	printf("                                                       请输入您的选择：");
}


/**
 * @brief 主函数
 * @detail 主函数是Faculty和Sort的两个数组变量F,S的起源，也是进入selection()的窗口
 * @return 程序执行成功与否
 * @retval 0 程序执行成功
 * @retval 1 程序执行失败
 * @attention while(true)保证了除了用户输入退出选项才能退出程序
 */
int main()
{
	string sSelect;
	char cSelect;
	/** 这里有另外一种方法
	* 动态分配方法，适用于自行添加学院
	* Faculty *F;
	* C的动态分配内存方法（不适用）
	* F = (Faculty*)malloc(sizeof(Faculty));
	* 使用C++的new方法来分配内存
	* F = new Faculty;
	* 经考虑该系统只需使用结构体数组即可，无需使用动态线性结构
	*/
	Faculty F[FMAX];
	Sort S[FMAX];
	// 初始化学院和排序数据结构
	initFaculty(F);
	initSort(F, S);

	while (true)
	{
		menu();
		cin >> sSelect;
		// 防止小调皮用户乱输入，因此增加判错功能
		cSelect = sSelect.at(0);
		if (cSelect == '1' || cSelect == '2' || cSelect == '3' || cSelect == '4')
		{
			selection(cSelect, F, S);	///如果输入正确，则进入selection()
		}
		else
		{
			printf("请输入正确选项！\n");
			system("pause");
			system("cls");
			continue;
		}
	}
	return 0;
}