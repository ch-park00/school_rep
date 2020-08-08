#include <stdio.h>
#include <stdlib.h>
int sum[125751] = { 0 };
int cur[125751];
void cal_sum(int cur_layer)
{
	int num = (cur_layer*(cur_layer + 1)) / 2;
	for (int i = num; i < num + (cur_layer + 1); i++)
	{
		if (i == num)
		{
			sum[i] = cur[i] + sum[i - cur_layer];
		}
		else if (i == num + cur_layer)
		{
			sum[i] = cur[i] + sum[num - 1];
		}
		else
		{
			int num1 = cur[i] + sum[i - cur_layer -1];
			int num2 = cur[i] + sum[i - cur_layer];
			if (num1 > num2)
			{
				sum[i] = num1;
			}
			else
			{
				sum[i] = num2;
			}
		}
	}
}
int main()
{
	int max = 0;
	int idx = 0;
	int num;
	scanf("%d", &num);
	scanf("%d", &cur[0]);
	sum[0] = cur[0];
	for (int i = 1; i < num; i++)
	{
		int j;
		for (j = 0; j < 1 + i; j++)
		{
			int tmp;
			scanf("%d", &tmp);
			cur[i*(i+1)/2 + j] = tmp;
		}
		// i층 최대 합 계산
		cal_sum(i);
	}
	idx = (num - 1)*(num) / 2;
	for (int i = idx; i < idx + num; i++)
	{
		if (max < sum[i])
		{
			max = sum[i];
		}
	}
	printf("%d\n", max);
}