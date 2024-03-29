#ifndef PCH_H
#define PCH_H
#include<string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <stack>
#include <algorithm>
#include<stdlib.h>  
#include<string.h>
using namespace std;
#define wordNumMax 500
#define FINITY 9999

//变量
extern int EnalbleLoop; //是否允许单词环 （0不允许，1允许）
extern int process;    //处理单词的方式 （0为单词数量，1为单词字母数）
extern int ProStart; //是否指定首字母（0不指定，1指定）
extern char StartWord; //首字母
extern int ProEnd;   //是否指定尾字母（0不指定，1指定）
extern char EndWord;  //尾字母
extern string fileName;  //文件路径

//函数
void FirstState(char *argv[]);
void SecondState(char *argv[]);
void ThirdState(char *argv[]);
void ErrorPrint(char *argv[]);
void StartProcess();

//接口类
class Core {
public:
	virtual void ProcessW(int start, int end) = 0;
	virtual void ProcessC(int start, int end) = 0;
};
//处理单词的基类
class ProcessNoRing :public Core{
public:
	ProcessNoRing(string fileName);
private:
	int wordNum = 0;    //记录单词数量
	int maxLen = 0;    //最长路径长度
	string wordArr[wordNumMax];    //存储所有的单词的数组
	int arc[wordNumMax][wordNumMax];    //存储邻接矩阵中边的权值
	int arcTemp[wordNumMax][wordNumMax];    //供操作的邻接矩阵
	int indegree[wordNumMax];    //入度矩阵
	int orderArr[wordNumMax];    //经过拓扑排序后的顶点序列
	int maxPath[wordNumMax];    //存储到顶点i的最长路径
	int point[wordNumMax];    //存储最长路线的选择点
	int path[wordNumMax][wordNumMax];    //存储最长路径的矩阵
	string fileName;
public:
	void init();

	void getWord(string fileName);

	void createMatrix();

	bool topologicalSort();

	void getMaxPathLen(int arg, char first, char last);

	void getMaxPath();

	void getMaxPathWithTail(int arg, char last);

	bool HasRing();
	void ProcessW(int start,int end);
	void ProcessC(int start, int end);
};

class ProcessWithRing  :public Core{

public :ProcessWithRing(string fileName)  
	 {
		this->fileName = fileName;
	}
private:
	string fileName;
	int wordNum = 0;                     //记录单词数量                     //最长路径长度
	string wordArr[100];          //存储所有的单词的数组
	int arcTemp[100][100]; //供操作的邻接矩阵
	int startPoint, endPoint;
	int visited[100] = { 0 };
	int PathCount = 0;
	int PathPublic[100];  //记录路径
	typedef struct
	{
		int path[200];
		int count;
		int letters;
	} Queue;
	Queue MyQueue[500];
	int MyQueueCount[100];   //记录节点数目
	int MyLetterCount[100];
private:
	void getWord(string fileName); //从文本中得到所有的单词
		//创建邻接矩阵
	void createMatrix();
	//返回第n个节点相连接序号最小的节点
	int first(int n);
	//返回第n个节点相连的比now节点序号大的节点,
	int next(int n, int now);
	void DFS(int nowPoint, int count);
public:
	void ProcessW(int start, int end);
	void ProcessC(int start, int end);
};


#endif 

