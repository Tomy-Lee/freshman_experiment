#include<iostream>
#include<string.h>
#include<math.h> 
#include <cstdlib>
using namespace std;
int number=-1;
class Ploynomial
{
public:
		double a[20];
	    string name ;
	    Ploynomial(){
	    	int i;
	    	for (i = 0; i < 20; i ++)
	    	a[i] = 0.0;
	    	name = "";
	    	}
	    void operator+(Ploynomial);
		void operator-(Ploynomial);
		void operator*(int );
	    double dairux(int);	
		double qiudao(Ploynomial);
		double equal(Ploynomial,Ploynomial);
	    

};
void printp(double *array){
	int first=0;
	for( int i=19;i>0;i--){
		if(array[i]==0)
		continue;
		if (array[i] > 0)
		{
			if (array[i] == 1){
				if(first !=0)
				{
					cout<<"+"; 
				} 
			}
			
			else
			{
				if(first != 0)
				{
					cout << "+" << array[i];
				}
				if (first == 0)
				{
					cout << array[i];
					first = 1;
				}
			}
		}
		if (array[i] < 0)
		{
			cout << array[i];
			first = 1;
		}
		cout << "x^" << i; 
	}
	if (array[0] > 0)
	{
		cout << "+" << array[0] << endl;
	}
	if (array[0] < 0)
	{
		cout << "-" << array[0] << endl;
	}
	cout<<endl;
}

void Ploynomial::operator+(Ploynomial obj1){
	double out[20],ab[20];
	int i;
	for(int i=0;i<20;i++){
		ab[i]=a[i];
	}
	for( i=0;i<20;i++){
		out[i]=ab[i]+obj1.a[i];
	}
	printp(out);
}

void Ploynomial::operator-(Ploynomial obj1){
		double out[20],ab[20];
	int i;
	for(int i=0;i<20;i++){
		ab[i]=a[i];
	}
	for( i=0;i<20;i++){
		out[i]=ab[i]-obj1.a[i];
	}
	printp(out);
}

void Ploynomial::operator*(int n){
	double ab[20];
	for(int i=0;i<20;i++){
		ab[i]=a[i];
	}
	for(int i=0;i<20;i++){
		ab[i]*= n;
	}
	printp(ab);
}

double Ploynomial::dairux(int x1){
	double sum=0;
	for(int i = 0 ;i<20; i++){
		sum = sum + this->a[i]*pow(x1 , i);
	}
	return sum;
}


Ploynomial xn[20]; 

void read (string in,double *store,string &nam)
{
	string sxi, sci;
	int ici;
	double dxi;
	nam = in.substr (0, in.find ("="));
    for ( ; ; )
	{
		sxi = in.substr (in.find ("(") + 1, in.find (",") - in.find ("(") - 1);
		sci = in.substr (in.find (",") + 1, in.find (")") - in.find (",") - 1);
		dxi = atof (sxi.c_str ());
		ici = atoi (sci.c_str ());
		store[ici] = store[ici]+dxi;
		in = in.substr (in.find (")") + 1);
		if (in == "")
		{
			break;
		}
	}
}

int createp(){
	cout<<"请输入多项式（格式如：r=（1,2）（2,1））："<<endl;
	string x;
	cin>>x;
	int length=x.size();
	int denghao=0,zuokuohao=0,youkuohao=0,douhao=0;
        for(int i=0;i<length;i++){
		if(x[i]=='=')
		denghao++;
		else if(x[i]=='(')
		zuokuohao++;
		else if(x[i]==')')
		youkuohao++;
		else if(x[i]==',')
		douhao++;
		else if(x[i]=='-');
		else if(x[i]<'0'||(x[i]>'9'&&x[i]<'A')||x[i]>'z'){
			cout<<"输入格式有误，请再次输入："<<endl;
			createp(); 
                    return 0;
		}
	}
	
	       if(denghao!=1){
			cout<<"输入格式有误，请再次输入："<<endl;
			createp(); 
			return 0;
		}
		else if(zuokuohao==youkuohao){
			if(zuokuohao!=douhao){
			cout<<"输入格式有误，请再次输入："<<endl;
			createp(); 
			return 0;
			}
		}
		else {
			cout<<"输入格式有误，请再次输入："<<endl;
			createp(); 
			return 0;	
		}
	number++;
	read(x, xn[number].a,xn[number].name);
}
int look(string a){
	int i;
	for( i=0 ;i<20 ;i++){
		if(a==xn[i].name)
		return i;
	}
	return -1;

}

void add(string a,string b){
	xn[look(a)]+xn[look(b)];
}

void sub(string a, string b){
	xn[look(a)]-xn[look(b)]; 
}

void scalar(string a ,int b){
	xn[look(a)]*b;
	
}

void replace(string a,int b){
	cout<<xn[look(a)].dairux(b)<<endl;
}


int main(){
	cout<<"1. 输入多项式\n2. 多项式相加\n3. 多项式相减\n4. 多项式与常数的乘法运算\n5. 求多项式代入某点的值\n6. 显示所有储存多项式\n9. 帮助（查看功能列表）\n0. 退出系统"<<endl; 
while(1){
	int caozuo;
	string a,b;
	int scalarx;
	cin>>caozuo;
	switch(caozuo){
		case 1:
			createp(); 
			cout<<"请输入要执行的下一步操作:"<<endl;
			break;
	    case 2:
	    	cout<<"请输入需要相加的第一个多项式的名称："<<endl;
			 cin>>a;
			if(look(a)==-1){
				cout<<"储存中并没有您输入的多项式名称。"<<endl;
				cout<<"已返回菜单，请输入要执行的下一步操作:"<<endl;
				break; 
			}
			cout<<"请输入需要相加的第二个多项式的名称："<<endl; 
			 cin>>b; 
			 if(look(b)==-1){
				cout<<"储存中并没有您输入的多项式名称。"<<endl;
				cout<<"已返回菜单，请输入要执行的下一步操作:"<<endl;
				break; 
			}
			 add(a,b);
	         cout<<"请输入要执行的下一步操作:"<<endl;
			 break;
	    case 3:
	    	cout<<"请输入需要相减的前一个多项式的名称："<<endl;
			 cin>>a;
		     if(look(a)==-1){
				cout<<"储存中并没有您输入的多项式名称。"<<endl;
				cout<<"已返回菜单，请输入要执行的下一步操作:"<<endl;
				break; 
			}
			 cout<< "请输入需要相减的后一个多项式的名称："<<endl;
			 cin>>b; 
			 if(look(b)==-1){
				cout<<"储存中并没有您输入的多项式名称。"<<endl;
				cout<<"已返回菜单，请输入要执行的下一步操作:"<<endl;
				break; 
			}
			 sub(a,b);
	         cout<<"请输入要执行的下一步操作:"<<endl;
			 break;
		case 4:
		     cout<<"请输入要倍乘的多项式名称："<<endl;
			 cin>>a;
	         if(look(a)==-1){
				cout<<"储存中并没有您输入的多项式名称。"<<endl;
				cout<<"已返回菜单，请输入要执行的下一步操作:"<<endl;
				break; 
			}
			 cout<<"请输入要倍乘的常量："<<endl;
			 cin>>scalarx;
			 scalar(a,scalarx);
			 cout<<"请输入要执行的下一步操作："<<endl;
		     break;
		case 5:
			cout<<"请输入要代入值的多项式名称："<<endl;
			cin>>a;
            if(look(a)==-1){
				cout<<"储存中并没有您输入的多项式名称。"<<endl;
				cout<<"已返回菜单，请输入要执行的下一步操作:"<<endl;
				break; 
			}
			cout<<"请输入要代入的值："<<endl;
			cin>>scalarx; 
			replace(a,scalarx);
			cout<<"请输入要执行的下一步操作："<<endl;
			break;
		case 6:
		     for(int i=0;i<20;i++){
		     	if(xn[i].name[0]!=0){
		     		cout<<xn[i].name<<"=";
					 printp(xn[i].a);
		     	}
		     	}
			cout<<"请输入要执行的下一步操作："<<endl;	
			 break;
		case 9:
		     cout<<"1. 输入多项式\n2. 多项式相加\n3. 多项式相减\n4. 多项式与常数的乘法运算\n5. 求多项式代入某点的值\n6. 显示所有储存多项式"<<endl;
			 cout<<"请输入要执行的下一步操作："<<endl;
			 break;	 	 
		case 0:
		     break;	 
	}
	if(caozuo==0)
	return 0;
}}
