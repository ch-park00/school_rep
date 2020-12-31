#include <stdio.h>
#include <stdlib.h>
#define SZ 10

int heap[SZ] = { 0,6,3,5,7,10,1,2 };
int heap_point = 0;
void findlocation(int cur, int last)
{
	int left = cur * 2;
	int right = left + 1;
	int big = cur;

	if (heap[big] < heap[left] && left<=last)
	{
		big = left;
	}
	if (heap[big]<heap[right] && right<=last)
	{
		big = right;
	}
	if (big == cur)
	{
		return;
	}
	else
	{
		int tmp = heap[big];
		heap[big] = heap[cur];
		heap[cur] = tmp;
		findlocation(big, last);
	}
}
void heapify()
{
	int cur = heap_point / 2;
	while (cur >= 1)
	{
		findlocation(cur, heap_point);
		cur--;
	}
}
void add2heap(int data)
{
	if (heap_point + 1 > SZ)
	{
		printf("heap is full\n");
		return;
	}
	int cur, parent;
	heap_point++;
	heap[heap_point] = data;
	cur = heap_point;
	parent = cur / 2;
	while (1)
	{
		if (heap[cur] < heap[parent] || parent < 1)
		{
			return;
		}
		else
		{
			int tmp = heap[cur];
			heap[cur] = heap[parent];
			heap[parent] = tmp;
			cur = parent;
			parent = cur / 2;
		}
	}
}
int del_heap()
{
	int ret = heap[1];
	heap[1] = heap[heap_point];
	heap_point--;
	findlocation(1, heap_point);
	return ret;
}
int main() 
{
	heap_point = 7;
	heapify();
	add2heap(30);
	printf("-----------------------\n");
	for (int i = 1; i <= 8; i++)
	{
		printf("%d\n", heap[i]);
	}
	int data = del_heap();
	printf("%d\n", data);
	printf("-----------------------\n");
	for (int i = 1; i <= 7; i++)
	{
		printf("%d\n", heap[i]);
	}
	return 0;
}