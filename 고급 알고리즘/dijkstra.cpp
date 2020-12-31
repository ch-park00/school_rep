#include <stdio.h>
#include <stdlib.h>
#define vertex_sz 5

struct table
{
	int found;
	int dist;
	int prev;
};

struct edge
{
	int vertex;
	int weight;
	struct edge *next;
};
struct vertex
{
	int vertex;
	struct edge *con;
};
struct vertex graph[vertex_sz];
struct table dijkstra[vertex_sz];
void addedge(int src, int dst, int w)
{
	struct edge *new1 = (struct edge*)malloc(sizeof(struct edge));
	new1->vertex = dst;
	new1->weight = w;
	new1->next = 0;

	if (graph[src].con == 0)
	{
		graph[src].con = new1;
	}
	else
	{
		struct edge *cur = graph[src].con;
		while (cur->next != 0)
		{
			cur = cur->next;
		}
		cur->next = new1;
	}
}
void add_graph_edge(int src, int dst, int w)
{
	addedge(src, dst, w);
	addedge(dst, src, w);
}
int find_small()
{
	int ret = -1;
	int dist = 9999999;
	for (int i = 0; i < vertex_sz; i++)
	{
		if (dijkstra[i].found == 0 && dist > dijkstra[i].dist)
		{
			dist = dijkstra[i].dist;
			ret = i;
		}
	}
	return ret;
}
void do_dijkstra(int start)
{
	dijkstra[start].dist = 0;
	while (1)
	{
		int next = find_small();
		if (next == -1)
		{
			break;
		}
		else
		{
			printf("found %d vertex : %d\n", next, dijkstra[next].dist);
			struct edge *cur = graph[next].con;
			dijkstra[next].found = 1;
			while (cur != 0)
			{
				if (dijkstra[cur->vertex].dist > dijkstra[next].dist + cur->weight)
				{
					dijkstra[cur->vertex].prev = next;
					dijkstra[cur->vertex].dist = dijkstra[next].dist + cur->weight;
				}
				cur = cur->next;
			}
		}
	}
}
int main()
{
	for (int i = 0; i < vertex_sz; i++)
	{
		graph[i].vertex = i;
		graph[i].con = 0;

		dijkstra[i].found = 0;
		dijkstra[i].dist = 9999999;
		dijkstra[i].prev = -1;
	}
	add_graph_edge(0, 1, 1);
	add_graph_edge(0, 2, 3);
	add_graph_edge(0, 4, 5);
	add_graph_edge(1, 2, 2);
	add_graph_edge(1, 4, 4);
	add_graph_edge(2, 4, 6);
	add_graph_edge(2, 3, 7);
	add_graph_edge(3, 4, 8);


	do_dijkstra(0);
	return 0;
}