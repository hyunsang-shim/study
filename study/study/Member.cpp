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
	cout << message << "�ϴ� �����͸� �Է��ϼ���." << endl;
	if (sw & MEMBER_NO) { cout << "��ȣ : "; cin >> tmp.no; }
	if (sw & MEMBER_NAME) { cout << "�̸� : "; cin >> tmp.name; }

	return tmp;
}

