
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
string separate = "$$";//分隔字符串
void Begin() {
    for (int i = 0; i < BUFFER_LENGTH; i++) {
        KONG[i] = '#';
    }
}
//其他向字符串转换
template<typename T> string toString(const T& t) {  //toString(T)
    ostringstream oss;  //创建一个格式化输出流
    oss << t;             //把值传递如流中
    return oss.str();
}
//将book对象更改为定长字符串
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

//将book对象更改为char[800]
char* BookToChar(Book newBook, char GET[BUFFER_LENGTH]) {
    string ss = BookToString(newBook);
    for (int i = 0; i < BUFFER_LENGTH; i++)
        GET[i] = ss[i];
    return GET;
}

//字符串分割函数
void Stringsplit(const string& str, const string& splits, vector<string>& res)
{
    string strs = str;// +splits;
    size_t pos = strs.find(splits);
    int step = splits.size();

    // 若找不到内容则字符串搜索函数返回 npos
    while (pos != strs.npos)
    {
        string temp = strs.substr(0, pos);
        res.push_back(temp);
        //去掉已分割的字符串,在剩下的字符串中进行分割
        strs = strs.substr(pos + step, strs.size());
        pos = strs.find(splits);
    }

}

//string转换Book对象
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