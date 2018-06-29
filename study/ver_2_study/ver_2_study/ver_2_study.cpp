// ver_2_study.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
// 6월 29일 새로 시작

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include "Employee.h"
#include "Faculty.h"
#include "Person.h"
#include "Student.h"
#include "Staff.h"
#include "MyPoint.h"
#include "MyPoint3D.h"
using namespace std;

void p638() {}
void p640() {}
void p656() {}

int int_cmp(const int *a, const int *b)
{
	if (*a < *b)
		return -1;
	else if (*a > *b)
		return 1;
	else
		return 0;
}

typedef struct {
	char name[10];
	int height;
	int weight;
}alg_p244_person;

int npcmp(const alg_p244_person *x, const alg_p244_person *y)
{
	return strcmp(x->name, y->name);
}

int hpcmp(const alg_p244_person *x, const alg_p244_person *y)
{
	return x->height < y->height ? -1 :
		x->height > y->height ? 1 : 0;
}

int wpcmp(const alg_p244_person *x, const alg_p244_person *y)
{
	return x->weight < y->weight ? 1 :
		x->weight > y->weight ? -1 : 0;
}

void print_person(const alg_p244_person x[], int no)
{
	int i = 0;
	for (i = 0; i < no; i++)
		cout << setw(10) << x[i].name << " " << x[i].height << "Cm " << x[i].weight << "Kg" << endl;
}

void alg_p244()
{
	alg_p244_person x[] = {
		{"sunmi", 170, 52},
	{"yoobin", 180, 70},
	{"sohee", 172, 63},
	{"jina", 165, 50},
	};
	

	int nx = sizeof(x) / sizeof(x[0]);

	cout << "정렬 전" << endl;
	print_person(x, nx);

	qsort(x, nx, sizeof(alg_p244_person), (int(*)(const void *, const void *))npcmp);
	cout << "이름 오름차순 정렬 후" << endl;
	print_person(x, nx);


	qsort(x, nx, sizeof(alg_p244_person), (int(*)(const void *, const void *))hpcmp);
	cout << "키 오름차순 정렬 후" << endl;
	print_person(x, nx);


	qsort(x, nx, sizeof(alg_p244_person), (int(*)(const void *, const void *))wpcmp);
	cout << "몸무게 오름차순 정렬 후" << endl;
	print_person(x, nx);

	
}

void alg_p243()
{
	int i, nx;
	int *x;
	cout << "qsort에 의한 정렬" << endl;
	cout << "요소 개수 : ";
	cin >> nx;

	x = (int*)calloc(nx, sizeof(int));

	for (i = 0; i < nx; i++)
	{
		cout << "x[" << i << "] : ";
		cin >> x[i];
	}

	qsort(x, nx, sizeof(int), (int(*)(const void*, const void*))int_cmp);

	cout << "오름차순으로 정렬됨" << endl;

	for (i = 0; i < nx; i++)
		cout << "x[" << i << "] = " << x[i] << endl;
	free(x);
}

void p661_q15_2()
{

	Student stu;
	Employee emp;
	Faculty fac;
	Staff stf;

	cout << stu.toString().c_str() << endl;
	cout << emp.toString().c_str() << endl;
	cout << fac.toString().c_str() << endl;
	cout << stf.toString().c_str() << endl;
}

void p661_q15_3()
{
	MyPoint3D basic;
	cout << "기본 생성자 : 점 P(" << basic.getX() << ", " << basic.getY() << ", " << basic.getZ() << ")" << endl;
	

	MyPoint3D point3D;
	double tmp;
	cout << "세 점의 좌표를 입력하세요. : ";
	cin >> tmp;
	point3D.setX(tmp);
	cin >> tmp;
	point3D.setY(tmp);
	cin >> tmp;
	point3D.setZ(tmp);


	MyPoint3D target3Dpoint;
	cout << "거리를 잴 세 점의 좌표를 입력하세요. : ";
	cin >> tmp;
	target3Dpoint.setX(tmp);
	cin >> tmp;
	target3Dpoint.setY(tmp);
	cin >> tmp;
	target3Dpoint.setZ(tmp);

	cout << "점 P1(" << point3D.getX() << ", " << point3D.getY() << ", " << point3D.getZ() << ")" << endl;
	cout << "점 P2(" << target3Dpoint.getX() << ", " << target3Dpoint.getY() << ", " << target3Dpoint.getZ() << ")" << endl;
	cout << "두 점 P1(" << point3D.getX() << ", " << point3D.getY() << ", " << point3D.getZ() 
		<< ") 과 점 P2(" << target3Dpoint.getX() << ", " << target3Dpoint.getY() << ", " << target3Dpoint.getZ() << ")" 
		<< "의 거리는 " << point3D.getDistance(target3Dpoint) << "입니다." << endl;

}

int main()
{
	//alg_p243();
	//alg_p244();
	//p661_q15_2();	// 완료
	//p661_q15_3();	// 완료

	//↓↓↓↓↓ 2018-06-29 ↓↓↓↓↓
	/*p638();
	p640();
	p656();*/


    return 0;
}

