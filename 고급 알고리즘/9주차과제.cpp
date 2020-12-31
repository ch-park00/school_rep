#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define vertex_sz 6
struct edge
{
	int vertex;
	struct edge *next;
};
struct vertex
{
	int data;
	struct edge *con;
};
//vertex 색상 정보 저장
int color[vertex_sz];
//그래프 저장
struct vertex graph[vertex_sz];
//색상의 개수
int color_num = 2;

void add2graph(int src, int dst)
{
	struct edge *cur = (struct edge*)malloc(sizeof(struct edge));
	cur->vertex = dst;
	cur->next = 0;

	if (graph[src].con == 0)
	{
		graph[src].con = cur;
	}
	else
	{
		struct edge *tmp = graph[src].con;
		while (tmp->next != 0)	tmp = tmp->next;
		tmp->next = cur;
	}
}
void addedge(int src, int dst)
{
	add2graph(src, dst);
	add2graph(dst, src);
}
int check_next(int ver)
{
	int ret = 0;
	for (int i = 0; i < color_num; i++)
	{
		struct edge *cur = graph[ver].con;
		while (cur != 0)
		{
			int idx = cur->vertex;
			if (color[idx] == i)
			{
				break;
			}
			cur = cur->next;
		}
		if (cur == 0)
		{
			color[ver] = i;
			if (ver == vertex_sz - 1)
			{
				for (int k = 0; k < vertex_sz; k++)
				{
					printf("%d\n", color[k]);
				}
				printf("----------------------\n");
				return 1;
			}
			int tmp = check_next(ver + 1);
			if (tmp != 0)	//ret=1;
			{
				return 1;
			}
		}
	}
	color[ver] = 0;
	return ret;
}
int is_fine(int num)
{
	int ret = 0;
	for (int i = 0; i < color_num; i++)
	{
		color[0] = i;
		int tmp = check_next(1);
		if (tmp != 0)	//ret = 1;
		{
			return 1;
		}
	}
	color[0] = 0;
	return ret;
}
void do_backtracking()
{
	while (1)
	{
		if (is_fine(color_num))
		{
			printf("%d\n", color_num);
			return;
		}
		else
		{
			color_num++;
		}
	}
}
int main()
{
	for (int i = 0; i < vertex_sz; i++)
	{
		graph[i].data = i;
		graph[i].con = 0;
		color[i] = -1;
	}
	addedge(0, 1);
	addedge(0, 4);
	addedge(0, 5);
	addedge(1, 3);
	addedge(1, 4);
	addedge(2, 3);
	addedge(2, 4);
	addedge(4, 5);
	do_backtracking();
	return 0;
}