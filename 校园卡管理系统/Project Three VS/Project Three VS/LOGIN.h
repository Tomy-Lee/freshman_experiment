#ifndef __LOGIN_H__
#define __LOGIN_H__
#include"Data.h"
int login(int option) {
	string CardNumber;
	string CardPassword;
	//int option;
	cout << "请输入卡号:";
	cin >> CardNumber;
	cout << "请输入密码:";
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
		cout << "请输入管理员账号:";
		cin >> adminAccount;
		cout << "请输入管理员密码:";
		cin >> adminPassword;
		ifExist = AdminLogin(adminAccount, adminPassword);
		if (ifExist == true) {
			//manage();
			cout << "登陆成功" << endl;
			return true;
			break;
		}
		else {
			cout << "用户名或密码错误，请重新输入。账号密码均输入Q返回" << endl;
			if ((adminAccount == "Q" || adminAccount == "Q") && (adminPassword == "q" || adminPassword == "q")) {
				ifTrue = false;
				return false;
			}
		}
	}
}
#endif