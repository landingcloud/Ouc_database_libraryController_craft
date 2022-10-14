#pragma once
#include<iostream>
#include"Configuration.h"

using namespace std;

namespace books {
	class BasicBook {
	public:
		void setISBN(ISBN isbn);
		void setBookName(BookName bookName);
		void setAuthor(Author author);
		void setPublisher(Publisher publisher);

		void getISBN(ISBN& isbn);
		void getBookName(BookName& bookName);
		void getAuthor(Author& author);
		void getPublisher(Publisher& publisher);

		BasicBook(ISBN isbn, BookName bookName, Author author, Publisher publisher);

	protected:
		ISBN isbn_;
		BookName book_name_;
		Author author_;
		Publisher publisher_;
	};

	class AbstractBook : public BasicBook {
	public:
		static void setTotal(int total) { total_s = total; }
		static void setEnable(int enable) { enable_s = enable; }

		int getTotal() { return total_s; };
		int getEnable() { return enable_s; };
		
		AbstractBook(ISBN isbn, BookName bookName, Author author, Publisher publisher, int total, int enable) :
			BasicBook(isbn, bookName, author, publisher) {
			total_s = total;
			enable_s = enable;
		}

	private:
		static int total_s;
		static int enable_s;
	};

	class ObjBook : public BasicBook {
	public:
		void setId(int id) { this->id_ = id; }
		int getId(int id) { return id; }
		ObjBook(ISBN isbn, BookName bookName, Author author, Publisher publisher, int id) :
			BasicBook(isbn, bookName, author, publisher), id_(id) {}
	private:
		int id_;
	};
}