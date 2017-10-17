#ifndef __AdminOp_H__
#define __AdminOp_H__
#include"LOGIN.h"
void AdminCampusCard() {
	int option;
	int option2;
	cout << "1.添加校园卡" << endl 
	     <<"2.删除校园卡" << endl << "3.单张校园卡业务办理" << endl;
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
		cout << "请输入卡号或学生姓名登录:";
		string Input;
		cin >> Input;
		opSC = findstudentCard(Input);
		if (opSC == -1) {
			cout << "未查询到相关信息" << endl;
		}
		else {
			while (ifTrue) {
				cout << "1.查询校园卡信息" << endl << "2.密码修改" << endl << "3.校园卡绑定"
					<< endl << "4.充值" << endl << "5.退出" << endl;
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
				default: cout << "指令输入错误" << endl;
				}
			}
		}
	}
	}
}
void AdminDepositCard() {
	int option;
	int option2;
	cout << "1.添加储蓄卡" << endl << "2.删除储蓄卡" << endl << "3.单张储蓄卡业务处理" << endl;
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
		cout << "请输入卡号或持卡人姓名登录:";
		string Input;
		cin >> Input;
		opSC = findDepositCard(Input);
		if (opSC == -1) cout << "未查询到相关数据" << endl;
		else {
			while (ifTrue) {
				cout << "1.查询储蓄卡信息" << endl << "2.密码修改" << endl
					<< "3.储蓄卡充值" << endl << "4.返回上一层" << endl;
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
					cout << "请选择充值方式:" << endl;
					cout << "1.现金" << endl;
					cout << "2.通过其他储蓄卡" << endl;
					cin >> a;
					DClist[opSC].TopUpBalance(a);
					break;
				}
				case 4: {
					ifTrue = false;
					break;
				}
				default: cout << "指令输入错误" << endl;
				}
			}
		}
	}
}
}
void AdminOperation() {
	bool ifTrue = true;
	while(ifTrue) {
	cout << "欢迎来到管理员页面" << endl;
	cout << "1.校园卡业务" << endl << "2.储蓄卡业务" << endl << "3.添加新的管理员" 
		 << endl << "4.删除管理员" << endl<<"5.显示所有校园卡记录"<<endl 
		 <<"6.显示所有储蓄卡信息"<<endl<<"7.显示所有绑定卡信息"<<endl<<"8.退出管理员系统"<< endl;
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
	default: cout << "指令输入错误" << endl;
	}
	}
}
#endif