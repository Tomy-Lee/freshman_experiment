#define __CampusCardOp_H__
#include"AdminOp.h"
void StudentCampusCardAdmin() {
	cout << "��ӭ����ѧ������Ϣ����ҳ��" << endl;
	cout << "��ӭ��,�𾴵�:";
	cout << CClist[ForUseCampusCard].StudentName  << "ͬѧ" << endl;
	int option;
	bool ifTrue = true;
	while (ifTrue) {
		cout << "��ѡ�����Ĳ���:" << endl <<"1.����"<<endl<<"2.��������" << endl << "3.��ֵ" << endl
			<< "4.�󶨴��" << endl <<"5.��ѯУ԰����ˮ��¼"<<endl<< "6.�˳�ϵͳ" << endl;
		cin >> option;
		switch (option) {
		case 1: {
			double a;
			int b;
			cout << "���������ѵĽ��:";
			cin >> a;
			cout << "��ѡ�����ѵĵص�" << endl;
			cout << "1.ʳ��" << endl << "2.��������" << endl;
			cin >> b;
			CClist[ForUseCampusCard].Pay(a, b);
			break;
		}
		case 2: {
			CClist[ForUseCampusCard].SetPassword(1); break;
		}
		case 3: {
			CClist[ForUseCampusCard].TopUp();
			break;
		}
		case 4: {
			CClist[ForUseCampusCard].addBindCard();
			break;
		    }
		case 5: {
			CClist[ForUseCampusCard].query();
			break;
		}
		case 6: return; break;
		default:cout << "ָ���������" << endl;
		}
	}
}