#ifndef __AdminOp_H__
#define __AdminOp_H__
#include"LOGIN.h"
void AdminCampusCard() {
	int option;
	int option2;
	cout << "1.���У԰��" << endl 
	     <<"2.ɾ��У԰��" << endl << "3.����У԰��ҵ�����" << endl;
	cin >> option2;
	switch (option2) {
	case 1: {
		addNewCampusCard();
		break;
	}
	case 2: {
		deleteCampusCard();
		break;
	}
	case 3: {
		bool ifTrue = true;
		int opSC;
		cout << "�����뿨�Ż�ѧ��������¼:";
		string Input;
		cin >> Input;
		opSC = findstudentCard(Input);
		if (opSC == -1) {
			cout << "δ��ѯ�������Ϣ" << endl;
		}
		else {
			while (ifTrue) {
				cout << "1.��ѯУ԰����Ϣ" << endl << "2.�����޸�" << endl << "3.У԰����"
					<< endl << "4.��ֵ" << endl << "5.�˳�" << endl;
				cin >> option;
				switch (option) {
				case 1: {
					CClist[opSC].query();
					break;
				}
				case 2: {
					CClist[opSC].SetPassword(2);
					break;
				}
				case 3: {
					CClist[opSC].addBindCard();
					break;
				}
				case 4: {
					CClist[opSC].TopUp();
					break;
				}
				case 5: {
					return;
					break;
				}
				default: cout << "ָ���������" << endl;
				}
			}
		}
	}
	}
}
void AdminDepositCard() {
	int option;
	int option2;
	cout << "1.��Ӵ��" << endl << "2.ɾ�����" << endl << "3.���Ŵ��ҵ����" << endl;
	cin >> option2;
	switch(option2) {
	case 1: {
		addNewDepositCard();
		break;
	}
	case 2: {
		deleteDepositCard();
		break;
	}
	case 3: {
		bool ifTrue = true;
		int opSC;
		cout << "�����뿨�Ż�ֿ���������¼:";
		string Input;
		cin >> Input;
		opSC = findDepositCard(Input);
		if (opSC == -1) cout << "δ��ѯ���������" << endl;
		else {
			while (ifTrue) {
				cout << "1.��ѯ�����Ϣ" << endl << "2.�����޸�" << endl
					<< "3.�����ֵ" << endl << "4.������һ��" << endl;
				cin >> option;
				switch (option) {
				case 1: {
					DClist[opSC].query(3);
					break;
				}
				case 2: {
					DClist[opSC].SetPassword(2);
					break;
				}
				case 3: {
					double a;
					cout << "��ѡ���ֵ��ʽ:" << endl;
					cout << "1.�ֽ�" << endl;
					cout << "2.ͨ���������" << endl;
					cin >> a;
					DClist[opSC].TopUpBalance(a);
					break;
				}
				case 4: {
					ifTrue = false;
					break;
				}
				default: cout << "ָ���������" << endl;
				}
			}
		}
	}
}
}
void AdminOperation() {
	bool ifTrue = true;
	while(ifTrue) {
	cout << "��ӭ��������Աҳ��" << endl;
	cout << "1.У԰��ҵ��" << endl << "2.���ҵ��" << endl << "3.����µĹ���Ա" 
		 << endl << "4.ɾ������Ա" << endl<<"5.��ʾ����У԰����¼"<<endl 
		 <<"6.��ʾ���д����Ϣ"<<endl<<"7.��ʾ���а󶨿���Ϣ"<<endl<<"8.�˳�����Աϵͳ"<< endl;
	int op;
	cin >> op;
	switch (op) {
	case 1: AdminCampusCard(); break;
	case 2: AdminDepositCard(); break;
	case 3: addAdminAccount(); break;
	case 4: deleteAdminAccount(); break;
	case 8: return; break;
	case 5: {
		for (int i = 0; i < CClist.size(); i++) {
			CClist[i].query();
		}
		break;
	}
	case 6: {
		for (int i = 0; i < DClist.size(); i++) {
			DClist[i].query(3);
		}
		break;
	}
	case 7: {
		for (int i = 0; i < BClist.size(); i++) {
			BClist[i].query();
		}
		break;
	}
	default: cout << "ָ���������" << endl;
	}
	}
}
#endif