#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
struct Node {
	int factor;	//每一项的系数
	int Power;	//每一项的幂
	Node* next;		//指向下一个多项式
	Node() {
		factor = Power = 0;
		next = NULL;
	}
};
class Poly {
private:
	Node* head;			//多项式链表头
	string name;		//多项式的名称
	int cnt;			//一共有多少项	
	static int numberOfAllPoly;
public:
	Poly();		//default constructor
	Poly(Poly& p);//copy constructor
	~Poly();//destructor
	friend bool input_poly(Poly& p); //input a polynomia
	friend bool input_notname(Poly& p, string input);
	friend bool input_and_save_poly();
	friend bool Derivation(); //求导
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
	void formalise();//将多项式中系数为0的项删除
	static bool show_all_poly();//show all the polynomia
	friend void filein();//文件输入
	friend void fileout();//文件输出
	void SaveOrNot();//save the result after calculation
};
void main_choice();
void help();

#endif