// dx_study.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "cVector3.h"
#include "cMatrix.h"


using namespace std;


void EpsilonTest()
{
	float oneFloat = 1.0f;
	float testFloat = 0.0f;

	for (int i = 0; i < 10; i++)
	{
		testFloat += 0.1f;
	}

	printf(" %.8f    %.8f    =>    %s \n", oneFloat, testFloat, oneFloat == testFloat ? "TRUE" : "FALSE");
}

int main()
{
	//Vector 연산
	/*cVector3 a(1, 2, 3);
	cVector3 b(1, -1, 3);
	cVector3 c(1, 2, 1);
	cVector3 tmp;
	float k = 4.0f;

	printf("vector a : %.3f, %.3f, %.3f\n", a.x, a.y, a.z);
	printf("vector b : %.3f, %.3f, %.3f\n", b.x, b.y, b.z);
	printf("vector c : %.3f, %.3f, %.3f\n", c.x, c.y, c.z);
	printf("float k : %.3f\n\n", k);

	printf("does a equal to b ? ==> %s\n", a == b ? "TRUE" : "FALSE");
	printf("does a not equal to b ? ==>  %s\n", a != b ? "TRUE" : "FALSE");


	tmp = a + b;
	printf("a + b = %.3f, %.3f, %.3f\n", tmp.x, tmp.y, tmp.z);

	tmp = a - b;
	printf("a - b = %.3f, %.3f, %.3f\n", tmp.x, tmp.y, tmp.z);
		
	tmp = a * k;
	printf("a * k = %.3f, %.3f, %.3f\n", tmp.x, tmp.y, tmp.z);

	tmp = a / k;
	printf("a / k = %.3f, %.3f, %.3f\n", tmp.x, tmp.y, tmp.z);

	
	printf("a Dot b = %.3f\n", a.Dot(a, b));
	printf("a Dot c = %.3f\n", a.Dot(a, c));
	printf("b Dot c = %.3f\n", b.Dot(b, c));

	tmp = a.Normalize();
	printf("Normalized a : %.3f, %.3f, %.3f\n", tmp.x, tmp.y, tmp.z);

	tmp = a.Cross(a, c);
	printf("a Cross c = %.3f, %.3f, %.3f\n", tmp.x, tmp.y, tmp.z);*/
  
	// Matrix 연산
	/*
	
	+ , -, *, scalar*, Inverse Matrix
	check Identity matrix

	*/
	int nMatDimension = 0;
	std::cout << "행렬의 차수를 입력하세요. : ";
	std::cin >> nMatDimension;

	cMatrix mat1(nMatDimension);
	mat1 = cMatrix::Identity(nMatDimension);

	cMatrix matrix_1(nMatDimension);
	cMatrix matrix_2(nMatDimension);

	int tmp[4][4] = {
		{1,3,4,0}, {6,7,8,5},	{98,7,6,9}, {54,3,2,5}
	};

	for (int i = 0; i < nMatDimension; i++)
	{

		for (int j = 0; j < nMatDimension; i++)
		{

		}
	}
	printf("Matrix #1\n");
	matrix_1.Print();

	printf("Matrix #2\n");
	matrix_2.Print();

	printf("Transpose Matrix #1   ==>\n");
	matrix_1.Transpose();
	matrix_1.Print();
	printf("Identity   ==>\n");
	cMatrix x(nMatDimension);
	x = cMatrix::Identity(matrix_1.Dimension());
	x.Print();

	printf("minor matrix of Matrix #1(2,1)   ==>\n");
	cMatrix tmp2(matrix_1.Dimension() - 1);
	tmp2 = matrix_1.Minor(2, 1);
	tmp2.Print();

	return 0;
}

