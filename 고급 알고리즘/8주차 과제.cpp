#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define vertex_sz 10
#define A_sz 5
#define K_sz 3
#define B_sz 2
#define max 999999

struct edge
{
	char sec;
	int v;
	int weight;
	struct edge *next;
};
struct vertex
{
	int v;
	char sec;
	struct edge *con;
};
struct dijkstra
{
	int prev;
	int found;
	int dist;
};
struct node
{
	int vertex;
	int w;
};
struct vertex graph[vertex_sz];
struct dijkstra table[vertex_sz];
struct node heap[vertex_sz];
int heap_pointer = 0;
char find_section(int vertex)	
{
	if (vertex < A_sz)	return 'A';
	else if (vertex >= A_sz + K_sz)	return 'B';
	return 'K';
}
void addedge(int src, int dst, int w)	{
	struct edge *new1 = (struct edge*)malloc(sizeof(struct edge));
	new1->v = dst;
	new1->weight = w;
	new1->sec = find_section(dst);
	new1->next = 0;
	if (graph[src].con == 0)	graph[src].con = new1;
	else 
	{
		struct edge *tmp = graph[src].con;
		while (tmp->next != 0)	tmp = tmp->next;
		tmp->next = new1;
	}
}
void add2graph(int src, int dst, int w)
{
	addedge(src, dst, w);
	addedge(dst, src, w);
}
void add2heap(int vertex)	
{
	int cur;
	if (heap_pointer >= vertex_sz)	return;
	heap_pointer++;
	heap[heap_pointer].vertex = vertex;
	heap[heap_pointer].w = table[vertex].dist;
	cur = heap_pointer;
	while (cur > 1)	{
		int parent = cur / 2;
		if (heap[cur].w < heap[parent].w)	{
			struct node tmp = heap[parent];
			memcpy(&heap[parent], &heap[cur], sizeof(struct node));
			memcpy(&heap[cur], &tmp, sizeof(struct node));
			cur = parent;
		}
		else 
		{
			break;
		}
	}
}
char pop()	
{
	if (heap_pointer == 0)	return -1;
	int cur;
	int ret = heap[1].vertex;
	memcpy(&heap[1], &heap[heap_pointer], sizeof(struct node));
	heap_pointer--;
	cur = 1;
	while (1)	
	{
		int min = cur;
		int left = min * 2;
		int right = left + 1;

		if (left <= heap_pointer && heap[min].w > heap[left].w)		min = left;
		if (right <= heap_pointer && heap[min].w > heap[right].w)	min = right;
		if (min == cur)	return ret;
		else	
		{
			struct node tmp = heap[min];
			memcpy(&heap[min], &heap[cur], sizeof(struct node));
			memcpy(&heap[cur], &tmp, sizeof(struct node));
			cur = min;
		}
	}
}
void do_dijkstra(char src_section, char dst_section)	
{
	for (int i = 0; i < vertex_sz; i++)	
	{
		table[i].found = 0;
		table[i].prev = -1;
		table[i].dist = max;
		if (find_section(i) == src_section)	
		{
			table[i].dist = 0;
			add2heap(i);
		}
	}
	while (1)
	{
		int vertex = pop();
		if (vertex == -1)
		{
			break;
		}
		else
		{
			if (table[vertex].found == 1)	
			{
				continue;
			}
			else	
			{
				printf("visit : %d, %d\n", vertex, table[vertex].dist);
				table[vertex].found = 1;
				if (find_section(vertex) == dst_section)	
				{
					printf("result : %d\n", table[vertex].dist);
					break;
				}
				else	
				{
					struct edge *cur = graph[vertex].con;
					while (cur != 0)	
					{
						if (table[cur->v].dist > table[vertex].dist + cur->weight)
						{
							table[cur->v].dist = table[vertex].dist + cur->weight;
							table[cur->v].prev = vertex;
							add2heap(cur->v);
						}
						cur = cur->next;
					}
				}
			}
		}
	}
}
int main()
{
	for (int i = 0; i < vertex_sz; i++)	
	{
		graph[i].v = 0;
		graph[i].con = 0;
		graph[i].sec = find_section(i);
	}
	add2graph(0, 1, 5);
	add2graph(0, 2, 3);
	add2graph(0, 5, 50);
	add2graph(1, 4, 10);
	add2graph(2, 3, 1);
	add2graph(3, 6, 30);
	add2graph(4, 7, 20);
	add2graph(5, 9, 5);
	add2graph(6, 8, 10);
	add2graph(7, 8, 20);

	do_dijkstra('A', 'B');
	return 0;
}