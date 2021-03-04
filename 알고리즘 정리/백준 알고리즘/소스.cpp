#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#if 0
int main()
{
	int t;
	int x1, y1, r1, x2, r2, y2;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		scanf("%d %d %d %d %d %d", &x1, &y1, &r1, &x2, &y2, &r2);
		double tmp = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
		if (x1 == x2 && y1 == y2)
		{
			if (r1 == r2)
			{
				printf("-1\n");
			}
			else
			{
				printf("0\n");
			}
		}
		else
		{
			if (abs(r1 - r2) < i && i < r1 + r2)
			{
				printf("2\n");
			}
			else if (abs(r1 - r2) == i || r1 + r2 == i)
			{
				printf("-1\n");
			}
			else
			{
				printf("0\n");
			}
		}
	}
	return 0;
}
#endif
#if 0
int zero = 0;
int one = 0;
void fibonacci(int n) {
	int last, cur, return_val;
	cur = 1;
	return_val = 0;
	for (int i = 0; i <= n; i++)
	{
		last = cur;
		cur = return_val;
		return_val = last + cur;
	}
	printf("%d %d\n", last, cur);
}
int main()
{
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		int data;
		scanf("%d", &data);
		fibonacci(data);
		zero = one = 0;
	}
	return 0;
}
#endif

#if 0
struct node
{
	int data;
	struct node *left;
	struct node* right;
};
struct node *root = 0;
struct node *cur = 0;
struct node *prev = 0;
void add2bst(int data_)
{
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->data = data_;
	new1->left = new1->right = 0;

	if (root == 0)
	{
		root = cur = new1;
		return;
	}
	else
	{
		if (cur->data > data_)
		{
			cur->left = new1;
			prev = cur;
			cur = new1;

		}
		else
		{
			if (prev->right == 0)
			{
				prev->right = new1;
				cur = new1;
			}
			else
			{
				struct node *tmp = root;
				while (1)
				{
					if (tmp->left == prev || tmp->right == prev)	break;
					if (tmp->data > prev->data)
					{
						tmp = tmp->left;
					}
					else
					{
						tmp = tmp->right;
					}
				}

			}
		}
	}
}
void postorder(struct node *cur)
{
	if (cur == 0)	return;
	postorder(cur->left);
	postorder(cur->right);
	printf("%d\n", cur->data);
}
int main()
{
	int input;
	scanf("%d", &input);
	add2bst(input);
	while (scanf("%d", &input) != EOF)
	{
		add2bst(input);
	}
	postorder(root);
	return 0;
}
#endif

#if 1
#define max_size 9999999
struct edge
{
	int ver;
	int weight;
	struct edge* next;
};
struct node
{
	int vertex;
	struct edge* con;
};
struct dijkstra
{
	int ver;
	int weight;
	int prev;
};
struct node* graph = 0;
struct dijkstra* table = 0;
struct dijkstra* heap = 0;
int heap_point = 0;
int num1, num2;
int *visited = 0;
int already_exist(int ver, int data, int weight)
{
	struct edge* cur = graph[ver].con;
	while (cur != 0)
	{
		if (cur->ver == data)
		{
			if (cur->weight > weight)
			{
				cur->weight = weight;
			}
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}
void addEdge(int src, int dst, int weight)
{
	int idx = src - 1;
	if (already_exist(idx, dst, weight) == 1)	return;
	struct edge* new1 = (struct edge*)malloc(sizeof(struct edge));

	new1->ver = dst;
	new1->next = 0;
	new1->weight = weight;

	if (graph[idx].con == 0)
	{
		graph[idx].con = new1;
	}
	else
	{
		struct edge* cur = graph[idx].con;
		while (cur->next != 0)
		{
			cur = cur->next;
		}
		cur->next = new1;
	}
}
void add2heap(struct dijkstra data)
{
	int cur, parent;
	heap_point++;
	heap[heap_point] = data;
	cur = heap_point;
	while (1)
	{
		parent = cur / 2;
		if (parent<1 || heap[cur].weight>heap[parent].weight)	break;
		else {
			struct dijkstra tmp = heap[parent];
			heap[parent] = heap[cur];
			heap[cur] = tmp;
			cur = parent;
		}
	}
}
int pop_heap()
{
	if (heap_point == 0)	return -1;
	struct dijkstra ret = heap[1];
	int cur = 1;
	heap[1] = heap[heap_point];
	heap_point--;
	while (1)
	{
		int min = cur;
		int left = cur * 2;
		int right = left + 1;
		if (left <= heap_point && heap[left].weight < heap[min].weight)
		{
			min = left;
		}
		if (right <= heap_point && heap[right].weight < heap[min].weight)
		{
			min = right;
		}
		if (min == cur)	break;
		else {
			struct dijkstra tmp = heap[min];
			heap[min] = heap[cur];
			heap[cur] = tmp;
			cur = min;
		}
	}
	return ret.ver - 1;
}
void fix_table(int idx)
{
	struct edge* cur = graph[idx].con;
	while (cur != 0)
	{
		int table_idx = cur->ver - 1;
		if (table[table_idx].weight > table[idx].weight + cur->weight)
		{
			table[table_idx].weight = table[idx].weight + cur->weight;
			table[table_idx].prev = idx + 1;
			add2heap(table[table_idx]);
		}
		cur = cur->next;
	}
}
void print_result()
{
	for (int i = 0; i < num1; i++)
	{
		if (table[i].weight == max_size) {
			printf("INF\n");
		}
		else {
			printf("%d\n", table[i].weight);
		}
	}
}
void do_dijkstra(int src)
{
	table = (struct dijkstra*)malloc(sizeof(struct dijkstra) * num1);
	heap = (struct dijkstra*)malloc(sizeof(struct dijkstra) * num2);
	visited = (int*)malloc(sizeof(int)*num1);
	
	for (int i = 0; i < num1; i++)
	{
		table[i].ver = i + 1;
		table[i].prev = 0;
		table[i].weight = max_size;
		visited[i] = 0;
	}
	table[src - 1].weight = 0;
	add2heap(table[src - 1]);
	while (1)
	{
		int idx = pop_heap();
		if (idx == -1)	break;
		if (visited[idx] == 1)	continue;
		else
		{
			visited[idx] = 1;
			fix_table(idx);
		}
	}
	print_result();
}
int main()
{
	int start;
	scanf("%d %d", &num1, &num2);
	graph = (struct node*)malloc(sizeof(struct node) * num1);
	for (int i = 0; i < num1; i++)
	{
		graph[i].vertex = i + 1;
		graph[i].con = 0;
	}
	scanf("%d", &start);
	for (int i = 0; i < num2; i++)
	{
		int src, dst, w;
		scanf("%d %d %d", &src, &dst, &w);
		addEdge(src, dst, w);
	}
	do_dijkstra(start);
	return 0;
}
#endif