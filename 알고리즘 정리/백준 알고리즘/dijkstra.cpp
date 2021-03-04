#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
const int NUM_VERTEX = 7;
struct edge
{
	char data;
	int weight;
	struct edge *next;
};
struct vertex
{
	char data;
	struct edge *con;
	struct vertex *next;
};
struct dijkstra
{
	char src;
	char prev;
	char found;
	int weight;
};
struct vertex *graph = 0;
struct dijkstra *table = 0;
char stack[NUM_VERTEX] = { 0 };
int top = -1;
void init(int num, ...)
{
	struct vertex *tmp = graph;
	va_list ap;
	va_start(ap, num);
	for (int i = 0; i < num; i++)
	{
		struct vertex *new1 = (struct vertex*)malloc(sizeof(struct vertex));
		new1->data = va_arg(ap, char);
		new1->next = 0;
		new1->con = 0;
		if (graph == 0) {
			graph = new1;
			tmp = graph;
		}
		else {
			tmp->next = new1;
			tmp = tmp->next;
		}
	}
	va_end(ap);
}
struct vertex* findvertex(char ver)
{
	struct vertex *cur = graph;
	while (cur != 0)
	{
		if (cur->data == ver)	break;
		cur = cur->next;
	}
	return cur;
}

void addEdge_(char src, char dst, int weight)
{
	struct vertex *cur = findvertex(src);
	if (cur == 0) {
		printf("src input error\n");
		return;
	}
	struct edge *new1 = (struct edge*)malloc(sizeof(struct edge));
	new1->data = dst;
	new1->weight = weight;
	new1->next = 0;
	if (cur->con == 0) {
		cur->con = new1;
	}
	else {
		struct edge *tmp = cur->con;
		while (tmp->next != 0)	tmp = tmp->next;
		tmp->next = new1;
	}
}
void addEdge(char src, char dst, int weight)
{
	addEdge_(src, dst, weight);
	addEdge_(dst, src, weight);
}
int findsmallestweight()
{
	int idx = -1;
	int min = 999999999;
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		if (table[i].weight < min && table[i].found == 0)
		{
			min = table[i].weight;
			idx = i;
		}
	}
	return idx;
}
int find_from_table(char src)
{
	int idx = -1;
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		if (table[i].src == src) {
			idx = i;
		}
	}
	return idx;
}
void fix_table(int index)
{
	struct edge *cur = findvertex(table[index].src)->con;
	while (cur != 0)
	{
		int idx = find_from_table(cur->data);
		if (table[idx].weight > cur->weight + table[index].weight)
		{
			table[idx].prev = table[index].src;
			table[idx].weight = cur->weight + table[index].weight;
		}
		cur = cur->next;
	}
}
void push(char data)
{
	if (top >= NUM_VERTEX)	return;
	top++;
	stack[top] = data;
}
char pop()
{
	if (top == -1)	return-1;
	char tmp = stack[top];
	top--;
	return tmp;
}
void print_path(char src, char dst)
{
	int idx = 0;
	idx = find_from_table(dst);
	while (1)
	{
		push(table[idx].src);
		if (table[idx].prev == 0)	break;
		idx = find_from_table(table[idx].prev);
	}
	while (1)
	{
		char data = pop();
		if (data == -1)	break;
		printf("%c\n", data);
	}
}
void dodijkstra(char src, char dst)
{
	if (findvertex(src) == 0 || findvertex(dst) == 0)
	{
		printf("input error\n");
		return;
	}
	table = (struct dijkstra*)malloc(sizeof(struct dijkstra)*NUM_VERTEX);
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		table[i].src = i + 'A';
		table[i].prev = 0;
		table[i].found = 0;
		table[i].weight = 999999999;
	}
	table[src - 'A'].weight = 0;
	while (1)
	{
		int idx = findsmallestweight();
		if (idx == -1 || table[idx].src==dst)	break;
		table[idx].found = 1;
		fix_table(idx);
	}
	printf("%c->%c:%d\n", src, dst, table[dst - 'A'].weight);
	print_path(src, dst);
}
int main()
{
	init(NUM_VERTEX, 'A', 'B', 'C', 'D', 'E', 'F', 'G');
	//A-B 방향성 없이 연결(양방향에서 모두 연결)
	addEdge('A', 'B', 8);
	addEdge('A', 'C', 5);
	addEdge('A', 'D', 3);
	addEdge('B', 'C', 7);
	addEdge('B', 'E', 13);
	addEdge('C', 'D', 4);
	addEdge('C', 'E', 20);
	addEdge('C', 'G', 17);
	addEdge('C', 'F', 80);
	addEdge('D', 'G', 2);
	addEdge('E', 'F', 15);

	dodijkstra('F', 'C');
	return 0;
}