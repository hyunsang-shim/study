// algorithm.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iomanip>

using namespace std;



void merge(const int a[], int na, const int b[], int nb, int c[])
{
	int pa = 0;
	int pb = 0;
	int pc = 0;


	while (pa < na && pb << nb)
		c[pc++] = (a[pa] <= b[pb]) ? a[pa++] : b[pb++];

	while (pa < na)
		c[pc++] = a[pa++];

	while (pb < nb)
		c[pc++] = b[pb++];
}


int main()
{
	int i, na, nb;
	int *a, *b, *c;
	cout << "a의 요소 개수 : ";
	cin >> na;
	cout << "b의 요소 개수 : ";
	cin >> nb;

	a = (int*)calloc(na, sizeof(int));
	b = (int*)calloc(nb, sizeof(int));
	c = (int*)calloc(na + nb, sizeof(int));

	cout << "a[0] : ";
	cin >> a[0];

	for (i = 1; i < na; i++)
	{
		do {
			cout << "a[" << i << "] : ";
			cin >> a[i];
		} while (a[i] < a[i - 1]);
	}

	cout << "b[0] : ";
	cin >> b[0];

	for (i = 1; i < nb; i++)
	{
		do {
			cout << "b[" << i << "] : ";
			cin >> b[i];
		} while (b[i] < b[i - 1]);
	}

	merge(a, na, b, nb, c);
	cout << "배열 a와 b를 병합하여 배열 c에 저장." << endl;

	for (i = 0; i < na + nb; i++)
		cout << "c[" << setw(2) << i << "] = " << setw(2) << c[i];

	free(a);
	free(b);
	free(c);

    return 0;
}

