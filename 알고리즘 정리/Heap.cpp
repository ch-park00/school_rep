#include <stdio.h>
// MAX Heap 구현
#define Sz 30
#define root 1
int heap[Sz] = { 0, 3,8,23,213,21,11,42 };
int heap_size = 7;

// 현재 내 노드와 child 노드를 비교해 바꿔야 하는 값이 있는지 검사하고 바꾼다.
// 이 때, 바꿀 경우에는 바꾼 후에 아래 쪽에서도 바꿔야 하는 경우가 생길 수 있으므로 
// 바꾼 아래쪽도 검사하는 과정이 있다.
void findLocation(int cur)
{
	int left = cur * 2;
	int right = left + 1;
	int big = cur;
	if (left <= heap_size && heap[big] < heap[left]) {
		big = left;
	}
	if (right <= heap_size && heap[big] < heap[right]) {
		big = right;
	}
	if (big == cur)	return;
	else
	{
		int tmp = heap[cur];
		heap[cur] = heap[big];
		heap[big] = tmp;
		findLocation(big);
	}
}
// 현재 heap 배열에 max heap에 맞게 변환
void heapify()
{
	int cur = heap_size / 2;
	while (1)
	{
		if (cur < 1)	break;
		findLocation(cur);
		cur--;
	}
}
void add2heap(int data)
{
	int parent;
	int cur;
	heap_size++;
	parent = heap_size / 2;
	cur = heap_size;
	heap[heap_size] = data;
	while (1)
	{
		if (parent < 1)	return;
		if (heap[cur] < heap[parent])	return;
		else
		{
			int tmp = heap[cur];
			heap[cur] = heap[parent];
			heap[parent] = tmp;
			cur = parent;
			parent = parent / 2;
		}
	}
}

int del_root()
{
	int max = heap[root];
	heap[root] = heap[heap_size];
	heap_size--;
	findLocation(root);
	return max;
}
int main()
{
	int max = -1;
	heapify();
	for (int i = 1; i <= heap_size; i++)
	{
		printf("%d\n", heap[i]);
	}
	add2heap(111);
	printf("---------------\n");
	for (int i = 1; i <= heap_size; i++)
	{
		printf("%d\n", heap[i]);

	}
	max = del_root();
	printf("max num:%d\n", max);
	for (int i = 1; i <= heap_size; i++)
	{
		printf("%d\n", heap[i]);
	}
	return 0;
}