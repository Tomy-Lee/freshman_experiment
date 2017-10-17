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
		double xishu[20];                 //����ʽ����ϵ�� 
		int mi[20];                      //����ʽ������ 
		string name;                     //����ʽ����
		polynomial() {                  //���캯�� 
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

ostream& operator <<(ostream &os, polynomial other){                //����<<����� 
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

polynomial& polynomial:: operator =(polynomial a) {                 //����= 
    int i;                 
	this->name = a.name;
	for (i = 0; i < 20; i++) {
		this->xishu[i] = a.xishu[i];
		this->mi[i] = a.mi[i];
	}
	return *this;
	
}

polynomial operator +(polynomial a1, polynomial a2) {             //����+�ӷ����� 
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

polynomial operator -(polynomial a1, polynomial a2) {             //����-�������� 
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

polynomial operator *(polynomial a1, polynomial a2) {            //����*����ʽ�˷����� 
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
  
polynomial operator *(polynomial b, int changshu) {              //����*����ʽ�볣���˻� 
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

bool operator == (polynomial a1, polynomial a2) {             //����==�ж϶���ʽ�Ƿ���� 
	int i;
	for(i = 0; i < 20; i++) {
		if(a1.xishu[i] != a2.xishu[i] || a1.mi[i] != a2.mi[i]){
			break;
			return false;
		} 
	} 
	return true;
}
 
polynomial polynomial::qiudao() { //�󵼺��� 
    	polynomial temp;
    	for (int i = 0; i <= 19; i++) {
    		temp.xishu[i] = xishu[i + 1] * mi[i + 1];
    		if (temp.xishu[i] != 0) {
    			temp.mi[i] = i;
			}
		}
		return temp;
}

double polynomial::qiuzhi(int a) {                                  //����ʽ��ֵ 
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
void desktop();                             //�Ӻ������� 
void readlist();
void baocun(polynomial other);
polynomial input();
void help();

int main() {                                    //������ 
    readlist(); 
    while( 1==1) {
          desktop();
    }
    return 0;
}

void desktop(){
	system("cls");
	int x;
    cout<<"                ��ӭʹ��tomy lee����ʽ����ϵͳ"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"   ��ѡ����Ӧ����,�����س�ȷ�ϣ�"<<endl;
    cout<<"               ***  1.�������ʽ    "<<endl;
    cout<<"               ***  2.����ʽ���    "<<endl;
    cout<<"               ***  3.����ʽ���    "<<endl;
    cout<<"               ***  4.����ʽ�볣���ĳ˷�����   "<<endl;
    cout<<"               ***  5.����ʽ��ֵ    "<<endl;
    cout<<"               ***  6.�����ʽ�˷�            "<<endl;
    cout<<"               ***  7.�ж϶���ʽ���    "<<endl;
    cout<<"               ***  8.����ʽ��   "<<endl;
    cout<<"               ***  9.��ʾ���д������ʽ    "<<endl;
    cout<<"               ***  10.����                 "<<endl;
    cout<<"               ***  0.�˳�ϵͳ                 "<<endl<<endl<<endl;
    cout<<"                                             ��лʹ�ã�"<<endl;
    cin>>x;
    system("cls");
    switch(x) {
    	case 1:{
    		char str;
    		string s;
    		polynomial temp;
    		cout<<"�밴��ʽ����һ������ʽ�� ����p=(1,2)(3,1) ����"<<endl;
			temp=input();
    		cout<<"�Ƿ񱣴��������ʽ�� Y or N"<<endl;
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"�������������ʽ�����֣������س����棺";
				cin>>s;
				temp.name=s;
				hehehe[geshu++]=temp;
				cout<<"����ɹ�"<<endl;
		        baocun(temp);
			    system("cls");  
			} 				
    	}break;
    	case 2:{
    		char str;
    		string s;
    		polynomial a, b, temp;
    		cout<<"�������һ������ʽ��";
			a=input(); 
    	    cout<<"������ڶ�������ʽ��"; 		
			b=input();	
    		temp = a + b;
    		cout<<"�������ǣ�"<<endl;
			cout<<temp<<endl;
			cout<<"�Ƿ񱣴��������ʽ�� Y or N"<<endl; 
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"�������������ʽ�����֣������س����棺";
				cin>>s;
				temp.name=s;
				hehehe[geshu++]=temp;
				cout<<"����ɹ�"<<endl;
		        baocun(temp);
			    system("cls"); 
			}
    		
    	}break;
    	case 3:{
    		char str;
    		string s;
    		polynomial a, b, temp;
    		cout<<"�������һ������ʽ��";
			a=input(); 
    	    cout<<"������ڶ�������ʽ��"; 		
			b=input();	
    		temp = a - b;
    		cout<<"�������ǣ�"<<endl;
			cout<<temp<<endl;
			cout<<"�Ƿ񱣴��������ʽ�� Y or N"<<endl; 
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"�������������ʽ�����֣������س����棺";
				cin>>s;
				temp.name=s;
				hehehe[geshu++]=temp;
				cout<<"����ɹ�"<<endl;
		        baocun(temp);
			    system("cls"); 
			}		
    		
    	}break;
    	case 4:{
    		int a;
    		char str;
    		string s;
    		polynomial temp;
    		cout<<"���������ʽ��"<<endl;
    		temp=input();
    		cout<<"�����볣����"<<endl;
			cin>>a;
			temp= temp * a;
			cout<<"�������ǣ�"<<endl;
			cout<<temp<<endl;
			cout<<"�Ƿ񱣴��������ʽ�� Y or N"<<endl; 
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"�������������ʽ�����֣������س����棺";
				cin>>s;
				temp.name=s;
				hehehe[geshu++]=temp;
				cout<<"����ɹ�"<<endl;
		        baocun(temp);
			    system("cls"); 
			}					
    	}break;
    	case 5:{
    		int a;
    		char str;
    		string s;
    		polynomial temp;
    		cout<<"���������ʽ��"<<endl;
    		temp=input();
    		cout<<"������x��ֵ��"<<endl;
			cin>>a;
			cout<<"�������ǣ�"<<endl;
			cout<<temp.qiuzhi(a)<<endl;
			cout<<"�Ƿ񱣴��������ʽ�� Y or N"<<endl; 
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"�������������ʽ�����֣������س����棺";
				cin>>s;
				temp.name=s;
				hehehe[geshu++]=temp;
				cout<<"����ɹ�"<<endl;
		        baocun(temp);
			}
    	}break;
    	case 6:{
    		char str;
    		string s;
    		polynomial a, b, temp;
    		cout<<"�������һ������ʽ��"<<endl;
    		a=input();
    		cout<<"������ڶ�������ʽ��"<<endl;
			b=input();
			temp = a * b;
			cout<<"�������ǣ�"<<endl;
			cout<<temp<<endl;
			cout<<"�Ƿ񱣴��������ʽ�� Y or N"<<endl; 
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"�������������ʽ�����֣������س����棺";
				cin>>s;
				temp.name=s;
				hehehe[geshu++]=temp;
				cout<<"����ɹ�"<<endl;
		        baocun(temp);
			}		
    	}break;
    	case 7:{
    		char str;
    		string s1, s2;
    		polynomial a, b;
    		cout<<"�������һ������ʽ��"<<endl;
    		a=input();
    		cout<<"������ڶ�������ʽ��"<<endl;
			b=input();
			if(a == b) {
				cout<<"��������ʽ���"<<endl; 
			}
			else cout<<"��������ʽ�����"<<endl; 
			cout<<"�Ƿ񱣴�����������ʽ�� Y or N"<<endl; 
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"�������һ��������ʽ�����֣������س����棺";
				cin>>s1;
				a.name=s1;
				hehehe[geshu++]=a;
				cout<<"��һ������ʽ����ɹ�"<<endl;
		        baocun(a);
		        cout<<"�������һ��������ʽ�����֣������س����棺";
				cin>>s2;
				b.name=s2;
				hehehe[geshu++]=b;
				cout<<"�ڶ�������ʽ����ɹ�"<<endl;
		        baocun(b);
			}			
    	}break;
    	case 8:{
    		char str;
    		string s;
    		polynomial temp;
    		cout<<"���������ʽ��"<<endl;
    		temp=input();
			cout<<"�������ǣ�"<<endl;
			cout<<temp.qiudao()<<endl;
			cout<<"�Ƿ񱣴��������ʽ�� Y or N"<<endl; 
			cin>>str;
			if(str == 'Y' || 'y') {
				cout<<"�������������ʽ�����֣������س����棺";
				cin>>s;
				temp.name=s;
				hehehe[geshu++]=temp;
				cout<<"����ɹ�"<<endl;
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
    		 cout<<"���˳�ϵͳ��"<<endl; 
    	    exit(0);
    	}break;
    	
    	default:{
		    cout<<"���������밴��ȷ��ʾ���룡"<<endl; 
		    system("pause");
		};    	
}
}

void help() {                        //������ 
	cout<< "����1���ж���ʽ����" << endl
		<< "����2���ж���ʽ�ӷ�" << endl
		<< "����3���ж���ʽ����"<< endl
		<< "����4���ж���ʽ�볣��������" << endl
		<< "����5���ж���ʽ��ֵ" << endl
		<< "����6���ж���ʽ�˷�" << endl
		<< "����7�ж���������ʽ�Ƿ����" << endl
		<< "����8���ж���ʽ��" <<endl
		<< "����9��ʾ��������ж���ʽ" <<endl
		<< "����10��ʾ����"<<endl
		<< "����0ֹͣ�������˳�ϵͳ"<<endl; 
}

void readlist() {                                 //��ȡlist�ж���ʽ��Ŀ 
    ifstream fin("list.txt");
	string name1;
	while(fin >> name1) {
	if (isalpha(name1[0]) && name1[1] != '\0') {   //�����ʽ��ȷʱ 
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
 
void baocun(polynomial other) {                                  //д�ļ���list
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

polynomial input() {                            //��ȡ��������Ķ���ʽ 
	        string name1;
			cin >> name1;			     
			if (name1[1] != '\0' && isalpha(name1[0])) {      //��ʽ��ȷʱ ,��p=()()() 
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
			else {                                          //��ʽ����ʱ 
			     int i;
			     for (i = 0; i < geshu; i++)
			        if (hehehe[geshu].name == name1) 
				        break;
			     if (i == geshu) 
					    cout << "������Ķ���ʽ����,���˳�ϵͳ����ѡ��"<<endl; 
			     return hehehe[geshu];
			}
}



