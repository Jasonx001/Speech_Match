#include"Speaker.h"

//��ѡ����������
void Speaker::set_Name(string name)
{
	this->m_name = name;
}

//��ѡ�����÷���
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

//��ʾ����
void Speaker::show_Name()
{
	cout << "Name: " << this->m_name << " ";
}

//��ʾ����
void Speaker::show_Score(const int index)
{
	cout << "Score: " << this->m_score[index] << " ";
}

//��ȡ����
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