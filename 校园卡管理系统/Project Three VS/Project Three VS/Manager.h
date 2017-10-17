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
	string TopUpMethod[2] = { "�ֽ�","���п�" };
	string Location[4] = { "��ʳ��","�ڽ�������","��У԰����ֵ","�����˳�ֵ" };
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
			cout << "������ԭʼ����:";
			cin >> Original_Password;
			cout << "������������:";
			cin >> New_Password;
			cout << "���ٴ�����������:";
			cin >> Check_Password;
			if (Password == Original_Password) {
				if (New_Password == Check_Password) {
					if (New_Password.size() != 6) cout << "���볤��ӦΪ6λ" << endl;
					else {
						Password = New_Password;
						cout << "�������óɹ�" << endl;
					}
				}
				else cout << "��������������벻һ��" << endl;
			}
			else cout << "�����������" << endl;
		}
		if (i == 2) {
			cout << "������������:";
			cin >> New_Password;
			cout << "���ٴ�����������:";
			cin >> Check_Password;
			if (New_Password == Check_Password) {
				if (New_Password.size() != 6) cout << "���볤��ӦΪ6λ" << endl;
				else {
					Password = New_Password;
					cout << "�������óɹ�" << endl;
				}
			}
			else {
				cout << "�����������벻һ��" << endl;
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
		cout << "�������µĵ绰����:";
		cin >> NewTele;
		cout << "���ٴ�����绰����:";
		cin >> CheckTele;
		if (NewTele == CheckTele) {
			OwnerTele = NewTele;
		}
		else cout << "�������벻һ��" << endl;
	}
	/*void DsetPassword(int i) {
		string Original_Password;
		string New_Password;
		string Check_Password;
		if (i == 1) {
			cout << "������ԭʼ����:";
			cin >> Original_Password;
			cout << "������������:";
			cin >> New_Password;
			cout << "���ٴ�����������:";
			cin >> Check_Password;
			if (Dpassword == Original_Password) {
				if (New_Password == Check_Password) {
					if (New_Password.size() != 6) cout << "���볤��ӦΪ6λ" << endl;
					else {
						Dpassword = New_Password;
						cout << "�������óɹ�" << endl;
					}
					}
				else cout << "��������������벻һ��" << endl;
			}
			else cout << "�����������" << endl;
		}
		if (i == 2) {
			cout << "������������:";
			cin >> New_Password;
			cout << "���ٴ�����������:";
			cin >> Check_Password;
			if (New_Password == Check_Password) {
				if (New_Password.size() != 6) cout << "���볤��ӦΪ6λ" << endl;
				else {
					Dpassword = New_Password;
					cout << "�������óɹ�" << endl;
				}
				}
			else {
				cout << "�����������벻һ��" << endl;
			}
		}
	} */
	bool Pay(double a,int place) {
		if (deposit - a >= -OverdraftLimit) {
			deposit -= a;
			//cout << "������֧���ص�:" << endl << "1.ʳ��" << endl << "2.��������" 
			//	<< endl << "3.��У԰����ֵ" << endl << "4.�����˴����ֵ" << endl;
			//int q;
			//cin >> q;
			AllInfo[countPay1].P.countLocation = place-1;
			cout << "֧���ɹ�" << endl;
			time_t rawtime = time(0);
			tm timeinfo;
			localtime_s(&timeinfo, &rawtime);
			AllInfo[countPay1].P.year = 1900 + timeinfo.tm_year; //��
			AllInfo[countPay1].P.month = 1 + timeinfo.tm_mon;//��
			AllInfo[countPay1].P.day = timeinfo.tm_mday;   //��
			AllInfo[countPay1].P.hour = timeinfo.tm_hour;  //ʱ
			AllInfo[countPay1].P.min = timeinfo.tm_min; //��
			AllInfo[countPay1].P.spentMoney = a;
			countPay1 += 1;
			return true;
		}
		else {
			cout << "���㣬���ֵ����ʹ��" << endl;
			return false;
		}
	}
	void query(int a) {
		switch (a) {
		case 1: {
			cout << "�˻���Ϣ:" << endl;
			cout << "�ֿ���������" << OwnerName << endl;
			cout << "������ţ�" << CardNumber << endl;
			cout << "�ֿ��˵绰��" << OwnerTele << endl;
			cout << "��" << deposit << endl;
			cout << "͸֧��ȣ�" << OverdraftLimit << endl;
		}break;
		case 2: {
			cout << "�˻���ˮ��Ϣ:" << endl;
			cout << "֧����Ϣ:" << endl;
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
				cout << AllInfo[i].P.min <<"    "<< Location[AllInfo[i].P.countLocation]<<"֧��" << AllInfo[i].P.spentMoney << "Ԫ" << endl;
			}
			cout << "��ֵ��Ϣ:" << endl;
			for (int i = 0; i < countPay2; i++) {
				cout << AllInfo[i].T.TopUpMoney << "ͨ��" << TopUpMethod[AllInfo[i].T.countMethod] << "��ֵ" << endl;
			}
		}break;
		case 3: {
			cout << "�˻���Ϣ:" << endl;
			cout << "�ֿ���������" << OwnerName << endl;
			cout << "������ţ�" << CardNumber << endl;
			cout << "�ֿ��˵绰��" << OwnerTele << endl;
			cout << "��" << deposit << endl;
			cout << "͸֧��ȣ�" << OverdraftLimit << endl << endl;
			cout << "�˻���ˮ��Ϣ:" << endl;
			cout << "֧����Ϣ:" << endl;
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
				cout << AllInfo[i].P.min <<"    "<<Location[AllInfo[i].P.countLocation]<<"֧��" << AllInfo[i].P.spentMoney << "Ԫ" << endl;
			}
			if (countPay1 == 0) cout << "��" << endl;
			cout << "��ֵ��Ϣ:" << endl;
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
				cout << "ͨ��" << TopUpMethod[AllInfo[i].T.countMethod] << "��ֵ"<< AllInfo[i].T.TopUpMoney<<"Ԫ" << endl;
			}
			if (countPay2 == 0) cout << "��" << endl;
		} break;
		default: cout << "�������" << endl;
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
		cout << "ѧ��������" << campus_card::StudentName << endl;
		cout << "ѧ��ѧ�ţ�" << campus_card::StudentNumber << endl;
		cout << "רҵ���ƣ�" << campus_card::Major << endl;
		cout << "������" << campus_card::deposit << endl;
		cout << "������Ϣ:" << endl;
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
				Location[AllInfo[i].P.countLocation] << "֧��" 
				<< AllInfo[i].P.spentMoney << "Ԫ" << endl;
		}
		if (countPay1 == 0) cout << "��" << endl;
		cout << "��ֵ��Ϣ:" << endl;
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
			cout << "ͨ��" << TopUpMethod[AllInfo[i].T.countMethod];
			if (AllInfo[i].T.countMethod == 1) { cout << DClist[AllInfo[i].T.AccountPos].CardNumber; }
			cout<< "��ֵ" << AllInfo[i].T.TopUpMoney << "Ԫ" << endl;
		}
		if (countPay2 == 0) cout << "��" << endl;
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
		cout << "У԰����Ϣ:" << endl;
		CClist[campus_card_pos].query();
		for (int i = 0; i < Count_Deposit_Card; i++) {
			cout << "�󶨿�" << i <<":"<< endl;
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
