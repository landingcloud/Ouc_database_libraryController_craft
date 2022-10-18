#pragma once
#define BUFFER_LENGTH 800	//MetaData长度
#define ADDRESS_LENGTH 8	//地址长度，现在是一个元数据可以存储100个地址。
//book堆表
#define ISBN_LENGTH 13		//ISBN长度
#define BOOKNAME_LENGTH 100	//书名长度
#define AUTHOR_LENGTH 100	//作者长度
#define PUBLISHER_LENGTH 100//出版社长度

#define ID_LENGTH 6	//id长度，暂时没啥用

#define PASSWORD_LENGTH 256

typedef char MetaData[BUFFER_LENGTH];	//元数据
typedef int ISBN[ISBN_LENGTH];			//ISBN
typedef char BookName[BOOKNAME_LENGTH];
typedef char Author[AUTHOR_LENGTH];
typedef char Publisher[PUBLISHER_LENGTH];
typedef char Address[ADDRESS_LENGTH];	//地址
typedef int ID[ID_LENGTH];				//id，暂时没用

enum {
	TYPE_TECH = 1000,
	TYPE_ART
};


