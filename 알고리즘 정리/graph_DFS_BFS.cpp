#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>
#define NUM_VERTEX 7
struct edge
{
	char data;
	int w;
	struct edge *next;
};
struct node 
{
	char v;
	struct edge *con;
};
struct node * graph[NUM_VERTEX];
int visited[NUM_VERTEX] = { 0 };
struct edge* stack = 0;

void Connect_Edge(int src, int dst)
{
	struct edge *new1 = (struct edge*)malloc(sizeof(struct edge));
	new1->data = dst + 'A';
	new1->next = 0;
	if (graph[src]->con == 0)
	{
		graph[src]->con = new1;
		return;
	}
	else
	{
		struct edge* cur = graph[src]->con;
		while (cur->next != 0)
		{
			cur = cur->next;
		}
		cur->next = new1;
	}
}
void addEdge(const char src, const char dst)
{
	int src_index = src - 'A';
	int dst_index = dst - 'A';
	Connect_Edge(src_index, dst_index);
	Connect_Edge(dst_index, src_index);
}
void init(int num, ...)
{
	va_list ap;
	va_start(ap, num);
	for (int i = 0; i < num; i++)
	{
		graph[i] = (struct node*)malloc(sizeof(struct node));
		graph[i]->v = va_arg(ap, char);
		graph[i]->con = 0;
	}
	va_end(ap);
}
// 입력받은 vertex와 연결되어 있는 vertex를 출력
void showConnectedVertex(const char d)
{
	int idx = d - 'A';
	struct edge *tmp = graph[idx]->con;
	while (tmp != 0)
	{
		printf("%c\n", tmp->data);
		tmp = tmp->next;
	}
}

void push(const char data)
{
	struct edge *new1 = (struct edge*)malloc(sizeof(struct edge));
	new1->data = data;
	new1->next = stack;
	stack = new1;
}
char pop()
{
	if (stack == 0)	return -1;
	struct edge *f = stack;
	char tmp = stack->data;
	stack = stack->next;
	free(f);
	return tmp;
}
void doDFS(const char start)
{
	push(start);
	while (1)
	{
		char tmp = pop();
		if (tmp == -1) {
			return;
		}
		else {
			if (visited[tmp - 'A']) {
				continue;
			}
			else {
				visited[tmp - 'A'] = 1;
				printf("%c\n", tmp);
				struct edge *cur = graph[tmp - 'A']->con;
				while (cur != 0)
				{
					push(cur->data);
					cur = cur->next;
				}
			}
		}
	}

}

void enqueue(const char data)
{
	struct edge *new1 = (struct edge *)malloc(sizeof(struct edge));
	new1->data = data;
	new1->next = 0;
	if (stack == 0)
	{
		stack = new1;
	}
	else
	{
		struct edge *tmp = stack;
		while (tmp->next != 0)	tmp = tmp->next;
		tmp->next = new1;
	}
}
char dequeue()
{
	if (stack == 0)	return -1;
	struct edge *tmp = stack;
	char ret = tmp->data;
	stack = stack->next;
	free(tmp);
	return ret;
}
void doBFS(const char start)
{
	enqueue(start);
	while (1)
	{
		char tmp = dequeue();
		if (tmp == -1) {
			return;
		}
		else {
			if (visited[tmp - 'A']) {
				continue;
			}
			else {
				visited[tmp - 'A'] = 1;
				printf("%c\n", tmp);
				struct edge *cur = graph[tmp - 'A']->con;
				while (cur != 0)
				{
					enqueue(cur->data);
					cur = cur->next;
				}
			}
		}
	}
	visited[NUM_VERTEX] = { 0 };
}
int main(void)
{
	init(NUM_VERTEX, 'A', 'B', 'C', 'D', 'E', 'F', 'G');
	//A-B 방향성 없이 연결(양방향에서 모두 연결)
	addEdge('A', 'B');
	addEdge('A', 'C');
	addEdge('A', 'D');
	addEdge('B', 'C');
	addEdge('B', 'E');
	addEdge('C', 'D');
	addEdge('C', 'E');
	addEdge('C', 'G');
	addEdge('C', 'F');
	addEdge('D', 'G');
	addEdge('E', 'F');
	doDFS('B');
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		visited[i] = 0;
	}
	printf("----------------\n");
	doBFS('B');
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		visited[i] = 0;
	}
	//showConnectedVertex('B');
}