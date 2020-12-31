#include <stdio.h>
#include <stdlib.h>

struct data
{
	int i;
	int j;
	int idx;
};
struct data hash[20][20];
int arr[7] = { 1, 2, 3, 4, 7, 8, 9 };

int hashfunction(int i, int j)
{
	return i + j;
}
void add2hash(int i, int j)
{
	int idx = hashfunction(i, j);
	
	if (hash[idx][0].idx == 0)
	{
		hash[idx][0].i = i;
		hash[idx][0].j = j;
		hash[idx][0].idx = 1;
	}
	else
	{
		int idx1 = hash[idx][0].idx;

		hash[idx][idx1].i = i;
		hash[idx][idx1].j = j;
		hash[idx][0].idx += 1;
	}
}
void print_all()
{
	for (int i = 0; i < 20; i++)
	{
		if (hash[i][0].idx == 0 || hash[i][0].idx == 1)
		{
			continue;
		}
		else
		{
			int tmp = hash[i][0].idx;
			for (int k = 0; k < tmp -1; k++)
			{
				for (int l = k + 1; l < tmp; l++)
				{
					printf("%d + %d ", hash[i][k].i, hash[i][k].j);
					printf("= ");
					printf("%d + %d\n", hash[i][l].i, hash[i][l].j);
				}
			}

		}
	}
}
void do_origin_function()
{
	for (int i = 0; i < 7 - 3; i++)
	{
		for (int j = i + 1; j < 7 - 2; j++)
		{
			for (int k = j + 1; k < 7 - 1; k++)
			{
				for (int l = k + 1; l < 7; l++)
				{
					if (arr[i] + arr[j] == arr[k] + arr[l])
					{
						printf("%d + %d = %d + %d\n", arr[i], arr[j], arr[k], arr[l]);
					}
					if (arr[i] + arr[k] == arr[j] + arr[l])
					{
						printf("%d + %d = %d + %d\n", arr[i], arr[k], arr[j], arr[l]);
					}
					if (arr[i] + arr[l] == arr[j] + arr[k])
					{
						printf("%d + %d = %d + %d\n", arr[i], arr[l], arr[j], arr[k]);
					}
				}
			}
		}
	}
}
int main()
{
	printf("origin function\n");
	do_origin_function();
	for (int i = 0; i < 20; i++)
	{
		hash[i][0].i = 0;
		hash[i][0].j = 0;
		hash[i][0].idx = 0;
	}
	for (int i = 0; i < 7 - 1; i++)
	{
		for (int j = i+1; j < 7; j++)
		{
			add2hash(arr[i], arr[j]);
		}
	}
	printf("hash\n");
	print_all();
	return 0;
}