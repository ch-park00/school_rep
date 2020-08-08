#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int index = 0;
int data[10002] = { 0 };

int data1[10000] = { 0 };
void q_sort(int left,int right)
{
	if (left >= right)
	{
		return;
	}
	int pivot = (left + right) / 2;
	int cur_left = left;
	int cur_right = right;
	while (1)
	{
		while (1)
		{
			if (data[cur_left] >= data[pivot] || cur_left>pivot)
			{
				break;
			}
			cur_left++;
		}
		while (1)
		{
			if (data[cur_right] <= data[pivot] || cur_right < pivot)
			{
				break;
			}
			cur_right--;
		}

		if (cur_left >= cur_right)
		{
			break;
		}
		else
		{
			int tmp = data[cur_left];
			data[cur_left] = data[cur_right];
			data[cur_right] = tmp;
			cur_left++, cur_right--;
		}
	}
	q_sort(left, pivot - 1);
	q_sort(pivot + 1, right);
	return;
}
void insert_sort(int input_data)
{
	if (index==0)
	{
		data[0] = input_data;
		index++;
		return;
	}
	for (int i = 0; i < index; i++)
	{
		if (data[i] == input_data)
		{
			return;
		}
		if (data[i] > input_data)
		{
			int tmp = data[i];
			int tmp1 = data[i + 1];
			data[i] = input_data;
			for (int j = i; j < index; j++)
			{
				if ((j - i) % 2 == 0)
				{
					data[j + 1] = tmp;
					tmp = data[j + 2];
				}
				else
				{
					data[j + 1] = tmp1;
					tmp1 = data[j + 2];
				}
			}
			index++;
			return;
		}
	}
	data[index] = input_data;
	index++;
}
int main()
{
	int num;
	scanf("%d", &num);
	for (int i = 0; i < num; i++)
	{
		int tmp;
		scanf("%d", &tmp);
		data1[tmp - 1] = data1[tmp - 1] + 1;
		insert_sort(tmp - 1);
	}
	for (int i = 0; i < index; i++)
	{
		for (int k = 0; k < data1[data[i]]; k++)
		{
			printf("%d\n", data[i] + 1);
		}
	}
	return 0;
}