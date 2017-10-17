#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
using namespace std;

const time_t t = time(NULL);
struct tm* current_time = localtime(&t);

class List {
public:
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;
    int flag4 = 0;
    string adress;
    double amt;
    long _id;
    int _year;
    int _mon;
    int _day;
    int hour;
    int min;
    int sec;
};

class card {
public:
    card() {}
    virtual void pay() {
    }
    virtual void query() {
    }
    long id;
    string name;
    double balance;
    int list_num;
    List *ListArray;
};

class campus_card : public card {
public:
    campus_card();
    void pay(string _adress, double amount);
    void query();
    string college;
    bool isBind;
    long bindID;
};

class deposit_card : public card {
public:
    deposit_card();
    void pay(string _adress, double amount); 
    void query();
    void transfer1(deposit_card &othercard);
    void transfer2(campus_card &othercard);
    void deposit(double amount);
    int getYear() {return year; }
    int getMon() {return mon; }
    int getDay() {return day; }
private:
    int year;
    int mon;
    int day;
    double overdraft_limit;
    double overdraft_money;
    double overdraft_rest;
};

class binding_card : public campus_card, public deposit_card {
public:
    void pay(string _adress, double amount, deposit_card *card1, int id1);
};

deposit_card::deposit_card() {
    year = current_time->tm_year + 1900;
    mon = current_time->tm_mon + 1;
    day = current_time->tm_mday;
    overdraft_limit = 1000; 
    overdraft_money = 0.0;
    overdraft_rest = 1000;
    ListArray = new List[15];
    list_num = -1;
}
void deposit_card::pay(string _adress, double amount) {
    if (amount <= balance) {
        balance -= amount;
        list_num++;
        ListArray[list_num].flag1 = 1;
        ListArray[list_num].adress = _adress;
        ListArray[list_num].amt = amount;
        ListArray[list_num]._year = current_time->tm_year + 1900;
        ListArray[list_num]._mon = current_time->tm_mon + 1;
        ListArray[list_num]._day = current_time->tm_mday;
        ListArray[list_num].hour = current_time->tm_hour;
        ListArray[list_num].min = current_time->tm_min;
        ListArray[list_num].sec = current_time->tm_sec;
        cout<<"支付成功！"<<endl;
        cout<<"您的余额为"<<balance<<"元"<<endl;
    }
    else if (amount - balance <= overdraft_rest) {
        overdraft_rest -= amount - balance;
        overdraft_money += amount - balance;
        balance = 0.0;
        list_num++;
        ListArray[list_num].flag1 = 1;
        ListArray[list_num].adress = _adress;
        ListArray[list_num].amt = amount;
        ListArray[list_num]._year = current_time->tm_year + 1900;
        ListArray[list_num]._mon = current_time->tm_mon + 1;
        ListArray[list_num]._day = current_time->tm_mday;
        ListArray[list_num].hour = current_time->tm_hour;
        ListArray[list_num].min = current_time->tm_min;
        ListArray[list_num].sec = current_time->tm_sec;
        cout<<"储蓄卡余额不足，使用透支额度支付成功！"<<endl;
        cout<<"您还可以透支"<<overdraft_rest<<"元"<<endl;
    }
    else
         cout<<"支付金额超出可透支额度，操作失败！"<<endl;
}
void deposit_card::query() {
     int i, j;
    cout<<"                    --------------------------"<<endl;
    cout<<"                    | 1    储蓄卡相关信息    |"<<endl;
    cout<<"                    | 2 支付收款流水记录信息  |"<<endl;
    cout<<"                    --------------------------"<<endl;
    cout<<"请输入您的选择：";
    cin>>i;
    switch (i) {
        case 1:
            cout <<"--------------------------------------------------------"<<endl;
            cout << setw(8) <<"卡号"<< setw(24) <<"发卡日期"<< setw(24)<<"持卡人姓名"<<setw(15)<<"余额"<<endl;
            cout <<"--------------------------------------------------------"<<endl;
            cout << setw(10) <<id<< setw(10) <<year<<"-"<<mon<<"-"<<day<< setw(15)<<name<<setw(13)<<balance<<endl;
            cout <<"--------------------------------------------------------"<<endl;
            cout <<"--------------------------------------------------------"<<endl;
            cout << setw(10) <<"可透支额度"<< setw(30) <<"已透支的金额"<< setw(34)<<"剩余可透支额度"<<endl;
            cout <<"--------------------------------------------------------"<<endl;
            cout << setw(10) <<overdraft_limit<< setw(20) <<overdraft_money<< setw(22)<<overdraft_rest<<endl;
            cout <<"--------------------------------------------------------"<<endl;
            break;
        case 2:
            cout <<"--------------------------------------------------------"<<endl;
            cout <<"卡号为"<<id<<"的"<<name<<"用户，您的储蓄卡流水记录信息如下"<<endl;
            cout <<"--------------------------------------------------------"<<endl;
            for (j = 0; j <= list_num; j++) {
                if (ListArray[j].flag1 == 1)
                    cout<<ListArray[j]._year<<"-"<<ListArray[j]._mon<<"-"<<ListArray[j]._day<<" "<<ListArray[j].hour<<":"<<ListArray[j].min<<":"<<ListArray[j].sec<<"  "
                    <<"您在"<<ListArray[j].adress<<"消费了"<<ListArray[j].amt<<"元"<<endl;
                if (ListArray[j].flag2 == 1)
                    cout<<ListArray[j]._year<<"-"<<ListArray[j]._mon<<"-"<<ListArray[j]._day<<" "<<ListArray[j].hour<<":"<<ListArray[j].min<<":"<<ListArray[j].sec<<"  "
                    <<"您给卡号为"<<ListArray[j]._id<<"的账户转账了"<<ListArray[j].amt<<"元"<<endl;
                if (ListArray[j].flag3 == 1)
                    cout<<ListArray[j]._year<<"-"<<ListArray[j]._mon<<"-"<<ListArray[j]._day<<" "<<ListArray[j].hour<<":"<<ListArray[j].min<<":"<<ListArray[j].sec<<"  "
                    <<"卡号为"<<ListArray[j]._id<<"的账户给您转账了"<<ListArray[j].amt<<"元"<<endl;
                if (ListArray[j].flag4 == 1)
                    cout<<ListArray[j]._year<<"-"<<ListArray[j]._mon<<"-"<<ListArray[j]._day<<" "<<ListArray[j].hour<<":"<<ListArray[j].min<<":"<<ListArray[j].sec<<"  "
                    <<"现金存款 转入"<<ListArray[j].amt<<"元"<<endl;
            }
            cout <<"--------------------------------------------------------"<<endl;
            break;
        default:
            cout<<"输入有误！"<<endl;
    }
}
void deposit_card::transfer1(deposit_card &othercard) {
    double amount;
    cout<<"请输入转账的金额：";
    cin>>amount;
    if (amount <= balance) {
        balance -= amount;
        othercard.balance += amount;
        list_num++;
        ListArray[list_num].flag2 = 1;
        ListArray[list_num]._id = othercard.id;
        ListArray[list_num].amt = amount;
        ListArray[list_num]._year = current_time->tm_year + 1900;
        ListArray[list_num]._mon = current_time->tm_mon + 1;
        ListArray[list_num]._day = current_time->tm_mday;
        ListArray[list_num].hour = current_time->tm_hour;
        ListArray[list_num].min = current_time->tm_min;
        ListArray[list_num].sec = current_time->tm_sec;
        othercard.list_num++;
        othercard.ListArray[othercard.list_num].flag3 = 1;
        othercard.ListArray[othercard.list_num]._id = id;
        othercard.ListArray[othercard.list_num].amt = amount;
        othercard.ListArray[othercard.list_num]._year = current_time->tm_year + 1900;
        othercard.ListArray[othercard.list_num]._mon = current_time->tm_mon + 1;
        othercard.ListArray[othercard.list_num]._day = current_time->tm_mday;
        othercard.ListArray[othercard.list_num].hour = current_time->tm_hour;
        othercard.ListArray[othercard.list_num].min = current_time->tm_min;
        othercard.ListArray[othercard.list_num].sec = current_time->tm_sec;
        cout<<"转账成功！"<<endl;
        cout<<"储蓄卡余额为"<<balance<<"元"<<endl;
    }
    else if (amount - balance <= overdraft_rest) {
        overdraft_rest -= amount - balance;
        overdraft_money += amount - balance;
        othercard.balance += amount;
        balance = 0.0;
        list_num++;
        ListArray[list_num].flag2 = 1;
        ListArray[list_num]._id = id;
        ListArray[list_num].amt = amount;
        ListArray[list_num]._year = current_time->tm_year + 1900;
        ListArray[list_num]._mon = current_time->tm_mon + 1;
        ListArray[list_num]._day = current_time->tm_mday;
        ListArray[list_num].hour = current_time->tm_hour;
        ListArray[list_num].min = current_time->tm_min;
        ListArray[list_num].sec = current_time->tm_sec;
        othercard.list_num++;
        othercard.ListArray[othercard.list_num].flag3 = 1;
        othercard.ListArray[othercard.list_num]._id = id;
        othercard.ListArray[othercard.list_num].amt = amount;
        othercard.ListArray[othercard.list_num]._year = current_time->tm_year + 1900;
        othercard.ListArray[othercard.list_num]._mon = current_time->tm_mon + 1;
        othercard.ListArray[othercard.list_num]._day = current_time->tm_mday;
        othercard.ListArray[othercard.list_num].hour = current_time->tm_hour;
        othercard.ListArray[othercard.list_num].min = current_time->tm_min;
        othercard.ListArray[othercard.list_num].sec = current_time->tm_sec;
        cout<<"储蓄卡余额不足，使用透支额度转账成功！"<<endl;
        cout<<"您还可以透支"<<overdraft_rest<<"元"<<endl;
    }
    else
         cout<<"转账金额超出可透支额度，操作失败！"<<endl;
}
void deposit_card::transfer2(campus_card &othercard) {
    double amount;
    cout<<"请输入转账的金额：";
    cin>>amount;
    if (amount <= balance) {
        balance -= amount;
        othercard.balance += amount;
        list_num++;
        ListArray[list_num].flag2 = 1;
        ListArray[list_num]._id = othercard.id;
        ListArray[list_num].amt = amount;
        ListArray[list_num]._year = current_time->tm_year + 1900;
        ListArray[list_num]._mon = current_time->tm_mon + 1;
        ListArray[list_num]._day = current_time->tm_mday;
        ListArray[list_num].hour = current_time->tm_hour;
        ListArray[list_num].min = current_time->tm_min;
        ListArray[list_num].sec = current_time->tm_sec;
        othercard.list_num++;
        othercard.ListArray[othercard.list_num].flag3 = 1;
        othercard.ListArray[othercard.list_num]._id = id;
        othercard.ListArray[othercard.list_num].amt = amount;
        othercard.ListArray[othercard.list_num]._year = current_time->tm_year + 1900;
        othercard.ListArray[othercard.list_num]._mon = current_time->tm_mon + 1;
        othercard.ListArray[othercard.list_num]._day = current_time->tm_mday;
        othercard.ListArray[othercard.list_num].hour = current_time->tm_hour;
        othercard.ListArray[othercard.list_num].min = current_time->tm_min;
        othercard.ListArray[othercard.list_num].sec = current_time->tm_sec;
        cout<<"转账成功！"<<endl;
        cout<<"储蓄卡余额为"<<balance<<"元"<<endl;
    }
    else if (amount - balance <= overdraft_rest) {
        overdraft_rest -= amount - balance;
        overdraft_money += amount - balance;
        othercard.balance += amount;
        balance = 0.0;
        list_num++;
        ListArray[list_num].flag2 = 1;
        ListArray[list_num]._id = othercard.id;
        ListArray[list_num].amt = amount;
        ListArray[list_num]._year = current_time->tm_year + 1900;
        ListArray[list_num]._mon = current_time->tm_mon + 1;
        ListArray[list_num]._day = current_time->tm_mday;
        ListArray[list_num].hour = current_time->tm_hour;
        ListArray[list_num].min = current_time->tm_min;
        ListArray[list_num].sec = current_time->tm_sec;
        othercard.list_num++;
        othercard.ListArray[othercard.list_num].flag3 = 1;
        othercard.ListArray[othercard.list_num]._id = id;
        othercard.ListArray[othercard.list_num].amt = amount;
        othercard.ListArray[othercard.list_num]._year = current_time->tm_year + 1900;
        othercard.ListArray[othercard.list_num]._mon = current_time->tm_mon + 1;
        othercard.ListArray[othercard.list_num]._day = current_time->tm_mday;
        othercard.ListArray[othercard.list_num].hour = current_time->tm_hour;
        othercard.ListArray[othercard.list_num].min = current_time->tm_min;
        othercard.ListArray[othercard.list_num].sec = current_time->tm_sec;
        cout<<"储蓄卡余额不足，使用透支额度转账成功！"<<endl;
        cout<<"您还可以透支"<<overdraft_rest<<"元"<<endl;
    }
    else
         cout<<"转账金额超出可透支额度，操作失败！"<<endl;
}
void deposit_card::deposit(double amount) {
    balance += amount;
    cout<<"存款成功！余额为"<<balance<<"元"<<endl;
    list_num++;
    ListArray[list_num].flag4 = 1;
    ListArray[list_num].amt = amount;
    ListArray[list_num]._year = current_time->tm_year + 1900;
    ListArray[list_num]._mon = current_time->tm_mon + 1;
    ListArray[list_num]._day = current_time->tm_mday;
    ListArray[list_num].hour = current_time->tm_hour;
    ListArray[list_num].min = current_time->tm_min;
    ListArray[list_num].sec = current_time->tm_sec;
}

campus_card::campus_card() {
    ListArray = new List[15];
    list_num = -1;
    isBind = false;
}
void campus_card::pay(string _adress, double amount) {
    if (amount <= balance) {
        balance -= amount;
        list_num++;
        ListArray[list_num].flag1 = 1;
        ListArray[list_num].adress = _adress;
        ListArray[list_num].amt = amount;
        ListArray[list_num]._year = current_time->tm_year + 1900;
        ListArray[list_num]._mon = current_time->tm_mon + 1;
        ListArray[list_num]._day = current_time->tm_mday;
        ListArray[list_num].hour = current_time->tm_hour;
        ListArray[list_num].min = current_time->tm_min;
        ListArray[list_num].sec = current_time->tm_sec;
    }
    else
        cout<<"支付金额超出余额，操作失败！"<<endl;
}
void campus_card::query() {
    int i, j;
    cout<<"                    --------------------------"<<endl;
    cout<<"                    | 1    校园卡相关信息    |"<<endl;
    cout<<"                    | 2    校园卡流水记录    |"<<endl;
    cout<<"                    --------------------------"<<endl;
    cout<<"请输入您的选择：";
    cin>>i;
    switch (i) {
        case 1:
            cout <<"-------------------------------------------------------------------"<<endl;
            cout << setw(6) <<"学号"<< setw(24) <<"学院"<< setw(22)<<"姓名"<<setw(17)<<"余额"<<endl;
            cout <<"-------------------------------------------------------------------"<<endl;
            cout << setw(10) <<id<< setw(14) <<college<< setw(20)<<name<<setw(13)<<balance<<endl;
            cout <<"-------------------------------------------------------------------"<<endl;
            cout <<"-------------------------------------------------------------------"<<endl;
            cout <<"  是否绑定储蓄卡：";
            if (isBind)
                cout<<"是。"<<endl;
            else
                cout<<"否。"<<endl;
            cout <<"-------------------------------------------------------------------"<<endl;
            break;
        case 2:
            cout <<"------------------------------------------------------------"<<endl;
            cout <<"学号为"<<id<<"的"<<name<<"同学，您的校园卡流水记录信息如下"<<endl;
            cout <<"------------------------------------------------------------"<<endl;
            for (j = 0; j <= list_num; j++) {
                if (ListArray[j].flag1 == 1)
                    cout<<ListArray[j]._year<<"-"<<ListArray[j]._mon<<"-"<<ListArray[j]._day<<" "<<ListArray[j].hour<<":"<<ListArray[j].min<<":"<<ListArray[j].sec<<"  "
                    <<"您在"<<ListArray[j].adress<<"消费了"<<ListArray[j].amt<<"元"<<endl;
                if (ListArray[j].flag3 == 1)
                    cout<<ListArray[j]._year<<"-"<<ListArray[j]._mon<<"-"<<ListArray[j]._day<<" "<<ListArray[j].hour<<":"<<ListArray[j].min<<":"<<ListArray[j].sec<<"  "
                    <<"卡号为"<<ListArray[j]._id<<"的储蓄卡账户给您转账了"<<ListArray[j].amt<<"元"<<endl;
            }
            cout <<"------------------------------------------------------------"<<endl;
            break;
        default:
            cout<<"输入有误！"<<endl;
    }
}

void binding_card::pay(string _adress, double amount, deposit_card *card1, int id1) {
    card1[id1].pay(_adress, amount);
}

void main_show() {
    cout<<"                    ------------------------------"<<endl;
    cout<<"                    |           主界面            |"<<endl;
    cout<<"                    ------------------------------"<<endl;
    cout<<"                    |  1 创建一个新的储蓄卡账户      |"<<endl;
    cout<<"                    |  2 创建一个新的校园卡账户      |"<<endl;
    cout<<"                    |  3     储蓄卡账户登录         |"<<endl;
    cout<<"                    |  4     校园卡账户登录         |"<<endl;
    cout<<"                    |  5     显示所有储蓄卡         |"<<endl;
    cout<<"                    |  6     显示所有校园卡         |"<<endl;
    cout<<"                    |  7          退出            |"<<endl;
    cout<<"                    ------------------------------"<<endl;
}
void deposit_show() {
    cout<<"                    ------------------------------"<<endl;
    cout<<"                    |       储蓄卡功能界面         |"<<endl;
    cout<<"                    ------------------------------"<<endl;
    cout<<"                    |  1       现金存款           |"<<endl;
    cout<<"                    |  2       支付功能           |"<<endl;
    cout<<"                    |  3       转账功能           |"<<endl;
    cout<<"                    |  4       查询功能           |"<<endl;
    cout<<"                    |  5         退出            |"<<endl;
    cout<<"                    ------------------------------"<<endl;
}
void campus_show() {
    cout<<"                    ------------------------------"<<endl;
    cout<<"                    |       校园卡功能界面          |"<<endl;
    cout<<"                    ------------------------------"<<endl;
    cout<<"                    |  1       支付功能            |"<<endl;
    cout<<"                    |  2       查询功能            |"<<endl;
    cout<<"                    |  3      绑定储蓄卡           |"<<endl;
    cout<<"                    |  4         退出             |"<<endl;
    cout<<"                    ------------------------------"<<endl;
}
int find_deposit_card(deposit_card *card1, long _id, int top) {
    int i, temp = 0;
    int flag = 0;
    for (i = 0; i <= top; i++) {
        if (card1[i].id == _id) {
            flag = 1;
            temp = i;
        }
    }
    if (flag == 1)
        return temp;
    else
        return -1;
}
int find_campus_card(campus_card *card2, long _id, int top) {
    int i, temp = 0;
    int flag = 0;
    for (i = 0; i <= top; i++) {
        if (card2[i].id == _id) {
            flag = 1;
            temp = i;
        }
    }
    if (flag == 1)
        return temp;
    else
        return -1;
}

int main() {
    deposit_card card1[20];
    campus_card card2[20];
    binding_card card3;
    int top1 = -1;
    int top2 = -1;
    int choice, choice1, choice2, choice3, temp, i, flag;
    string name1;
    long id1;
    double balance1;
    string college2;
    string name2;
    long id2;
    double balance2;
    string _adress;
    double amount;
    while(1) {
        main_show();
        cout<<"请输入您的选择：";
        cin>>choice;
        if (choice == 7) {
            cout<<"已成功退出系统！"<<endl;
            break;
        }
        switch(choice) {
            case 1:
                cout<<"请输入户主的姓名：";
                cin>>name1;
                cout<<"请输入该账户的卡号：";
                cin>>id1;
                cout<<"请输入您为该账户充值的金额：";
                cin>>balance1;
                top1++;
                card1[top1];
                card1[top1].name = name1;
                card1[top1].id = id1;
                card1[top1].balance = balance1;
                cout<<"储蓄卡账户创建成功！系统已自动为该账户设置1000元的可透支金额。"<<endl;
                break;
            case 2:
                cout<<"请输入您所在的学院名称：";
                cin>>college2;
                cout<<"请输入您的姓名：";
                cin>>name2;
                cout<<"请输入您的学号：";
                cin>>id2;
                cout<<"请输入您为该校园卡充值的金额：";
                cin>>balance2;
                top2++;
                card2[top2];
                card2[top2].college = college2;
                card2[top2].name = name2;
                card2[top2].id = id2;
                card2[top2].balance = balance2;
                cout<<"校园卡账户创建成功！"<<endl;
                break;
            case 3:
                cout<<"请输入该储蓄卡的卡号：";
                cin>>id1;
                temp = find_deposit_card(card1, id1, top1);
                if (temp == -1)
                    cout<<"该卡号不存在，输入错误！请重新操作。"<<endl;
                else {
                    cout<<"登录成功！请选择您要对该储蓄卡进行的操作。"<<endl;
                    while (1) {
                        deposit_show();
                        cout<<"请输入您的选择：";
                        cin>>choice1;
                        switch (choice1) {
                            case 1:
                                cout<<"请输入您所要存入的金额：";
                                cin>>amount;
                                card1[temp].deposit(amount);
                                break;
                            case 2:
                                cout<<"请输入消费地点：";
                                cin>>_adress;
                                cout<<"请输入支付金额：";
                                cin>>amount;
                                card1[temp].pay(_adress, amount);
                                break;
                            case 3:
                                cout<<"                    ----------------------"<<endl;
                                cout<<"                    | 1 转账给其他储蓄卡 |"<<endl;
                                cout<<"                    | 2 转账给其他校园卡 |"<<endl;
                                cout<<"                    ----------------------"<<endl;
                                cout<<"请输入您的选择：";
                                cin>>choice3;
                                switch (choice3) {
                                    case 1:
                                        cout<<"请输入所要转入的储蓄卡的卡号：" ;
                                        cin>>id1;
                                        flag = find_deposit_card(card1, id1, top1);
                                        if (flag == -1)
                                            cout<<"该卡号不存在，输入错误！请重新操作。"<<endl;
                                        else {
                                            card1[temp].transfer1(card1[flag]);
                                            cout<<"转账成功！"<<endl;
                                        }
                                        break;
                                    case 2:
                                        cout<<"请输入所要转入的校园卡的卡号：" ;
                                        cin>>id2;
                                        flag = find_campus_card(card2, id2, top2);
                                        if (flag == -1)
                                            cout<<"该学号不存在，输入错误！请重新操作。"<<endl;
                                        else {
                                            card1[temp].transfer2(card2[flag]);
                                            cout<<"转账成功！"<<endl;
                                        }
                                        break;
                                    default:
                                        cout<<"输入错误，请重新操作！"<<endl;
                                }
                                break;
                            case 4:
                                card1[temp].query();
                                break;
                        }
                        if (choice1 == 5) {
                            cout<<"已成功退出储蓄卡操作界面！"<<endl;
                            break;
                        }
                    }
                }
                break;
            case 4:
                cout<<"请输入您的学号：";
                cin>>id2;
                temp = find_campus_card(card2, id2, top2);
                if (temp == -1)
                    cout<<"该学号不存在，输入错误！请重新操作。"<<endl;
                else {
                    cout<<"登录成功！请选择您要对该校园卡进行的操作。"<<endl;
                    while (1) {
                        campus_show();
                        cout<<"请输入您的选择：";
                        cin>>choice2;
                        switch (choice2) {
                            case 1:
                                cout<<"请输入消费地点：";
                                cin>>_adress;
                                cout<<"请输入支付金额：";
                                cin>>amount;
                                if (card2[temp].isBind == false || (card2[temp].isBind == true && amount <= card2[temp].balance))
                                    card2[temp].pay(_adress, amount);
                                else {
                                    cout<<"校园卡余额不足，多出部分由绑定卡支付"<<endl;
                                    card3.pay(_adress, amount - card2[temp].balance, card1, card2[temp].bindID);
                                    if (card2[temp].balance != 0)
                                        card2[temp].pay(_adress, card2[temp].balance);
                                }
                                break;
                            case 2:
                                card2[temp].query();
                                break;
                            case 3:
                                cout<<"请输入所要绑定的储蓄卡的卡号：";
                                cin>>id1;
                                flag = find_deposit_card(card1, id1, top1);
                                if (flag == -1)
                                    cout<<"该卡号不存在，输入错误！请重新操作。"<<endl;
                                else {
                                    card2[temp].isBind = true;
                                    card2[temp].bindID = flag;
                                    cout<<"绑定成功！"<<endl;
                                }
                                break;
                        }
                        if (choice2 == 4) {
                            cout<<"已成功退出校园卡操作界面！"<<endl;
                            break;
                        }
                    }
                }
                break;
            case 5:
                cout <<"--------------------------------------------------------"<<endl;
                cout << setw(8) <<"卡号"<< setw(24) <<"发卡日期"<< setw(24)<<"持卡人姓名"<<setw(15)<<"余额"<<endl;
                cout <<"--------------------------------------------------------"<<endl;
                for (i = 0; i <= top1; i++) {
                    cout << setw(10) <<card1[i].id<< setw(10)<<card1[i].getYear()<<"-"<<card1[i].getMon()<<"-"<<card1[i].getDay()<< setw(15)<<card1[i].name<<setw(13)<<card1[i].balance<<endl;
                    cout <<"--------------------------------------------------------"<<endl;
                }
                break;
            case 6:
                cout <<"-------------------------------------------------------------------"<<endl;
                cout << setw(6) <<"学号"<< setw(24) <<"学院"<< setw(22)<<"姓名"<<setw(17)<<"余额"<<endl;
                cout <<"-------------------------------------------------------------------"<<endl;
                for (i = 0; i <= top2; i++) {
                    cout << setw(10) <<card2[i].id<< setw(14) <<card2[i].college<< setw(20)<<card2[i].name<<setw(13)<<card2[i].balance<<endl;
                    cout <<"-------------------------------------------------------------------"<<endl;
                }
                break;
            default:
                cout<<"输入错误！请重新操作。"<<endl;
                break;
        }
    }
    getchar();
    return 0;
}
