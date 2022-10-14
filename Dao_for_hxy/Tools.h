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