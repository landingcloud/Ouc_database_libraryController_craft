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
		void setTotal(int total) { total_ = total; }
		void setEnable(int enable) { enable_ = enable; }

		int getTotal() { return total_; };
		int getEnable() { return enable_; };
		
		AbstractBook(ISBN isbn, BookName bookName, Author author, Publisher publisher, int total, int enable) :
			BasicBook(isbn, bookName, author, publisher),
			total_(total), enable_(enable), ids_p(NULL), enable_ids_p(NULL) {}

		~AbstractBook() {
			if (ids_p != NULL) {
				delete[] ids_p;
				ids_p = NULL;
			}

			if (enable_ids_p != NULL) {
				delete[] enable_ids_p;
				enable_ids_p = NULL;
			}
		}

	private:
		int total_;
		int enable_;

		int* ids_p;
		int* enable_ids_p;
	};

	class ObjBook : public BasicBook {
	public:
		void setId(int id) { this->id_ = id; }
		int getId(int id) { return id; }
		void setIsBorrowed(bool isBorrowed) { this->is_borrowed_ = isBorrowed; }
		bool getIsBorrowed() { return this->is_borrowed_; }
		ObjBook(ISBN isbn, BookName bookName, Author author, Publisher publisher, int id) :
			BasicBook(isbn, bookName, author, publisher), id_(id), is_borrowed_(0) {}
		//ObjBook(BasicBook* basicBook, int id);
	private:
		int id_;
		bool is_borrowed_;
	};
}