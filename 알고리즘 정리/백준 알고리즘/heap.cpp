#include <stdio.h>
// MAX Heap ±¸Çö
#define Sz 30
#define root 1
int heap[Sz] = { 0, 3,8,23,213,21,11,42 };
int heap_size = 7;

void findLocation(int cur_)
{
	int cur = cur_;
	while (1)
	{
		int left = cur * 2;
		int right = left + 1;
		int big = cur;

		if (left <= heap_size && heap[left] > heap[big])	big = left;
		if (right <= heap_size && heap[right] > heap[big])	big = right;
		
		if (cur == big)	return;
		else
		{
			int tmp = heap[big];
			heap[big] = heap[cur];
			heap[cur] = tmp;
			cur = big;
		}
	}
}
void heapify()
{
	int cur = heap_size / 2;
	while (cur >= 1)
	{
		findLocation(cur);
		cur--;
	}
}
void add_data(int data_)
{
	heap_size++;
	int cur = heap_size;
	heap[cur] = data_;
	while (1)
	{
		int parent = cur / 2;
		if (parent<1 || heap[parent]>heap[cur])	return;
		else
		{
			int tmp = heap[cur];
			heap[cur] = heap[parent];
			heap[parent] = tmp;
			cur = parent;
		}
	}
}
int del_data()
{
	int return_val = heap[1];
	heap[1] = heap[heap_size];
	heap_size--;
	findLocation(1);
	return return_val;
}
void show_heap()
{
	for (int i = 1; i <= heap_size; i++)	printf("%d\n", heap[i]);
}
int main()
{
	heapify();
	show_heap();
	add_data(17);
	printf("----------------\n");
	show_heap();
	printf("del data:%d\n-------------\n", del_data());
	show_heap();
	return 0;
}