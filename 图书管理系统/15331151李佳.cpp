#include<iostream>
#include<cstdlib>
#include<string>
#include<string.h>
#include<fstream>
#include<Windows.h>
using namespace std;

struct Book{
	string name;                           //书名
	string author;                         //作者名 
	int num=0;                             //现有数量
	int total=0;                          //总库存 
};

Book book[1000];

void checkbook(string str);              //函数声明
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

void checkbook(string str) {                      //书名查找是否存在书目 
     int i;
     for(i=1; i<=shuliang; i++) {
         if(str==book[i].name) {
             cout<<"《"<<str<<"》";
             cout<<" 本书现库存 "<<book[i].num<<" 本。"<<endl;
             cout<<"回车键返回主菜单。"<<endl;
             break;
         }
     }
     if(i==shuliang+1) {
         cout<<"对不起，您所查找的书目不存在，请与图书管理员联系。"<<endl; 
         cout<<"回车键返回主菜单。"<<endl;
     }
     system("pause");
}
    
void checkauthor(string str) {                      //作者名查找是否存在书目 
     int i;
     for(i=1; i<=shuliang; i++) {
         if(str==book[i].author) {
             cout<<"《"<<book[i].name<<"》";
             cout<<" 本书现库存 "<<book[i].num<<" 本。"<<endl;
             cout<<"回车键返回主菜单。"<<endl;
             break;
         }
     }
     if(i==shuliang+1) {
         cout<<"对不起，您所查找的书目不存在，请与图书管理员联系。"<<endl; 
         cout<<"回车键返回主菜单。"<<endl;
     }
     system("pause");
}    
 
void borrowbook(string str){                          //借书 
	 int i;
     for(i=1; i<=shuliang; i++) {
         if(str==book[i].name) {
             if(book[i].num==0) {
                cout<<"对不起！您要借阅的书已经全部借阅出去，请过段时间再借。"<<endl;
                cout<<"回车键返回主菜单。"<<endl;
             }
             else {
                book[i].num--;
                cout<<"借阅成功"<<endl; 
                cout<<"本书预留数目为"<<book[i].num<<"，请按时归还，谢谢合作。"<<endl;
				cout<<"回车键返回主菜单。"<<endl; 
             } 
             break;
         }
     }
    if(i==shuliang+1)
    cout<<"抱歉，您要借阅的书不存在，请与图书管理员联系。"<<endl;
    cout<<"回车键返回主菜单。"<<endl;
    system("pause");
} 

void returnbook(string str){                      //还书 
	 int i;
     for(i=1; i<=shuliang; i++) {
         if(str==book[i].name) {
             book[i].num++;
             cout<<"归还成功"<<endl;
             cout<<"书目《"<<book[i].name<<"》的现有库存量为"<<book[i].num<<endl; 
             cout<<"回车键返回主菜单。"<<endl;
             break;
         }
     }
     if(i==shuliang+1)
     cout<<"暂时没有此类书目，请选择功能2进行添加，多谢合作。"<<endl;
     cout<<"回车键返回主菜单。"<<endl;
     system("pause");
}
 
void addbook(string str){                 //增加书 
	 int i;
     for(i=1; i<=shuliang; i++) {
         if(book[i].name==str) {
         	int a;
         	cout<<"请输入作者名："<<endl;
         	cin>>book[i].author;
         	cout<<"添加数目："<<endl;
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
         cout<<"请输入作者名："<<endl;
         	cin>>book[i].author;
         cout<<"添加数目："<<endl;
		 cin>>a; 
         book[i].num+=a;
         book[i].total+=a;
         shuliang++;
     }
     cout<<"添加成功"<<endl;
     cout<<"书目《"<<book[i].name<<"》的总库存为"<<book[i].total<<",目前有"<<book[i].num<<"本。\n"<<endl;
     cout<<"回车键返回主菜单。"<<endl;
     system("pause");
}

void delebook(string str){                         //删除书 
	 int i;
     for(i=1; i<=shuliang; i++) {
         if(str==book[i].name) {
            book[i].num--;
            book[i].total--;
            break;
         }
     }
     if(i==shuliang+1) {
         cout<<"对不起，未找到您要删除的书。"<<endl;
		 cout<<"回车键返回主菜单。"<<endl;	
     }
     if(book[i].total==0) {
         for(; i<shuliang; i++) {
            book[i]=book[i+1];
         }
         shuliang--;
         book[shuliang+1]=book[shuliang+2];
     }
     cout<<"书目《"<<str<<"》删除成功"<<endl;
     cout<<"回车键返回主菜单。"<<endl;
     system("pause");
}

void desktop(){                           //主菜单界面 
	system("cls");
	int x;
    cout<<"                欢迎登陆tomy lee图书管理系统"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"   请选择相应功能,并按回车确认："<<endl;
    cout<<"               ***  1.查找书目"<<endl;
    cout<<"               ***  2.借阅/归还    "<<endl;
    cout<<"               ***  3.增加/删除"<<endl<<endl<<endl;
    cout<<"                                             感谢合作！"<<endl;
    cin>>x;
    system("cls");
    switch(x){
          case 1: {
          	int m;
          	string str;
          	cout<<"请选择查找方式："<<endl;
	        cout<<"       1.书名查找        2.作者查找"<<endl; 
	        cin>>m;
	        switch(m){
	        	case 1:{
	        		cout<<"请输入书名："<<endl;
	        		cin>>str;
	        		checkbook(str);
	        		break;
	        	}
	        	case 2:{
	        		cout<<"请输入作者名："<<endl;
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
                 cout<<"请选择功能，并按回车确认："<<endl;
                 cout<<"            1.借阅          2.归还      "<<endl<<endl<<endl;

                 cin>>z;
                 if(z==1) {
                      cout<<"请输入书名，并按回车确认:"<<endl;
                      cin>>str; 
                    borrowbook(str);
             }
                else {
                     cout<<"请输入书名，并按回车确认:"<<endl;
                     cin>>str;
                     returnbook(str);
                }
                system("cls");
                  
    }break;
    case 3: {
               int y;
                   string str;
                   cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
                   cout<<"请选择功能，并按回车确认："<<endl;
                   cout<<"     1.增加            2.删除"<<endl<<endl<<endl;
                   cin>>y;
                          if(y==1) {
                                   cout<<"请输入书名，并按回车确认:"<<endl;
                                   cin>>str; 
                                   addbook(str);
                           }
                          else {
                                   cout<<"请输入书名，并按回车确认:"<<endl;
                                   cin>>str;
                                   delebook(str);
                          }
                  system("cls");  
    }break;
    }
}

void readlist() {                                 //读取booklist书目 
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

void baocun() {                         //写文件 
	int i;
    ofstream booklist2("booklist.txt",ios::out);
    booklist2<<"书目         作者     现有数量     总库存";
    for(i=1; i<=shuliang; i++) {
          booklist2<<endl;
          booklist2<<book[i].name<<"     "<<book[i].author<<"     "<<book[i].num<<"     "<<book[i].total<<endl;
    }
    booklist2.close();
} 

