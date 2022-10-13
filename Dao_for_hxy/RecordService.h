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

	//people����book
	int BorrowBook(Book* book, People* people);
	//people����book
	int GiveBackBook(Book* book, People* people);
	//����Ա���һ����
	int AddBook(Book* book, People* people);
	//����Աɾ��һ����
	int DeleteBook(Book* book, People* people);
	
	//people���Լ������
	int LookBorrowedBooks(Book* books, int& num, People* people);
	//people���Լ�������
	int LookBackedBooks(Book* books, int& num, People* people);
	//��book��˭��
	int LookBorrowPeoples(People* peoples, int& num, Book* book);
	//��book��˭��
	int LookBackPeoples(People* peoples, int& num, Book* book);
	
	//�����Ա�����ʲô��
	int LookAddedBoods(Book* books, int& num, People* people);
	//�����Աɾ����ʲô��
	int LookDeletededBooks(Book* books, int& num, People* people);
	//��book��˭�����
	int LookAddPeoples(People* peoples, int& num, Book* book);
	//��book��˭ɾ��
	int LookDeletedPeoples(People* peoples, int& num, Book* book);
	

}