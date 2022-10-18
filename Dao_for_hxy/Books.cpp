#include "Books.h"

void books::BasicBook::setISBN(ISBN isbn)
{
	for (int i = 0; i < ISBN_LENGTH; ++i) {
		this->isbn_[i] = isbn[i];
	}
}

void books::BasicBook::setBookName(BookName bookName)
{
	memset(this->book_name_, '\0', BOOKNAME_LENGTH);
	strcpy_s(this->book_name_, BOOKNAME_LENGTH, bookName);
}

void books::BasicBook::setAuthor(Author author)
{
	memset(this->author_, '\0', AUTHOR_LENGTH);
	strcpy_s(this->author_, AUTHOR_LENGTH, author);
}

void books::BasicBook::setPublisher(Publisher publisher)
{
	memset(this->publisher_, '\0', PUBLISHER_LENGTH);
	strcpy_s(this->publisher_, PUBLISHER_LENGTH, publisher);
}

void books::BasicBook::getISBN(ISBN& isbn)
{
	for (int i = 0; i < ISBN_LENGTH; ++i) {
		isbn[i] = this->isbn_[i];
	}
}

void books::BasicBook::getBookName(BookName& bookName)
{
	strcpy_s(bookName, BOOKNAME_LENGTH, this->book_name_);
}

void books::BasicBook::getAuthor(Author& author)
{
	strcpy_s(author, AUTHOR_LENGTH, this->author_);
}

void books::BasicBook::getPublisher(Publisher& publisher)
{
	strcpy_s(publisher, PUBLISHER_LENGTH, this->publisher_);
}

books::BasicBook::BasicBook(ISBN isbn, BookName bookName, Author author, Publisher publisher)
{
	setISBN(isbn);
	setBookName(bookName);
	setAuthor(author);
	setPublisher(publisher);
}

//books::ObjBook::ObjBook(BasicBook* basicBook, int id)
//{
//	ISBN isbn = { 0 };
//	basicBook->getISBN(isbn);
//	BookName bookName = { 0 };
//	basicBook->getBookName(bookName);
//	Author author = { 0 };
//	basicBook->getAuthor(author);
//	Publisher publisher = { 0 };
//	basicBook->getPublisher(publisher);
//	
//
//}

void books::AbstractBook::setTotal(int total, int* ids)
{
	if (ids == NULL)
		return;

	this->total_ = total;
	if (this->ids_p != NULL) {
		delete[] this->ids_p;
	}
	this->ids_p = new int[this->total_];
	for (int i = 0; i < this->total_; ++i) {
		this->ids_p[i] = ids[i];
	}
}

void books::AbstractBook::setEnable(int enable, int* enable_ids)
{
	if (enable_ids == NULL)
		return;
	this->enable_ = enable;
	if (this->enable_ids_p != NULL) {
		delete[] this->enable_ids_p;
	}
	for (int i = 0; i < this->enable_; ++i) {
		this->enable_ids_p[i] = enable_ids[i];
	}
}
