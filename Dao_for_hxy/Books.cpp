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
