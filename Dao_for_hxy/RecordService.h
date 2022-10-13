#pragma once
#include "Dao.h"
using namespace std;

class Book;
class People;

namespace service {
	class RecordService {
	public:
		RecordService(char* serviceName, int nameLength);
		RecordService(const char* serviceName);
		~RecordService();
		int AddRecord(Book* book, People* people);
		int SearchRecordByPeo(int& num, char** metadatas, People* people);
		int SearchRecordByBook(int& num, char** metadatas, Book* book);
		int GetALL(char** metadatas, int& num);
	private:
		char* service_name_;
		int name_length_;
		dao::HeapFileManager* heap_p;
		dao::HashMapManager* peo_hash_p;
		dao::HashMapManager* book_hash_p;
	};

	//people借书book
	int BorrowBook(Book* book, People* people);
	//people还书book
	int GiveBackBook(Book* book, People* people);
	//管理员添加一本书
	int AddBook(Book* book, People* people);
	//管理员删除一本书
	int DeleteBook(Book* book, People* people);
	
	//people查自己借的书
	int LookBorrowedBooks(Book* books, int& num, People* people);
	//people查自己还的书
	int LookBackedBooks(Book* books, int& num, People* people);
	//查book被谁借
	int LookBorrowPeoples(People* peoples, int& num, Book* book);
	//查book被谁还
	int LookBackPeoples(People* peoples, int& num, Book* book);
	
	//查管理员添加了什么书
	int LookAddedBoods(Book* books, int& num, People* people);
	//查管理员删除了什么书
	int LookDeletededBooks(Book* books, int& num, People* people);
	//查book被谁添加了
	int LookAddPeoples(People* peoples, int& num, Book* book);
	//查book被谁删了
	int LookDeletedPeoples(People* peoples, int& num, Book* book);
	

}