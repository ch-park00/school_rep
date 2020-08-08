#include <stdio.h>
#include <stdlib.h>
#define max_size 9999999
int ver_num, edge_num;
struct edge
{
	int src;
	int dst;
	int w;
};
struct vertex
{
	int ver;
	int cnt;
	struct edge *edge;
	int point;
};
struct vertex* graph = 0;
struct edge* con = 0;
struct edge* table = 0;
struct edge* heap = 0;
int top = 0;
int findindex(int data)
{
	return data - 1;
}
void addEdge(int src, int dst, int w)
{
	int idx = findindex(src);
	graph[idx].cnt++;

}

void make_graph()
{
	for (int i = 0; i < ver_num; i++)
	{
		graph[i].edge = (struct edge*)malloc(sizeof(struct edge) * graph[i].cnt);
	}
	for (int i = 0; i < edge_num; i++)
	{
		int idx = con[i].src - 1;
		int con_idx = graph[idx].point;
		graph[idx].edge[con_idx].dst = con[i].dst;
		graph[idx].edge[con_idx].w = con[i].w;
		graph[idx].point++;
	}
}
void add2Heap(struct edge data)
{
	int cur;
	top++;
	heap[top] = data;
	cur = top;

	while (1)
	{
		int parent = cur / 2;
		if (parent<1 || heap[cur].w>heap[parent].w)
		{
			return;
		}
		else
		{
			struct edge tmp = heap[parent];
			heap[parent] = heap[cur];
			heap[cur] = tmp;
			cur = parent;
		}
	}
}
int pop_from_heap()
{
	if (top == 0)	return -1;
	int ret = heap[1].src - 1;
	int cur = 1;
	heap[1] = heap[top];
	top--;

	while (1)
	{
		int min, left, right;
		min = cur;
		left = cur * 2;
		right = left + 1;
		if (left <= top && heap[min].w > heap[left].w)
		{
			min = left;
		}
		if (right <= top && heap[min].w > heap[right].w)
		{
			min = right;
		}
		if (cur == min) {
			break;
		}
		else {
			struct edge tmp = heap[min];
			heap[min] = heap[cur];
			heap[cur] = tmp;
			cur = min;
		}
	}
	return ret;
}
void fix_table(int index)
{
	int num = graph[index].cnt;
	struct edge *fix = graph[index].edge;
	for (int i = 0; i < num; i++)
	{
		int idx = fix[i].dst - 1;
		if (table[idx].w > table[index].w + fix[i].w)
		{
			table[idx].w = table[index].w + fix[i].w;
			add2Heap(table[idx]);
		}
	}
}
void print_result()
{
	for (int i = 0; i < ver_num; i++)
	{
		if (table[i].w == max_size)
		{
			printf("INF\n");
		}
		else
		{
			printf("%d\n", table[i].w);
		}
	}
}
void do_dijkstra(int start)
{
	table = (struct edge*)malloc(sizeof(struct edge) * ver_num);
	heap = (struct edge*)malloc(sizeof(struct edge) * edge_num);
	for (int i = 0; i < ver_num; i++)
	{
		table[i].src = i + 1;
		table[i].w = max_size;
	}
	table[start - 1].w = 0;
	add2Heap(table[start - 1]);

	while (1)
	{
		int idx = pop_from_heap();
		if (idx == -1)	break;
		else
		{
			fix_table(idx);
		}
	}
	print_result();
}
int main()
{
	int start;
	scanf("%d %d", &ver_num, &edge_num);
	scanf("%d", &start);
	graph = (struct vertex*)malloc(sizeof(struct vertex) * ver_num);
	con = (struct edge*)malloc(sizeof(struct edge) * edge_num);
	for (int i = 0; i < ver_num; i++)
	{
		graph[i].ver = i + 1;
		graph[i].cnt = 0;
		graph[i].point = 0;
	}
	for (int i = 0; i < edge_num; i++)
	{
		int data1, data2, data3;
		scanf("%d %d %d", &data1, &data2, &data3);
		con[i].src = data1;
		con[i].dst = data2;
		con[i].w = data3;
		graph[data1 - 1].cnt++;
	}
	make_graph();
	free(con);

	do_dijkstra(start);
	return 0;
}