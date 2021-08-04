#pragma once
#include<iostream>
#include<map>
#include<vector>
#include"Speaker.h"
using namespace std;

//�����ݽ������Ĺ�����
class SpeechManager
{
public:
	//�޲ι��캯��
	SpeechManager();


	//��ʾ�˵�����
	void show_Menu();

	//�˳�ϵͳ
	void exit_System();

	//��������
	~SpeechManager();

	//��ʼ������
	void init_Vector();

	//����ѡ��
	void create_Speaker();

	//��������
	void start_Match();

	//��ǩ
	void draw_Show();

	//ִ�б���
	void conduct_Match();

	//��ʾ�������ѡ����Ϣ
	void show_Result();

	//������������csv�ļ�
	void save_Record();

	//��ȡ�����¼
	void read_Record();

	//��ʾ�����¼
	void show_Record();

	//��������¼
	void clean_Record();

	//��һ��ѡ�ֱ������
	vector<int> v_fst;

	//��һ�ֽ���ѡ�ֱ��
	vector<int> v_scd;

	//����ǰ����ѡ�ֱ��
	vector<int> v_vct;

	//ѡ�ּ���������
	map<int, Speaker> m_spkr;

	//��¼��������
	int m_round;

	//��¼�ļ��Ƿ�Ϊ��
	bool record_Empty;

	//������Ǽ�����¼
	map<int, vector<string>> m_rcd;
};