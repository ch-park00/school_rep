#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	char data[30];
	struct node *right;
	struct node *left;
};
typedef struct node bst;
bst *root = 0;
bst *stack[100];
int top = -1;
void push(bst *p)
{
	if (top > 99)
	{
		return;
	}
	top++;
	stack[top] = p;
}
bst *pop()
{
	if (top == -1)
	{
		return 0;
	}
	top--;
	return stack[top + 1];
}
void connect(bst *p)
{
	bst *q = root;
	if (q == 0)
	{
		root = p;
		return;
	}
	else
	{
		while (1)
		{
			if (strcmp(p->data,q->data) < 0)
			{
				if (q->left == 0)
				{
					q->left = p;
					return;
				}
				else
				{
					q = q->left;
				}
			}
			else
			{
				if (q->right == 0)
				{
					q->right = p;
					return;
				}
				else
				{
					q = q->right;
				}
			}
		}
	}
}
bst * findleast()
{
	bst *p = root->right;
	while (1)
	{
		if (p->left == 0)
		{
			return p;
		}
		push(p);
		p = p->left;
	}
}
bst * findmost()
{
	bst *p = root->left;
	while (1)
	{
		if (p->right == 0)
		{
			return p;
		}
		push(p);
		p = p->right;

	}
}
void removeroot(bst *n)
{
	bst *p = root;
	if (p->left == 0 && p->right == 0)
	{
		root = 0;
		free(p);
		printf("none\n");
	}
	else if (p->left != 0 && p->right == 0)
	{
		root = root->left;
		printf("%s\n", root->data);
		free(p);
	}
	else if (p->left == 0 && p->right != 0)
	{
		root = root->right;
		printf("%s\n", root->data);
		free(p);
	}
	else
	{
		bst *q1 = findleast();
		bst *parent1 = pop();
		top = -1;
		strcpy(root->data, q1->data);
		bst *q2 = findmost();
		bst *parent2 = pop();
		printf("%s\n", q2->data);
		printf("%s\n", q1->data);

	}
}
void main()
{
	int a;
	scanf("%d", &a);
	for (int i = 0; i < a; i++)
	{
		bst *p = (bst*)malloc(sizeof(bst));
		p->left = 0;
		p->right = 0;
		scanf("%s", p->data);
		connect(p);
	}
	removeroot(root);
}