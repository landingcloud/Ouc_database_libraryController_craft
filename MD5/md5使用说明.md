## 目前而言md5可以运行但稍有些麻烦，正在尝试合并成统一的一个md5（）函数中

//要加密字符串，更改encrypt[] 即可

unsigned char encrypt[] = "admin";  
//加密所需变量和步骤
unsigned char decrypt[16];//存储md5加密后内容
MD5_CTX md5;

//计算md5，存在decrypt

MD5Init(&md5);
MD5Update(&md5, encrypt, (int)strlen((char*)encrypt));//只是个中间步骤
MD5Final(&md5, decrypt);//32位



## 上述代码复制进主函数，调用计算即可，decrypt[16]的3到11为16位md5，本体为32位md5