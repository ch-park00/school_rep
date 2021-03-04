#include <stdio.h>
#include <stdlib.h>
struct node
{
	int val;
	struct node *next;
};
struct node *stack = 0;
struct node *queue = 0;

struct node* createnode(int data)
{
	struct node* new1 = (struct node*)malloc(sizeof(struct node));
	new1->val = data;
	new1->next = 0;
	return new1;
}
void add_Stack(int data)
{
	struct node *cur = createnode(data);
	if (stack == 0)
	{
		stack = cur;
	}
	else
	{
		struct node *tmp = stack;
		while (tmp->next != 0)
		{
			tmp = tmp->next;
		}
		tmp->next = cur;
	}
}
int pop()
{
	if (stack == 0)
	{
		printf("Stack is Empty");
		return -9999;
	}
	else
	{
		struct node *tmp = stack;
		if (tmp->next == 0)
		{
			int return_val = tmp->val;
			stack = 0;
			free(tmp);
			return return_val;
		}
		else
		{
			struct node *tmp1 = stack;
			while (tmp->next != 0)
			{
				tmp = tmp->next;
			}
			while (tmp1->next != tmp)	tmp1 = tmp1->next;
			tmp1->next = tmp->next;
			int return_val = tmp->val;
			free(tmp);
			return return_val;
		}
	}
}
void add_Queue(int data)
{
	struct node *new1 = createnode(data);
	if (queue == 0)
	{
		queue = new1;
	}
	else
	{
		new1->next = queue;
		queue = new1;
	}
}
int dequeue()
{
	if (queue == 0)
	{
		printf("Queue is Empty");
		return -9999;
	}
	else
	{
		struct node *tmp = queue;
		while (tmp->next != 0)
		{
			tmp = tmp->next;
		}
		if (tmp == queue)
		{
			int return_val = tmp->val;
			queue = 0;
			free(tmp);
			return return_val;
		}
		else
		{
			struct node *tmp1 = queue;
			while (tmp1->next != tmp)
			{
				tmp1 = tmp1->next;
			}
			int return_val = tmp->val;
			tmp1->next = tmp->next;
			free(tmp);
			return return_val;
		}

	}
}
int main()
{
	for (int i = 0; i < 4; i = i + 1)
	{
		add_Stack(i + 1);
		add_Queue(i + 1);
	}
	for (int i = 0; i < 5; i = i + 1)
	{
		printf("%d\n",pop());
	}
	printf("------------------------\n");
	for (int i = 0; i < 5; i = i + 1)
	{
		printf("%d\n", dequeue());
	}

	return 0;
}