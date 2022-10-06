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
		* ÿ��д�붼�����ԭ���ݣ��������Ӧ�ñ������������������뷽ʽ��
		* @return -1˵��δ���������д��ʧ��
		* @return 0˵��д��ɹ�
		*/
		virtual int WriteData(char* data, int data_length);
		virtual int WriteData(MetaData& data);
		//��index����ֻ��ʾ�ļ��ĵڼ���Ԫ���ݣ�û�������κ����壬�����������ļ��ṹ
		virtual MetaData& GetData(int index);
	protected:
		char* file_name_;
		int name_length_;
		int file_length_;	//����Ԫ���ݣ���ʵ���Ǽ��У�
		int bit_num_;		//һ������bit

		ifstream ifs_;
		fstream ofs_;
		//�������ݺ���´�С��Ϣ��size�ǲ����˼�������
		void UpdateSize_(int size = 1);
		void ResetSize_();

		ifstream& GetIfs();
		fstream& GetOfs();
		int OpenIfs();
		//��Ҫ����
		virtual int OpenOfs();
		void CloseIfs();
		void CloseOfs();
	};

	//���ļ��ĵ�һ�д洢����λ�ã�ʹ��\0���зָ�
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
		int index_;	//���� �������е�Ԫ���ݵ�ַ
	};
}