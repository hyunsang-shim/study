// attribute_parser.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


typedef struct tags {
	string tag;
	vector<vector<string>> attr_val;
	tags *next;
}TAGS;

int main()
{
	int Lines, args;
	vector<string> Tags;
	string tmp;

	//cin >> Lines >> args;
	//	cin.ignore();

	Lines = 1;
	args = 0;
	for (int i = 0; i < Lines*2; i++)
	{		
		getline(cin, tmp,'\n');
		Tags.push_back(tmp);
	}

	cout << "입력받은 태그" << endl;
	for (int i = 0; i < Lines * 2; i++)
	{
		cout << Tags[i] << endl;
	}

	
	TAGS stored;
	for (int i = 0; i < Lines * 2 - 1; i++)
		for (int j = 0; j < Tags[i].size(); j++)
			if (Tags[i][j] == '<')
			{
				stored.tag = Tags[i].substr(j + 1, Tags[i].find(" "));
				Tags[i].erase(0, Tags[i].find(" ")+1);
			}

	cout << "stored.tag : " << stored.tag << endl;
	cout << "Tags[i] : " << Tags[0] << endl;



    return 0;
}

