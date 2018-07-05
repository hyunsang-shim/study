//#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()
{
	char a[5] = "asdf";
	char b[5] = "dsfr";
	char *tmp;

	tmp = (char*)malloc(sizeof(char) * (strlen(a)+1));
	printf("%d", sizeof(tmp) / sizeof(char));


	//strcpy_s(tmp, strlen(a), a);

	//printf("%s", a);

	return 0;

}