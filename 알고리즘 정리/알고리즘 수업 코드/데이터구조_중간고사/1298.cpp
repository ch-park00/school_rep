#include <stdio.h>
#include <stdlib.h>
int heap[100] = { 0 };
void setting(int i,int a)
{
	int big = i;
	int left = i*2;
	int right = i * 2 + 1;
	if (heap[big] < heap[left] && left<a)
	{
		big = left;
	}
	if (heap[big] < heap[right] && right < a)
	{
		big = right;
	}
	if (big == i)
	{
		return;
	}
	else
	{
		int temp = heap[big];
		heap[big] = heap[i];
		heap[i] = temp;
		setting(big, a);
	}
}
void heapify(int a)
{
	int i = a / 2;
	while (1)
	{
		if (i == 0)
		{
			break;
		}
		setting(i,a);
		i--;
	}
}
void removeroot(int i)
{
	int temp = heap[i];
	heap[1] = temp;
	setting(1, i - 1);
}
void main()
{
	int i = 0;
	int a;
	int b;
	scanf("%d", &a);
	for (i = 1; i <= a; i++)
	{
		scanf("%d", &heap[i]);
		heapify(a);
	}
	scanf("%d", &b);
	for (i = 0; i < b; i++)
	{
		removeroot(a-i);
	}
	if ((a - b) < 3)
	{
		printf("none");
	}
	else
	{
		printf("%d", heap[3]);
	}
}