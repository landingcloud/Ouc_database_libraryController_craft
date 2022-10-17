#pragma once
#include "Tools.h"
#include "Books.h"
#include "PeoPles.h"
#include "Dao.h"

#include <list>
using namespace std;

namespace service {
	class BookService {
	public:
		BookService(char* service_name, int name_length);
		BookService(const char* service_name, int name_length);
		~BookService();
		int AddBook(books::BasicBook basicBook);
		int DeleteBook(books::ObjBook objBook);
		int SearchBooks(books::BasicBook basicBook, books::ObjBook* objBooks, int& num);	//objBooks需要开辟空间
		int SearchBooks(books::BasicBook basicBook, list<books::ObjBook>& objBooks);
		int ChangeBooks(books::BasicBook oldBook, books::BasicBook newBook);

		int BorrowBook(books::ObjBook objBook, peoples::BasicPeoPle people);
		int GiveBackBook(books::ObjBook objBook, peoples::BasicPeoPle people);

	private:
		char* service_name_;
		int name_length_;
		dao::HeapFileManager* book_heap_p;
		dao::HashMapManager* isbn_hash_p;
		dao::HashMapManager* name_hash_p;
		dao::HashMapManager* author_hash_p;

		dao::HashMapManager* borrowed_hash_p;
		dao::HashMapManager* borrow_hash_p;
	};
}