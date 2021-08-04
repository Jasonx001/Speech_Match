#include"Speech_Manager.h"
#include<algorithm>
#include<deque>
#include<numeric>
#include<fstream>

//无参构造函数
SpeechManager::SpeechManager()
{
	//初始化比赛管理系统--->置空
	this->init_Vector();
	//创建选手
	this->create_Speaker();
	//读取往届记录
	this->read_Record();
}


//显示菜单功能
void SpeechManager::show_Menu()
{
	cout << "************************************" << endl;
	cout << "******** 欢迎参加演讲比赛 **********" << endl;
	cout << "********** 1.开始演讲比赛 **********" << endl;
	cout << "********** 2.查看往届记录 **********" << endl;
	cout << "********** 3.清空比赛记录 **********" << endl;
	cout << "********** 0.退出比赛程序 **********" << endl;
	cout << "************************************" << endl;
	cout << endl;
}

//退出系统
void SpeechManager::exit_System()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}



//析构函数
SpeechManager::~SpeechManager()
{

}

//初始化容器
void SpeechManager::init_Vector()
{
	this->v_fst.clear();
	this->v_scd.clear();
	this->v_vct.clear();
	this->m_spkr.clear();
	this->m_rcd.clear();
	this->m_round = 1;
}

//创建选手
void SpeechManager::create_Speaker()
{
	//创建12名选手
	string name_seed = "ABCDEFGHIJKL";
	for (int i = 0; i < name_seed.size(); i++)
	{
		string name = "选手";
		name += name_seed[i];

		Speaker spkr;
		spkr.set_Name(name);

		//将选手编号添加到第一轮选手的容器
		this->v_fst.push_back(i + 100001);

		//选手编号及对应的编号放入map容器
		this->m_spkr.insert(make_pair(i + 100001, spkr));

	}
}

//启动比赛
void SpeechManager::start_Match()
{
	//抽签
	this->draw_Show();
	
	//第一轮比赛
	this->conduct_Match();

	//显示比赛结果选手信息
	this->show_Result();
	
	//第一轮比赛结束后，设置轮数为2
	this->m_round++;

	//抽签
	this->draw_Show();

	//第二轮比赛
	this->conduct_Match();
	
	//显示冠亚季军
	this->show_Result();
	
	//将比赛结果写入.csv文件
	this->save_Record();

	//执行完一次比赛后，对管理器做初始化
	//初始化比赛管理系统--->置空
	this->init_Vector();

	//创建选手
	this->create_Speaker();
	//读取往届记录
	this->read_Record();

	cout << "本届比赛结束！！！" << endl;
	system("pause");
	system("cls");

}

//抽签
void SpeechManager::draw_Show()
{
	cout << "------第" << this->m_round << "轮比赛抽签------" << endl;
	if (this->m_round == 1)
	{
		random_shuffle(this->v_fst.begin(), this->v_fst.end());
		for (vector<int>::iterator it = this->v_fst.begin(); it != this->v_fst.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(this->v_scd.begin(), this->v_scd.end());
		for (vector<int>::iterator it = this->v_scd.begin(); it != this->v_scd.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	system("pause");
	cout << endl;
}

//执行比赛
void SpeechManager::conduct_Match()
{
	//根据轮数来执行比赛
	cout << "--------第<<" << this->m_round << ">>轮比赛开始-------" << endl;

	//记录比赛选手数目
	int num = 0;

	//定义要执行比赛的容器
	vector<int> v_match;

	//定义临时存储选手分数信息的map容器，降序按分数降序排列
	multimap<double, int, greater<double>> m_spkr_tmp;

	if (this->m_round == 1)
	{
		v_match = this->v_fst;
	}
	else
	{
		v_match = this->v_scd;
	}

	//对当前进行比赛的每个选手打分，计算平均分，并按分数降序排列
	for (vector<int>::iterator it = v_match.begin(); it != v_match.end(); it++)
	{
		num++;

		//10个评委打分
		deque<double> dq_score;
		for (int i = 0; i < 10; i++)
		{
			//随机一个600-1000的数，除以10，就相当于得到了一个60-100之间的小数
			double score = (rand() % 401 + 600) / 10.f;
			
			//向分数容器中添加分数
			dq_score.push_back(score);
		}

		//对分数进行排序
		sort(dq_score.begin(), dq_score.end());

		//去除最高分和最低分
		dq_score.pop_back();
		dq_score.pop_front();

		//对所有分数求和取平均分
		double sum = accumulate(dq_score.begin(), dq_score.end(), 0.0f);
		double ult_score = sum / (double)dq_score.size();

		//根据选手编号保存其分数
		this->m_spkr[*it].set_Score(ult_score);

		//6个人一组，用临时容器保存数据
		m_spkr_tmp.insert(make_pair(ult_score, *it));
		if (num % 6 == 0)
		{
			cout << "-------第" << num / 6 << "小组的比赛成绩--------" << endl;
			for (multimap<double, int, greater<double>>::iterator it_tmp = m_spkr_tmp.begin(); it_tmp != m_spkr_tmp.end(); it_tmp++)
			{
				cout << "选手编号：" << (*it_tmp).second << " ";
				this->m_spkr[(*it_tmp).second].show_Name();
				this->m_spkr[(*it_tmp).second].show_Score(this->m_round - 1);
				cout << endl;
			}

			//取当前组的前三名
			int count_win = 0;
			for (multimap<double, int, greater<double>>::iterator it_tmp = m_spkr_tmp.begin();
				 it_tmp != m_spkr_tmp.end() && count_win < 3; it_tmp++, count_win++)
			{
				if (this->m_round == 1)//第一轮：将两组的前三名放入第二个容器
				{
					this->v_scd.push_back((*it_tmp).second);
				}
				else // 第二轮：将冠亚季军的编号放入v_vct容器中
				{
					this->v_vct.push_back((*it_tmp).second);
				}
			}

			m_spkr_tmp.clear();
		}
	}
	cout << "-----------第" << this->m_round << "轮比赛结束-----------" << endl;
	system("pause");
}

//显示比赛结果选手信息
void SpeechManager::show_Result()
{
	if (this->m_round == 1)
	{
		cout << "第一轮比赛晋级选手:" << endl;
		for (vector<int>::iterator it = this->v_scd.begin(); it != this->v_scd.end(); it++)
		{
			cout << "选手编号：" << (*it);
			this->m_spkr[*it].show_Name();
			this->m_spkr[*it].show_Score(this->m_round-1);
			cout << endl;
		}
	}
	else
	{
		cout << "决赛胜出选手：" << endl;
		for (vector<int>::iterator it = this->v_vct.begin(); it != this->v_vct.end(); it++)
		{
			cout << "选手编号：" << (*it);
			this->m_spkr[*it].show_Name();
			this->m_spkr[*it].show_Score(this->m_round-1);
			cout << endl;
		}
	}
	system("pause");
	system("cls");
	this->show_Menu();
}

//保存比赛结果到csv文件
void SpeechManager::save_Record()
{
	ofstream ofs;
	ofs.open("Match Record.csv", ios::out | ios::app); // 用追加的方式写文件

	vector<int>::const_iterator it = this->v_vct.begin();
	for (it; it != this->v_vct.end(); it++)
	{
		ofs << *it << "," << this->m_spkr[*it].get_Score(this->m_round) << ",";
	}
	ofs << endl;
	ofs.close();
	this->record_Empty = false;

	cout << "比赛结果已记录！" << endl;

}

//读取往届记录
void SpeechManager::read_Record()
{
	ifstream ifs;
	//文件不存在或者文件为空的两种情况
	//1、文件不存在
	ifs.open("Match Record.csv", ios::in);
	if (!ifs.is_open())
	{
		this->record_Empty = true;
		//cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}
	
	//2、文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "记录为空！" << endl;
		this->record_Empty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->record_Empty = false;
	ifs.putback(ch);//将上面读取的单个字符放回来

	string data;
	int TM = 1; //默认比赛开始于第一届
	while (ifs >> data)
	{
		string sub_data;
		int pos = -1;
		int start_pos = 0;
		vector<string> v_str;
		
		while (true)
		{
			pos = data.find(",", start_pos);//查找逗号位置
			if (pos == -1)
			{
				//未找到逗号
				break;
			}
			else
			{
				sub_data = data.substr(start_pos, pos - start_pos);
				v_str.push_back(sub_data);
				start_pos = pos + 1; //这一步很重要，不然程序会进入死循环
			}
		}

		//将数据存放至往届冠亚季军容器内
		this->m_rcd.insert(make_pair(TM, v_str));
		TM++;//读完一行，TM自增一次，读下一行，相当于下一届
	}
	ifs.close();
}

//显示往届记录
void SpeechManager::show_Record()
{
	if (this->record_Empty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "*********往届记录********" << endl;
		for (map<int, vector<string>>::const_iterator it = this->m_rcd.begin();
			it != this->m_rcd.end(); it++)
		{

			cout << "第" << (*it).first << "届"
				<< "  冠军：" << it->second[0] << "  Score: " << it->second[1]
				<< "  亚军：" << it->second[2] << "  Score: " << it->second[3]
				<< "  季军：" << it->second[4] << "  Score: " << it->second[5]
				<< endl;
		}
	}
	system("pause");
	system("cls");
}

//清空往届记录
void SpeechManager::clean_Record()
{
	cout << "您确定要清空比赛记录吗？" << endl;
	cout << "1 -- 确定" << endl;
	cout << "2 -- 取消" << endl;
	cout << "请输入对应操作数并按Enter以执行对应操作：" << endl;
	int opt;
	cin >> opt;
	if (opt == 1) //确定删除记录
	{
		ofstream ofs;
		ofs.open("Match Record.csv", ios::trunc); //以trunc方式打开文件，可直接清空文件
		ofs.close();

		//初始化比赛管理系统--->置空
		this->init_Vector();

		//创建选手
		this->create_Speaker();

		//读取往届记录
		this->read_Record();

		//将为空指示职位true
		this->record_Empty = true;
		cout << "比赛记录已清空！" << endl;
	}
	else
	{
		return;
	}
	system("pause");
	system("cls");
}