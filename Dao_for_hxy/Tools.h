#pragma once
#include <iostream>
#include "Configuration.h"

void CharsExpand(char* dst, int& dstLength, char* src, int srcLength, char* adder, int adderLength);
void CharsExpand(char* dst, int& dstLength, char* src, int srcLength, const char* adder);
int ConverCharS2Meta(MetaData& metadata, char* data, int data_length);
int ConverCharS2BookName(BookName& bookname, char* data, int data_length);
int ConverCharS2Author(Author& author, char* data, int data_length);
int ConverCharS2Publisher(Publisher& publisher, char* data, int data_length);
int ConverCharS2ISBN(ISBN& isbn, char* data, int data_length = 13);
char* ConverMeta2Chars(MetaData metadata);
bool IsAddressSame(Address address1, Address address2);
unsigned long ConverAddress2Index(Address address);
void ConverIndex2Address(Address& address, unsigned long index);
// DJB Hash Function
unsigned int DJBHash(char* str);
unsigned int ISBNHash(ISBN isbn);
unsigned int NameHash(BookName bookName);
unsigned int AuthorHash(Author author);
unsigned int PublisherHash(Publisher publisher);