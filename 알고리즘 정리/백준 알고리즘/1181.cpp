#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
	char data[51];
	int len;
};
struct node heap[20001];
int pointer = 0;

void add2heap(char data[51])
{
	pointer++;
	strcpy(heap[pointer].data, data);
	heap[pointer].len = strlen(data);
	int cur = pointer;
	while (cur > 1)
	{
		int parent = cur / 2;
		if (heap[parent].len < heap[cur].len)
		{
			break;
		}
		else if (heap[parent].len > heap[cur].len)
		{
			struct node tmp = heap[parent];
			heap[parent] = heap[cur];
			heap[cur] = tmp;
			cur = parent;
		}
		else
		{
			int result = strcmp(heap[parent].data, heap[cur].data);
			// (사전상 뒷순서)
			if (result > 0)
			{
				struct node tmp = heap[parent];
				heap[parent] = heap[cur];
				heap[cur] = tmp;
				cur = parent;
			}
			else
			{
				break;
			}
		}
	}
}
void print_all()
{
	int cur;
	char prev[51] = { 0 };
	while (pointer != 0)
	{
		if (strcmp(prev, heap[1].data) != 0)
		{
			printf("%s\n", heap[1].data);
			strcpy(prev, heap[1].data);
		}
		heap[1] = heap[pointer];
		pointer--;
		cur = 1;
		while (cur < pointer)
		{
			int min = cur;
			int left = cur * 2;
			int right = left + 1;

			if (left <= pointer && heap[min].len > heap[left].len)
			{
				min = left;
			}
			else if (left <= pointer && heap[min].len == heap[left].len)
			{
				if (strcmp(heap[min].data, heap[left].data) > 0)
				{
					min = left;
				}
			}
			if (right <= pointer && heap[min].len > heap[right].len)
			{
				min = right;
			}
			else if (right <= pointer && heap[min].len == heap[right].len)
			{
				if (strcmp(heap[min].data, heap[right].data) > 0)
				{
					min = right;
				}
			}

			if (min == cur)
			{
				break;
			}
			else
			{
				struct node tmp = heap[min];
				heap[min] = heap[cur];
				heap[cur] = tmp;
				cur = min;
			}
		}
	}
}
int main()
{
	int num;
	scanf("%d", &num);
	for (int i = 0; i < num; i++)
	{
		char tmp[51];
		scanf("%s", tmp);
		add2heap(tmp);
	}
	print_all();
	return 0;
}