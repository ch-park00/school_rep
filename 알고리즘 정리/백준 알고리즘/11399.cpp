#include <stdio.h>
#include <stdlib.h>
int *P = 0;
int sum = 0;

void cal_time(int num)
{
	for (int i = 0; i < num; i++)
	{
		int min = 99999;
		int idx = -1;
		for (int j = 0; j < num; j++)
		{
			if (P[j] < min)
			{
				min = P[j];
				idx = j;
			}
		}
		sum = sum + min * (num - i);
		P[idx] = 99999;
	}
}
int main()
{
	int num;
	scanf("%d", &num);
	P = (int*)malloc(sizeof(int)*num);
	for (int i = 0; i < num; i++)
	{
		int data;
		scanf("%d", &data);
		P[i] = data;
	}
	cal_time(num);
	printf("%d\n", sum);
	return 0;
}