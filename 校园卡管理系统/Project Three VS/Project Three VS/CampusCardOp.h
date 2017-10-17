#define __CampusCardOp_H__
#include"AdminOp.h"
void StudentCampusCardAdmin() {
	cout << "欢迎来到学生卡信息管理页面" << endl;
	cout << "欢迎您,尊敬的:";
	cout << CClist[ForUseCampusCard].StudentName  << "同学" << endl;
	int option;
	bool ifTrue = true;
	while (ifTrue) {
		cout << "请选择您的操作:" << endl <<"1.消费"<<endl<<"2.更改密码" << endl << "3.充值" << endl
			<< "4.绑定储蓄卡" << endl <<"5.查询校园卡流水记录"<<endl<< "6.退出系统" << endl;
		cin >> option;
		switch (option) {
		case 1: {
			double a;
			int b;
			cout << "请输入消费的金额:";
			cin >> a;
			cout << "请选择消费的地点" << endl;
			cout << "1.食堂" << endl << "2.教育超市" << endl;
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
		default:cout << "指令输入错误" << endl;
		}
	}
}