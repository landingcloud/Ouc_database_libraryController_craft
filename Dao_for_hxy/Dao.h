#pragma once
#include<iostream>
#include<fstream>

#include<list>
#include<set>
using namespace std;

#define BUFFER_LENGTH 100
typedef char MetaData[BUFFER_LENGTH];


namespace dao {
	class FileManager {
	public:
		FileManager(char* file_name, int name_length);
		FileManager(const char* file_name, int name_length);
		~FileManager();
		char* GetFileName();
		int GetNameLength();
		int GetFileLength();
		int GetBitNum();
		
		MetaData& ConverCharS2Meta(char* data, int data_length);
		char* ConverMeta2Chars(MetaData metadata);
		/*
		* 每次写入都会清空原数据，这个函数应该被重载以适用其他插入方式。
		* @return -1说明未打开输出流，写入失败
		* @return 0说明写入成功
		*/
		virtual int WriteData(char* data, int data_length);
		virtual int WriteData(MetaData& data);
		//此index仅仅只表示文件的第几个元数据，没有其他任何意义，具体意义结合文件结构
		virtual MetaData& GetData(int index);
	protected:
		char* file_name_;
		int name_length_;
		int file_length_;	//几个元数据（其实就是几行）
		int bit_num_;		//一共多少bit

		ifstream ifs_;
		fstream ofs_;
		//插入数据后更新大小信息，size是插入了几个数据
		void UpdateSize_(int size = 1);
		void ResetSize_();

		ifstream& GetIfs();
		fstream& GetOfs();
		int OpenIfs();
		//需要重载
		virtual int OpenOfs();
		void CloseIfs();
		void CloseOfs();
	};

	//堆文件的第一行存储空闲位置，使用\0进行分割
	class HeapFileManager : public FileManager {
	public:
		HeapFileManager(char* file_name, int name_length);
		HeapFileManager(const char* file_name, int name_length);
		~HeapFileManager();
		const set<int> GetVoidPos() { return move(void_pos_); }

		
		virtual int WriteData(char* data, int data_length);
		virtual int WriteData(MetaData& metadata);
		int DeleteData(int index);

	private:
		set<int> void_pos_;
		char* void_pos_file_name_;
		int void_pos_file_name_length_;

		void ReadVoidPos_();
		void UpdataVoidPos_();

		int OpenOfs();
	};

	class HashMapManager : public FileManager {
	public:
		HashMapManager(char* file_name, int name_length) : FileManager(file_name, name_length), index_(-1) {}
		HashMapManager(const char* file_name, int name_length) : FileManager(file_name, name_length), index_(-1) {}
		int GetIndex() { return index_; }

		int WriteData(int index, MetaData content);

	private:
		int index_;	//返回 堆数据中的元数据地址
	};
}