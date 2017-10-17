//created by lixiaoyun
//last update in 2016/03/27
//All rights reserved
//��Ҫ���䵱�û����������ʱ��Ҫ��ʾ�û��������룬��while����,fighting
#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
static int  numberOfAllBooks = 0;
static int classcount[26] = { 0 };

struct publishTime {
	int year;
	int month;
	int day;
	struct publishTime() {
		year = month = day = 0;
	}
};
struct book {
	//ID��һλ��ʾ���࣬��������ֱ�ʾ�÷����еĵڼ���
	int id;
	string bookName;
	string author;
	string publishCompany;
	int ver;
	int classification;
	publishTime Time;
	int total;
	int borrow;
	int onShelf;
	struct book* next;
	struct book() {
		next = NULL;
	};
};



//����
bool in();
//��������Ӧ����ģ�壬��ʾ��ǰ����һ������Ϊcount����Ŀ
bool add_book(book *&book1, int count);
//д����Ŀ����Ϣ
bool input_book_imformation(book *&book1, int cla);
//���ݷ��ഴ��һ������Ŀ
bool create_book(int cla, int num);
//����
bool Delete();
//���ģ��黹
//ͨ��id�����н��飬����
bool borrow_full();
bool borrow_simple();
bool Return();
bool off_shelf(book *&book1);
bool back_to_shelf(book *&book1);
//�����鼮
bool find();
//��ʾ��ǰ������Ŀ
bool show_allbooks();
//��ʾ�ض���Ŀ
bool show_book();
//������Ŀ����
bool findBooksByAuthor(string authorName);
bool findBooksByBookName(string bookName);
bool findBooksByClassification(int cla);
bool findBooksByPublishTime(publishTime time);
bool findBookById(int clas, int id, book*& book1);
//����������ʾ
void main_choice();
void class_choice();
void find_choice();
//�������鼮�ı�׼���
void standard_output(book* book1);
//allocate memory
void Allocate();
//free memory
void Free();
//Judge if the id input is right.
void IDInput(char& cla, int& id);

#endif