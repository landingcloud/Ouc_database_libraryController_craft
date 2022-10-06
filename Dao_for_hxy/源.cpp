#include<iostream>
#include<fstream>
#include<string>
#include"Dao.h"
using namespace std;
#define BUFFER_LENGTH 100
typedef char META[BUFFER_LENGTH];

int FillBuffer(char* buffer, char* con) {
	int index = 0;
	while (con[index]) {
		if (index >= BUFFER_LENGTH)
			return -1;
		buffer[index] = con[index];
		index++;
	}
	return 0;
}

int FillBuffer(char* buffer, const char* con) {
	int index = 0;
	while (con[index]) {
		if (index >= BUFFER_LENGTH)
			return -1;
		buffer[index] = con[index];
		index++;
	}
	buffer[BUFFER_LENGTH - 1] = '\n';
	return 0;
}

namespace dao {
	void test1() {
		MetaData data1 = { 0 };
		MetaData data2 = { 0 };
		MetaData data3 = { 0 };
		MetaData data4 = { 0 };
		FillBuffer(data1, "");
		FillBuffer(data2, "12345诶");
		FillBuffer(data3, "这是第三条数据");
		FillBuffer(data4, "这是第四条数据呢！");
		char fileName[] = "./测试用文件夹/fileManager.txt";
		FileManager fileManager(fileName, sizeof(fileName));
		int w0 = fileManager.WriteData(data4);
		//int o1 = fileManager.OpenOfs();
		int w1 = fileManager.WriteData(data1);
		int w2 = fileManager.WriteData(data2);
		int w3 = fileManager.WriteData(data3);
		int w4 = fileManager.WriteData(data4);
		//fileManager.CloseOfs();
		MetaData& g0 = fileManager.GetData(1);
		//int i0 = fileManager.OpenIfs();
		MetaData& g1 = fileManager.GetData(1);
		cout << "完毕" << endl;
		//fileManager.CloseIfs();
	}



	void test2() {
		MetaData data1 = { 0 };
		MetaData data2 = { 0 };
		MetaData data3 = { 0 };
		MetaData data4 = { 0 };
		MetaData data5 = { 0 };
		FillBuffer(data1, "123");
		FillBuffer(data2, "12345诶、、、");
		FillBuffer(data3, "这是第三条数据@@@");
		FillBuffer(data4, "这是第四条数据呢！￥￥￥");
		FillBuffer(data5, "这是插入数据");
		char fileName[] = "./测试用文件夹/HeapfileManager";
		HeapFileManager heapFileManager(fileName, sizeof(fileName));
		//int o1 = heapFileManager.OpenOfs();
		int w1 = heapFileManager.WriteData(data1);
		int w2 = heapFileManager.WriteData(data2);
		int w3 = heapFileManager.WriteData(data3);
		int w4 = heapFileManager.WriteData(data4);
		/*int w5 = heapFileManager.WriteData(data5);*/
		//heapFileManager.CloseOfs();

		//heapFileManager.OpenIfs();
		MetaData& returnData = heapFileManager.GetData(2);
		cout << returnData << endl;
		//heapFileManager.CloseIfs();

		//heapFileManager.OpenOfs();
		int d2 = heapFileManager.DeleteData(1);
		int d3 = heapFileManager.DeleteData(2);
		int w6 = heapFileManager.WriteData(data5);
		int w7 = heapFileManager.WriteData(data5);
		int w8 = heapFileManager.WriteData(data5);
		//heapFileManager.CloseOfs();
	}
}


int main() {
	dao::test2();
}