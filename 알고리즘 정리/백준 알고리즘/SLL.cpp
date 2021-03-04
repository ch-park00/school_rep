#include <stdio.h>
#include <stdlib.h>
struct node
{
	int num;
	struct node *next;
};
struct node *head = 0;

struct node* createnode(int num)
{
	struct node *cur = (struct node*)malloc(sizeof(struct node));
	cur->num = num;
	cur->next = 0;
	return cur;
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
	}
}
void insertnode(int index, int num)
{
	if (index == 0)
	{
		struct node *new1 = createnode(num);
		new1->next = head;
		head = new1;
		return;
	}
	struct node *cur = head;
	for (int i = 1; i < index; i++)
	{
		cur = cur->next;
		if (cur == 0)
		{
			printf("input error\n");
			return;
		}
	}
	struct node *new1 = createnode(num);
	new1->next = cur->next;
	cur->next = new1;
	
}
void deletenode(int index)
{
	if (head == 0 || index < 0)	return;
	if (index == 0)
	{
		struct node *tmp = head;
		head = head->next;
		free(tmp);
		return;
	}
	else
	{
		struct node *prev = head;
		for (int i = 1; i < index; i++)
		{
			prev = prev->next;
			if (prev == NULL)
			{
				printf("error\n");
				return;
			}
		}
		struct node *tmp = prev->next;
		prev->next = prev->next->next;
		free(tmp);
		return;
	}
}
int main()
{
//	insertnode(0, 500);
	struct node *tmp = head;
	while (tmp != 0)
	{
		printf("%d\n", tmp->num);
		tmp = tmp->next;
	}
	printf("------------------------\n");
	deletenode(0);
	tmp = head;
	printf("%x\n", tmp);
	return 0;
}