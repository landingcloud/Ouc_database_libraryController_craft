#include "Tools.h"

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
	// TODO: �ڴ˴����� return ���
	try {
		memcpy_s(metadata, BUFFER_LENGTH, data, data_length);
		metadata[BUFFER_LENGTH - 1] = '\n';	//�ÿ�,���зֿ�����ʵûɶ��Ҫ
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
		printf("ISBN���Ȳ��Ϸ�");
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
			printf("ISBN���Ϸ�");

		return -1;
	}
}

char* ConverMeta2Chars(MetaData metadata)
{
	char* data = NULL;
	return nullptr;
}