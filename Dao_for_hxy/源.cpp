#include<iostream>
#include"Configuration.h"
#include"Tools.h"
#include<fstream>
#include"Dao.h"

using namespace std;

void test(MetaData& metadata) {
	memset(metadata, '1', BUFFER_LENGTH - 1);
}

void test1() {
	char* data = new char[10]{ 0 };
	strcat_s(data, 10, "123");
	MetaData metadata = { 0 };
	ConverCharS2Meta(metadata, data, 10);
	cout << metadata;
}

int AddAddress2Meta(MetaData& metadata, Address address)
{
	for (int i = 0; i < BUFFER_LENGTH; i += ADDRESS_LENGTH) {
		if (metadata[i] == '\0') {
			for (int j = 0; j < ADDRESS_LENGTH; ++j) {
				metadata[i + j] = address[j];
			}
			return 0;
		}
		
	}
	return -1;
}
int SplitMeta2Address(MetaData metadata, int& num,  Address* addresses)
{
	num = 0;
	char** temp = new char*[BUFFER_LENGTH / ADDRESS_LENGTH];	//×î´ónumÊý
	for (int i = 0; i < BUFFER_LENGTH / ADDRESS_LENGTH; i += 1) {
		temp[i] = new char[ADDRESS_LENGTH] { 0 };
		if (metadata[i * ADDRESS_LENGTH] != '\0') {
			++num;
			for (int j = 0; j < ADDRESS_LENGTH; ++j) {
				temp[i][j] = metadata[i * ADDRESS_LENGTH + j];
			}
		}
	}
	
	for (int i = 0; i < num; ++i) {
		strcpy_s(addresses[i], ADDRESS_LENGTH, temp[i]);
		delete[] temp[i];
	}
	delete[] temp;
	return 0;
}
void test2() {
	MetaData metadata = { 0 };
	Address address1 = { '1', '2', '3', '4', '5', '6', '7', '\0' };
	Address address2 = { '8', '7', '6', '5', '4', '3', '2', '\0' };
	AddAddress2Meta(metadata, address1);
	cout << metadata << endl;
	AddAddress2Meta(metadata, address2);
	cout << metadata << endl;
	cout << endl;
	Address* addresses = new Address[BUFFER_LENGTH / ADDRESS_LENGTH];
	int num = 0;
	SplitMeta2Address(metadata, num, addresses);
	for (int i = 0; i < num; i++) {
		cout << addresses[i] << endl;
	}
	
}

void test3_2(int* ints) {
	ints = new int[3];
	ints[0] = 0;
	ints[1] = 1;
	ints[2] = 2;
}

void test3() {
	int* ints = NULL;
	test3_2(ints);
	cout << ints;
}

void test5() {
	const char* string= "123456\n";
	
	fstream fs;
	fs.open("test.txt", ios::in | ios::out | ios::binary);
	fs.clear();
	fs.seekp(sizeof("123456\n") * 8, ios::beg);
	fs.write(string, sizeof("123456\n"));
	fs.close();
}

void test6() {
	dao::HashMapManager hashMapManager("hashtest.txt", sizeof("hashtest.txt"));
	Address address1 = { '1', '2', '3', '4', '5', '6', '7', '\0' };
	Address address2 = { '8', '7', '6', '5', '4', '3', '2', '\0' };
	Address address3 = { '1', '1', '4', '5', '1', '4', '\0', '\0' };
	hashMapManager.WriteContents(2, address1);
	hashMapManager.WriteContents(2, address2);
	hashMapManager.WriteContents(4, address3);
	int num = 0;
	Address* addresses = new Address[BUFFER_LENGTH / ADDRESS_LENGTH];
	hashMapManager.GetContents(2, num, addresses);
	for (int i = 0; i < num; i++) {
		cout << addresses[i] << endl;
	}
	hashMapManager.DeleteContents(2, address2);
}

int test7() {
	const char* service_name_ = "12345";
	int name_length_ = strlen(service_name_);
	int heapNameLength = strlen("./books/") + name_length_ + strlen("_heap") + 1;
	char* heapName = new char[heapNameLength];
	memset(heapName, 0, heapNameLength);
	strcat_s(heapName, heapNameLength, "./books/");
	strcat_s(heapName, heapNameLength, service_name_);
	strcat_s(heapName, heapNameLength, "_heap");
	cout << heapName;
	return 0;
}
int main() {
	
	test7();

}
