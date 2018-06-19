#include <iostream>
#include <cstring>
#include "Member.h"

using namespace std;

int MemberNoCmp(const Member * x, const Member * y)
{
	return x->no < y->no ? -1 : x->no > y->no ? 1 : 0;
}

int MemberNameCmp(const Member * x, const Member * y)
{
	return strcmp(x->name, y->name);
}

void PrintMember(const Member * x)
{
	cout << x->no << " " << x->name;
}

void PrintLnMember(const Member * x)
{
	cout << x->no << " " << x->name << endl;

}

Member ScanMember(const char * message, int sw)
{
	Member tmp;
	cout << message << "하는 데이터를 입력하세요." << endl;
	if (sw & MEMBER_NO) { cout << "번호 : "; cin >> tmp.no; }
	if (sw & MEMBER_NAME) { cout << "이름 : "; cin >> tmp.name; }

	return tmp;
}

