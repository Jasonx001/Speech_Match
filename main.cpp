#include"Speech_Manager.h"
#include<string>
#include<ctime>

using namespace std;

int main()
{
	//添加随机数种子
	srand((unsigned int)time(NULL));

	SpeechManager m;

	//测试选手信息是否正常存入
	/*for (map<int, Speaker>::iterator it = m.m_spkr.begin(); it != m.m_spkr.end(); it++)
	{
		cout << "选手编号：" << (*it).first << "  ";
		(*it).second.show_Name();
		(*it).second.show_Score();
		cout << endl;
	}*/
	while (true)
	{
		m.show_Menu();
		int opt = 0;
		cout << "请输入您的选择：" << endl;
		cin >> opt;
		switch (opt)
		{
		case 1: //开始比赛
			m.start_Match();
			break;
		case 2: //查看往届记录
			m.show_Record();
			break;
		case 3: //清空往届记录
			m.clean_Record();
			break;
		case 0: //退出系统
			m.exit_System();
			break;

		default:
			break;
		}
	}
	
	//system("pause");
	return 0;
}