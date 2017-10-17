#include<iostream>
#include<string>
#include<string.h>
#include<iomanip>
#include<Windows.h>
#include<cstdlib>
#include<stdio.h>
using namespace std;

void desktop();                            //函数声明 
void campusdesk();
void depositdesk();

class Account{                             //流水账类 
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

class Card{                              //基类card类 
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

class Campuscard : public Card{                  //继承类校园卡类 
public:
	Campuscard();
    void pay(string adress, double amount);
    void inquire();
    string school;
    bool isbinding;
    long bindid;
};

class Debitcard : public Card{                     //继承类储蓄卡类 
public:
    Debitcard();
    void pay(string adress, double amount); 
    void inquire();
    void transfers1(Debitcard &othercard);
    void transfers2(Campuscard &othercard);
    void debit(double amount);
private:
    long timee;
    double limit;                   //透支额度 
    double moneyed;                //已用透支数额 
    double surplus;                 //剩余额度 
};

class Bindingcard : public Campuscard, public Debitcard{                 //共同子类绑定卡类 
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
        cout<<"请输入消费时间（例如20160529）："<<endl;
		cin>>time; 
		listarray[listnum].time = time;
    }
    else
        cout<<"超出余额，操作失败！"<<endl;
}
void Campuscard::inquire() {
    int i, j;
    cout<<" 1.校园卡信息 "<<endl;
    cout<<" 2.校园卡消费记录 "<<endl;
    cout<<"请输入您的选择：";
    cin>>i;
    switch (i) {
        case 1:
            cout <<"学号 :"<<id<<endl;
			cout<<"学院 :"<<school<<endl; 
            cout <<"姓名 :"<<name<<endl;
            cout<<"余额 :"<<overage<<endl;
            cout <<"  是否绑定储蓄卡：";
            break;
        case 2:
            cout <<"您的校园卡消费记录如下 :"<<endl;
                for (j = 0; j <= listnum; j++) {
                   if (listarray[j].xiaofei == 1)
                        cout<<listarray[j].time<<"您于"<<listarray[j].adress<<"消费"<<listarray[j].amount<<"元"<<endl;
                   if (listarray[j].zhuanchu == 1)
                         cout<<listarray[j].time<<"卡号为"<<listarray[j].id<<"的储蓄卡转账"<<listarray[j].amount<<"元"<<endl;
                }
            break;
        default:
            cout<<"输入错误"<<endl;
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
        cout<<"请输入消费时间（例如20160529）："<<endl;
		cin>>time; 
		listarray[listnum].time = time;
        cout<<"余额 :"<<overage<<"元"<<endl;
    }
    else if (amount - overage <= surplus) {
        surplus -= amount - overage;
        moneyed += amount - overage;
        overage = 0.0;
        listnum++;
        listarray[listnum].xiaofei = 1;
        listarray[listnum].adress = adress;
        listarray[listnum].amount = amount;
        cout<<"请输入消费时间（例如20160529）："<<endl;
		cin>>time; 
		listarray[listnum].time = time;
        cout<<"还可透支"<<surplus<<"元"<<endl;
    }
    else
        cout<<"超出可透支额度"<<endl;
}

void Debitcard :: inquire() {
    int i, j;
    cout<<"  1.储蓄卡信息 "<<endl;
    cout<<"  2.储蓄卡消费记录 "<<endl;
    cout<<"请输入选择：";
    cin>>i;
    switch (i) {
        case 1:
            cout <<"卡号" <<id<<endl;
			cout<<"发卡日期"<<timee<<endl;
			cout<<"姓名"<<name<<endl;
			cout<<"余额"<<overage<<endl;
            cout <<"可透支额度"<<limit<<endl;
			cout<<"已透支的金额"<<moneyed<<endl; 
			cout<<"剩余额度"<<surplus<<endl;
            break;
        case 2:
            cout <<"您的储蓄卡消费记录如下 :"<<endl;
            for (j = 0; j <= listnum; j++) {
                if (listarray[j].xiaofei == 1)
                    cout<<listarray[j].time<<"您于"<<listarray[j].adress<<"消费"<<listarray[j].amount<<"元"<<endl;
                if (listarray[j].zhuanru == 1)
                    cout<<listarray[j].time<<"给卡号"<<listarray[j].id<<"转账"<<listarray[j].amount<<"元"<<endl;
                if (listarray[j].zhuanchu == 1)
                    cout<<listarray[j].time<<"卡号"<<listarray[j].id<<"给您转账"<<listarray[j].amount<<"元"<<endl;
                if (listarray[j].cunru == 1)
                    cout<<listarray[j].time<<"存款"<<listarray[j].amount<<"元"<<endl;
            }
            break;
        default:
            cout<<"输入错误"<<endl;
    }
}

void Debitcard :: transfers1(Debitcard &othercard) {
    double amount;
    long time;
    cout<<"请输入转账金额：";
    cin>>amount;
    if (amount <= overage) {
        overage -= amount;
        othercard.overage += amount;
        listnum++;
        listarray[listnum].zhuanru = 1;
        listarray[listnum].id = othercard.id;
        listarray[listnum].amount = amount;
        cout<<"请输入时间："<<endl;
        cin>>time;
        listarray[listnum].time = time;
        othercard.listnum++;
        othercard.listarray[othercard.listnum].zhuanchu = 1;
        othercard.listarray[othercard.listnum].id = id;
        othercard.listarray[othercard.listnum].amount = amount;
        othercard.listarray[othercard.listnum].time = time;
        cout<<"转账成功！储蓄卡余额为"<<overage<<"元"<<endl;
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
        cout<<"请输入时间："<<endl;
        cin>>time;
        listarray[listnum].time = time;
        othercard.listnum++;
        othercard.listarray[othercard.listnum].zhuanchu = 1;
        othercard.listarray[othercard.listnum].id = id;
        othercard.listarray[othercard.listnum].amount = amount;
        othercard.listarray[othercard.listnum].time = time;
        cout<<"支额度转账成功！还可透支"<<surplus<<"元"<<endl;
    }
    else
        cout<<"超出额度"<<endl;
}

void Debitcard :: transfers2(Campuscard &othercard) {
	long time;
    double amount;
    cout<<"请输入转账的金额：";
    cin>>amount;
    if (amount <= overage) {
        overage -= amount;
        othercard.overage += amount;
        listnum++;
        listarray[listnum].zhuanru = 1;
        listarray[listnum].id = othercard.id;
        listarray[listnum].amount = amount;
        cout<<"请输入时间："<<endl;
        cin>>time;
        listarray[listnum].time = time;
        othercard.listnum++;
        othercard.listarray[othercard.listnum].zhuanchu = 1;
        othercard.listarray[othercard.listnum].id = id;
        othercard.listarray[othercard.listnum].amount = amount;
        othercard.listarray[othercard.listnum].time = time;
        cout<<"转账成功！储蓄卡余额为"<<overage<<"元"<<endl;
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
        cout<<"请输入时间："<<endl;
        cin>>time;
        listarray[listnum].time = time;
        othercard.listnum++;
        othercard.listarray[othercard.listnum].zhuanchu = 1;
        othercard.listarray[othercard.listnum].id = id;
        othercard.listarray[othercard.listnum].amount = amount;
        othercard.listarray[othercard.listnum].time = time;
        cout<<"支额度转账成功！还可透支"<<surplus<<"元"<<endl; 
    }
    else
        cout<<"超出额度"<<endl;
}

void Debitcard :: debit(double amount) {
	long time;
    overage += amount;
    cout<<"存款成功！余额"<<overage<<"元"<<endl;
    listnum++;
        listarray[listnum].cunru = 1;
        listarray[listnum].amount = amount;
        cout<<"请输入时间："<<endl;
        cin>>time;
        listarray[listnum].time = time;
}

void Bindingcard::pay(string adress, double amount, Debitcard *card1, int id1) {
    card1[id1].pay(adress, amount);
}

int find_debitcard(Debitcard *card1, long id, int num) {           //查询储蓄卡 
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
int find_campuscard(Campuscard *card2, long id, int num) {                //查询校园卡 
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

int main() {                        //主函数 
	while(1==1) {
		desktop(); 
	}
	return 0;
}

void desktop() {                                 //初始界面函数 
	system("cls");
	int x;
    cout<<"                欢迎登陆tomy lee校园卡管理系统"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"   请选择相应功能,并按回车确认："<<endl;
    cout<<"               ***  1.校园卡账户"<<endl;
    cout<<"               ***  2.储蓄卡账户    "<<endl;
    cout<<"               ***  3.退出系统"<<endl<<endl<<endl;
    cout<<"                                             感谢合作！"<<endl;
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
    		cout<<"已退出系统"<<endl;
    	}break;
    }
}

void campusdesk() {                      //校园卡管理界面 
    string name1, school1, adress1;
    long id1, id2, id3;
    int money1, flag;
    int cardnum = -1;
    int temp, caozuo;
    double amount1;
	system("cls");
	int y; 
	cout<<"                欢迎登陆tomy lee校园卡管理系统"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"   请选择相应功能,并按回车确认："<<endl;
    cout<<"               ***  1.添加新的校园卡账户"<<endl;
    cout<<"               ***  2.校园卡账户登录    "<<endl; 
    cin>>y;
    system("cls");
    switch(y) {
    	case 1:{
    		cout<<"请输入学院名称："<<endl;
            cin>>school1;
            cout<<"请输入学生姓名："<<endl;
            cin>>name1;
            cout<<"请输入学号："<<endl;
            cin>>id1;
            cout<<"请输入您为该校园卡充值的金额：";
            cin>>money1;
            cardnum++;
            card1[cardnum].school = school1;
            card1[cardnum].name = name1;
            card1[cardnum].id = id1;
            card1[cardnum].overage = money1;
            cout<<"新的校园卡账户已添加，谢谢合作！"<<endl;   		
    	}break;
    	case 2:{
    		cout<<"请输入学生卡ID：";
                cin>>id2;
                temp = find_campuscard(card1, id2, cardnum);
                if(temp == -1){ 
                    cout<<"对不起，该账户不存在，请确认后重新输入。"<<endl;
                    getchar();
				    } 
                else {
                   cout<<"成功登录！请选择:"<<endl;
                   while(1==1) { 
                    cout<<"1.支付                2.查询消费记录"<<endl;
					cout<<"3.绑定储蓄卡          4.退出"<<endl; 
					cin>>caozuo;
                    switch (caozuo) {
                            case 1:{                           
                                cout<<"请输入消费地点："<<endl;
                                cin>>adress1;
                                cout<<"请输入消费金额："<<endl;
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
                                cout<<"请输入将要绑定的储蓄卡号："<<endl;
                                cin>>id3;
                                flag = find_debitcard(card2, id3, cardnum);
                                if (flag == -1)
                                     cout<<"此卡不存在，请确认后操作。"<<endl;
                                else {
                                    card1[temp].isbinding = true;
                                    card1[temp].bindid = flag;
                                    cout<<"储蓄卡已绑定成功"<<endl;
                                }
                                }break;
                            case 4 :{
                            	cout<<"已退出操作"<<endl;
                            	break;
                            }
                            default:
                                 cout<<"输入有误，请重新操作。"<<endl;
                                 break;
                        } 
					}           
                }  		
    	}break;
    }
}

void depositdesk() {                       //储蓄卡管理界面
    string name1, adress1;
	long id1, id2, id3;
	double overage1, amount, amount1;
	int temp, caozuo, caozuo1, flag, cardnum=-1;
	system("cls");
	int y; 
	cout<<"                欢迎登陆tomy lee校园卡管理系统"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"   请选择相应功能,并按回车确认："<<endl;
    cout<<"               ***  1.添加新的储蓄卡账户"<<endl;
    cout<<"               ***  2.储蓄卡账户登录    "<<endl; 
    cin>>y;
    system("cls");
    switch(y) {
    	case 1:{
    		    cout<<"请输入户主姓名："<<endl;
                cin>>name1;
                cout<<"请输入卡号："<<endl;
                cin>>id1;
                cout<<"请输入充值金额："<<endl;
                cin>>overage1;
                cardnum++;
                card2[cardnum].name = name1;
                card2[cardnum].id = id1;
                card2[cardnum].overage = overage1;
                cout<<"新的储蓄卡账户添加成功！默认为该账户设置1000元的可透支金额。"<<endl;
        }break;
    	case 2:{
    		cout<<"请输入登录卡号："<<endl;
                cin>>id2;
                temp = find_debitcard(card2, id2, cardnum);
                if (temp == -1) { 
                    cout<<"此卡不存在，请确认后操作。"<<endl;
                    getchar();
                    } 
                else {
                	cout<<"成功登录！请选择:"<<endl;
                	while(1==1) { 
                    cout<<"1.存款                2.支付"<<endl;
					cout<<"3.查询消费记录        4.转账          5.退出"<<endl;
					cin>>caozuo;
                    switch (caozuo) {
                            case 1:
                                cout<<"请输入您所要存入的金额：";
                                cin>>amount1;
                                card2[temp].debit(amount1);
                                break;
                            case 2:
                                cout<<"请输入消费地点："<<endl;
                                cin>>adress1;
                                cout<<"请输入支付金额："<<endl;
                                cin>>amount1;
                                card2[temp].pay(adress1, amount1);
                                break;
                            case 3:
                                cout<<"   1 转账给其他储蓄卡 "<<endl;
                                cout<<"   2 充值给其他校园卡 "<<endl;
                                cout<<"请输入选择："<<endl;
                                cin>>caozuo1;
                                switch (caozuo1) {
                                    case 1:
                                        cout<<"请输入转入的储蓄卡号："<<endl ;
                                        cin>>id3;
                                        flag = find_debitcard(card2, id3, cardnum);
                                        if (flag == -1)
                                            cout<<"输入错误,请确认后操作。"<<endl;
                                        else {
                                            card2[temp].transfers1(card2[flag]);
                                            cout<<"充值成功！"<<endl;
                                        }
                                        break;
                                    case 2:
                                        cout<<"请输入所要转入的校园卡号："<<endl;
                                        cin>>id3;
                                        flag = find_campuscard(card1, id3, cardnum);
                                        if (flag == -1)
                                            cout<<"输入错误,请确认后操作。"<<endl;
                                        else {
                                            card2[temp].transfers2(card1[flag]);
                                            cout<<"充值成功！"<<endl;
                                        }
                                        break;
                                    default:
                                        cout<<"输入错误，请确认后操作！"<<endl;
                                }
                                break;
                            case 4:
                                card2[temp].inquire();
                                break;
                            case 5:
                            	cout<<"已退出系统"<<endl;
								break; 
							default:
                                 cout<<"输入有误，请重新操作。"<<endl;
                                 break;
                        }          
                    }
                } 
            }break;  		
    	}
}

