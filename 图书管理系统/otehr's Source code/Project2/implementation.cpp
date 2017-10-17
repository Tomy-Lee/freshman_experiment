//the implemetation of function
#include "Library.h"
#include <cstring>
#include <string>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cmath>
using namespace std;
//��ʼʱhead��nextָ��end������ÿ�������Ŀ����ǰһ��endָ�����飬ͬʱ����endָ�����顣
static book* (head[26]);
static book* (End[26]);
//��id�Ǽ�������id�Ƿ����
//id A0000001
static bool registerId[26][1000000] = { 0 };
void Allocate() {
	for (int i = 0; i < 26; i++) {
		head[i] = NULL;
		End[i] = NULL;
	}
}
bool in() {
	//bookName
	string name;
	int id, num;
	char cla;
	cout << "Enter the book's name(within 100 words):  ";
	getline(cin, name);
	cout << "Enter the number of this book you add to library:  ";
	while (scanf_s("%d", &num) && num <= 0) {
		cout << "The number should be larger than 0. Please enter again: ";
	}
	if (findBooksByBookName(name)) {
		cout << "Enter the book ID(0 to create a new book):  ";
		IDInput(cla, id);
		if (cla == '0') {
			book *temp = NULL;
			if (!findBookById(cla - 'A', id, temp)) {
				return false;
			}
			if (!add_book(temp, num)) {
				cout << "Error.\n";
				return false;
			}

		}
		//����һ������Ŀ
		else {
			class_choice();
			char choose;
			cin >> choose;
			if (!create_book(choose - 'A', num)) {
				return false;
			}
		}
	}
	//����Ҳ������򴴽�һ������Ŀ
	else {
		class_choice();
		char choose;
		cin >> choose;
		cin.get();
		if (!create_book(choose - 'A', num)) {
			return false;
		}
	}
	return true;
}

bool Delete() {
	char cla;
	int id;
	cout << "Enter the id you want to delete: ";
	IDInput(cla, id);
	if (!registerId[cla - 'A'][id])  {
		cout << "This id is invalid.\n";
		return false;
	}
	book* temp = NULL;
	findBookById(cla - 'A', id, temp);
	book* t = NULL;
	t = head[cla - 'A'];
	for (int i = 0; i < classcount[cla - 'A'] - 1; i++) {
		t = t->next;
	}
	t->next = temp->next;
	classcount[cla - 'A']--;
	if (!classcount[cla - 'A'])
		head[cla - 'A'] = NULL;
	registerId[cla - 'A'][id] = false;
	numberOfAllBooks--;
	if (temp != NULL)
		delete temp;
	
}
bool add_book(book *&book1, int count) {
	book1->total += count;
	book1->onShelf += count;
	return true;
}
//input all imformation
bool input_book_imformation(book *&book1, int cla) {
	string name;
	int num;
	int n1, n2, n3;
	cout << "Enter the book's name:  ";
	getline(cin, name);
	book1->bookName = name;
	cout << "Enter the author's name:  ";
	getline(cin, name);
	book1->author = name;
	cout << "Enter the name of the publish company:  ";
	getline(cin, name);
	book1->publishCompany = name;
	cout << "Enter the version:  ";
	cin >> num;
	book1->ver = num;
	cout << "Enter the publish time(year month day):  ";
	cin >> n1 >> n2 >> n3;
	cin.get();
	book1->Time.year = n1;
	book1->Time.month = n2;
	book1->Time.day = n3;
	book1->classification = cla;
	//ID A0000000
	book1->id = classcount[book1->classification]++;
	registerId[cla][book1->id] = true;
	book1->borrow = book1->total = book1->onShelf = 0;
	numberOfAllBooks++;
	return true;
}
//��������Ŀ
bool create_book(int cla, int num) {
	book *newbook = new book;
	newbook->next = NULL;
	if (!input_book_imformation(newbook, cla))
		return false;
	if (!add_book(newbook, num))
		return false;
	if (head[cla] == NULL)
		head[cla] = newbook;
	else
		End[cla]->next = newbook;
	End[cla] = newbook;
	return true;
}
//borrow
bool borrow_full() {
	string bookname;
	cout << "Enter the book name:  ";
	getline(cin, bookname);
	if (findBooksByBookName(bookname))
		borrow_simple();
	else {
		cout << "Can't find this book.\n";
		return false;
	}
	return true;
}

bool borrow_simple() {
	char cla;
	int id;
	string input;
	cout << "Enter the book ID:  ";
	book* temp = NULL;
	while (1) {
		IDInput(cla, id);
		if (!findBookById(cla - 'A', id, temp)) {
			return false;
		}
		if (temp->onShelf) {
			off_shelf(temp);
			return true;
		}
		cout << "This books are all borrowed. Please enter another book ID: ";
	}
	return true;
}
//return
bool Return() {
	char cla;
	int id;
	cout << "Enter the book ID:  ";
	IDInput(cla, id);
	book* temp = NULL;
	if (!findBookById(cla - 'A', id, temp)) {
		return false;
	}
	if (!temp->borrow) {
		cout << "This book are all on shelf.\n";
		return false;
	}
	back_to_shelf(temp);
	return true;
}
bool off_shelf(book *&book1) {
	book1->borrow++;
	book1->onShelf--;
	return true;
}

bool back_to_shelf(book *&book1) {
	book1->borrow--;
	book1->onShelf++;
	return true;
}
//find()
bool find() {
	cout << "Choose the searching method:\n"
		<< "a. Author name        b. Book name\n"
		<< "c. Classification     d. Publish time\n";
	char choice;
	cin >> choice;
	cin.get();
	string name;
	if (choice == 'a' || choice == 'A') {
		cout << "Enter the author name:  ";
		getline(cin, name);
		if (findBooksByAuthor(name))
			return true;
		else {
			cout << "Can't find the book.\n";
			return false;
		}
	}
	if (choice == 'b' || choice == 'B') {
		cout << "Enter the book name:  ";
		getline(cin, name);
		if (findBooksByBookName(name))
			return true;
		else {
			cout << "Can't find the book.\n";
			return false;
		}
	}
	if (choice == 'c' || choice == 'C') {
		class_choice();
		char ch;
		cin >> ch;
		cin.get();
		if (findBooksByClassification(ch - 'A'))
			return true;
		else {
			cout << "Can't find the book.\n";
			return false;
		}
	}
	if (choice == 'd' || choice == 'D') {
		publishTime temp;
		cout << "Enter the publish time(year month day):  ";
		cin >> temp.year >> temp.month >> temp.day;
		if (findBooksByPublishTime(temp))
			return true;
		else {
			cout << "Can't find the book.\n";
			return false;
		}
	}
	return true;
}
//��ʾ�ض�����Ŀ
bool show_book(){
	char cla;
	int id;
	cout << "Enter the book id you want to know:  ";
	IDInput(cla, id);
	book *temp = NULL;
	if (!findBookById(cla - 'A', id, temp)) {
		return false;
	}
	standard_output(temp);
	return true;
}
//��ʾ������Ŀ
bool show_allbooks() {
	book *cur = NULL;
	int count = 1;
	if (!numberOfAllBooks) {
		cout << "No books.\n";
		return false;
	}
	for (int i = 0; i < 26; i++) {
		cur = head[i];
		while (cur != NULL) {
			cout << "#" << count++ << endl;
			standard_output(cur);
			cur = cur->next;
		}
	}
	return true;
}
//�����������������鱾
bool findBooksByAuthor(string authorName) {
	//��������
	int count = 1;
	bool find = false;
	book* cur = NULL;
	for (int i = 0; i < 26; i++) {
		if (!classcount[i])
			continue;
		cur = head[i];
		while (cur != NULL) {
			if (authorName == cur->author) {
				cout << "#" << count++ << endl;
				standard_output(cur);
				find = true;
			}
			cur = cur->next;
		}
	}
	return find;
}
//�������������鱾
bool findBooksByBookName(string bookName) {
	//��������
	int count = 1;
	bool find = false;
	if (!numberOfAllBooks) {
		return false;
	}
	book* cur = NULL;
	for (int i = 0; i < 26; i++) {
		if (!classcount[i])
			continue;
		cur = head[i];
		while (1) {
			if (bookName == cur->bookName) {
				cout << "#" << count++ << endl;
				standard_output(cur);
				find = true;
			}
			if (cur->next == NULL)
				break;
			else
				cur = cur->next;
		}
	}
	return find;
}
//�÷���������
bool findBooksByClassification(int cla) {
	//����÷�����û���鼮���򷵻�false
	if (!classcount[cla])
		return false;
	int count = 1;
	book* cur = NULL;
	cur = head[cla];
	while (cur != NULL) {
		cout << "#" << count++ << endl;
		standard_output(cur);
		cur = cur->next;
	}
	return true;
}
//�ó���ʱ��������
bool findBooksByPublishTime(publishTime time) {
	int count = 1;
	bool find = false;
	book* cur = NULL;
	for (int i = 0; i < 26; i++) {
		if (!classcount[i])
			continue;
		cur = head[i];
		while (cur != NULL) {
			if (time.year == cur->Time.year && time.month == cur->Time.month && time.day == cur->Time.day) {
				cout << "#" << count++ << endl;
				standard_output(cur);
				find = true;
			}
			cur = cur->next;
		}
	}
	return find;
}

void standard_output(book* book1) {
	cout << "  ID: " << (char)(book1->classification + 'A') << setfill('0') << setw(7) << book1->id << endl;
	cout << "  Bookname: " << book1->bookName << endl;
	cout << "  Author name: " << book1->author << endl;
	cout << "  Publish company:  " << book1->publishCompany << endl;
	cout << "  Version: " << book1->ver << endl;
	cout << "  Publish time: " << book1->Time.year << "y " << book1->Time.month
		<< "m " << book1->Time.day << "d\n";
	cout << "  Borrow: " << setfill(' ') << setw(5) << book1->borrow
		<< "\tOn shelf: " << book1->onShelf << endl;
}

void main_choice() {
	cout << "a. Store book                 b. Borrow book\n"
		 << "c. Return book                d. Search book\n"
		 << "e. show details of a book     f. show all books\n"
		 << "g. Delete book                h. quit\n";
	cout << "Enter your choice:  ";
}

void find_choice() {
	cout << "a. By author name      b. By book name\n"
		<< "c. By classification   d. By publish time\n";
	cout << "Enter your choice:  ";
}

void class_choice() {
	cout << "Choose the book's classification: \n"
		<< "A: ���˼���塢�������塢ë��˼�롢��Сƽ����\n"
		<< "B: ��ѧ���ڽ�\n"
		<< "C: ����ѧ����\n"
		<< "D: ���Ρ�����\n"
		<< "E: ����\n"
		<< "F: ����\n"
		<< "G: �Ļ�����ѧ������������\n"
		<< "H: ���ԡ�����\n"
		<< "I: ��ѧ\n"
		<< "J: ����\n"
		<< "K: ��ʷ������\n"
		<< "N: ��Ȼ��ѧ����\n"
		<< "O: �����ѧ�ͻ�ѧ\n"
		<< "P: ����ѧ�������ѧ\n"
		<< "Q: �����ѧ\n"
		<< "R: ҽҩ������\n"
		<< "S: ũҵ��ѧ\n"
		<< "T: ��ҵ����\n"
		<< "U: ��ͨ����\n"
		<< "V: ���ա�����\n"
		<< "X: ������ѧ����ȫ��ѧ\n"
		<< "Z: �ۺ���ͼ��\n";
}
bool findBookById(int clas, int id, book*& book1) {
	if (!registerId[clas][id]) {
		cout << "This ID is invalid.\n";
		return false;
	}
	book *current = NULL;
	book *prev = NULL;
	current = head[clas];
	for (int i = 0; i < classcount[clas] - 1; i++) {
		prev = current;
		current = current->next;
	}
	book1 = current;
	return true;
}
void Free() {
	for (int i = 0; i < 26; i++) {
		book* current = NULL;
		if (!classcount[i])
			continue;
		while (current != NULL) {
			delete current;
			current = current->next;
		}
	}
}

void IDInput(char& cla, int& id) {
	string input;
	int ans = 0;
	while (cin >> input) {
		if (input.length() == 8 && input[0] >= 'A' && input[0] <= 'Z')
		 {
			cla = input[0];
			for (int i = 1; i < 8; i++) {
				if (input[i] < '0' || input[i] > '9')
					break;
				ans += (input[i] - '0') * pow(10, 8 - i);
				if (i == 7){
					id = ans;
					return;
				}
			}
		}
		else {
			cout << "Error ID input. Please enter again: ";
		}
	}
}