#include <stdio.h>
#include <stdlib.h>

#define vertex_sz 11
#define stack_sz 20
// Edge 정보를 저장하는 구조체
struct edge
{
	int vertex;
	int weight;
	struct edge *next;
};
//vertex 정보 저장
struct vertex
{
	int data;
	struct edge *con;
};
//stack에 사용하는 구조체
struct s
{
	int data;
	int sum_w;
};
//그래프 저장
struct vertex graph[vertex_sz];
//스택
struct s stack[stack_sz];
int visited[vertex_sz];
int top = -1;

void push(int data, int w)
{
	if (top == stack_sz - 1)
	{
		printf("stack full\n");
		return;
	}
	top++;
	stack[top].data = data;
	stack[top].sum_w = w;
}
struct s pop()
{
	if (top == -1)
	{
		struct s t = { -1,-1 };
		return t;
	}
	struct s tmp = stack[top];
	top--;
	return tmp;
}
void addedge(int src, int dst, int w)
{
	int idx = src;
	struct edge *new1 = (struct edge*)malloc(sizeof(struct edge));
	new1->vertex = dst;
	new1->weight = w;
	new1->next = 0;

	if (graph[idx].con == 0)
	{
		graph[idx].con = new1;
	}
	else
	{
		struct edge *cur = graph[idx].con;
		while (cur->next != 0)	cur = cur->next;
		cur->next = new1;
	}
}
void add2edge(int src, int dst, int w)
{
	addedge(src, dst, w);
	addedge(dst, src, w);
}
int do_DFS(int start)
{
	int max_w = 0;
	int w = 0;
	push(start, w);
	while (1)
	{
		struct s tmp = pop();
		if (tmp.data == -1)
		{
			return max_w;
		}
		else
		{
			if (visited[tmp.data] == 0)
			{
				visited[tmp.data] = 1;
				w = tmp.sum_w;
				if (max_w < w)
				{
					max_w = w;
				}
				printf("visit %d and cur weight %d\n", tmp.data, tmp.sum_w);
				struct edge *cur = graph[tmp.data].con;
				while (cur != 0)
				{
					if (visited[cur->vertex] == 0)
					{
						push(cur->vertex, w + cur->weight);
					}
					cur = cur->next;
				}
			}
		}
	}
}

void my_function()
{
	int max_w = 0;
	for (int i = 0; i < vertex_sz; i++)
	{
		printf("cur vertex : %d\n", i);
		int data = do_DFS(i);
		printf("--------------------\n");
		if (data > max_w)
		{
			max_w = data;
		}
		for (int j = 0; j < vertex_sz; j++)
		{
			visited[j] = 0;
		}
	}
	printf("max : %d\n", max_w);
}
int main()
{
	for (int i = 0; i < vertex_sz; i++)
	{
		graph[i].data = i;
		graph[i].con = 0;
	}
	add2edge(0, 1, 1);
	add2edge(1, 2, 1);
	add2edge(2, 3, 1);
	add2edge(1, 4, 20);
	add2edge(2, 5, 5);
	add2edge(5, 6, 2);
	add2edge(5, 7, 2);
	add2edge(6, 8, 2);
	add2edge(0, 9, 10);
	add2edge(9, 10, 5);

	my_function();
	return 0;
}