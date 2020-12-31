#include <stdio.h>
#include <stdlib.h>

#define vertex_sz 5
struct vertex
{
	int data;
	int weight;
	struct vertex *next;
};
struct edge
{
	int v1;
	int v2;
	int w;
};
struct vertex *graph[vertex_sz];
struct edge E[8];
int cycle_detection[vertex_sz] = { 0,1,2,3,4 };
void addEdge(int src, int dst, int weight)
{
	struct vertex *new1 = (struct vertex*)malloc(sizeof(struct vertex));
	new1->data = dst;
	new1->weight = weight;
	new1->next = 0;

	if (graph[src] == 0)
	{
		graph[src] = new1;
	}
	else
	{
		struct vertex *cur = graph[src];
		while (cur->next != 0)	cur = cur->next;
		cur->next = new1;
	}
}
//모든 엣지에 대해 오름차순 정렬
void sort_edge()
{
	int idx = 0;
	for (int i = 0; i < vertex_sz; i++)
	{
		struct vertex *cur = graph[i];
		while (cur != 0)
		{
			E[idx].v1 = i;
			E[idx].v2 = cur->data;
			E[idx].w = cur->weight;
			idx++;
			cur = cur->next;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 7 - i; j++)
		{
			if (E[j].w > E[j+1].w)
			{
				struct edge tmp = E[j];
				E[j] = E[j+1];
				E[j+1] = tmp;
			}
		}
	}
}

int cycle_detection_function(int i, int j)
{
	return (cycle_detection[i] == cycle_detection[j] ? 1 : 0);
}
void change_cycle_array(int v1, int v2)
{
	int g1 = cycle_detection[v1];
	int g2 = cycle_detection[v2];
	int small, big;
	if (g1 > g2)
	{
		big = g1;
		small = g2;
	}
	else
	{
		big = g2;
		small = g1;
	}
	for (int i = 0; i < vertex_sz; i++)
	{
		if (cycle_detection[i] == big)
		{
			cycle_detection[i] = small;
		}
	}
}
void do_MST()
{
	int sum_edge = 0;
	for (int i = 0; i < 8; i++)
	{
		if (cycle_detection[E[i].v1] != cycle_detection[E[i].v2])
		{
			printf("%d - %d :%d\n", E[i].v1, E[i].v2, E[i].w);
			sum_edge++;
			change_cycle_array(E[i].v1, E[i].v2);
			if (sum_edge == vertex_sz - 1)
			{
				return;
			}
		}
	}
}
int main()
{
	addEdge(0, 1, 1);
	addEdge(0, 2, 3);
	addEdge(0, 4, 5);
	addEdge(1, 2, 2);
	addEdge(1, 4, 4);
	addEdge(2, 4, 6);
	addEdge(2, 3, 7);
	addEdge(3, 4, 8);

	sort_edge();
	do_MST();
	return 0;
}