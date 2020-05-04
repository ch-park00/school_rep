#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define Sz 5
int data[Sz];

void bubble_sort(int* data)
{
	for (int i = 0; i < Sz - 1; i++)
	{
		for (int j = 0; j < Sz - i - 1; j++)
		{
			if (data[j] > data[j + 1])
			{
				int tmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = tmp;
			}
		}
	}
}
void selection_sort(int* data)
{
	for (int i = 0; i < Sz - 1; i++)
	{
		for (int j = Sz - 2; j >= i; j--)
		{
			if (data[j] > data[j + 1])
			{
				int tmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = tmp;
			}
		}
	}
}
void q_sort(int* data, int p, int L, int R)
{
	int l = L;
	int r = R;
	if (p >= R)	return;
	while (1)
	{
		if (data[p] < data[l] || l >= R)
		{
			break;
		}
		l++;
	}
	while (1)
	{
		if (data[p] < data[r])
		{
			break;
		}
		r--;
	}
	if (l < r)
	{
		int temp = data[l];
		data[l] = data[r];
		data[r] = temp;
	}
	else if (l == r)
	{
		int temp = p;
		while (temp < r)
		{
			int tmp = data[temp];
			data[temp] = data[temp + 1];
			data[temp + 1] = tmp;
		}
		q_sort(data, p, p + 1, R - 1);
	}
	else
	{
		int temp = data[p];
		data[p] = data[r];
		data[r] = temp;
		q_sort(data, p, p + 1, r - 1);
		q_sort(data, l, l + 1, R);
	}
}

int main()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < Sz; i++)
	{
		data[i] = rand();
		printf("%d\n", data[i]);
	}
	//bubble_sort(data); 
	//selection_sort(data);
	q_sort(data, 0, 1, Sz - 1);
	printf("--------------\n");
	for (int i = 0; i < Sz; i++)
	{
		printf("%d\n", data[i]);
	}
	return 0;
}