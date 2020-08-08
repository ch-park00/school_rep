#if 0
#include<stdio.h>
#include<stdlib.h>

#define NUM_VERTEX 6


struct node {
	char v;
	struct node *next;
};

struct node *stack_by_SLL = 0; //top과 같은 역활.

void push(char _c)
{
	struct node *_new = (struct node*)malloc(sizeof(struct node));
	_new->v = _c;
	_new->next = 0;

	if (stack_by_SLL == 0)
	{
		stack_by_SLL = _new;
		return;
	}
	else
	{
		_new->next = stack_by_SLL;
		stack_by_SLL = _new;
		return;
	}

	return;
}

char pop(void)
{
	
	if (stack_by_SLL == 0)
	{
		printf("out of stack");
		return '*';
	}
	else
	{
		struct node *top = stack_by_SLL;
		stack_by_SLL = top->next;

		char res = top->v;
		free(top);
		return res;
	}
}



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
	struct node *t = graph[i]; //head임
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
	push('A');
	push('b');
	push('c');

	char c;

	while ((c = pop()) != '*') //stack_by_SLL != 0
	{
		printf("%c\n", c);
	}

}












#if 0
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
	struct node *t = graph[i]; //head임
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



// matrix
#define NUM_VERTEX 4

int graph[NUM_VERTEX][NUM_VERTEX];

int getIndex(char _c)
{
	return _c - 'A';
}

void addEdge(char _src, char _dst)
{
	//해당하는 index를 구한다.
	int s = getIndex(_src);
	int d = getIndex(_dst);

	graph[s][d] = 1;
	graph[d][s] = 1;

	return;
}

void showConnectedVertex(char _c)
{
	int j = getIndex(_c);
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		if (graph[j][i] == 1)
		{
			printf("%c ", i+'A');
		}
	}
	return;
}


int main(void)
{
	addEdge('A','B');
	addEdge('A', 'C');
	addEdge('B', 'D');
	addEdge('C', 'D');
	
	showConnectedVertex('C'); /// A와D가 출력해야됨

	return 0;
}
#endif 
#endif 