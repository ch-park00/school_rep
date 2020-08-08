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
	char ver;
	char prev_ver;
	int dist;
};
struct vertex *graph = 0;
struct dijkstra *table = 0;
struct dijkstra heap[100] = { 0 };
char stack[100] = { 0 };
int top_stack = -1;
int top = 0;
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

void add2heap(struct dijkstra cur)
{
	top++;
	int idx = top;
	heap[top] = cur;
	while (1)
	{
		int parent = idx / 2;
		if (parent < 1 || heap[idx].dist > heap[parent].dist)	return;
		struct dijkstra tmp = heap[parent];
		heap[parent] = heap[idx];
		heap[idx] = tmp;
		idx = parent;
	}
}
struct dijkstra pop()
{
	int cur = 1;
	struct dijkstra tmp = heap[1];
	if (top == 0)	return { 0,0 };
	heap[1] = heap[top];
	top--;
	while (1)
	{
		int big = cur;
		int left = cur * 2;
		int right = left + 1;
		if (left <= top && heap[cur].dist > heap[left].dist)
		{
			big = left;
		}
		if (right <= top && heap[big].dist > heap[right].dist)
		{
			big = right;
		}
		if (cur == big)	break;
		struct dijkstra tmp1 = heap[big];
		heap[big] = heap[cur];
		heap[cur] = tmp1;
		cur = big;
	}
	return tmp;
}
struct vertex* find_ver(char ver)
{
	struct vertex* cur = graph;
	while (cur != 0)
	{
		if (cur->data == ver)
		{
			break;
		}
		cur = cur->next;
	}
	return cur;
}
void fix_table(struct dijkstra ver_)
{
	struct edge *cur = find_ver(ver_.ver)->con;
	while (cur != 0)
	{
		if (table[cur->data - 'A'].dist > ver_.dist + cur->weight)
		{
			table[cur->data - 'A'].dist = ver_.dist + cur->weight;
			table[cur->data - 'A'].prev_ver = ver_.ver;
			struct dijkstra tmp = { cur->data,ver_.ver, ver_.dist + cur->weight };
			add2heap(tmp);
		}
		cur = cur->next;
	}
}
void push(char data)
{
	if (top_stack > 99)	return;
	top_stack++;
	stack[top_stack] = data;
}
char pop_stack()
{
	if (top_stack == -1)	return -1;
	char tmp = stack[top_stack];
	top_stack--;
	return tmp;
}
void find_path(char ver)
{
	int idx = ver - 'A';
	while (1)
	{
		push(table[idx].ver);
		if (table[idx].prev_ver == 0)	break;
		idx = table[idx].prev_ver - 'A';
	}
	while (1)
	{
		char data = pop_stack();
		if (data == -1)	break;
		printf("%c\n", data);
	}
}
void dodijkstra_heap(char src, char dst)
{
	table = (struct dijkstra*)malloc(sizeof(struct dijkstra)*NUM_VERTEX);
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		table[i].ver = 'A' + i;
		table[i].dist = 9999999;
		table[i].prev_ver = 0;
	}
	table[src - 'A'].dist = 0;
	add2heap(table[src - 'A']);
	while (1)
	{
		struct dijkstra cur = pop();
		if ((cur.dist == 0 && cur.ver == 0) || cur.ver == dst) {
			printf("%c->%c:%d\n", src, dst, cur.dist);
			break;
		}
		if (cur.dist > table[cur.ver - 'A'].dist)	continue;
		else {
			fix_table(cur);
		}
	}
	find_path(dst);
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

	dodijkstra_heap('F', 'C');
	return 0;
}