#include "pch.h"
 void ProcessNoRing::init()
{
	for (int i = 0; i < wordNumMax; i++)
	{
		indegree[i] = 0;
		maxPath[i] = 0;
		point[i] = 0;
		for (int j = 0; j < wordNumMax; j++) {
			path[i][j] = 0;
		}
	}
}

void ProcessNoRing::getWord(string fileName)    //从文本中得到所有的单词 
{
	fstream wordTxt;
	char singleChar;
	bool flag = false;    //用于标识读入的字符是否为字母
	bool ifNewWord = false;
	wordTxt.open(fileName, ios::in);
	wordTxt >> noskipws;
	while (!wordTxt.eof())
	{
		wordTxt >> singleChar;
		//cout << singleChar << endl;
		if (wordTxt.fail())
		{
			break;
		}
		if (wordNum >= wordNumMax)
		{
			cout << "too many words!!!" << endl;
			break;
		}
		if (singleChar >= 'A'&&singleChar <= 'Z')
		{
			singleChar = singleChar - 'A' + 'a';
		}
		if (singleChar >= 'a'&&singleChar <= 'z')
		{
			if (!flag)
			{
				flag = true;
			}
			wordArr[wordNum] += singleChar;
		}
		else
		{
			if (flag)
			{
				flag = false;
				ifNewWord = true;
				for (int i = 0; i < wordNum; i++)
				{
					if (wordArr[wordNum] == wordArr[i])
					{
						ifNewWord = false;
						wordArr[wordNum].clear();
						break;
					}
				}
				if (ifNewWord)
				{
					wordNum++;
				}
			}
		}
	}
}

void ProcessNoRing::createMatrix()    //创建邻接矩阵
{
	for (int i = 0; i < wordNum; i++)
	{
		for (int j = 0; j < wordNum; j++)
		{
			if (j == i)
			{
				arc[i][j] = FINITY;
				arcTemp[i][j] = FINITY;
				continue;
			}
			if (wordArr[i][wordArr[i].length() - 1] == wordArr[j][0])
			{
				arc[i][j] = wordArr[j].length();
				arcTemp[i][j] = wordArr[j].length();
				indegree[j]++;
			}
			else
			{
				arc[i][j] = FINITY;
				arcTemp[i][j] = FINITY;
			}
		}
	}
}

bool ProcessNoRing::topologicalSort()    //拓扑排序
{
	stack<int> s;    //存放顶点的栈
	int temp;    //当前出栈元素
	int count = 0;    //记录经过排序后顶点的数量，即经拓扑排序后序列的顶点数量
	for (int i = 0; i < wordNum; i++)
	{
		if (indegree[i] == 0)
		{
			s.push(i);
			indegree[i] = -1;    //对已经入栈的点进行标记
		}
	}
	while (!s.empty())
	{
		temp = s.top();
		s.pop();
		orderArr[count] = temp;
		count++;
		for (int i = 0; i < wordNum; i++)
		{
			if (arcTemp[temp][i] != FINITY)
			{
				arcTemp[temp][i] = FINITY;
				indegree[i]--;
				if (indegree[i] == 0)
				{
					s.push(i);
					indegree[temp] = -1;    //对已经出栈的点进行标记
				}
			}

		}
	}
	if (count < wordNum)
	{
		return false;    //返回false代表该图有环
	}
	return true;
}

void ProcessNoRing::getMaxPathLen()    //获取最长路径
{
	int v1, v2;
	for (int i = 0; i < wordNum; i++)
	{
		v2 = orderArr[i];
		for (int j = 0; j < i; j++)
		{
			v1 = orderArr[j];
			if (arc[v1][v2] != FINITY)    //表示v1可达v2，进行判断
			{
				if (maxPath[v1] + 1 > maxPath[v2])
				{
					maxPath[v2] = maxPath[v1] + 1;
				}
				if (maxPath[v2] > maxLen)
				{
					maxLen = maxPath[v2];
					path[v1][v2] = maxLen;
				}
				//cout << "v1: " << v1 << " v2: " << v2 << " max: " << max << endl;
			}
		}
	}
	cout << "maxLen: " << maxLen << endl;
}

void ProcessNoRing::getMaxPath()    //获取最长路径
{
	stack<int> s;    //记录路线的栈
	int max;    //记录当前最长路径长度
	for (int i = wordNum - 1; i > 0;)
	{
		for (int j = 0; j < wordNum; j++)
		{
			point[j] = path[j][i];
		}
		sort(point, point + wordNum);
		max = point[wordNum - 1];    //排序后的最大值
		if (max != 0)
		{
			for (int j = 0; j < wordNum; j++)
			{
				if (path[j][i] == max)
				{
					s.push(i);
					i = j;
					if (i == 0)
					{
						s.push(i);
					}
					break;
				}
			}
		}
	}
	cout << "max path is: ";
	for (int i = 0; i < s.size(); i++)
	{
		if (i != 0)
		{
			cout << " -> ";
		}
		cout << s.top();
		s.pop();
	}
}

int ProcessNoRing::processW()
{
	init();
	ofstream result("result.txt");
	getWord(fileName);
	createMatrix();
	if (topologicalSort())
	{
		cout << "topologicalSort success!" << endl;
	}
	else
	{
		cout << "topologicalSort failed!" << endl;
	}
	getMaxPathLen();
	getMaxPath();    //这个还有问题，等等回来写吧
	for (int i = 0; i < wordNum; i++)
	{
		result << wordArr[i] << ":  ";
		for (int j = 0; j < wordNum; j++)
		{
			result << arc[i][j] << "  ";
		}
		result << endl;
	}
	result << endl;
	for (int i = 0; i < wordNum; i++)
	{
		result << wordArr[orderArr[i]] << "  ";
	}
	return 0;
}

ProcessNoRing::ProcessNoRing(string fileName) {
	this->fileName = fileName;
}

//另一个类/////////////////////////////

void ProcessWithRing:: getWord(string fileName) //从文本中得到所有的单词
{
	fstream wordTxt;
	char singleChar;
	bool flag = false; //用于标识读入的字符是否为字母
	bool ifNewWord = false;
	wordTxt.open(fileName, ios::in);
	wordTxt >> noskipws;
	while (!wordTxt.eof())
	{
		wordTxt >> singleChar;
		//cout << singleChar << endl;
		if (wordTxt.fail())
		{
			break;
		}
		if (wordNum >= wordNumMax)
		{
			cout << "too many words!!!" << endl;
			break;
		}
		if (singleChar >= 'A' && singleChar <= 'Z')
		{
			singleChar = singleChar - 'A' + 'a';
		}
		if (singleChar >= 'a' && singleChar <= 'z')
		{
			if (!flag)
			{
				flag = true;
			}
			wordArr[wordNum] += singleChar;
		}
		else
		{
			if (flag)
			{
				flag = false;
				ifNewWord = true;
				for (int i = 0; i < wordNum; i++)
				{
					if (wordArr[wordNum] == wordArr[i])
					{
						ifNewWord = false;
						wordArr[wordNum].clear();
						break;
					}
				}
				if (ifNewWord)
				{
					wordNum++;
				}
			}
		}
	}
}
//创建邻接矩阵
void ProcessWithRing::createMatrix()
{
	memset(arcTemp, 0, 80000);
	for (int i = 0; i < wordNum; i++)
	{
		for (int j = 0; j < wordNum; j++)
		{
			if (wordArr[i][wordArr[i].length() - 1] == wordArr[j][0])
			{
				arcTemp[i][j] = wordArr[j].length();
			}
		}
	}
}

int ProcessWithRing::first(int n)
{
	for (int i = 0; i < wordNum; i++)
	{
		if (arcTemp[n][i])
			return i;
	}
	return 9999;
}


int ProcessWithRing::next(int n, int now)
{
	for (int i = now + 1; i < wordNum; i++)
	{
		if (arcTemp[n][i])
			return i;
	}
	return 9999; //当找不到节点n的下一个节点，返回1000
}


void ProcessWithRing::DFS(int nowPoint, int count)
{
	visited[nowPoint] = 1;
	PathPublic[count++] = nowPoint;
	if (nowPoint == endPoint && (count) >= 1)
	{
		//	printf("这两个城市间第%d条简单路径为: ", pathNumber);
		int tmp = 0;
		for (int i = 0; i < count; i++)
		{
			MyQueue[PathCount].path[i] = PathPublic[i];
			tmp = tmp + wordArr[PathPublic[i]].length();
			//		printf("%d-->", MyQueue[PathCount].path[i] + 1);
		}
		//	printf("路径长度为: %d\n", count);
		MyLetterCount[PathCount] = tmp;
		MyQueue[PathCount].letters = tmp;
		MyQueueCount[PathCount] = count;
		MyQueue[PathCount].count = count;
		PathCount++;
	}
	else
	{
		int k;
		for (k = first(nowPoint); k < wordNum; k = next(nowPoint, k))
		{
			if (visited[k] == 0)
				DFS(k, count);
		}
	}
	visited[nowPoint] = 0; //算法关键，回溯，将访问过状态变为未访问状态
	(count)--;
	if (count < 1)
	{
		//printf("不存在\n");
	}
	return;
}

void ProcessWithRing::ProcessW(int start,int end) {
	ofstream result("result.txt");
	getWord(fileName);
	createMatrix();
	for (int i = 0; i < wordNum; i++)
	{
		for (int j = 0; j < wordNum; j++)
		{
			if (i != j)
			{
				startPoint = i;
				endPoint = j;
				DFS(i, 0);
			}
		}
	}
	int x1 = 0;
	int x2 = 0;
	if (start&&!end) {
		for (int i = 0; i < PathCount; i++) {
			if (MyQueueCount[i] > x2&&wordArr[MyQueue[i].path[0]][0] == StartWord) {
				x1 = i;
				x2 = MyQueueCount[i];
			}
		}
		for (int j = 0; j < MyQueue[x1].count; j++)
		{
			int x = MyQueue[x1].path[j];
			result << wordArr[x] << endl;
		}
	}
	else if (end && !start) {
		for (int i = 0; i < PathCount; i++) {
			if (MyQueueCount[i] > x2&&wordArr[MyQueue[i].path[MyQueue[i].count-1]][wordArr[MyQueue[i].path[MyQueue[i].count-1]].length()-1] == EndWord) {
				x1 = i;
				x2 = MyQueueCount[i];
			}
		}
		for (int j = 0; j < MyQueue[x1].count; j++)
		{
			int x = MyQueue[x1].path[j];
			result << wordArr[x] << endl;
		}
	}
	else if (end&&start) {
		for (int i = 0; i < PathCount; i++) {
			bool t1 = MyQueueCount[i] > x2&&wordArr[MyQueue[i].path[MyQueue[i].count - 1]][wordArr[MyQueue[i].path[MyQueue[i].count - 1]].length() - 1] == EndWord;
			bool t2 = wordArr[MyQueue[i].path[0]][0] == StartWord;
			if (t1&&t2) {
				x1 = i;
				x2 = MyQueueCount[i];
			}
		}
		for (int j = 0; j < MyQueue[x1].count; j++)
		{
			int x = MyQueue[x1].path[j];
			result << wordArr[x] << endl;
		}
	}
	else {
		x1 = PathCount - 1;
		x2 = MyQueueCount[PathCount - 1];

		sort(MyQueueCount, MyQueueCount + PathCount);
		for (int i = 0; i < PathCount; i++)
		{
			if (MyQueue[i].count == MyQueueCount[PathCount - 1])
			{
				for (int j = 0; j < MyQueue[i].count; j++)
				{
					int x = MyQueue[i].path[j];
					result << wordArr[x] << endl;
				}
				break;
			}
		}
	}
	if (x2 == 0) {
		cout << "没有存在的路径" << endl;
	}
	
}

void ProcessWithRing::ProcessC(int start,int end) {
	ofstream result("result.txt");
	getWord(fileName);
	createMatrix();
	for (int i = 0; i < wordNum; i++)
	{
		for (int j = 0; j < wordNum; j++)
		{
			if (i != j)
			{
				startPoint = i;
				endPoint = j;
				DFS(i, 0);
			}
		}
	}
	int x1 = 0;
	int x2 = 0;
	if (start && !end) {
		for (int i = 0; i < PathCount; i++) {
			if (MyLetterCount[i] > x2&&wordArr[MyQueue[i].path[0]][0] == StartWord) {
				x1 = i;
				x2 = MyLetterCount[i];
			}
		}
		for (int j = 0; j < MyQueue[x1].count; j++)
		{
			int x = MyQueue[x1].path[j];
			result << wordArr[x] << endl;
		}
	}
	else if (end && !start) {
		for (int i = 0; i < PathCount; i++) {
			if (MyLetterCount[i] > x2&&wordArr[MyQueue[i].path[MyQueue[i].count - 1]][wordArr[MyQueue[i].path[MyQueue[i].count - 1]].length() - 1] == EndWord) {
				x1 = i;
				x2 = MyLetterCount[i];
			}
		}
		for (int j = 0; j < MyQueue[x1].count; j++)
		{
			int x = MyQueue[x1].path[j];
			result << wordArr[x] << endl;
		}
	}
	else if (end&&start) {
		for (int i = 0; i < PathCount; i++) {
			bool t1 = MyLetterCount[i] > x2&&wordArr[MyQueue[i].path[MyQueue[i].count - 1]][wordArr[MyQueue[i].path[MyQueue[i].count - 1]].length() - 1] == EndWord;
			bool t2 = wordArr[MyQueue[i].path[0]][0] == StartWord;
			if (t1&&t2) {
				x1 = i;
				x2 = MyLetterCount[i];
			}
		}
		for (int j = 0; j < MyQueue[x1].count; j++)
		{
			int x = MyQueue[x1].path[j];
			result << wordArr[x] << endl;
		}
	}
	else {
		x1 = PathCount - 1;
		x2 = MyLetterCount[PathCount - 1];
		sort(MyLetterCount, MyLetterCount + PathCount);
		for (int i = 0; i < PathCount; i++)
		{
			if (MyQueue[i].letters == MyLetterCount[PathCount - 1])
			{
				for (int j = 0; j < MyQueue[i].count; j++)
				{
					int x = MyQueue[i].path[j];
					result << wordArr[x] << endl;
				}
				break;
			}
		}
		
	}
	if (x2 == 0) {
		cout << "没有存在的路径" << endl;
	}
}


////////////////////////////////
void StartProcess() {
	if (EnalbleLoop) { //有环
		ProcessWithRing HasRing= ProcessWithRing(fileName);
		if (process == 0) {  //采用-w
			HasRing.ProcessW(ProStart, ProEnd);
		}
		else {
			HasRing.ProcessC(ProStart, ProEnd);
		}
	}
	else {

	}
}

