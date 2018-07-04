// study_2.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;


double q17_6_rec(int i, double result)
{
	result += i / (i + 1.0);

	if (i > 1)
		return q17_6_rec(i - 1, result);
	else
		return result;
}

void p720_q17_6()
{
	int i;
	double result = 0;

	cout << "급수의 합" << endl;
	cout << "급수를 몇 까지 계산 할까요? ";
	cin >> i;
	
	cout << "급수의 합 m(" << i << ") = " << q17_6_rec(i, result) << endl;
}

void displayPermuation(const string& s1, const string& s2)
{
	//s2 = 원본
	//s1 바꾼 문자열	
	int n = s2.length();

	if (n == 0)
		cout << s1 << endl;
	else
		for (int i = 0; i < n; i++)
		{			
			//빈 것에 원본의 i번째 문자를 넣고, 원본을 
			//cout << "s1 + s2.at(i): " << s1 + s2.at(i) << ", s2.substr(0, i) : " << s2.substr(0, i) << ",   s2.substr(i + 1, n-1) : " << s2.substr(i + 1, n - 1) << endl;	//확인용
			displayPermuation(s1 + s2.at(i), s2.substr(0, i) + s2.substr(i + 1, n-1));
		}
}

void displayPermuation(const string& s)
{
	displayPermuation("", s);
}

void p722_q17_17()
{
	string input;
	cout << "문자열 순열" << endl;
	cout << "문자열을 입력하세요 : ";
	cin >> input;

	displayPermuation(input);
}


string DecimalToBinary(int value, string result)
{
	int tmp = value;
	char a[8];
	
	if (tmp/2 >= 1)
	{
		_itoa_s(tmp % 2, a, 10);
		result.append(a, 1);
		return DecimalToBinary(tmp/2, result);
	}
	else
	{		
		result.append("1", 1);
		//결과가 거꾸로 들어가 있으니까 뒤집어 준다.
		for (int i = 0; i < result.length()/2; i++)
		{
			char x;
			x = result.at(i);
			result.at(i) = result.at(result.length() - (i + 1));
			result.at(result.length() - (i + 1)) = x;
		}
		return result;
	}	
}


char numToHEX[17]= {"0123456789ABCDEF"};

string DecimalToHex(int value, string result)
{
	int tmp = value;
	char a;

	if (tmp / 16 >= 1)
	{
		a = numToHEX[tmp % 16];
		result.append(a, 1);
		return DecimalToHex(tmp / 16, result);
	}
	else
	{
		a = numToHEX[tmp % 16];
		result.append(a, 1);
		//결과가 거꾸로 들어가 있으니까 뒤집어 준다.
		for (int i = 0; i < result.length() / 2; i++)
		{
			char x;
			x = result.at(i);
			result.at(i) = result.at(result.length() - (i + 1));
			result.at(result.length() - (i + 1)) = x;
		}
		return result;
	}
}
void p726_q17_21()
{
	cout << "10진수 -> 2진수 변환" << endl;
	cout << "10진수 정수를 입력하세요. : "; 
	int input;
	cin >> input;

	string result;
	cout << input << "(10진수) -> " << DecimalToBinary(input, result) << "(2진수)" << endl;

}

void p726_q17_22()
{
	cout << "10진수를 16진수로 변환" << endl;

	cout << "10진수 정수를 입력하세요. : ";
	int input;
	cin >> input;

	string result;
	cout << input << "(10진수) -> " << DecimalToHex(input, result) << "(16진수)" << endl;

}


int main()
{
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	//2018.07.04
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	//p720_q17_6();
	//p722_q17_17();
	//p726_q17_21();
	p726_q17_22();	//진행중
	//p726_q17_23();	//미진행
	//p726_q17_24();	//미진행



    return 0;
}

