#include "Calculator.h"
#include <iostream>

using namespace std;
int main() {
	int choice;
	filein();
	cout << "欢迎使用多项式计算器： \n";
	main_choice();
	while ((cin >> choice) && choice) {
		cin.get();
		if (choice == 1) {
			if (!input_and_save_poly()) {
				cout << endl << endl;
				main_choice();
			}
		}
		if (choice == 2) {
			if (!AdditionFull()) {
				cout << endl << endl;
				main_choice();
			}
		}
		if (choice == 3) {
			if (!SubstractionFull()) {
				cout << endl << endl;
				main_choice();
			}
		}
		if (choice == 4) {
			cout << "1.多项式与常数相乘\n2.多项式与多项式相乘\n0.返回主菜单\n";
			cout << "请输入你的选择：";
			cin >> choice;
			cin.get();
			if (choice == 1) {
				if (!MultiplicationFull()) {
					cout << endl << endl;
					main_choice();
				}
			}
			else if (choice == 2) {
				if (!MultiPoly()) {
					cout << endl << endl;
					main_choice();
				}
			}
		}
		if (choice == 5) {
			if (!EvaluationFull()) {
				cout << endl << endl;
				main_choice();
			}
		}
		if (choice == 6) {
			if (!Poly::show_all_poly()) {
				cout << endl << endl;
				main_choice();
			}
		}
		if (choice == 7) {
			if (!Derivation()) {
				cout << endl << endl;
				main_choice();
			}
		}
		if (choice == 8) {
			if (!EqualOrNot()) {
				cout << endl << endl;
				main_choice();
			}
		}
		if (choice == 9) {
			help();
			int c;
			if (cin >> c && !c) {
				cout << endl << endl;
				main_choice();
				continue;
			}
		}
		cout << endl << endl;
		main_choice();
	}
	fileout();
	return 0;
}