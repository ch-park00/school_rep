#include <stdio.h>
#include <stdlib.h>
# if 0
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
#endif
#if 0
struct node
{
	int data;
	struct node *next;
};
struct node *head = 0;
int flag = 0;
void add2SLL(int i)
{
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->data = i;
	new1->next = 0;

	if (head == 0)
	{
		head = new1;
	}
	else
	{
		struct node *tmp = head;
		while (tmp->next != 0)
		{
			tmp = tmp->next;
		}
		tmp->next = new1;
	}
}
void init_SLL(int n)
{
	for (int i = 1; i <= n; i++)
	{
		add2SLL(i);
	}
}
void del_node(int k)
{
	struct node *tmp = head;
	if (k == 0)
	{
		head = head->next;
		if (flag == 0)
		{
			printf("%d,", tmp->data);
			flag = 1;
		}
		else
		{
			printf(" %d,", tmp->data);
		}
		free(tmp);
		return;
	}
	for (int i = 0; i < k - 1; i++)
	{
		if (tmp->next == 0)
		{
			tmp = head;
		}
		else
		{
			tmp = tmp->next;
		}
	}
	if (tmp->next == 0)
	{
		tmp = head;
		head = head->next;
		if (flag == 0)
		{
			printf("%d,", tmp->data);
			flag = 1;
		}
		else
		{
			printf(" %d,", tmp->data);
		}
		
		free(tmp);
	}
	else
	{
		if (tmp->next->next == 0)
		{
			struct node *tmp1 = tmp->next;
			tmp->next = 0;
			if (flag == 0)
			{
				printf("%d,", tmp1->data);
				flag = 1;
			}
			else
			{
				printf(" %d,", tmp1->data);
			}
			
			free(tmp1);
		}
		else
		{
			struct node *tmp1 = head;
			struct node *tmp2 = tmp->next;
			while (tmp1->next != 0)
			{
				tmp1 = tmp1->next;
			}
			tmp->next = 0;
			tmp1->next = head;
			head = tmp2->next;
			if (flag == 0)
			{
				printf("%d,", tmp2->data);
				flag = 1;
			}
			else
			{
				printf(" %d,", tmp2->data);
			}
			
			free(tmp2);
		}
	}
}
void do_yo(int k)
{
	printf("<");
	while (1)
	{
		if (head->next == 0)
		{
			if (flag == 0)
			{
				printf("%d>", head->data);
			}
			else
			{
				printf(" %d>", head->data);
			}
			
			return;
		}
		else
		{
			del_node(k - 1);
		}
	}
}
int main()
{
	int n, k;
	scanf("%d %d", &n, &k);
	init_SLL(n);

	do_yo(k);
	return 0;
}
#endif
struct node
{
	int data;
	struct node *next;
};
struct node *head = 0;
void add2sll(int N)
{
	struct node *prev;
	for (int i = 1; i <= N; i++)
	{
		struct node *new1 = (struct node*)malloc(sizeof(struct node));
		new1->data = i;
		new1->next = 0;

		if (head == 0)
		{
			head = new1;
			prev = head;
		}
		else
		{
			prev->next = new1;
			prev = new1;
		}
		new1->next = head;
	}
}
void delnode(int K)
{
	struct node *tmp = head;
	struct node *prev = 0;
	while (tmp != prev)
	{
		for (int i = 0; i < K; i++);
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == head)
			head = tmp->next;
		prev->next = tmp->next;
		printf("%d, ", tmp->data);
		free(tmp);
		tmp = prev->next;
	}
	printf("%d>", tmp->data);
}
int main()
{
	int N, K;
	struct node *p = head;
	scanf("%d %d", &N, &K);
	add2sll(N);
	struct node *tmp = head;
	for (int i = 0; i < 7; i++)
	{
		printf("%d", tmp->data);
		tmp = tmp->next;
	}
	printf("<");
	delnode(K);
	return 0;
}