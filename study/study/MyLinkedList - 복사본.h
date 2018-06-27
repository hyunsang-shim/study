#pragma once


typedef struct _node_data_
{
	int num;
} MY_NODE_DATA;

typedef struct _node_ {
	MY_NODE_DATA data;
	struct _node_ *prev;
	struct _node_ *next;
} MY_NODE;

typedef struct __my_list{
	MY_NODE *head;
	MY_NODE *cur;
} MY_LIST;

void Init(MY_LIST *list);

MY_NODE *Search(MY_LIST *list, MY_NODE_DATA *x, int compare(const MY_NODE_DATA *x, const MY_NODE_DATA *y));

//赣府俊 持扁
void InsertFront(MY_LIST *list, const MY_NODE_DATA *x);

//部府俊 持扁
void InsertRear(MY_LIST *list, const MY_NODE_DATA *x);

void RemoveFront(MY_LIST *list);

void RemoveRear(MY_LIST *list);

void RemoveCurrent(MY_LIST *list);

void Clear(MY_LIST *list);

void Print_Current(const MY_LIST *list);

void Print_Current_Last(const MY_LIST *list);

void Print(const MY_LIST *list);

void Terminate(MY_LIST *list);



