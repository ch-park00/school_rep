#include <stdio.h>
#include <stdlib.h>
#define Sz 6
//graph구현
struct node
{
	char v;
	struct node *next; //stack(queue)에 사용
	struct node *left; //이 두개는 bst에서 사용(visited구현시)
	struct node *right;
};
struct node *graph[Sz] = { 0 };
//stack 구현
struct node *stack = 0;
//queue 구현
struct node *queue = 0;
//visited 생성
struct node *visited = 0; 

void add2visited(char v) //visited에 새로운 버텍스를 추가
{
	struct node *new1 = (struct node *)malloc(sizeof(struct node));
	new1->v = v;
	new1->left = 0;
	new1->right = 0;

	if (visited == 0)
	{
		visited = new1;
	}
	else
	{
		struct node *temp = visited;
		while (1)
		{
			if (temp->v > v)
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
int checkvisited(char v)
{
	struct node *temp = visited;
	while (temp != 0)
	{
		if (temp->v == v) //찾는 값을 찾았음
		{
			return 1;
		}
		if (temp->v > v)
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;
		}
	}
	return 0; //while문을 돌면서 찾는값을 찾지못함
}
void enqueue(char t) //맨 뒤에 붙임
{
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->v = t;
	new1->next = 0;

	if (queue == 0)
	{
		queue = new1;
	}
	else
	{
		struct node *temp = queue;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
char dequeue() //맨앞에서 데이터 dequeue
{
	if (queue == 0)
	{
		return '-';
	}
	char v = queue->v;
	struct node *temp = queue;
	queue = queue->next;
	free(temp);
	return v;
}
void push(char v)
{
	struct node *new1 = (struct node *)malloc(sizeof(struct node));
	new1->v = v;
	new1->next = 0;

	new1->next = stack; //기존 맨앞에 있던 애를 새로 만든 node와 연결
	stack = new1; //stack의 head를 맨앞으로 이동
	return;
}
char pop()
{
	if (stack == 0)
	{
		return '-'; //리턴할 값이 없다
	}
	else
	{
		struct node *temp = stack;
		char t = stack->v; 
		stack = stack->next;// 스택(헤드)을 뒤로 이동
		free(temp); //return한 노드는 free시켜준다. 안하면 unreferenced space가 된다.
		return t;
	}
}
void addEdgemini(char src, char dst)
{
	int idx = src - 'A';
	struct node *new1 = (struct node *)malloc(sizeof(struct node));
	new1->v = dst;
	new1->next = 0;

	if (graph[idx] == 0)
	{
		graph[idx] = new1;
	}
	else
	{
		struct node *temp = graph[idx];
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
void addEdge(char src, char dst) //edge로 vertex들 연결
{
	addEdgemini(src, dst);
	addEdgemini(dst, src);
}
void performDFS(char t)
{
	//1단계
	push(t);
	//2단계
	while (1)
	{
		char x = pop();
		if (x == '-')
		{
			return;
		}
		if (checkvisited(x) == 1)
		{
			continue;
		}
		else
		{
			printf("---->%c\n", x); //화면에 출력후
			add2visited(x); //visited에 추가
			int idx = x-'A'; //그리고 연결된 vertex들을 stack에 push
			struct node *temp = graph[idx];
			while (temp != 0)
			{
				if (checkvisited(temp->v) == 0)
				{
					push(temp->v);
				}
				temp = temp->next;
			}
		}
	}
}
void performBFS(char t)
{
	//1단계
	enqueue(t);
	//2단계
	while (1)
	{
		char x = dequeue();
		if (x == '-')
		{
			return;
		}
		if (checkvisited(x) == 1)
		{
			continue;
		}
		else
		{
			printf("---->%c\n", x);
			add2visited(x);
			int idx = x - 'A';
			struct node *temp = graph[idx];
			while (temp != 0)
			{
				if (checkvisited(temp->v) == 0)
				{
					enqueue(temp->v);
				}
				temp = temp->next;
			}
		}
	}
}
//BFS 및 DFS를 구현
int main()
{
 	addEdge('A', 'C'); //들어가는 순서가 여기서는 상관없다.하지만 BST로 구현할때는 순서가 중요
	addEdge('C', 'B');
	addEdge('C', 'F');
	addEdge('B', 'E');
	addEdge('D', 'B');
	addEdge('D', 'F');
	printf("DFS:\n");
	performDFS('C'); //
	printf("BFS:\n");
	visited = 0;
	performBFS('C'); //이 두개의 visited는 공용으로 쓰기 때문에 하려면 중간에 visited를 초기화해야한다.
	return 0;
}