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

#define _CRT_SECURE_NO_WARNINGS		///��ֹ����ʹ��scanf, strcpy�Ȳ���ȫ�������±���
#define PMAX 10						///������Ŀ�����
#define FMAX 21						///Ժϵ���������

/*���������Ŀ��Ժϵ���Ƶ�ȫ�ֱ�������*/
string projectArray[PMAX] = { "50��","100��","200��","400��","1500��","������","����","������Զ","������Զ","Ǧ��" };
string facultyArray[FMAX] = { "ũѧ�����＼��ѧԺ","ֲ�ﱣ��ѧԺ","ʳƷ��ѧ����ѧԺ","ˮ��ѧԺ","������ѧԺ",
							  "���ù���ѧԺ","����ѧԺ","��������ѧԺ","�����ѧ����ѧԺ","԰��԰��ѧԺ","�̲�ѧԺ",
						      "���繤��ѧԺ","��������ѧԺ", "��������ѧѧԺ","����ѧԺ","����ҽѧԺ","��Դ�뻷��ѧԺ",
							  "��ѧԺ","��ѧԺ","���˼����ѧԺ","����ѧԺ" };


/*������Ŀ���ݽṹ*/
struct Project
{
	int p_Num = NULL;
	string p_Name;
	double score = NULL;
};

/*Ժϵ���ݽṹ*/
struct Faculty
{
	int f_Num = NULL;
	string f_Name;
	Project projectArray[PMAX];		///1��Ժϵ��10��������Ŀ�����Faculty�ṹ��Ƕ��Project�ṹ��
	double total_score = NULL;
};

/*�������ݽṹ���������򣬲����ı�Ժϵԭ�����*/
struct Sort
{
	int s_Num = NULL;
	string s_Name;
	double total_score = NULL;
};


/*���������*/
void initFaculty(Faculty F[]);								///���ڳ�ʼ��Ժϵ���ݽṹ�ĺ���
void initSort(Faculty F[], Sort S[]);						///���ڳ�ʼ���������ݽṹ�ĺ���
void updataTotalScore(int s_Num, Faculty F[], Sort S[]);		///���ڸ���ѡ��Ժϵ���ܷ�
void showInfo();												///��ӡ��Ϣ�ĺ���������������Ŀ��ź����ƣ�Ժϵ��ź�����
void showScore(Faculty F[]);									///��ӡ�����ĺ����������û������Ժϵ��Ŵ�ӡ
void addScore(Faculty F[], Sort S[]);						///�ӷֺ���������¼��ɼ�
void totalScoreSort(Sort S[]);								///����Ժϵ�ֽܷ�������
void showSort(Sort S[]);										///��ӡ��������������Ժϵ
void selection(char select, Faculty F[], Sort S[]);			///����˵���ѡ�����ת����
void menu();													///���˵�


/**
 * @brief ��Ժϵ�Ľṹ��������г�ʼ������ֵ
 * @param F F��Facult�ṹ������
 * @return NULL
 * @attention �ø�ֵ������Ժϵ��total_score
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
 * @brief ��Sort�Ľṹ��������г�ʼ���͸�ֵ
 * @param F F��Faculty�ṹ������
 * @param S S��Sort�ṹ������
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
 * @brief ���ڸ���ѡ��Ժϵ���ܷ֣�ÿ¼��һ�γɼ���ִ��һ�Σ�¼��ɼ��ĺ���ΪaddScore()
 * @param f_Num f_NumΪ��Ҫ���µ�Ժϵ���
 * @param F F��Faculty�ṹ������
 * @param S S��Sort�ṹ������
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
 * @brief ��ʾ������Ŀ��Ժϵ���ã������û��������
 * @return NULL
 * @note ��Ϊ���������ʾҳ�����
 */
void showInfo()
{
	cout << "====================================================================================================================" << endl;
	cout << setiosflags(ios::right) << setw(70) << "�˶�����Ŀ�Լ�����ѧԺ����" << endl;
	cout << "====================================================================================================================" << endl;
	cout << setiosflags(ios::left) << setw(20) << "�˶������Ŀ��ţ�" << resetiosflags(ios::left)
		 << setiosflags(ios::right) << setw(38) << "��ѧԺ��ţ�" << resetiosflags(ios::right) << setw(40) << "��ѧԺ��ţ�" << endl;
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
 * @brief ����Ժϵ��Ŵ�ӡ��Ժϵ���ܷ�
 * @param F FΪFaculty�ṹ������
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
		cout << "�ֲܷ�ѯ" << endl;
		cout << "����������Ҫ��ѯ��ѧԺ��ţ�";
		cin >> f_Num;
		f_Num--;
		cout << F[f_Num].f_Name << "�����˶�����ܷ��ǣ�" << F[f_Num].total_score << "\n" << endl;
		cout << "������1������ѯ......��" << endl;
		cout << "������0�ص����˵�......��" << endl;
		cin >> sSelect;
		cSelect = sSelect.at(0);
		if (cSelect == '0')break;
	}
}


/**
 * @brief ΪԺϵ¼�������Ŀ�ɼ�
 * @param F F��Faculty�ṹ������
 * @param S S��Sort�ṹ�����飬Ժϵ�����ı䣬SortҲ��֮����
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
		cout << "������Ժϵ��ţ�";
		cin >> f_Num;
		// ��Ϊ������0��ʼ�������Ҫ��1
		f_Num--;
		cout << "��ѡ����ǣ�" << F[f_Num].f_Name << endl;
		cout << "�����������Ŀ��ţ�";
		cin >> p_Num;
		p_Num--;
		cout << "��ѡ����ǣ�" << F[f_Num].projectArray[p_Num].p_Name << endl;
		cout << "���������Ŀ�ĳɼ���";
		cin >> score;
		// Ϊ��Ժϵ�ĸ���Ŀ�ɼ���ֵ
		F[f_Num].projectArray[p_Num].score = score;
		cout << "\n¼��ɹ���" << endl;
		cout << F[f_Num].f_Name << F[f_Num].projectArray[p_Num].p_Name << "�ɼ��ǣ�" << F[f_Num].projectArray[p_Num].score << "��\n" << endl;
		F[f_Num].total_score = F[f_Num].projectArray[p_Num].score;
		// ÿһ��¼��ɼ�����Ҫ����Score�ṹ���������S
		updataTotalScore(f_Num, F, S);
		cout << "������1����¼�����......��" << endl;
		cout << "������0�ص����˵�......��\n" << endl;
		cin >> sSelect;
		cSelect = sSelect.at(0);
		if (cSelect == '0')break;
	}
	return;
}


/**
 * @brief ���ܷ�����
 * @param S Sort�ṹ�����飬���������Ľṹ������
 * @return NULL
 * @note ʹ��S����������F����������Ϊ�˱���F�������±�ͱ�Ŷ�Ӧ���䣬������ҷ���
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
 * @brief ������������ź����ѧԺ˳���������
 * @param S Sort�ṹ������
 * @return NULL
 */
void showSort(Sort S[])
{
	string sSelect;
	char cSelect = NULL;

	totalScoreSort(S);
	cout << "����                    " << "ѧԺ                        " << "�ܷ�" << endl;
	cout << "----            " << "--------------------                " << "----" << endl;
	for (int i = 0; i < FMAX; i++)
	{
		cout << setiosflags(ios::right) << setw(2) << i + 1 << resetiosflags(ios::right) << setiosflags(ios::left) << setw(15) << " "
			<< resetiosflags(ios::right) << setiosflags(ios::left) << setw(35) << S[i].s_Name << S[i].total_score << endl;
	}
	cout << "\n��ѯ��ɣ�" << endl;
	cout << "������0�ص����˵�......��\n" << endl;
	cin >> sSelect;
	cSelect = sSelect.at(0);
	if (cSelect == '0')return;
}


/**
 * @brief ϵͳ����ѡ����
 * @param select �����������ݶ����������û�ѡ��
 * @param F Faculty�ṹ������
 * @param S Sort�ṹ������
 * @return NULL
 * @note selection()�൱��һ�����������������Ͳ˵������Ÿ�����Ҫ����ģ��
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
		printf("��ӭ���´�ʹ�ã�\n");
		exit(0);
	}
}


/**
 * @brief ��ӡ���˵�
 * @return NULL
 */
void menu()
{
	system("cls");
	printf("\n\n\n");
	printf("                                                ��ӭ����У�˶���ɼ�����ϵͳ^-^\n\n");
	printf("                                             |===================================|\n");
	printf("                                             |            1.�ɼ�¼��             |\n");
	printf("                                             |            2.��ѯԺϵ�÷�         |\n");
	printf("                                             |            3.�鿴����             |\n");
	printf("                                             |            4.�˳�                 |\n");
	printf("                                             |===================================|\n\n");
	printf("                                                       ����������ѡ��");
}


/**
 * @brief ������
 * @detail ��������Faculty��Sort�������������F,S����Դ��Ҳ�ǽ���selection()�Ĵ���
 * @return ����ִ�гɹ����
 * @retval 0 ����ִ�гɹ�
 * @retval 1 ����ִ��ʧ��
 * @attention while(true)��֤�˳����û������˳�ѡ������˳�����
 */
int main()
{
	string sSelect;
	char cSelect;
	/** ����������һ�ַ���
	* ��̬���䷽�����������������ѧԺ
	* Faculty *F;
	* C�Ķ�̬�����ڴ淽���������ã�
	* F = (Faculty*)malloc(sizeof(Faculty));
	* ʹ��C++��new�����������ڴ�
	* F = new Faculty;
	* �����Ǹ�ϵͳֻ��ʹ�ýṹ�����鼴�ɣ�����ʹ�ö�̬���Խṹ
	*/
	Faculty F[FMAX];
	Sort S[FMAX];
	// ��ʼ��ѧԺ���������ݽṹ
	initFaculty(F);
	initSort(F, S);

	while (true)
	{
		menu();
		cin >> sSelect;
		// ��ֹС��Ƥ�û������룬��������д���
		cSelect = sSelect.at(0);
		if (cSelect == '1' || cSelect == '2' || cSelect == '3' || cSelect == '4')
		{
			selection(cSelect, F, S);	///���������ȷ�������selection()
		}
		else
		{
			printf("��������ȷѡ�\n");
			system("pause");
			system("cls");
			continue;
		}
	}
	return 0;
}