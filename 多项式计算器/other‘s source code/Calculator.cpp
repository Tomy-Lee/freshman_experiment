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
	cout << "���ܲ˵���\n";
	cout << "    1.���벢�������ʽ\n";
	cout << "    2.����ʽ���\n";
	cout << "    3.����ʽ���\n";
	cout << "    4.����ʽ�˷�����\n";
	cout << "    5.�����ʽ����ĳ���ֵ\n";
	cout << "    6.��ʾ���д������ʽ\n";
	cout << "    7.�Զ���ʽ������\n";
	cout << "    8.�ж�������ʽ�Ƿ����\n";
	cout << "    9.�������鿴�����б�\n";
	cout << "    0.�˳�ϵͳ\n";
	cout << "���������ѡ��\n";
}

//�����ĵ�
void help() {
	cout << "��ӭʹ�ö���ʽ�������������Ը��ݹ��ܲ˵���ѡ�������\n"
		<< "    �������ʽ�ĸ�ʽ����: (1,4)(2,3)(3,2)���������ʾ x^4+2x^3+3x^2\n"
		<< "    ע�������Խ�����ʽ����\n"
		<< "    ͬʱ��Ҳ���Խ�����ʽ������������ɽ���Ӧ�����Ƶ�������ʽʹ�ã���p=(1,4)(2,3)(3,2)\n"
		<< "    ���⣬�������ʽ�ĸ�ʽ�Խ��ݸ�ʽ�������x^4+2x^3+3x^2\n"
		<< "    �����������룬ϵͳ�������Զ���ʾ����������һ�Σ��κ�����״̬������0Ϊ�˻����˵�\n"
		<< "    ��л����ʹ�ã�ף��ʹ����죡\n";
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
	if (input[0] != '(') { // �������Ϊ����ʽ����
		bool Find = false;
		for (int i = 0; i < Poly::numberOfAllPoly; i++) {
			if (poly[i].name == input) {
				Find = true;
				p = poly[i];
				break;
			}
		}
		if (!Find)
			cout << "�����ڸö���ʽ\n";
		return Find;
	}
	//������벻�Ƕ���ʽ����
	if (!input_notname(p, input))
		return false;
	return true;
}

bool input_notname(Poly& p, string input) {
	int k = 0;
	int num = 0;//number of ,
	stringstream ss;// ������������input
	for (int i = 0; i < input.length(); i++) { // �ȶԶ���ʽ���м�⣬���Ƿ�Ϸ�����
		if (input[i] == '(') {
			if ((i && input[i - 1] == ')') || !i) {
				k++;
				p.cnt++;
				num = 0;
			}
			else {
				cout << "��������\n";
				return false;
			}
		}
		else if (input[i] == ')') {
			k--;
			if (num != 1) {
				cout << "��������\n";
				return false;
			}
		}
		else if (input[i] == ',')
			num++;
		if (k > 1 || k < 0) {
			cout << "��������\n";
			return false;
		}
	}
	if (k) {//if k!= 0 return false
		cout << "��������\n";
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
	while (!ss.eof()) {//��������eof���ж���ֹ
		if (k && !num) {//�ڣ�֮ǰΪϵ��
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
		if (k && num) {//�ڣ�֮��Ϊָ��
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
	l1: cout << "������һ������ʽ��0�������˵�����";
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

//��
bool Derivation() {
	Poly p1, temp;
	cout << "���������ʽ���Խ�����ʽ���룩��";
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
	cout << "���Ϊ��";
	temp.print();
	temp.SaveOrNot();
	return true;
}

bool EqualOrNot() {
	Poly p1, p2;
	cout << "�������һ������ʽ���Խ�����ʽ���룩��";
	while (!input_poly(p1));
	cout << "������ڶ�������ʽ���Խ�����ʽ���룩��";
	while (!input_poly(p2));
	if (p1 == p2) {
		cout << "������ʽ���\n";
	}
	else {
		cout << "������ʽ�����\n";
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

//���ض���ʽ������һ������������ʽ��� 
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

//����ʽ�����ʽ���
bool MultiPoly() { 
	Poly p1, p2, p3, temp;
	cout << "�������һ������ʽ���Խ�����ʽ���룩��";
	while (!input_poly(p1)) {
		cout << "�������һ������ʽ���Խ�����ʽ���룩��";
	}
	cout << "������ڶ�������ʽ���Խ�����ʽ���룩��";
	while (!input_poly(p2))
		cout << "������ڶ�������ʽ���Խ�����ʽ���룩��";
	Node *cur = temp.head, *cur2 = p2.head;
	while (cur2 != NULL) {
		p3 = p1 * cur2;
		temp = temp + p3;
		cur2 = cur2->next;
	}
	temp.formalise();
	cout << "���Ϊ��";
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

//���ú���ָ�룬���������ͬһ��������
bool AdditionFull() {
	Poly p1, p2, p3;
	cout << "�������һ������ʽ���Խ�����ʽ���룩��";
	while (!input_poly(p1));\
		cout << "�������һ������ʽ���Խ�����ʽ���룩��";
	cout << "������ڶ�������ʽ���Խ�����ʽ���룩��";
	while (!input_poly(p2))
		cout << "������ڶ�������ʽ���Խ�����ʽ���룩��";
	p3 = p1+p2;
	cout << "���Ϊ��";
	p3.print();
	p3.SaveOrNot();
	return true;
}

bool SubstractionFull() {
	Poly p1, p2, p3;
	cout << "�������һ������ʽ���Խ�����ʽ���룩��";
	while (!input_poly(p1))
		cout << "�������һ������ʽ���Խ�����ʽ���룩��";
	cout << "������ڶ�������ʽ���Խ�����ʽ���룩��";
	while (!input_poly(p2))
		cout << "������ڶ�������ʽ���Խ�����ʽ���룩��";
	p3 = p1 - p2;
	cout << "���Ϊ��";
	p3.print();
	char ch;
	cout << "�Ƿ񱣴������(Y/N):";
	cin >> ch;
	cin.get();
	p3.SaveOrNot();
	return true;
}

bool MultiplicationFull() {
	Poly p2, p3;
	int num;
	cout << "�����볣��ֵ��";
	cin >> num;
	cin.get();
	cout << "������ڶ�������ʽ���Խ�����ʽ���룩��";
	while (!input_poly(p2))
		cout << "������ڶ�������ʽ���Խ�����ʽ���룩��";
	p3 = num * p2;
	cout << "���Ϊ��";
	p3.print();
	char ch;
	cout << "�Ƿ񱣴������(Y/N):";
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

//�����渳ֵ
bool EvaluationFull() {
	Poly temp;
	int num;
	cout << "���������ʽ���Խ�����ʽ���룩��";
	while (!input_poly(temp))
		cout << "���������ʽ���Խ�����ʽ���룩��";
	cout << "������x��ֵ��";
	cin >> num;
	cout << "��x = " << num << "ʱ������ʽ��ֵΪ" << temp.evaluation(num) << endl;
	return true;
}

void Poly::print() {
	Node* cur = head;
	while (cur != NULL) {
		if (cur->Power) {//ָ����Ϊ0ʱ
			if (cur->factor > 0) {//ϵ��>0
				if (cur != head) {
					if (cur->factor == 1) {//��ϵ��Ϊ1
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
			else {//ϵ��<0
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
		else {//ָ��Ϊ0ʱ
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

//ѯ���Ƿ񱣴���
void Poly::SaveOrNot() {
	char ch;
	cout << "�Ƿ񱣴������(Y/N):";
	cin >> ch;
	cin.get();
	while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n') {
		cout << "�Ƿ񱣴������(Y/N):";
		cin >> ch;
	}
	if (ch == 'Y' || ch == 'y') {
		cout << "���������ʽ���ƣ�";
		poly[Poly::numberOfAllPoly] = *this;
		getline(cin, poly[Poly::numberOfAllPoly].name);
		Poly::numberOfAllPoly++;
	}
}

//�򿪳���ʱ�ȶ�ȡ�ļ�
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

//�رճ���ʱ�������е����ݴ�ӡ���ļ���
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