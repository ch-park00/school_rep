#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cnt = 0;
struct edge
{
	char *name;
	int dist;
	struct edge *next;
};
struct vertex
{
	char *name;
	struct edge *con;
	struct vertex *next;
};
struct dijkstra
{
	char *name;
	char *prev;
	int found;
	int dist;
};
struct node
{
	char *name;
	struct node *next;
};
struct node *stack = 0;
struct vertex *graph = 0;
struct dijkstra *dtable = 0;
void push(char *name)
{
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->name = name;
	new1->next = stack;
	stack = new1;
}
char* pop()
{
	if (stack == 0)
	{
		return 0;
	}
	struct node *temp = stack;
	char *temp1 = temp->name;
	stack = stack->next;
	free(temp);
	return temp1;
}
void add2vertex(char *name)
{
	struct vertex *new1 = (struct vertex*)malloc(sizeof(struct vertex));
	new1->name = (char*)malloc(sizeof(char)*strlen(name) + 1);
	new1->con = 0;
	new1->next = 0;
	strcpy(new1->name, name);

	if (graph == 0)
	{
		graph = new1;
	}
	else
	{
		struct vertex *temp = graph;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
	cnt++;
}
struct vertex* findvertexbyname(char *name)
{
	struct vertex *temp = graph;
	while (temp != 0)
	{
		if (strcmp(temp->name, name) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	return 0;
}
void add2edge(char *name1, char *name2, int dist)
{
	struct vertex *cur = findvertexbyname(name1);
	struct edge *new1 = (struct edge*)malloc(sizeof(struct edge));
	new1->name = (char*)malloc(sizeof(char)*strlen(name2) + 1);
	new1->dist = dist;
	new1->next = 0;
	strcpy(new1->name, name2);

	if (cur->con == 0)
	{
		cur->con = new1;
	}
	else
	{
		struct edge *temp = cur->con;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
void addedge(char *name1, char *name2, int dist)
{
	add2edge(name1, name2, dist);
	add2edge(name2, name1, dist);
}
int findsmallest()
{
	int idx = -1;
	int min = 999999;
	for (int i = 0; i < cnt; i++)
	{
		if (dtable[i].dist < min && dtable[i].found == 0)
		{
			idx = i;
			min = dtable[i].dist;
		}
	}
	return idx;
}
int findidxfromtable(char *name)
{
	for (int i = 0; i < cnt; i++)
	{
		if (strcmp(dtable[i].name, name) == 0)
		{
			return i;
		}
	}
	return -1;
}
void showpath(char *name)
{
	int idx = findidxfromtable(name);
	char *src;
	while (1)
	{
		push(dtable[idx].name);
		if (dtable[idx].prev == 0)
		{
			src = dtable[idx].name;
			break;
		}
		idx = findidxfromtable(dtable[idx].prev);
	}
	char *p = pop();
	printf("경로:%s", p);
	while (1)
	{
		p = pop();
		if (p == 0)
		{

			printf("\n");
			return;
		}
		printf("->%s", p);
	}
}
void dodijkstra(char *name1, char *name2)
{
	struct vertex *src = findvertexbyname(name1);
	struct vertex *dst = findvertexbyname(name2);
	if (src == 0 || dst == 0)
	{
		printf("input error\n");
		return;
	}
	dtable = (struct dijkstra*)malloc(sizeof(struct dijkstra)*cnt);
	struct vertex *temp = graph;
	for (int i = 0; i < cnt; i++)
	{
		dtable[i].name = temp->name;
		dtable[i].found = 0;
		dtable[i].dist = 999999;
		dtable[i].prev = 0;
		if (strcmp(dtable[i].name, src->name) == 0)
		{
			dtable[i].dist = 0;
		}
		temp = temp->next;
	}

	while (1)
	{
		int idx = findsmallest();
		if (idx == -1)
		{
			printf("unexpected error\n");
			return;
		}
		dtable[idx].found = 1;
		if (strcmp(dtable[idx].name, dst->name) == 0)
		{
			printf("거리:%d\n", dtable[idx].dist);
			showpath(dtable[idx].name);
			free(dtable);
			return;
		}
		else
		{
			struct edge *cur = findvertexbyname(dtable[idx].name)->con;
			while (cur != 0)
			{
				int idx1 = findidxfromtable(cur->name);
				if (dtable[idx1].found == 0 && dtable[idx1].dist > dtable[idx].dist + cur->dist)
				{
					dtable[idx1].prev = dtable[idx].name;
					dtable[idx1].dist = dtable[idx].dist + cur->dist;
				}
				cur = cur->next;
			}
		}
	}

}
int main()
{
	add2vertex((char*)"DENVER");
	add2vertex((char*)"MADISON");
	add2vertex((char*)"CHICAGO");
	add2vertex((char*)"DESMOINES");
	add2vertex((char*)"STLOUIS");
	add2vertex((char*)"KANSASCITY");
	add2vertex((char*)"OKCITY");
	add2vertex((char*)"LASVEGAS");
	add2vertex((char*)"SALTLAKE");
	add2vertex((char*)"LOSANGELES");
	add2vertex((char*)"TUCSON");
	add2vertex((char*)"DALLAS");
	addedge((char*)"DENVER", (char*)"MADISON", 833);
	addedge((char*)"DENVER", (char*)"DESMOINES", 602);
	addedge((char*)"DENVER", (char*)"LASVEGAS", 615);
	addedge((char*)"DENVER", (char*)"SALTLAKE", 378);
	addedge((char*)"MADISON", (char*)"DESMOINES", 240);
	addedge((char*)"MADISON", (char*)"CHICAGO", 122);
	addedge((char*)"CHICAGO", (char*)"DESMOINES", 301);
	addedge((char*)"CHICAGO", (char*)"STLOUIS", 259);
	addedge((char*)"DESMOINES", (char*)"STLOUIS", 270);
	addedge((char*)"DESMOINES", (char*)"KANSASCITY", 177);
	addedge((char*)"DESMOINES", (char*)"OKCITY", 472);
	addedge((char*)"KANSASCITY", (char*)"STLOUIS", 244);
	addedge((char*)"KANSASCITY", (char*)"OKCITY", 300);
	addedge((char*)"KANSASCITY", (char*)"DALLAS", 454);
	addedge((char*)"OKCITY", (char*)"SALTLAKE", 864);
	addedge((char*)"OKCITY", (char*)"LASVEGAS", 992);
	addedge((char*)"OKCITY", (char*)"TUCSON", 800);
	addedge((char*)"LASVEGAS", (char*)"LOSANGELES", 231);
	addedge((char*)"LASVEGAS", (char*)"DALLAS", 1075);
	addedge((char*)"LOSANGELES", (char*)"SALTLAKE", 581);
	addedge((char*)"LOSANGELES", (char*)"TUCSON", 455);
	addedge((char*)"TUCSON", (char*)"DALLAS", 824);
	while (1)
	{
		char src[30];
		char dst[30];
		printf("출발 도시:");
		scanf("%s", src);
		printf("도착 도시:");
		scanf("%s", dst);
		dodijkstra(src, dst);
	}
	return 0;
}