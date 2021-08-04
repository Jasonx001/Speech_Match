#include"Speaker.h"

//给选手设置姓名
void Speaker::set_Name(string name)
{
	this->m_name = name;
}

//给选手设置分数
void Speaker::set_Score(double score)
{
	if (this->m_score[0] == 0)
	{
		this->m_score[0] = score;
	}
	else
	{
		this->m_score[1] = score;
	}
}

//显示姓名
void Speaker::show_Name()
{
	cout << "Name: " << this->m_name << " ";
}

//显示分数
void Speaker::show_Score(const int index)
{
	cout << "Score: " << this->m_score[index] << " ";
}

//获取分数
double Speaker::get_Score(const int round)
{
	if (round == 1)
	{
		return this->m_score[0];
	}
	else
	{
		return this->m_score[1];
	}
}