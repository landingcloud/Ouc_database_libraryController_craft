#include "Tools.h"
#include <vector>

//不确定能不能用
void CharsExpand(char* dst, int& dstLength, char* src, int srcLength, char* adder, int adderLength)
{
	int totalLength = srcLength + adderLength;
	char* finalChar = new char[totalLength];
	strcat_s(finalChar, srcLength, src);
	strcat_s(finalChar, totalLength, adder);
	
	dstLength = totalLength;
	if (dst != NULL)
		delete[] dst;
	dst = finalChar;
}
//不确定能不能用
void CharsExpand(char* dst, int& dstLength, char* src, int srcLength, const char* adder)
{
	int totalLength = dstLength + strlen(adder);

	char* finalChar = new char[totalLength];
	strcat_s(finalChar, srcLength, src);
	strcat_s(finalChar, totalLength, adder);

	dstLength = totalLength;
	if (dst != NULL)
		delete[] dst;
	dst = finalChar;
}

int ConverCharS2Meta(MetaData& metadata, char* data, int data_length)
{
	// TODO: 在此处插入 return 语句
	try {
		memcpy_s(metadata, BUFFER_LENGTH, data, data_length);
		metadata[BUFFER_LENGTH - 1] = '\n';	//好看,按行分开，其实没啥必要
		return 0;
	}
	catch (int e) {
		return -1;
	}
	
}
int ConverCharS2BookName(BookName& bookname, char* data, int data_length)
{
	try {
		memcpy_s(bookname, BOOKNAME_LENGTH, data, data_length);
		return 0;
	}
	catch (int e) {
		return -1;
	}
}
int ConverCharS2Author(Author& author, char* data, int data_length)
{
	try {
		memcpy_s(author, AUTHOR_LENGTH, data, data_length);
		return 0;
	}
	catch (int e) {
		return -1;
	}
}
int ConverCharS2Publisher(Publisher& publisher, char* data, int data_length)
{
	try {
		memcpy_s(publisher, PUBLISHER_LENGTH, data, data_length);
		return 0;
	}
	catch (int e) {
		return -1;
	}
}

int ConverCharS2ISBN(ISBN& isbn, char* data, int data_length)
{
	if (data_length != 13) {
		printf("ISBN长度不合法");
		return -1;
	}
	try {
		for (int i = 0; i < data_length; ++i) {
			int t = data[i] - '0';
			if (t < 0 || t > 9) {
				throw(-1);
			}
			isbn[i] = t;
		}
		return 0;
	}
	catch (int e) {
		if (e == -1)
			printf("ISBN不合法");

		return -1;
	}
}

char* ConverMeta2Chars(MetaData metadata)
{
	char* data = NULL;
	return nullptr;
}

bool IsAddressSame(Address address1, Address address2)
{
	try {
		for (int i = 0; i < ADDRESS_LENGTH; ++i) {
			if (address1[i] != address2[i])
				return false;
		}
		return true;
	}
	catch(int e){
		printf("某个地址为空");
		return false;
	}
	
}

unsigned long ConverAddress2Index(Address address)
{
	unsigned long sum = 0;
	for (int i = 0; i < ADDRESS_LENGTH && address[i] != '\0'; ++i) {
		sum *= 10;
		sum += address[i] - '0';
	}
	return sum;
}

void ConverIndex2Address(Address& address, unsigned long index)
{
	if (address == NULL)
		return;
	std::vector<int> perNum;
	while (index) {
		perNum.push_back(index % 10);
		index /= 10;
	}
	for (int i = perNum.size() - 1; i >= 0; --i) {
		address[i] = perNum[i] + '0';
	}

}


unsigned int DJBHash(char* str)
{
	unsigned int hash = 5381;

	while (*str)
	{
		hash += (hash << 5) + (*str++);
	}

	return (hash & 0x7FFFFFFF);
}

unsigned int ISBNHash(ISBN isbn)
{
	unsigned int hash = 5381;
	for (int i = 0; i < ISBN_LENGTH; ++i) {
		hash += (hash << 5) + isbn[i];
	}
	return (hash & 0x7FFFFFFF);
}

unsigned int NameHash(BookName bookName)
{
	unsigned int hash = 5381;
	for (int i = 0; i < BOOKNAME_LENGTH; ++i) {
		hash += (hash << 5) + bookName[i];
	}
	return (hash & 0x7FFFFFFF);
}

unsigned int AuthorHash(Author author)
{
	unsigned int hash = 5381;
	for (int i = 0; i < AUTHOR_LENGTH; ++i) {
		hash += (hash << 5) + author[i];
	}
	return (hash & 0x7FFFFFFF);
}

unsigned int PublisherHash(Publisher publisher)
{
	unsigned int hash = 5381;
	for (int i = 0; i < PUBLISHER_LENGTH; ++i) {
		hash += (hash << 5) + publisher[i];
	}
	return (hash & 0x7FFFFFFF);
}
