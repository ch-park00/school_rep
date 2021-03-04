#include <stdio.h>
#include <stdlib.h>
//1753 오답
#if 0
#define max_size 9999999
struct edge
{
	int ver;
	int weight;
	struct edge *next;
};
struct vertex
{
	int ver;
	struct edge *con;
};
struct dijkstra
{
	int ver;
	int weight;
	int prev;
};
struct vertex *graph = 0;
struct dijkstra *table = 0;
struct dijkstra *heap = 0;
int top = 0;
int ver_num, edge_num;
int start_ver = 0;
void add2Edge(int src, int dst, int weight)
{
	struct edge *new1 = (struct edge*)malloc(sizeof(struct edge));
	new1->ver = dst;
	new1->weight = weight;
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
void add2Heap(struct dijkstra data)
{
	if (top > edge_num - 1)	return;
	top++;
	heap[top] = data;
	int cur = top;
	while (1)
	{
		int parent = cur / 2;
		if (parent<1 || heap[parent].weight>heap[cur].weight)	break;
		else {
			struct dijkstra tmp = heap[parent];
			heap[parent] = heap[cur];
			heap[cur] = tmp;
			cur = parent;
		}
	}
}
int pop_from_heap()
{
	if (top == 0)	return -1;
	int ret = heap[1].ver - 1;
	heap[1] = heap[top];
	top--;
	int cur = 1;
	while (1)
	{
		int min, left, right;
		min = cur;
		left = min * 2;
		right = left + 1;
		if (left <= top && heap[min].weight > heap[left].weight)
		{
			min = left;
		}
		if (right <= top && heap[min].weight > heap[right].weight)
		{
			min = right;
		}
		if (min == cur)	break;
		else {
			struct dijkstra tmp = heap[cur];
			heap[cur] = heap[min];
			heap[min] = tmp;
			cur = min;
		}
	}
	return ret;
}
void fix_table(int index)
{
	struct edge *cur = graph[index].con;
	while (cur != 0)
	{
		if (table[cur->ver - 1].weight > table[index].weight + cur->weight)
		{
			table[cur->ver - 1].weight = table[index].weight + cur->weight;
			table[cur->ver - 1].prev = index + 1;
			add2Heap(table[cur->ver - 1]);
		}
		cur = cur->next;
	}
}
void print_result()
{
	for (int i = 0; i < ver_num; i++)
	{
		if (table[i].weight == max_size)
		{
			printf("INF\n");
		}
		else
		{
			printf("%d\n", table[i].weight);
		}
	}
}
void do_dijkstra(int ver_)
{
	table = (struct dijkstra*)malloc(sizeof(struct dijkstra)*ver_num);
	heap = (struct dijkstra*)malloc(sizeof(struct dijkstra)*edge_num);
	heap[0] = { -1,-1,-1 };
	for (int i = 0; i < ver_num; i++)
	{
		table[i].ver = i + 1;
		table[i].prev = 0;
		table[i].weight = max_size;
	}
	table[ver_ - 1].weight = 0;
	add2Heap(table[ver_ - 1]);
	while (1)
	{
		int idx = pop_from_heap();
		if (idx == -1)	break;
		
		fix_table(idx);
	}
	print_result();
}
int main()
{
	scanf("%d %d", &ver_num, &edge_num);
	graph = (struct vertex*)malloc(sizeof(struct vertex)*ver_num);
	for (int i = 0; i < ver_num; i++)
	{
		graph[i].ver = i + 1;
		graph[i].con = 0;
	}
	scanf("%d", &start_ver);
	for (int i = 0; i < edge_num; i++)
	{
		int src, dst, w;
		scanf("%d %d %d", &src, &dst, &w);
		add2Edge(src, dst, w);
	}
	do_dijkstra(start_ver);
	return 0;
}
#endif

//1753 정답
#if 0
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

#endif

//1991 정답
#if 0
int num, last_idx;
char root[300] = { 0 };
int findidx(char data)
{
	for (int i = 1; i < last_idx; i++)
	{
		if (root[i] == data)
		{
			return i;
		}
	}
	return -1;
}
void add2bst(char root_, char left_, char right_)
{
	if (root[1] == 0)
	{
		root[1] = root_;
		root[2] = left_;
		root[3] = right_;
		last_idx = 3;
	}
	else
	{
		int idx = findidx(root_);
		if (idx == -1)	return;
		
		root[idx * 2] = left_;
		root[idx * 2 + 1] = right_;
		last_idx = idx * 2 + 1;
	}
}
void do_preorder(int index)
{
	if (index > last_idx || root[index] == '.')	return;
	printf("%c", root[index]);
	do_preorder(index * 2);
	do_preorder(index * 2 + 1);
}

void do_inorder(int index)
{

	if (index > last_idx || root[index] == '.')	return;
	do_inorder(index * 2);
	printf("%c", root[index]);
	do_inorder(index * 2 + 1);
}
void do_postorder(int index)
{
	if (index > last_idx || root[index] == '.')	return;
	do_postorder(index * 2);
	do_postorder(index * 2 + 1);
	printf("%c", root[index]);
}
void print_result(int start)
{
	do_preorder(start);
	printf("\n");

	do_inorder(start);
	printf("\n");

	do_postorder(start);
}
int main()
{
	scanf("%d", &num);
	getchar();
	
	for (int i = 0; i < num; i++)
	{
		char a, b, c;
		scanf("%c %c %c", &a, &b, &c);
		getchar();
		add2bst(a, b, c);
	}
	for (int i = 0; i < 16; i++)
	{
		printf("%c\n", root[i]);
	}
	print_result(1);
	return 0;
}
#endif

//1016
#if 0
int *is_it;
void do_function(int min_, int max_)
{
	int cnt = 0;
	int num = 2;
	int idx = 0;
	while (1)
	{
		if (num*num > max_)	break;

		int idx = min_ / (num*num) ;
		int tmp = (min_) % (num*num);
		if (tmp != 0)
		{
			idx = idx + (num*num)-tmp;
		}
		if (is_it[idx] == 0)
		{
			while (1)
			{
				if (idx >= max_ - min_)	break;
				is_it[idx] = 1;
				idx = idx + (num*num);
			}
		}
		num++;
	}
	for (int i = 0; i <= max_ - min_; i++)
	{
		if (is_it[i] == 0)
		{
			cnt++;
		}
	}
	printf("%d\n", cnt);
}
int main()
{
	int min, max;
	scanf("%d %d", &min, &max);
	is_it = (int*)malloc((max - min +10) * 4);
	for (int i = 0; i <= max - min; i++)
	{
		is_it[i] = 0;
	}
	do_function(min, max);
	return 0;
}
#endif

//2957번
#if 1

struct node
{
	int idx;
	int data;
	struct node* next;
};
struct node** root = 0;
int cnt = 0;
struct node* find_node(int layer, int idx)
{
	struct node *cur = root[layer];
	if (cur == 0)
	{
		return 0;
	}
	while (cur != 0)
	{
		if (cur->idx == idx)
		{
			return cur;
		}
		cur = cur->next;
	}
	return 0;
}
void add2root(struct node *new1, int layer)
{
	struct node *cur = root[layer];
	if (cur == 0)
	{
		root[layer] = new1;
		return;
	}
	while (cur->next != 0)	cur = cur->next;
	cur->next = new1;
}
void add2bst(int data)
{
	if (root[0] == 0)
	{
		root[0] = (struct node*)malloc(sizeof(struct node));
		root[0]->idx = 1;
		root[0]->data = data;
		root[0]->next = 0;
		return;
	}
	else
	{
		cnt++;
		int layer = 0;
		int index = 1;
		while (1)
		{
			struct node *cur = find_node(layer, index);
			if (cur == 0)
			{
				cnt--;
				struct node *new1 = (struct node *)malloc(sizeof(struct node));
				new1->data = data;
				new1->idx = index;
				new1->next = 0;
				add2root(new1, layer);
				return;
			}
			if (cur->data > data)
			{
				layer++;
				index = index * 2;
			}
			else
			{
				layer++;
				index = index * 2 + 1;
			}
			cnt++;
		}
	}
}
int main()
{
	int num;
	scanf("%d", &num);
	root = (struct node**)calloc(num, sizeof(struct node*));
	for (int i = 0; i < num; i++)
	{
		int data;
		scanf("%d", &data);
		add2bst(data);
		printf("**%d**\n", cnt);
	}
	return 0;
}
#endif