#define _CRT_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
struct edge
{
	int v1;
	int v2;
	int weight;
	struct edge *next;
};
struct vertex
{
	int v;
	struct vertex *next;
	struct edge *con;
};
struct visit
{
	int v1;
	struct visit *left;
	struct visit *right;
};
struct dijkstra
{
	int v;
	int found;
	int dist;
	int prev;
};
struct fam
{
	int v;
	int v_fam;
};
struct visit *visited = 0;
struct edge *edges = 0;
struct vertex *vertexes = 0;
struct vertex *stack = 0;
struct vertex *queue = 0;
struct dijkstra *dtable = 0;
struct fam *family = 0;
void push(int v)
{
	struct vertex *new1 = (struct vertex *)malloc(sizeof(struct vertex));
	new1->v = v;
	new1->next = 0;

	new1->next = stack;
	stack = new1;
}
int pop()
{
	if (stack == 0)
	{
		return -1;
	}
	else
	{
		struct vertex *temp = stack;
		int temp1 = temp->v;
		stack = stack->next;
		free(temp);
		return temp1;
	}
}
void enqueue(int v)
{
	struct vertex *new1 = (struct vertex*)malloc(sizeof(struct vertex));
	new1->v = v;
	new1->next = 0;
	if (queue == 0)
	{
		queue = new1;
	}
	else
	{
		struct vertex *temp = queue;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
int dequeue()
{
	if (queue == 0)
	{
		return -1;
	}
	else
	{
		struct vertex *temp = queue;
		int temp1 = temp->v;
		queue = queue->next;
		free(temp);
		return temp1;
	}
}
int isinvertex(int v)
{
	struct vertex *temp = vertexes;
	while (temp != 0)
	{
		if (temp->v == v)
		{
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}
void addvertex(int v)
{
	if (isinvertex(v) == 1)
	{
		return;
	}
	else
	{
		struct vertex *new1 = (struct vertex *)malloc(sizeof(vertex));
		new1->v = v;
		new1->next = 0;
		new1->con = 0;
		if (vertexes == 0)
		{
			vertexes = new1;
		}
		else
		{
			struct vertex *temp = vertexes;
			while (temp->next != 0)
			{
				temp = temp->next;
			}
			temp->next = new1;
		}
	}
}
void addedge(int v1, int v2, int w)
{
	struct edge *new1 = (struct edge*)malloc(sizeof(struct edge));
	new1->v1 = v1;
	new1->v2 = v2;
	new1->weight = w;
	new1->next = 0;

	if (edges == 0)
	{
		edges = new1;
	}
	else
	{
		struct edge *temp = edges;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
void getedgeinfo(FILE *f)
{
	while (1)
	{
		int a, b, c;
		fscanf(f, "%d %d %d", &a, &b, &c);
		if (a == -1 && b == -1 && c==-1)
		{
			return;
		}
		else
		{
			addvertex(a);
			addvertex(b);
			addedge(a, b, c);
		}
	}
}
struct vertex * findvertex(int v)
{
	struct vertex *temp = vertexes;
	while (temp != 0)
	{
		if (temp->v == v)
		{
			return temp;
		}
		temp = temp->next;
	}
}
void addvertexedge(struct vertex *v1, int v2, int w)
{
	struct edge *new1 = (struct edge *)malloc(sizeof(struct edge));
	new1->v2 = v2;
	new1->weight = w;
	new1->next = 0;
	if (v1->con == 0)
	{
		v1->con = new1;
	}
	else
	{
		struct edge *temp = v1->con;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
void add2graph()
{
	struct edge *temp = edges;
	while (temp != 0)
	{
		struct vertex *v1 = findvertex(temp->v1);
		struct vertex *v2 = findvertex(temp->v2);
		addvertexedge(v1, temp->v2, temp->weight);
		addvertexedge(v2, temp->v1, temp->weight);
		temp = temp->next;
	}
}
int isinvisited(int i)
{
	struct visit *temp = visited;
	while (temp != 0)
	{
		if (temp->v1 == i)
		{
			return 1;
		}
		if (temp->v1 > i)
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;
		}
	}
	return 0;
}
void addvisited(int v)
{
	struct visit *new1 = (struct visit*)malloc(sizeof(struct visit));
	new1->v1 = v;
	new1->left = new1->right = 0;

	if (visited == 0)
	{
		visited = new1;
	}
	else
	{
		struct visit *temp = visited;
		while (1)
		{
			if (temp->v1 > v)
			{
				if (temp->left == 0)
				{
					temp->left = new1;
					return;
				}
				temp = temp->left;
			}
			else
			{
				if (temp->right == 0)
				{
					temp->right = new1;
					return;
				}
				temp = temp->right;
			}
		}
	}
}
void runDFS(int v)
{
	int cnt = 0;
	push(v);
	while (1)
	{
		int i = pop();
		if (i == -1)
		{
			printf("question 1 : %d\n", cnt - 1);
			visited = 0;
			return;
		}
		if (isinvisited(i) == 1)
		{
			continue;
		}
		else
		{
			cnt++;
			addvisited(i);
			struct edge *temp = findvertex(i)->con;
			while (temp != 0)
			{
				if (isinvisited(temp->v2) == 0)
				{
					push(temp->v2);
				}
				temp = temp->next;
			}
		}
	}
}
void runBFS(int v)
{
	int cnt = 0;
	enqueue(v);
	while (1)
	{
		int i = dequeue();
		if (i == -1)
		{
			visited = 0;
			printf("question 2: %d\n", cnt - v);
			return;
		}
		if (isinvisited(i) == 1)
		{
			continue;
		}
		else
		{
			cnt = cnt + i;
			addvisited(i);
			struct edge *temp = findvertex(i)->con;
			while (temp != 0)
			{
				if (isinvisited(temp->v2) == 0)
				{
					enqueue(temp->v2);
				}
				temp = temp->next;
			}
		}
	}
}
int howmanyedge()
{
	int cnt = 0;
	struct edge *temp = edges;
	while (temp != 0)
	{
		temp = temp->next;
		cnt++;
	}
	return cnt;
}

int howmanyvertex()
{
	int cnt = 0;
	struct vertex *temp = vertexes;
	while (temp != 0)
	{
		temp = temp->next;
		cnt++;
	}
	return cnt;
}
int findvertexfromtable(int v)
{
	for (int i = 0; i < howmanyvertex(); i++)
	{
		if (dtable[i].v == v)
		{
			return i;
		}
	}
}

int findshortest()
{
	int idx = -1;
	int shortest = 999999;
	for (int i = 0; i < howmanyvertex(); i++)
	{
		if (dtable[i].found == 0 && dtable[i].dist < shortest)
		{
			shortest = dtable[i].dist;
			idx = i;
		}
	}
	return idx;
}
int calculate(int v1, int v2)
{
	int idx = findvertexfromtable(v2);
	int idx1 = findvertexfromtable(v1);
	return (dtable[idx].dist - dtable[idx1].dist);
}
int findfam(int v)
{
	struct vertex *temp = findvertex(v);
	for (int i = 0; i < howmanyvertex(); i++)
	{
		if (family[i].v == v)
		{
			return family[i].v_fam;
		}
	}
}
void changefam(int v1, int v2)//v2의 fam을 v1의 fam으로 변경
{
	struct vertex *temp = findvertex(v1);
	struct vertex *temp1 = findvertex(v2);
	int i = findfam(temp->v);
	int k = findfam(temp1->v);
	for (int j = 0; j < howmanyvertex(); j++)
	{
		if (family[j].v_fam == i)
		{
			family[j].v_fam = k;
		}
	}
}
void runMST(int t)
{
	int i = 0;
	struct edge *mst = (struct edge *)malloc(sizeof(struct edge)*howmanyedge());
	struct edge *temp = edges;
	while (temp != 0)
	{
		mst[i].v1 = temp->v1;
		mst[i].v2 = temp->v2;
		mst[i].weight = temp->weight;
		i++;
		temp = temp->next;
	}
	for (int i = 1; i < howmanyedge(); i++)
	{
		for (int j = 0; j < howmanyedge() - i; j++)
		{
			if (mst[j].weight > mst[j + 1].weight)
			{
				struct edge t = mst[j];
				mst[j] = mst[j + 1];
				mst[j + 1] = t;
			}
		}
	}
	struct vertex *temp1 = vertexes;
	family = (struct fam*)malloc(sizeof(struct fam)*howmanyvertex());
	for (int i = 0; i < howmanyvertex(); i++)
	{
		family[i].v = family[i].v_fam = temp1->v;
		temp1 = temp1->next;
	}
	int ccnt = 0;
	int cccnt = 0;
	for (int i = 0; i < howmanyedge(); i++)
	{
		if (findfam(mst[i].v1) == findfam(mst[i].v2))
		{
			continue;
		}
		else
		{
			cccnt++;
			ccnt = ccnt + mst[i].weight;
			changefam(mst[i].v1, mst[i].v2);
			if (cccnt == howmanyvertex() - 1)
			{
				printf("question 3: %d\n", ccnt);
				break;
			}
		}
	}
}
void rundijkstra(int v1, int v2)
{
	int i = 0;
	dtable = (struct dijkstra *)malloc(sizeof(struct dijkstra)*howmanyvertex());
	struct vertex *temp = vertexes;
	while (temp != 0)
	{
		dtable[i].v = temp->v;
		dtable[i].found = 0;
		dtable[i].dist = 999999;
		dtable[i].prev = 0;
		i++;
		temp = temp->next;
	}
	int idx = findvertexfromtable(v1);
	dtable[idx].dist = 0;
	while (1)
	{
		int temp = findshortest();
		if (temp == -1)
		{
			printf("question 4: %d\n", calculate(v1, v2));
			return;
		}
		else
		{
			dtable[temp].found = 1;
			struct edge *temp1 = findvertex(dtable[temp].v)->con;
			while (temp1 != 0)
			{
				int temp_idx = findvertexfromtable(temp1->v2);
				if (dtable[temp_idx].found == 0 &&
					dtable[temp_idx].dist > dtable[temp].dist + temp1->weight)
				{
					dtable[temp_idx].dist = dtable[temp].dist + temp1->weight;
					dtable[temp_idx].prev = dtable[temp].v;
				}
				temp1 = temp1->next;
			}
		}
	}
}
int main()
{
	int t, t1;
	FILE *f = fopen("data.txt", "rt");
	getedgeinfo(f);
	add2graph();
	fscanf(f, "%d", &t);
	runDFS(t);
	fscanf(f, "%d", &t);
	runBFS(t);
	fscanf(f, "%d", &t);
	runMST(t);
	fscanf(f, "%d %d", &t, &t1);
	rundijkstra(t,t1); //괄호 첫번째 변수가 시작vertex, 두번째가 끝나는 vertex
	fclose(f);
	return 0;
}