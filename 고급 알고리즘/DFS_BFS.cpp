#include <stdio.h>
#include <stdlib.h>
#define vertex_num 5
struct vertex
{
	int data;
	struct vertex *next;
};
struct vertex *graph[vertex_num];
//DFS 시 사용
int stack[10];
int top = -1;
//vertex 방문여부 표시 배열
int visited[vertex_num] = { 0 };
//BFS 시 사용
int queue[10] = { 0 };
int front = 0;
int rear = 0;
void push(int data)
{
	if (top >= 9)
	{
		printf("stack is full\n"); 
		return;
	}
	top++;
	stack[top] = data;
}
int pop()
{
	if (top == -1)
	{
		printf("stack is empty\n");
		return -999;
	}
	top--;
	return stack[top + 1];
}


void enqueue(int data)
{
	if ((rear + 1) % 10 == front)
	{
		printf("queue is full\n");
		return;
	}
	queue[rear] = data;
	rear = (rear + 1) % 10;
}
int dequeue()
{
	if (front == rear)
	{
		printf("queue is empty\n");
		return -999;
	}
	int ret = queue[front];
	front = (front + 1) % 10;
	return ret;
}
void addedge(int src, int dst)
{
	struct vertex *new1 = (struct vertex*)malloc(sizeof(struct vertex));
	new1->data = dst;
	new1->next = 0;
	int idx = src;
	if (graph[idx] == 0)
	{
		graph[idx] = new1;
	}
	else
	{
		struct vertex *tmp = graph[idx];
		while (tmp->next != 0)	tmp = tmp->next;
		tmp->next = new1;
	}
}
void add2Edge(int src, int dst)
{
	addedge(src, dst);
	addedge(dst, src);
}
int find_Next(int vertex)
{
	struct vertex *cur = graph[vertex];
	while (cur != 0)
	{
		if (visited[cur->data] == 0)
		{
			return cur->data;
		}
		cur = cur->next;
	}
	return -1;
}
void do_DFS(int start_vetex)
{
	push(start_vetex);
	
	while (1) {
		if (top == -1)
		{
			return;
		}
		int next = -1;
		next = find_Next(stack[top]);

		if (next == -1)
		{
			next=pop();
		}
		else
		{
			printf("visit %d\n", next);
			visited[next] = 1;
			push(next);
		}
	}
}
void do_BFS(int start_vertex)
{
	enqueue(start_vertex);
	while (1)
	{
		if (front == rear)
		{
			return;
		}
		int k = dequeue();
		if (visited[k] == 0)
		{
			visited[k] = 1;
			printf("visit %d\n", k);
			struct vertex *cur = graph[k];
			while (cur != 0)
			{
				if (visited[cur->data] == 0)
				{
					enqueue(cur->data);
				}
				cur = cur->next;
			}
		}
	}
}
int main()
{
	add2Edge(0, 1);
	add2Edge(0, 2);
	add2Edge(0, 4);
	add2Edge(1, 2);
	add2Edge(2, 3);
	add2Edge(2, 4);
	add2Edge(3, 4);

	do_DFS(1);
	//0-1-2-4-3

	//do_BFS(0);
}