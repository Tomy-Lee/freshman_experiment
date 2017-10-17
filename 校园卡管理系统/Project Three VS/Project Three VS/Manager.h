#ifndef __MANAGER_H_
#define __MANAGER_H__
#include<string>
#include<iostream>
#include<time.h>
#include<vector>
#include<fstream>
#include<istream>
using namespace std;
int ForUseCampusCard = 0;
int ForUseDepositCard = 0;
int ForUseBindedCard = 0;
class card {
public:
	//string CardNumber;
	string Password;
	virtual bool Pay(double a, int place) = 0;
	virtual void query() {};
	string TopUpMethod[2] = { "现金","银行卡" };
	string Location[4] = { "于食堂","于教育超市","给校园卡充值","给他人充值" };
	struct PayInfo {
		struct Payment {
			int year, month, day, hour, min;
			double spentMoney;
			int countLocation;
		} P;
		struct TopUp {
			int year, month, day, hour, min;
			double TopUpMoney;
			int countMethod;
			int AccountPos;
		} T;
	};
	struct PayInfo AllInfo[10000];
	void SetPassword(int i) {
		string Original_Password;
		string New_Password;
		string Check_Password;
		if (i == 1) {
			cout << "请输入原始密码:";
			cin >> Original_Password;
			cout << "请输入新密码:";
			cin >> New_Password;
			cout << "请再次输入新密码:";
			cin >> Check_Password;
			if (Password == Original_Password) {
				if (New_Password == Check_Password) {
					if (New_Password.size() != 6) cout << "密码长度应为6位" << endl;
					else {
						Password = New_Password;
						cout << "密码设置成功" << endl;
					}
				}
				else cout << "两次输入的新密码不一致" << endl;
			}
			else cout << "密码输入错误" << endl;
		}
		if (i == 2) {
			cout << "请输入新密码:";
			cin >> New_Password;
			cout << "请再次输入新密码:";
			cin >> Check_Password;
			if (New_Password == Check_Password) {
				if (New_Password.size() != 6) cout << "密码长度应为6位" << endl;
				else {
					Password = New_Password;
					cout << "密码设置成功" << endl;
				}
			}
			else {
				cout << "两次密码输入不一致" << endl;
			}
		}
	}
};
class deposit_card :public card {
public:
	double deposit;
	double OverdraftLimit;
	string CardNumber;
	string OwnerName;
	string OwnerTele;
	//string Dpassword;
	//bool ifBind;
	int countPay1;
	int countPay2;
	void TopUpBalance(int a);
	deposit_card(double _deposit = 0, double _OverdraftLimit = 500, string number = "000000", string name = "none",
		string tele = "0000000000", string _password = "000000") {
		deposit = _deposit;
		OverdraftLimit = _OverdraftLimit;
		CardNumber = number;
		OwnerName = name;
		OwnerTele = tele;
		Password = _password;
		countPay1 = 0;
		countPay2 = 0;
	}
	void ModifyTele() {
		string NewTele;
		string CheckTele;
		cout << "请输入新的电话号码:";
		cin >> NewTele;
		cout << "请再次输入电话号码:";
		cin >> CheckTele;
		if (NewTele == CheckTele) {
			OwnerTele = NewTele;
		}
		else cout << "两次输入不一致" << endl;
	}
	/*void DsetPassword(int i) {
		string Original_Password;
		string New_Password;
		string Check_Password;
		if (i == 1) {
			cout << "请输入原始密码:";
			cin >> Original_Password;
			cout << "请输入新密码:";
			cin >> New_Password;
			cout << "请再次输入新密码:";
			cin >> Check_Password;
			if (Dpassword == Original_Password) {
				if (New_Password == Check_Password) {
					if (New_Password.size() != 6) cout << "密码长度应为6位" << endl;
					else {
						Dpassword = New_Password;
						cout << "密码设置成功" << endl;
					}
					}
				else cout << "两次输入的新密码不一致" << endl;
			}
			else cout << "密码输入错误" << endl;
		}
		if (i == 2) {
			cout << "请输入新密码:";
			cin >> New_Password;
			cout << "请再次输入新密码:";
			cin >> Check_Password;
			if (New_Password == Check_Password) {
				if (New_Password.size() != 6) cout << "密码长度应为6位" << endl;
				else {
					Dpassword = New_Password;
					cout << "密码设置成功" << endl;
				}
				}
			else {
				cout << "两次密码输入不一致" << endl;
			}
		}
	} */
	bool Pay(double a,int place) {
		if (deposit - a >= -OverdraftLimit) {
			deposit -= a;
			//cout << "请输入支付地点:" << endl << "1.食堂" << endl << "2.教育超市" 
			//	<< endl << "3.给校园卡充值" << endl << "4.给他人储蓄卡充值" << endl;
			//int q;
			//cin >> q;
			AllInfo[countPay1].P.countLocation = place-1;
			cout << "支付成功" << endl;
			time_t rawtime = time(0);
			tm timeinfo;
			localtime_s(&timeinfo, &rawtime);
			AllInfo[countPay1].P.year = 1900 + timeinfo.tm_year; //年
			AllInfo[countPay1].P.month = 1 + timeinfo.tm_mon;//月
			AllInfo[countPay1].P.day = timeinfo.tm_mday;   //日
			AllInfo[countPay1].P.hour = timeinfo.tm_hour;  //时
			AllInfo[countPay1].P.min = timeinfo.tm_min; //分
			AllInfo[countPay1].P.spentMoney = a;
			countPay1 += 1;
			return true;
		}
		else {
			cout << "余额不足，请充值后再使用" << endl;
			return false;
		}
	}
	void query(int a) {
		switch (a) {
		case 1: {
			cout << "账户信息:" << endl;
			cout << "持卡人姓名：" << OwnerName << endl;
			cout << "储蓄卡卡号：" << CardNumber << endl;
			cout << "持卡人电话：" << OwnerTele << endl;
			cout << "余额：" << deposit << endl;
			cout << "透支额度：" << OverdraftLimit << endl;
		}break;
		case 2: {
			cout << "账户流水信息:" << endl;
			cout << "支付信息:" << endl;
			for (int i = 0; i < countPay1; i++) {
				cout << AllInfo[i].P.year << "-";
				if (AllInfo[i].P.month < 10)cout << "0";
				cout << AllInfo[i].P.month << "-";
				if (AllInfo[i].P.day < 10) cout << "0";
				cout << AllInfo[i].P.day << " ";
				cout << " ";
				if (AllInfo[i].P.hour < 10) cout << "0";
				cout << AllInfo[i].P.hour << ":";
				if (AllInfo[i].P.min < 10) cout << "0";
				cout << AllInfo[i].P.min <<"    "<< Location[AllInfo[i].P.countLocation]<<"支付" << AllInfo[i].P.spentMoney << "元" << endl;
			}
			cout << "充值信息:" << endl;
			for (int i = 0; i < countPay2; i++) {
				cout << AllInfo[i].T.TopUpMoney << "通过" << TopUpMethod[AllInfo[i].T.countMethod] << "充值" << endl;
			}
		}break;
		case 3: {
			cout << "账户信息:" << endl;
			cout << "持卡人姓名：" << OwnerName << endl;
			cout << "储蓄卡卡号：" << CardNumber << endl;
			cout << "持卡人电话：" << OwnerTele << endl;
			cout << "余额：" << deposit << endl;
			cout << "透支额度：" << OverdraftLimit << endl << endl;
			cout << "账户流水信息:" << endl;
			cout << "支付信息:" << endl;
			for (int i = 0; i < countPay1; i++) {
				cout << AllInfo[i].P.year << "-";
				if (AllInfo[i].P.month < 10)cout << "0";
				cout << AllInfo[i].P.month << "-";
				if (AllInfo[i].P.day < 10) cout << "0";
				cout << AllInfo[i].P.day << " ";
				cout << " ";
				if (AllInfo[i].P.hour < 10) cout << "0";
				cout << AllInfo[i].P.hour << ":";
				if (AllInfo[i].P.min < 10) cout << "0";
				cout << AllInfo[i].P.min <<"    "<<Location[AllInfo[i].P.countLocation]<<"支付" << AllInfo[i].P.spentMoney << "元" << endl;
			}
			if (countPay1 == 0) cout << "无" << endl;
			cout << "充值信息:" << endl;
			for (int i = 0; i < countPay2; i++) {
				cout << AllInfo[i].T.year << "-";
				if (AllInfo[i].T.month < 10)cout << "0";
				cout << AllInfo[i].T.month << "-";
				if (AllInfo[i].T.day < 10) cout << "0";
				cout << AllInfo[i].T.day << " ";
				cout << " ";
				if (AllInfo[i].T.hour < 10) cout << "0";
				cout << AllInfo[i].T.hour << ":";
				if (AllInfo[i].T.min < 10) cout << "0";
				cout << AllInfo[i].T.min << "    ";
				cout << "通过" << TopUpMethod[AllInfo[i].T.countMethod] << "充值"<< AllInfo[i].T.TopUpMoney<<"元" << endl;
			}
			if (countPay2 == 0) cout << "无" << endl;
		} break;
		default: cout << "输入错误" << endl;
		}
	}
};
typedef vector<deposit_card> DC;
DC DClist;
class campus_card : public card {
public:
	int countPay1 = 0;
	int countPay2 = 0;
	int BindCardPos;
	string Major;
	string StudentNumber;
	string StudentName;
	double deposit;
	//string Cpassword;
	int countBindCard = 0;
	int CardArr[100];
	campus_card(double _deposit = 0, string major = "none", string number = "0000",
		string name = "none", string _password = "0000", bool a = false) {
		Major = major;
		StudentName = name;
		StudentNumber = number;
		deposit = _deposit;
		Password = _password;
		countBindCard = 0;
		BindCardPos = -1;
	}
	bool Pay(double a, int place);
	void query() {
		cout << "学生姓名：" << campus_card::StudentName << endl;
		cout << "学生学号：" << campus_card::StudentNumber << endl;
		cout << "专业名称：" << campus_card::Major << endl;
		cout << "卡内余额：" << campus_card::deposit << endl;
		cout << "消费信息:" << endl;
		for (int i = 0; i < countPay1; i++) {
			cout << AllInfo[i].P.year << "-";
			if (AllInfo[i].P.month < 10)cout << "0";
			cout << AllInfo[i].P.month << "-";
			if (AllInfo[i].P.day < 10) cout << "0";
			cout << AllInfo[i].P.day << " ";
			cout << " ";
			if (AllInfo[i].P.hour < 10) cout << "0";
			cout << AllInfo[i].P.hour << ":";
			if (AllInfo[i].P.min < 10) cout << "0";
			cout << AllInfo[i].P.min << "    " << 
				Location[AllInfo[i].P.countLocation] << "支付" 
				<< AllInfo[i].P.spentMoney << "元" << endl;
		}
		if (countPay1 == 0) cout << "无" << endl;
		cout << "充值信息:" << endl;
		for (int i = 0; i < countPay2; i++) {
			cout << AllInfo[i].T.year << "-";
			if (AllInfo[i].T.month < 10)cout << "0";
			cout << AllInfo[i].T.month << "-";
			if (AllInfo[i].T.day < 10) cout << "0";
			cout << AllInfo[i].T.day << " ";
			cout << " ";
			if (AllInfo[i].T.hour < 10) cout << "0";
			cout << AllInfo[i].T.hour << ":";
			if (AllInfo[i].T.min < 10) cout << "0";
			cout << AllInfo[i].T.min << "    ";
			cout << "通过" << TopUpMethod[AllInfo[i].T.countMethod];
			if (AllInfo[i].T.countMethod == 1) { cout << DClist[AllInfo[i].T.AccountPos].CardNumber; }
			cout<< "充值" << AllInfo[i].T.TopUpMoney << "元" << endl;
		}
		if (countPay2 == 0) cout << "无" << endl;
	}

	void addBindCard();
	void TopUp();
};
typedef vector<campus_card> CC;
CC CClist;
class binding_card : public deposit_card, public campus_card {
 public:
	int campus_card_pos;
	int deposit_card_pos[100];
	int Count_Deposit_Card = 0;
	binding_card(){}
	void query() {
		cout << "校园卡信息:" << endl;
		CClist[campus_card_pos].query();
		for (int i = 0; i < Count_Deposit_Card; i++) {
			cout << "绑定卡" << i <<":"<< endl;
			DClist[deposit_card_pos[i]].query(3);
		}
	}
};
typedef vector<binding_card> BC;
BC BClist;
class administrator {
private:
	string Account;
	string Password;
	int access;
public:
	void setAccount(string inAccount) {
		Account = inAccount;
	}
	void setPassword(string inPassword) {
		Password = inPassword;
	}
	string returnAccount() {
		return Account;
	}
	string returnPassword() {
		return Password;
	}
	void setAccess(int i) {
		access = i;
	}
};
typedef vector<administrator> ADMIN;
ADMIN ADlist;
administrator admini;
#endif
