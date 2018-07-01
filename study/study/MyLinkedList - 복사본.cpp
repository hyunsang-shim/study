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
		MY_NODE *ptr = list->head->next;	// �� ����� ���� ��忡 ���� ������
		free(list->head);					// �Ӹ� ��带 ����
		list->head = list->cur = ptr;		// ���� ���� �Ӹ� ��带 ���� �� ����� ���� ���� ����
	}
}

void RemoveRear(MY_LIST * list)
{
	if (list->head != NULL)
	{
		if ((list->head)->next == NULL)	//��尡 1���� ���
			RemoveFront(list);
		else
		{
			MY_NODE *ptr = list->head;
			MY_NODE *pre;
			/*
			ptr�� ���� ��带 ���� ����
			pre�� ������� ���� ��带 ����Ų��
			*/
			while (ptr->next != NULL)
			{
				pre = ptr;
				ptr = ptr->next;
			}
			pre->next = NULL; // ������ ������� ���� ��带 �������� �����.
			free(ptr);	//������带 �����Ѵ�.
			list->cur = pre;	// ���� ��带 ���� ���� ������Ʈ �Ѵ�.
		}
	}
}

void RemoveCurrent(MY_LIST * list)
{
	if (list->cur == list->head)		//�Ӹ� ��带 ������ �Ŷ��
		RemoveFront(list);		//�Ӹ� ��� ������ ����
	else
	{
		MY_NODE *ptr = list->head;		// ù ��带 �ӽ� ���� ����
		while (ptr->next != list->cur)	// �ӽ� ����� ���� ��尡 ã�� ��尡 �ƴ϶��	
			ptr = ptr->next;		// ���� ���� �̵�
		
		/*
		cur == B
		  D
		A B C

		D = A (A.next == B)
		ptr = ptr->next (B)
		==> ptr.cur --> B�� ��
		ptr->next = list->cur(B)->next(C)
		ptr->next == C

		list->cur = ptr(B);
		*/

		//ã�����ϱ�
		ptr->next = list->cur->next;	//�ӽ� ����� next ���� ���� �� ����� next������ ������Ʈ
		free(list->cur);		// ���� ��� ���� ����
		list->cur = ptr;		// ���� ��带 �ӽ� ���� ��ü;
	}
}

void Clear(MY_LIST * list)
{
	while (list->head != NULL)	//��尡 ���� �ƴϸ�
		RemoveFront(list); // �տ��� �ϳ��� ����������.
	// �� ����� ����
	list->cur = NULL; // ���ݲ� ����.
}

void Print_Current(const MY_LIST * list)
{
	if (list->cur == NULL)
		cout << "���� �� ��尡 �����ϴ�." << endl;
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
		cout << "��尡 �����ϴ�." << endl;
	else 
	{
		MY_NODE *ptr = list->head;
		cout << "��� ��� ����" << endl;
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
	//ã�� ���� ��带 ����ų ���� ptr�� �����ϰ�, list->head�� �ʱ�ȭ	
	MY_NODE *ptr = list->head;
	// ptr�� NULL���� �Ǵ�. NULL�� �����̰ų� �Ҵ���� ���� ���
	while (ptr != NULL)
	{
		if (compare(&ptr->data, x) == 0)	// Ű ���� ���� ���
		{
			list->cur = ptr;	// ���� = ã�Ҵ�
			return ptr; //���� �Ѱ���
		}
		ptr = ptr->next;	//���� ���� �̵�
	}
	return NULL;	//���� = NULL ��ȯ
}
