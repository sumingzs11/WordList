#include "pch.h"
#pragma warning(disable:4996)

int EnalbleLoop; //是否允许单词环 （0不允许，1允许）
int process;    //处理单词的方式 （0为单词数量，1为单词字母数）
int ProStart; //是否指定首字母（0不指定，1指定）
char StartWord; //首字母
int ProEnd;   //是否指定尾字母（0不指定，1指定）
char EndWord;  //尾字母
string fileName;  //文件路径
int ArgvCnt;  //用于给命令行参数计数
//我们规定参数最多的命令行格式是 -r -h a -t b -w（即r是最先开始的，h与t可以交换）

int main(int argc, char *argv[])
{
	ArgvCnt = 1;
	if (argc < 3 || argc>8)
	{
		cout << ("Input Error") << endl;
		return -1;
	}
	if (strcmp(argv[ArgvCnt] , "-r")==0) {
		EnalbleLoop = 1;
		ArgvCnt++;
		FirstState(argv);
	}
	else if (strcmp(argv[ArgvCnt], "-w") == 0 || strcmp(argv[ArgvCnt], "-c") == 0) {
		cout << "66" << endl;
		process = strcmp(argv[ArgvCnt], "-w") == 0 ? 0 : 1;
		ArgvCnt++;
		ThirdState(argv);
	}
	else if (strcmp(argv[ArgvCnt], "-h") == 0 || strcmp(argv[ArgvCnt], "-t") == 0) {
		ProStart = strcmp(argv[ArgvCnt], "-h") == 0;
		ProEnd = strcmp(argv[ArgvCnt], "-t") == 0;
		ArgvCnt++;
		if (strlen(argv[ArgvCnt]) == 1 && isalpha(argv[ArgvCnt][0])) {
			StartWord = argv[ArgvCnt][0];
			EndWord = argv[ArgvCnt][0];
			ArgvCnt++;
			SecondState(argv);
		}
		else {
			ErrorPrint(argv);
		}
	}
	else {
		ErrorPrint(argv);
	}
	return 0;
}


void FirstState(char *argv[]) {
	if (strcmp(argv[ArgvCnt], "-w") == 0 || strcmp(argv[ArgvCnt], "-c") == 0) {
		process = strcmp(argv[ArgvCnt], "-w") == 0 ? 0 : 1;
		ArgvCnt++;
		ThirdState(argv);
	}
	else if (strcmp(argv[ArgvCnt], "-h") == 0 || strcmp(argv[ArgvCnt], "-t") == 0) {
		ProStart = strcmp(argv[ArgvCnt], "-h") == 0;
		ProEnd = strcmp(argv[ArgvCnt], "-t") == 0;
		ArgvCnt++;
		if (strlen(argv[ArgvCnt]) == 1 && isalpha(argv[ArgvCnt][0])) {
			StartWord = argv[ArgvCnt][0];
			EndWord = argv[ArgvCnt][0];
			ArgvCnt++;
			SecondState(argv);
		}
		else {
			ErrorPrint(argv);
		}
	}
	else {
		ErrorPrint(argv);
	}
}
void SecondState(char *argv[]) {
	if (strcmp(argv[ArgvCnt], "-w") == 0 || strcmp(argv[ArgvCnt], "-c") == 0) {
		process = strcmp(argv[ArgvCnt], "-w") == 0 ? 0 : 1;
		ArgvCnt++;
		ThirdState(argv);
	}
	else if (strcmp(argv[ArgvCnt], "-h") == 0 || ProEnd) {
		ProStart = 1;
		ArgvCnt++;
		if (strlen(argv[ArgvCnt]) == 1 && isalpha(argv[ArgvCnt][0])) {
			StartWord = argv[ArgvCnt][0];
			ArgvCnt++;
			SecondState(argv);
		}
	}
	else if (strcmp(argv[ArgvCnt], "-t") == 0 || ProStart) {
		ProEnd = 1;
		ArgvCnt++;
		if (strlen(argv[ArgvCnt]) == 1 && isalpha(argv[ArgvCnt][0])) {
			EndWord = argv[ArgvCnt][0];
			ArgvCnt++;
			SecondState(argv);
		}
	}
	else {
		ErrorPrint(argv);
	}
}
void ThirdState(char *argv[]) {
	FILE *fp;
	fp = fopen(argv[ArgvCnt], "r");
	fileName = argv[ArgvCnt];
	if (fp == NULL) {
		ErrorPrint(argv);
	}
	fclose(fp);
	StartProcess();
}
void ErrorPrint(char *argv[]) {
	cout << ("Input Error") << endl;
	exit(0);
}

