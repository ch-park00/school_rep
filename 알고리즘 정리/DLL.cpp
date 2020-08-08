#include <stdio.h>
#include <stdlib.h>
struct node
{
	int data;
	struct node *next;
	struct node *prev;
};
struct node *head = 0;

struct node*createnode(int num)
{
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->data = num;
	new1->next = 0;
	new1->prev = 0;
	return new1;
}
void addnode(int num)
{
	struct node *new1 = createnode(num);
	if (head == 0)
	{
		head = new1;
		return;
	}
	else
	{
		struct node *tmp = head;
		while (tmp->next != 0)
		{
			tmp = tmp->next;
		}
		tmp->next = new1;
		new1->prev = tmp;
	}
}
void insertnode(int index, int num)
{
	if (index < 0)	return;
	if (index == 0)
	{
		struct node *new1 = createnode(num);
		new1->next = head;
		head->prev = new1;
		head = new1;
		return;
	}
	else
	{
		struct node *cur = head;
		int cnt = 1;
		while (cur != 0)
		{
			if (cnt >= index)	break;
			cnt++;
			cur = cur->next;
		}
		if (cur == 0) return;
		else
		{
			struct node *new1 = createnode(num);
			if (cur->next == 0)
			{
				cur->next = new1;
				new1->prev = cur;
			}
			else
			{
				new1->next = cur->next;
				new1->prev = cur;
				cur->next->prev = new1;
				cur->next = new1;
			}
		}
	}
}
void deletenode(int index)
{
	if (index < 0 || head == 0)	return;
	if (index == 0)
	{
		struct node *tmp = head;
		tmp->next->prev = 0;
		head = head->next;
		free(tmp);
		return;
	}
	else
	{
		int cnt = 1;
		struct node *cur = head;
		while (cur != 0)
		{
			if (cnt > index)	break;
			cnt++;
			cur = cur->next;
		}
		if (cur == 0)	return;
		else
		{
			if (cur->next == 0)
			{
				cur->prev->next = 0;
			}
			else
			{

				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;
			}
			free(cur);
			return;
		}
	}
}
int main()
{
	for (int i = 0; i < 10; i++)
	{
		addnode(i);
	}
	insertnode(1, 22);
	deletenode(0);
	struct node *tmp = head;
	while (tmp->next != 0)
	{
		tmp = tmp->next;
	}
	while (tmp != 0)
	{
		printf("%d, %x\n", tmp->data,tmp->next);
		tmp = tmp->prev;
	}
	return 0;
}