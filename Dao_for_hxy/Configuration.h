#pragma once
#define BUFFER_LENGTH 800	//MetaData����
#define ADDRESS_LENGTH 8	//��ַ���ȣ�������һ��Ԫ���ݿ��Դ洢100����ַ��
//book�ѱ�
#define ISBN_LENGTH 13		//ISBN����
#define BOOKNAME_LENGTH 100	//��������
#define AUTHOR_LENGTH 100	//���߳���
#define PUBLISHER_LENGTH 100//�����糤��

#define ID_LENGTH 6	//id���ȣ���ʱûɶ��

#define PASSWORD_LENGTH 256

typedef char MetaData[BUFFER_LENGTH];	//Ԫ����
typedef int ISBN[ISBN_LENGTH];			//ISBN
typedef char BookName[BOOKNAME_LENGTH];
typedef char Author[AUTHOR_LENGTH];
typedef char Publisher[PUBLISHER_LENGTH];
typedef char Address[ADDRESS_LENGTH];	//��ַ
typedef int ID[ID_LENGTH];				//id����ʱû��

enum {
	TYPE_TECH = 1000,
	TYPE_ART
};


