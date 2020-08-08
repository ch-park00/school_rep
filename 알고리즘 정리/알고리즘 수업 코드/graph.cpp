#include<stdio.h>
#include<stdlib.h>
#define NUM_VERTEX 4
struct node {
	char v;
	struct node *next;
};
struct node * graph[NUM_VERTEX];
int getIndex(char _c)
{
	return _c - 'A';
}
void addEdge(char _s, char _c)
{
	int i = getIndex(_s);
	int j = getIndex(_c);
	struct node *_new = (struct node*)malloc(sizeof(struct node));
	_new->next = 0;
	_new->v = _c;
	struct node *_new2 = (struct node *)malloc(sizeof(struct node));
	_new2->next = 0;
	_new2->v = _s;
	if (graph[i] == 0)
	{
		graph[i] = _new;
		return;
	}
	struct node *t = graph[i];
	while (1)
	{
		if (t->next == 0)
		{
			t->next = _new;
			break;
		}
		t = t->next;
	}
	if (graph[j] == 0)
	{
		graph[j] = _new2;
		return;
	}
	struct node *p = graph[j];
	while (1)
	{
		if (p->next == 0)
		{
			p->next = _new2;
			return;
		}
		p = p->next;
	}
}
void showConnectedVertex(char _c)
{
	int i = getIndex(_c);
	struct node *t = graph[i]; //headÀÓ
	while (1)
	{
		if (t == 0)
		{
			return;
		}
		printf("%c ", t->v);
		t = t->next;
	}

	return;
}
int main(void)
{
	addEdge('A', 'B');
	addEdge('A', 'C');
	addEdge('B', 'D');
	addEdge('C', 'D');

	showConnectedVertex('C');
}