#pragma once
#include<iostream>
#include<string>
using namespace std;

//����ѡ����
class Speaker
{
public:

	//��ѡ����������
	void set_Name(string name);

	//��ѡ�����÷���
	void set_Score(double score);

	//��ʾ����
	void show_Name();

	//��ʾ����
	void show_Score(const int index);

	//��ȡ����
	double get_Score(const int round);

private:
	string m_name;
	double m_score[2] = { 0, 0 }; //��������������ֵ÷�
};