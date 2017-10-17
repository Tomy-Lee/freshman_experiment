//the implementation of CALCULATOR_H

#include "Calculator.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdio>
using namespace std;

Poly poly[1000];
int Poly::numberOfAllPoly = 0;
// the main menu
void main_choice(){
	cout << "功能菜单：\n";
	cout << "    1.输入并保存多项式\n";
	cout << "    2.多项式相加\n";
	cout << "    3.多项式相减\n";
	cout << "    4.多项式乘法运算\n";
	cout << "    5.求多项式代入某点的值\n";
	cout << "    6.显示所有储存多项式\n";
	cout << "    7.对多项式进行求导\n";
	cout << "    8.判断两多项式是否相等\n";
	cout << "    9.帮助（查看功能列表）\n";
	cout << "    0.退出系统\n";
	cout << "请输入你的选择：\n";
}

//帮助文档
void help() {
	cout << "欢迎使用多项式计算器，您可以根据功能菜单的选项操作：\n"
		<< "    输入多项式的格式如下: (1,4)(2,3)(3,2)，该输入表示 x^4+2x^3+3x^2\n"
		<< "    注意输入以降幂形式输入\n"
		<< "    同时您也可以将多项式命名，命名后可将对应的名称当作多项式使用，如p=(1,4)(2,3)(3,2)\n"
		<< "    此外，输出多项式的格式以降幂格式输出，如x^4+2x^3+3x^2\n"
		<< "    若您错误输入，系统都将会自动提示你重新输入一次，任何输入状态下输入0为退回主菜单\n"
		<< "    感谢您的使用，祝您使用愉快！\n";
}

//default constructor
Poly::Poly() {
	head = NULL;
	name = "";
	cnt = 0;
}

//copy constructor 
Poly::Poly(Poly& p) {
	head = p.head;
	name = p.name;
	cnt = p.cnt;
}

//destructor
Poly::~Poly() {
	Node* cur = head;
	Node* psave = NULL;
	while (cur != NULL) {
		psave = cur->next;
		delete cur;
		cur = psave;
	}
}

bool input_poly(Poly& p) {
	string input;
	getline(cin, input);
	if (input[0] != '(') { // 如果输入为多项式名称
		bool Find = false;
		for (int i = 0; i < Poly::numberOfAllPoly; i++) {
			if (poly[i].name == input) {
				Find = true;
				p = poly[i];
				break;
			}
		}
		if (!Find)
			cout << "不存在该多项式\n";
		return Find;
	}
	//如果输入不是多项式名称
	if (!input_notname(p, input))
		return false;
	return true;
}

bool input_notname(Poly& p, string input) {
	int k = 0;
	int num = 0;//number of ,
	stringstream ss;// 用输入流保存input
	for (int i = 0; i < input.length(); i++) { // 先对多项式进行检测，看是否合法输入
		if (input[i] == '(') {
			if ((i && input[i - 1] == ')') || !i) {
				k++;
				p.cnt++;
				num = 0;
			}
			else {
				cout << "错误输入\n";
				return false;
			}
		}
		else if (input[i] == ')') {
			k--;
			if (num != 1) {
				cout << "错误输入\n";
				return false;
			}
		}
		else if (input[i] == ',')
			num++;
		if (k > 1 || k < 0) {
			cout << "错误输入\n";
			return false;
		}
	}
	if (k) {//if k!= 0 return false
		cout << "错误输入\n";
		return false;
	}
	int hhh = 0;
	num = 0;
	char ch;
	ss << input;
	Node* cur = NULL;
	Node* pre = new Node;
	cur = p.head;
	//if (cur == NULL) cout << "Oops!\n";
	while (!ss.eof()) {//输入流用eof来判断终止
		if (k && !num) {//在，之前为系数
			if (p.head == NULL) {
				p.head = new Node;
				cur = p.head;
				pre = p.head;
			}
			else {
				cur->next = new Node;
				cur = cur->next;
				cur->next = NULL;
			}
			ss >> cur->factor;
		}
		if (k && num) {//在，之后为指数
			ss >> cur->Power;
		}
		ss >> ch;
		if (ch == '(') {
			k++;
		}
		else if (ch == ')' && k) {
			k--;
			num = 0;
			if (cur != p.head) {
				pre->next = cur;
				pre = cur;
			}
		}
		else if (ch == ',')
			num++;
	}
	p.print();
	p.formalise();
	ss.clear();
	return true;
}
bool input_and_save_poly() {
	l1: cout << "请输入一个多项式（0返回主菜单）：";
	int cnt = 0;
	char ch;
	char str[100];
	while ((ch = getchar()) && ch != '=') {
		if (ch == '0')
			return false;// input 0 to return to the main menu
		str[cnt++] = ch;
	}
	str[cnt] = '\0';
	poly[Poly::numberOfAllPoly].name = str;
	string input;
	cin >> input;
	cin.get();
	while (!input_notname(poly[Poly::numberOfAllPoly], input))
		goto l1;
	poly[Poly::numberOfAllPoly].formalise();
	Poly::numberOfAllPoly++;
	return true;
}

//求导
bool Derivation() {
	Poly p1, temp;
	cout << "请输入多项式（以降幂形式输入）：";
	while (!input_poly(p1));
	Node* cur1 = p1.head, *cur = temp.head;
	Node* pre = new Node;
	while (cur1 != NULL) {
		if (temp.head == NULL) {
			temp.head = new Node;
			cur = temp.head;
			pre = temp.head;
		}
		else {
			cur->next = new Node;
			cur = cur->next;
			cur->next = NULL;
		}
		if (cur1->Power) {
			cur->factor = cur1->factor * cur1->Power;
			cur->Power = cur1->Power - 1;
		}
		cur1 = cur1->next;
		if (cur != temp.head) {
			pre->next = cur;
			pre = cur;
		}
	}
	temp.formalise();
	cout << "结果为：";
	temp.print();
	temp.SaveOrNot();
	return true;
}

bool EqualOrNot() {
	Poly p1, p2;
	cout << "请输入第一个多项式（以降幂形式输入）：";
	while (!input_poly(p1));
	cout << "请输入第二个多项式（以降幂形式输入）：";
	while (!input_poly(p2));
	if (p1 == p2) {
		cout << "两多项式相等\n";
	}
	else {
		cout << "两多项式不相等\n";
	}
	return true;
}

bool Poly::operator==(Poly& p) {
	Node* cur1 = this->head, *cur2 = p.head;
	while (cur1 != NULL || cur2 != NULL) {
		if (!(cur1->factor == cur2->factor && cur1->Power == cur2->Power))
			return false;
		if (cur1->next == NULL) {
			if (cur2->next == NULL)
				return true;
			else
				return false;
		}
		if (cur2->next == NULL) {
			if (cur1->next == NULL)
				return true;
			else
				return false;
		}
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
}

Poly operator+(Poly& p1, Poly& p2) {
	Poly *temp = new Poly;
	Node *cur1 = p1.head, *cur2 = p2.head, *cur = temp->head;
	Node *pre = new Node();
	while (cur1 != NULL || cur2 != NULL) {
		if (temp->head == NULL) {
			temp->head = new Node;
			cur = temp->head;
			pre = temp->head;
		}
		else {
			cur->next = new Node;
			cur = cur->next;
			cur->next = NULL;
		}
		if (cur2 == NULL) {
			cur->factor = cur1->factor;
			cur->Power = cur1->Power;
			cur1 = cur1->next;
			if (cur != temp->head) {
				pre->next = cur;
				pre = cur;
			}
		}
		else if (cur1 == NULL) {
			cur->factor = cur2->factor;
			cur->Power = cur2->Power;
			cur2 = cur2->next;
			if (cur != temp->head) {
				pre->next = cur;
				pre = cur;
			}
		}
		else {
			if (cur1->Power == cur2->Power) {
				cur->factor = cur1->factor + cur2->factor;
				cur->Power = cur1->Power;
				cur1 = cur1->next;
				cur2 = cur2->next;
				if (cur != temp->head) {
					pre->next = cur;
					pre = cur;
				}
			}
			else if (cur1->Power > cur2->Power) {
				cur->factor = cur1->factor;
				cur->Power = cur1->Power;
				cur1 = cur1->next;
				if (cur != temp->head) {
					pre->next = cur;
					pre = cur;
				}
			}
			else {
				cur->factor = cur2->factor;
				cur->Power = cur2->Power;
				cur2 = cur2->next;
				if (cur != temp->head) {
					pre->next = cur;
					pre = cur;
				}
			}
		}
	}
	temp->formalise();
	return *temp;
}


Poly operator-(Poly& p1, Poly& p2) {
	Poly* temp = new Poly;
	Node* cur = temp->head, *cur1 = p1.head, *cur2 = p2.head;
	Node* pre = new Node;
	while (cur1 != NULL || cur2 != NULL) {
		if (temp->head == NULL) {
			temp->head = new Node;
			cur = temp->head;
			pre = temp->head;
		}
		else {
			cur->next = new Node;
			cur = cur->next;
			cur->next = NULL;
		}
		if (cur2 == NULL) {
			cur->factor = cur1->factor;
			cur->Power = cur1->Power;
			cur1 = cur1->next;
			if (cur != temp->head) {
				pre->next = cur;
				pre = cur;
			}
		}
		else if (cur1 == NULL) {
			cur->factor = -cur2->factor;
			cur->Power = cur2->Power;
			cur2 = cur2->next;
			if (cur != temp->head) {
				pre->next = cur;
				pre = cur;
			}
		}
		else {
			if (cur1->Power == cur2->Power) {
				cur->factor = cur1->factor - cur2->factor;
				cur->Power = cur1->Power;
				cur1 = cur1->next;
				cur2 = cur2->next;
				if (cur != temp->head) {
					pre->next = cur;
					pre = cur;
				}
			}
			else if (cur1->Power > cur2->Power) {
				cur->factor = cur1->factor;
				cur->Power = cur1->Power;
				cur1 = cur1->next;
				if (cur != temp->head) {
					pre->next = cur;
					pre = cur;
				}
			}
			else {
				cur->factor = -cur2->factor;
				cur->Power = cur2->Power;
				cur2 = cur2->next;
				if (pre != temp->head) {
					pre->next = cur;
					pre = cur;
				}
			}
		}
	}
	temp->formalise();
	return *temp;
}

//重载多项式中其中一项与整个多项式相乘 
Poly operator*(Poly& p, Node*& node) {
	Poly* temp = new Poly;
	Node* cur1 = p.head, *cur = temp->head;
	Node* pre = new Node;
	while (cur1 != NULL) {
		if (temp->head == NULL) {
			temp->head = new Node;
			cur = temp->head;
			pre = temp->head;
		}
		else {
			cur->next = new Node;
			cur = cur->next;
			cur->next = NULL;
		}
		cur->factor = cur1->factor * (node->factor);
		cur->Power = cur1->Power + node->Power;
		if (cur != temp->head) {
			pre->next = cur;
			pre = cur;
		}
		cur1 = cur1->next;
	}
	temp->formalise();
	return *temp;
}

//多项式与多项式相乘
bool MultiPoly() { 
	Poly p1, p2, p3, temp;
	cout << "请输入第一个多项式（以降幂形式输入）：";
	while (!input_poly(p1)) {
		cout << "请输入第一个多项式（以降幂形式输入）：";
	}
	cout << "请输入第二个多项式（以降幂形式输入）：";
	while (!input_poly(p2))
		cout << "请输入第二个多项式（以降幂形式输入）：";
	Node *cur = temp.head, *cur2 = p2.head;
	while (cur2 != NULL) {
		p3 = p1 * cur2;
		temp = temp + p3;
		cur2 = cur2->next;
	}
	temp.formalise();
	cout << "结果为：";
	temp.print();
	temp.SaveOrNot();
	return true;
}

Poly operator*(int num, Poly& p) {
	Poly* temp = new Poly;
	Node* cur1 = p.head, *cur = temp->head;
	Node* pre = new Node;
	while (cur1 != NULL) {
		if (temp->head == NULL) {
			temp->head = new Node;
			cur = temp->head;
			pre = temp->head;
		}
		else {
			cur->next = new Node;
			cur = cur->next;
			cur->next = NULL;
		}
		cur->factor = num * cur1->factor;
		cur->Power = cur1->Power;
		if (cur != temp->head) {
			pre->next = cur;
			pre = cur;
		}
		cur1 = cur1->next;
	}
	temp->formalise();
	return *temp;
}

Poly& Poly::operator=(Poly& p) {
	Node* cur = head, *cur1 = p.head;
	Node* pre = new Node;
	Node* latter = NULL;
	while (cur != NULL) {
		latter = cur->next;
		delete cur;
		cur = latter;
	}
	head = NULL;
	while (cur1 != NULL) {
		if (head == NULL) {
			head = new Node;
			cur = head;
			pre = head;
		}
		else {
			cur->next = new Node;
			cur = cur->next;
			cur->next = NULL;
		}
		cur->factor = cur1->factor;
		cur->Power = cur1->Power;
		if (cur != head) {
			pre->next = cur;
			pre = cur;
		}
		cur1 = cur1->next;
	}
	name = p.name;
	cnt = p.cnt;
	return *this;
}

//利用函数指针，将运算放入同一个函数中
bool AdditionFull() {
	Poly p1, p2, p3;
	cout << "请输入第一个多项式（以降幂形式输入）：";
	while (!input_poly(p1));\
		cout << "请输入第一个多项式（以降幂形式输入）：";
	cout << "请输入第二个多项式（以降幂形式输入）：";
	while (!input_poly(p2))
		cout << "请输入第二个多项式（以降幂形式输入）：";
	p3 = p1+p2;
	cout << "结果为：";
	p3.print();
	p3.SaveOrNot();
	return true;
}

bool SubstractionFull() {
	Poly p1, p2, p3;
	cout << "请输入第一个多项式（以降幂形式输入）：";
	while (!input_poly(p1))
		cout << "请输入第一个多项式（以降幂形式输入）：";
	cout << "请输入第二个多项式（以降幂形式输入）：";
	while (!input_poly(p2))
		cout << "请输入第二个多项式（以降幂形式输入）：";
	p3 = p1 - p2;
	cout << "结果为：";
	p3.print();
	char ch;
	cout << "是否保存计算结果(Y/N):";
	cin >> ch;
	cin.get();
	p3.SaveOrNot();
	return true;
}

bool MultiplicationFull() {
	Poly p2, p3;
	int num;
	cout << "请输入常数值：";
	cin >> num;
	cin.get();
	cout << "请输入第二个多项式（以降幂形式输入）：";
	while (!input_poly(p2))
		cout << "请输入第二个多项式（以降幂形式输入）：";
	p3 = num * p2;
	cout << "结果为：";
	p3.print();
	char ch;
	cout << "是否保存计算结果(Y/N):";
	cin >> ch;
	cin.get();
	p3.SaveOrNot();
	return true;
}

double Poly::evaluation(int x) {
	double sum = 0;
	Node* cur = head;
	while (cur != NULL) {
		sum += (pow(x, cur->Power)) * (cur->factor);
		cur = cur->next;
	}
	return sum;
}

//完整版赋值
bool EvaluationFull() {
	Poly temp;
	int num;
	cout << "请输入多项式（以降幂形式输入）：";
	while (!input_poly(temp))
		cout << "请输入多项式（以降幂形式输入）：";
	cout << "请输入x的值：";
	cin >> num;
	cout << "当x = " << num << "时，多项式的值为" << temp.evaluation(num) << endl;
	return true;
}

void Poly::print() {
	Node* cur = head;
	while (cur != NULL) {
		if (cur->Power) {//指数不为0时
			if (cur->factor > 0) {//系数>0
				if (cur != head) {
					if (cur->factor == 1) {//若系数为1
						cout << "+x";
						if (cur->Power != 1) {
							cout << "^" << cur->Power;
						}
					}
					else {
						cout << "+" << cur->factor << 'x';
						if (cur->Power != 1) {
							cout << "^" << cur->Power;
						}
					}
				}
				else {
					if (cur->factor == 1) {
						cout << "x";
						if (cur->Power != 1) {
							cout << "^" << cur->Power;
						}
					}
					else {
						cout << cur->factor << 'x';
						if (cur->Power != 1) {
							cout << "^" << cur->Power;
						}
					}
				}
			}
			else {//系数<0
				if (cur->factor == -1) {
					cout << "-x";
					if (cur->Power != 1) {
						cout << "^" << cur->Power;
					}
				}
				else {
					cout << cur->factor << 'x';
					if (cur->Power != 1) {
						cout << "^" << cur->Power;
					}
				}
			}
		}
		else {//指数为0时
			if (cur->factor > 0) {
				if (cur != head) {
					cout << "+" << cur->factor;
				}
				else
					cout << cur->factor;
			}
				
			else
				cout << cur->factor;
		}
		cur = cur->next;
	}
	cout << endl;
}

void Poly::formalise() {
	Node* cur = this->head;
	Node* pre = NULL, *latter = NULL;
	while (cur != NULL) {
		if (cur->factor == 0) {
			if (cur == this->head) {
				this->head = cur->next;
				latter = cur->next;
				delete cur;
				cur = latter;
			}
			else {
				pre->next = cur->next;
				cur->next = NULL;
				delete cur;
				cur = pre->next;
			}
		}
		else {
			pre = cur;
			cur = cur->next;
		}
	}
}

bool Poly::show_all_poly() {
	for (int i = 0; i < numberOfAllPoly; i++) {
		cout << poly[i].name << '=';
		poly[i].print();
	}
	return true;
}

//询问是否保存结果
void Poly::SaveOrNot() {
	char ch;
	cout << "是否保存计算结果(Y/N):";
	cin >> ch;
	cin.get();
	while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n') {
		cout << "是否保存计算结果(Y/N):";
		cin >> ch;
	}
	if (ch == 'Y' || ch == 'y') {
		cout << "请输入多项式名称：";
		poly[Poly::numberOfAllPoly] = *this;
		getline(cin, poly[Poly::numberOfAllPoly].name);
		Poly::numberOfAllPoly++;
	}
}

//打开程序时先读取文件
void filein() {
	ifstream fin;
	fin.open("polynomia.txt", ifstream::in);
	string input;
	char c[100];
	while (!fin.eof()) {
		int cnt = 0;
		char ch;
		while ((fin >> ch) && ch != '=') {
			c[cnt++] = ch;
		}
		c[cnt] = '\0';
		if (ch == '=')
			poly[Poly::numberOfAllPoly].name = c;
		getline(fin, input);
		if (input_notname(poly[Poly::numberOfAllPoly], input)) {
			Poly::numberOfAllPoly++;
		}
	}
	fin.close();
}

//关闭程序时将程序中的数据打印到文件中
void fileout() {
	ofstream fout;
	fout.open("Polynomia.txt", ofstream::out);
	for (int i = 0; i < Poly::numberOfAllPoly; i++) {
		fout << poly[i].name << '=';
		Node * cur = poly[i].head;
		Node * psave = NULL;
		while (cur != NULL) {
			fout << '(' << cur->factor << ',' << cur->Power << ')';
			psave = cur->next;
			cur = psave;
		}
		fout << endl;
	}
	fout.close();
}