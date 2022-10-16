#include "BookService.h"

service::BookService::BookService(char* service_name, int name_length)
{
	name_length_ = name_length;
	service_name_ = new char[name_length_];
	strcpy_s(service_name_, name_length_, service_name);

	//�����ѱ�
	int heapNameLength = strlen("./books/") + name_length_ + strlen("_heap") + 1;
	char* heapName = new char[heapNameLength];
	memset(heapName, 0, heapNameLength);
	strcat_s(heapName, heapNameLength, "./books/");
	strcat_s(heapName, heapNameLength, service_name_);
	strcat_s(heapName, heapNameLength, "_heap");
	this->book_heap_p = new dao::HeapFileManager(heapName, heapNameLength);
	delete[] heapName;
	//������ϣ��
	int isbn_hashNameLength = strlen("./books/") + name_length_ + strlen("_isbn_hash") + 1;
	char* isbn_hashName = new char[isbn_hashNameLength];
	memset(isbn_hashName, 0, isbn_hashNameLength);
	strcat_s(isbn_hashName, isbn_hashNameLength, "./books/");
	strcat_s(isbn_hashName, isbn_hashNameLength, service_name_);
	strcat_s(isbn_hashName, isbn_hashNameLength, "_isbn_hash");
	this->isbn_hash_p = new dao::HashMapManager(isbn_hashName, isbn_hashNameLength);
	delete[] isbn_hashName;

	int name_hashNameLength = strlen("./books/") + name_length_ + strlen("_name_hash") + 1;
	char* name_hashName = new char[name_hashNameLength];
	memset(name_hashName, 0, name_hashNameLength);
	strcat_s(name_hashName, name_hashNameLength, "./books/");
	strcat_s(name_hashName, name_hashNameLength, service_name_);
	strcat_s(name_hashName, name_hashNameLength, "_name_hash");
	this->name_hash_p = new dao::HashMapManager(name_hashName, name_hashNameLength);
	delete[] name_hashName;

	int author_hashNameLength = strlen("./books/") + name_length_ + strlen("_author_hash") + 1;
	char* author_hashName = new char[author_hashNameLength];
	memset(author_hashName, 0, author_hashNameLength);
	strcat_s(author_hashName, author_hashNameLength, "./books/");
	strcat_s(author_hashName, author_hashNameLength, service_name_);
	strcat_s(author_hashName, author_hashNameLength, "_author_hash");
	this->author_hash_p = new dao::HashMapManager(author_hashName, author_hashNameLength);
	delete[] author_hashName;

	//�������hash��key�����id��value���˵�id
	int borrowed_hashNameLength = strlen("./books/") + name_length_ + strlen("_borrowed_hash") + 1;
	char* borrowed_hashName = new char[borrowed_hashNameLength];
	memset(borrowed_hashName, 0, borrowed_hashNameLength);
	strcat_s(borrowed_hashName, borrowed_hashNameLength, "./books/");
	strcat_s(borrowed_hashName, borrowed_hashNameLength, service_name_);
	strcat_s(borrowed_hashName, borrowed_hashNameLength, "_borrowed_hash");
	this->borrowed_hash_p = new dao::HashMapManager(borrowed_hashName, borrowed_hashNameLength);
	delete[] borrowed_hashName;

	//�������hash��key���˵�id��value�����id
	int borrow_hashNameLength = strlen("./books/") + name_length_ + strlen("_borrow_hash") + 1;
	char* borrow_hashName = new char[borrow_hashNameLength];
	memset(borrow_hashName, 0, borrow_hashNameLength);
	strcat_s(borrow_hashName, borrow_hashNameLength, "./books/");
	strcat_s(borrow_hashName, borrow_hashNameLength, service_name_);
	strcat_s(borrow_hashName, borrow_hashNameLength, "_borrow_hash");
	this->borrow_hash_p = new dao::HashMapManager(borrow_hashName, borrow_hashNameLength);
	delete[] borrow_hashName;
}

service::BookService::~BookService()
{
	delete[] service_name_;
	delete book_heap_p;
	delete isbn_hash_p;
	delete name_hash_p;
	delete author_hash_p;
	delete borrowed_hash_p;
}

int service::BookService::AddBook(books::BasicBook basicBook)
{
	//����key

	//��basicBook��ӵ��ѱ�����index��ͬʱҲ��Ϊ�����id

	//��index׷�ӵ�ÿ��hash���key�ĺ���
	return 0;
}

int service::BookService::DeleteBook(books::ObjBook objBook)
{
	//��ȡid

	//�ڽ��hash�в鿴�Ƿ񱻽����

	//���û�б����
	//�Ӷѱ�ɾ����Ӧindex���飬����id����index

	//��ÿ��hash����ɾ����Ӧindex����
	return 0;
}

int service::BookService::SearchBooks(books::BasicBook basicBook, books::ObjBook* objBooks, int& num)
{
	//��ȡ��ÿһ��key

	//��ÿ��hash������ȡ���ݣ�������ȡindex��

	//indexȥ��

	//ʣ�µ�index��������objBooks
	return 0;
}

int service::BookService::ChangeBooks(books::BasicBook oldBook, books::BasicBook newBook)
{
	//ͨ��searchBook�ҵ�����index
	
	//����
	return 0;
}

int service::BookService::BorrowBook(books::ObjBook objBook, peoples::BasicPeoPle people)
{
	//��ȡid��

	//��id������hash���У�����key��id��value����

	return 0;
}

int service::BookService::GiveBackBook(books::ObjBook objBook, peoples::BasicPeoPle people)
{
	//��ȡindex

	//�ڽ��index��ɾ��
	return 0;
}


