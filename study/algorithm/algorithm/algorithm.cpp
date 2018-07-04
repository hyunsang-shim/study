// algorithm.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iomanip>

using namespace std;


static int *buff;
void __merge(int a[], int left, int right)
{
	if (left < right)		// 계속 반으로 쪼개기 때문에, 2개일 때 더이상 쪼개지 않는다.
	{
		int center = (left + right) / 2;	// 중간 = (왼쪽 + 오른쪽) /2
		int pos = 0;		// 위치값, 전체 중 위치
		int total_pl;	// 반복문 전용, 전체 중 왼쪽부터 카운트 되어 올라간다. (right까지)
		int cnt = 0;	// 반복문 전용, 카운트
		int cur_pl = left;	// 반복문 전용 (현재 재귀에서의 왼쪽끝)

		__merge(a, left, center);		// 쪼개진 것을 왼쪽으로 가면서 쪼개서 정렬하고
		__merge(a, center + 1, right);	// 오른쪽으로 가면서 정렬한다. 조각조각 분기분기 

		// 위의 재귀 호출 반복이 끝나면
		for (total_pl = left; total_pl <= center; total_pl++)	// 왼쪽값 부터 중앙까지
			buff[total_pl++] = a[pos];	// 버퍼에 넣는다. (2개짜리 -> 4개짜리 -> 8개짜리 16개짜리 이 순서대로 실행됨

		while (pos <= right && cnt < total_pl)	// 왼쪽 끝난 위치부터 오른쪽 끝까지 이고 (&&) 0부터 왼쪽 개수 -1 까지
			a[cur_pl++] = (buff[cnt] <= a[total_pl]) ? buff[cnt++] : a[total_pl++];	// 버퍼[j]에 있는게 a[i]에 있는 것보다 작거나 같으면 buff[j]값을, 아니면 a[i]값을 a[k]에 넣는다.

		while (cnt < total_pl)	// j가 포지션 값 보다 작으면
			a[cur_pl++] = buff[cnt++];	//a[k]에 버퍼[j] 값을 넣는다. (j++, k++)
	}
}


void merge2(int a[], int left, int right, int tmp[])
{
	cout << "left : " << left << ", right : " << right << endl;
	if (left < right)
	{
		int center = (left + right) / 2;
		int pl = left;
		int cnt = 0;
		
		
		merge2(a, left, center, tmp);
		merge2(a, center + 1, right, tmp);
	

		for (pl = left; pl <= center; pl++)
			tmp[pl++] = a[pl];

		
	}

	for (int x = 0; x < right; x++)
		cout << "a[x] : " << a[x] << endl;
}

void merge(const int a[], int na, const int b[], int nb, int c[])
{
	int pa = 0;
	int pb = 0;
	int pc = 0;

	while (pa < na && pb < nb)
		c[pc++] = (a[pa] <= b[pb]) ? a[pa++] : b[pb++];

	//a[]가 b 보다 많을 경우
	while (pa < na)
		c[pc++] = a[pa++];

	//b[]가 a[]보다 많을 경우.
	while (pb < nb)
		c[pc++] = b[pb++];
}

void Merge_Sort()
{
	//일반 merge sort
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
		cout << "c[" << setw(2) << i << "] = " << setw(2) << c[i] << endl;

	free(a);
	free(b);
	free(c);
}


void Heap_sort_up(int a[], int n)
{
}

int *result;
int* Heap_sort_down(int a[], int n)
{
	result = (int*)calloc(n, sizeof(int));

		for (int i = (n - 1) / 2; i >=0; i--)
		{
			static int top = (i - 1) / 2;
			static int left;
			if (i * 2 + 2 >= n)
				left = 0;
			else
				left = i * 2 + 2;

			static int right;		
			if (i * 2 + 2 >= n)
				right = n-1;
			else
				right = i * 2 + 2;

			cout << i << "회차" << "\t";
			cout << "top : " << a[top] << "\t" << "left : " << a[left] << "\t" << a[right] << endl;
			if ((left == 0 ? 0 : a[top] < a[left]) || (right == 0 ? 0 : a[top] < a[right]))
			{
				if (a[left] < a[right])
				{
					int temp = a[right];
					a[right] = a[top];
					a[top] = temp;
					temp = right;
					right = top;
					top = temp;
				}
				else
				{
					int temp = a[left];
					a[left] = a[top];
					a[top] = temp;
					temp = left;
					left = top;
					top = temp;
				}
			}
			
			result[n - (i + 1)] = a[top];
		
	}
	return result;
}


void Heap_sort()
{

	cout << "힙 정렬 (오름차순)" << endl;

	int nx = 0;
	cout << "요소 개수 : ";
	cin >> nx;
	
	int *arr;

	arr = new int [nx];

	for (int i = 0; i < nx; i++)
	{
		cout << "x[" << i << "] : ";
		cin >> arr[i];
	}

	arr = Heap_sort_down(arr, nx);

	cout << "오름차순으로 정렬" << endl;

	for (int i = 0; i < nx; i++)
	{
		cout << "x["<< i << "] : " << arr[i] << endl;
	}
}

int main()
{
	
	//Merge_Sort();
	Heap_sort();	


    return 0;
}

