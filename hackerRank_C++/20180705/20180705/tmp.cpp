////#include "stdafx.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//
//
//int main()
//{
//
//	int lexicographic_sort(const char* a, const char* b) {
//		return strcmp(a, b);
//
//	}
//
//	int lexicographic_sort_reverse(const char* a, const char* b) {
//		return strcmp(b, a);
//	}
//
//	int sort_by_number_of_distinct_characters(const char* a, const char* b) {
//		int cnt_a;
//		int cnt_b;
//
//		for (int i = 0, j = strlen(a) - 1; i < strlen(a), j >= 0; i++, j--)
//		{
//			if (a[i] != a[j])
//				cnt_a++;
//		}
//
//		for (int i = 0, j = strlen(b) - 1; i < strlen(b), j >= 0; i++, j--)
//		{
//			if (b[i] != b[j])
//				cnt_b++;
//		}
//
//		if (cnt_a > cnt_b || ((cnt_a == cnt_b) && (lexicographic_sort(a, b))))
//			return -1;
//		else if (cnt_a == cnt_b)
//			return 0;
//		else
//			return 1;
//	}
//
//	int sort_by_length(const char* a, const char* b) {
//
//		if (strlen(a) < strlen(b))
//			return 1;
//		else if (strlen(a) == strlen(b))
//		{
//			if (a[0] < b[0])
//				return 0;
//			else if (a[0] > b[0])
//				return 2;
//			elsr if (a[0] == b[0])
//		}
//
//		else
//			return -1;
//	}
//
//	void string_sort(char** arr, const int len, int(*cmp_func)(const char* a, const char* b)) {
//
//		if (((*cmp_func)(a, b)))
//			for (int i = 0, j = i + 1; i <= len - 2, j < len; i++, j++)
//				if (((*cmp_func)(arr[i], arr[j])) < 0)
//				{
//					char *tmp;
//					tmp = (char*)malloc(strlen(arr[i]) * sizeof(char));
//
//					strcpy(tmp, arr[i]);
//					strcpy(arr[i], arr[j]);
//					strcpy(arr[j], tmp);
//				}
//
//	}
//
//}