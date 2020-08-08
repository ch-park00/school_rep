#include<stdio.h>
#include<stdlib.h>

#define SZ 6

int graph[SZ][SZ];

void addEdge(char src, char dst)
{
	graph[src - 'A'][dst - 'A'] = 1;
	graph[dst - 'A'][src - 'A'] = 1;
}

struct node {
	char v;
	struct node *next;
};

struct node *top = 0;

void push(char v)
{
	struct node *_new = (struct node*)malloc(sizeof(struct node));
	_new->next = top;
	_new->v = v;
	top = _new;
	return;
}

char pop(void)
{
	if (top == 0)
	{
		return '0';
	}
	struct node *t = top;
	char temp = top->v;
	top = top->next;
	free(t);
	return temp;
}

struct visit {
	char v;
	struct visit *left;
	struct visit *right;
};

struct visit *visited = 0;

void addTovisit(char v)
{
	printf("visted : %c\n", v);
	struct visit *_new = (struct visit*)malloc(sizeof(struct visit));
	_new->left = _new->right = 0;
	_new->v = v;

	if (visited == 0)
	{
		visited = _new;
		return;
	}
	struct visit *t = visited;
	while (1)
	{
		if (t->v > v)
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

int isVisted(char v)
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

void performDFS(char v)
{
	push(v);
	while (1)
	{
		char vertex = pop();
		if (vertex == '0')
		{
			return;
		}
		if (isVisted(vertex) == 1)
		{
			continue;
		}
		addTovisit(vertex);
		for (int i = 0; i < SZ; i++)
		{
			if (graph[vertex - 'A'][i] == 1)
			{
				if (isVisted(i + 'A') == 0)
				{
					push(i + 'A');
				}
			}
		}

	}
}


int main()
{
	addEdge('A', 'B');
	addEdge('A', 'C');
	addEdge('C', 'D');
	addEdge('B', 'D');
	addEdge('D', 'E');
	addEdge('D', 'F');

	performDFS('F');
}