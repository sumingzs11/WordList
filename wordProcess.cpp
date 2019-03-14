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

void ProcessNoRing::getWord(string fileName)    //���ı��еõ����еĵ��� 
{
	fstream wordTxt;
	char singleChar;
	bool flag = false;    //���ڱ�ʶ������ַ��Ƿ�Ϊ��ĸ
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

void ProcessNoRing::createMatrix()    //�����ڽӾ���
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

bool ProcessNoRing::topologicalSort()    //��������
{
	stack<int> s;    //��Ŷ����ջ
	int temp;    //��ǰ��ջԪ��
	int count = 0;    //��¼��������󶥵������������������������еĶ�������
	for (int i = 0; i < wordNum; i++)
	{
		if (indegree[i] == 0)
		{
			s.push(i);
			indegree[i] = -1;    //���Ѿ���ջ�ĵ���б��
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
					indegree[temp] = -1;    //���Ѿ���ջ�ĵ���б��
				}
			}

		}
	}
	if (count < wordNum)
	{
		return false;    //����false�����ͼ�л�
	}
	return true;
}

bool ProcessNoRing::HasRing() {
	init();
	getWord(fileName);
	createMatrix();
	if (topologicalSort())
	{
		return true;
	}
	return false;
}

void ProcessNoRing::getMaxPathLen(int arg, char first, char last) //��ȡ�·��  arg=0:������Ŀ���  arg=1:���ʳ����; first:ָ��������ĸ��û������0  last��ָ����β��ĸ��û������0
{
	int v1, v2;
	int length = 1;
	bool firstFlag, lastFlag;    //true:�ҵ��˷��ϵĿ�ʼ/��β  false:û���ҵ����ϵĿ�ʼ/��β
	bool headFlag;    //����Ƿ�ָ����ʼ��ĸ  true:�ҵ�  false:û�ҵ�

	if (first == 0)
	{
		firstFlag = true;
		headFlag = false;
	}
	else if (first >= 'a'&&first <= 'z')
	{
		firstFlag = false;
		headFlag = true;
	}
	else if (first >= 'A'&&first <= 'Z')
	{
		firstFlag = false;
		headFlag = true;
		first = first - 'A' + 'a';
	}
	else
	{
		cout << "illegimate input as first char: " << first << endl;
		return;
	}

	if (last == 0)
	{
		lastFlag = true;
	}
	else if (last >= 'a'&&last <= 'z')
	{
		lastFlag = false;
	}
	else if (last >= 'A'&&last <= 'Z')
	{
		lastFlag = false;
		last = last - 'A' + 'a';
	}
	else
	{
		cout << "illegimate input as last char: " << last << endl;
		return;
	}

	for (int i = 0; i < wordNum; i++)
	{
		v2 = orderArr[i];
		if (!firstFlag)
		{
			if (wordArr[v2][0] == first)
			{
				firstFlag = true;
				if (arg == 0)
				{
					maxPath[v2] = 1;
				}
				else
				{
					maxPath[v2] = wordArr[v2].length();
				}
				continue;
			}
			else
			{
				continue;
			}
		}
		if (maxPath[v2] == 0)
		{
			if (arg == 0)
			{
				maxPath[v2] = 1;
			}
			else
			{
				maxPath[v2] = wordArr[v2].length();
			}
		}
		for (int j = 0; j < i; j++)
		{
			v1 = orderArr[j];
			if (arc[v1][v2] != FINITY)    //��ʾv1�ɴ�v2�������ж�
			{
				if (arg == 1)
				{
					length = arc[v1][v2];
				}
				if (headFlag&&maxPath[v1] == 0)
				{
					continue;
				}
				path[v1][v2] = maxLen;
				if (maxPath[v1] + length > maxPath[v2])
				{
					maxPath[v2] = maxPath[v1] + length;
				}
				if (maxPath[v2] > maxLen)
				{
					maxLen = maxPath[v2];
					path[v1][v2] = maxLen;
				}
				//cout << "v1: " << v1 << " v2: " << v2 << " maxLen: " << maxLen << endl;
				//cout << wordArr[v1] << "   " << wordArr[v2] << endl;
			}
		}
	}
	if (lastFlag)
	{
		cout << "maxLen: " << maxLen << endl;
	}
}

void ProcessNoRing::getMaxPath()    //��ȡ�·��
{
	stack<int> s;    //��¼·�ߵ�ջ
	int max;    //��¼��ǰ�·������
	int stackSize;    //ջ�ĳ���
	//bool flag = false;    //��ʶ�ǲ��ǵ�һ����������ĵ���
	int iStart = 0, jStart = 0;    //��¼��ʼ�ĵ�������һ��
	for (int i = 0; i < wordNum; i++)
	{
		for (int j = 0; j < wordNum; j++)
		{
			if (path[i][j] > path[iStart][jStart])
			{
				iStart = i;
				jStart = j;
			}
		}
	}
	for (int j = jStart; j >=0;)
	{
		for (int i = 0; i < wordNum; i++)
		{
			point[i] = path[i][j];
		}
		sort(point, point + wordNum);
		max = point[wordNum - 1]; //���������ֵ
		if (max == 0)
		{
			s.push(j);
			break;
		}
		for (int i = 0; i < wordNum; i++)
		{
			if (path[i][j] == max)
			{
				s.push(j);
				j = i;
			}
		}
	}


	ofstream result("solution.txt");
	stackSize = s.size();
	for (int i = 0; i < stackSize; i++)
	{
		result << wordArr[s.top()]<<endl;
		s.pop();
	}
	result.close();
}

void ProcessNoRing::getMaxPathWithTail(int arg, char last)    //��ȡ��β�����·��  arg=0:������Ŀ���  arg=1:���ʳ����;
{
	stack<int> s;    //��¼·�ߵ�ջ
	int max;    //��¼��ǰ�·������
	int stackSize;    //ջ�ĳ���
	//bool flag = false;    //��ʶ�ǲ��ǵ�һ����������ĵ���
	int iStart = 0, jStart = 0;    //��¼��ʼ�ĵ�������һ��
	string tempStr;    //��¼���ܻ��õ��ĵ���
	for (int i = 0; i < wordNum; i++)
	{
		for (int j = 0; j < wordNum; j++)
		{
			if (path[i][j] > path[iStart][jStart])
			{
				iStart = i;
				jStart = j;
			}
		}
	}
	for (int j = jStart; j >= 0;)
	{
		for (int i = 0; i < wordNum; i++)
		{
			point[i] = path[i][j];
		}
		sort(point, point + wordNum);
		max = point[wordNum - 1]; //���������ֵ
		if (max == 0)
		{
			s.push(j);
			break;
		}
		for (int i = 0; i < wordNum; i++)
		{
			if (path[i][j] == max)
			{
				s.push(j);
				j = i;
			}
		}
	}

	if (last >= 'a'&&last <= 'z')
	{
		//last = last;
	}
	else if (last >= 'A'&&last <= 'Z')
	{
		last = last - 'A' + 'a';
	}
	else
	{
		cout << "illegimate input as last char: " << last << endl;
		return;
	}

	maxLen = 0;
	stackSize = s.size();
	ofstream result("solution.txt");
	for (int i = 0; i < stackSize; i++)
	{
		result << wordArr[s.top()]<<endl;
		tempStr = wordArr[s.top()];
		s.pop();
		if (arg == 0)
		{
			maxLen++;
		}
		else
		{
			maxLen += tempStr.length();
		}
		if (tempStr[tempStr.length() - 1] == last)
		{
			if (s.empty())
			{
				
				return;
			}
			else
			{
				if (wordArr[s.top()][wordArr[s.top()].length() - 1] == last)
				{
					
					result << wordArr[s.top()] << endl;
					if (arg == 0)
					{
						maxLen++;
					}
					else
					{
						maxLen += wordArr[s.top()].length();
					}
				}
				return;
			}
		}
	}
	result.close();
}

void ProcessNoRing::ProcessW(int start,int end)
{
	init();
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
	if (start && !end) {
		getMaxPathLen(0, StartWord, 0);
		getMaxPath();
	}
	else if (end && !start) {
		getMaxPathLen(0, 0, EndWord);
		getMaxPathWithTail(0, EndWord);
	}
	else if (end&&start) {
		getMaxPathLen(0, StartWord, EndWord);
		getMaxPath();
	}
	else {
		getMaxPathLen(0, 0, 0);
		getMaxPath();
	}  
}

void ProcessNoRing::ProcessC(int start,int end) {
	init();
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
	if (start && !end) {
		getMaxPathLen(1, StartWord, 0);
		getMaxPath();
	}
	else if (end && !start) {
		getMaxPathLen(1, 0, EndWord);
		getMaxPathWithTail(1, EndWord);
	}
	else if (end&&start) {
		getMaxPathLen(1, StartWord, EndWord);
		getMaxPath();
	}
	else {
		getMaxPathLen(1, 0, 0);
		getMaxPath();
	}
}

ProcessNoRing::ProcessNoRing(string fileName) {
	this->fileName = fileName;
}

//��һ����/////////////////////////////

void ProcessWithRing:: getWord(string fileName) //���ı��еõ����еĵ���
{
	fstream wordTxt;
	char singleChar;
	bool flag = false; //���ڱ�ʶ������ַ��Ƿ�Ϊ��ĸ
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
//�����ڽӾ���
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
	return 9999; //���Ҳ����ڵ�n����һ���ڵ㣬����1000
}


void ProcessWithRing::DFS(int nowPoint, int count)
{
	visited[nowPoint] = 1;
	PathPublic[count++] = nowPoint;
	if (nowPoint == endPoint && (count) >= 1)
	{
		//	printf("���������м��%d����·��Ϊ: ", pathNumber);
		int tmp = 0;
		for (int i = 0; i < count; i++)
		{
			MyQueue[PathCount].path[i] = PathPublic[i];
			tmp = tmp + wordArr[PathPublic[i]].length();
			//		printf("%d-->", MyQueue[PathCount].path[i] + 1);
		}
		//	printf("·������Ϊ: %d\n", count);
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
	visited[nowPoint] = 0; //�㷨�ؼ������ݣ������ʹ�״̬��Ϊδ����״̬
	(count)--;
	if (count < 1)
	{
		//printf("������\n");
	}
	return;
}

void ProcessWithRing::ProcessW(int start,int end) {
	ofstream result("solution.txt");
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
		cout << "û�д��ڵ�·��" << endl;
	}
	result.close();
}

void ProcessWithRing::ProcessC(int start,int end) {
	ofstream result("solution.txt");
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
		cout << "û�д��ڵ�·��" << endl;
	}
	result.close();
}


////////////////////////////////
void StartProcess() {

	if (EnalbleLoop) { //�л�
		ProcessNoRing NoRing = ProcessNoRing(fileName);
		ProcessWithRing HasRing= ProcessWithRing(fileName);
		if (NoRing.HasRing()) {  //��ͼ
			if (process == 0) {  //����-w
				NoRing.ProcessW(ProStart, ProEnd);
			}
			else {
				NoRing.ProcessC(ProStart, ProEnd);
			}
		}
		else {
			if (process == 0) {  //����-w
				HasRing.ProcessW(ProStart, ProEnd);
			}
			else {
				HasRing.ProcessC(ProStart, ProEnd);
			}
		}
		
	}
	else {
		ProcessNoRing NoRing = ProcessNoRing(fileName);
		if (process == 0) {  //����-w
			NoRing.ProcessW(ProStart, ProEnd);
		}
		else {
			NoRing.ProcessC(ProStart, ProEnd);
		}
	}
}

