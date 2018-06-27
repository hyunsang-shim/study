#include "MyLinkedList.h"
#include "stdafx.h"
using namespace std;

void Init(MY_LIST * list)
{
	list->head = NULL;	
	list->cur = NULL;
}

void InsertFront(MY_LIST * list, const MY_NODE_DATA * x)
{
	MY_NODE *ptr = list->head;
	list->head = list->cur = Alloc();
}

void InsertRear(MY_LIST * list, const MY_NODE_DATA * x)
{
	if (list->head == NULL)
		InsertFront(list, x);
	else
	{
		MY_NODE *ptr = list->head;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = list->cur = Alloc();
		SetNode(ptr->next, x, NULL, NULL);
	}
}

void RemoveFront(MY_LIST * list)
{
	if (list->head != NULL)
	{
		MY_NODE *ptr = list->head->next;	// 앞 노드의 다음 노드에 대한 포인터
		free(list->head);					// 머리 노드를 해제
		list->head = list->cur = ptr;		// 지금 노드와 머리 노드를 원래 앞 노드의 다음 노드로 변경
	}
}

void RemoveRear(MY_LIST * list)
{
	if (list->head != NULL)
	{
		if ((list->head)->next == NULL)	//노드가 1개일 경우
			RemoveFront(list);
		else
		{
			MY_NODE *ptr = list->head;
			MY_NODE *pre;
			/*
			ptr은 꼬리 노드를 향해 가고
			pre는 꼬리노드 직전 노드를 가리킨다
			*/
			while (ptr->next != NULL)
			{
				pre = ptr;
				ptr = ptr->next;
			}
			pre->next = NULL; // 원래의 꼬리노드 직전 노드를 꼬리노드로 만든다.
			free(ptr);	//꼬리노드를 해제한다.
			list->cur = pre;	// 지금 노드를 직전 노드로 없데이트 한다.
		}
	}
}

void RemoveCurrent(MY_LIST * list)
{
	if (list->cur == list->head)		//머리 노드를 선택한 거라면
		RemoveFront(list);		//머리 노드 삭제로 가능
	else
	{
		MY_NODE *ptr = list->head;		// 첫 노드를 임시 노드로 지정
		while (ptr->next != list->cur)	// 임시 노드의 다음 노드가 찾는 노드가 아니라면	
			ptr = ptr->next;		// 다음 노드로 이동
		
		/*
		cur == B
		  D
		A B C

		D = A (A.next == B)
		ptr = ptr->next (B)
		==> ptr.cur --> B가 됨
		ptr->next = list->cur(B)->next(C)
		ptr->next == C

		list->cur = ptr(B);
		*/

		//찾았으니까
		ptr->next = list->cur->next;	//임시 노드의 next 값을 삭제 할 노드의 next값으로 업데이트
		free(list->cur);		// 지금 노드 값을 해제
		list->cur = ptr;		// 지금 노드를 임시 노드로 대체;
	}
}

void Clear(MY_LIST * list)
{
	while (list->head != NULL)	//헤드가 널이 아니면
		RemoveFront(list); // 앞에껄 하나씩 지워나간다.
	// 다 지우고 나서
	list->cur = NULL; // 지금껄 비운다.
}

void Print_Current(const MY_LIST * list)
{
	if (list->cur == NULL)
		cout << "선택 한 노드가 없습니다." << endl;
	else
		cout << (&list->cur->data)->num << " ";
}

void Print_Current_Last(const MY_LIST * list)
{
	Print_Current(list);
	cout << endl;
}

void Print(const MY_LIST * list)
{
	if (list->head == NULL)
		cout << "노드가 없습니다." << endl;
	else 
	{
		MY_NODE *ptr = list->head;
		cout << "모든 노드 정보" << endl;
		while (ptr != NULL)
		{
			cout << (&list->cur->data)->num << " ";
			ptr = ptr->next;
		}
	}
}

void Terminate(MY_LIST * list)
{
	Clear(list);
}

static MY_NODE *Alloc(void)
{
	return (MY_NODE*)calloc(1, sizeof(MY_NODE));
}

static void SetNode(MY_NODE *n, const MY_NODE_DATA *x, MY_NODE *next, MY_NODE *prev)
{
	n->data = *x;
	n->next = next;
	n->prev = prev;
}

MY_NODE *Search(MY_LIST *list, MY_NODE_DATA *x, int compare(const MY_NODE_DATA *x, const MY_NODE_DATA *y))
{
	//찾는 중인 노드를 가리킬 변수 ptr을 선언하고, list->head로 초기화	
	MY_NODE *ptr = list->head;
	// ptr이 NULL인지 판단. NULL은 꼬리이거나 할당되지 않은 경우
	while (ptr != NULL)
	{
		if (compare(&ptr->data, x) == 0)	// 키 값이 같은 경우
		{
			list->cur = ptr;	// 같다 = 찾았다
			return ptr; //값을 넘겨줌
		}
		ptr = ptr->next;	//다음 노드로 이동
	}
	return NULL;	//실패 = NULL 반환
}
