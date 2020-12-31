#include <stdio.h>

int arr[10] = { 31,24,56,1,4,10,6,76,87,30 };
void bubble()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9 - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
		for (int i = 0; i < 9; i++)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
	}
}
void selection()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 8; j >= 0+i; j--)
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
		for (int i = 0; i < 9; i++)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
	}
}
void insertion()
{
	for (int i = 1; i < 9; i++)
	{
		int j = i;
		while ((j - 1) >= 0) {
			if (arr[j - 1] > arr[j])
			{
				int tmp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = tmp;
				j--;
			}
			else
			{
				break;
			}
		}
		for (int i = 0; i < 9; i++)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
	}
}
void q_sort(int pivot, int left, int right)
{
	if (left >= right)
	{
		printf("%d %d\n", left, right);
		return;
	}
	int P = arr[pivot];
	int L = left;
	int R = right;
	while (1)
	{
		while (1)
		{
			if (arr[L] > P || L >= right)
			{
				break;
			}
			L++;
		}
		while (1)
		{
			if (arr[R] < P || R <= left)
			{
				break;
			}
			R--;
		}
		if (L >= R)
		{
			int tmp = arr[pivot];
			arr[pivot] = arr[R];
			arr[R] = tmp;
			q_sort(pivot, left, R - 1);
			q_sort(R + 1, R + 2, right);
			return;
		}
		else
		{
			int tmp = arr[L];
			arr[L] = arr[R];
			arr[R] = tmp;
		}
	}
}

int main()
{
	//bubble();
	//selection();
	//insertion();
	q_sort(0, 1, 9);
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", arr[i]);
	}
	return 0;
}