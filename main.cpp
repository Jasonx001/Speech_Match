#include"Speech_Manager.h"
#include<string>
#include<ctime>

using namespace std;

int main()
{
	//������������
	srand((unsigned int)time(NULL));

	SpeechManager m;

	//����ѡ����Ϣ�Ƿ���������
	/*for (map<int, Speaker>::iterator it = m.m_spkr.begin(); it != m.m_spkr.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << (*it).first << "  ";
		(*it).second.show_Name();
		(*it).second.show_Score();
		cout << endl;
	}*/
	while (true)
	{
		m.show_Menu();
		int opt = 0;
		cout << "����������ѡ��" << endl;
		cin >> opt;
		switch (opt)
		{
		case 1: //��ʼ����
			m.start_Match();
			break;
		case 2: //�鿴�����¼
			m.show_Record();
			break;
		case 3: //��������¼
			m.clean_Record();
			break;
		case 0: //�˳�ϵͳ
			m.exit_System();
			break;

		default:
			break;
		}
	}
	
	//system("pause");
	return 0;
}