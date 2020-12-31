#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *prev;
	struct node *next;
};

struct node *head = 0;

void add2DLL(int data)
{
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->data = data;
	new1->next = new1->prev = 0;

	if (head == 0)
	{
		head = new1;
	}
	else
	{
		struct node *cur = head;
		while (cur->next != 0)
		{
			cur = cur->next;
		}
		cur->next = new1;
		new1->prev = cur;
	}
}

void printDLL()
{
	struct node *cur = head;
	while (cur != 0)
	{
		printf("%d\n", cur->data);
		cur = cur->next;
	}
}
void insertDLL(int prev, int data)
{
	struct node *cur = head;
	while (cur != 0)
	{
		if (cur->data == prev)
		{
			break;
		}
		cur = cur->next;
	}
	if (cur == 0)	return;
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->data = data;
	new1->next = new1->prev = 0;
	new1->prev = cur;
	new1->next = cur->next;
	cur->next = new1;
	if (new1->next != 0)
	{
		new1->next->prev = new1;
	}

}
void del_DLL(int data)
{
	struct node *cur = head;
	while (cur != 0)
	{
		if (cur->data == data)
		{
			break;
		}
		cur = cur->next;
	}
	if (cur == 0)	return;
	if (cur == head)
	{
		if (head->next != 0)
		{
			cur->next->prev = 0;
		}
		head = head->next;
		free(cur);
	}
	else if (cur->next == 0)
	{
		cur->prev->next = 0;
		free(cur);
	}
	else
	{
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		free(cur);
	}
}
int main()
{
	add2DLL(1);
	add2DLL(2);
	add2DLL(3);
	printDLL();
	printf("------------------\n");
	insertDLL(2, 22);
	insertDLL(3, 33);
	insertDLL(1, 11);
	del_DLL(1);
	del_DLL(33);
	printDLL();
	return 0;
}