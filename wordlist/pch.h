#ifndef PCH_H
#define PCH_H
#include<string>
#include <iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;

//变量
extern string G_FilePath;
//函数
void FirstState(char *argv[]);
void SecondState(char *argv[]);
void ThirdState(char *argv[]);
void ErrorPrint(char *argv[]);
#endif //PCH_H
