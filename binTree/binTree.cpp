// binTree.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>

#include "cBST.h"
#include "cNode.h"

int main()
{
	cBST bst;

	bst.Insert(20, 100);
	bst.Insert(15, 101);
	bst.Insert(11, 102);
	bst.Insert(29, 103);
	bst.Insert(13, 104);
	bst.Insert(17, 105);
	bst.Insert(26, 106);
	bst.Insert(30, 107);
	bst.Insert(12, 108);
	bst.Insert(11, 109);

	printf("printing Tree Data....\n");
	bst.Print();


	// 정렬 순서 : Key값 기준
	// 프린트 할 때는 데이터 값을 사용?
	printf("Finding Key 26....\n");
	if (bst.Find(26))
		printf("Key 26 Found! : The Data is = %d\n", bst.Find(26)->GetData());
	else
		printf("Key 26 was not Found\n");
	
	printf("Deleting Key 15....\n");
	bst.Delete(15);

	printf("printing Tree Data....\n");
	bst.Print();

    return 0;
}

