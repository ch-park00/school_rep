#include <stdio.h>
#include <stdlib.h>

struct node
{
	int idx;
	int data;
	struct node* next;
};
struct node** root = 0;
int cnt = 0;
struct node* find_node(int layer, int idx)
{
	struct node *cur = root[layer];
	if (cur == 0)
	{
		return 0;
	}
	while (cur != 0)
	{
		if (cur->idx == idx)
		{
			return cur;
		}
		cur = cur->next;
	}
	return 0;
}
void add2root(struct node *new1, int layer)
{
	struct node *cur = root[layer];
	if (cur == 0)
	{
		root[layer] = new1;
		return;
	}
	while (cur->next != 0)	cur = cur->next;
	cur->next = new1;
}
void add2bst(int data)
{
	if (root[0] == 0)
	{
		root[0] = (struct node*)malloc(sizeof(struct node));
		root[0]->idx = 1;
		root[0]->data = data;
		root[0]->next = 0;
		return;
	}
	else
	{
		cnt++;
		int layer = 0;
		int index = 1;
		while (1)
		{
			struct node *cur = find_node(layer, index);
			if (cur == 0)
			{
				cnt--;
				struct node *new1 = (struct node *)malloc(sizeof(struct node));
				new1->data = data;
				new1->idx = index;
				new1->next = 0;
				add2root(new1, layer);
				return;
			}
			if (cur->data > data)
			{
				layer++;
				index = index * 2;
			}
			else
			{
				layer++;
				index = index * 2 + 1;
			}
			cnt++;
		}
	}
}
int main()
{
	int num;
	scanf("%d", &num);
	root = (struct node**)calloc(num, sizeof(struct node*));
	for (int i = 0; i < num; i++)
	{
		int data;
		scanf("%d", &data);
		add2bst(data);
		printf("**%d**\n", cnt);
	}
	return 0;
}