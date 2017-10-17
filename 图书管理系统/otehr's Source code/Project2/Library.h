//created by lixiaoyun
//last update in 2016/03/27
//All rights reserved
//需要补充当用户错误输入的时候要提示用户重新输入，用while（）,fighting
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
	//ID第一位表示分类，后面的数字表示该分类中的第几项
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



//进货
bool in();
//进货，对应进货模板，表示当前进货一批数量为count的数目
bool add_book(book *&book1, int count);
//写入书目的信息
bool input_book_imformation(book *&book1, int cla);
//根据分类创建一个新书目
bool create_book(int cla, int num);
//出货
bool Delete();
//借阅，归还
//通过id来进行借书，还书
bool borrow_full();
bool borrow_simple();
bool Return();
bool off_shelf(book *&book1);
bool back_to_shelf(book *&book1);
//查找书籍
bool find();
//显示当前所有书目
bool show_allbooks();
//显示特定书目
bool show_book();
//查找书目方法
bool findBooksByAuthor(string authorName);
bool findBooksByBookName(string bookName);
bool findBooksByClassification(int cla);
bool findBooksByPublishTime(publishTime time);
bool findBookById(int clas, int id, book*& book1);
//操作界面显示
void main_choice();
void class_choice();
void find_choice();
//搜索后书籍的标准输出
void standard_output(book* book1);
//allocate memory
void Allocate();
//free memory
void Free();
//Judge if the id input is right.
void IDInput(char& cla, int& id);

#endif