#include <stdio.h>
#include <stdlib.h>
struct node
{
	int data;
	struct node *next;
};
struct node *head = 0;

void add2dll(int i)
{
	struct node *p = (struct node*)malloc(sizeof(struct node));
	p->data = i;
	p->next = 0;
	if (head == 0)
	{
		head = p;
		return;
	}
	else
	{
		struct node *temp = head;
		while (1)
		{
			if (temp->next == 0)
			{
				temp->next = p;
				return;
			}
			temp = temp->next;
		}
	}
}
void deletenode(int i)
{
	struct node *p = head;
	struct node *temp = head;

	while (1)
	{
		if (p == 0)
		{
			return;
		}
		if (p->data == i)
		{
			break;
		}
		p = p->next;
	}
	while (1)
	{
		if (temp->next == p)
		{
			break;
		}
		temp = temp->next;
	}
	if (p == head)
	{
		head = head->next;
		free(p);
		return;
	}
	else
	{
		temp->next = p->next;
		free(p);
	}
}
void printall()
{
	struct node *p = head;
	while (p != 0)
	{
		printf("%d\n", p->data);
		p = p->next;
	}
}
void main()
{
	int a;
	scanf("%d", &a);
	for (int i = 0; i < a; i++)
	{
		int temp;
		scanf("%d",&temp);
		add2dll(temp);
	}
	scanf("%d", &a);
	deletenode(a);
	printall();
}