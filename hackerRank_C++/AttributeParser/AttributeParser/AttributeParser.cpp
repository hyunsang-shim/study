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
	vector<string> attr;
	vector<string> val; 
	tags *next;
}TAGS;

int main()
{
	int Lines, args;
	vector<string> Tags;
	string tmp;

	//cin >> Lines >> args;
	//	cin.ignore();

	Lines = 2;
	args = 0;
	/*for (int i = 0; i < Lines * 2; i++)
	{
		getline(cin, tmp, '\n');
		Tags.push_back(tmp);
	}
*/

	Tags.push_back("<a href=\"test.com\">");
	Tags.push_back("<body title=\"test\" font-size=\"15pt\">");
	Tags.push_back("</a>");
	Tags.push_back("</body>");

	cout << "입력받은 태그" << endl;
	for (int i = 0; i < Lines * 2; i++)
	{
		cout << Tags[i] << endl;
	}

	TAGS *stored = new TAGS[Lines] ;

	int cnt_tag=0;
	int cnt_attr = 0;
	int cnt_val = 0;

	for (int i = 0; i < Lines * 2 - 1; i++)
	{
		if (i > 0)
			stored[i - 1].next = &stored[i];

		cout << "next : " << stored[i].next << endl;		
		for (int j = 0; j < Tags[i].length(); j++)
		{

			cnt_attr = 0;
			cnt_val = 0;
			while (Tags[i].at(j) != '>')
			{
				string tmp;

				if (Tags[i].at(j) == '<' && Tags[i].at(j+1) =='/')
					break;
				//태그 이름을 떼어낸다.

				if (Tags[i].at(j) == '<')
				{
					tmp = Tags[i].substr(j + 1, Tags[i].find(" ", 0) - (j + 1));

					j = Tags[i].find(" ", 0);
					stored.tag.append(tmp);
					cnt_tag++;
				}
				tmp.clear();

				if (Tags[i].at(j) == ' ')
				{
					j++;
					while (Tags[i].at(j) != '=')
					{
						tmp.append(1, Tags[i].at(j));
						j++;
					}
					stored.attr.push_back(tmp);
					cnt_attr++;

				}

				if (Tags[i].at(j) == '"')
				{
					j++;
					while (Tags[i].at(j) != '"')
					{
						tmp.append(1, Tags[i].at(j));
						j++;
					}
					stored[i].val.push_back(tmp);
					cnt_val++;
				}

				j++;
			}


			cout << "stored.tag : " << endl;
			for (int i = 0; i < cnt_tag; i++)
			{
				cout << "태그 " << i << " : " << stored[i].tag << endl;
				for (int k = 0; k < cnt_attr; k++)
					cout << "태그 " << stored[i].tag[k] << " -> " << stored[i].attr[k] << "=" << stored[i].val[k] << endl;
			}

		}
	}

	
	
	


	return 0;
}
