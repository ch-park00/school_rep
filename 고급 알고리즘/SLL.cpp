#include <stdio.h>
#include <stdlib.h>
#if 0
struct node
{
	int i;
	struct node *next;
};
struct node *head = 0;

void add2SLL(int data)
{
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->i = data;
	new1->next = 0;

	if (head == 0)
	{
		head = new1;
	}
	else
	{
		struct node *cur = head;
		while (cur->next != 0) {
			cur = cur->next;
		}
		cur->next = new1;
	}
}
void print_SLL()
{
	struct node *cur = head;
	while (cur != 0)
	{
		printf("%d\n", cur->i);
		cur = cur->next;
	}
}

void insert_SLL(int prev_data, int data)
{
	struct node *cur = head;
	while (cur != 0)
	{
		if (cur->i == prev_data)
		{
			break;
		}
		else
		{
			cur = cur->next;
		}
	}
	if (cur == 0)
	{
		return;
	}
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->i = data;
	new1->next = 0;
	if (cur->next == 0)
	{
		cur->next = new1;
		return;
	}
	else
	{
		new1->next = cur->next;
		cur->next = new1;
	}
}
void destory_SLL()
{
	struct node *cur = head;
	while (head != 0)
	{
		cur = head;
		head = head->next;
		free(cur);
	}
}
void delete_SLL(int data)
{
	struct node *cur = head;
	while (cur != 0)
	{
		if (cur->i == data)
		{
			break;
		}
		cur = cur->next;
	}
	if (cur == 0)
	{
		return;
	}
	if (cur == head)
	{
		head = head->next;
		free(cur);
		return;
	}
	else
	{
		struct node *prev = head;
		while (prev->next != cur)
		{
			prev = prev->next;
		}
		prev->next = cur->next;
		free(cur);
		return;
	}
}
int main()
{
	add2SLL(10);
	add2SLL(11);
	add2SLL(12);
	destory_SLL();
	add2SLL(4);
	add2SLL(5);
	add2SLL(6);
	insert_SLL(4, 11);
	insert_SLL(11, 22);
	insert_SLL(90, 1);
	delete_SLL(6);
	print_SLL();
	struct node *p;
	p = (struct node*)malloc(sizeof(struct node));
	p->i = 10;
	p->next = 0;
	printf("%d\n", p->i);
	free(p);
	return 0;
}
#endif
struct node
{
	int data;
	struct node *next;
};
struct node *head = 0;

void add2SLL(int data)
{
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->data = data;
	new1->next = 0;

	if (head == 0)
	{
		head = new1;
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
void insert_SLL(int prev, int data)
{
	struct node *tmp = head;
	while (tmp != 0)
	{
		if (tmp->data == prev)
		{
			break;
		}
		tmp = tmp->next;
	}
	if (tmp == 0)
	{
		printf("찾는 노드가 없습니다\n");
		return;
	}
	else
	{
		struct node *new1 = (struct node*)malloc(sizeof(struct node));
		new1->data = data;
		new1->next = 0;

		new1->next = tmp->next;
		tmp->next = new1;
	}
}
void delete_SLL(int data)
{
	struct node *tmp = head;
	while (tmp != 0)
	{
		if (tmp->data == data)
		{
			break;
		}
		tmp = tmp->next;
	}
	if (tmp == 0)
	{
		printf("지우는 노드가 없습니다\n");
		return;
	}
	else
	{
		if (tmp == head)
		{
			head = head->next;
			free(tmp);
		}
		else
		{
			struct node *prev = head;
			while (prev->next != tmp)
			{
				prev = prev->next;
			}
			prev->next = tmp->next;
			tmp->next = 0;
			free(tmp);
		}
	}
}

void print_SLL()
{
	struct node *tmp = head;
	while (tmp != 0)
	{
		printf("%d\n", tmp->data);
		tmp = tmp->next;
	}
}
int main()
{
	add2SLL(1);
	add2SLL(3);
	insert_SLL(3, 6);
	add2SLL(4);
	add2SLL(5);
	delete_SLL(5);
	//1-2-3-5
	print_SLL();
	return 0;
}