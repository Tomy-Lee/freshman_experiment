#ifndef __LOGIN_H__
#define __LOGIN_H__
#include"Data.h"
int login(int option) {
	string CardNumber;
	string CardPassword;
	//int option;
	cout << "�����뿨��:";
	cin >> CardNumber;
	cout << "����������:";
	cin >> CardPassword;
	switch (option) {
	case 1: {
		int count = 0;
		for (int i = 0; i < CClist.size(); i++) {
			if (CardNumber == CClist[i].StudentNumber && CardPassword == CClist[i].Password) {
				count = 1;
				ForUseCampusCard = i;
				return i + 1;
				break;
			}
		}
		if (count == 0) return 0;
		break;
	}
	case 2: {
		int count = 0;
		for (int i = 0; i < DClist.size(); i++) {
			if (CardNumber == DClist[i].CardNumber&&CardPassword == DClist[i].Password) {
				count = 1;
				ForUseDepositCard = i;
				return i + 1;
				break;
			}
		}
		if (count == 0) return 0;
		break;
	}
	}
}
bool AdminLogin(string a, string b) {
	int count = 0;
	for (int i = 0; i < ADlist.size(); i++) {
		if (ADlist[i].returnAccount() == a && ADlist[i].returnPassword() == b) {
			count += 1;
			break;
		}
	}
	if (count == 0) return false;
	else return true;
}
bool admin() {
	string adminAccount;
	string adminPassword;
	bool ifTrue = true;
	bool ifExist;
	while (ifTrue) {
		cout << "���������Ա�˺�:";
		cin >> adminAccount;
		cout << "���������Ա����:";
		cin >> adminPassword;
		ifExist = AdminLogin(adminAccount, adminPassword);
		if (ifExist == true) {
			//manage();
			cout << "��½�ɹ�" << endl;
			return true;
			break;
		}
		else {
			cout << "�û���������������������롣�˺����������Q����" << endl;
			if ((adminAccount == "Q" || adminAccount == "Q") && (adminPassword == "q" || adminPassword == "q")) {
				ifTrue = false;
				return false;
			}
		}
	}
}
#endif