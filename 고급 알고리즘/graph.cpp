#include <stdio.h>
#include <stdlib.h>
struct vertex
{
	int data;
	struct vertex *next;
};
//전역변수는 값이 0으로 초기화
struct vertex graph1[4];
int graph[4][4] = { 0 };

void addEdge(int src, int dst)
{
	graph[src][dst] = 1;
	graph[dst][src] = 1;

	//SLL 이용
	struct vertex *new1 = (struct vertex*)malloc(sizeof(struct vertex));
	
	struct vertex *new2 = (struct vertex*)malloc(sizeof(struct vertex));
	new1->data = dst;
	new1->next = 0;
	new2->data = src;
	new1->next = 0;

	if (graph1[src].next == 0)
	{
		graph1[src].next = new1;
	}
	else
	{
		struct vertex *tmp = graph1[src].next;
		while (tmp->next != 0)
		{
			tmp = tmp->next;
		}
		tmp->next = new1;
	}
	if (graph1[dst].next == 0)
	{
		graph1[dst].next = new2;
	}
	else
	{
		struct vertex *tmp = graph1[dst].next;
		while (tmp->next != 0)
		{
			tmp = tmp->next;
		}
		tmp->next = new2;
	}


}
int main()
{
	//1->0, 0->1
	//addEdge(0, 1);
	//addEdge(0, 2);
	unsigned int i = 515;
	unsigned char c = 276;
	unsigned char *p = (unsigned char*)&i;
	printf("%d\n",*p);
	printf("%x %x\n", p, &i);
	printf("%d\n", i);
	*p = *p;
	printf("%x %x\n", p, &i);
	printf("%d\n", i);
	return 0;
}