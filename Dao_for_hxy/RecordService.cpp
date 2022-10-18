
#include "RecordService.h"
#include "Tools.h"

service::RecordService::RecordService(char* serviceName, int nameLength)
{
	service_name_ = new char[nameLength];
	name_length_ = nameLength;
	memcpy_s(service_name_, name_length_, serviceName, nameLength);

	/*int heapNameLength = name_length_ + sizeof("_heap");
	char* heapName = new char[heapNameLength];
	memset(heapName, 0, heapNameLength);
	strcat_s(heapName, name_length_, service_name_);
	strcat_s(heapName, heapNameLength, "_heap");
	heap_p = new dao::HeapFileManager(heapName, heapNameLength);*/

	//�����ѱ�
	int heapNameLength = 0;
	char* heapName = { 0 };
	CharsExpand(heapName, heapNameLength, service_name_, name_length_, "_heap");
	heap_p = new dao::HeapFileManager(heapName, heapNameLength);
	//����people��ϣ��
	int peoHashNameLength;
	char* peoHash = NULL;
	CharsExpand(peoHash, peoHashNameLength, service_name_, name_length_, "_peo_hash");
	peo_hash_p = new dao::HashMapManager(peoHash, peoHashNameLength);
	//����book��ϣ��
	int bookHashNameLength;
	char* bookHash = NULL;
	CharsExpand(bookHash, bookHashNameLength, service_name_, name_length_, "_book_hash");
	book_hash_p = new dao::HashMapManager(bookHash, bookHashNameLength);
}

service::RecordService::RecordService(const char* serviceName)
{
	service_name_ = new char[strlen(serviceName)];
	name_length_ = strlen(serviceName);
	memcpy_s(service_name_, name_length_, serviceName, strlen(serviceName));

	//�����ѱ�
	int heapNameLength;
	char* heapName = NULL;
	CharsExpand(heapName, heapNameLength, service_name_, name_length_, "_heap");
	heap_p = new dao::HeapFileManager(heapName, heapNameLength);
	//����people��ϣ��
	int peoHashNameLength;
	char* peoHash = NULL;
	CharsExpand(peoHash, peoHashNameLength, service_name_, name_length_, "_peo_hash");
	peo_hash_p = new dao::HashMapManager(peoHash, peoHashNameLength);
	//����book��ϣ��
	int bookHashNameLength;
	char* bookHash = NULL;
	CharsExpand(bookHash, bookHashNameLength, service_name_, name_length_, "_book_hash");
	book_hash_p = new dao::HashMapManager(bookHash, bookHashNameLength);
}

service::RecordService::~RecordService()
{
	delete heap_p;
	delete peo_hash_p;
	delete book_hash_p;
	delete[] service_name_;
}

int service::RecordService::AddRecord(Book* book, People* people)
{
	//������˱��MetaData��
	//MetaData metadata = { 0 };
	//��metadata��ӵ��ѱ�
	//int index = heap_p->WriteData(metadata);
	//��bookHash�н���������
	//int key;
	//book_hash_p->WriteContents(key, index);
	//��peopleHash�н���������

	return 0;
}

int service::RecordService::SearchRecordByPeo(int& num, char** metadatas, People* people)
{
	//�����ֵ
	int key;
	int* indexs;
	//peo_hash_p->GetContents(key, num, indexs);
	//��ȡmetadata
	metadatas = new char*[num];
	for (int i = 0; i < num; ++i) {
		metadatas[i] = new char[BUFFER_LENGTH];
		//strcpy_s(metadatas[i], BUFFER_LENGTH, heap_p->GetData(indexs[i]));
	}

	return 0;
}

int service::RecordService::SearchRecordByBook(int& num, char** metadatas, Book* book)
{
	//�����ֵ
	int key;
	int* indexs;
	//book_hash_p->GetContents(key, num, indexs);
	//��ȡmetadata
	metadatas = new char* [num];
	for (int i = 0; i < num; ++i) {
		metadatas[i] = new char[BUFFER_LENGTH];
		//strcpy_s(metadatas[i], BUFFER_LENGTH, heap_p->GetData(indexs[i]));
	}
	return 0;
}

int service::RecordService::GetALL(char** metadatas, int& num)
{
	return heap_p->GetAllData(metadatas, num);
}

int service::BorrowBook(Book* book, People* people)
{
	
	RecordService recordService("Borrow");
	//����book�Ĺ�ϣֵ

	//����people�Ĺ�ϣֵ

	//�����ַ���
	return 0;
}
