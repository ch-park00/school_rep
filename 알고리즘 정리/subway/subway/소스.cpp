#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

struct edge
{
	char *id;
	int dist;
	struct edge *next;
};
struct vertex
{
	char *id;
	char *name;
	char *linenum;
	struct edge *con;
	struct vertex *next;
};
struct dijkstra
{
	char *id;
	int find;
	int dist;
	char *prev;
};
struct node
{
	char *id;
	struct node *next;
};
struct node *stack;
struct vertex *graph = 0;
struct dijkstra *dtable = 0;
int cnt = 0;

void push(char *id)
{
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->id = id;
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
	char *temp1 = temp->id;
	stack = stack->next;
	free(temp);
	return temp1;
}
void add2graph(char *id, char *name, char *linenum)
{
	struct vertex *new1 = (struct vertex*)malloc(sizeof(struct vertex));
	new1->id = (char*)malloc(sizeof(char)*strlen(id) + 1);
	new1->name = (char*)malloc(sizeof(char)*strlen(name) + 1);
	new1->linenum = (char*)malloc(sizeof(char)*strlen(linenum) + 1);
	strcpy(new1->id, id);
	strcpy(new1->name, name);
	strcpy(new1->linenum, linenum);
	new1->next = 0;
	new1->con = 0;
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
struct vertex* findstationbyid(char *id)
{
	struct vertex *temp = graph;
	while (temp != 0)
	{
		if (strcmp(temp->id, id) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	return 0;
}
struct vertex *findstationbyname(char *name)
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
void addedge(char *id1, char *id2, int dist)
{
	struct vertex *cur = findstationbyid(id1);
	struct edge *new1 = (struct edge*)malloc(sizeof(struct edge));
	new1->id = (char*)malloc(sizeof(char)*strlen(id2) + 1);
	new1->dist = dist;
	new1->next = 0;
	strcpy(new1->id, id2);

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
int findsmallestidx()
{
	int idx = -1;
	int min = 999999;
	for (int i = 0; i < cnt; i++)
	{
		if (dtable[i].dist < min && dtable[i].find == 0)
		{
			idx = i;
			min = dtable[i].dist;
		}
	}
	return idx;
}
int findfromtable(char *id)
{
	for (int i = 0; i < cnt; i++)
	{
		if (strcmp(dtable[i].id, id) == 0)
		{
			return i;
		}
	}
}
void showpath(int idx)
{
	int idx1 = idx;
	int dec = 0;
	struct vertex *d_station = findstationbyid(dtable[idx].id);
	struct vertex *s_station;
	while (1)
	{
		push(dtable[idx1].id);
		if (dtable[idx1].prev == 0)
		{
			s_station = findstationbyid(dtable[idx1].id);
			break;
		}
		idx1 = findfromtable(dtable[idx1].prev);
	}
	char prev[20];
	char cur_line[20];
	char prev_line[20];
	while (1)
	{
		char *p = pop();
		if (p == 0)
		{
			return;
		}

		struct vertex *temp = findstationbyid(p);
		if (strcmp(temp->name, prev) == 0)
		{
			if (strcmp(temp->name, s_station->name) == 0 || strcmp(temp->name, d_station->name) == 0)
			{
				strcpy(prev_line, temp->linenum);
				continue;
			}
			else
			{

				if (dec == 1)
				{
					continue;
				}
				else
				{
					dec = 1;
					printf("**È¯½Â");
				}
			}
		}
		else
		{
			if (dec == 1)
			{
				dec = 0;
				printf("%s->%s**\n", prev_line, temp->linenum);
			}
			printf("%s\n", temp->name);
			strcpy(prev, temp->name);
			strcpy(prev_line, temp->linenum);
		}
	}
}
void dodijkstra(char *s_name, char *d_name)
{
	struct vertex *s = findstationbyname(s_name);
	struct vertex *d = findstationbyname(d_name);
	if (s == 0 || d == 0)
	{
		printf("error\n");
		return;
	}
	dtable = (struct dijkstra*)malloc(sizeof(struct dijkstra)*cnt);
	struct vertex *temp = graph;
	for (int i = 0; i < cnt; i++)
	{
		dtable[i].id = temp->id;
		dtable[i].find = 0;
		dtable[i].dist = 999999;
		dtable[i].prev = 0;
		if (strcmp(s->id, temp->id) == 0)
		{
			dtable[i].dist = 0;
		}
		temp = temp->next;
	}
	while (1)
	{
		int idx = findsmallestidx();
		if (idx == -1)
		{
			printf("unexpected error\n");
			return;
		}
		dtable[idx].find = 1;
		if (strcmp(dtable[idx].id, d->id) == 0)
		{
			printf("cur dist:%d\n", dtable[idx].dist);
			showpath(idx);
			free(dtable);
			return;
		}
		struct edge *temp = findstationbyid(dtable[idx].id)->con;
		while (temp != 0)
		{
			int idx1 = findfromtable(temp->id);
			if (dtable[idx1].find == 0 && dtable[idx1].dist > dtable[idx].dist + temp->dist)
			{
				dtable[idx1].dist = dtable[idx].dist + temp->dist;
				dtable[idx1].prev = dtable[idx].id;
			}
			temp = temp->next;
		}
	}
}
int main()
{
	FILE *f = fopen("seoul.txt", "rt");
	char buf[100];
	while (1)
	{
		char id[20];
		char name[30];
		char linenum[20];
		fgets(buf, 99, f);
		if (strcmp(buf, "\n") == 0)
		{
			break;
		}
		sscanf(buf, "%s %s %s", id, name, linenum);
		add2graph(id, name, linenum);
		buf[0] = 0;
	}
	while (!(feof(f)))
	{
		char id1[20];
		char id2[20];
		int dist;
		fgets(buf, 99, f);
		if (buf[0] == 0)
		{
			break;
		}
		sscanf(buf, "%s %s %d", id1, id2, &dist);
		addedge(id1, id2, dist);
		buf[0] = 0;
	}
	fclose(f);
	for (int i = 0; i < cnt; i++)
	{
		struct vertex *cur = graph;
		for (int k = 0; k < i; k++)
		{
			cur = cur->next;
		}
		char *comid;
		char *comname;
		comid = cur->id;
		comname = cur->name;
		cur = cur->next;
		while (cur != 0)
		{
			if (strcmp(comname, cur->name) == 0)
			{
				addedge(comid, cur->id, 0);
				addedge(cur->id, comid, 0);
			}
			cur = cur->next;
		}
	}
	while (1)
	{
		char s[30];
		char d[30];
		printf("Ãâ¹ß ¿ª:");
		scanf("%s", s);
		printf("µµÂø ¿ª:");
		scanf("%s", d);
		dodijkstra(s, d);
	}
	return 0;
}