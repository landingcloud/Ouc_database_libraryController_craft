#pragma once
#define BUFFER_LENGTH 500
#define ISBN_LENGTH 13
#define BOOKNAME_LENGTH 100
#define AUTHOR_LENGTH 100
#define PUBLISHER_LENGTH 100
#define PASSWORD_LENGTH 256
enum {
	TYPE_TECH = 1000,
	TYPE_ART
};

typedef char MetaData[BUFFER_LENGTH];
typedef int ISBN[ISBN_LENGTH];
typedef char BookName[BOOKNAME_LENGTH];
typedef char Author[AUTHOR_LENGTH];
typedef char Publisher[PUBLISHER_LENGTH];
