// Q3_22.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

//참고
//비주얼 스튜디오 단축키
//블록 모두 접기 : Ctrl + m + o
//블록 모두 펼치기 : Ctrl + m + p


#include "stdafx.h"
#include "Circle.h"
#include "Circle2D.h"
#include "Rectangle.h"
#include "Rectangle2D.h"
#include "MyPoint.h"
#include "StopWatch.h"
#include "Stack.h"
#include "Loan.h"
#include "Member.h"
#include "LinkedList.h"
#include "Student.h"

using namespace std;


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
	int sum = 0;
	int cnt = 0;
	double mean = 0;
	string input_5_1;

	cout << "정수들을 입력하세요. : ";
	getline(cin, input_5_1);	

	for (int i = 0; i < input_5_1.length(); i++)
	{
		if (input_5_1.at(i) - 48 >= 0 && input_5_1.at(i) - 48 < 10)
		{
			cnt++;
			//cout << cnt << endl;
		}
	}
	
	int *numbers = (int*)malloc(sizeof(int) * input_5_1.length());
	
	for (int i = 0; i < cnt*2-1; i++)
		if (input_5_1.at(i) - 48 >= 0 && input_5_1.at(i) - 48 < 10)
		{
			numbers[i] = input_5_1.at(i) - 48;
			sum += numbers[i];
			cout << "sum : " << sum << endl;
		}

	mean = sum / cnt;

	cout << "입력된 수 들의 평균은 " << fixed << setprecision(2) << mean << "입니다." << endl;
	
	

	
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
void p281_Q6_24() 
{

	
	int ans[] = { 0 };
	int cnt_ans = 0;
	//소수인지 확인


	//회문인지 확인
	//숫자를 임시 스트링 배열에 넣고
	//맨 앞과 맨 뒤를 길이의 1/2까지 비교해서
	//모두 같음이면 출력 할 숫자 목록에 추가

	//목록의 마지막 요소를 임시 스트링 배열에 넣고
	//길이를 판단.
	//길이 +1을 구한다. (setw용)
	int width = 0;

	// 회문 출력
	// 출력 할 숫자 목록의 숫자를 0번부터 10개씩 출력한다.
	
	for (int i = 0; i < cnt_ans; i++)
	{
		static int cnt_print = 0;

		cout << setw(width) << ans[i];

	}
}

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

double minimum(double array[], int size)
{
	double minimum = 9999999;
	int minimum_idx = 0;
	for (int i = 0; i < size; i++)
		minimum = minimum > array[i] ? array[i] : minimum;

	return minimum;
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

	cout << "가장 작은 수 : " << minimum(input, sizeof(input) / sizeof(double)) << endl;
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

	srand(time(0));

	int slots;
	int balls;
	cout << "빈 머신!" << endl;
	cout << "슬롯 수를 입력하세요.: ";
	cin >> slots;

	int *BallsInSlots;
	BallsInSlots = (int*)calloc(slots, sizeof(int));

	cout << "몇 개의 공을 넣을까요? : ";
	cin >> balls;

	for (int ball_cnt = 0; ball_cnt < balls; ball_cnt++)
	{
		int ball_dest = slots / 2;

		for (int i = 0; i < slots - 1; i++)
		{
			if (( rand() % 100000 ) % 2 == 0)
			{
				if (ball_dest > 0)
				{
					ball_dest--;
					//cout << "L";	// 테스트용
				}
				else
				{
					ball_dest = 0;
					//cout << "L"; //테스트용
				}
			}
			else
			{
				if (ball_dest < slots - 1)
				{
					ball_dest++;
					//cout << "R";	// 테스트용
				}
				else
				{
					ball_dest = slots;
					//cout << "R";	// 테스트용
				}
			}
		}

		//cout << " ==> "<< ball_dest << "번 슬롯" << endl;	// 테스트용
		BallsInSlots[ball_dest] += 1;
	}

	for (int i = 0; i < slots; i++)
	{
		//if(BallsInSlots[i])	//편한 확인용
		cout << setw(3) << i + 1 << "번째 슬롯 : " << setw(5) << BallsInSlots[i] << " 개("
			<< fixed << setw(5) << setprecision(4) << (double)(((double)BallsInSlots[i] / (double)balls) * 100) << " %)" << endl;
	}
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

	cout << "The area of the circle of radius " << circle1.getRadius() << " is " << circle1.getArea() << endl;
	cout << "The area of the circle of radius " << circle2.getRadius() << " is " << circle2.getArea() << endl;
	cout << "The area of the circle of radius " << circle3.getRadius() << " is " << circle3.getArea() << endl;

	circle2.setRadius(100);
	cout << "The area of the circle of radius " << circle2.getRadius() << " is " << circle2.getArea() << endl;

	circle1;
	cout << "(circle1) The area of the circle of radius " << circle1.getRadius() << " is " << circle1.getArea() << endl;


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

bool replaceString(string & s, const string & oldSubStr, const string & newSubStr)
{
	bool isReplaced = false;
	int currentPosition = 0;

	while (currentPosition < s.length())
	{
		int position = s.find(oldSubStr, currentPosition);
		if (position == string::npos)
			return isReplaced;
		else
		{
			s.replace(position, oldSubStr.length(), newSubStr);
			currentPosition = position + newSubStr.length();
			isReplaced = true;
		}
	}

	return isReplaced;
	return false;
}

void p413()
{
	cout << " Enter string s, oldSubStr, and newSubStr: ";
	string s, oldSubStr, newSubStr;
	cin >> s >> oldSubStr >> newSubStr;

	bool isReplaced = replaceString(s, oldSubStr, newSubStr);

	if (isReplaced)
		cout << "The replaced string is " << s << endl;
	else
		cout << "no matches" << endl;
}
void p422_p424()
{
	cout << "Number of circle objects created : " << Circle::getNumberOfObjects() << endl;

	Circle circle1;
	cout << "The area of the circle of radius " << circle1.getRadius() << " is " << circle1.getArea() << endl;
	cout << "Number of circle objects created : " << Circle::getNumberOfObjects() << endl;

	Circle circle2(5.0);
	cout << "The area of the circle of radius " << circle2.getRadius() << " is " << circle2.getArea() << endl;
	cout << "Number of circle objects created : " << Circle::getNumberOfObjects() << endl;

	circle1.setRadius(3.3);
	cout << "The area of the circle of radius " << circle1.getRadius() << " is " << circle1.getArea() << endl;

	cout << "circle1.getNumberOfObjects() returns  " << circle1.getNumberOfObjects() << endl;
	cout << "circle2.getNumberOfObjects() returns  " << circle2.getNumberOfObjects() << endl;
}
void p438()
{
	Stack<int> stack;

	cout << "peek 테스트" << stack.peek() << endl;

	for (int i = 0; i < 101; i++)
		stack.push(i);

	while (!stack.isEmpty())
	{
		cout << stack.pop() << " ";
		cout << "peek 테스트" << stack.peek() << endl;

	}

}

void p443_Q10_1()
{
	string s1;
	string s2;
	int compare = 0;


	cout << "Enter a string s1 : ";
	cin >> s1;
	cout << "Enter a string s2 : ";
	cin >> s2;

	for (int i = 0; i < s1.length(); i++)
	{	
		//cout << "체크 중 : " << s1.at(i) << endl;	// 테스트
		
		//cout << s1.at(i) << " : ";	// 테스트
		for (int j = 0; j < s2.length(); j++)
		{
			if (s1.at(i) == s2.at(j))
			{
				//cout << "있음" << endl;	// 테스트
				compare++;
				break;
			}
			else
			{
				//cout << "없음" << endl;	// 테스트	
			}
		}
		
	}

	//cout << endl << "compare : " << compare << endl;	// 테스트

	if (compare == s1.length())
		cout << s1 << " and " << s2 << " are anagrams" << endl;
	else
		cout << s1 << " and " << s2 << " are not anagrams" << endl;

}

string commonChars(const string& s1, const string& s2)
{
	string common = {""};
	
	for (int i = 0; i < s1.length(); i++)
	{
		int tmp = s2.find(s1.substr(i, 1));
		if(tmp > 0)
		{
			common.append(s1.substr(i, 1));
		}
	}
	return common;
}

void p443_Q10_2() 
{
	int commonCharSize = 0;
	string s1;
	string s2;

	cout << "Enter a string for s1 : ";
	cin >> s1;
	cout << "Enter a string for s2 : ";
	cin >> s2;
	
	commonCharSize = commonChars(s1, s2).length();
	if (commonCharSize)
		cout << "The common characters are : " << commonChars(s1, s2) << endl;
	else
		cout << "There is no common character" << endl;
}
void p445_Q10_15()
{
	char isContinue = 'y';
	
	do {
		system("cls");

		srand(time(NULL));
		//입력 및 입력 처리용
		char guess;
		int correct = 0;
		int missed = 0;
		bool isCorrect = false;

		//기능 제어용
		int nTry = 0;
		int correctSum = 0;		
		int MaxTry = 10;		
		bool *isOpen;

		//문제은행
		string words[] =
		{
			"program","class","direct","unity","api","whiteboard"
		};

		//선정된 문제
		string Question = words[rand() % 6];

		//표시 여부 플래그 배열 할당 및 초기화(false)
		isOpen = (bool*)calloc(Question.length(), sizeof(bool));
		for (int i = 0; i < Question.length(); i++)
		{
			isOpen[i] = false;
		}

		//단어가 길어지면 도전 횟수 증가
		MaxTry = Question.length() + 5;

		cout << "행 맨 게임!" << endl;
		//cout << "정답 확인 : " << Question << endl;	// 테스트

		do {
			isCorrect = false;

			cout << "문제 : ";
			for (int i = 0; i < Question.length(); i++)
			{
				if (!isOpen[i])
					cout << "*";
				else
					cout << Question.at(i);
			}
			cout << MaxTry << "번 중 "<< nTry << "번째 도전 > ";
			cin >> guess;

			for (int i = 0; i < Question.length(); i++)
			{

				if (Question.at(i) == guess)
				{
					if (!isOpen[i])
					{
						isOpen[i] = true;
						correctSum++;
						isCorrect = true;
					}
					else
					{
						cout << guess << "(은)는 이미 입력 하셨습니다." << endl;
					}
				}
			}

			if (!isCorrect)
			{
				cout << guess << "(은)는 포함되지 않습니다." << endl;
				missed++;
			}

			nTry++;
		} while (nTry < MaxTry && correctSum != Question.length());

		if (correctSum == Question.length())
			std::cout << "정답은 " << Question << "이었습니다!" << endl << "결과 : 맞춤 - " << correctSum << "회 / 틀림 - " << missed << "회" << endl;

		std::cout << endl << "다시 한번 도전 하시겠습니까? (y - 다시 도전 / n - 그만하기) : ";
		cin >> isContinue;

	} while (isContinue == 'y' || isContinue == 'Y');
}

int** set_no(int **board, int row, int col)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			board[abs(i-8)][abs(col-j)] = -1;
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == -1)
				cout << "□";
			else if (board[i][j] == 1)
				cout << "☆";
			else
				cout << "■";
		}
		cout << endl;
	}

	return board;
}
void alg_p192()
{
	/*
	//1. 8x8 체스판
	//2. 퀸을 배치. 퀸은 가로 / 세로 / 대각선 방향으로 직선이동
	//3. 서로 공격할 수 없도록 8명의 퀸을 배치하라. (있는 곳 : ■, 없는 곳 : □)
	//4. 재귀 함수를 이용하여 제작하라.
	//5. 첫번째 퀸 위치를 사용자가 입력할 수 있도록 하라.
	*/

	int **board = (int**)calloc(8, sizeof(int*));	
	int row;
	int col;
			
	for (int i = 0; i < 8; i++)
	{
		board[i] = (int*)calloc(8, sizeof(int));

		for (int j = 0; j < 8; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}


	cout << "8명의 퀸!" << endl;
	cout << "첫번째 퀸을 어디에 배치할 까요? " << endl << "행 : ";
	
	//srand(time(NULL));	// 테스트
	//row = rand() % 8;	// 테스트
	//col = rand() % 8;	// 테스트
	
	cin >> row;
	cout << "열 : ";
	cin >> col;	
	
	//좌상에서 우하로 N자 형으로 검색
	for (int col = 0; col < 8; col++)
	{
		for (int row = 0; row < 8; row++)
		{
			board[row][col] = 1;			
			board = set_no(board, row, col);
		}
	}

	for (int i = 0; i < 8; i++)
	{
		cout << "               ";
		for (int j = 0; j < 8; j++)
		{
			if ((board[i][j] == 0))
				cout << "□ ";
			else if ((board[i][j] == -1))
				cout << "▩ ";
			else if ((board[i][j] == 1))
				cout << "■ ";
		}
		cout << endl;
	}
	

	free(board);
}

void printArray(const int* list, int size)
{
	for (int i = 0; i < size; i++)
		cout << list[i] << " ";
	cout << endl;
}

int* p469_f(int list1[], const int list2[], int size)
{
	for (int i = 0; i < size; i++)
	{
		list1[i] += list2[i];
	}
	return list1;
}
void p469_1()
{
	int list1[] = { 1,2,3,4 };
	int list2[] = { 1,2,3,4 };

	int* p = p469_f(list1, list2, 4);
	cout << p[0] << endl;
	cout << p[1] << endl;
}
void p469_2()
{
	int list[] = { 4,2,3,6,5,1 };
	printArray(list, 6);

	int* min = min_element(list, list + 6);
	int* max = max_element(list, list + 6);
	cout << "The min value is " << *min << " at index " << (min - list) << endl;
	cout << "The max value is " << *max << " at index " << (max - list) << endl;

	random_shuffle(list, list + 6);
	printArray(list, 6);

	sort(list, list + 6);
	printArray(list, 6);

	int key = 4;
	int* p = find(list, list + 6, key);
	if (p != list + 6)
		cout << "The value " << *p << " is found at postion " << (p - list) << endl;
	else
		cout << "The valus " << *p << " is not found" << endl;
}
int* p473_reverse(const int* list, int size)
{
	int* result = new int[size];
	
	for (int i = 0, j = size - 1; i < size; i++, j--)
		result[j] = list[i];

	return result;
}

void p473() 
{
	int list[] = { 1,2,3,4,5,6 };
	int *p = p473_reverse(list, 6);
	printArray(p, 6);

	delete p;
}

void p481()
{
	Circle* pCircle1 = new Circle();
	Circle* pCircle2 = new Circle();
	Circle* pCircle3 = new Circle();

	cout << "Number of cirlce objects created: " << Circle::getNumberOfObjects() << endl;

	delete pCircle1;

	cout << "Number of cirlce objects created: " << Circle::getNumberOfObjects() << endl;

}

void p487()
{
	Circle circle1(5);
	Circle circle2(circle1);

	cout << "After creating circle2 from circle1: " << endl;
	cout << "\tcircle1.getRadius() returns " << circle1.getRadius() << endl;
	cout << "\tcircle1.getArea() returns " << circle1.getArea() << endl;
	cout << "\tcircle2.getRadius() returns " << circle2.getRadius() << endl;
	cout << "\tcircle2.getArea() returns " << circle2.getArea() << endl;


	circle1.setRadius(10.5);
	circle2.setRadius(20.5);

	cout << "After Modifying circle1 and circle2: " << endl; 
	cout << "\tcircle1.getRadius() returns " << circle1.getRadius() << endl;
	cout << "\tcircle1.getArea() returns " << circle1.getArea() << endl;
	cout << "\tcircle2.getRadius() returns " << circle2.getRadius() << endl;
	cout << "\tcircle2.getArea() returns " << circle2.getArea() << endl;
}

int* doubleCapacity(const int* list, int size)
{
	int* a = new int[size * 2];

	for (int i = 0; i < size * 2; i++)
	{
		if (i >= size)
			a[i] = 0;
		else
			a[i] = list[i];
	}

	return a;

}
void p494_q11_3()
{
	int Capacity_1[6] = { 1,2,3,4,5,6 };
	cout << "Before : " << endl;
	printArray(Capacity_1, 6);
	int *a = doubleCapacity(Capacity_1, 6);

	cout << "After : " << endl;
	printArray(a, 12);
}


void p496_q11_8()
{
	Circle2D c1(2, 2, 5.5);
	Circle2D c2(2, 2, 5.5);
	Circle2D c3(4,5, 10.5);
	cout << "Page 496, Q 11.8 >> " << endl;
	cout << "Rectangle c1 : center (x,y) = " << c1.getPosX() << ", " << c1.getPosY() << ", radius = " << c1.getRadius() << endl;
	cout << "Rectangle c2 : center (x,y) = " << c2.getPosX() << ", " << c2.getPosY() << ", radius = " << c2.getRadius() << endl;
	cout << "Rectangle c3 : center (x,y) = " << c3.getPosX() << ", " << c3.getPosY() << ", radius = " << c3.getRadius() << endl;
	
	cout << "Area of c1 is : " << c1.getArea() << " and perimeter of c1 is " << c1.getPerimeter() << endl;
	cout << "c1.contains(3,3) is " << c1.contains(3, 3) << endl;
	cout << "c1.contains(c2) is " << c1.contains(c2) << endl;
	cout << "c1.overlaps(c3) is " << c1.overlaps(c3) << endl << endl;
}

void p496_q11_9()
{
	Rectangle2D r1(2, 2, 5.5, 4.9);
	Rectangle2D r2(4, 5, 10.5, 3.2);
	Rectangle2D r3(3, 5, 2.3, 5.4);

	cout << "Page 497, Q 11.9 >> " << endl;
	cout << "Rectangle r1 : center (x,y) = " << r1.getCenterX() << ", " << r1.getCenterY() << ", width = " << r1.getWidth() << ", height = " << r1.getHeight() << endl;
	cout << "Rectangle r2 : center (x,y) = " << r2.getCenterX() << ", " << r2.getCenterY() << ", width = " << r2.getWidth() << ", height = " << r2.getHeight() << endl;
	cout << "Rectangle r3 : center (x,y) = " << r3.getCenterX() << ", " << r3.getCenterY() << ", width = " << r3.getWidth() << ", height = " << r3.getHeight() << endl;
		
	cout << "Area of r1 is : " << r1.getArea() << " and perimeter of c1 is " << r1.getPerimeter() << endl;
	cout << "r1.contains(3,3) is " << r1.contains(3, 3) << endl;
	cout << "r1.contains(r2) is " << r1.contains(r2) << endl;
	cout << "r1.overlaps(r3) is " << r1.overlaps(r3) << endl;
}


typedef enum {
	TERMINATE, INS_FRONT, INS_REAR, RMV_FRONT, RMV_REAR, PRINT_CRNT, RMV_CRNT, SRCH_NO, SRCH_NAME, PRINT_ALL, CLEAR
} MENU;

MENU SelectMenu(void)
{
	int i, ch;

	// 각 요소들을 (char*)로 캐스트 해야 정상 작동함. (책과는 다르다... )
	char *mstring[] = {(char*)("머리에 노드를 삽입"), (char*)("꼬리에 노드를 삽입"), (char*)("머리 노드를 삭제"),
		(char*)("꼬리 노드를 삭제"), (char*)("선택한 노드를 출력"), (char*)("선택한 노드를 삭제"),
		(char*)("번호로 검색"), (char*)("이름으로 검색"), (char*)("모든 노드를 출력"),
		(char*)("모든 노드를 삭제"),
	};

	do
	{
		for (i = TERMINATE; i < CLEAR; i++)
		{
			cout << "(" << setw(2) << i + 1 << ") " << mstring[i] << "\t";
			if ((i % 3) == 2)
				cout << endl;
		}
		cout << "( 0) 종료 : ";
		cin >> ch;
	} while (ch < TERMINATE || ch > CLEAR);
		return (MENU)ch;
}

void alg_341()
{
	MENU menu;
	List list;
	Initialize(&list);

	do {
		Member x;
		switch (menu = SelectMenu())
		{
		case INS_FRONT:
			x = ScanMember("머리에 삽입", MEMBER_NO | MEMBER_NAME);
			InsertFront(&list, &x);
			break; 
		case INS_REAR:
			x = ScanMember("꼬리에 삽입", MEMBER_NO | MEMBER_NAME);
			InsertRear(&list, &x);
			break;
		case RMV_FRONT:
			RemoveFront(&list);
			break;
		case RMV_REAR:
			RemoveRear(&list);
			break;
		case PRINT_CRNT:
			PrintLnCurrent(&list);
			break;
		case RMV_CRNT:
			RemoveCurrent(&list);
			break;
		case SRCH_NO:
			x = ScanMember("검색", MEMBER_NO);
			if (search(&list, &x, MemberNoCmp) != NULL)
				PrintLnCurrent(&list);
			else
				cout << "그 번호의 데이터가 없습니다." << endl;
			break;
		case SRCH_NAME:
			x = ScanMember("검색", MEMBER_NAME);
			if (search(&list, &x, MemberNameCmp) != NULL)
				PrintLnCurrent(&list);
			else
				cout << "그 이름의 데이터가 없습니다." << endl;
			break;			
		case PRINT_ALL:
			Print(&list);
			break;
		case CLEAR:
			Clear(&list);
			break;
		}
	} while (menu != TERMINATE);
	Terminate(&list);
}

template<typename T1, typename T2>
T2 maxValue(T1 value1, T2 value2)
{
	if (value1 > value2)
		return value1;
	else
		return value2;
}

template<typename T>
void sort(T list[], int listSize)
{
	for (int i = 0; i < listSize; i++)
	{
		T currentMin = list[i];
		int currentMinIndex = i;


		for (int j = i + 1; j < listSize; j++)
		{
			if (currentMin > list[j])
			{
				currentMin = list[j];
				currentMinIndex = j;
			}
		}

		if (currentMinIndex != i)
		{
			list[currentMinIndex] = list[i];
			list[i] = currentMin;
		}
	}
}

template<typename T>
void printArray(const T list[], int listSize)
{
	for (int i = 0; i < listSize; i++)
	{
		cout << list[i] << " ";
	}
	cout << endl;
}

void p503()
{
	cout << "Maximum between 1 and 3 is " << maxValue(1, 3) << endl;
	cout << "Maximum between 1 and 0.3 is " << maxValue(1, 0.3) << endl;
	cout << "Maximum between 'A' and 'N' is " << maxValue('A', 'N') << endl;
	cout << "Maximum between \"NBC\" and \"ABC\" is " << maxValue("NBC", "ABC") << endl;
}

void p507()
{
	int list1[] = { 3, 5, 1, 0, 2, 8, 7 };
	sort(list1, 7);
	printArray(list1, 7);

	double list2[] = { 3.5,0.5,1.4,0.4,2.5,1.8,4.7 };
	sort(list2, 7);
	printArray(list2, 7);

	string list3[] = { "Atlanta", "Dallas", "Denver", "Chicago" };
	sort(list3, 4);
	printArray(list3, 4);
}
void testgenericstack()
{
	Stack<int> intStack;
	for (int i = 0; i < 10; i++)
		intStack.push(i);

	while (!intStack.isEmpty())
		cout << intStack.pop() << " ";
	cout << endl;

	Stack<string> stringStack;
	stringStack.push("chicago");
	stringStack.push("Denver");
	stringStack.push("London");

	while (!stringStack.isEmpty())
		cout << stringStack.pop() << " ";
	cout << endl;
}

template<typename T>
void PrintStack(Stack<T>& stack)
{
	while (!stack.isEmpty())
		cout << stack.pop() << " ";
	cout << endl;
}

void testgenericstackwithtemplatefunction()
{
	Stack<int> intStack;

	for (int i = 0; i < 10; i++)
		intStack.push(i);
	PrintStack(intStack);

	Stack<string> stringStack;
	stringStack.push("chicago");
	stringStack.push("Denver");
	stringStack.push("London");
	PrintStack(stringStack);
}

void p521()
{
	vector<int> intVector;

	for (int i = 0; i < 10; i++)
	{
		intVector.push_back(i + 1);
		cout << "size : " << intVector.size() << endl;
	}

	cout << "Numbers in the vector: ";
	for (int i = 0; i < intVector.size(); i++)
		cout << intVector[i] << " ";

	vector<string> stringVector;
	stringVector.push_back("Dallas");
	stringVector.push_back("Huston");
	stringVector.push_back("Austin");
	stringVector.push_back("Norman");

	cout << "\nStrings in the string vector: ";
	for (int i = 0; i < stringVector.size(); i++)
		cout << stringVector[i] << " ";

	stringVector.pop_back();

	vector<string> V2;
	V2.swap(stringVector);
	V2[0] = "Atlanta";

	cout << "\nStrings in the cector v2: ";
	for (int i = 0; i < V2.size(); i++)
		cout << V2.at(i) << " ";
	cout << endl;	
}

int sum(const vector<vector<int>> &matrix)
{
	int total = 0;
	for (unsigned row = 0; row < matrix.size(); row++)
	{
		for (unsigned column = 0; column < matrix[row].size(); column++)
		{
			total += matrix[row][column];
		}
	}

	return total;
}
void p525()
{
	vector<vector<int>> matrix(4);

	for (unsigned i = 0; i < 4; i++)
		matrix[i] = vector<int>(3);

	matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
	matrix[1][0] = 4; matrix[1][1] = 5; matrix[1][2] = 6;
	matrix[2][0] = 7; matrix[2][1] = 8; matrix[2][2] = 9;
	matrix[3][0] = 10; matrix[3][1] = 11; matrix[3][2] = 12;

	cout << "Sum of all elements is : " << sum(matrix) << endl;
}


// 입력된 문자열을 단순히 쪼개서 하나로 만드는 함수
vector<string> split_them(const string &expression)
{
	//입력된 수식을 잘라서 숫자부와 연산자 및 괄호 부분으로 나눠서 저장

	vector<string> all;	//리턴용
	string numbers;	//숫자 전용 임시 저장소

	//cout << "익스프레션 사이즈 (커스텀 ) " << expression.size() << endl;	// 테스트
	for (unsigned i = 0; i < expression.size(); i++)	//수식 길이 동안
	{
		if (isdigit(expression[i]))	//숫자면
		{
			numbers.append(1, expression[i]);	// 숫자 입시 저장소에 넣는다.			
		}
		else if (numbers.size() > 0)				//숫자 쌓아 놓은게 있으면
		{
			all.push_back(numbers);			//숫자 문자열을 리턴용 문자열 뒤에 넣는다.
			numbers.erase();				//숫자 문자열을 비워준다. 다음 숫자 입력을 위해서.
		}
		else if (numbers.size() == 0)	// 숫자는 아닌데, 첫 글자가 문자이면
		{
			if (expression[i] == '-')	// 마이너스 다음에 바로 괄호가 오면 -1 *와 같으니까
				if(expression[i+1] == '(' || (isspace(expression[i + 1]) && expression[i+2] == '('))
			{
				numbers.append(1, expression[i]);	//마이너스 넣고
				numbers.append(1, '1');	// 1 넣고
				all.push_back(numbers);	// 스택에 넣고
				numbers.erase();	// 넘버 지운다.
				all.push_back("*");	// 곱하기도 넣어준다.
				i++;	// 한칸 이동시킨다.
			}
			else if (expression[i] == '-' && isdigit(expression[i + 1]))
			{
				i++;
				numbers.append(1, expression[i - 1]);
				numbers.append(1, expression[i]);
			}
		}

		if (!isspace(expression[i]) && !isdigit(expression[i]))		// 스페이스 바가 아니면 연산자니까 저장저장
		{								
			string s;						// 지역변수로 잠깐 쓰고 버림. if 나가면 사라짐
			s.append(1, expression[i]);		// s에다가 지금 그 문자 넣는다.
			all.push_back(s);				// 리턴용 끝에다가 붙여넣는다.
		}
	}

	if (numbers.size() > 0)						// 마지막 숫자는 아직 numbers에 들어있으니까 
		all.push_back(numbers);					// 리턴용에 넣어준다.

	return all;		//받아라!
}   
// 계산식을 실행하는 부분
void DoOperation(Stack<double> &numStack, Stack<char> &oprStack)
{
	char op = oprStack.pop();	// 마지막에 들어간 게 연산자 -> 꺼내기
	double right = numStack.pop();	// 나중에 들어간게 오른쪽 숫자 -> 꺼내기
	double left = 0.0;			// 에러 처리용?
	if (!numStack.isEmpty())
		left = numStack.pop();	// 먼저 들어간게 왼쪽 숫자 -> 꺼내기
	else
		op = '+';

	//cout << "현재 계산 할 수식 : " << left <<" " << op << " "<< right << endl;	//테스트
	// 연산자에 따라서 숫자 스택 끝에 계산 결과를 넣는다. 
	// 어파치 숫자 끝에 2개 빠지고 그 계산 결과를 넣는 것이기 때문에 OK.
	if (op == '+')
	{
		numStack.push(left + right);
		//cout << " = " << left + right << endl;	// 테스트
	}
	else if (op == '-')
	{
		if (right > 0)
			numStack.push(left - right);
		else 
			numStack.push(left + right);
		//cout << " = " << left - right << endl;	// 테스트
	}
	else if (op == '*')
	{
		numStack.push(left * right);
		//cout << " = " << left * right << endl;	// 테스트
	}
	else if (op == '/')
	{
		numStack.push(left / right);
		//cout << " = " << left / right << endl;	// 테스트
	}
	else if (op == '^')	//추가분
	{
		numStack.push(pow(left, right));
	}
	else if (op == '%')	//추가분
	{
		if (abs(left) < abs(right))
			numStack.push(left);
		else
		{
			if (left < 0)
			{
				while (abs(left) > abs(right))
				{
					left = left + abs(right);
				}
				numStack.push(left);
			}
			else
			{
				while (abs(left) > abs(right))
				{
					left = left - abs(right);
				}
				numStack.push(left);
			}
			
		}
	}
	
}
// 입력된 계산식을 잘라서 숫자부와 연산자부로 나눠 넣는 함수
double makeCalulatable(const string &expression)	
{
	//숫자 저장용 스택
	Stack<double> numStack;

	//연산자 저장용 스택
	Stack<char> oprStack;

	//토큰 생성 : 토큰 = 각 글자들. 토큰 길이 = 숫자 + 연산자 더하기
	vector<string> tokens = split_them(expression);
	
	//테스트
	//cout << "입력된 토큰 : ";
	//for (unsigned i = 0; i < tokens.size(); i++)					// 토큰 처음부터 끝까지
	//	cout << tokens[i] << " ";
	//cout << endl;

	//토큰 검색
	for (unsigned i = 0; i < tokens.size(); i++)					// 토큰 처음부터 끝까지
	{		
		// 이번 차례가 연산자라면, 앞에 나왔던 연산자를 먼저 처리한다. 
		if (tokens[i][0] == '-' && isdigit(tokens[i][1]))
		{
			numStack.push(atof(tokens[i].c_str()));
			//cout << "음수를 넣고, 픽 해본다 : " << numStack.peek() << endl;	// 테스트
		}

		if (tokens[i][0] == '+' || tokens[i][0] == '-')				// 더하기나 빼기이면 -> + - * - 전부 해결
		{
			while (!oprStack.isEmpty() &&							// 일단 비어있지 않고
				(oprStack.peek() == '+' || oprStack.peek() == '-'			//더하기거나 빼기거나
					|| oprStack.peek() == '*' || oprStack.peek() == '/'		//곱하기거나 나누기일 때마다
					|| oprStack.peek() == '^' || oprStack.peek() == '%'))	//지수이거나 나머지 연산일 때	// 추가
			{
				DoOperation(numStack, oprStack);					// 숫자 스택과 연산자 스택을 넘겨서 계산 시킨다.
			}
				oprStack.push(tokens[i][0]);									// 앞쪽 계산을 끝냈으니, 이번 차례 연산자를 넣어준다.
		}
		else if (tokens[i][0] == '*' || tokens[i][0] == '/' || tokens[i][0] == '%')		// 곱하기 또는 빼기
		{
			while (!oprStack.isEmpty() &&							// 일단 비어있지 않고
				(oprStack.peek() == '*' || oprStack.peek() == '/'		// 곱하기거나 나누기일 때마다
					|| oprStack.peek() == '^' || oprStack.peek() == '%'))	//지수이거나 나머지 연산일 때
			{
				DoOperation(numStack, oprStack);
			}
				oprStack.push(tokens[i][0]);							// 앞쪽 계산을 끝냈으니, 이번 차례 연산자를 넣어준다.
		}
		else if (tokens[i][0] == '^')		// 제곱
		{
			while (!oprStack.isEmpty() &&							// 일단 비어있지 않고
				(oprStack.peek() == '*' || oprStack.peek() == '/'		// 곱하기거나 나누기일 때마다
					|| oprStack.peek() == '^' || oprStack.peek() == '%'))	//지수이거나 나머지 연산일 때
			{
				DoOperation(numStack, oprStack);
			}
			oprStack.push(tokens[i][0]);							// 앞쪽 계산을 끝냈으니, 이번 차례 연산자를 넣어준다.			
		}
		else if (tokens[i][0] == '(')								// 여는 괄호면!!!!
		{
			oprStack.push('(');							// 연산자 스택에 ( 넣는다. ) 나왔을 때 중단점 확인을 위해서.
		}
		else if (tokens[i][0] == ')')								// 닫는 괄호면
		{
			while (oprStack.peek() != '(')							// (가 나올 때 까지
			{
				DoOperation(numStack, oprStack);					//계산 ㄱㄱ
			}														// 이제 oprStack의 마지막 요소는 (가 되었다.
			oprStack.pop();											//여는 괄호를 뺀다.
		}
		else if (tokens[i][0] == '.')						// 소수점 처리
		{
			int head_num = numStack.pop();	// 먼저 들어갔던 소수점 앞 숫자를 꺼내서 임시 저장
			//cout << "pop된 head_num : " << head_num << endl;		// 테스트~

			i++;	// 다음 인덱스로 넘긴다.
			double tmp = atof(tokens[i].c_str());		//소수 이후 숫자를 tmp에 넣는다.	
			//cout << "tmp : " << tmp << endl;	// 테스트
			//cout << "tmp / pow(10, tokens[i].size()) : " << tmp / pow(10, tokens[i].size()) << endl;	// 테스트
			
			tmp /= pow(10, tokens[i].size());	// 숫자 길이 만큼 소수점으로 만들어준다.
			if (head_num >=0)
				numStack.push(head_num + tmp);	//소수점 앞쪽이 양수면 더해주고
			else
				numStack.push(head_num - tmp);	//소수점 앞쪽이 음수면 빼준다.

			//테스트
			//cout << "(소수점 넣기 후) 지금 oprStack.peek() : " << oprStack.peek() << endl;
		}
		else														// 숫자
		{
			//if (i + 1 < tokens.size())
			//{
			//	if (isdigit(tokens[i][0]) && isdigit(tokens[i + 1][0]))		//숫자만 2개 연속으로 있다면
			//	{
			//		numStack.push(atof(tokens[i].c_str()));					//숫자처럼 생긴 문자를 c-string 스타일의 숫자로 만들어서 숫자 스택에 넣는다.
			//		i++;
			//		/*버그 수정
			//		오른쪽 계산 결과가 음수 * 음수 = 양수 가 되어버리면 부호가 사라지는 문제 수정
			//		=> 오른쪽이 될 숫자가 양수이면, 음수 계산 후 양수가 되어버렸을 수 있으므로 +를 더해준다.
			//		++는 +와 동일.+-는 -와 동일하므로 문제 없음
			//		*/
			//		if (atof(tokens[i].c_str()) > 0)				
			//		{
			//			oprStack.push('+');
			//			numStack.push(atof(tokens[i].c_str()));					//숫자처럼 생긴 문자를 c-string 스타일의 숫자로 만들어서 숫자 스택에 넣는다.
			//		}
			//		else
			//			numStack.push(atof(tokens[i].c_str()));					//숫자처럼 생긴 문자를 c-string 스타일의 숫자로 만들어서 숫자 스택에 넣는다.

			//	}
			//	else
			//		numStack.push(atof(tokens[i].c_str()));					//숫자처럼 생긴 문자를 c-string 스타일의 숫자로 만들어서 숫자 스택에 넣는다.			
			//}
			//else
				numStack.push(atof(tokens[i].c_str()));			
		}
	}
	
	//마무리로 남아있는게 있다면 싹 해치운다.
	while (!oprStack.isEmpty())
	{
		DoOperation(numStack, oprStack);
	}

	// 연산자는 없는데, 숫자만 2개 남은 경우가 있다면 두 수를 +시켜준다. 
	// (오른쪽 계산 결과 - 부호가 사라지고 양수가 될 경우, 연산자 증발 현상 발생)
	// 이 때는 + 기호를 강제 삽입하여 연산시켜준다.
	//if (oprStack.isEmpty() && numStack.getSize() > 1)
	//{
	//	oprStack.push('+');
	//	DoOperation(numStack, oprStack);
	//}

	return numStack.pop();											//숫자 스택에 들어있는 최종값 = 계산 결과를 리턴한다.
}

double makeCalulatable2(const string &expression)
{
	//숫자 저장용 스택
	Stack<double> numStack;

	//연산자 저장용 스택
	Stack<char> oprStack;

	//토큰 생성 : 토큰 = 각 글자들. 토큰 길이 = 숫자 + 연산자 더하기
	vector<string> tokens = split_them(expression);

	//테스트
	cout << "입력된 토큰33 : ";
	for (unsigned i = 0; i < tokens.size(); i++)					// 토큰 처음부터 끝까지
		cout << tokens[i];
	cout << endl;

	//토큰 검색
	for (unsigned i = 0; i < tokens.size(); i++)					// 토큰 처음부터 끝까지
	{
		double tmp[99];
		int tmp_cnt = 0;

		//숫자 스택에 들어있는 최종값 = 계산 결과를 리턴한다.
	}

	return numStack.pop();											//숫자 스택에 들어있는 최종값 = 계산 결과를 리턴한다.
}
void calculator()
{
	string expression;
	//cout << "Enter an expression : ";
	//getline(cin, expression);

	//expression = "-1+2";	//테스트 문자열
	//cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;

	//expression = "-1 - 2 - 3";	//테스트 문자열
	//cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;

	//expression = "- ( 2 - 3 )";	//테스트 문자열
	//cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;

	//expression = "-(1 - 2) - 3";	//테스트 문자열
	//cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;

	
	//테스트 케이스
	expression = "4.0 ^ -3.0";	//테스트 문자열
	cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;
	expression = "-4.0 ^ -3.0";	//테스트 문자열
	cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;
	expression = "-4.0 ^ 3.0";	//테스트 문자열
	cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;
	expression = "4.0 ^ (-3.0)";	//테스트 문자열
	cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;
	expression = "(-4.0) ^ (-3.0)";	//테스트 문자열
	cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;
	expression = "(-4.0) ^ 3.0";	//테스트 문자열
	cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;
	expression = "1.234%3";	//테스트 문자열
	cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;
	expression = "-1.234%3";	//테스트 문자열
	cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;
	expression = "-1.234%-3";	//테스트 문자열
	cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;
	expression = "(-1.234)%3";	//테스트 문자열
	cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;
	expression = "(-1.234)%(-3)";	//테스트 문자열
	cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;
	expression = "-1.234%(-3)";	//테스트 문자열
	cout << expression << " = " << fixed << setprecision(2) << makeCalulatable(expression) << endl;
	

}

class cNode
{
public:
	cNode();
	~cNode();

	int m_nData;
	cNode *m_pNext;

	void Insert(cNode *pNode);
	void Print();
	void Delete(int n, cNode **ppThis);
	void Reverse(cNode *pPrev);
	cNode *GetTail();
};

class cLinkedList
{
public:
	cLinkedList();
	~cLinkedList();

private:
	cNode* m_pHead;

public:
	void Insert(int n);
	void Delete(int n);
	void Print();
	void Reverse();
};

void alg_Q2018_06_19()
{
	ifstream FP;
	string command;

	cLinkedList MyList;	
}

//계산시킨다
double infixToPostfix(const string &expression)
{
	//숫자 저장용 스택
	Stack<double> numStack;

	//연산자 저장용 스택
	Stack<char> oprStack;

	//토큰 생성 : 토큰 = 각 글자들. 토큰 길이 = 숫자 + 연산자 더하기
	vector<string> tokens = split_them(expression);

	//토큰 검색
	for (unsigned i = 0; i < tokens.size(); i++)					// 토큰 처음부터 끝까지
	{
		// 이번 차례가 연산자라면, 앞에 나왔던 연산자를 먼저 처리한다. 
		if (tokens[i][0] == '+' || tokens[i][0] == '-')				// 더하기나 빼기이면 -> + - * - 전부 해결
		{
			if (i == 0 && tokens[i][0] == '-')	// 첫 문자가 - 이면
			{
				i++;
				numStack.push(atof(tokens[i].c_str()) * -1);
			}
			/*버그 수정
			2번째 숫자 이후 음수 처리 불가 수정
			*/
			else if (tokens[i][0] == '-' && i <= tokens.size() - 1)
			{
				i++;
				numStack.push(atof(tokens[i].c_str()) * -1);
			}
			else
			{
				while (!oprStack.isEmpty() &&							// 일단 비어있지 않고
					(oprStack.peek() == '+' || oprStack.peek() == '-'			//더하기거나 빼기거나
						|| oprStack.peek() == '*' || oprStack.peek() == '/'		//곱하기거나 나누기일 때마다
						|| oprStack.peek() == '^' || oprStack.peek() == '%'))	//지수이거나 나머지 연산일 때	// 추가
				{
					DoOperation(numStack, oprStack);					// 숫자 스택과 연산자 스택을 넘겨서 계산 시킨다.
				}
				oprStack.push(tokens[i][0]);									// 앞쪽 계산을 끝냈으니, 이번 차례 연산자를 넣어준다.
			}

		}
		else if (tokens[i][0] == '*' || tokens[i][0] == '/' || tokens[i][0] == '%')		// 곱하기 또는 빼기
		{
			if (i == 0 && tokens[i][0] == '-')	// 첫 문자가 - 이면
			{
				i++;
				numStack.push(atof(tokens[i].c_str()) * -1);
			}
			/*버그 수정
			2번째 숫자 이후 음수 처리 불가 수정
			*/
			else if (tokens[i][0] == '-' && i <= tokens.size() - 1)
			{
				i++;
				numStack.push(atof(tokens[i].c_str()) * -1);
			}
			else
			{
				while (!oprStack.isEmpty() &&							// 일단 비어있지 않고
					(oprStack.peek() == '*' || oprStack.peek() == '/'		// 곱하기거나 나누기일 때마다
						|| oprStack.peek() == '^' || oprStack.peek() == '%'))	//지수이거나 나머지 연산일 때
				{
					DoOperation(numStack, oprStack);
				}
				oprStack.push(tokens[i][0]);							// 앞쪽 계산을 끝냈으니, 이번 차례 연산자를 넣어준다.
			}
		}
		else if (tokens[i][0] == '^')		// 곱하기 또는 빼기
		{
			if (i == 0 && tokens[i][0] == '-')	// 첫 문자가 - 이면
			{
				i++;
				oprStack.push('+');			//-로 바꿨으니 연산자가 사라짐. 결과에 따라 +가 될 수 있으므로 + 연산자를 넣어줌
				numStack.push(atof(tokens[i].c_str()) * -1);
			}
			else
			{
				while (!oprStack.isEmpty() &&							// 일단 비어있지 않고
					(oprStack.peek() == '*' || oprStack.peek() == '/'		// 곱하기거나 나누기일 때마다
						|| oprStack.peek() == '^' || oprStack.peek() == '%'))	//지수이거나 나머지 연산일 때
				{
					DoOperation(numStack, oprStack);
				}
				oprStack.push(tokens[i][0]);							// 앞쪽 계산을 끝냈으니, 이번 차례 연산자를 넣어준다.
			}
		}
		else if (tokens[i][0] == '(')								// 여는 괄호면!!!!
		{
			//다음에 음수가 오는 지 확인 및 처리
			if (tokens[i + 1][0] == '-')
			{
				oprStack.push('(');
				i += 2;
				numStack.push(atof(tokens[i].c_str()) * -1);
			}
			else
				oprStack.push('(');							// 연산자 스택에 ( 넣는다. ) 나왔을 때 중단점 확인을 위해서.
		}
		else if (tokens[i][0] == ')')								// 닫는 괄호면
		{
			while (oprStack.peek() != '(')							// (가 나올 때 까지
			{
				DoOperation(numStack, oprStack);					//계산 ㄱㄱ
			}														// 이제 oprStack의 마지막 요소는 (가 되었다.
			oprStack.pop();											//여는 괄호를 뺀다.
		}
		else if (tokens[i][0] == '.')						// 소수점 처리
		{
			int head_num = numStack.pop();	// 먼저 들어갔던 소수점 앞 숫자를 꺼내서 임시 저장
											//cout << "pop된 head_num : " << head_num << endl;		// 테스트~

			i++;	// 다음 인덱스로 넘긴다.
			double tmp = atof(tokens[i].c_str());		//소수 이후 숫자를 tmp에 넣는다.	
														//cout << "tmp : " << tmp << endl;	// 테스트
														//cout << "tmp / pow(10, tokens[i].size()) : " << tmp / pow(10, tokens[i].size()) << endl;	// 테스트

			tmp /= pow(10, tokens[i].size());	// 숫자 길이 만큼 소수점으로 만들어준다.
			if (head_num >= 0)
				numStack.push(head_num + tmp);	//소수점 앞쪽이 양수면 더해주고
			else
				numStack.push(head_num - tmp);	//소수점 앞쪽이 음수면 빼준다.

												//테스트
												//cout << "(소수점 넣기 후) 지금 oprStack.peek() : " << oprStack.peek() << endl;
		}
		else														// 숫자
		{
			if (i + 1 < tokens.size())
			{
				if (isdigit(tokens[i][0]) && isdigit(tokens[i + 1][0]))		//숫자만 2개 연속으로 있다면
				{
					numStack.push(atof(tokens[i].c_str()));					//숫자처럼 생긴 문자를 c-string 스타일의 숫자로 만들어서 숫자 스택에 넣는다.
					i++;
					/*버그 수정
					오른쪽 계산 결과가 음수 * 음수 = 양수 가 되어버리면 부호가 사라지는 문제 수정
					=> 오른쪽이 될 숫자가 양수이면, 음수 계산 후 양수가 되어버렸을 수 있으므로 +를 더해준다.
					++는 +와 동일.+-는 -와 동일하므로 문제 없음
					*/
					if (atof(tokens[i].c_str()) > 0)
					{
						oprStack.push('+');
						numStack.push(atof(tokens[i].c_str()));					//숫자처럼 생긴 문자를 c-string 스타일의 숫자로 만들어서 숫자 스택에 넣는다.
					}
					else
						numStack.push(atof(tokens[i].c_str()));					//숫자처럼 생긴 문자를 c-string 스타일의 숫자로 만들어서 숫자 스택에 넣는다.

				}
				else
					numStack.push(atof(tokens[i].c_str()));					//숫자처럼 생긴 문자를 c-string 스타일의 숫자로 만들어서 숫자 스택에 넣는다.			
			}
			else
				numStack.push(atof(tokens[i].c_str()));
		}
	}

	//마무리로 남아있는게 있다면 싹 해치운다.
	while (!oprStack.isEmpty())
	{
		DoOperation(numStack, oprStack);
	}

	// 연산자는 없는데, 숫자만 2개 남은 경우가 있다면 두 수를 +시켜준다. 
	// (오른쪽 계산 결과 - 부호가 사라지고 양수가 될 경우, 연산자 증발 현상 발생)
	// 이 때는 + 기호를 강제 삽입하여 연산시켜준다.
	if (oprStack.isEmpty() && numStack.getSize() > 1)
	{
		oprStack.push('+');
		DoOperation(numStack, oprStack);
	}

	return numStack.pop();											//숫자 스택에 들어있는 최종값 = 계산 결과를 리턴한다.

}

void p534_q12_16(Stack<double> &numStack, Stack<char> &oprStack)
{
	char op = oprStack.pop();	// 마지막에 들어간 게 연산자 -> 꺼내기
	double right = numStack.pop();	// 나중에 들어간게 오른쪽 숫자 -> 꺼내기
	double left = numStack.pop();	// 먼저 들어간게 왼쪽 숫자 -> 꺼내기

	//cout << "현재 계산 할 수식 : " << left << op << right << endl;	//테스트
	// 연산자에 따라서 숫자 스택 끝에 계산 결과를 넣는다. 
	// 어파치 숫자 끝에 2개 빠지고 그 계산 결과를 넣는 것이기 때문에 OK.
	if (op == '+')
	{
		numStack.push(left + right);
		//cout << " = " << left + right << endl;	// 테스트
	}
	else if (op == '-')
	{
		numStack.push(left - right);
		//cout << " = " << left - right << endl;	// 테스트
	}
	else if (op == '*')
	{
		numStack.push(left * right);
		//cout << " = " << left * right << endl;	// 테스트
	}
	else if (op == '/')
	{
		numStack.push(left / right);
		//cout << " = " << left / right << endl;	// 테스트
	}
	else if (op == '^')	//추가분
	{
		numStack.push(pow(left, right));
	}
	else if (op == '%')	//추가분
	{
		if (abs(left) < abs(right))
			numStack.push(left);
		else
		{
			if (left < 0)
			{
				while (abs(left) > abs(right))
				{
					left = left + abs(right);
				}
				numStack.push(left);
			}
			else
			{
				while (abs(left) > abs(right))
				{
					left = left - abs(right);
				}
				numStack.push(left);
			}

		}
	}
}

void p534_q12_18()
{
	string expression;
	cout << "수식을 후위 표기법으로 변환한 후, 계산 결과를 출력합니다." << endl;
	cout << "수식을 입력하세요. : ";
	getline(cin, expression);
	cout << expression << " = " << fixed << setprecision(2) << infixToPostfix(expression) << endl;
}

#define Q12_20_MAX_INPUT 10
template<typename T>
void shuffle_it(vector<T> &v)
{
	for (int i = 0; i < Q12_20_MAX_INPUT; i++)
	{
		T tmp;
		int x = rand() % Q12_20_MAX_INPUT;

		tmp = v[i];
		v[i] = v[x];
		v[x] = tmp;
	}
}

template<typename T>
void show_compare(vector<T> &before, vector<T> &after)
{
	cout << "idx\tBefore\tAfter" << endl;
	for (int i = 0; i < Q12_20_MAX_INPUT; i++)
	{
		cout << i << "\t" << before[i] << "\t" << after[i] << endl;
	}
}

void p536_q12_20()
{
	srand(time(0));

	vector<int> input;
	vector<int> output;

	for (int i = 0; i < Q12_20_MAX_INPUT; i++)
	{
		input.push_back(rand() % 100);
		output.push_back(input.at(i));
	}	

	shuffle_it(output);

	show_compare(input, output);
}

void p545()
{
	ofstream output;
	output.open("scores.txt");
	if (output.fail())
	{
		cout << "파일을 열 수 없습니다. \n프로그램을 종료합니다." << endl;
		return;
	}

	output << "John" << " " << "T" << " " << "Smith" << " " << 90 << endl;
	output << "Eric" << " " << "K" << " " << "Jones" << " " << 85 << endl;

	output.close();

	cout << "Done" << endl;	
}
void p546()
{
	ifstream input("scores.txt");

	if (input.fail())
	{
		cout << "파일이 존재하지 않습니다. \n프로그램을 종료합니다." << endl;
		return;
	}	

	string firstName;
	char mi;
	string lastName;
	int score;

	input >> firstName >> mi >> lastName >> score;
	cout << firstName << " " << mi << " " << lastName << " " << score << endl;

	input >> firstName >> mi >> lastName >> score;
	cout << firstName << " " << mi << " " << lastName << " " << score << endl;

	input.close();

	cout << "Done." << endl;
}
void p549()
{
	ifstream input("score.txt");

	if (input.fail())
	{
		cout << "파일이 존재하지 않습니다. \n프로그램을 종료합니다." << endl;
		return;
	}

	double sum = 0;
	double number = 0;

	while (input >> number)
	{
		cout << number << " ";
		sum += number;
	}

	input.close();

	cout << "\n합은 " << sum << "입니다." << endl;
}

void p550()
{
	string filename;
	cout << "파일 이름을 입력하세요. : ";
	cin >> filename;

	ifstream input(filename.c_str());

	if (input.fail())
		cout << "\"" << filename << "\"" << "파일이 존재하지 않습니다." << endl;
	else
		cout << "\"" << filename << "\"" << "파일을 찾았습니다." << endl;
}

void p552()
{
	ofstream output;

	output.open("formattedscores.txt");

	output << setw(6) << "John" << setw(2) << "T" << setw(6) << "Smith" << setw(4) << 90 << endl;
	output << setw(6) << "Erik" << setw(2) << "K" << setw(6) << "Jones" << setw(4) << 85 << endl;

	output.close();

	cout << "done" << endl;
}


#define q13_MAX_INPUT 100
void p575_q13_1()
{

	cout << "프로그래밍 실습 13-1" << endl;
	ofstream output;
	ifstream input;

	string filename;
	//filename = "Exercise13_1_test.txt";
	filename = "Exercise13_1_output.txt";

	input.open(filename);

	if (input.fail())
	{
		cout << "\"" << filename << "\"" << "파일이 존재하지 않습니다." << endl;
		cout << "프로그램을 종료합니다. " << endl;
		return;
	}
	else
	{
		input.open("Exercise13_1_output.txt");
		double nums;

		cout << "추가 전 : " << endl;
		while (input >> nums)
			cout << setw(5) << nums;
		input.close();

		output.open("Exercise13_1_output.txt", ios::app);

		for (int i = 0; i < q13_MAX_INPUT; i++)
		{
			if (i % 10+1 == 10)
				output << setw(5) << rand() % 550 + 1 + rand()%320 << endl;
			else
				output << setw(5) << rand() % 500 + 1;
		}		
		output.close();

		cout << "\n추가 후 : " << endl;
		input.open("Exercise13_1_output.txt");
		while (input >> nums)
			cout << setw(5) << nums;
		input.close();
	}

}
void p575_q13_4()
{
	cout << endl << "프로그래밍 실습 13-4" << endl;

	ofstream output;
	ifstream input;
	vector<double> numbers;

	int cnt = 0;
	string filename;
	//filename = "Exercise13_1_test.txt";
	filename = "Exercise13_1_output.txt";

	input.open(filename);

	if (input.fail())
	{
		cout << "\"" << filename << "\"" << "파일이 존재하지 않습니다." << endl;
		cout << "프로그램을 종료합니다. " << endl;
		return;
	}
	else
	{
		double tmp;
		while (!input.eof())
		{
			input >> tmp;
			//cout << tmp << endl;	// 확인용
			if (cnt < q13_MAX_INPUT)
			{
				numbers.push_back(tmp);			
	
				cnt++;
			}
			else
				break;
		}
		input.close();

		for (int i = 0; i < q13_MAX_INPUT-1; i++)
		{
			//cout << i << "회차" << endl;
			for (int j = i+1; j < q13_MAX_INPUT; j++)
			{
				
				if (numbers[i] > numbers[j])
				{
					//cout << numbers[i] << " < 교환 > " << numbers[j] << endl;	// 확인용
					SWAP_A_B(&numbers[i], &numbers[j], sizeof(double));
					//cout << "결과 : " << numbers[i] << ",  " << numbers[j] << endl;	// 확인용
				}				
			}
		}

		output.open("Exercise13_1_output_Q13_4.txt");

		if (output.fail())
		{
			cout << "Exercise13_1_output_Q13_4.txt 파일을 열지 못했습니다.\n프로그램을 종료합니다." << endl;
			return;
		}
		else
		{
			for (int i = 0; i < q13_MAX_INPUT; i++)
			{
				if (i % 10 + 1 == 10)
					output << setw(5) << numbers[i] << endl;
				else
					output << setw(5) << numbers[i] << " ";
			}
			output.close();
		}
	}

	cout << "Done!" << endl;
}

void p567()
{

}
void p553() 
{
	ifstream input("state.txt");

	if (input.fail())
	{
		cout << "File does not exist" << endl;
		cout << "Exit program" << endl;
		return;
	}

	string state;

	while (!input.eof())
	{
		getline(input, state, '#');
		cout << state << endl;
	}

	input.close();

	cout << "Done" << endl;

	return;
}

void p554() 
{
	cout << "Enter a source file name: ";
	string inputFilename;
	cin >> inputFilename;

	cout << "Enter a terget file name: ";
	string outputFilename;
	cin >> outputFilename;

	ifstream input(inputFilename.c_str());
	ofstream output(outputFilename.c_str());

	if (input.fail())
	{
		cout << inputFilename << " does not exits" << endl;
		cout << "Exit program" << endl;
		return;
	}

	char ch = input.get();
	while (!input.eof())
	{
		output.put(ch);
		ch = input.get();
	}

	input.close();
	output.close();

	cout << "\nCopy Done!" << endl;	
}


void p556()
{
	fstream inout;

	inout.open("city.txt", ios::out);

	inout << "Dallas" << " " << "Los Angeles" << " " << "Huston" << " ";

	inout.close();

	inout.open("city.txt", ios::out | ios::app);
	inout << "Savannah" << " " << "Austin" << " " << "Chicago";

	inout.close();

	string city;

	inout.open("city.txt", ios::in);
	while (!inout.eof())
	{
		inout >> city;
		cout << city << " ";
	}

	inout.close();
}

void showState(const fstream &stream)
{
	cout << "Stream status :" << endl;
	cout << "eof()" << stream.eof() << endl;
	cout << "fail()" << stream.fail() << endl;
	cout << "bad()" << stream.bad() << endl;
	cout << "good()" << stream.good() << endl;
}
void p558()
{
	fstream inout;

	inout.open("temp.txt", ios::out);
	inout << "Dallas";
	cout << "Normal operation (no errors)" << endl;

	showState(inout);
	inout.close();

	inout.open("temp.txt", ios::in);
	string city;
	inout >> city;
	cout << "end of File (no errors)" << endl;
	showState(inout);

	inout.close();

	inout >> city;
	cout << "Bad operation (errors) " << endl;
	showState(inout);


}


void p561_1()
{
	fstream binaryio("city.dat", ios::out | ios::binary);
	string s = "Atlanta";
	binaryio.write(s.c_str(), s.size());
	binaryio.close();

	cout << "Done" << endl;
}

void p561_2()
{
	const int SIZE = 5;

	fstream binaryio;
	binaryio.open("array.dat", ios::out | ios::binary);
	double array[SIZE] = { 3.4, 1.2, 2.5, 5.66, 6.9 };
	binaryio.write(reinterpret_cast<char*>(&array), sizeof(array));
	binaryio.close();

	binaryio.open("array.dat", ios::in | ios::binary);
	double result[SIZE];
	binaryio.read(reinterpret_cast<char*>(&result), sizeof(result));
	binaryio.close();

	for (int i = 0; i < SIZE; i++)
		cout << result[i] << " ";
}


void p562()
{
	cout << "p562 " << endl;
	fstream binaryio("city.dat", ios::in | ios::binary);

	char s[10];
	binaryio.read(s, 10);
	cout << "Number of chars read: " << binaryio.gcount() << endl;
	s[binaryio.gcount()] = '\0';
	cout << s << endl;

	binaryio.close();

}


void displayStudent(const Student &student)
{
	cout << student.getFirstName() << " ";
	cout << student.getMi() << " ";
	cout << student.getLastName() << " ";
	cout << student.getScore() << endl;
}

void p566()
{
	fstream binaryio;
	binaryio.open("student.dat", ios::out | ios::binary);

	Student student1("John", 'T', "Smith", 90);
	Student student2("Eric", 'K', "Jones", 85);
	Student student3("Susan", 'T', "King", 67);
	Student student4("Kim", 'K', "Peterson", 95);


	binaryio.write(reinterpret_cast<char*> (&student1), sizeof(Student));
	binaryio.write(reinterpret_cast<char*> (&student2), sizeof(Student));
	binaryio.write(reinterpret_cast<char*> (&student3), sizeof(Student));
	binaryio.write(reinterpret_cast<char*> (&student4), sizeof(Student));

	binaryio.close();

	binaryio.open("student.dat", ios::in | ios::binary);

	Student studentNew;

	binaryio.read(reinterpret_cast<char*> (&studentNew), sizeof(Student));
	displayStudent(studentNew);

	binaryio.read(reinterpret_cast<char*>(&studentNew), sizeof(Student));
	displayStudent(studentNew);

	binaryio.close();
}

void p570()
{
	fstream binaryio;
	binaryio.open("student.dat", ios::out | ios::binary);

	Student student1("FirstName1", 'A', "LastName1", 10);
	Student student2("FirstName2", 'B', "LastName2", 20);
	Student student3("FirstName3", 'C', "LastName3", 30);
	Student student4("FirstName4", 'D', "LastName4", 40);
	Student student5("FirstName5", 'E', "LastName5", 50);
	Student student6("FirstName6", 'F', "LastName6", 60);
	Student student7("FirstName7", 'G', "LastName7", 70);
	Student student8("FirstName8", 'H', "LastName8", 80);
	Student student9("FirstName9", 'I', "LastName9", 90);
	Student student10("FirstName10", 'J', "LastName10", 100);

	binaryio.write(reinterpret_cast<char*>(&student1), sizeof(Student));
	binaryio.write(reinterpret_cast<char*>(&student2), sizeof(Student));
	binaryio.write(reinterpret_cast<char*>(&student3), sizeof(Student));
	binaryio.write(reinterpret_cast<char*>(&student4), sizeof(Student));
	binaryio.write(reinterpret_cast<char*>(&student5), sizeof(Student));
	binaryio.write(reinterpret_cast<char*>(&student6), sizeof(Student));
	binaryio.write(reinterpret_cast<char*>(&student7), sizeof(Student));
	binaryio.write(reinterpret_cast<char*>(&student8), sizeof(Student));
	binaryio.write(reinterpret_cast<char*>(&student9), sizeof(Student));
	binaryio.write(reinterpret_cast<char*>(&student10), sizeof(Student));


	binaryio.close();

	binaryio.open("student.dat", ios::in | ios::binary);

	Student studentNew;
	binaryio.seekg(2 * sizeof(Student));

	cout << "Current position is " << binaryio.tellg() << endl;

	binaryio.read(reinterpret_cast<char*>(&studentNew), sizeof(Student));

	displayStudent(studentNew);

	cout << "Current position is " << binaryio.tellg() << endl;

	binaryio.close();
}

void p572()
{
	fstream binaryio;

	binaryio.open("student2.dat", ios::in | ios::out | ios::binary);

	Student student1;
	binaryio.seekg(sizeof(Student));
	binaryio.read(reinterpret_cast<char*>(&student1), sizeof(Student));
	displayStudent(student1);

	student1.setLastName("Yao");
	binaryio.seekp(sizeof(Student));
	binaryio.write(reinterpret_cast<char*>(&student1), sizeof(Student));
	displayStudent(student1);

	Student student2;
	binaryio.seekg(sizeof(Student));
	binaryio.read(reinterpret_cast<char*>(&student2), sizeof(Student));
	displayStudent(student2);

	binaryio.close();

}

void p577_q13_17()
{
	// 원본 파일 입력 받는다
	// 사이즈를 입력받는다.
	// 원본 파일을 사이즈 까지 읽어들인다
	// 사이즈 꽉 차면 다음으로 넘어간다.

	ifstream sourceFile;
	ofstream destFile;


	cout << "원본 파일명을 입력하세요. : ";
	string fileName;
	cin >> fileName;
	string fileName_dest = fileName;

	cout << "파일을 나눌 크기를 byte 단위로 입력하세요. : ";
	int split_size;
	cin >> split_size;

	//원본, 사이즈 구하기
	sourceFile.open(fileName, ios::in | ios::binary);
	//포인터를 끝으로 옮기고
	
	//파일 크기 계산
	unsigned long int cur_pos = sourceFile.tellg();
	sourceFile.seekg(0, ios::end);
	unsigned long int size_src = sourceFile.tellg();
	sourceFile.seekg(0, ios::beg);	
	
	while (cur_pos <= size_src)
	{
		fileName_dest = fileName;
		fileName_dest.append("_");
		fileName_dest.append(to_string(cur_pos / split_size));

		destFile.open(fileName_dest, ios::out | ios::app | ios::binary);				

		if ((cur_pos / split_size) > sizeof(long int))
		{
			long int tmp;
			sourceFile.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
			cur_pos = sourceFile.tellg();
			destFile.write(reinterpret_cast<char*>(&tmp), sizeof(tmp));
		}
		else if ((cur_pos / split_size) > sizeof(int))
		{
			int tmp;
			sourceFile.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
			cur_pos = sourceFile.tellg();
			destFile.write(reinterpret_cast<char*>(&tmp), sizeof(tmp));
		}
		else
		{
			char tmp;
			sourceFile.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
			cur_pos = sourceFile.tellg();
			destFile.write(reinterpret_cast<char*>(&tmp), sizeof(tmp));
		}

		destFile.close();
	}
	
	
	cout << "done" << endl;

	

}
void p577_q13_18()
{	}

void Insertion(int a[], int n)
{
	int i, j;
	for (i = 1; i < n; i++)
	{
		int tmp = a[i];
		for (j = i; j > 0 && a[j - 1] > tmp; j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

void alg_p214()
{
	int i, nx;
	int *x;
	cout << "단순 삽입 정렬"<< endl;

	cout << "요소 개수 : ";
	cin >> nx;

	x = (int*)calloc(nx, sizeof(int));

	for (i = 0; i < nx; i++)
	{
		cout << "x[" << i << "] : ";
		cin >> x[i];
	}
	
	StopWatch timer;
	timer.start();
	for (int nn = 0; nn < 1000000; nn++)
		Insertion(x, nx);

	timer.stop();	
	cout << "걸린 시간 : " << timer.getElapsedTime() << endl;
	cout << "오름차순으로 정렬 됨" << endl;

	for (i = 0; i < nx; i++)
		cout << "x[" << i << "] = " << x[i] << endl;

	free(x);
}

void Insertion_list(Member m, int n)
{
	
}
void alg_p214_listed()
{
	
}
int main()
{	

	//↓↓↓↓↓ 2018-06-26 ↓↓↓↓↓
	//p553();	// 완료
	//p554();	// 완료
	//p556();	// 완료
	//p558();	// 완료
	//p561_1();	// 완료
	//p561_2();	// 완료
	//p562();	// 완료



	//p577_q13_17();	// 이상하게 되었다.
	//p577_q13_18();

	//p566();	// lastName이 이상하게 나온다.
	//p570();// lastName이 이상하게 나온다.
	//p572();

	//alg_p214();
	alg_p214_listed();



	//↓↓↓↓↓ 2018-06-22 ↓↓↓↓↓
	//p536_q12_20();	// 완료
	//p545();	// 완료
	//p546();	// 완료
	//p549();	// 완료
	//p550();	// 완료
	//p552();	// 완료
	//p575_q13_1();	// 완료
	//p575_q13_4();	// 완료

	//↓↓↓↓↓ 2018-06-21 ↓↓↓↓↓
	//calculator();	// 개선 완료 -> 할 것 아직 있음.
	//p534_q12_18();

	//↓↓↓↓↓ 2018-06-20 ↓↓↓↓↓
	//p503();	// 완료
	//p507();	// 완료
	//testgenericstack();	// 완료
	//testgenericstackwithtemplatefunction();	// 완료
	//p521();	// 완료
	//p211_Q5_1();	// 완료
	//p525();	// 완료


	//calculator();	// 완료?
	

	//미완료
	/*
	gichul_20180601();
	
	p280_Q6_21();
	p280_Q6_22();
	p281_Q6_23();
	p281_Q6_24();
	alg_p192();// 8명의 퀸! < 모르겠당.
	//p534_Q12_16();
	//p534_Q12_18();
	//alg_Q2018_06_19();

	*/
	
	//↓↓↓↓↓ 2018-06-19 ↓↓↓↓↓
	//p469_1();	// 완료
	//p469_2();	// 완료
	//p473();	// 완료
	//p481();	// 완료
	//p487();	// 완료
	//p494_q11_3();	//완료
	//p496_q11_8();	// 완료
	//p496_q11_9();	// 완료
	//alg_341();	// 완료


	//↓↓↓↓↓ 2018-06-15 ↓↓↓↓↓
	/*
	p413();	// 완료
	p422_p424();	// 완료
	p438();	//완료
	p443_Q10_1();	//완료
	p443_Q10_2();	//완료
	p445_Q10_15();	// 완료
	*/
	
	//↓↓↓↓↓ 2018-06-14 ↓↓↓↓↓	
	/*
	alg_p178_Q5_3();	// 완료
	p401_Q9_4();	// 완료
	p402_Q9_7();	// 완료
	p400_Q9_1();	// 완료
	p395();	// 완료
	p376();	// 완료
	p374();	// 완료
	*/

	//↓↓↓↓↓ 2018-06-12 ↓↓↓↓↓	
	/*
	p360_Q8_15();	// 완료
	p360_Q8_21();	// 완료
	p356_Q8_5();	// 완료
	p358_Q8_9();	// 완료
	p328_Q7_15();	// 완료 	
	p329_Q7_17();	// 완료
	p335_Q7_38();	// 완료
	*/

	//↓↓↓↓↓ 2018-06-11 ↓↓↓↓↓
	/*
	Q3_25();	// 완료
	Q3_26();	// 완료
	Q3_29();	// 완료
	alg_p109();	//완료
	alg_p115();	//완료
	p278_Q6_16();	//완료
	p279_Q6_20();	//완료
	p220_q5_49();	// 완료
	p220_q5_54();	// 완료
	p220_q5_57();	// 완료
	p218_Q5_35();	// 완료
	p218_Q5_40();	// 완료
	p218_Q5_43();	// 완료
	alg_p103();	// 완료
	alg_p85_mod();	// 완료
	Q3_19();	//완료
	Q3_20();	//완료
	Q3_22();	//완료
	p149();	//완료
	p150();	//완료
	p158();	//완료
	p159();	//완료
	p161_Q4_1();	// 완료
	p162_Q4_4();		// 완료
	p164_Q4_16();		// 완료
	p164_q4_23();		// 완료
	p173_5_2_1();		// 완료
	p206();			// 완료	
	p213_5_7();		// 완료 sin / cos  같은 함수는 안에 들어가는 각도 값이 라디안 값. 각도 * (PI / 180) = 라디안 각도
	p213_5_8();		// 완료
	p214_5_19();		// 완료
	p214_5_21();	//완료
	p286_Q6_43();	// 완료
	p282_6_35();	// 완료
	p282_6_30();	// 완료
	p327_Q7_3();	// 완료
	p327_Q7_9to10();	// 완료
	p298_7_3();	// 완료
	*/

	return 0;
}

cLinkedList::cLinkedList()
{
}

cLinkedList::~cLinkedList()
{
}

void cLinkedList::Insert(int n)
{
}

void cLinkedList::Delete(int n)
{
}

void cLinkedList::Print()
{
}

void cLinkedList::Reverse()
{
}

cNode::cNode()
{
}

cNode::~cNode()
{
}

void cNode::Insert(cNode * pNode)
{
}

void cNode::Print()
{
}

void cNode::Delete(int n, cNode ** ppThis)
{
}

void cNode::Reverse(cNode * pPrev)
{
}

cNode * cNode::GetTail()
{
	return nullptr;
}
