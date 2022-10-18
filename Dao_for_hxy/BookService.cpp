#include "BookService.h"
#include <set>
#include <algorithm>

service::BookService::BookService(char* service_name, int name_length)
{
	name_length_ = name_length;
	service_name_ = new char[name_length_];
	strcpy_s(service_name_, name_length_, service_name);

	//建立堆表
	int heapNameLength = strlen("./books/") + name_length_ + strlen("_heap") + 1;
	char* heapName = new char[heapNameLength];
	memset(heapName, 0, heapNameLength);
	strcat_s(heapName, heapNameLength, "./books/");
	strcat_s(heapName, heapNameLength, service_name_);
	strcat_s(heapName, heapNameLength, "_heap");
	this->book_heap_p = new dao::HeapFileManager(heapName, heapNameLength);
	delete[] heapName;
	//建立哈希表
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

	//建立借出hash表，key是书的id，value是人的id
	int borrowed_hashNameLength = strlen("./books/") + name_length_ + strlen("_borrowed_hash") + 1;
	char* borrowed_hashName = new char[borrowed_hashNameLength];
	memset(borrowed_hashName, 0, borrowed_hashNameLength);
	strcat_s(borrowed_hashName, borrowed_hashNameLength, "./books/");
	strcat_s(borrowed_hashName, borrowed_hashNameLength, service_name_);
	strcat_s(borrowed_hashName, borrowed_hashNameLength, "_borrowed_hash");
	this->borrowed_hash_p = new dao::HashMapManager(borrowed_hashName, borrowed_hashNameLength);
	delete[] borrowed_hashName;

	//建立借出hash表，key是人的id，value是书的id
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
	//生成key
	int isbnHash = ISBNHash(basicBook.getthisISBN());
	int bookNameHash = NameHash(basicBook.getthisBookName());
	int authorHash = AuthorHash(basicBook.getthisAuthor());
	//将basicBook添加到堆表，返回index、同时也认为是书的id

	//将index追加到每个hash表的key的后面
	return 0;
}

int service::BookService::DeleteBook(books::ObjBook objBook)
{
	//提取id
	unsigned long id = objBook.getId();
	//在借出hash中查看是否被借出了
	int num = 0;
	Address* address = new Address[BUFFER_LENGTH / ADDRESS_LENGTH];
	if (this->borrowed_hash_p->GetContents(id, num, address) == 0) {
		//成功取出
		this->book_heap_p->DeleteData(id);
		Address bookAddress = { 0 };
		ConverIndex2Address(bookAddress, id);
		//提取出每一个key
		int isbnHash = ISBNHash(objBook.getthisISBN());
		int bookNameHash = NameHash(objBook.getthisBookName());
		int authorHash = AuthorHash(objBook.getthisAuthor());
		this->isbn_hash_p->DeleteContents(isbnHash, bookAddress);
		this->name_hash_p->DeleteContents(bookNameHash, bookAddress);
		this->author_hash_p->DeleteContents(authorHash, bookAddress);
	}
	else {
		//被借出了
		return -1;
	}
	

	//如果没有被借出
	//从堆表删除对应index的书，其中id就是index

	//从每个hash表中删除对应index的书
	return 0;
}

int service::BookService::SearchBooks(books::BasicBook basicBook, books::ObjBook* objBooks, int& num)
{
	//提取出每一个key
	int isbnHash = ISBNHash(basicBook.getthisISBN());
	int bookNameHash = NameHash(basicBook.getthisBookName());
	int authorHash = AuthorHash(basicBook.getthisAuthor());

	//从每个hash表中提取内容（Address）
	Address* address_ISBN = new Address[BUFFER_LENGTH / ADDRESS_LENGTH];
	int isbn_num = 0;
	this->isbn_hash_p->GetContents(isbnHash, isbn_num, address_ISBN);
	
	Address* address_bookName = new Address[BUFFER_LENGTH / ADDRESS_LENGTH];
	int bookName_num = 0;
	this->name_hash_p->GetContents(bookNameHash, bookName_num, address_bookName);

	Address* address_author = new Address[BUFFER_LENGTH / ADDRESS_LENGTH];
	int author_num = 0;
	this->author_hash_p->GetContents(authorHash, author_num, address_author);
	//index取交集

	//index访问堆表获取MetaData，并通过MetaData构建obj

	
	return 0;
}

int service::BookService::SearchBooks(books::BasicBook basicBook, list<books::ObjBook>& objBooks)
{
	//提取出每一个key
	int isbnHash = ISBNHash(basicBook.getthisISBN());
	int bookNameHash = NameHash(basicBook.getthisBookName());
	int authorHash = AuthorHash(basicBook.getthisAuthor());

	//从每个hash表中提取内容（Address）
	Address* address_ISBN = new Address[BUFFER_LENGTH / ADDRESS_LENGTH];
	int isbn_num = 0;
	this->isbn_hash_p->GetContents(isbnHash, isbn_num, address_ISBN);

	Address* address_bookName = new Address[BUFFER_LENGTH / ADDRESS_LENGTH];
	int bookName_num = 0;
	this->name_hash_p->GetContents(bookNameHash, bookName_num, address_bookName);

	Address* address_author = new Address[BUFFER_LENGTH / ADDRESS_LENGTH];
	int author_num = 0;
	this->author_hash_p->GetContents(authorHash, author_num, address_author);

	//index求交集
	set<int> isbnIndex;
	for (int i = 0; i < isbn_num; ++i) {
		isbnIndex.insert(ConverAddress2Index(address_ISBN[i]));
	}
	delete[] address_ISBN;
	set<int> nameIndex;
	for (int i = 0; i < bookName_num; ++i) {
		nameIndex.insert(ConverAddress2Index(address_bookName[i]));
	}
	delete[] address_bookName;
	set<int> authorIndex;
	for (int i = 0; i < author_num; ++i) {
		authorIndex.insert(ConverAddress2Index(address_author[i]));
	}
	delete[] address_author;
	
	set<int> res1;
	set<int> res2;
	set_intersection(isbnIndex.begin(), isbnIndex.end(), nameIndex.begin(), nameIndex.end(), insert_iterator<set<int>>(res1, res1.begin()));
	set_intersection(res1.begin(), res1.end(), authorIndex.begin(), authorIndex.end(), insert_iterator<set<int>>(res2, res2.begin()));
	//获取MetaData
	for (auto it : res2) {
		MetaData metadata = { 0 };
		this->book_heap_p->GetData(metadata, it);

		//objBooks.insert()
	}

	return 0;
}

int service::BookService::ChangeBooks(books::BasicBook oldBook, books::BasicBook newBook)
{
	//通过searchBook找到所有index
	//提取出每一个key
	int isbnHash = ISBNHash(oldBook.getthisISBN());
	int num = 0;
	Address* addresses = new Address[BUFFER_LENGTH / ADDRESS_LENGTH];
	this->isbn_hash_p->GetContents(isbnHash, num, addresses);
	
	//生成新的MetaData
	for (int i = 0; i < num; ++i) {
		int index = ConverAddress2Index(addresses[i]);
		//this->book_heap_p->UpdataData(index, );
	}
	//覆盖
	return 0;
}

int service::BookService::BorrowBook(books::ObjBook objBook, peoples::BasicPeoPle people)
{
	//提取书id号
	int id = objBook.getId();
	//将数据插入被借出hash表中，其中key是书id，value是人
	Address address = { 0 };
	ConverIndex2Address(address, people.getId());
	this->borrowed_hash_p->WriteContents(id, address);
	
	//将数据插入借出hash表中，其中key是人id，value是书
	id = people.getId();
	ConverIndex2Address(address, objBook.getId());
	this->borrow_hash_p->WriteContents(id, address);
	return 0;
}

int service::BookService::GiveBackBook(books::ObjBook objBook, peoples::BasicPeoPle people)
{
	//提取书id号
	int id = objBook.getId();
	//在被借出index下删除
	Address address = { 0 };
	ConverIndex2Address(address, people.getId());
	this->borrowed_hash_p->DeleteContents(id, address);

	//同理，修改借出index
	id = people.getId();
	ConverIndex2Address(address, objBook.getId());
	this->borrow_hash_p->DeleteContents(id, address);

	return 0;
}


