#pragma once
#include<iostream>
#include<fstream>
#include<set>
#include"Configuration.h"
using namespace std;



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
		
		int GetAllData(char** metadatas, int& num);
		/*
		* ÿ��д�붼�����ԭ���ݣ��������Ӧ�ñ������������������뷽ʽ��
		* @return -1˵��δ���������д��ʧ��
		* @return 0˵��д��ɹ�
		*/
		virtual int WriteData(char* data, int data_length);
		virtual int WriteData(MetaData& data);
		//��index����ֻ��ʾ�ļ��ĵڼ���Ԫ���ݣ�û�������κ����壬�����������ļ��ṹ
		virtual int GetData(MetaData& metadata, int index);
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
		int UpdataData(int index, char* data, int data_length);
		int UpdataData(int index, MetaData& metadata);
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
		HashMapManager(char* file_name, int name_length) : FileManager(file_name, name_length){}
		HashMapManager(const char* file_name, int name_length) : FileManager(file_name, name_length){}

		//int WriteData(int index, MetaData content);
		int GetContents(int key, int& num, int* indexs);
		int WriteContents(int key, int value);


	private:
		
	};
}