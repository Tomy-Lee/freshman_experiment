#ifndef __functions_H__
#define __functions_H__
#include "Manager.h"
bool ifDepositCardExist(string a) {
	int ifTrue = false;
	for (int i = 0; i < DClist.size(); i++) {
		if (DClist[i].CardNumber == a) {
			ifTrue = true;
			break;
		}
	}
	return ifTrue;
}
bool ifCampusCardExist(string a) {
	int ifTrue = false;
	for (int i = 0; i < CClist.size(); i++) {
		if (CClist[i].StudentNumber == a) {
			ifTrue = true;
			break;
		}
	}
	return ifTrue;
}
bool IfPasswordSame(int pos, string b) {
	if (DClist[pos].Password == b) {
		return true;
	}
	else return false;
}
int ReturnDcLocation(string a) {
	int pos = 0;
	for (int i = 0; i < DClist.size(); i++) {
		if (DClist[i].CardNumber == a) {
			pos = i;
			break;
		}
	}
	return pos;
}
int NewBindingCard(int a, int b) {
	class binding_card* newcard;
	newcard = new binding_card;
	newcard->campus_card_pos = a;
	newcard->Count_Deposit_Card = 1;
	newcard->deposit_card_pos[0] = b;
	BClist.push_back(*newcard);
	return BClist.size() - 1;
}
void ExistBindingCard(int a, int b) {
	BClist[a].deposit_card_pos[BClist[a].Count_Deposit_Card] = b;
	BClist[a].Count_Deposit_Card += 1;
}
void campus_card::addBindCard() {
	string BindNumber;
	string BindPassword;
	cout << "请输入储蓄卡卡号:";
	cin >> BindNumber;
	cout << "请输入储蓄卡密码:";
	cin >> BindPassword;
	if (ifDepositCardExist(BindNumber)) {
		int Locate = ReturnDcLocation(BindNumber);
		if (IfPasswordSame(Locate, BindPassword)) {
			if (countBindCard == 0) {
				BindCardPos = NewBindingCard(ForUseCampusCard,Locate);
				//class binding_card *newcard;
				//newcard = new binding_card;
				CardArr[countBindCard] = Locate;
				countBindCard += 1;
			}
			else {
				ExistBindingCard(BindCardPos, Locate);
				CardArr[countBindCard] = Locate;
				countBindCard += 1;
			}
			cout << "储蓄卡添加成功" << endl;
		}
	}
}
void GetLocalTime(int &a, int &b, int &c, int &d, int &e) {
	time_t rawtime = time(0);
	tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	a = 1900 + timeinfo.tm_year; //年
	b = 1 + timeinfo.tm_mon;//月
	c = timeinfo.tm_mday;   //日
	d = timeinfo.tm_hour;  //时
	e = timeinfo.tm_min; //分
}
void deposit_card::TopUpBalance(int a) {
	switch (a) {
	case 1: {
		double Money;
		cout << "请输入充值金额:";
		cin >> Money;
		deposit_card::deposit += Money;
		cout << "充值成功" << endl;
		GetLocalTime(AllInfo[countPay2].T.year, AllInfo[countPay2].T.month,
			AllInfo[countPay2].T.day, AllInfo[countPay2].T.hour,
			AllInfo[countPay2].T.min);
		AllInfo[countPay2].T.countMethod = 0;
		AllInfo[countPay2].T.TopUpMoney = Money;
		countPay2 += 1;
	}
	break;
	case 2: {
		bool exit = true;
		string Cardnumber;
		string Cardpassword;
		cout << "请输入卡号:";
		cin >> Cardnumber;
		cout << "请输入密码:";
		cin >> Cardpassword;
		if (ifDepositCardExist(Cardnumber)) {
			int pos;
			pos = ReturnDcLocation(Cardnumber);
			while (exit) {
				if (Cardpassword == DClist[pos].Password) {
					cout << "请输入充值金额:";
					double Money;
					cin >> Money;
					if (DClist[pos].deposit - Money >= 0) {
						this->deposit += Money;
						DClist[pos].Pay(Money,4);
						exit = false;
						GetLocalTime(AllInfo[countPay2].T.year, AllInfo[countPay2].T.month,
							AllInfo[countPay2].T.day, AllInfo[countPay2].T.hour,
							AllInfo[countPay2].T.min);
						AllInfo[countPay2].T.countMethod = 1;
						AllInfo[countPay2].T.TopUpMoney = Money;
						countPay2 += 1;
						cout << "充值成功" << endl;
					}
				}
				else {
					cout << "密码错误，请重新输入。退出请出入Q" << endl;
					cin >> Cardpassword;
					if (Cardpassword == "Q" || Cardpassword == "q") exit = false;
				}
			}
			exit = true;
		}
		else cout << "不存在这张卡" << endl;
	}
	}

}
void addNewDepositCard() {
	class deposit_card *addCard;
	addCard = new deposit_card;
	string CN;
	string PW;
	bool ifTrue = true;
	while (ifTrue) {
		cout << "请输入卡号:";
		//string CN;
		cin >> CN;
		ifTrue = ifDepositCardExist(CN);
		if (ifTrue == true) cout << "该卡号已存在" << endl;
	}
	cout << "请输入余额:";
	double depo;
	cin >> depo;
	cout << "请输入持卡人电话号码:";
	string teleN;
	cin >> teleN;
	ifTrue = true;
	while (ifTrue) {
		cout << "请输入密码:";
		cin >> PW;
		if (PW.size() == 6) {
			ifTrue == false;
			break;
		}
		else {
			cout << "密码长度需要为6位" << endl;
		}
	}
	cout << "请输入持卡人姓名:";
	string N;
	cin >> N;
	addCard->CardNumber = CN;
	addCard->deposit = depo;
	addCard->Password = PW;
	addCard->OwnerTele = teleN;
	addCard->OwnerName = N;
	DClist.push_back(*addCard);
}
bool campus_card::Pay(double a, int place) {
	if (deposit - a < 0) {
		cout << "余额不足，请充值后再次支付" << endl;
		return false;
	}
	else {
		deposit -= a;
		cout << "支付成功" << endl;
		GetLocalTime(AllInfo[countPay2].P.year, AllInfo[countPay2].P.month,
			AllInfo[countPay2].P.day, AllInfo[countPay2].P.hour,
			AllInfo[countPay2].P.min);
		AllInfo[countPay2].P.spentMoney = a;
		AllInfo[countPay2].P.countLocation = place;
		countPay1 += 1;
		return true;
	}
}
void campus_card::TopUp() {
	if (countBindCard == 0) {
		cout << "未绑定银行卡，无法进行充值" << endl;
	}
	else {
		cout << "请选择支付的储蓄卡号" << endl;
		for (int i = 0; i < countBindCard; i++) {
			cout << i + 1 << "." << DClist[CardArr[i]].CardNumber << endl;
		}
		int choice;
		cin >> choice;
		if (choice > countBindCard) cout << "输入错误" << endl;
		else {
			cout << "请输入充值金额" << endl;
			double money;
			cin >> money;
			if (DClist[CardArr[choice - 1]].Pay(money, 3)) {
				deposit += money;
				cout << "充值成功" << endl;
				GetLocalTime(AllInfo[countPay2].T.year, AllInfo[countPay2].T.month,
					AllInfo[countPay2].T.day, AllInfo[countPay2].T.hour,
					AllInfo[countPay2].T.min);
				AllInfo[countPay2].T.countMethod = 1;
				AllInfo[countPay2].T.TopUpMoney = money;
				AllInfo[countPay2].T.AccountPos = choice - 1;
				countPay2 += 1;
			}
			else cout << "储蓄卡余额不足，请重新选择" << endl;
		}
	}
}
void addNewCampusCard() {
	string a, b, c, d;
	double e;
	bool ifTrue = true;
	class campus_card *newCard;
	newCard = new campus_card;
	while (ifTrue) {
		cout << "请输入学号:";
		cin >> a;
		ifTrue = ifCampusCardExist(a);
		if (ifTrue == true) cout << "该学号已存在" << endl;
		else newCard->StudentNumber = a;
	}
	cout << "请输入持卡人姓名";
	cin >> newCard->StudentName;
	cout << "请输入专业:";
	cin >> newCard->Major;
	ifTrue = true;
	while (ifTrue) {
		cout << "请输入密码:";
		cin >> b;
		if (b.size() == 6) { 
			newCard->Password = b; 
			ifTrue = false;
			break;
		}
		else cout << "密码长度需要为6位" << endl;
	}
	cout << "请输入余额";
	cin >> newCard->deposit;
	CClist.push_back(*newCard);
}
int findstudentCard(string a) {
	int i;
	int count = 0;
	for ( i = 0; i < CClist.size(); i++) {
		if (CClist[i].StudentNumber == a || CClist[i].StudentName == a) {
			count += 1;
			break;
		}
	}
	if(count > 0) return i;
	else return -1;
}
int findDepositCard(string a) {
	int i;
	int count = 0;
	for ( i = 0; i < CClist.size(); i++) {
		if (DClist[i].CardNumber == a || DClist[i].OwnerName == a) {
			count += 1;
			break;
		}
	}
	if(count > 0) return i;
	else return -1;
}
void deleteCampusCard() {
	string a;
	cout << "请输入校园卡卡号";
	cin >> a;
	int b;
	b = findstudentCard(a);
	if (b == -1) cout << "不存在该账户" << endl;
	else {
		CC::iterator it = CClist.begin() + b;
		CClist.erase(it);
		cout << "账号删除成功" << endl;
	}
}
void deleteDepositCard() {
	string a;
	cout << "请输入储蓄卡卡号";
	cin >> a;
	int b;
	b = findDepositCard(a);
	if (b == -1) cout << "不存在该账户" << endl;
	else {
		DC::iterator it = DClist.begin() + b;
		DClist.erase(it);
		cout << "账号删除成功" << endl;
	}
}
int findAdminAccout(string a) {
	int i = 0;
	int count = 0;
	for (i = 0; i < ADlist.size(); i++) {
		if (ADlist[i].returnAccount() == a) {
			count += 1;
			break;
		}
	}
	if (count == 0) return -1;
	else return i;
}
void addAdminAccount() {
	class administrator *a;
	a = new administrator;
	string c; 
	string b;
	string e;
	cout << "请输入管理员账号:";
	cin >> c;
	cout << "请输入管理员密码:";
	cin >> b;
	cout << "请再次输入管理员密码:";
	cin >> e;
	if (b == e) {
		a->setAccount(c);
		a->setPassword(b);
		a->setAccess(0);
		ADlist.push_back(*a);
	}
	else {
		cout << "两次输入密码不一致" << endl;
	}
}
void deleteAdminAccount() {
	string a;
	int b;
	cout << "请输入管理员账户:";
	cin >> a;
	if (a == "admin") cout << "你没有权限删除该账户" << endl;
	else {
		b = findAdminAccout(a);
		if (b == -1) cout << "不存在该账户" << endl;
		else {
			ADMIN::iterator it = ADlist.begin() + b;
			ADlist.erase(it);
			cout << "账号删除成功" << endl;
		}
	}
}
#endif
