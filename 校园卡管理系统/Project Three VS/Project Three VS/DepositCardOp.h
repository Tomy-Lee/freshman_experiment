#define __DepositCardOp_H__
#include"CampusCardOp.h"
void StudentDepositCardAdmin() {
	cout << "欢迎来到储蓄卡信息管理页面" << endl;
	cout << "欢迎您,尊敬的:";
	cout << DClist[ForUseDepositCard].OwnerName << "先生/女士" << endl;
	int option;
	bool ifTrue = true;
	while (ifTrue) {
		cout << "请选择您的操作:" << endl << "1.储蓄卡充值" << endl << "2.储蓄卡流水信息查询" << endl
			<< "3.修改储蓄卡密码" << endl << "4.修改电话信息"<<endl<<"5.退出系统" << endl;
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
		default: cout << "指令输入错误" << endl;
		}
	}
}


