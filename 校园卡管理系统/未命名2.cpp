//
//  main.cpp
//  У԰���ռ���
//
//  Created by superHMY on 16/5/25.
//  Copyright (c) 2016�� superHMY. All rights reserved.
//

#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
using namespace std;

const time_t t = time(NULL);
struct tm* current_time = localtime(&t);

class List {//��ˮ��Ϣ��¼
public:
    int flag1 = 0;//��¼ 1 ����ʱ�ε����Ѷ���
    int flag2 = 0;//��¼ 2 ����ʱת�˸�ĳ�˻�����Ǯ
    int flag3 = 0;//��¼ 3 ����ʱĳ�˻�ת�˸��Լ�����Ǯ
    int flag4 = 0;//��¼ 4 ����ʱ�ֽ������Ǯ
    string adress;//���ѵص�
    double amt;//���ѽ��
    long _id;//ת���˻�
    //����ʱ��
    int _year;
    int _mon;
    int _day;
    int hour;
    int min;
    int sec;
};

class card {//����
public:
    card() {}
    virtual void pay() {//֧������
    }
    virtual void query() {//��ѯ����
    }
    long id;//����
    string name;//�ֿ�������
    double balance;//���
    int list_num;//��ˮ��Ϣ����ĸ���
    List *ListArray;//��ˮ��Ϣ����
};

class campus_card : public card {
public:
    campus_card();//����һ��У԰���˻�
    void pay(string _adress, double amount);
    void query();//��ѯ 1 У԰�������Ϣ 2 У԰������ˮ��¼��Ϣ
    string college;//ѧԺ
    bool isBind;//�Ƿ�󶨴��
    long bindID;//�󶨵Ĵ���Ŀ���
};

class deposit_card : public card {
public:
    deposit_card();//����һ������˻�
    void pay(string _adress, double amount); //�øô��֧������֧���Ľ���������Ĳ�������Զ�ѡ��͸֧��������͸֧��������ʧ��
    void query();//��ѯ 1 ��������Ϣ 2 ֧���տ���ˮ��¼��Ϣ
    void transfer1(deposit_card &othercard);//ת�˸��������
    void transfer2(campus_card &othercard);//ת�˸�����У԰��
    void deposit(double amount);//�ֽ���
    int getYear() {return year; }
    int getMon() {return mon; }
    int getDay() {return day; }
private:
    //��������
    int year;
    int mon;
    int day;
    double overdraft_limit;//�ܵ�͸֧��ȣ������˻�ʱ�Ὣ͸֧�����Ϊ1000Ԫ
    double overdraft_money;//�ѱ�͸֧�Ķ��
    double overdraft_rest;//ʣ��Ŀ�͸֧���
};

class binding_card : public campus_card, public deposit_card {
public:
    void pay(string _adress, double amount, deposit_card *card1, int id1);//��У԰������ʱ������Ĳ�����ֱ��ʹ�ô��֧��
};

//������ܺ���
deposit_card::deposit_card() {
    year = current_time->tm_year + 1900;
    mon = current_time->tm_mon + 1;
    day = current_time->tm_mday;
    overdraft_limit = 1000; //��͸֧�����Ϊ1000
    overdraft_money = 0.0;
    overdraft_rest = 1000;
    ListArray = new List[15];
    list_num = -1;
}
void deposit_card::pay(string _adress, double amount) {
    if (amount <= balance) {
        balance -= amount;
        //������ˮ��Ϣ����
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
        cout<<"֧���ɹ���"<<endl;
        cout<<"�������Ϊ"<<balance<<"Ԫ"<<endl;
    }
    else if (amount - balance <= overdraft_rest) {
        overdraft_rest -= amount - balance;
        overdraft_money += amount - balance;
        balance = 0.0;
        //������ˮ��Ϣ����
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
        cout<<"������㣬ʹ��͸֧���֧���ɹ���"<<endl;
        cout<<"��������͸֧"<<overdraft_rest<<"Ԫ"<<endl;
    }
    else
        cout<<"֧��������͸֧��ȣ�����ʧ�ܣ�"<<endl;
}
void deposit_card::query() {
    int i, j;
    cout<<"                    --------------------------"<<endl;
    cout<<"                    | 1    ��������Ϣ    |"<<endl;
    cout<<"                    | 2 ֧���տ���ˮ��¼��Ϣ  |"<<endl;
    cout<<"                    --------------------------"<<endl;
    cout<<"����������ѡ��";
    cin>>i;
    switch (i) {
        case 1:
            cout <<"--------------------------------------------------------"<<endl;
            cout << setw(8) <<"����"<< setw(24) <<"��������"<< setw(24)<<"�ֿ�������"<<setw(15)<<"���"<<endl;
            cout <<"--------------------------------------------------------"<<endl;
            cout << setw(10) <<id<< setw(10) <<year<<"-"<<mon<<"-"<<day<< setw(15)<<name<<setw(13)<<balance<<endl;
            cout <<"--------------------------------------------------------"<<endl;
            cout <<"--------------------------------------------------------"<<endl;
            cout << setw(10) <<"��͸֧���"<< setw(30) <<"��͸֧�Ľ��"<< setw(34)<<"ʣ���͸֧���"<<endl;
            cout <<"--------------------------------------------------------"<<endl;
            cout << setw(10) <<overdraft_limit<< setw(20) <<overdraft_money<< setw(22)<<overdraft_rest<<endl;
            cout <<"--------------------------------------------------------"<<endl;
            break;
        case 2:
            cout <<"--------------------------------------------------------"<<endl;
            cout <<"����Ϊ"<<id<<"��"<<name<<"�û������Ĵ����ˮ��¼��Ϣ����"<<endl;
            cout <<"--------------------------------------------------------"<<endl;
            for (j = 0; j <= list_num; j++) {
                if (ListArray[j].flag1 == 1)
                    cout<<ListArray[j]._year<<"-"<<ListArray[j]._mon<<"-"<<ListArray[j]._day<<" "<<ListArray[j].hour<<":"<<ListArray[j].min<<":"<<ListArray[j].sec<<"  "
                    <<"����"<<ListArray[j].adress<<"������"<<ListArray[j].amt<<"Ԫ"<<endl;
                if (ListArray[j].flag2 == 1)
                    cout<<ListArray[j]._year<<"-"<<ListArray[j]._mon<<"-"<<ListArray[j]._day<<" "<<ListArray[j].hour<<":"<<ListArray[j].min<<":"<<ListArray[j].sec<<"  "
                    <<"��������Ϊ"<<ListArray[j]._id<<"���˻�ת����"<<ListArray[j].amt<<"Ԫ"<<endl;
                if (ListArray[j].flag3 == 1)
                    cout<<ListArray[j]._year<<"-"<<ListArray[j]._mon<<"-"<<ListArray[j]._day<<" "<<ListArray[j].hour<<":"<<ListArray[j].min<<":"<<ListArray[j].sec<<"  "
                    <<"����Ϊ"<<ListArray[j]._id<<"���˻�����ת����"<<ListArray[j].amt<<"Ԫ"<<endl;
                if (ListArray[j].flag4 == 1)
                    cout<<ListArray[j]._year<<"-"<<ListArray[j]._mon<<"-"<<ListArray[j]._day<<" "<<ListArray[j].hour<<":"<<ListArray[j].min<<":"<<ListArray[j].sec<<"  "
                    <<"�ֽ��� ת��"<<ListArray[j].amt<<"Ԫ"<<endl;
            }
            cout <<"--------------------------------------------------------"<<endl;
            break;
        default:
            cout<<"��������"<<endl;
    }
}
void deposit_card::transfer1(deposit_card &othercard) {
    double amount;
    cout<<"������ת�˵Ľ�";
    cin>>amount;
    if (amount <= balance) {
        balance -= amount;
        othercard.balance += amount;
        //������ˮ��Ϣ����
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
        //������ˮ��Ϣ������ת�˸��Ĵ����
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
        cout<<"ת�˳ɹ���"<<endl;
        cout<<"������Ϊ"<<balance<<"Ԫ"<<endl;
    }
    else if (amount - balance <= overdraft_rest) {
        overdraft_rest -= amount - balance;
        overdraft_money += amount - balance;
        othercard.balance += amount;
        balance = 0.0;
        //������ˮ��Ϣ����
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
        //������ˮ��Ϣ������ת�˸��Ĵ����
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
        cout<<"������㣬ʹ��͸֧���ת�˳ɹ���"<<endl;
        cout<<"��������͸֧"<<overdraft_rest<<"Ԫ"<<endl;
    }
    else
        cout<<"ת�˽�����͸֧��ȣ�����ʧ�ܣ�"<<endl;
}
void deposit_card::transfer2(campus_card &othercard) {
    double amount;
    cout<<"������ת�˵Ľ�";
    cin>>amount;
    if (amount <= balance) {
        balance -= amount;
        othercard.balance += amount;
        //������ˮ��Ϣ����
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
        //������ˮ��Ϣ������ת�˸���У԰����
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
        cout<<"ת�˳ɹ���"<<endl;
        cout<<"������Ϊ"<<balance<<"Ԫ"<<endl;
    }
    else if (amount - balance <= overdraft_rest) {
        overdraft_rest -= amount - balance;
        overdraft_money += amount - balance;
        othercard.balance += amount;
        balance = 0.0;
        //������ˮ��Ϣ����
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
        //������ˮ��Ϣ������ת�˸���У԰����
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
        cout<<"������㣬ʹ��͸֧���ת�˳ɹ���"<<endl;
        cout<<"��������͸֧"<<overdraft_rest<<"Ԫ"<<endl;
    }
    else
        cout<<"ת�˽�����͸֧��ȣ�����ʧ�ܣ�"<<endl;
}
void deposit_card::deposit(double amount) {
    balance += amount;
    cout<<"���ɹ������Ϊ"<<balance<<"Ԫ"<<endl;
    //������ˮ��Ϣ����
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

//У԰�����ܺ���
campus_card::campus_card() {
    ListArray = new List[15];
    list_num = -1;
    isBind = false;
}
void campus_card::pay(string _adress, double amount) {
    if (amount <= balance) {
        balance -= amount;
        //������ˮ��Ϣ����
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
        cout<<"֧������������ʧ�ܣ�"<<endl;
}
void campus_card::query() {
    int i, j;
    cout<<"                    --------------------------"<<endl;
    cout<<"                    | 1    У԰�������Ϣ    |"<<endl;
    cout<<"                    | 2    У԰����ˮ��¼    |"<<endl;
    cout<<"                    --------------------------"<<endl;
    cout<<"����������ѡ��";
    cin>>i;
    switch (i) {
        case 1:
            cout <<"-------------------------------------------------------------------"<<endl;
            cout << setw(6) <<"ѧ��"<< setw(24) <<"ѧԺ"<< setw(22)<<"����"<<setw(17)<<"���"<<endl;
            cout <<"-------------------------------------------------------------------"<<endl;
            cout << setw(10) <<id<< setw(14) <<college<< setw(20)<<name<<setw(13)<<balance<<endl;
            cout <<"-------------------------------------------------------------------"<<endl;
            cout <<"-------------------------------------------------------------------"<<endl;
            cout <<"  �Ƿ�󶨴����";
            if (isBind)
                cout<<"�ǡ�"<<endl;
            else
                cout<<"��"<<endl;
            cout <<"-------------------------------------------------------------------"<<endl;
            break;
        case 2:
            cout <<"------------------------------------------------------------"<<endl;
            cout <<"ѧ��Ϊ"<<id<<"��"<<name<<"ͬѧ������У԰����ˮ��¼��Ϣ����"<<endl;
            cout <<"------------------------------------------------------------"<<endl;
            for (j = 0; j <= list_num; j++) {
                if (ListArray[j].flag1 == 1)
                    cout<<ListArray[j]._year<<"-"<<ListArray[j]._mon<<"-"<<ListArray[j]._day<<" "<<ListArray[j].hour<<":"<<ListArray[j].min<<":"<<ListArray[j].sec<<"  "
                    <<"����"<<ListArray[j].adress<<"������"<<ListArray[j].amt<<"Ԫ"<<endl;
                if (ListArray[j].flag3 == 1)
                    cout<<ListArray[j]._year<<"-"<<ListArray[j]._mon<<"-"<<ListArray[j]._day<<" "<<ListArray[j].hour<<":"<<ListArray[j].min<<":"<<ListArray[j].sec<<"  "
                    <<"����Ϊ"<<ListArray[j]._id<<"�Ĵ���˻�����ת����"<<ListArray[j].amt<<"Ԫ"<<endl;
            }
            cout <<"------------------------------------------------------------"<<endl;
            break;
        default:
            cout<<"��������"<<endl;
    }
}

//binding_card��Ĺ��ܺ���
void binding_card::pay(string _adress, double amount, deposit_card *card1, int id1) {
    card1[id1].pay(_adress, amount);
}

void main_show() {
    cout<<"                    ------------------------------"<<endl;
    cout<<"                    |           ������            |"<<endl;
    cout<<"                    ------------------------------"<<endl;
    cout<<"                    |  1 ����һ���µĴ���˻�      |"<<endl;
    cout<<"                    |  2 ����һ���µ�У԰���˻�      |"<<endl;
    cout<<"                    |  3     ����˻���¼         |"<<endl;
    cout<<"                    |  4     У԰���˻���¼         |"<<endl;
    cout<<"                    |  5     ��ʾ���д��         |"<<endl;
    cout<<"                    |  6     ��ʾ����У԰��         |"<<endl;
    cout<<"                    |  7          �˳�            |"<<endl;
    cout<<"                    ------------------------------"<<endl;
}
void deposit_show() {
    cout<<"                    ------------------------------"<<endl;
    cout<<"                    |       ������ܽ���         |"<<endl;
    cout<<"                    ------------------------------"<<endl;
    cout<<"                    |  1       �ֽ���           |"<<endl;
    cout<<"                    |  2       ֧������           |"<<endl;
    cout<<"                    |  3       ת�˹���           |"<<endl;
    cout<<"                    |  4       ��ѯ����           |"<<endl;
    cout<<"                    |  5         �˳�            |"<<endl;
    cout<<"                    ------------------------------"<<endl;
}
void campus_show() {
    cout<<"                    ------------------------------"<<endl;
    cout<<"                    |       У԰�����ܽ���          |"<<endl;
    cout<<"                    ------------------------------"<<endl;
    cout<<"                    |  1       ֧������            |"<<endl;
    cout<<"                    |  2       ��ѯ����            |"<<endl;
    cout<<"                    |  3      �󶨴��           |"<<endl;
    cout<<"                    |  4         �˳�             |"<<endl;
    cout<<"                    ------------------------------"<<endl;
}
int find_deposit_card(deposit_card *card1, long _id, int top) {//���뿨���ҵ���Ӧ�Ĵ�������ظô���������е�inde�����Ҳ����򷵻�-1
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
int find_campus_card(campus_card *card2, long _id, int top) {//���뿨ѧ���ҵ���Ӧ��У԰�������ظ�У԰���������е�inde�����Ҳ����򷵻�-1
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
    int top1 = -1;//���������
    int top2 = -1;//У԰��������
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
        cout<<"����������ѡ��";
        cin>>choice;
        if (choice == 7) {
            cout<<"�ѳɹ��˳�ϵͳ��"<<endl;
            break;
        }
        switch(choice) {
            case 1:
                cout<<"�����뻧����������";
                cin>>name1;
                cout<<"��������˻��Ŀ��ţ�";
                cin>>id1;
                cout<<"��������Ϊ���˻���ֵ�Ľ�";
                cin>>balance1;
                top1++;
                card1[top1];//����һ������˻�
                card1[top1].name = name1;
                card1[top1].id = id1;
                card1[top1].balance = balance1;
                cout<<"����˻������ɹ���ϵͳ���Զ�Ϊ���˻�����1000Ԫ�Ŀ�͸֧��"<<endl;
                break;
            case 2:
                cout<<"�����������ڵ�ѧԺ���ƣ�";
                cin>>college2;
                cout<<"����������������";
                cin>>name2;
                cout<<"����������ѧ�ţ�";
                cin>>id2;
                cout<<"��������Ϊ��У԰����ֵ�Ľ�";
                cin>>balance2;
                top2++;
                card2[top2];//����һ��У԰���˻�
                card2[top2].college = college2;
                card2[top2].name = name2;
                card2[top2].id = id2;
                card2[top2].balance = balance2;
                cout<<"У԰���˻������ɹ���"<<endl;
                break;
            case 3:
                cout<<"������ô���Ŀ��ţ�";
                cin>>id1;
                temp = find_deposit_card(card1, id1, top1);
                if (temp == -1)
                    cout<<"�ÿ��Ų����ڣ�������������²�����"<<endl;
                else {
                    cout<<"��¼�ɹ�����ѡ����Ҫ�Ըô�����еĲ�����"<<endl;
                    while (1) {
                        deposit_show();
                        cout<<"����������ѡ��";
                        cin>>choice1;
                        switch (choice1) {
                            case 1:
                                cout<<"����������Ҫ����Ľ�";
                                cin>>amount;
                                card1[temp].deposit(amount);
                                break;
                            case 2:
                                cout<<"���������ѵص㣺";
                                cin>>_adress;
                                cout<<"������֧����";
                                cin>>amount;
                                card1[temp].pay(_adress, amount);
                                break;
                            case 3:
                                cout<<"                    ----------------------"<<endl;
                                cout<<"                    | 1 ת�˸�������� |"<<endl;
                                cout<<"                    | 2 ת�˸�����У԰�� |"<<endl;
                                cout<<"                    ----------------------"<<endl;
                                cout<<"����������ѡ��";
                                cin>>choice3;
                                switch (choice3) {
                                    case 1:
                                        cout<<"��������Ҫת��Ĵ���Ŀ��ţ�" ;
                                        cin>>id1;
                                        flag = find_deposit_card(card1, id1, top1);
                                        if (flag == -1)
                                            cout<<"�ÿ��Ų����ڣ�������������²�����"<<endl;
                                        else {
                                            card1[temp].transfer1(card1[flag]);
                                            cout<<"ת�˳ɹ���"<<endl;
                                        }
                                        break;
                                    case 2:
                                        cout<<"��������Ҫת���У԰���Ŀ��ţ�" ;
                                        cin>>id2;
                                        flag = find_campus_card(card2, id2, top2);
                                        if (flag == -1)
                                            cout<<"��ѧ�Ų����ڣ�������������²�����"<<endl;
                                        else {
                                            card1[temp].transfer2(card2[flag]);
                                            cout<<"ת�˳ɹ���"<<endl;
                                        }
                                        break;
                                    default:
                                        cout<<"������������²�����"<<endl;
                                }
                                break;
                            case 4:
                                card1[temp].query();
                                break;
                        }
                        if (choice1 == 5) {
                            cout<<"�ѳɹ��˳�����������棡"<<endl;
                            break;
                        }
                    }
                }
                break;
            case 4:
                cout<<"����������ѧ�ţ�";
                cin>>id2;
                temp = find_campus_card(card2, id2, top2);
                if (temp == -1)
                    cout<<"��ѧ�Ų����ڣ�������������²�����"<<endl;
                else {
                    cout<<"��¼�ɹ�����ѡ����Ҫ�Ը�У԰�����еĲ�����"<<endl;
                    while (1) {
                        campus_show();
                        cout<<"����������ѡ��";
                        cin>>choice2;
                        switch (choice2) {
                            case 1:
                                cout<<"���������ѵص㣺";
                                cin>>_adress;
                                cout<<"������֧����";
                                cin>>amount;
                                if (card2[temp].isBind == false || (card2[temp].isBind == true && amount <= card2[temp].balance))
                                    card2[temp].pay(_adress, amount);
                                else {//У԰�����㣬����Ĳ������ɰ󶨿�������а󶨵Ļ���֧��
                                    cout<<"У԰�����㣬��������ɰ󶨿�֧��"<<endl;
                                    card3.pay(_adress, amount - card2[temp].balance, card1, card2[temp].bindID);
                                    if (card2[temp].balance != 0)
                                        card2[temp].pay(_adress, card2[temp].balance);
                                }
                                break;
                            case 2:
                                card2[temp].query();
                                break;
                            case 3:
                                cout<<"��������Ҫ�󶨵Ĵ���Ŀ��ţ�";
                                cin>>id1;
                                flag = find_deposit_card(card1, id1, top1);
                                if (flag == -1)
                                    cout<<"�ÿ��Ų����ڣ�������������²�����"<<endl;
                                else {
                                    card2[temp].isBind = true;
                                    card2[temp].bindID = flag;
                                    cout<<"�󶨳ɹ���"<<endl;
                                }
                                break;
                        }
                        if (choice2 == 4) {
                            cout<<"�ѳɹ��˳�У԰���������棡"<<endl;
                            break;
                        }
                    }
                }
                break;
            case 5:
                cout <<"--------------------------------------------------------"<<endl;
                cout << setw(8) <<"����"<< setw(24) <<"��������"<< setw(24)<<"�ֿ�������"<<setw(15)<<"���"<<endl;
                cout <<"--------------------------------------------------------"<<endl;
                for (i = 0; i <= top1; i++) {
                    cout << setw(10) <<card1[i].id<< setw(10)<<card1[i].getYear()<<"-"<<card1[i].getMon()<<"-"<<card1[i].getDay()<< setw(15)<<card1[i].name<<setw(13)<<card1[i].balance<<endl;
                    cout <<"--------------------------------------------------------"<<endl;
                }
                break;
            case 6:
                cout <<"-------------------------------------------------------------------"<<endl;
                cout << setw(6) <<"ѧ��"<< setw(24) <<"ѧԺ"<< setw(22)<<"����"<<setw(17)<<"���"<<endl;
                cout <<"-------------------------------------------------------------------"<<endl;
                for (i = 0; i <= top2; i++) {
                    cout << setw(10) <<card2[i].id<< setw(14) <<card2[i].college<< setw(20)<<card2[i].name<<setw(13)<<card2[i].balance<<endl;
                    cout <<"-------------------------------------------------------------------"<<endl;
                }
                break;
            default:
                cout<<"������������²�����"<<endl;
                break;
        }
    }
    getchar();
    return 0;
}
