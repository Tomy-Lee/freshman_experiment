#define __DepositCardOp_H__
#include"CampusCardOp.h"
void StudentDepositCardAdmin() {
	cout << "��ӭ���������Ϣ����ҳ��" << endl;
	cout << "��ӭ��,�𾴵�:";
	cout << DClist[ForUseDepositCard].OwnerName << "����/Ůʿ" << endl;
	int option;
	bool ifTrue = true;
	while (ifTrue) {
		cout << "��ѡ�����Ĳ���:" << endl << "1.�����ֵ" << endl << "2.�����ˮ��Ϣ��ѯ" << endl
			<< "3.�޸Ĵ������" << endl << "4.�޸ĵ绰��Ϣ"<<endl<<"5.�˳�ϵͳ" << endl;
		cin >> option;
		switch (option) {
		case 1: {
			DClist[ForUseDepositCard].TopUpBalance(2);
			break;
		}
		case 2: {
			DClist[ForUseDepositCard].query(3);
			break;
		}
		case 3: {
			DClist[ForUseDepositCard].SetPassword(1);
			break;
		}
		case 5: {
			return;
			break;
		}
		case 4: {
			DClist[ForUseDepositCard].ModifyTele();
			break;
		}
		default: cout << "ָ���������" << endl;
		}
	}
}


