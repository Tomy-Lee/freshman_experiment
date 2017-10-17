#include<iostream>
#include<string>
#include<string.h>
#include<iomanip>
#include<Windows.h>
#include<cstdlib>
#include<stdio.h>
using namespace std;

void desktop();                            //�������� 
void campusdesk();
void depositdesk();

class Account{                             //��ˮ���� 
public:
	string adress;
	double amount;
	long id;
	long time;
	bool xiaofei;
	bool zhuanru;
	bool zhuanchu;
	bool cunru;
};

class Card{                              //����card�� 
public:
    Card() {}
    long id;
    string name;
    double overage;
    int listnum;
    Account *listarray;
    virtual void pay() {}
    virtual void inquire() {}
};

class Campuscard : public Card{                  //�̳���У԰���� 
public:
	Campuscard();
    void pay(string adress, double amount);
    void inquire();
    string school;
    bool isbinding;
    long bindid;
};

class Debitcard : public Card{                     //�̳��ഢ��� 
public:
    Debitcard();
    void pay(string adress, double amount); 
    void inquire();
    void transfers1(Debitcard &othercard);
    void transfers2(Campuscard &othercard);
    void debit(double amount);
private:
    long timee;
    double limit;                   //͸֧��� 
    double moneyed;                //����͸֧���� 
    double surplus;                 //ʣ���� 
};

class Bindingcard : public Campuscard, public Debitcard{                 //��ͬ����󶨿��� 
public:
	void pay(string adress, double amount, Debitcard *card1, int id1);
};  

Campuscard::Campuscard() {
    listarray = new Account[15];
    listnum = -1;
    isbinding = false;
}

void Campuscard :: pay(string adress, double amount) {
	long time;
    if(amount <= overage) {
        overage =overage - amount;
        listnum++;
        listarray[listnum].xiaofei = 1;
        listarray[listnum].adress = adress;
        listarray[listnum].amount = amount;
        cout<<"����������ʱ�䣨����20160529����"<<endl;
		cin>>time; 
		listarray[listnum].time = time;
    }
    else
        cout<<"����������ʧ�ܣ�"<<endl;
}
void Campuscard::inquire() {
    int i, j;
    cout<<" 1.У԰����Ϣ "<<endl;
    cout<<" 2.У԰�����Ѽ�¼ "<<endl;
    cout<<"����������ѡ��";
    cin>>i;
    switch (i) {
        case 1:
            cout <<"ѧ�� :"<<id<<endl;
			cout<<"ѧԺ :"<<school<<endl; 
            cout <<"���� :"<<name<<endl;
            cout<<"��� :"<<overage<<endl;
            cout <<"  �Ƿ�󶨴����";
            break;
        case 2:
            cout <<"����У԰�����Ѽ�¼���� :"<<endl;
                for (j = 0; j <= listnum; j++) {
                   if (listarray[j].xiaofei == 1)
                        cout<<listarray[j].time<<"����"<<listarray[j].adress<<"����"<<listarray[j].amount<<"Ԫ"<<endl;
                   if (listarray[j].zhuanchu == 1)
                         cout<<listarray[j].time<<"����Ϊ"<<listarray[j].id<<"�Ĵ��ת��"<<listarray[j].amount<<"Ԫ"<<endl;
                }
            break;
        default:
            cout<<"�������"<<endl;
    }
}

Debitcard::Debitcard() {
    limit = 1000; 
    moneyed = 0.0;
    surplus = 1000;
    listarray = new Account[15];
    listnum = -1;
    timee=0;
}

void Debitcard :: pay(string adress, double amount) {
	long time;
    if (amount <= overage) {
        overage -= amount;
        listnum++;
        listarray[listnum].xiaofei = 1;
        listarray[listnum].adress = adress;
        listarray[listnum].amount = amount;
        cout<<"����������ʱ�䣨����20160529����"<<endl;
		cin>>time; 
		listarray[listnum].time = time;
        cout<<"��� :"<<overage<<"Ԫ"<<endl;
    }
    else if (amount - overage <= surplus) {
        surplus -= amount - overage;
        moneyed += amount - overage;
        overage = 0.0;
        listnum++;
        listarray[listnum].xiaofei = 1;
        listarray[listnum].adress = adress;
        listarray[listnum].amount = amount;
        cout<<"����������ʱ�䣨����20160529����"<<endl;
		cin>>time; 
		listarray[listnum].time = time;
        cout<<"����͸֧"<<surplus<<"Ԫ"<<endl;
    }
    else
        cout<<"������͸֧���"<<endl;
}

void Debitcard :: inquire() {
    int i, j;
    cout<<"  1.�����Ϣ "<<endl;
    cout<<"  2.������Ѽ�¼ "<<endl;
    cout<<"������ѡ��";
    cin>>i;
    switch (i) {
        case 1:
            cout <<"����" <<id<<endl;
			cout<<"��������"<<timee<<endl;
			cout<<"����"<<name<<endl;
			cout<<"���"<<overage<<endl;
            cout <<"��͸֧���"<<limit<<endl;
			cout<<"��͸֧�Ľ��"<<moneyed<<endl; 
			cout<<"ʣ����"<<surplus<<endl;
            break;
        case 2:
            cout <<"���Ĵ�����Ѽ�¼���� :"<<endl;
            for (j = 0; j <= listnum; j++) {
                if (listarray[j].xiaofei == 1)
                    cout<<listarray[j].time<<"����"<<listarray[j].adress<<"����"<<listarray[j].amount<<"Ԫ"<<endl;
                if (listarray[j].zhuanru == 1)
                    cout<<listarray[j].time<<"������"<<listarray[j].id<<"ת��"<<listarray[j].amount<<"Ԫ"<<endl;
                if (listarray[j].zhuanchu == 1)
                    cout<<listarray[j].time<<"����"<<listarray[j].id<<"����ת��"<<listarray[j].amount<<"Ԫ"<<endl;
                if (listarray[j].cunru == 1)
                    cout<<listarray[j].time<<"���"<<listarray[j].amount<<"Ԫ"<<endl;
            }
            break;
        default:
            cout<<"�������"<<endl;
    }
}

void Debitcard :: transfers1(Debitcard &othercard) {
    double amount;
    long time;
    cout<<"������ת�˽�";
    cin>>amount;
    if (amount <= overage) {
        overage -= amount;
        othercard.overage += amount;
        listnum++;
        listarray[listnum].zhuanru = 1;
        listarray[listnum].id = othercard.id;
        listarray[listnum].amount = amount;
        cout<<"������ʱ�䣺"<<endl;
        cin>>time;
        listarray[listnum].time = time;
        othercard.listnum++;
        othercard.listarray[othercard.listnum].zhuanchu = 1;
        othercard.listarray[othercard.listnum].id = id;
        othercard.listarray[othercard.listnum].amount = amount;
        othercard.listarray[othercard.listnum].time = time;
        cout<<"ת�˳ɹ���������Ϊ"<<overage<<"Ԫ"<<endl;
    }
    else if (amount - overage <= surplus) {
        surplus -= amount - overage;
        moneyed += amount - overage;
        overage += amount;
        overage = 0.0;
        listnum++;
        listarray[listnum].zhuanru = 1;
        listarray[listnum].id = othercard.id;
        listarray[listnum].amount = amount;
        cout<<"������ʱ�䣺"<<endl;
        cin>>time;
        listarray[listnum].time = time;
        othercard.listnum++;
        othercard.listarray[othercard.listnum].zhuanchu = 1;
        othercard.listarray[othercard.listnum].id = id;
        othercard.listarray[othercard.listnum].amount = amount;
        othercard.listarray[othercard.listnum].time = time;
        cout<<"֧���ת�˳ɹ�������͸֧"<<surplus<<"Ԫ"<<endl;
    }
    else
        cout<<"�������"<<endl;
}

void Debitcard :: transfers2(Campuscard &othercard) {
	long time;
    double amount;
    cout<<"������ת�˵Ľ�";
    cin>>amount;
    if (amount <= overage) {
        overage -= amount;
        othercard.overage += amount;
        listnum++;
        listarray[listnum].zhuanru = 1;
        listarray[listnum].id = othercard.id;
        listarray[listnum].amount = amount;
        cout<<"������ʱ�䣺"<<endl;
        cin>>time;
        listarray[listnum].time = time;
        othercard.listnum++;
        othercard.listarray[othercard.listnum].zhuanchu = 1;
        othercard.listarray[othercard.listnum].id = id;
        othercard.listarray[othercard.listnum].amount = amount;
        othercard.listarray[othercard.listnum].time = time;
        cout<<"ת�˳ɹ���������Ϊ"<<overage<<"Ԫ"<<endl;
    }
    else if (amount - overage <= surplus) {
        surplus -= amount - overage;
        moneyed += amount - overage;
        overage += amount;
        overage = 0.0;
        listnum++;
        listarray[listnum].zhuanru = 1;
        listarray[listnum].id = othercard.id;
        listarray[listnum].amount = amount;
        cout<<"������ʱ�䣺"<<endl;
        cin>>time;
        listarray[listnum].time = time;
        othercard.listnum++;
        othercard.listarray[othercard.listnum].zhuanchu = 1;
        othercard.listarray[othercard.listnum].id = id;
        othercard.listarray[othercard.listnum].amount = amount;
        othercard.listarray[othercard.listnum].time = time;
        cout<<"֧���ת�˳ɹ�������͸֧"<<surplus<<"Ԫ"<<endl; 
    }
    else
        cout<<"�������"<<endl;
}

void Debitcard :: debit(double amount) {
	long time;
    overage += amount;
    cout<<"���ɹ������"<<overage<<"Ԫ"<<endl;
    listnum++;
        listarray[listnum].cunru = 1;
        listarray[listnum].amount = amount;
        cout<<"������ʱ�䣺"<<endl;
        cin>>time;
        listarray[listnum].time = time;
}

void Bindingcard::pay(string adress, double amount, Debitcard *card1, int id1) {
    card1[id1].pay(adress, amount);
}

int find_debitcard(Debitcard *card1, long id, int num) {           //��ѯ��� 
    int i, temp = 0, flag = 0;
    for (i = 0; i <= num; i++) {
        if (card1[i].id == id) {
            flag = 1;
            temp = i;
        }
    }
    if (flag == 1)
        return temp;
    else
        return -1;
}
int find_campuscard(Campuscard *card2, long id, int num) {                //��ѯУ԰�� 
    int i, temp = 0, flag = 0;
    for (i = 0; i <= num; i++) {
        if (card2[i].id == id) {
            flag = 1;
            temp = i;
        }
    }
    if (flag == 1)
        return temp;
    else
        return -1;
}

Campuscard card1[30];
Debitcard card2[30];
Bindingcard card3;

int main() {                        //������ 
	while(1==1) {
		desktop(); 
	}
	return 0;
}

void desktop() {                                 //��ʼ���溯�� 
	system("cls");
	int x;
    cout<<"                ��ӭ��½tomy leeУ԰������ϵͳ"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"   ��ѡ����Ӧ����,�����س�ȷ�ϣ�"<<endl;
    cout<<"               ***  1.У԰���˻�"<<endl;
    cout<<"               ***  2.����˻�    "<<endl;
    cout<<"               ***  3.�˳�ϵͳ"<<endl<<endl<<endl;
    cout<<"                                             ��л������"<<endl;
    cin>>x;
    system("cls");
    switch(x) {
    	case 1:{
    		campusdesk();
    	}break;
    	case 2:{
    		depositdesk();
    	}break;
    	case 3:{
    		cout<<"���˳�ϵͳ"<<endl;
    	}break;
    }
}

void campusdesk() {                      //У԰��������� 
    string name1, school1, adress1;
    long id1, id2, id3;
    int money1, flag;
    int cardnum = -1;
    int temp, caozuo;
    double amount1;
	system("cls");
	int y; 
	cout<<"                ��ӭ��½tomy leeУ԰������ϵͳ"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"   ��ѡ����Ӧ����,�����س�ȷ�ϣ�"<<endl;
    cout<<"               ***  1.����µ�У԰���˻�"<<endl;
    cout<<"               ***  2.У԰���˻���¼    "<<endl; 
    cin>>y;
    system("cls");
    switch(y) {
    	case 1:{
    		cout<<"������ѧԺ���ƣ�"<<endl;
            cin>>school1;
            cout<<"������ѧ��������"<<endl;
            cin>>name1;
            cout<<"������ѧ�ţ�"<<endl;
            cin>>id1;
            cout<<"��������Ϊ��У԰����ֵ�Ľ�";
            cin>>money1;
            cardnum++;
            card1[cardnum].school = school1;
            card1[cardnum].name = name1;
            card1[cardnum].id = id1;
            card1[cardnum].overage = money1;
            cout<<"�µ�У԰���˻�����ӣ�лл������"<<endl;   		
    	}break;
    	case 2:{
    		cout<<"������ѧ����ID��";
                cin>>id2;
                temp = find_campuscard(card1, id2, cardnum);
                if(temp == -1){ 
                    cout<<"�Բ��𣬸��˻������ڣ���ȷ�Ϻ��������롣"<<endl;
                    getchar();
				    } 
                else {
                   cout<<"�ɹ���¼����ѡ��:"<<endl;
                   while(1==1) { 
                    cout<<"1.֧��                2.��ѯ���Ѽ�¼"<<endl;
					cout<<"3.�󶨴��          4.�˳�"<<endl; 
					cin>>caozuo;
                    switch (caozuo) {
                            case 1:{                           
                                cout<<"���������ѵص㣺"<<endl;
                                cin>>adress1;
                                cout<<"���������ѽ�"<<endl;
                                cin>>amount1;
                                if (!card1[temp].isbinding  || (card1[temp].isbinding && amount1 <= card1[temp].overage))
                                                    card1[temp].pay(adress1, amount1);
                                else {
                                    card3.pay(adress1, amount1 - card1[temp].overage, card2, card1[temp].bindid);
                                    if (card1[temp].overage != 0)
                                             card1[temp].pay(adress1, card1[temp].overage);
                            }
                                }break;
                            case 2:
                                card1[temp].inquire();
                                break;
                            case 3:{ 
                                cout<<"�����뽫Ҫ�󶨵Ĵ���ţ�"<<endl;
                                cin>>id3;
                                flag = find_debitcard(card2, id3, cardnum);
                                if (flag == -1)
                                     cout<<"�˿������ڣ���ȷ�Ϻ������"<<endl;
                                else {
                                    card1[temp].isbinding = true;
                                    card1[temp].bindid = flag;
                                    cout<<"����Ѱ󶨳ɹ�"<<endl;
                                }
                                }break;
                            case 4 :{
                            	cout<<"���˳�����"<<endl;
                            	break;
                            }
                            default:
                                 cout<<"�������������²�����"<<endl;
                                 break;
                        } 
					}           
                }  		
    	}break;
    }
}

void depositdesk() {                       //����������
    string name1, adress1;
	long id1, id2, id3;
	double overage1, amount, amount1;
	int temp, caozuo, caozuo1, flag, cardnum=-1;
	system("cls");
	int y; 
	cout<<"                ��ӭ��½tomy leeУ԰������ϵͳ"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"   ��ѡ����Ӧ����,�����س�ȷ�ϣ�"<<endl;
    cout<<"               ***  1.����µĴ���˻�"<<endl;
    cout<<"               ***  2.����˻���¼    "<<endl; 
    cin>>y;
    system("cls");
    switch(y) {
    	case 1:{
    		    cout<<"�����뻧��������"<<endl;
                cin>>name1;
                cout<<"�����뿨�ţ�"<<endl;
                cin>>id1;
                cout<<"�������ֵ��"<<endl;
                cin>>overage1;
                cardnum++;
                card2[cardnum].name = name1;
                card2[cardnum].id = id1;
                card2[cardnum].overage = overage1;
                cout<<"�µĴ���˻���ӳɹ���Ĭ��Ϊ���˻�����1000Ԫ�Ŀ�͸֧��"<<endl;
        }break;
    	case 2:{
    		cout<<"�������¼���ţ�"<<endl;
                cin>>id2;
                temp = find_debitcard(card2, id2, cardnum);
                if (temp == -1) { 
                    cout<<"�˿������ڣ���ȷ�Ϻ������"<<endl;
                    getchar();
                    } 
                else {
                	cout<<"�ɹ���¼����ѡ��:"<<endl;
                	while(1==1) { 
                    cout<<"1.���                2.֧��"<<endl;
					cout<<"3.��ѯ���Ѽ�¼        4.ת��          5.�˳�"<<endl;
					cin>>caozuo;
                    switch (caozuo) {
                            case 1:
                                cout<<"����������Ҫ����Ľ�";
                                cin>>amount1;
                                card2[temp].debit(amount1);
                                break;
                            case 2:
                                cout<<"���������ѵص㣺"<<endl;
                                cin>>adress1;
                                cout<<"������֧����"<<endl;
                                cin>>amount1;
                                card2[temp].pay(adress1, amount1);
                                break;
                            case 3:
                                cout<<"   1 ת�˸�������� "<<endl;
                                cout<<"   2 ��ֵ������У԰�� "<<endl;
                                cout<<"������ѡ��"<<endl;
                                cin>>caozuo1;
                                switch (caozuo1) {
                                    case 1:
                                        cout<<"������ת��Ĵ���ţ�"<<endl ;
                                        cin>>id3;
                                        flag = find_debitcard(card2, id3, cardnum);
                                        if (flag == -1)
                                            cout<<"�������,��ȷ�Ϻ������"<<endl;
                                        else {
                                            card2[temp].transfers1(card2[flag]);
                                            cout<<"��ֵ�ɹ���"<<endl;
                                        }
                                        break;
                                    case 2:
                                        cout<<"��������Ҫת���У԰���ţ�"<<endl;
                                        cin>>id3;
                                        flag = find_campuscard(card1, id3, cardnum);
                                        if (flag == -1)
                                            cout<<"�������,��ȷ�Ϻ������"<<endl;
                                        else {
                                            card2[temp].transfers2(card1[flag]);
                                            cout<<"��ֵ�ɹ���"<<endl;
                                        }
                                        break;
                                    default:
                                        cout<<"���������ȷ�Ϻ������"<<endl;
                                }
                                break;
                            case 4:
                                card2[temp].inquire();
                                break;
                            case 5:
                            	cout<<"���˳�ϵͳ"<<endl;
								break; 
							default:
                                 cout<<"�������������²�����"<<endl;
                                 break;
                        }          
                    }
                } 
            }break;  		
    	}
}

