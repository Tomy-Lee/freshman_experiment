#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
struct Node {
	int factor;	//ÿһ���ϵ��
	int Power;	//ÿһ�����
	Node* next;		//ָ����һ������ʽ
	Node() {
		factor = Power = 0;
		next = NULL;
	}
};
class Poly {
private:
	Node* head;			//����ʽ����ͷ
	string name;		//����ʽ������
	int cnt;			//һ���ж�����	
	static int numberOfAllPoly;
public:
	Poly();		//default constructor
	Poly(Poly& p);//copy constructor
	~Poly();//destructor
	friend bool input_poly(Poly& p); //input a polynomia
	friend bool input_notname(Poly& p, string input);
	friend bool input_and_save_poly();
	friend bool Derivation(); //��
	friend Poly operator+(Poly& p1, Poly& p2);
	friend Poly operator-(Poly& p1, Poly& p2);
	friend Poly operator*(int num, Poly& p);
	friend Poly operator*(Poly& p, Node*& node);
	Poly& operator=(Poly& p);
	bool operator==(Poly& p);
	friend bool EqualOrNot();
	friend bool AdditionFull();
	friend bool SubstractionFull();
	friend bool MultiplicationFull();
	friend bool MultiPoly();
	friend bool EvaluationFull();
	//friend Poly& operator*(Poly& p, int num);//overload poly * double
	double evaluation(int x); //evalution
	void print();//print the result
	void formalise();//������ʽ��ϵ��Ϊ0����ɾ��
	static bool show_all_poly();//show all the polynomia
	friend void filein();//�ļ�����
	friend void fileout();//�ļ����
	void SaveOrNot();//save the result after calculation
};
void main_choice();
void help();

#endif