#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<cmath>
typedef struct {
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];
}MD5_CTX;



#define F(x,y,z) ((x&y)|(~x&z))
#define G(x,y,z) ((x&z)|(y&~z))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y^(x|~z))
#define ROTATE_LEFT(x,n) ((x<<n)|(x>>(32-n)))
#define FF(a,b,c,d,x,s,ac) { a+=F(b,c,d)+x+ac; a=ROTATE_LEFT(a,s); a+=b;}
#define GG(a,b,c,d,x,s,ac) { a+=G(b,c,d)+x+ac; a=ROTATE_LEFT(a,s); a+=b;}
#define HH(a,b,c,d,x,s,ac) { a+=H(b,c,d)+x+ac; a=ROTATE_LEFT(a,s); a+=b;}
#define II(a,b,c,d,x,s,ac) { a+=I(b,c,d)+x+ac; a=ROTATE_LEFT(a,s); a+=b;}

void MD5Init(MD5_CTX* context);
void MD5Update(MD5_CTX* context, unsigned char* input, unsigned int inputlen);
void MD5Final(MD5_CTX* context, unsigned char digest[16]);
void MD5Transform(unsigned int state[4], unsigned char block[64]);
void MD5Encode(unsigned char* output, unsigned int* input, unsigned int len);
void MD5Decode(unsigned int* output, unsigned char* input, unsigned int len);



/**
* 
//要加密字符串，更改即可
unsigned char encrypt[] = "admin";//"admin";//21232f297a57a5a743894a0e4a801fc3  
//加密所需变量和步骤
unsigned char decrypt[16];//存储md5加密后内容
MD5_CTX md5;
MD5Init(&md5);
MD5Update(&md5, encrypt, (int)strlen((char*)encrypt));//只是个中间步骤
MD5Final(&md5, decrypt);//32位

//输出（可以不用）
printf("加密前:%s\n加密后16位:", encrypt);
for (i = 4; i < 12; i++) {
    printf("%02x", decrypt[i]);
}
printf("\n加密前:%s\n加密后32位:", encrypt);
for (i = 0; i < 16; i++) {
    printf("%02x", decrypt[i]);
}
*/