#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book
{
private:

    string bookName;    //书名
    string author;      //作者
    string publisher;   //出版社名
    string publishDate; //出版日期
    string genre;       //类型
    string ISBN;        //ISBN
    int bookTotal;      //书的库存
    int bookAvailable;  //可借阅书
    int price;          //价格
public:
    Book();
    Book(string bookName);
    Book(string bookName, string author);
    Book(string bookName, string author, string publisher);
    Book(string bookName, string author, string publisher, string publishDate);
    Book(string bookName, string author, string publisher, string publishDate, string genre);
    Book(string bookName, string author, string publisher, string publishDate, string genre, string ISBN);
    Book(string bookName, string author, string publisher, string publishDate, string genre, string ISBN, int bookTotal);
    Book(string bookName, string author, string publisher, string publishDate, string genre, string ISBN, int bookTotal, int bookAvailable);
    Book(string bookName, string author, string publisher, string publishDate, string genre, string ISBN, int bookTotal, int bookAvailable, int price);
    ~Book();

    void setBookName(string name);
    void setAuthor(string author);
    void setISBN(string ISBN);
    void setGenre(string genre);
    void setPubliser(string publisher);
    void setPublishDate(string publishDate);
    void setBookTotal(int bookTotal);
    void setBookAvailable(int bookAvailbale);
    void setBookPrice(int price);
    void setId(int id);

    string getBookName();
    string getAuthor();
    string getISBN();
    string getGenre();
    string getPubliser();
    string getPublishDate();
    int getBookTotal();
    int getBookAvailable();
    int getBookPrice();
    int getId();

};

#endif