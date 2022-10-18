#include "Book.h"

Book::Book()
{
}

Book::Book(string bookName)
{
    this->bookName = bookName;
}

Book::Book(string bookName, string author)
{
    this->bookName = bookName;
    this->author = author;
}

Book::Book(string bookName, string author, string publisher)
{
    this->bookName = bookName;
    this->author = author;
    this->publisher = publisher;
}

Book::Book(string bookName, string author, string publisher, string publishDate)
{
    this->bookName = bookName;
    this->author = author;
    this->publisher = publisher;
    this->publishDate = publishDate;
}

Book::Book(string bookName, string author, string publisher, string publishDate, string genre)
{
    this->bookName = bookName;
    this->author = author;
    this->publisher = publisher;
    this->publishDate = publishDate;
    this->genre = genre;
}

Book::Book(string bookName, string author, string publisher, string publishDate, string genre, string ISBN)
{
    this->bookName = bookName;
    this->author = author;
    this->publisher = publisher;
    this->publishDate = publishDate;
    this->genre = genre;
    this->ISBN = ISBN;
}

Book::Book(string bookName, string author, string publisher, string publishDate, string genre, string ISBN, int bookTotal)
{
    this->bookName = bookName;
    this->author = author;
    this->publisher = publisher;
    this->publishDate = publishDate;
    this->genre = genre;
    this->ISBN = ISBN;
    this->bookTotal = bookTotal;
}

Book::Book(string bookName, string author, string publisher, string publishDate, string genre, string ISBN, int bookTotal, int bookAvailable)
{
    this->bookName = bookName;
    this->author = author;
    this->publisher = publisher;
    this->publishDate = publishDate;
    this->genre = genre;
    this->ISBN = ISBN;
    this->bookTotal = bookTotal;
    this->bookAvailable = bookAvailable;
}

Book::Book(string bookName, string author, string publisher, string publishDate, string genre, string ISBN, int bookTotal, int bookAvailable, int price)
{
    this->bookName = bookName;
    this->author = author;
    this->publisher = publisher;
    this->publishDate = publishDate;
    this->genre = genre;
    this->ISBN = ISBN;
    this->bookTotal = bookTotal;
    this->bookAvailable = bookAvailable;
    this->price = price;
}

Book::~Book()
{
}

void Book::setBookName(string name)
{
    this->bookName = name;
}

void Book::setAuthor(string author)
{
    this->author = author;
}

void Book::setISBN(string ISBN)
{
    this->ISBN = ISBN;
}

void Book::setGenre(string genre)
{
    this->genre = genre;
}

void Book::setPubliser(string publisher)
{
    this->publisher = publisher;
}

void Book::setBookTotal(int bookTotal)
{
    this->bookTotal = bookTotal;
}

void Book::setBookAvailable(int bookAvailable)
{
    this->bookAvailable = bookAvailable;
}

void Book::setBookPrice(int price)
{
    this->price = price;
}

void Book::setPublishDate(string publishDate)
{
    this->publishDate = publishDate;
}

string Book::getBookName()
{
    return this->bookName;
}

string Book::getAuthor()
{
    return this->author;
}

string Book::getISBN()
{
    return this->ISBN;
}

string Book::getGenre()
{
    return this->genre;
}

string Book::getPubliser()
{
    return this->publisher;
}

string Book::getPublishDate()
{
    return this->publishDate;
}

int Book::getBookTotal()
{
    return this->bookTotal;
}

int Book::getBookAvailable()
{
    return this->bookAvailable;
}

int Book::getBookPrice()
{
    return this->price;
}