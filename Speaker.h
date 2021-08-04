#pragma once
#include<iostream>
#include<string>
using namespace std;

//创建选手类
class Speaker
{
public:

	//给选手设置姓名
	void set_Name(string name);

	//给选手设置分数
	void set_Score(double score);

	//显示姓名
	void show_Name();

	//显示分数
	void show_Score(const int index);

	//获取分数
	double get_Score(const int round);

private:
	string m_name;
	double m_score[2] = { 0, 0 }; //分数，最多有两轮得分
};