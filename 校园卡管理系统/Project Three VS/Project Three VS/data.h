#ifndef __Data_H__
#define __Data_H__
#include"functions.h"

void ReadInData() {
	ifstream CaCard;
	string qq;
	CaCard.open("campus_card.txt");
	if (!CaCard) cout << "No previous Campus Card" << endl;
	else {
		//cout << "in campus card" << endl;
		while (!CaCard.eof()) {
			class campus_card *newcard;
			newcard = new campus_card;
			string inMajor;
			string name;
			string number;
			double _deposit;
			int count1, count2;
			int count3;
			string password;
			string q;
			CaCard >> _deposit >> count1 >> count2 >> count3;
			getline(CaCard, qq);
			getline(CaCard, inMajor);
			getline(CaCard, name);
			getline(CaCard, number);
			getline(CaCard, password);
			newcard->Major = inMajor;
			newcard->StudentName = name;
			newcard->StudentNumber = number;
			newcard->deposit = _deposit;
			newcard->Password = password;
			newcard->countPay1 = count1;
			newcard->countPay2 = count2;
			newcard->countBindCard = count3;
			if(count1 != 0){
			for (int i = 0; i < count1; i++) {
				CaCard >> newcard->AllInfo[i].P.year
					>> newcard->AllInfo[i].P.month
					>> newcard->AllInfo[i].P.day
					>> newcard->AllInfo[i].P.hour
					>> newcard->AllInfo[i].P.min
					>> newcard->AllInfo[i].P.spentMoney
					>> newcard->AllInfo[i].P.countLocation;
				getline(CaCard, q);
			}
		}
			if (count2 != 0) {
				for (int i = 0; i < count2; i++) {
					CaCard >> newcard->AllInfo[i].T.year
						>> newcard->AllInfo[i].T.month
						>> newcard->AllInfo[i].T.day
						>> newcard->AllInfo[i].T.hour
						>> newcard->AllInfo[i].T.min
						>> newcard->AllInfo[i].T.TopUpMoney
						>> newcard->AllInfo[i].T.countMethod;
					if (newcard->AllInfo[i].T.countMethod == 1) CaCard >> newcard->AllInfo[i].T.AccountPos;
					getline(CaCard, q);
				}
			}
			if (count3 != 0) {
				for (int i = 0; i < count3; i++) {
					CaCard >> newcard->CardArr[i];
					getline(CaCard,q);
				}
			}
			CClist.push_back(*newcard);
		}
		CaCard.close();
	}
	ifstream DeCard;
	DeCard.open("deposit_card.txt");
	if (!DeCard) cout << "no previous Deposit Card" << endl;
	else {
		//cout << "in deposit card" << endl;
	while (!DeCard.eof()) {
		class deposit_card *newcard;
		newcard = new deposit_card;
		double _deposit, _OverdraftLimit;
		int count1, count2;
		string _CardNumber, _OwnerName, _OwnerTele, _Dpassword;
		DeCard >> _deposit >> _OverdraftLimit >> count1 >> count2;
		getline(DeCard, qq);
		getline(DeCard, _CardNumber);
		getline(DeCard, _OwnerName);
		getline(DeCard, _OwnerTele);
		getline(DeCard, _Dpassword);
		int a[1000], b[1000], c[1000], d[1000], e[1000],j[1000];
		double f[1000];
		if (count1 != 0) {
			for (int i = 0; i < count1; i++) {
				DeCard >> a[i] >> b[i] >> c[i] >> d[i] >> e[i] >> f[i] >> j[i];
				getline(DeCard, qq);
			}
		}
		//double g[1000];
		//int h[1000];
		if (count2 != 0) {
			for (int i = 0; i < count2; i++) {
				DeCard >> newcard->AllInfo[i].T.TopUpMoney 
					>>newcard->AllInfo[i].T.year >> newcard->AllInfo[i].T.month
					>> newcard->AllInfo[i].T.day>> newcard->AllInfo[i].T.hour
					>> newcard->AllInfo[i].T.min
					>>newcard->AllInfo[i].T.countMethod;
				getline(DeCard, qq);
			}
		}
		newcard->deposit = _deposit;
		newcard->countPay1 = count1;
		newcard->countPay2 = count2;
		newcard->OverdraftLimit = _OverdraftLimit;
		newcard->Password = _Dpassword;
		newcard->CardNumber = _CardNumber;
		newcard->OwnerName = _OwnerName;
		newcard->OwnerTele = _OwnerTele;
		if (count1 != 0) {
			for (int i = 0; i < count1; i++) {
				newcard->AllInfo[i].P.year = a[i]; //年
				newcard->AllInfo[i].P.month = b[i];//月
				newcard->AllInfo[i].P.day = c[i];   //日
				newcard->AllInfo[i].P.hour = d[i];  //时
				newcard->AllInfo[i].P.min = e[i]; //分
				newcard->AllInfo[i].P.spentMoney = f[i];
				newcard->AllInfo[i].P.countLocation = j[i];
			}
		}
		DClist.push_back(*newcard);
	}
	DeCard.close();
}
}
void savedata() {
	ofstream saveDeCard;
	saveDeCard.open("deposit_card.txt", ios::ate | ios::out);
	for (int i = 0; i < DClist.size(); i++) {
		saveDeCard << DClist[i].deposit << " " << DClist[i].OverdraftLimit << " " 
			<< DClist[i].countPay1 << " " << DClist[i].countPay2 << endl;
		saveDeCard << DClist[i].CardNumber << endl << DClist[i].OwnerName 
			<< endl << DClist[i].OwnerTele << endl << DClist[i].Password << endl;
		for (int j = 0; j < DClist[i].countPay1; j++) {
			saveDeCard << DClist[i].AllInfo[j].P.year
				<< " " << DClist[i].AllInfo[j].P.month
				<< " " << DClist[i].AllInfo[j].P.day
				<< " " << DClist[i].AllInfo[j].P.hour
				<< " " << DClist[i].AllInfo[j].P.min
				<< " " << DClist[i].AllInfo[j].P.spentMoney
				<< " " << DClist[i].AllInfo[j].P.countLocation;
			if (i == DClist.size()-1 && DClist[i].countPay2 == 0 && j == DClist[i].countPay1 - 1);
			else saveDeCard << endl;
		}
		for (int j = 0; j < DClist[i].countPay2; j++) {
			saveDeCard
				<< DClist[i].AllInfo[j].T.TopUpMoney << " "
				<< DClist[i].AllInfo[j].T.year << " "
				<< DClist[i].AllInfo[j].T.month << " "
				<< DClist[i].AllInfo[j].T.day << " "
				<< DClist[i].AllInfo[j].T.hour << " "
				<< DClist[i].AllInfo[j].T.min << " "
				<< DClist[i].AllInfo[j].T.countMethod;
			if (i == DClist.size()-1 && j == DClist[i].countPay2 - 1);
			else saveDeCard << endl;
		}
	}
	ofstream saveCaCard;
	saveCaCard.open("campus_card.txt", ios::ate | ios::out);
	for (int i = 0; i < CClist.size(); i++) {
		saveCaCard << CClist[i].deposit << " " << CClist[i].countPay1 << " " 
			       << CClist[i].countPay2 << " " << CClist[i].countBindCard << endl;
		saveCaCard << CClist[i].Major << endl << CClist[i].StudentName << endl 
			       << CClist[i].StudentNumber << endl << CClist[i].Password << endl;
		for (int j = 0; j < CClist[i].countPay1; j++) {
			saveCaCard << CClist[i].AllInfo[j].P.year
				<< " " << CClist[i].AllInfo[j].P.month
				<< " " << CClist[i].AllInfo[j].P.day
				<< " " << CClist[i].AllInfo[j].P.hour
				<< " " << CClist[i].AllInfo[j].P.min
				<< " " << CClist[i].AllInfo[j].P.spentMoney
				<< " " << CClist[i].AllInfo[j].P.countLocation;
			if (i == CClist.size() - 1 && CClist[i].countPay2 == 0 && j == CClist[i].countPay1 - 1);
			else saveCaCard << endl;
		}
		for (int j = 0; j < CClist[i].countPay2; j++) {
			saveCaCard
				<< CClist[i].AllInfo[j].T.year << " "
				<< CClist[i].AllInfo[j].T.month << " "
				<< CClist[i].AllInfo[j].T.day << " "
				<< CClist[i].AllInfo[j].T.hour << " "
				<< CClist[i].AllInfo[j].T.min << " "
				<< CClist[i].AllInfo[j].T.TopUpMoney << " "
				<< CClist[i].AllInfo[j].T.countMethod;
			if (CClist[i].AllInfo[j].T.countMethod == 1) saveCaCard <<" "<< CClist[i].AllInfo[j].T.AccountPos;
			if (i == CClist.size() - 1 && CClist[i].countBindCard == 0 && j == CClist[i].countPay2 - 1);
			else saveCaCard << endl;
		}
		for (int j = 0; j < CClist[i].countBindCard; j++) {
			saveCaCard << CClist[i].CardArr[j];
			if (i == CClist.size() - 1 && j == CClist[i].countBindCard - 1);
			else saveCaCard << endl;
		}
	}
}


#endif