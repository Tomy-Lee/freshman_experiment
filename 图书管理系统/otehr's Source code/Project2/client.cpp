//client.cpp
//main function
#include "Library.h"
#include <iostream>
#include <string>
#include <iomanip>

int main() {
	char choice;
	cout << "This is a library management system, now you have 4 choices to do:\n";
	main_choice();
	while (cin >> choice && choice != 'q' && choice != 'h') {
		cin.get();
		if (choice == 'a' || choice == 'A') {
			if (!in()) {
				cout << "Error.\n";
				cout << endl;
				main_choice();
				continue;
			}
		}
		else if (choice == 'b' || choice == 'B') {
			if (!borrow_full()) {
				cout << endl;
				main_choice();
				continue;
			}
		}
		else if (choice == 'c' || choice == 'C') {
			if (!Return()) {
				cout << endl;
				main_choice();
				continue;
			}
		}
		else if (choice == 'd' || choice == 'D') {
			if (find()) {
				cout << "Borrow or not(Y/N): ";
				char choi;
				cin >> choi;
				if (choi == 'Y' || choi == 'y') {
					if (!borrow_simple()) {
						cout << "Error.\n\n";
						main_choice();
						continue;
					}
				}
			}
		}
		else if (choice == 'e' || choice == 'E') {
			if (!show_book()) {
				cout << endl;
				main_choice();
				continue;
			}
		}
		else if (choice == 'f' || choice == 'F') {
			if (!show_allbooks()) {
				cout << "Error.\n\n";
				main_choice();
				continue;
			}
		}
		else if (choice == 'g' || choice == 'G') {
			if (!Delete()) {
				cout << endl;
				main_choice();
				continue;
			}
		}
		else {
			cout << "Error input.\n\n";
			main_choice();
			continue;
		}
		cout << endl;
		main_choice();
	}
	Free();
	cout << "Bye.\n";
	return 0;
}
