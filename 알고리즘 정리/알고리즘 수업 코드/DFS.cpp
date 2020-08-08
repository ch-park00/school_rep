#if 0
#include<stdio.h>
#include<stdlib.h>

#define SZ 6

struct node {
	char v;
	struct node *next;
};

struct node *graph[SZ];

void _addEdge(char src, char dst)
{
	int idx = src - 'A';
	struct node *_new = (struct node*)malloc(sizeof(struct node));
	_new->next = 0;
	_new->v = dst;

	if (graph[idx] == 0)
	{
		graph[idx] = _new;
		return;
	}

	struct node *t = graph[idx];
	while (t->next != 0)
	{
		t = t->next;
	}
	t->next = _new;
}

void addEdge(char src, char dst)
{
	_addEdge(src, dst);
	_addEdge(dst, src);
}
//stack 

struct node *top = 0;

char pop(void)
{
	if (top == 0)
	{
		return '0';
	}
	struct node *t = top;
	char vertex = t->v;
	top = top->next;
	free(t);
	return vertex;
}

void push(char v)
{
	struct node *_new = (struct node*)malloc(sizeof(struct node));
	_new->v = v;
	_new->next = top;
	top = _new;
}

//visited

struct visit {
	char v;
	struct visit *left;
	struct visit *right;
};

struct visit *visited = 0;

void addToVisted(char v)
{
	printf("visited : %c\n", v);
	struct visit *_new = (struct visit*)malloc(sizeof(struct visit));
	_new->left = 0;
	_new->right = 0;
	_new->v = v;

	if (visited == 0)
	{
		visited = _new;
		return;
	}

	struct visit *t = visited;

	while (1)
	{
		if (t->v > _new->v)
		{
			if (t->left == 0)
			{
				t->left = _new;
				return;
			}
			t = t->left;
		}
		else
		{
			if (t->right == 0)
			{
				t->right = _new;
				return;
			}
			t = t->right;
		}
	}
}

int Isvisited(char v)
{
	struct visit *t = visited;
	while (t != 0)
	{
		if (t->v == v)
		{
			return 1;
		}
		else if (t->v > v)
		{
			t = t->left;
		}
		else
		{
			t = t->right;
		}
	}
	return 0;
}

void performsDFS(char v)
{
	push(v);
	while (1)
	{
		char vertex = pop();

		if (vertex == '0')
		{
			return;
		}
		if (Isvisited(vertex) == 1)
		{
			continue;
		}
		addToVisted(vertex);

		struct node *connected = graph[vertex - 'A'];
		while (connected != 0)
		{
			if (Isvisited(connected->v) == 0)
			{
				push(connected->v);
			}
			connected = connected->next;
		}
	}
}

int main(void)
{
	addEdge('A', 'B');
	addEdge('A', 'C');
	addEdge('C', 'D');
	addEdge('B', 'D');
	addEdge('D', 'E');
	addEdge('D', 'F');


	performsDFS('F');

	return 0;
}
#endif