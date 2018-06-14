// Q3_22.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include "Circle.h"
#include "Loan.h"
#include "Rectangle.h"
#include "MyPoint.h"
#include "StopWatch.h"




using namespace std;

const double PI = 3.14159265359;


double Get_Length(double x1, double y1, double x2, double y2)
{
	//직선의 거리
	/*
	점 A(x1, y1)와 점 B(x2, y2)사이의 거리 = 	root( ( x2 - x1 ) ^2 + ( y2 - y1 ) ^2 )
	*/
	double a = x2 - x1;
	double b = y2 - y1;

	return pow((pow(a, 2.0) + pow(b, 2.0)), 0.5);
}

void SWAP_A_B(void *a, void *b, int n)
{
	void *tmp;
	tmp = malloc(n);
	memcpy(tmp, a, n);
	memcpy(a, b, n);
	memcpy(b, tmp, n);
	free(tmp);
}

void Q3_19()
{
	//직선의 거리
	/*
	root((x2 - x1)^2 + (y2 - y1)^2)
	*/


	cout << "원의 반지름을 입력하세요. : ";
	double radius;
	cin >> radius;

	cout << "구하고자 하는 점 X의 좌표쌍을 입력하세요 (x,y) : ";
	double x, y;
	cin >> x >> y;

	if (pow((pow(x, 2) + pow(y, 2)), 0.5) > radius)
		cout << "점 X(" << x << ", " << y << ") 는 원의 바깥에 있습니다." << endl;
	else
		cout << "점 X(" << x << ", " << y << ") 는 원 안에 있습니다." << endl;

}

void Q3_20()
{

	cout << "사각형의 폭과 높이를 입력하세요. : ";
	double width, height;
	cin >> width >> height;

	cout << "구하고자 하는 점X의 좌표쌍(x,y)을 입력하세요. : ";
	double x, y;
	cin >> x >> y;

	double tmp_x, tmp_y;

	if (x < 0)
		tmp_x = -1 * x;

	if (y < 0)
		tmp_y = -1 * y;

	if ((tmp_x <= width / 2.0) && (tmp_y <= height / 2.0))
		cout << "점은 사각형의 안에 있습니다." << endl;
	else
		cout << "점은 사각형의 바깥에 있습니다." << endl;
}

void Q3_22()
{
	//직선의 방정식
	/*

	참고 : http://www.cvi.kr/xe/cvi_qna/40255


	직선 AB : 두 점 A(x1,y1), B(x2, y2)를 지나는 직선
	직선 CD : 구 점 C(x3, y3), D(x4, y4)를 지나는 직선일 때,

	두 직선의 교점(Px, Py)의 좌표는
	Px = ((x1*y2 - y1*x2) * (x3 - x4) - (x1-x2) * ( x3 * x4 - y3 * x4))/((x1=x2)*(y3-y4) - (y1-y2)*(x3-x4))
	Py = (((x1*y2 - y1*x2)*(y3 -y4) - (y1-y2)(x3*y4 - y3*y4 ))/((x1-x2)*(y3-y4) - (y1 - y2) * (x3 - x4))
	단, (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4) = 0 이면 두 직선은 평행 또는 일치.
	*/
	double x1, x2, x3, x4, y1, y2, y3, y4;

	cout << "직선 AB의 각 점의 좌표 2쌍씩 (4개) 입력하세요. : ";
	cin >> x1 >> y1 >> x2 >> y2;
	cout << "직선 cD의 각 점의 좌표 2쌍씩 (4개) 입력하세요. : ";
	cin >> x3 >> y3 >> x4 >> y4;

	//sample Data
	/*교점 있음
	x1 = 2;
	y1 = 2;
	x2 = 5;
	y2 = -1.0;
	x3 = 4.0;
	y3 = 2.0;
	x4 = -1.0;
	y4 = -2.0;
	*/

	//sample Data
	/*교점 없음
	x1 = 2;
	y1 = 2;
	x2 = 7;
	y2 = 6.0;
	x3 = 4.0;
	y3 = 2.0;
	x4 = -1.0;
	y4 = -2.0;
	*/

	double a = y1 - y2;
	double b = x1 - x2;
	double c = y3 - y4;
	double d = x3 - x4;
	double Px, Py;

	Px = (((x1 * y2 - y1 * x2) * d) - (b * (x3 * y4 - y3 * x4))) / ((b * c) - (a * d));
	Py = (((x1 * y2 - y1 * x2) * c) - (a * (x3 * y4 - y3 * x4))) / ((b * c) - (a * d));


	if (a*d - b * c == 0)
		cout << "두 직선은 평행 합니다." << endl;
	else
		cout << "두 직선은 점 (" << Px << ", " << Py << ") 에서 교차합니다." << endl;
}
//다시
void Q3_25()
{
	cout << "사각형 A의 중점 좌표(x,y)를 입력하세요. : ";
	double xA, yA;
	cin >> xA >> yA;

	cout << "사각형 A의 폭과 높이를 입력하세요. : ";
	double width_A, height_A;
	cin >> width_A >> height_A;

	cout << "사각형 B의 중점 좌표(x,y)를 입력하세요. : ";
	double xB, yB;
	cin >> xB >> yB;

	cout << "사각형 B의 폭과 높이를 입력하세요. : ";
	double width_B, height_B;
	cin >> width_B >> height_B;

	//임시 사각형 B의 각 점의 좌표를 위한 임시 변수	
	double x1, y1, x2, y2;

	x1 = xA + width_A / 2;
	x2 = xB - width_B / 2;
	y1 = yA + height_A / 2;
	y2 = yB - height_B / 2;

	//판단하기		
	/*겹치기 조건
	점으로부터 (0,0)까지의 수평 거리가 폭/2보다 작거나 같고, 수직 거리가 높이/2보다 작거나 같으면
	그 점은 직사각형의 내부에 있다.

	//직선의 거리
	root((x2 - x1)^2 + (y2 - y1)^2)

	*/

	//사각형 B의 각 점의 좌표
	double Bx1, Bx2, Bx3, Bx4;
	double By1, By2, By3, By4;

	Bx1 = xB - width_B / 2;
	Bx2 = xB + width_B / 2;
	Bx3 = Bx1;
	Bx4 = Bx2;

	By1 = yB + height_B / 2;
	By2 = By1;
	By3 = yB - height_B / 2;
	By4 = By3;

	if (Get_Length(xA, yA, Bx3, yA) <= width_A / 2 && Get_Length(xA, yA, xA, By2) <= height_A / 2)
		cout << "사각형 B는 사각형 A의 내부에 있습니다." << endl;
	else if (Get_Length(xA, yA, Bx3, yA) <= width_A / 2 || Get_Length(xA, yA, xA, By2) <= height_A / 2)
		cout << "사각형 B는 사각형 A와 겹칩니다." << endl;
	else
		cout << "사각형 B는 사각형 A와 겹치지 않습니다." << endl;


}

void Q3_26()
{

	//직선의 거리
	// root((x2 - x1) ^ 2 + (y2 - y1) ^ 2)

	double Ax, Ay, Ar;
	double Bx, By, Br;
	cout << "원 A의 중점 좌표와 반지름을 입력하세요. (x, y, r) : ";
	cin >> Ax >> Ay >> Ar;
	cout << "원 B의 중점 좌표와 반지름을 입력하세요. (x, y, r) : ";
	cin >> Bx >> By >> Br;

	if (Get_Length(Ax, Ay, Bx, By) <= Ar + Br)
	{
		if (Get_Length(Ax, Ay, Bx, By) <= abs(Ar - Br))
			cout << "원 B는 원 A의 안에 있습니다." << endl;
		else
			cout << "원 B는 원 A와 겹칩니다." << endl;
	}
	else
		cout << "두 원 A와 B는 겹치지 않습니다." << endl;


}

void Q3_29()
{
	double x1, x2, x3;
	double y1, y2, y3;

	cout << "직선 AB의 좌표쌍 2쌍을 각각 입력하세요. (x1, y1, x2, y2) : ";
	cin >> x1 >> y1 >> x2 >> y2;

	cout << "확인 할 점C의 좌표를 입력하세요. : ";
	cin >> x3 >> y3;

	double result = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);

	if (result == 0)
		cout << "점 C는 직선 AB 위에 있습니다." << endl;
	else if (result > 0)
		cout << "점 C는 직선 AB의 왼쪽에 있습니다." << endl;
	else
		cout << "점 C는 직선 AB의 오른쪽에 있습니다." << endl;

}
void p149()
{
	string city1, city2;
	cout << "Enter the first City: ";
	getline(cin, city1);

	cout << "Enter the second city: ";
	getline(cin, city2);

	cout << "The cities in alphabetical order are ";
	if (city1 < city2)
		cout << city1 << " " << city2 << endl;
	else
		cout << city2 << " " << city1 << endl;
}

void p150()
{
	string s1 = "good morning";
	string s2 = "good afternoon";

	cout << s1[0] << endl;

	cout << (s1 == s2 ? "true" : "false") << endl;
	cout << (s1 != s2 ? "true" : "false") << endl;
	cout << (s1 > s2 ? "true" : "false") << endl;
	cout << (s1 >= s2 ? "true" : "false") << endl;
	cout << (s1 < s2 ? "true" : "false") << endl;
	cout << (s1 <= s2 ? "true" : "false") << endl;
}

void p158()
{
	ofstream output;

	output.open("numbers.txt");

	output << 95 << " " << 56 << " " << 34;

	output.close();

	cout << "Done" << endl;

}

void p159()
{
	ifstream input;

	input.open("numbers.txt");

	int score1, score2, score3;

	input >> score1;
	input >> score2;
	input >> score3;

	cout << "Total score is " << score1 + score2 + score3 << endl;

	input.close();

	cout << "Done" << endl;

}

void p162_Q4_4()
{
	double s6, area6;
	cout << "육각형의 한 변의 길이를 입력하세요. : ";
	cin >> s6;

	area6 = (6 * pow(s6, 2)) / (4 * tan(PI / 6));

	cout << "육각형의 면적은 " << area6 << "입니다." << endl;
}
void p164_Q4_16()
{
	cout << "문자열을 입력하세요.";
	string input_4_16;

	getline(cin, input_4_16);
	cout << "문자열의 길이는 " << input_4_16.length() << "이고, 첫 문자는 " << input_4_16.at(0) << "입니다." << endl;
}
void p164_q4_23()
{
	string ssn;
	string name;
	string ssn_old;
	string name_old;
	bool isErrorSSN = false;

	ifstream input;
	input.open("SSN.txt");

	input >> ssn_old;
	input >> name_old;

	input.close();


	cout << "SSN을 입력하세요.: ";
	cin >> ssn;

	//숫자인지 아닌지 검사
	for (int i = 0; i < ssn.length(); i++)
	{
		//구분자 위치는 건너뛴다
		if (ssn.at(3) != '-' || ssn.at(6) != '-')	//구분자 자리에 다른게 있나?
		{
			isErrorSSN = true;
			break;
		}
		else if (isdigit(ssn.at(i)) == 0)	//숫자니?
		{
			isErrorSSN = true;
			break;
		}
		else if (ssn.length() != 11)	//길이가 안맞나?
		{
			isErrorSSN = true;
			break;
		}
	}

	//숫자가 아니거나, 중간에 구분자가 -가 아니거나, 길이가 모자라거나 넘을 경우 에러
	if (isErrorSSN)
		cout << ssn << " 은 유효하지 않은 SSN 입니다." << endl;
	else if (ssn == ssn_old)
		cout << ssn << "은 이미 입력되어있습니다. ";
	else
	{
		cout << "이름을 입력하세요.: ";
		cin >> name;

		ofstream output;
		output.open("SSN.txt");
		output << ssn << " " << name;

		output.close();
	}

}

void p173_5_2_1()
{
	//난수 생성
	srand(time(0));
	int number = rand() % 101;	// 100 까지 나와야 하니까 %101!!
	int answer = 0;

	// 문제 출력
	cout << "0부터 100 사이의 숫자를 맞춰보세요!" << endl << endl;

	while (answer != number)
	{
		cout << "정답은....?  ";
		cin >> answer;

		if (answer > number)
			cout << answer << " 보다는 작아요!" << endl;
		else if (answer < number)
			cout << answer << " 보다는 커요!" << endl;
	}

	cout << "정답!!" << endl;
	cout << "정답은 " << number << "였습니다!" << endl;

}

void p206()
{
	string input_p206;
	bool isPal = true;

	cout << "문자열을 입력하세요. : ";
	cin >> input_p206;

	int high = input_p206.length() - 1;
	for (int i = 0; i < input_p206.length() / 2; i++)
	{
		if (input_p206[i] != input_p206[high])
			isPal = false;
		else
			isPal = true;

		high--;
	}

	if (isPal)
		cout << "문자열 " << input_p206 << "은 회문입니다." << endl;
	else
		cout << "문자열 " << input_p206 << "은 회문이 아닙니다." << endl;
}

void p211_Q5_1()
{

	string input_5_1;
	cout << "정수들을 입력하세요. : ";
	getline(cin, input_5_1);
	int cnt = 0;

	for (int i = 0; input_5_1.at(i) != '\0'; i++)
	{
		cnt++;
		cout << "input_5_1.at(i) : " << input_5_1.at(1) << endl;
	}

	int *numbers = (int*)malloc(sizeof(int) * input_5_1.length());
}

void p213_5_7()
{
	cout << "Degree\tSin\tCos" << endl;

	for (int i = 0; i <= 360; i += 10)
	{
		cout << fixed << setprecision(4) << i << "\t" << sin(i*(PI / 180)) << "\t" << cos(i*(PI / 180)) << endl;
	}
}

void p213_5_8()
{
	cout << "Number\tSquarRoot" << endl;

	for (int i = 0; i <= 20; i += 2)
	{
		cout << fixed << setprecision(4) << i << "\t" << sqrt(i) << endl;;
	}
}

void p214_5_19()
{
	int N_5_19 = 0;
	cout << "1 - 15 사이의 정수를 입력하세요. : ";
	cin >> N_5_19;

	for (int i = 0; i < N_5_19; i++)
	{
		for (int j = N_5_19 - 1; j > i; j--)
			cout << "   ";

		for (int k = i + 1; k > 0; k--)
			cout << k << "  ";

		for (int l = 2; l <= i + 1; l++)
			cout << l << "  ";


		cout << endl;
	}
}

void p214_5_21()
{
	int N_5_21 = 0;
	int tmp = 1;
	cout << "몇 번 반복 할까요? : ";
	cin >> N_5_21;


	for (int i = 0; i < N_5_21; i++)
	{
		for (int x = N_5_21 - 1; x > i; x--)
		{
			cout << setw(N_5_21 / 2) << " ";
		}

		for (int j = 0; j <= i; j++)
			cout << setw(N_5_21 / 2) << pow(2, j);

		for (int k = i - 1; k >= 0; k--)
			cout << setw(N_5_21 / 2) << pow(2, k);

		cout << endl;
	}

}

void alg_p76_a()
{

	int i, n;
	unsigned long counter = 0;

	for (int x = 0; x < 1000; x++) {
		for (n = 2; n <= 1000; n++)
		{
			for (i = 2; i < n; i++)
			{
				counter++;
				if (n % i == 0)
					break;
			}
			/*if (n == i);
			printf("%d\n", n);*/
		}
	}

	//printf("나눗셈을 실행 한 횟수 : %lu\n", counter);
	cout << "a" << endl;
}

void alg_p76_b()
{
	int i, n;
	unsigned long counter = 0;
	int prime[500];
	int ptr = 0;
	prime[ptr++] = 2;

	for (n = 3; n <= 1000; n += 2)
	{
		for (i = 1; i < ptr; i++)
		{
			counter++;
			if (n % prime[i] == 0)
				break;
		}
		if (ptr == i)
			prime[ptr++] = n;
	}

	cout << "b" << endl;

	//for (i = 0; i < ptr; i++)
	//	printf("%d\n", prime[i]);
	//	printf("나눗셈을 실행 한 횟수 : %lu\n", counter);

}

void alg_p76_c()
{
	int i, n;
	unsigned long counter = 0;
	int prime[500];
	int ptr = 0;
	prime[ptr++] = 2;
	prime[ptr++] = 3;

	for (n = 5; n <= 1000; n += 2) {
		int flag = 0;
		for (i = 1; counter++, prime[i] * prime[i] <= n; i++) {
			counter++;
			if (n%prime[i] == 0) {
				flag = 1;
				break;
			}
		}
		if (!flag)
			prime[ptr++] = n;
	}

	cout << "c" << endl;
	//for (i = 0; i < ptr; i++)
	//	printf("%d\n", prime[i]);
	//	printf("나눗셈을 실행 한 횟수 : %lu\n", counter);
}

int mdays[][12] = {
	{ 31,28,31,30,31,30,31,31,30,31,30,31 },
{ 31,29,31,30,31,30,31,31,30,31,30,31 }
};

int isleap(int year)
{
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int dayofyear(int y, int m, int d)
{
	//원본
	/*
	int i;
	int days = d;
	for (i = 1; i < m; i++)
	days += mdays[isleap(y)][i - 1];
	return days;
	*/

	//테스트 출력
	//cout << "day " << m << endl;
	m--; // 한달 뒤로 보낸다. 이번달은 d로 받아오니까.
	while (m > 0)
	{
		d += mdays[isleap(y)][m - 1];	// 배열이 0부터 시작하니까 달 숫자를 1 빼준다.
		m--; //다음 계산할 달(뒤로 1달)로 넘어간다.
			 //테스트
			 //cout << m << " : " << mdays[isleap(y)][m] << endl; // 테스트 출력
	}

	return d;

}

void alg_p85_mod()
{
	int year, month, day;
	int retry;
	do {
		cout << "연 : ";
		cin >> year;
		cout << "월 : ";
		cin >> month;
		cout << "일 : ";
		cin >> day;
		cout << year << "연도의 " << dayofyear(year, month, day) << " 일 입니다." << endl;
		cout << "다시 할까요? (1 - 예 /0 - 아니오) : ";
		cin >> retry;
	} while (retry == 1);
}

int search(int a[], int n, int key)
{
	int i = 0;
	a[n] = key;
	while (1)
	{
		if (a[i] == key)
			break;
		i++;
	}
	return i == n ? -1 : i;
}

void alg_p103()
{
	int i, nx, ky, idx;
	int *x;

	cout << "선형 검색(보초법)";
	cout << "요소 개수 : ";
	cin >> nx;

	x = (int*)calloc(nx + 1, sizeof(int));

	for (i = 0; i < nx; i++)
	{
		cout << "x[" << i << "] : ";
		cin >> x[i];
	}
	cout << "검색값 : ";
	cin >> ky;
	idx = search(x, nx, ky);
	if (idx == -1)
		cout << "검색에 실패했습니다." << endl;
	else
		cout << ky << "(은)는 x[" << idx << "]에 있습니다." << endl;

	free(x);

}

void gichul_20180601()
{
	//이승수
	/*
	숫자 X보다 크거나 같은 수 중 가장 작은 2의 승수 (2^n)를 NPOT(Next Power of Two)라고 할 때,
	주어진 숫자 N개의 NPOT를 구하여 모두 XOR한 값을 구하시오

	조건 :
	1 < X < 2^63
	1 <= N < 2 ^ 18
	*/

	int do_cnt = 0;
	cout << "숫자를 입력하세요. : ";
	cin >> do_cnt;
	int *input_num = (int*)malloc(sizeof(int) * do_cnt);
	int *NPOT = (int*)malloc(sizeof(int) * do_cnt);

	for (int i = 0; i < do_cnt; i++)
	{
		cout << i + 1 << "번째 숫자 : ";
		cin >> input_num[i];
	}

	for (int i = 0; i < do_cnt; i++)
	{
		//각각의 NPOT를 계산
	}

	//각각의 NPOT를 XOR 해버림

}

//다시
void p161_Q4_1()
{
	double r = 0;

	cout << "오각형의 중점과 꼭짓점 사이의 거리를 입력하세요." << endl;
	cin >> r;

	//오각형의 면적
	//(5 * s^2) / (4 * tan(PI / 5))
	//
	// 제 2코사인 법칙
	// a^2 = b^2+ c^2 -2bc cosA
	//a = root(b^2 + c^2 - (2* b* c) * cosA)
	double b = pow(r, 2);
	double c = pow(r, 2);

	//빗변
	double s = pow(pow(r, 2) + pow(r, 2) - (2 * r * r) * cos(72 * (PI / 180)), 0.5);
	double area = (5 * pow(s, 2)) / (4 * tan(PI / 5));


	cout << "오각형의 넓이는 " << fixed << setprecision(2) << area << " 입니다." << endl;


}

void p218_Q5_35()
{
	//숫자 범위 : 1 ~ 10,000
	//약수 구하기
	//숫자 n에 대해서 1 ~ n까지 각각의 숫자로 n%a를 했을 때 0이면 배열에 넣는다.
	//만약 n = a이면 지금까지 배열에 들어간 것들을 모두 합했을 때, n과 같으면 완전수.
	//완전수 역시 따로 배열에 넣어서 출력 준비를 한다.

	int input;
	int *diviser = (int*)malloc(sizeof(int));
	int sum_divs = 0;
	int *answer = (int*)malloc(sizeof(int));
	int cnt_div = 0;
	int cnt_ans = 0;

	cout << "1부터 몇 까지의 숫자 중에서 완전수를 찾을까요?";
	cin >> input;

	for (int i = 1; i < input; i++)
	{
		//나누기 중간 계산용 변수 초기화
		cnt_div = 0;
		sum_divs = 0;


		for (int j = 1; j < i; j++)
		{
			if (i % j == 0)	//나누어지면
			{
				diviser = (int*)realloc(diviser, sizeof(int)* (cnt_div + 1));	// 배열을 1칸 늘림
				diviser[cnt_div++] = j;	// 집어넣고 카운트 올림
				sum_divs += diviser[cnt_div - 1];	// 합쳐본다
			}
		}

		// 약수들의 합 = 그 숫자?
		if (sum_divs == i)
		{
			answer = (int*)realloc(answer, sizeof(int)* (cnt_ans + 1));	//배열 1칸 늘림
			answer[cnt_ans++] = i;	// 집어넣고 카운트 +1
		}
	}

	//결과 출력
	cout << "1부터 " << input << "사이의 숫자 중에서 완전수는 " << cnt_ans << "개 이고, 각각 아래와 같습니다." << endl;

	for (int i = 0; i < cnt_ans; i++)
	{
		cout << answer[i] << endl;
	}
}

void p218_Q5_40()
{
	//추가 조건
	//100번 1,000번. 10,000번 100,000번 1,000,000번. 각각 % 출력
	srand(time(0));

	int front = 0, back = 0;
	int k = 0;
	for (k = 2; k <= 6; k++)
	{
		front = 0; back = 0;
		for (long i = 0; i < pow(10, k); i++)
		{
			if (rand() % 2 == 0)
				front++;
			else
				back++;
		}

		cout << pow(10, k) << "회 결과 - 앞: " << front << "회 / 뒤: " << back << "회 (앞: " << (double)((double)front / (double)(front + back)) * 100 << " %)" << endl;
	}

}

void p218_Q5_43()
{
	int count;
	int cur_t;
	int target_t;
	int cdown = 0;
	cout << "몇 초를 잴까요? :";
	cin >> count;

	cur_t = time(NULL);
	target_t = cur_t + count;

	cout << count << "를 카운트 합니다." << endl;

	while (target_t - cur_t >= 0)
	{
		cur_t = time(NULL);

		if (target_t - cur_t == 0)
		{
			cout << "카운트 다운 종료!" << endl;
			break;
		}
		else if (target_t - cur_t == count)
		{
			//확인용
			//cout << "시간 : " << target_t - cur_t << " cdown : " << cdown << endl;
			cout << target_t - cur_t << "초 남았습니다." << endl;
			count--;
		}
	}
}

void p220_q5_49()
{
	string sent1;
	string sent2;
	int last_idx = 0;
	int ans_cnt = 0;
	char *ans = (char*)calloc(1, sizeof(char));

	cout << "첫 번째 문장을 입력하세요. : ";
	getline(cin, sent1);
	cout << "두 번째 문장을 입력하세요. : ";
	getline(cin, sent2);

	for (int i = 0; i < sent1.length(); i++)
	{
		if (sent1.at(i) == ' ')
			break;
		else
			last_idx = i;
	}

	for (int i = 0; i <= last_idx; i++)
	{
		if (sent1.at(i) == sent2.at(i))
		{
			ans_cnt = i + 1;
		}
		else
			break;
	}


	if (ans_cnt == 0)
		cout << "공통 접두어가 없습니다." << endl;
	else
	{
		cout << "공통 접두어는  \"";
		for (int i = 0; i < ans_cnt; i++)
			cout << sent1.at(i);
		cout << "\" 입니다." << endl;
	}

}

void p220_q5_54()
{
	// coutletter.txt를 읽어서, 그 안에 있는 글자 수를 센다.
	// 파일을 읽는다
	// 파일의 끝에 도달할 때까지 한 줄씩 가져온다.
	// 각 줄의 글자 수(길이)를 더한다.
	// 더해진 글자 수를 출력한다.

	ifstream input;
	input.open("countletter.txt");

	int count = 0;
	string line;

	if (!input)
	{
		cout << "파일을 찾을 수 없습니다!" << endl;
		return;
	}

	while (!input.eof())
	{
		getline(input, line);
		count += line.length();
	}

	cout << "countletter.txt 파일에는 " << count << "글자가 있습니다." << endl;

}

void p220_q5_57()
{
	//비번 검사
	//최소 8자 이상의 문자
	//문자와 숫자로만 구성되어야 함.
	//2개 이상의 숫자가 필요함.

	string input;	//입력받을 문자열
	int min_count = 8;	//최소 문자 수
	bool isAlNum = true;	//영문 또는 숫자 플래그
	int cnt_digit = 0;	//숫자 카운터

	cout << "비밀번호를 입력하세요. : ";
	getline(cin, input);

	//길이 검사
	if (input.length() < min_count)
	{
		cout << "잘못된 비밀번호 입니다." << endl << "최소 8자 이상 입력하셔야 합니다." << endl;
		return;
	}

	//입력 규칙 검사 1 - 문자 종류 검사
	for (int i = 0; i < input.length(); i++)
	{
		if (!isalnum(input.at(i)))
		{
			cout << "잘못된 비밀번호 입니다." << endl << "영문 또는 숫자만 입력할 수 있습니다." << endl;
			isAlNum = false;
			return;
		}
	}

	//입력 규칙 검사 2 - 숫자 갯수 검사.
	for (int i = 0; i < input.length(); i++)
	{
		if (isdigit(input.at(i)))
			cnt_digit++;
	}

	if (cnt_digit < 2)
	{
		cout << "잘못된 비밀번호 입니다." << endl << "최소 2개의 숫자를 입력해야 합니다." << endl;
		return;
	}
	else
		cout << "올바른 비밀번호 입니다." << endl;
}

void printMatrix(int n)
{
	srand(time(NULL));


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << setw(3) << rand() % 2;
		}
		cout << endl;
	}
}

void p278_Q6_16()
{
	int n;

	cout << "정수를 입력하세요. : ";
	cin >> n;

	printMatrix(n);
}

bool LeftOfLine(double x0, double y0, double x1, double y1, double x2, double y2)
{
	if ((x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0) > 0)
		return true;
	else
		return false;
}
bool RightOfLine(double x0, double y0, double x1, double y1, double x2, double y2)
{
	if ((x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0) < 0)
		return true;
	else
		return false;
}
bool onTheSameLine(double x0, double y0, double x1, double y1, double x2, double y2)
{
	if ((x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0) > 0 || ((x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0) < 0))
		if ((x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0) != 0)
			return true;
		else
			return false;

}
bool onTheLineSegment(double x0, double y0, double x1, double y1, double x2, double y2)
{
	if ((x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0) == 0)
		if ((x0 >= x2 || y0 <= y2) && (x1 >= x2 || y1 >= y2))
			return true;
		else
			return false;
}

void p279_Q6_20()
{
	double x0 = 0, x1 = 0, x2 = 0;
	double y0 = 0, y1 = 0, y2 = 0;

	cout << "세 점의 좌표를 입력합니다. " << endl << "점 A의 좌표 : ";
	cin >> x0 >> y0;
	cout << "점 B의 좌표 : ";
	cin >> x1 >> y1;
	cout << "점 C의 좌표 : ";
	cin >> x2 >> y2;

	if (onTheLineSegment(x0, y0, x1, y1, x2, y2))
		cout << "점 C(" << x2 << ", " << y2 << ")는 선분 AB( A(" << x0 << ", " << y0 << " ) 부터 B( " << x1 << ", " << y1 << ") 위에 있습니다." << endl;

	if (onTheSameLine(x0, y0, x1, y1, x2, y2))
		cout << "점 C(" << x2 << ", " << y2 << ")는 선분 AB( A(" << x0 << ", " << y0 << " ) 부터 B( " << x1 << ", " << y1 << ")의 연장선상에 있습니다." << endl;

	if (LeftOfLine(x0, y0, x1, y1, x2, y2))
		cout << "점 C(" << x2 << ", " << y2 << ")는 선분 AB( A(" << x0 << ", " << y0 << " ) 부터 B( " << x1 << ", " << y1 << ")의 왼쪽에 있습니다." << endl;

	if (RightOfLine(x0, y0, x1, y1, x2, y2))
		cout << "점 C(" << x2 << ", " << y2 << ")는 선분 AB( A(" << x0 << ", " << y0 << " ) 부터 B( " << x1 << ", " << y1 << ")의 오른쪽에 있습니다." << endl;

}

void p280_Q6_21()
{
	int cnt = 0;
	int num = 2;
	int ans_cnt = 0;
	int print_per_line = 10;
	int *ans = (int*)calloc(1, sizeof(int));
	int *aTmp = (int*)calloc(1, sizeof(int));
	int place = 0;
	while (cnt < 10)
	{
		int tmp = 0;

		for (int i = 1; i <= num; i++)
		{
			if (num % i == 0)
				tmp++;
		}

		if (tmp == 2)
		{
			//회문 소수인지 판단하고 맞으면 아래 실행하도록 수정
			for (int k = 0; k < 100; k++)
			{
				if (num % (int)pow(10, k) == 0)
				{
					place = k;
					aTmp = (int*)realloc(aTmp, sizeof(int) * k + 1);

					cout << "자릿수 : " << place << endl;

					for (int x = place; x > 0; x--)
					{
						aTmp[x - 1] = num / pow(10, x);
						cout << "짠! : " << aTmp[x - 1] << endl;
					}
				}
			}
			ans = (int*)realloc(ans, sizeof(int) * (cnt + 1));
			ans[cnt] = num;
			ans_cnt++;
			cnt++;
		}

		cout << num << endl;
		num++;
	}

	for (int i = 0; i < ans_cnt; i++)
	{
		if (i % 11 == 10)
			cout << endl << setw(5) << ans[i];
		else
			cout << setw(5) << ans[i];
	}

}

void p280_Q6_22()
{
	srand(time(NULL));

	int point = 0;
	int dice1 = rand() % 6 + 1;
	int dice2 = rand() % 6 + 1;

	cout << "당신의 주사위 " << dice1 << " + " << dice2 << " = " << dice1 + dice2 << endl;

	if (dice1 + dice2 == 2 || dice1 + dice2 == 3 || dice1 + dice2 == 12)
		cout << "당신의 패배입니다." << endl;
	else if (dice1 + dice2 == 7 || dice1 + dice2 == 11)
		cout << "당신의 승리입니다" << endl;
	else
	{
		point = dice1 + dice2;
		cout << "포인트는 " << point << "입니다." << endl;
	}

	while (point != 0)
	{
		dice1 = rand() % 6 + 1;
		dice2 = rand() % 6 + 1;

		cout << "당신의 주사위 " << dice1 << " + " << dice2 << " = " << dice1 + dice2 << endl;

		if (dice1 + dice2 == point)
		{
			cout << "당신의 승리입니다" << endl;
			break;
		}
		else if (dice1 + dice2 == 7)
		{
			cout << "당신의 패배입니다." << endl;
			break;
		}
		else
			cout << "포인트는 " << point << "입니다." << endl;
	}


}
void p281_Q6_23()
{

}
void p281_Q6_24() {}

void alg_p109()
{
	int input;
	int search;
	int result = 0;
	int arrMin = 0, arrMax = 0;

	cout << "이진 검색" << endl;
	cout << "요소의 갯수를 입력하세요. : ";
	cin >> input;
	int *aData = (int*)calloc(input, sizeof(int)*input);
	arrMax = input - 1;

	cout << "오름차순으로 입력하세요. " << endl;
	for (int i = 0; i < input; i++)
	{
		cout << "x[" << i << "] = ";
		cin >> aData[i];
	}

	cout << "검색 값을 입력하세요. : ";
	cin >> search;

	while (arrMin <= arrMax)
	{
		cout << "검색 범위 : " << arrMin << " ~ " << arrMax << endl;

		if (aData[(arrMin + arrMax) / 2] == search)
		{
			result = arrMax / 2;
			break;
		}
		else if (aData[(arrMin + arrMax) / 2] > search)
			arrMax = arrMax / 2 - 1;
		else if (arrMin == arrMax)
		{
			if (arrMin == search)
				result = 0;
			else
				result = -1;
		}
		else
			arrMin = arrMax / 2 + 1;
	}


	if (result >= 0)
		cout << search << "(은)는  x[" << result << "]에 있습니다." << endl;
	else
		cout << search << "(을)를 찾을 수 없습니다." << endl;



}

void alg_p115()
{
	int input;
	int search;
	int result = 0;
	int arrMin = 0, arrMax = 0;

	cout << "이진 검색" << endl;
	cout << "요소의 갯수를 입력하세요. : ";
	cin >> input;
	int *aData = (int*)calloc(input, sizeof(int)*input);
	arrMax = input - 1;

	cout << "오름차순으로 입력하세요. " << endl;
	for (int i = 0; i < input; i++)
	{
		cout << "x[" << i << "] = ";
		cin >> aData[i];
	}

	cout << "검색 값을 입력하세요. : ";
	cin >> search;

	cout << "   |";
	for (int i = 0; i < input; i++)
		cout << setw(3) << i;

	cout << endl;

	cout << setw(0) << "---+";
	for (int i = 0; i < input; i++)
		cout << "---";
	cout << endl;


	while (arrMin <= arrMax)
	{

		cout << "   " << "|";

		for (int i = 0; i < arrMin; i++)
			cout << "   ";

		cout << "<-";

		for (int i = 0; i < (arrMin + arrMax) / 2; i++)
			cout << "   ";

		cout << setw(0) << "+";

		for (int i = (arrMin + arrMax) / 2; i < arrMax; i++)
			cout << setw(3) << " ";

		cout << "->" << endl;

		cout << setw(3) << (arrMin + arrMax) / 2 << "|";
		for (int i = 0; i < input; i++)
			cout << setw(3) << aData[i];
		cout << endl;

		if (aData[(arrMin + arrMax) / 2] == search)
		{
			result = arrMax / 2;
			break;
		}
		else if (aData[(arrMin + arrMax) / 2] > search)
			arrMax = arrMax / 2 - 1;
		else if (arrMin == arrMax)
		{
			if (arrMin == search)
				result = 0;
			else
				result = -1;
		}
		else
			arrMin = arrMax / 2 + 1;
	}


	if (result >= 0)
		cout << search << "(은)는  x[" << result << "]에 있습니다." << endl;
	else
		cout << search << "(을)를 찾을 수 없습니다." << endl;

}

int int_cmp(const int *a, const int *b)
{
	if (*a < *b)
		return -1;
	else if (*a > *b)
		return 1;
	else
		return 0;
}

void shuffle(string& s)
{
	srand(time(NULL));

	cout << "원본 : " << s << endl;
	for (int i = 1; i < s.length() - s.length() % 3; i++)
	{
		SWAP_A_B(&s.at(rand() % (s.length() - 1)), &s.at(rand() % (s.length() - 1)), sizeof(char));
	}
	cout << "결과 : " << s << endl;
}
void p282_6_30()
{
	string input;
	cout << "문자열을 입력하세요. :";
	getline(cin, input);

	shuffle(input);
}

void intersectPoint(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double& x, double& y, bool& isIntersecting)
{
	double a = y1 - y2;
	double b = x1 - x2;
	double c = y3 - y4;
	double d = x3 - x4;

	double mother_A = a * d - b * c;

	if (mother_A == 0)
		isIntersecting = true;
	else
		isIntersecting = true;

	if (isIntersecting)
	{


		x = (((x1 * y2 - y1 * x2) * d) - (b * (x3 * y4 - y3 * x4))) / ((b * c) - (a * d));
		y = (((x1 * y2 - y1 * x2) * c) - (a * (x3 * y4 - y3 * x4))) / ((b * c) - (a * d));

		cout << "두 직선은 점 (" << x << ", " << y << ") 에서 교차합니다." << endl;
	}
	else
		cout << "두 직선은 평행 합니다." << endl;

}
void p282_6_35()
{
	double x1 = 0, x2 = 0, x3 = 0, x4 = 0;
	double y1 = 0, y2 = 0, y3 = 0, y4 = 0;
	double x = 0, y = 0;
	bool isIntersecting = false;

	cout << isIntersecting << endl;// 테스트용
	cout << "첫 번째 직선의 끝점 2개의 좌표쌍을 입력하세요. (x1,y1) (x2,y2) : ";
	cin >> x1 >> y1 >> x2 >> y2;

	cout << "두 번째 직선의 끝점 2개의 좌표쌍을 입력하세요. (x3,y3) (x4,y4) : ";
	cin >> x3 >> y3 >> x4 >> y4;

	intersectPoint(x1, y1, x2, y2, x3, y3, x4, y4, x, y, isIntersecting);
}
int indexOf(const string& s1, const string&s2)
{
	int ans = 0;
	int cnt = 0;
	//확인용
	/*cout << s1 << " (length : " << s1.length() << ")" << endl;
	cout << s2 << " (length : " << s2.length() << ")" << endl;*/

	for (int i = 0; i < s2.length() - s1.length() + 1; i++)
	{
		for (int j = i; j < i + s1.length(); j++)
		{
			if (s2.at(j) == s1.at(j - i))
			{
				ans = i;
				//cout << i << "같음" << endl;	// 확인용
				cnt++;
				if (cnt == s1.length())
					return ans;
			}
			else
			{
				ans = -1;
				cnt = 0;
			}
		}
		//검색 위치 확인 용
		/*cout << s2 << endl;
		for (int x = 0; x < i; x++)
		cout << " ";
		cout << "*" << "(" << i << "),ans = " << ans << endl;*/
	}

	return ans;
}

void p286_Q6_43()
{
	string s1;
	string s2;

	cout << "첫 번째 문자열을 입력하세요.";
	getline(cin, s1);
	cout << "두 번째 문자열을 입력하세요.";
	getline(cin, s2);


	/* 	//테스트용
	s1 = "asd";
	s2 = "dbjhbskb sj asd jcik";
	*/
	cout << "index of (\"" << s1 << "\", \"" << s2 << "\" ) is " << indexOf(s1, s2) << endl;
}

void p298_7_3() //복권문제
{
	ifstream file;
	file.open("lottery.txt");	// 모두 있음
								//file.open("lottery_bad.txt");	// 부족함

	int cnt = 0;
	bool iscovered = false;
	bool sheet[99] = { false };
	int numbers[99] = { 0 };

	if (file.is_open())
	{
		for (int i = 0; numbers[i] == 0; i++)
		{
			file >> numbers[i];
			cnt = i;
		}
		file.close();
	}
	// cout << "파일 읽기 종료." << "cnt : " << cnt << "cnt2 : " << cnt2 << endl;	// 테스트

	for (int i = 0; i <= cnt; i++)
	{
		if (numbers[i] == 0)
			break;
		else if (numbers[i] != 0)
		{
			sheet[i] = true;
			// cout << "시트 [" << i << "] : " << sheet[i] << endl;	// 테스트
		}
	}

	for (int i = 0; i < cnt; i++)
	{
		if (sheet[i] == true)
			iscovered = true;
		else
		{
			iscovered = false;
			break;
		}
	}

	cout << "The ticket ";

	if (!iscovered)
		cout << "don't ";

	cout << "cover all numbers." << endl;
}

void p327_Q7_3()
{
	cout << "1부터 100 사이의 정수를 입력하세요. : " << endl << "입력 : ";
	string numbers;
	getline(cin, numbers);

	int ans[101] = { 0 };
	int cnt = 0;

	//cout << numbers.length() << endl;	// 확인용
	for (int i = 0; i < numbers.length(); i++)
	{
		if (numbers.at(i) == 32)	//아스키 코드로 스페이스 바
		{
			ans[cnt] += 1;	// 숫자랑 같은 배열 위치에 카운트를 1 증가시킨다.
			cnt = 0;	//카운트 초기화
		}
		else
		{
			cnt *= 10;	// 공백이 아니면 지금까지 저장한 수에 10을 곱한다. (한자릿수 올려줌)
			cnt += numbers.at(i) - 48;	// 숫자처럼 생긴 문자는 ASCII 값48부터니까 -48하면 숫자값이 나옴
										//cout << "i = " << i << ", cnt = " << cnt << endl;	// 확인용
		}
	}

	ans[cnt] += 1;	//마지막 숫자의 카운트를 하나 올린다. (if문을 빠져나오기 때문에 +1시켜줄 수 없음)	

	for (int i = 0; i <= 100; i++)
	{
		// 1개일 때... 영문이라 단수/복수 구분을 위해서
		if (ans[i] != 0 && ans[i] == 1)
		{
			cout << i << " occurs " << ans[i] << " time" << endl;
		}
		else if (ans[i] != 0 && ans[i] > 1)
		{
			cout << i << " occurs " << ans[i] << " times" << endl;
		}
	}
}

double min(double array[], int size)
{
	double min = 9999999;
	int min_idx = 0;
	for (int i = 0; i < size; i++)
		min = min > array[i] ? array[i] : min;

	return min;
}
int indexOfSmalledtElement(double array[], int size)
{
	double min = 9999999;
	int min_idx = 0;
	for (int i = 0; i < size; i++)
	{
		min = array[i];
		if (array[min_idx] > array[i])
			min_idx = i;
	}
	return min_idx;
}
void p327_Q7_9to10()
{
	cout << "숫자 10개를 입력하세요. : " << endl << "입력 : ";
	double input[10] = { 0 };
	for (int i = 0; i < 10; i++)
		cin >> input[i];

	//확인용
	/*
	cout << "출력 : ";
	for (int i = 0; i < 10; i++)
	cout << input[i] << " " ;
	cout << endl;
	*/

	cout << "가장 작은 수 : " << min(input, sizeof(input) / sizeof(double)) << endl;
	cout << "가장 작은 수의 인덱스 : " << indexOfSmalledtElement(input, sizeof(input) / sizeof(double)) << endl;
}

void p328_Q7_15()
{
	bool lockers[100] = { true };	// 1번 학생이 모두 열어버림
		
	for (int i = 1; i < 100; i++)	// 학생
	{		
		for (int j = 1; j*i < 100; j++)	//상호작용 할 락커 번호
		{
			lockers[i*j] = !lockers[i*j];				
		}
	}

	for (int i = 0; i < 100; i++)	// 출력하기
	{
		if (lockers[i])
			cout << i+1 << " ";
	}

	cout << endl;	
	
}
void p329_Q7_17()
{
	/*
	분기 횟수 = 슬롯 수 -1
	왼쪽 끝 = 슬롯수 -1 * L
	왼쪽 끝 +1 = 슬롯 수 -1-1*L + R

	*/
}

void ftoa(double f, char s[])
{
	sprintf(s, "%.4f", f);
	
	int Dot = 0;
	for (int i = 0; i < strlen(s); i++)	//소수점 위치를 찾는다
	{
		if (s[i] == '.')
			Dot = i;
	}
	
	for (int i = 0; i < strlen(s); i++)	// 문자 길이만큼 반복
	{
		if (i < Dot && (Dot - i) % 3 == 0)	// 소수점 기준으로 3자리 마다 앞쪽으로
			cout << ", " << s[i] << " ";	//콤마 찍고 숫자 찍고
		else
			cout << s[i] << " " ;	//아니면 그냥 숫자만 찍고
	}
	cout << endl;	
}

void p335_Q7_38() 
{
	double f;
	char s[99];

	cout << "실수를 입력하세요. :";
	cin >> f;

	ftoa(f, s);
}

const int N = 3;


void addMatrix(const double a[][N], const double b[][N], double c[][N])
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			c[i][j] = a[i][j] + b[i][j];

	cout << "두 행렬의 곱" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int n = 0; n < N; n++)
		{
			cout << setw(4) << a[i][n];
		}

		if (i % 2 == 0)
			cout << setw(4) << " ";
		else
			cout << setw(4) << "+";

		for (int m = 0; m < N; m++)
		{
			cout << setw(4) << b[i][m];
		}


		if (i % 2 == 0)
			cout << setw(4) << " ";
		else
			cout << setw(4) << "=";

		for (int l = 0; l < N; l++)
		{
			cout << setw(5) << c[i][l];
		}

		cout << endl;
	}

}
void p356_Q8_5() 
{
	double a[N][N];
	double b[N][N];
	double c[N][N];

	cout << "첫 번째 행렬을 입력하세요. : ";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> a[i][j];
		}		
	}

	/*cout << "A 행렬" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << a[i][j] << " " ;
		}
		cout << endl;
	}*/

	cout << "두 번째 행렬을 입력하세요. : ";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> b[i][j];
		}
	}

	/*cout << "B 행렬" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << b[i][j] << " ";
		}
		cout << endl;

	}*/

	addMatrix(a, b, c);
}
void multiplyMatrix(const double a[][N], const double b[][N], double c[][N])
{
	//정답 행렬을 초기화
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			c[i][j] = 0;
		}		
	}	

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
			{
				c[i][j] += a[i][k] * b[k][j];
				//cout << "c["<<i<<"]["<<j<<"]"<< c[i][j] << "should be " << a[i][k] * b[k][j] << endl;
			}


	cout << "두 행렬의 합 " << endl;
	for (int i = 0; i < N; i++)
	{
		for (int n = 0; n < N; n++)
		{
			cout << setw(4) << a[i][n];
		}

		if (i % 2 == 0)
			cout << setw(4) << " ";
		else
			cout << setw(4) << "*";

		for (int m = 0; m < N; m++)
		{
			cout << setw(4) << b[i][m];
		}


		if (i % 2 == 0)
			cout << setw(4) << " ";
		else
			cout << setw(4) << "=";

		for (int l = 0; l < N; l++)
		{
			cout << setw(5) << fixed << setprecision(1) << c[i][l];
		}

		cout << endl;
	}

}
void p358_Q8_9()
{
	double a[N][N];
	double b[N][N];
	double c[N][N];

	cout << "첫 번째 행렬을 입력하세요. : ";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> a[i][j];
		}
	}

	/*cout << "A 행렬" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << setw(4) << a[i][j] << " ";
		}
		cout << endl;
	}*/

	cout << "두 번째 행렬을 입력하세요. : ";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> b[i][j];
		}
	}

	/*cout << "B 행렬" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << setw(4) << b[i][j] << " ";
		}
		cout << endl;
	}*/

	multiplyMatrix(a, b, c);
}

void inverse(const double A[][2], double inverseOfA[][2])
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			inverseOfA[i][j] = 0;
		}
	}
	double a = A[0][0];
	double b = A[0][1];
	double c = A[1][0];
	double d = A[1][1];
	
	double tmp[2][2] = { d, -b, -c, a };

	//cout << "tmp : " << endl << tmp[0][0] << " " << tmp[0][1] << endl << tmp[1][0] << " " << tmp[1][1] << endl;	// 테스트

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)			
			{
				inverseOfA[i][j] = (1/(a*d - b*c)) * tmp[i][j];
			}

	for (int i = 0; i < 2; i++)
	{
		for (int l = 0; l < 2; l++)
		{
			cout << setw(5) << fixed << setprecision(1) << inverseOfA[i][l];
		}
		cout << endl;
	}
}
void p360_Q8_15()
{
	double A[2][2];
	double inverseOfA[2][2];

	cout << "숫자 4개를 입력해주세요. : ";
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			cin >> A[i][j];

	inverse(A, inverseOfA);

}

bool isConsecutiveFour(double values[][7])
{
	int lines = 6;
	int same_count = 4;

	int cnt = 0;
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			cnt = 0;
			//가로 검사
			for (int hor = 0; hor < same_count && j+hor < 7; hor++)	//4개 일치이므로 그만큼 앞에까지
			{
				if (values[i][j] == values[i][j + hor])
					cnt += 1;
				else
				{
					cnt = 0;
					break;
				}

				if (cnt == 4)
					return true;
			}

			//세로 검사
			for (int ver = 0; ver < same_count; ver++)	//4개 일치이므로 그만큼 앞에까지
			{
				if (values[i][j] == values[i+ver][j])
					cnt += 1;
				else
				{
					cnt = 0;
					break;
				}

				if (cnt == 4)

					return true;
			}

			//대각선 검사 (/)
			for (int upright = 0; upright < same_count && i - upright >= 0 && j - upright >= 0; upright++)	//4개 일치이므로 그만큼 앞에까지
			{
				if (values[i][j] == values[i+upright][j+upright] && i >0 && j > 0)
					cnt += 1;
				else
				{
					cnt = 0;
					break;
				}

				if (cnt == 4)
					return true;
			}

			//대각선 검사 (\)		
			for (int downright = 0; downright < same_count && i + downright < lines && j + downright < 7; downright++)	//4개 일치이므로 그만큼 앞에서 끝
			{
				if (values[i][j] == values[i + downright][j + downright])
					cnt += 1;
				else
				{
					cnt = 0;
					break;
				}

				if (cnt == 4)
					return true;
			}
		}
	}
	return false;
}
void p360_Q8_21()
{
	const int lines = 6;	//입력 할 줄 수
	const int cols = 7;
	bool ans = false;
	double values[lines][cols];

	
	for (int i = 0; i < lines; i++)
	{
		cout << i + 1 << "번째 줄의 숫자 7개를 입력하세요. : ";
		for (int j = 0; j < cols; j++)
			cin >> values[i][j];
	}

	ans = isConsecutiveFour(values);

	if (ans)
		cout << "TRUE" << endl;
	else
		cout << "FALSE" << endl;

	/*테스트 데이터
	int values1[lines][cols] = { 
		0, 1, 0, 3, 1, 6, 1, 
		0, 1, 6, 8, 6, 0, 1,
		5, 6, 2, 1, 8, 2, 9,
		6, 5, 6, 1, 1, 9, 1,
		1, 3, 6, 1, 4, 0, 7,
		3, 3, 3, 3, 4, 0, 7
	};
	int values2[lines][cols] = {
		0, 1, 0, 3, 1, 6, 1,
		0, 1, 6, 8, 6, 0, 1,
		5, 5, 2, 1, 8, 2, 9,
		6, 5, 6, 1, 1, 9, 1,
		1, 5, 6, 1, 4, 0, 7,
		3, 5, 3, 3, 4, 0, 7 
	};
	int values3[lines][cols] = {
		0, 1, 0, 3, 1, 6, 1,
		0, 1, 6, 8, 6, 0, 1,
		5, 6, 2, 1, 6, 2, 9,
		6, 5, 6, 6, 1, 9, 1,
		1, 3, 6, 1, 4, 0, 7,
		3, 6, 3, 3, 4, 0, 7
	};
	int values4[lines][cols] = {
		0, 1, 0, 3, 1, 6, 1,
		0, 1, 6, 8, 6, 0, 1,
		9, 6, 2, 1, 8, 2, 9,
		6, 9, 6, 1, 1, 9, 1,
		1, 3, 9, 1, 4, 0, 7,
		3, 3, 3, 9, 4, 0, 7
	};
	*/

	//테스트
	/*
	bool ans1 = isConsecutiveFour(values1);
	bool ans2 = isConsecutiveFour(values2);
	bool ans3 = isConsecutiveFour(values3);
	bool ans4 = isConsecutiveFour(values4);
	*/

	//테스트
	/*
	cout << " 1 : " << ans1 << endl; 
	cout << "  2 : " << ans2 << endl;
	cout << "  3 : " << ans3 << endl;	
	cout << "  4 : " << ans4 << endl;
	*/
}



void p374()
{
	Circle circle1(1.0);
	Circle circle2(25);
	Circle circle3(125);

	cout << "The area of the circle of radius " << circle1.radius << " is " << circle1.getArea() << endl;
	cout << "The area of the circle of radius " << circle2.radius << " is " << circle2.getArea() << endl;
	cout << "The area of the circle of radius " << circle3.radius << " is " << circle3.getArea() << endl;

	circle2.radius = 100;
	cout << "The area of the circle of radius " << circle2.radius << " is " << circle2.getArea() << endl;

	circle1;
	cout << "(circle1) The area of the circle of radius " << circle1.radius << " is " << circle1.getArea() << endl;


}

class TV
{
public:
	int channel;
	int volumeLevel;
	bool on;

	TV()
	{
		channel = 1;
		volumeLevel = 1;
		on = false;
	}

	void turnOn()
	{
		on = true;
	}

	void turnOff()
	{
		on = false;
	}

	void setChannel(int newChannel)
	{
		if (on && newChannel >= 1 && newChannel <= 120)
			channel = newChannel;
	}

	void setVolume(int newVolumeLevel)
	{
		if (on && newVolumeLevel >= 1 && newVolumeLevel <= 7)
			volumeLevel = newVolumeLevel;
	}

	void channelUp()
	{
		if (on && channel < 120)
		channel++;
	}

	void channelDown()
	{
		if (on && channel > 1)
			channel--;
	}
	void volumeUp()
	{
		if (on && volumeLevel < 7)
			volumeLevel++;
	}

	void volumeDown()
	{
		if (on && volumeLevel > 1)
			volumeLevel--;
	}
};

void p376()
{
	TV tv1;
	tv1.turnOn();
	tv1.setChannel(30);
	tv1.setVolume(3);

	TV tv2;
	tv2.turnOn();
	tv2.channelUp();
	tv2.channelUp();
	tv2.volumeUp();

	cout << "tv1's channel is " << tv1.channel << " and volume level is " << tv1.volumeLevel << endl;
	cout << "tv2's channel is " << tv2.channel << " and volume level is " << tv2.volumeLevel << endl;
}

void p395()
{
	cout << "Enter Yearly interest rate, for example 8.25: ";
	double annualInterestRate;
	cin >> annualInterestRate;;

	cout << "Enter number of years as an integer, for example 5: ";
	int numberOfYears;
	cin >> numberOfYears;

	cout << "Enter loan amount, for example 120000.95: ";
	double loanAmount;
	cin >> loanAmount;

	Loan loan(annualInterestRate, numberOfYears, loanAmount);

	cout << fixed << setprecision(2);
	cout << "The monthly payment is " << loan.getMonthlyPayment() << endl;
	cout << "The total payment is " << loan.getTotalPayment() << endl;
}


void p400_Q9_1()
{
	cRectangle r1;
	cRectangle r2;

	r1.setWidth(4);
	r1.setHeight(40);

	r2.setWidth(3.5);
	r2.setHeight(35.9);

	cout << setw(3) << "r1.width : " << r1.getWidth() << " r1.height : " << r1.getHeight() << " r1.area : " << r1.getArea() << " r1.perimeter : " << r1.getPerimeter() << endl;
	cout << setw(3) << "r2.width : " << r2.getWidth() << " r2.height : " << r2.getHeight() << " r2.area : " << r2.getArea() << " r2.perimeter : " << r2.getPerimeter() << endl;
}

void p401_Q9_4()
{
	MyPoint P1;
	MyPoint P2;

	P1.setX(0);
	P1.setY(0);
	P2.setX(10);
	P2.setY(30.5);

	cout << "두 점 (0,0)에서 (10,30.5) 까지의 거리는 " << P1.getDistance(P2) << " 입니다." << endl;
}

void p402_Q9_7()
{
	StopWatch timer;
	int arrTest[100000];
	srand(time(NULL));

	for (int i = 0; i < 100000; i++)
		arrTest[i] = rand() % 1000 + rand()%500 + rand()%100;

	int tmp_idx = 0;
	
	cout << "10,000개의 난수를 선택정렬 합니다. START!!" << endl;
	timer.start();
	//cout << " 시작 : " << timer.getStartTime() << endl;	// 테스트
		for (int i = 0; i < 100000; i++)
		{
			for (int j = i; j < 100000; j++)
			{

				if (arrTest[j] < arrTest[i])
					tmp_idx = j;
			}

			SWAP_A_B(&arrTest[i], &arrTest[tmp_idx], sizeof(int));
		}
	timer.stop();
	//cout << " 끝 : " << timer.getEndTime() << endl;	// 테스트
	
	cout << "작업에 걸린 시간은 " << timer.getElapsedTime() << "밀리초 입니다." << endl;
	
}

long double Factorial(double n)
{
	if (n > 0)
		return n * Factorial(n - 1);
	else
		return 1;
}


int hanoi(int disc, char from, char to)
{
	if (disc == 1)
	{
		cout << disc << "번 : " << "기둥 " << (char)(from) << " >> " << "기둥 " << (char)(to) << endl;
		return 0;
	}

	hanoi(disc - 1, from, 198 - from - to);

	cout << disc << "번 : " << "기둥 " << (char)(from) << " >> " << "기둥 " << (char)(to) << endl;	
	hanoi(disc - 1, 198 - from - to, to);

	return 0;

}
void alg_p178_Q5_3()
{
	int from = 'A';
	int to = 'C';
	int disc;
	StopWatch timer;
	cout << "하노이의 탑!" << endl;
	cout << "몇 개의 원반을 옮길까요? ";
	cin >> disc;

	timer.start();
	hanoi(disc, from, to);
	timer.stop();

	cout << "경과 시간 : " << timer.getElapsedTime() << " 밀리초(ms)" << endl;
}

int main()
{




	//alg_p178_Q5_3();	// 완료
	//p401_Q9_4();	// 완료
	//p402_Q9_7();	// 완료
	//p400_Q9_1();	// 완료
	//p395();	// 완료
	//p376();	// 완료

	//p374();	// 완료


	//p360_Q8_15();	// 완료
	//p360_Q8_21();	// 완료
	//p356_Q8_5();	// 완료
	//p358_Q8_9();	// 완료

	//p328_Q7_15();	// 완료
	//p329_Q7_17();	// 미완
	//p335_Q7_38();	// 완료


	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
	// 2018-06-12
	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
	//gichul_20180601();
	//p211_Q5_1();	
	//p280_Q6_21();
	//p280_Q6_22();
	//p281_Q6_23();
	//p281_Q6_24();
	//Q3_25();	// 완료
	//Q3_26();	// 완료
	//Q3_29();	// 완료
	//alg_p109();	//완료
	//alg_p115();	//완료
	//p278_Q6_16();	//완료
	//p279_Q6_20();	//완료
	//p220_q5_49();	// 완료
	//p220_q5_54();	// 완료
	//p220_q5_57();	// 완료
	//p218_Q5_35();	// 완료
	//p218_Q5_40();	// 완료
	//p218_Q5_43();	// 완료
	//alg_p103();	// 완료
	//alg_p85_mod();	// 완료
	//Q3_19();	//완료
	//Q3_20();	//완료
	//Q3_22();	//완료
	//p149();	//완료
	//p150();	//완료
	//p158();	//완료
	//p159();	//완료
	//p161_Q4_1();	// 완료
	//p162_Q4_4();		// 완료
	//p164_Q4_16();		// 완료
	//p164_q4_23();		// 완료
	//p173_5_2_1();		// 완료
	//p206();			// 완료	
	//p213_5_7();		// 완료 sin / cos  같은 함수는 안에 들어가는 각도 값이 라디안 값. 각도 * (PI / 180) = 라디안 각도
	//p213_5_8();		// 완료
	//p214_5_19();		// 완료
	//p214_5_21();	//완료
	//p286_Q6_43();	// 완료
	//p282_6_35();	// 완료
	//p282_6_30();	// 완료
	//p327_Q7_3();	// 완료
	//p327_Q7_9to10();	// 완료
	//p298_7_3();	// 완료
	return 0;
}

