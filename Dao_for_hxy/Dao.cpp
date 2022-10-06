#include "Dao.h"

dao::FileManager::FileManager(char* file_name, int name_length)
{
	file_name_ = new char[name_length];
	name_length_ = name_length;
	memcpy_s(file_name_, name_length, file_name, name_length);
	ResetSize_();
	
	OpenIfs();
	ifs_.seekg(0, ios::end);
	bit_num_ = ifs_.tellg();
	file_length_ = bit_num_ / BUFFER_LENGTH;
	CloseIfs();
}

dao::FileManager::FileManager(const char* file_name, int name_length)
{
	file_name_ = new char[name_length];
	name_length_ = name_length;
	memcpy_s(file_name_, name_length, file_name, name_length);
	ResetSize_();

	OpenIfs();
	ifs_.seekg(0, ios::end);
	bit_num_ = ifs_.tellg();
	file_length_ = bit_num_ / BUFFER_LENGTH;
	CloseIfs();
}

dao::FileManager::~FileManager()
{
	this->CloseIfs();
	this->CloseOfs();
	delete[] file_name_;
}

char* dao::FileManager::GetFileName()
{
	return file_name_;
}

int dao::FileManager::GetNameLength()
{
	return name_length_;
}

int dao::FileManager::GetFileLength()
{
	return file_length_;
}

int dao::FileManager::GetBitNum()
{
	return bit_num_;
}

ifstream& dao::FileManager::GetIfs()
{
	// TODO: �ڴ˴����� return ���
	return ifs_;
}

fstream& dao::FileManager::GetOfs()
{
	// TODO: �ڴ˴����� return ���
	return ofs_;
}

int dao::FileManager::OpenIfs()
{
	ofs_.close();
	ifs_.open(file_name_, ios::in | ios::binary);
	if (ifs_.is_open()) {
		return 0;
	}
	return -1;
}

int dao::FileManager::OpenOfs()
{
	ifs_.close();
	ofs_.open(file_name_, ios::out | ios::binary);
	if (!ofs_.is_open()) {
		return -1;
	}
	ResetSize_();
	return 0;
}

void dao::FileManager::CloseIfs()
{
	ifs_.close();
}

void dao::FileManager::CloseOfs()
{
	ofs_.close();
}

MetaData& dao::FileManager::ConverCharS2Meta(char* data, int data_length)
{
	// TODO: �ڴ˴����� return ���
	MetaData metadata = { 0 };
	memcpy_s(metadata, BUFFER_LENGTH, data, data_length);
	metadata[BUFFER_LENGTH - 1] = '\n';	//�ÿ�,���зֿ�����ʵûɶ��Ҫ
	return metadata;
}
char* dao::FileManager::ConverMeta2Chars(MetaData metadata)
{
	char* data = NULL;
	return nullptr;
}
/*
* ֻ����β���������ݣ��������Ӧ�ñ������������������뷽ʽ��
* @return -1˵��δ�������������ʧ��
* @return 0˵������ɹ�
*/
int dao::FileManager::WriteData(char* data, int data_length)
{
	if (!ofs_.is_open()) {
		/*return -1;*/
		if (OpenOfs() != 0)
			return -1;
	}

	MetaData& metadata = ConverCharS2Meta(data, data_length);
	ofs_.write(metadata, BUFFER_LENGTH);
	UpdateSize_();
	CloseOfs();
	return 0;
}

int dao::FileManager::WriteData(MetaData& data)
{
	if (!ofs_.is_open()) {
		/*return -1;*/
		if (OpenOfs() != 0)
			return -1;
	}

	ofs_.write(data, BUFFER_LENGTH);
	UpdateSize_();
	CloseOfs();
	return 0;
}
/*
* ��index����ֻ��ʾ�ļ��ĵڼ���Ԫ���ݣ�û�������κ����壬�����������ļ��ṹ
*/
MetaData& dao::FileManager::GetData(int index)
{
	if (!ifs_.is_open())
		OpenIfs();

	if (!ifs_.is_open() || index >= file_length_ || index < 0) {
		MetaData metadata = { 0 };
		return metadata;
	}
	ifs_.clear();
	ifs_.seekg(index * BUFFER_LENGTH, ios::beg);	//�ƶ����±�λ��
	MetaData metadata;
	ifs_.getline(metadata, BUFFER_LENGTH);	//��ȡһ��Ԫ����

	CloseIfs();
	return metadata;
}

void dao::FileManager::UpdateSize_(int size)
{
	file_length_ += size;
	bit_num_ += size * BUFFER_LENGTH;
}

void dao::FileManager::ResetSize_()
{
	file_length_ = 0;
	bit_num_ = 0;
}

dao::HeapFileManager::HeapFileManager(char* file_name, int name_length) : FileManager(file_name, name_length)
{
	//���ɴ洢��λ�õ��ļ�����
	void_pos_file_name_length_ = name_length + sizeof("_void_pos");
	void_pos_file_name_ = new char[void_pos_file_name_length_];
	memset(void_pos_file_name_, 0, void_pos_file_name_length_);
	strcat_s(void_pos_file_name_, name_length_, file_name_);
	strcat_s(void_pos_file_name_, void_pos_file_name_length_, "_void_pos");

	//��ȡ��ȱλ��
	ReadVoidPos_();
}

dao::HeapFileManager::HeapFileManager(const char* file_name, int name_length) : FileManager(file_name, name_length)
{
	//���ɴ洢��λ�õ��ļ�����
	void_pos_file_name_length_ = name_length + sizeof("_void_pos");
	void_pos_file_name_ = new char[void_pos_file_name_length_];
	memset(void_pos_file_name_, 0, void_pos_file_name_length_);
	strcat_s(void_pos_file_name_, name_length_, file_name_);
	strcat_s(void_pos_file_name_, void_pos_file_name_length_, "_void_pos");

	//��ȡ��ȱλ��
	ReadVoidPos_();
}

dao::HeapFileManager::~HeapFileManager()
{
	UpdataVoidPos_();
	delete[] void_pos_file_name_;
}

int dao::HeapFileManager::OpenOfs()
{
	ofs_.open(file_name_, ios::out | ios::in | ios::binary);
	if (ofs_.is_open()) {
		return 0;
	}
	return -1;
}

int dao::HeapFileManager::WriteData(char* data, int data_length)
{
	if (!ofs_.is_open()) {
		/*return -1;*/
		if (OpenOfs() != 0)
			return -1;
	}

	MetaData& metadata = ConverCharS2Meta(data, data_length);
	if (void_pos_.empty()) {
		ofs_.clear();
		ofs_.seekp((file_length_) * BUFFER_LENGTH, ios::end);
		ofs_.write(metadata, BUFFER_LENGTH);
		UpdateSize_();
		CloseOfs();
		return file_length_;
	}
	else {
		int index = *void_pos_.begin();
		ofs_.clear();
		ofs_.seekp(index * BUFFER_LENGTH, ios::beg);
		ofs_.write(metadata, BUFFER_LENGTH);

		//����λ�ø���
		//void_pos_.pop_front();
		void_pos_.erase(void_pos_.begin());
		CloseOfs();
		return index;
	}
	
}

int dao::HeapFileManager::WriteData(MetaData& metadata) {
	if (!ofs_.is_open()) {
		/*return -1;*/
		if (OpenOfs() != 0)
			return -1;
	}

	
	if (void_pos_.empty()) {
		ofs_.clear();
		ofs_.seekp((file_length_) * BUFFER_LENGTH, ios::beg);
		ofs_.write(metadata, BUFFER_LENGTH);
		UpdateSize_();
		CloseOfs();
		return file_length_;
	}
	else {
		//int index = void_pos_.front();
		int index = *void_pos_.begin();
		ofs_.clear();
		ofs_.seekp(index * BUFFER_LENGTH, ios::beg);
		ofs_.write(metadata, BUFFER_LENGTH);

		//����λ�ø���
		//void_pos_.pop_front();
		void_pos_.erase(void_pos_.begin());
		CloseOfs();
		return index;
	}
}

int dao::HeapFileManager::DeleteData(int index)
{
	if (!ofs_.is_open()) {
		/*return -1;*/
		if (OpenOfs() != 0)
			return -1;
	}
	if (!ofs_.is_open() || index >= file_length_ || index < 0) {
		return -1;
	}

	MetaData void_data = { 0 };
	void_data[BUFFER_LENGTH - 1] = '\n';

	ofs_.clear();
	ofs_.seekp(index * BUFFER_LENGTH, ios::beg);
	ofs_.write(void_data, BUFFER_LENGTH);
	//void_pos_.push_back(index);
	void_pos_.insert(index);
	CloseOfs();
	return index;
}

void dao::HeapFileManager::ReadVoidPos_()
{
	/*	�ѷ�����ԭ�������ļ���һ�д�ſ�������
	if (OpenIfs() != 0) {
		return;
	}
	ifs_.clear();
	ifs_.seekg(0L, ios::beg);
	MetaData head_data = { 0 };
	ifs_.read(head_data, BUFFER_LENGTH);

	char* ptr = NULL;
	char delimiter[] = "\0";
	char* token = strtok_s(head_data, delimiter, &ptr);
	while (token != NULL) {
		void_pos_.push_back(atoi(token));
		token = strtok_s(NULL, delimiter, &ptr);
	}
	*/

	//��ǰʹ�ã�����ļ��������
	ifstream pos_ifs(void_pos_file_name_, ios::in | ios::binary);
	if (!pos_ifs.is_open()) {
		return;
	}
	int pos;
	while (pos_ifs >> pos) {
		//void_pos_.push_back(pos);
		void_pos_.insert(pos);
	}
	pos_ifs.close();
}

void dao::HeapFileManager::UpdataVoidPos_()
{
	ofstream pos_ofs(void_pos_file_name_, ios::out | ios::binary);
	if (!pos_ofs.is_open()) {
		return;
	}
	for (auto it : void_pos_) {
		pos_ofs << it << "\n";
	}
	pos_ofs.close();
}