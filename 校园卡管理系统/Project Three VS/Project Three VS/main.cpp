#include<stdlib.h>
#include"DepositCardOp.h";
void caseOne() {
	admini.setAccount("admin");
	admini.setPassword("admin");
	admini.setAccess(1);
	ADlist.push_back(admini);
	ReadInData();
	int option;
	int type = 10;
	bool ifTrue = true;
	while (ifTrue) {
		cout << "��ѡ���¼��ʽ:" << endl << "1.У԰����¼" << endl << "2.�����¼" << endl << "3.����Ա��¼" << endl;
		cout << "4.�˳�ϵͳ" << endl;
		cin >> option;
		if (option == 3) {
			if (admin()) AdminOperation();
		}
		else if (option == 4) {
			savedata();
			break;
		}
		else {
			if (option > 4) cout << "ָ���������" << endl;
			else {
				type = login(option);
				if (type == 0) {
					cout << "���Ż��������" << endl;
				}
				else {
					switch (option) {
					case 1:StudentCampusCardAdmin(); break;
					case 2:StudentDepositCardAdmin(); break;
					}
				}
			}
		}
	}
	cout << "ϵͳ���˳�,ף���������" << endl;
	getchar();
	getchar();
}
void caseTwo(int a, int b) {
	ReadInData();
	class binding_card* newcard;
	newcard = new binding_card;
	newcard->campus_card_pos = a;
	newcard->deposit_card_pos[0] = b;
	newcard->deposit_card_pos[1] = 1;
	newcard->deposit_card_pos[2] = 2;
	newcard->Count_Deposit_Card = 3;
	BClist.push_back(*newcard);
	for (int i = 0; i < BClist.size(); i++) {
		BClist[i].query();
	}
	int i;
	cin >> i;
}
void caseThree() {
	for (int i = 0; i < BClist.size(); i++) {
		BClist[i].query();
	}
	int i;
	cin >> i;
}
int main() {
	caseOne();
}
