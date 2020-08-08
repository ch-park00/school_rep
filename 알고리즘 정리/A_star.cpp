#include <stdio.h>
#include <stdlib.h>
struct edge
{
	int ver;
	int weight;
	struct edge *next;
};
struct node
{
	int data;
	int G;
	int H;
	int F;
	struct edge* con;
};
struct node *graph = 0;
struct node *open_list;
struct node *closed_list;
int open_point = 0;
int closed_point = 0;
void addedge(int src, int dst, int w)
{
	struct edge *new1 = (struct edge*)malloc(sizeof(struct edge));
	new1->ver = dst;
	new1->weight = w;
	new1->next = 0;

	if (graph[src - 1].con == 0)
	{
		graph[src - 1].con = new1;
	}
	else
	{
		struct edge *cur = graph[src - 1].con;
		while (cur->next != 0)	cur = cur->next;
		cur->next = new1;
	}
}
void add2Edge(int src, int dst, int w)
{
	addedge(src, dst, w);
	addedge(dst, src, w);
}
void add2open(int ver, int w)
{
	struct node *new2 = (struct node*)malloc(sizeof(struct node));
	new2->data = ver;
	new2->G = 0;
	new2->H=
}
void A_star_dijkstra(int src, int dst)
{
	open_list = (struct node*)malloc(sizeof(struct node) * 9);
	closed_list = (struct node*)malloc(sizeof(struct node) * 9);

	add2open(src, 0);
}
int main()
{
	graph = (struct node*)malloc(sizeof(struct node) * 9);
	for (int i = 0; i < 9; i++)
	{
		graph[i].data = i + 1;
		graph[i].con = 0;
	}
	add2Edge(1,2,1);
	add2Edge(2, 3, 1);
	add2Edge(5, 6, 1);
	add2Edge(7, 8, 1);
	add2Edge(8, 9, 1);
	add2Edge(1, 5, 3);
	add2Edge(3, 5, 3);
	add2Edge(2, 6, 3);
	add2Edge(5, 7, 3);
	add2Edge(5, 9, 3);
	add2Edge(6, 8, 3);
	add2Edge(2, 5, 2);
	add2Edge(3, 6, 2);
	add2Edge(5, 8, 2);
	add2Edge(6, 9, 2);

	A_star_dijkstra(1, 7);
	return 0;
}