#include "Dao.h"
#include "Tools.h"

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
	// TODO: 在此处插入 return 语句
	return ifs_;
}

fstream& dao::FileManager::GetOfs()
{
	// TODO: 在此处插入 return 语句
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


int dao::FileManager::GetAllData(char** metadatas, int& num)
{
	if (!ifs_.is_open())
		OpenIfs();
	metadatas = new char* [file_length_];
	for (int i = 0; i < file_length_; ++i) {
		MetaData metadata;
		ifs_.getline(metadata, BUFFER_LENGTH);	//获取一个元数据
		
		metadatas[i] = new char[BUFFER_LENGTH];
		strcpy_s(metadatas[i], BUFFER_LENGTH, metadata);
	}
	num = file_length_;
	return 0;
}
/*
* 只能以尾插添加数据，这个函数应该被重载以适用其他插入方式。
* @return -1说明未打开输出流，插入失败
* @return 0说明插入成功
*/
int dao::FileManager::WriteData(char* data, int data_length)
{
	if (!ofs_.is_open()) {
		/*return -1;*/
		if (OpenOfs() != 0)
			return -1;
	}

	MetaData metadata = { 0 };
	if (ConverCharS2Meta(metadata, data, data_length) != 0)
		return -1;
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
* 此index仅仅只表示文件的第几个元数据，没有其他任何意义，具体意义结合文件结构
*/
int dao::FileManager::GetData(MetaData& metadata, int index)
{
	if (!ifs_.is_open())
		OpenIfs();

	if (!ifs_.is_open() || index >= file_length_ || index < 0) {
		memset(metadata, 0, BUFFER_LENGTH);
		return -1;
	}
	ifs_.clear();
	ifs_.seekg(index * BUFFER_LENGTH, ios::beg);	//移动到下标位置
	ifs_.getline(metadata, BUFFER_LENGTH);	//获取一个元数据

	CloseIfs();
	return 0;
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
	//生成存储空位置的文件名称
	void_pos_file_name_length_ = name_length + sizeof("_void_pos");
	void_pos_file_name_ = new char[void_pos_file_name_length_];
	memset(void_pos_file_name_, 0, void_pos_file_name_length_);
	strcat_s(void_pos_file_name_, name_length_, file_name_);
	strcat_s(void_pos_file_name_, void_pos_file_name_length_, "_void_pos");

	//读取空缺位置
	ReadVoidPos_();
}

dao::HeapFileManager::HeapFileManager(const char* file_name, int name_length) : FileManager(file_name, name_length)
{
	//生成存储空位置的文件名称
	void_pos_file_name_length_ = name_length + sizeof("_void_pos");
	void_pos_file_name_ = new char[void_pos_file_name_length_];
	memset(void_pos_file_name_, 0, void_pos_file_name_length_);
	strcat_s(void_pos_file_name_, name_length_, file_name_);
	strcat_s(void_pos_file_name_, void_pos_file_name_length_, "_void_pos");

	//读取空缺位置
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
	//没有打开成功，说明文件没有创建，创建后重试一下
	ofstream createFile(file_name_, ios::out | ios::binary);
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

	MetaData metadata = { 0 };
	if (ConverCharS2Meta(metadata, data, data_length) != 0)
		return -1;
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

		//空闲位置更新
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

		//空闲位置更新
		//void_pos_.pop_front();
		void_pos_.erase(void_pos_.begin());
		CloseOfs();
		return index;
	}
}

int dao::HeapFileManager::UpdataData(int index, char* data, int data_length)
{
	MetaData metadata = { 0 };
	if (ConverCharS2Meta(metadata, data, data_length) != 0)
		return -1;
	return UpdataData(index, metadata);
}

int dao::HeapFileManager::UpdataData(int index, MetaData& metadata)
{
	if (!ofs_.is_open()) {
		/*return -1;*/
		if (OpenOfs() != 0)
			return -1;
	}
	if (!ofs_.is_open() || index >= file_length_ || index < 0) {
		return -1;
	}
	ofs_.clear();
	ofs_.seekp(index * BUFFER_LENGTH, ios::beg);
	ofs_.write(metadata, BUFFER_LENGTH);
	CloseOfs();
	return 0;
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
	/*	已废弃，原本设想文件第一行存放空闲数据
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

	//当前使用，别的文件存放数据
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

int dao::HashMapManager::WriteData(int key, MetaData metadata)
{
	if (!ofs_.is_open()) {
		/*return -1;*/
		if (OpenOfs() != 0)
			return -1;
	}

	ofs_.clear();
	ofs_.seekp(key * BUFFER_LENGTH, ios::beg);
	ofs_.write(metadata, BUFFER_LENGTH);
	if (key >= this->file_length_)
		UpdateSize_(key - this->file_length_ + 1);	//补全的位置+当前位置
	CloseOfs();
	return 0;
}

int dao::HashMapManager::AddAddress2Meta(MetaData& metadata, Address address)
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

int dao::HashMapManager::SplitMeta2Address(MetaData metadata, int& num, Address* addresses)
{
	num = 0;
	char** temp = new char* [BUFFER_LENGTH / ADDRESS_LENGTH];	//最大num数
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

int dao::HashMapManager::GetContents(int key, int& num, Address* addresses)
{
	MetaData metadata = { 0 };
	if (GetData(metadata, key) == 0) {
		SplitMeta2Address(metadata, num, addresses);
		return 0;
	}
	else {
		return -1;
	}
	
}

int dao::HashMapManager::WriteContents(int key, Address address)
{
	//得到原本字符串
	MetaData metadata = { 0 };
	GetData(metadata, key);
	AddAddress2Meta(metadata, address);
	WriteData(key, metadata);
	return 0;
}

int dao::HashMapManager::DeleteContents(int key, Address address)
{
	//直接覆盖
	if (address[0] == '\0') {
		Address voidAddress = { 0 };
		WriteData(key, voidAddress);
		return 0;
	}
	
	int num = 0;
	Address* addresses = new Address[BUFFER_LENGTH / ADDRESS_LENGTH];
	GetContents(key, num, addresses);
	for (int i = 0; i < num; ++i) {
		//找到相等的，删掉
		if (IsAddressSame(addresses[i], address)) {
			MetaData metadata = { 0 };
			GetData(metadata, key);
			//找到对应位置，覆盖掉
			for (int j = 0; j < ADDRESS_LENGTH; ++j) {
				metadata[j + i * ADDRESS_LENGTH] = '\0';
			}
			//重新覆盖
			WriteData(key, metadata);
			//其实这里可以直接退出了，不过想循环完，去掉所有相同的（理论正常情况下不存在相同的）
			//return 0;
		}
	}
	//没找到，可以直接退出了
	return 0;
}

int dao::HashMapManager::OpenOfs()
{
	ofs_.open(file_name_, ios::out | ios::in | ios::binary);
	if (ofs_.is_open()) {
		return 0;
	}
	//没有打开成功，说明文件没有创建，创建后重试一下
	ofstream createFile(file_name_, ios::out | ios::binary);
	ofs_.open(file_name_, ios::out | ios::in | ios::binary);
	if (ofs_.is_open()) {
		return 0;
	}
	return -1;
}


