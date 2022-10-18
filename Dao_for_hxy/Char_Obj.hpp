
#pragma execution_character_set("utf-8")
#include <iostream>
#include<sstream> 
#include <string>
#include <cstdio>
#include <regex>
#include "Book.h"
using namespace std;
#define BUFFER_LENGTH 800 
char GET[BUFFER_LENGTH];


char KONG[BUFFER_LENGTH];
string separate = "$$";//�ָ��ַ���
void Begin() {
    for (int i = 0; i < BUFFER_LENGTH; i++) {
        KONG[i] = '#';
    }
}
//�������ַ���ת��
template<typename T> string toString(const T& t) {  //toString(T)
    ostringstream oss;  //����һ����ʽ�������
    oss << t;             //��ֵ����������
    return oss.str();
}
//��book�������Ϊ�����ַ���
string BookToString(Book newBook) {
    string ss;
    Begin();
    ss = ss + newBook.getISBN() + separate;
    ss = ss + newBook.getBookName() + separate;
    ss = ss + newBook.getAuthor() + separate;
    ss = ss + newBook.getPubliser() + separate;
    ss = ss + newBook.getPublishDate() + separate;
    ss = ss + toString(newBook.getBookTotal()) + separate;
    ss = ss + toString(newBook.getBookPrice()) + separate;
    ss = ss + toString(newBook.getBookAvailable()) + separate;
    ss = ss + newBook.getGenre() + separate;
    ss += KONG;
    ss.erase(BUFFER_LENGTH);
    return ss;
}

//��book�������Ϊchar[800]
char* BookToChar(Book newBook, char GET[BUFFER_LENGTH]) {
    string ss = BookToString(newBook);
    for (int i = 0; i < BUFFER_LENGTH; i++)
        GET[i] = ss[i];
    return GET;
}

//�ַ����ָ��
void Stringsplit(const string& str, const string& splits, vector<string>& res)
{
    string strs = str;// +splits;
    size_t pos = strs.find(splits);
    int step = splits.size();

    // ���Ҳ����������ַ��������������� npos
    while (pos != strs.npos)
    {
        string temp = strs.substr(0, pos);
        res.push_back(temp);
        //ȥ���ѷָ���ַ���,��ʣ�µ��ַ����н��зָ�
        strs = strs.substr(pos + step, strs.size());
        pos = strs.find(splits);
    }

}

//stringת��Book����
Book CharToBook(char* GET) {
    string book_find;
    book_find = GET;
    Book bookObj;
    vector<string> strList;
    Stringsplit(book_find, separate, strList);
    bookObj.setISBN(strList.at(0));
    bookObj.setBookName(strList.at(1));
    bookObj.setAuthor(strList.at(2));
    bookObj.setPubliser(strList.at(3));
    bookObj.setPublishDate(strList.at(4));
    bookObj.setBookTotal(stoi(strList.at(5)));
    bookObj.setBookPrice(stod(strList.at(6)));
    bookObj.setBookAvailable(stoi(strList.at(7)));
    bookObj.setGenre(strList.at(8));
    return bookObj;
}