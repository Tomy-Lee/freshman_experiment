#include<iostream>
#include<cstdlib>
#include<string>
#include<string.h>
#include<fstream>
#include <math.h>
#include<Windows.h>
using namespace std;

class polynomial {
	public:
		double xishu[20];                 //多项式各次系数 
		int mi[20];                      //多项式各次幂 
		string name;                     //多项式名字
		polynomial() {                  //构造函数 
	          for(int i = 0; i < 20; i++) {
		           xishu[i] = 0.0; 
			       mi[i] = 0;
	          }
	          name = "";
        }                                    
	   friend ostream& operator <<(ostream &os, polynomial other); 
	   polynomial& operator =(polynomial a);   
	   friend polynomial operator +(polynomial a1, polynomial a2);
       friend polynomial operator -(polynomial a1, polynomial a2);  
       friend polynomial operator *(polynomial a1, polynomial a2);
       friend polynomial operator *(polynomial b, int changshu);
       friend bool operator == (polynomial a1, polynomial a2);
       polynomial qiudao();
       double qiuzhi(int a);
};

ostream& operator <<(ostream &os, polynomial other){                //重载<<输出流 
	int i, j;
	for(i=19; i>0; i--) {
		if(other.xishu[i] != 0) {
			os<<other.xishu[i]<<"x^"<<other.mi[i];
			break;
		}
	}
	for(j= i-1; j>0; j--) {
		if(other.xishu[j] > 0) {
			os<<'+'<<other.xishu[j]<<"x^"<<other.mi[j];
		}
		else if(other.xishu[j] < 0) {
			os<<other.xishu[j]<<"x^"<<other.mi[j];
		}
	}
   if(other.xishu[0] > 0) 
       os<<'+'<< other.xishu[0];
   else if(other.xishu[0] < 0) 
       os<<other.xishu[0];
   cout<<endl;
   return os;	
}

polynomial& polynomial:: operator =(polynomial a) {                 //重载= 
    int i;                 
	this->name = a.name;
	for (i = 0; i < 20; i++) {
		this->xishu[i] = a.xishu[i];
		this->mi[i] = a.mi[i];
	}
	return *this;
	
}

polynomial operator +(polynomial a1, polynomial a2) {             //重载+加法运算 
	int i;
	polynomial b;
	for(i = 0; i < 20; i++) {
		b.xishu[i]=a1.xishu[i]+a2.xishu[i];
		if (b.xishu[i] != 0) {
      	b.mi[i] = i;
	  }
	}
	return b;
}

polynomial operator -(polynomial a1, polynomial a2) {             //重载-减法运算 
    int i;
	polynomial b;
	for(i = 0; i < 20; i++) {
		b.xishu[i]=a1.xishu[i]-a2.xishu[i];
		if (b.xishu[i] != 0) {
      	b.mi[i] = i;
	  }
	}	
	return b;
}

polynomial operator *(polynomial a1, polynomial a2) {            //重载*多项式乘法运算 
	int i, j, mi2;
	polynomial b;
	for(i = 0; i < 20; i++) {
		for(j = 0; j < 20; j++) {
			mi2=a1.mi[i] + a2.mi[j];
			b.xishu[mi2]=a1.xishu[i] * a2.xishu[j];
			if (b.xishu[mi2] != 0)
			      b.mi[mi2] = mi2;
		    else  b.mi[mi2] = 0;
		}
	}
	return b;
} 
  
polynomial operator *(polynomial b, int changshu) {              //重载*多项式与常数乘积 
	int i;
	polynomial c;
	for(i = 0; i < 20; i++) {
		if(b.xishu[i] != 0) {
			c.xishu[i] = b.xishu[i] * changshu;
			c.mi[i] = b.mi[i];
		}
	}
	return c;
}  

bool operator == (polynomial a1, polynomial a2) {             //重载==判断多项式是否相等 
	int i;
	for(i = 0; i < 20; i++) {
		if(a1.xishu[i] != a2.xishu[i] || a1.mi[i] != a2.mi[i]){
			break;
			return false;
		} 
	} 
	return true;
}
 
polynomial polynomial::qiudao() { //求导函数 
    	polynomial temp;
    	for (int i = 0; i <= 19; i++) {
    		temp.xishu[i] = xishu[i + 1] * mi[i + 1];
    		if (temp.xishu[i] != 0) {
    			temp.mi[i] = i;
			}
		}
		return temp;
}

double polynomial::qiuzhi(int a) {                                  //多项式求值 
	double sum=0.0;
	int i;
	for(i = 0; i< 20; i++) {
		if(xishu[i] != 0) {
			sum = xishu[i] * pow(a, mi[i]);
		}
	}
	return sum;
}

polynomial hehehe[100];
int geshu; 
void desktop();                             //子函数声明 
void readlist();
void baocun(polynomial other);
polynomial input();
void help();

int main() {                                    //主函数 
    readlist(); 
    while( 1==1) {
          desktop();
    }
    return 0;
}

void desktop(){
	system("cls");
	int x;
    cout<<"                欢迎使用tomy lee多项式计算系统"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"   请选择相应功能,并按回车确认："<<endl;
    cout<<"               ***  1.输入多项式    "<<endl;
    cout<<"               ***  2.多项式相加    "<<endl;
    cout<<"               ***  3.多项式相减    "<<endl;
    cout<<"               ***  4.多项式与常数的乘法运算   "<<endl;
    cout<<"               ***  5.多项式求值    "<<endl;
    cout<<"               ***  6.求多项式乘法            "<<endl;
    cout<<"               ***  7.判断多项式相等    "<<endl;
    cout<<"               ***  8.多项式求导   "<<endl;
    cout<<"               ***  9.显示所有储存多项式    "<<endl;
    cout<<"               ***  10.帮助                 "<<endl;
    cout<<"               ***  0.退出系统                 "<<endl<<endl<<endl;
    cout<<"                                             感谢使用！"<<endl;
    cin>>x;
    system("cls");
    switch(x) {
    	case 1:{
    		char str;
    		string s;
    		polynomial temp;
    		cout<<"请按格式输入一个多项式（ 形如p=(1,2)(3,1) ）："<<endl;
			temp=input();
    		cout<<"是否保存这个多项式， Y or N"<<endl;
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"请输入这个多项式的名字，并按回车保存：";
				cin>>s;
				temp.name=s;
				hehehe[geshu++]=temp;
				cout<<"保存成功"<<endl;
		        baocun(temp);
			    system("cls");  
			} 				
    	}break;
    	case 2:{
    		char str;
    		string s;
    		polynomial a, b, temp;
    		cout<<"请输入第一个多项式：";
			a=input(); 
    	    cout<<"请输入第二个多项式："; 		
			b=input();	
    		temp = a + b;
    		cout<<"计算结果是："<<endl;
			cout<<temp<<endl;
			cout<<"是否保存这个多项式， Y or N"<<endl; 
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"请输入这个多项式的名字，并按回车保存：";
				cin>>s;
				temp.name=s;
				hehehe[geshu++]=temp;
				cout<<"保存成功"<<endl;
		        baocun(temp);
			    system("cls"); 
			}
    		
    	}break;
    	case 3:{
    		char str;
    		string s;
    		polynomial a, b, temp;
    		cout<<"请输入第一个多项式：";
			a=input(); 
    	    cout<<"请输入第二个多项式："; 		
			b=input();	
    		temp = a - b;
    		cout<<"计算结果是："<<endl;
			cout<<temp<<endl;
			cout<<"是否保存这个多项式， Y or N"<<endl; 
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"请输入这个多项式的名字，并按回车保存：";
				cin>>s;
				temp.name=s;
				hehehe[geshu++]=temp;
				cout<<"保存成功"<<endl;
		        baocun(temp);
			    system("cls"); 
			}		
    		
    	}break;
    	case 4:{
    		int a;
    		char str;
    		string s;
    		polynomial temp;
    		cout<<"请输入多项式："<<endl;
    		temp=input();
    		cout<<"请输入常数："<<endl;
			cin>>a;
			temp= temp * a;
			cout<<"计算结果是："<<endl;
			cout<<temp<<endl;
			cout<<"是否保存这个多项式， Y or N"<<endl; 
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"请输入这个多项式的名字，并按回车保存：";
				cin>>s;
				temp.name=s;
				hehehe[geshu++]=temp;
				cout<<"保存成功"<<endl;
		        baocun(temp);
			    system("cls"); 
			}					
    	}break;
    	case 5:{
    		int a;
    		char str;
    		string s;
    		polynomial temp;
    		cout<<"请输入多项式："<<endl;
    		temp=input();
    		cout<<"请输入x的值："<<endl;
			cin>>a;
			cout<<"计算结果是："<<endl;
			cout<<temp.qiuzhi(a)<<endl;
			cout<<"是否保存这个多项式， Y or N"<<endl; 
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"请输入这个多项式的名字，并按回车保存：";
				cin>>s;
				temp.name=s;
				hehehe[geshu++]=temp;
				cout<<"保存成功"<<endl;
		        baocun(temp);
			}
    	}break;
    	case 6:{
    		char str;
    		string s;
    		polynomial a, b, temp;
    		cout<<"请输入第一个多项式："<<endl;
    		a=input();
    		cout<<"请输入第二个多项式："<<endl;
			b=input();
			temp = a * b;
			cout<<"计算结果是："<<endl;
			cout<<temp<<endl;
			cout<<"是否保存这个多项式， Y or N"<<endl; 
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"请输入这个多项式的名字，并按回车保存：";
				cin>>s;
				temp.name=s;
				hehehe[geshu++]=temp;
				cout<<"保存成功"<<endl;
		        baocun(temp);
			}		
    	}break;
    	case 7:{
    		char str;
    		string s1, s2;
    		polynomial a, b;
    		cout<<"请输入第一个多项式："<<endl;
    		a=input();
    		cout<<"请输入第二个多项式："<<endl;
			b=input();
			if(a == b) {
				cout<<"两个多项式相等"<<endl; 
			}
			else cout<<"两个多项式不相等"<<endl; 
			cout<<"是否保存这两个多项式， Y or N"<<endl; 
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"请输入第一个个多项式的名字，并按回车保存：";
				cin>>s1;
				a.name=s1;
				hehehe[geshu++]=a;
				cout<<"第一个多项式保存成功"<<endl;
		        baocun(a);
		        cout<<"请输入第一个个多项式的名字，并按回车保存：";
				cin>>s2;
				b.name=s2;
				hehehe[geshu++]=b;
				cout<<"第二个多项式保存成功"<<endl;
		        baocun(b);
			}			
    	}break;
    	case 8:{
    		char str;
    		string s;
    		polynomial temp;
    		cout<<"请输入多项式："<<endl;
    		temp=input();
			cout<<"计算结果是："<<endl;
			cout<<temp.qiudao()<<endl;
			cout<<"是否保存这个多项式， Y or N"<<endl; 
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"请输入这个多项式的名字，并按回车保存：";
				cin>>s;
				temp.name=s;
				hehehe[geshu++]=temp;
				cout<<"保存成功"<<endl;
		        baocun(temp);
			    system("cls"); 
			}						
    	}break;
    	case 9:{
    		int i;
    		for (i = 0; i < geshu; i++)
    			cout << hehehe[i].name << ":" << hehehe[i] <<endl;
                system("pause");
    	}break;
    	case 10:{
    		help();
    		system("pause");
    	}break;
    	case 0:{
    		 cout<<"已退出系统！"<<endl; 
    	    exit(0);
    	}break;
    	
    	default:{
		    cout<<"输入有误，请按正确提示输入！"<<endl; 
		    system("pause");
		};    	
}
}

void help() {                        //帮助栏 
	cout<< "输入1进行多项式输入" << endl
		<< "输入2进行多项式加法" << endl
		<< "输入3进行多项式减法"<< endl
		<< "输入4进行多项式与常数的运算" << endl
		<< "输入5进行多项式求值" << endl
		<< "输入6进行多项式乘法" << endl
		<< "输入7判断两个多项式是否相等" << endl
		<< "输入8进行多项式求导" <<endl
		<< "输入9显示储存的所有多项式" <<endl
		<< "输入10显示帮助"<<endl
		<< "输入0停止操作并退出系统"<<endl; 
}

void readlist() {                                 //读取list中多项式项目 
    ifstream fin("list.txt");
	string name1;
	while(fin >> name1) {
	if (isalpha(name1[0]) && name1[1] != '\0') {   //输入格式正确时 
            string name2; 
			int i; 
			for(i = 0; i < name1.size(); i++)
		        if (name1[i] == '=') {
		            name2 = name1.substr(0, i);
			        break; 
		        }
			hehehe[geshu].name = name2;
			int k = 0;
			for(int j = 0; j < name1.size(); j++)
			    if (name1[j] == '(')
				    k++;
		    i = i + 1;
		    int l = 0; 	
			while(l != k) {
				int flag = 0;
			    if (name1[i + 1] == '-') {
				    flag = 1;
				    name1.replace(i + 1, 1, "");
			    }
               	int num1;
			    double num2;
			    num2 = name1[i + 1] - '0';
			    num1 = name1[i + 3] - '0';
				if (flag == 1)
			        num2 = -num2;
			    hehehe[geshu].mi[num1] = num1;
			    hehehe[geshu].xishu[num1] = num2;
			    i += 5;
			    l++;
			   }
	       geshu++;
	       }
	       name1 = "";
   }
   fin.close();
}
 
void baocun(polynomial other) {                                  //写文件进list
	int i;
	ofstream fout;
	fout.open("list.txt", ios::app);
	fout << other.name << '=';
    for (i = 19; i >0 ; i--) {	
	     if (other.xishu[i] != 0) {
	         fout << '(' <<other.xishu[i]<< ',' << other.mi[i] << ')';
	     } 
    }
   fout << endl;
   fout << flush; 
   fout.close();
} 

polynomial input() {                            //读取键盘输入的多项式 
	        string name1;
			cin >> name1;			     
			if (name1[1] != '\0' && isalpha(name1[0])) {      //格式正确时 ,即p=()()() 
			     string name2;
			     int i;
			     for(i = 0; i < name1.size(); i++)
		             if (name1[i] == '=') {
		                 name2 = name1.substr(0, i);
			             break; 
		             }
			     hehehe[geshu].name = name2;
			     int k = 0;
			     for(int j = 0; j < name1.size(); j++)
			        if (name1[j] == '(') 
					    k++;
		         i = i + 1;
		         int l = 0;
			     while(l != k) {
			        int num1;
					double num2;
			        int flag = 0;
			        if (name1[i + 1] == '-') {
				        flag = 1;
				        name1.replace(i + 1, 1, "");
			        }
			        num2 = name1[i + 1] - '0';
			        num1 = name1[i + 3] - '0';
			        if (flag == 1)
			             num2 = -num2;
			        hehehe[geshu].mi[num1] = num1;
			        hehehe[geshu].xishu[num1] = num2;
			        i += 5;
			        l++;
			     }
			     return hehehe[geshu++];
			}			
			else {                                          //格式错误时 
			     int i;
			     for (i = 0; i < geshu; i++)
			        if (hehehe[geshu].name == name1) 
				        break;
			     if (i == geshu) 
					    cout << "您输入的多项式有误,请退出系统重新选择"<<endl; 
			     return hehehe[geshu];
			}
}



