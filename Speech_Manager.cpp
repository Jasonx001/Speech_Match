#include"Speech_Manager.h"
#include<algorithm>
#include<deque>
#include<numeric>
#include<fstream>

//�޲ι��캯��
SpeechManager::SpeechManager()
{
	//��ʼ����������ϵͳ--->�ÿ�
	this->init_Vector();
	//����ѡ��
	this->create_Speaker();
	//��ȡ�����¼
	this->read_Record();
}


//��ʾ�˵�����
void SpeechManager::show_Menu()
{
	cout << "************************************" << endl;
	cout << "******** ��ӭ�μ��ݽ����� **********" << endl;
	cout << "********** 1.��ʼ�ݽ����� **********" << endl;
	cout << "********** 2.�鿴�����¼ **********" << endl;
	cout << "********** 3.��ձ�����¼ **********" << endl;
	cout << "********** 0.�˳��������� **********" << endl;
	cout << "************************************" << endl;
	cout << endl;
}

//�˳�ϵͳ
void SpeechManager::exit_System()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}



//��������
SpeechManager::~SpeechManager()
{

}

//��ʼ������
void SpeechManager::init_Vector()
{
	this->v_fst.clear();
	this->v_scd.clear();
	this->v_vct.clear();
	this->m_spkr.clear();
	this->m_rcd.clear();
	this->m_round = 1;
}

//����ѡ��
void SpeechManager::create_Speaker()
{
	//����12��ѡ��
	string name_seed = "ABCDEFGHIJKL";
	for (int i = 0; i < name_seed.size(); i++)
	{
		string name = "ѡ��";
		name += name_seed[i];

		Speaker spkr;
		spkr.set_Name(name);

		//��ѡ�ֱ����ӵ���һ��ѡ�ֵ�����
		this->v_fst.push_back(i + 100001);

		//ѡ�ֱ�ż���Ӧ�ı�ŷ���map����
		this->m_spkr.insert(make_pair(i + 100001, spkr));

	}
}

//��������
void SpeechManager::start_Match()
{
	//��ǩ
	this->draw_Show();
	
	//��һ�ֱ���
	this->conduct_Match();

	//��ʾ�������ѡ����Ϣ
	this->show_Result();
	
	//��һ�ֱ�����������������Ϊ2
	this->m_round++;

	//��ǩ
	this->draw_Show();

	//�ڶ��ֱ���
	this->conduct_Match();
	
	//��ʾ���Ǽ���
	this->show_Result();
	
	//���������д��.csv�ļ�
	this->save_Record();

	//ִ����һ�α����󣬶Թ���������ʼ��
	//��ʼ����������ϵͳ--->�ÿ�
	this->init_Vector();

	//����ѡ��
	this->create_Speaker();
	//��ȡ�����¼
	this->read_Record();

	cout << "�����������������" << endl;
	system("pause");
	system("cls");

}

//��ǩ
void SpeechManager::draw_Show()
{
	cout << "------��" << this->m_round << "�ֱ�����ǩ------" << endl;
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

//ִ�б���
void SpeechManager::conduct_Match()
{
	//����������ִ�б���
	cout << "--------��<<" << this->m_round << ">>�ֱ�����ʼ-------" << endl;

	//��¼����ѡ����Ŀ
	int num = 0;

	//����Ҫִ�б���������
	vector<int> v_match;

	//������ʱ�洢ѡ�ַ�����Ϣ��map���������򰴷�����������
	multimap<double, int, greater<double>> m_spkr_tmp;

	if (this->m_round == 1)
	{
		v_match = this->v_fst;
	}
	else
	{
		v_match = this->v_scd;
	}

	//�Ե�ǰ���б�����ÿ��ѡ�ִ�֣�����ƽ���֣�����������������
	for (vector<int>::iterator it = v_match.begin(); it != v_match.end(); it++)
	{
		num++;

		//10����ί���
		deque<double> dq_score;
		for (int i = 0; i < 10; i++)
		{
			//���һ��600-1000����������10�����൱�ڵõ���һ��60-100֮���С��
			double score = (rand() % 401 + 600) / 10.f;
			
			//�������������ӷ���
			dq_score.push_back(score);
		}

		//�Է�����������
		sort(dq_score.begin(), dq_score.end());

		//ȥ����߷ֺ���ͷ�
		dq_score.pop_back();
		dq_score.pop_front();

		//�����з������ȡƽ����
		double sum = accumulate(dq_score.begin(), dq_score.end(), 0.0f);
		double ult_score = sum / (double)dq_score.size();

		//����ѡ�ֱ�ű��������
		this->m_spkr[*it].set_Score(ult_score);

		//6����һ�飬����ʱ������������
		m_spkr_tmp.insert(make_pair(ult_score, *it));
		if (num % 6 == 0)
		{
			cout << "-------��" << num / 6 << "С��ı����ɼ�--------" << endl;
			for (multimap<double, int, greater<double>>::iterator it_tmp = m_spkr_tmp.begin(); it_tmp != m_spkr_tmp.end(); it_tmp++)
			{
				cout << "ѡ�ֱ�ţ�" << (*it_tmp).second << " ";
				this->m_spkr[(*it_tmp).second].show_Name();
				this->m_spkr[(*it_tmp).second].show_Score(this->m_round - 1);
				cout << endl;
			}

			//ȡ��ǰ���ǰ����
			int count_win = 0;
			for (multimap<double, int, greater<double>>::iterator it_tmp = m_spkr_tmp.begin();
				 it_tmp != m_spkr_tmp.end() && count_win < 3; it_tmp++, count_win++)
			{
				if (this->m_round == 1)//��һ�֣��������ǰ��������ڶ�������
				{
					this->v_scd.push_back((*it_tmp).second);
				}
				else // �ڶ��֣������Ǽ����ı�ŷ���v_vct������
				{
					this->v_vct.push_back((*it_tmp).second);
				}
			}

			m_spkr_tmp.clear();
		}
	}
	cout << "-----------��" << this->m_round << "�ֱ�������-----------" << endl;
	system("pause");
}

//��ʾ�������ѡ����Ϣ
void SpeechManager::show_Result()
{
	if (this->m_round == 1)
	{
		cout << "��һ�ֱ�������ѡ��:" << endl;
		for (vector<int>::iterator it = this->v_scd.begin(); it != this->v_scd.end(); it++)
		{
			cout << "ѡ�ֱ�ţ�" << (*it);
			this->m_spkr[*it].show_Name();
			this->m_spkr[*it].show_Score(this->m_round-1);
			cout << endl;
		}
	}
	else
	{
		cout << "����ʤ��ѡ�֣�" << endl;
		for (vector<int>::iterator it = this->v_vct.begin(); it != this->v_vct.end(); it++)
		{
			cout << "ѡ�ֱ�ţ�" << (*it);
			this->m_spkr[*it].show_Name();
			this->m_spkr[*it].show_Score(this->m_round-1);
			cout << endl;
		}
	}
	system("pause");
	system("cls");
	this->show_Menu();
}

//������������csv�ļ�
void SpeechManager::save_Record()
{
	ofstream ofs;
	ofs.open("Match Record.csv", ios::out | ios::app); // ��׷�ӵķ�ʽд�ļ�

	vector<int>::const_iterator it = this->v_vct.begin();
	for (it; it != this->v_vct.end(); it++)
	{
		ofs << *it << "," << this->m_spkr[*it].get_Score(this->m_round) << ",";
	}
	ofs << endl;
	ofs.close();
	this->record_Empty = false;

	cout << "��������Ѽ�¼��" << endl;

}

//��ȡ�����¼
void SpeechManager::read_Record()
{
	ifstream ifs;
	//�ļ������ڻ����ļ�Ϊ�յ��������
	//1���ļ�������
	ifs.open("Match Record.csv", ios::in);
	if (!ifs.is_open())
	{
		this->record_Empty = true;
		//cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}
	
	//2���ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "��¼Ϊ�գ�" << endl;
		this->record_Empty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->record_Empty = false;
	ifs.putback(ch);//�������ȡ�ĵ����ַ��Ż���

	string data;
	int TM = 1; //Ĭ�ϱ�����ʼ�ڵ�һ��
	while (ifs >> data)
	{
		string sub_data;
		int pos = -1;
		int start_pos = 0;
		vector<string> v_str;
		
		while (true)
		{
			pos = data.find(",", start_pos);//���Ҷ���λ��
			if (pos == -1)
			{
				//δ�ҵ�����
				break;
			}
			else
			{
				sub_data = data.substr(start_pos, pos - start_pos);
				v_str.push_back(sub_data);
				start_pos = pos + 1; //��һ������Ҫ����Ȼ����������ѭ��
			}
		}

		//�����ݴ����������Ǽ���������
		this->m_rcd.insert(make_pair(TM, v_str));
		TM++;//����һ�У�TM����һ�Σ�����һ�У��൱����һ��
	}
	ifs.close();
}

//��ʾ�����¼
void SpeechManager::show_Record()
{
	if (this->record_Empty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "*********�����¼********" << endl;
		for (map<int, vector<string>>::const_iterator it = this->m_rcd.begin();
			it != this->m_rcd.end(); it++)
		{

			cout << "��" << (*it).first << "��"
				<< "  �ھ���" << it->second[0] << "  Score: " << it->second[1]
				<< "  �Ǿ���" << it->second[2] << "  Score: " << it->second[3]
				<< "  ������" << it->second[4] << "  Score: " << it->second[5]
				<< endl;
		}
	}
	system("pause");
	system("cls");
}

//��������¼
void SpeechManager::clean_Record()
{
	cout << "��ȷ��Ҫ��ձ�����¼��" << endl;
	cout << "1 -- ȷ��" << endl;
	cout << "2 -- ȡ��" << endl;
	cout << "�������Ӧ����������Enter��ִ�ж�Ӧ������" << endl;
	int opt;
	cin >> opt;
	if (opt == 1) //ȷ��ɾ����¼
	{
		ofstream ofs;
		ofs.open("Match Record.csv", ios::trunc); //��trunc��ʽ���ļ�����ֱ������ļ�
		ofs.close();

		//��ʼ����������ϵͳ--->�ÿ�
		this->init_Vector();

		//����ѡ��
		this->create_Speaker();

		//��ȡ�����¼
		this->read_Record();

		//��Ϊ��ָʾְλtrue
		this->record_Empty = true;
		cout << "������¼����գ�" << endl;
	}
	else
	{
		return;
	}
	system("pause");
	system("cls");
}