#pragma once
#include<iostream>
#include<map>
#include<vector>
#include"Speaker.h"
using namespace std;

//定义演讲比赛的管理类
class SpeechManager
{
public:
	//无参构造函数
	SpeechManager();


	//显示菜单功能
	void show_Menu();

	//退出系统
	void exit_System();

	//析构函数
	~SpeechManager();

	//初始化容器
	void init_Vector();

	//创建选手
	void create_Speaker();

	//启动比赛
	void start_Match();

	//抽签
	void draw_Show();

	//执行比赛
	void conduct_Match();

	//显示比赛结果选手信息
	void show_Result();

	//保存比赛结果到csv文件
	void save_Record();

	//读取往届记录
	void read_Record();

	//显示往届记录
	void show_Record();

	//清空往届记录
	void clean_Record();

	//第一轮选手编号容器
	vector<int> v_fst;

	//第一轮晋级选手编号
	vector<int> v_scd;

	//比赛前三名选手编号
	vector<int> v_vct;

	//选手及分数容器
	map<int, Speaker> m_spkr;

	//记录比赛轮数
	int m_round;

	//记录文件是否为空
	bool record_Empty;

	//往届冠亚季军记录
	map<int, vector<string>> m_rcd;
};