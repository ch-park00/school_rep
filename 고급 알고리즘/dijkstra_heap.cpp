#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SZ 999999
#define SZ 5
struct edge
{
	int ver;
	int dist;
	struct edge* next;
};
struct vertex
{
	int ver;
	struct edge* con;
};
struct dijkstra
{
	int prev;
	int dist;
	int found;
};
struct node
{
	int ver;
	int w;
};
struct vertex graph[SZ];
struct dijkstra table[SZ];
struct node heap[SZ + 1];
int heap_pointer = 0;
void addedge(int src, int dst, int w)
{
	struct edge* new1 = (struct edge*)malloc(sizeof(struct edge));
	new1->ver = dst;
	new1->dist = w;
	new1->next = 0;

	if (graph[src].con == 0)
	{
		graph[src].con = new1;
	}
	else
	{
		struct edge* tmp = graph[src].con;
		while (tmp->next != 0)
		{
			tmp = tmp->next;
		}
		tmp->next = new1;
	}
}
void add2graph(int src, int dst, int w)
{
	addedge(src, dst, w);
	addedge(dst, src, w);
}
void add2heap(int ver)
{
	int cur;
	heap_pointer++;
	heap[heap_pointer].ver = ver;
	heap[heap_pointer].w = table[ver].dist;
	cur = heap_pointer;
	while (cur > 1)
	{
		int parent = cur / 2;

		if (heap[cur].w < heap[parent].w)
		{
			struct node tmp = heap[cur];
			heap[cur].w = heap[parent].w;
			heap[cur].ver = heap[parent].ver;
			heap[parent].ver = tmp.ver;
			heap[parent].w = tmp.w;
			cur = parent;
		}
		else
		{
			break;
		}
	}
}
int pop()
{
	if (heap_pointer == 0)
	{
		return -1;
	}
	int ret = heap[1].ver;
	int cur, min, left, right;
	memcpy(&heap[1], &heap[heap_pointer], sizeof(struct node));
	heap_pointer--;
	cur = 1;
	while (1)
	{
		min = cur;
		left = min * 2;
		right = left + 1;

		if (heap[min].w > heap[left].w&& left <= heap_pointer)
		{
			min = left;
		}
		if (heap[min].w > heap[right].w&& right <= heap_pointer)
		{
			min = right;
		}
		if (min == cur)
		{
			return ret;
		}
		else
		{
			struct node tmp;
			memcpy(&tmp, &heap[min], sizeof(struct node));
			memcpy(&heap[min], &heap[cur], sizeof(struct node));
			memcpy(&heap[cur], &tmp, sizeof(struct node));
			cur = min;
		}
	}

}
void do_dijkstra(int start, int dst)
{
	for (int i = 0; i < SZ; i++)
	{
		table[i].dist = MAX_SZ;
		table[i].found = 0;
		table[i].prev = -1;
	}
	table[start].dist = 0;
	add2heap(start);
	while (1)
	{
		int ver = pop();
		if (ver == -1)
		{
			break;
		}
		else
		{
			if (table[ver].found == 1)
			{
				continue;
			}
			else {
				printf("visit %d : %d\n", ver, table[ver].dist);
				if (ver == dst)
				{
					break;
				}
				struct edge* cur = graph[ver].con;
				table[ver].found = 1;
				while (cur != 0)
				{
					if (table[cur->ver].dist > table[ver].dist + cur->dist)
					{
						table[cur->ver].dist = table[ver].dist + cur->dist;
						table[cur->ver].prev = ver;
						add2heap(cur->ver);
					}
					cur = cur->next;
				}
			}
		}
	}
}
int main()
{
	add2graph(0, 1, 1);
	add2graph(0, 2, 3);
	add2graph(0, 4, 5);
	add2graph(1, 2, 2);
	add2graph(1, 4, 4);
	add2graph(2, 4, 6);
	add2graph(2, 3, 7);
	add2graph(3, 4, 8);

	do_dijkstra(0, 3);
	return 0;
}