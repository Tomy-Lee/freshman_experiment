#include<iostream>
#include<cstdlib>
#include<string>
#include<string.h>
#include<fstream>
#include<Windows.h>
using namespace std;

struct Book{
	string name;                           //����
	string author;                         //������ 
	int num=0;                             //��������
	int total=0;                          //�ܿ�� 
};

Book book[1000];

void checkbook(string str);              //��������
void checkauthor(string str);            
void borrowbook(string str);       
void returnbook(string str);
void addbook(string str);
void delebook(string str);
void desktop();
void readlist();
void baocun();

int shuliang=0;

int main() {
    readlist();
    while( 1==1) {
          desktop();
          baocun();
    }
    return 0;
}

void checkbook(string str) {                      //���������Ƿ������Ŀ 
     int i;
     for(i=1; i<=shuliang; i++) {
         if(str==book[i].name) {
             cout<<"��"<<str<<"��";
             cout<<" �����ֿ�� "<<book[i].num<<" ����"<<endl;
             cout<<"�س����������˵���"<<endl;
             break;
         }
     }
     if(i==shuliang+1) {
         cout<<"�Բ����������ҵ���Ŀ�����ڣ�����ͼ�����Ա��ϵ��"<<endl; 
         cout<<"�س����������˵���"<<endl;
     }
     system("pause");
}
    
void checkauthor(string str) {                      //�����������Ƿ������Ŀ 
     int i;
     for(i=1; i<=shuliang; i++) {
         if(str==book[i].author) {
             cout<<"��"<<book[i].name<<"��";
             cout<<" �����ֿ�� "<<book[i].num<<" ����"<<endl;
             cout<<"�س����������˵���"<<endl;
             break;
         }
     }
     if(i==shuliang+1) {
         cout<<"�Բ����������ҵ���Ŀ�����ڣ�����ͼ�����Ա��ϵ��"<<endl; 
         cout<<"�س����������˵���"<<endl;
     }
     system("pause");
}    
 
void borrowbook(string str){                          //���� 
	 int i;
     for(i=1; i<=shuliang; i++) {
         if(str==book[i].name) {
             if(book[i].num==0) {
                cout<<"�Բ�����Ҫ���ĵ����Ѿ�ȫ�����ĳ�ȥ�������ʱ���ٽ衣"<<endl;
                cout<<"�س����������˵���"<<endl;
             }
             else {
                book[i].num--;
                cout<<"���ĳɹ�"<<endl; 
                cout<<"����Ԥ����ĿΪ"<<book[i].num<<"���밴ʱ�黹��лл������"<<endl;
				cout<<"�س����������˵���"<<endl; 
             } 
             break;
         }
     }
    if(i==shuliang+1)
    cout<<"��Ǹ����Ҫ���ĵ��鲻���ڣ�����ͼ�����Ա��ϵ��"<<endl;
    cout<<"�س����������˵���"<<endl;
    system("pause");
} 

void returnbook(string str){                      //���� 
	 int i;
     for(i=1; i<=shuliang; i++) {
         if(str==book[i].name) {
             book[i].num++;
             cout<<"�黹�ɹ�"<<endl;
             cout<<"��Ŀ��"<<book[i].name<<"�������п����Ϊ"<<book[i].num<<endl; 
             cout<<"�س����������˵���"<<endl;
             break;
         }
     }
     if(i==shuliang+1)
     cout<<"��ʱû�д�����Ŀ����ѡ����2������ӣ���л������"<<endl;
     cout<<"�س����������˵���"<<endl;
     system("pause");
}
 
void addbook(string str){                 //������ 
	 int i;
     for(i=1; i<=shuliang; i++) {
         if(book[i].name==str) {
         	int a;
         	cout<<"��������������"<<endl;
         	cin>>book[i].author;
         	cout<<"�����Ŀ��"<<endl;
			 cin>>a; 
             book[i].num+=a;
             book[i].total+=a;
             break;
         }
     }
     if(i==shuliang+1) {
         book[i+1]=book[i];
         book[i].name=str;
         int a;
         cout<<"��������������"<<endl;
         	cin>>book[i].author;
         cout<<"�����Ŀ��"<<endl;
		 cin>>a; 
         book[i].num+=a;
         book[i].total+=a;
         shuliang++;
     }
     cout<<"��ӳɹ�"<<endl;
     cout<<"��Ŀ��"<<book[i].name<<"�����ܿ��Ϊ"<<book[i].total<<",Ŀǰ��"<<book[i].num<<"����\n"<<endl;
     cout<<"�س����������˵���"<<endl;
     system("pause");
}

void delebook(string str){                         //ɾ���� 
	 int i;
     for(i=1; i<=shuliang; i++) {
         if(str==book[i].name) {
            book[i].num--;
            book[i].total--;
            break;
         }
     }
     if(i==shuliang+1) {
         cout<<"�Բ���δ�ҵ���Ҫɾ�����顣"<<endl;
		 cout<<"�س����������˵���"<<endl;	
     }
     if(book[i].total==0) {
         for(; i<shuliang; i++) {
            book[i]=book[i+1];
         }
         shuliang--;
         book[shuliang+1]=book[shuliang+2];
     }
     cout<<"��Ŀ��"<<str<<"��ɾ���ɹ�"<<endl;
     cout<<"�س����������˵���"<<endl;
     system("pause");
}

void desktop(){                           //���˵����� 
	system("cls");
	int x;
    cout<<"                ��ӭ��½tomy leeͼ�����ϵͳ"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"   ��ѡ����Ӧ����,�����س�ȷ�ϣ�"<<endl;
    cout<<"               ***  1.������Ŀ"<<endl;
    cout<<"               ***  2.����/�黹    "<<endl;
    cout<<"               ***  3.����/ɾ��"<<endl<<endl<<endl;
    cout<<"                                             ��л������"<<endl;
    cin>>x;
    system("cls");
    switch(x){
          case 1: {
          	int m;
          	string str;
          	cout<<"��ѡ����ҷ�ʽ��"<<endl;
	        cout<<"       1.��������        2.���߲���"<<endl; 
	        cin>>m;
	        switch(m){
	        	case 1:{
	        		cout<<"������������"<<endl;
	        		cin>>str;
	        		checkbook(str);
	        		break;
	        	}
	        	case 2:{
	        		cout<<"��������������"<<endl;
	        		cin>>str;
	        		checkauthor(str);
	        		break;
	        	}
	        }
                               
    }break;
          case 2: {
          	     int z;
                 string str;
                 cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
                 cout<<"��ѡ���ܣ������س�ȷ�ϣ�"<<endl;
                 cout<<"            1.����          2.�黹      "<<endl<<endl<<endl;

                 cin>>z;
                 if(z==1) {
                      cout<<"�����������������س�ȷ��:"<<endl;
                      cin>>str; 
                    borrowbook(str);
             }
                else {
                     cout<<"�����������������س�ȷ��:"<<endl;
                     cin>>str;
                     returnbook(str);
                }
                system("cls");
                  
    }break;
    case 3: {
               int y;
                   string str;
                   cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
                   cout<<"��ѡ���ܣ������س�ȷ�ϣ�"<<endl;
                   cout<<"     1.����            2.ɾ��"<<endl<<endl<<endl;
                   cin>>y;
                          if(y==1) {
                                   cout<<"�����������������س�ȷ��:"<<endl;
                                   cin>>str; 
                                   addbook(str);
                           }
                          else {
                                   cout<<"�����������������س�ȷ��:"<<endl;
                                   cin>>str;
                                   delebook(str);
                          }
                  system("cls");  
    }break;
    }
}

void readlist() {                                 //��ȡbooklist��Ŀ 
    char readin[200];
    int num=0,i;
    ifstream booklist1("booklist.txt");
    booklist1.getline(readin,100);
    while(!booklist1.eof()) {
           num++;
           booklist1.getline(readin,100);
           book[num].name=readin;
           booklist1.getline(readin,100);
           book[num].author=readin;
           booklist1.getline(readin,100);
           book[num].num=readin[0]-48;
           booklist1.getline(readin,100);
           book[num].total=readin[0]-48;
    }
    booklist1.close();
    shuliang=num;
}

void baocun() {                         //д�ļ� 
	int i;
    ofstream booklist2("booklist.txt",ios::out);
    booklist2<<"��Ŀ         ����     ��������     �ܿ��";
    for(i=1; i<=shuliang; i++) {
          booklist2<<endl;
          booklist2<<book[i].name<<"     "<<book[i].author<<"     "<<book[i].num<<"     "<<book[i].total<<endl;
    }
    booklist2.close();
} 

