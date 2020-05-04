#include <stdio.h>
#include "sort.h"
int data[20] = { 10,45,4,123,15,55,123,2 };
int search(int data_,int index)
{
	int start = 0;
	int last = index;
	while (start<=last)
	{
		int mid = (start + last) / 2;
		if (data[mid] == data_)	return mid;
		if (data[mid] > data_)	last = mid - 1;
		else
		{
			start = mid + 1;
		}
	}
	return -1;
}
int main()
{
	int idx = 0;
	q_sort(data, 0, 1, 7);
	idx = search(10, 7);
	printf("%d\n", data[idx]);
	return 0;
}