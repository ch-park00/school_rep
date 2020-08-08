#include <stdio.h>
#include <stdlib.h>

int *is_it;
void do_function(int min_, int max_)
{
	int cnt = 0;
	int num = 2;
	int idx = 0;
	while (1)
	{
		if (num*num > max_)	break;

		int idx = min_ / (num*num);
		int tmp = (min_) % (num*num);
		if (tmp != 0)
		{
			idx = idx + (num*num) - tmp;
		}
		if (is_it[idx] == 0)
		{
			while (1)
			{
				if (idx >= max_ - min_)	break;
				is_it[idx] = 1;
				idx = idx + (num*num);
			}
		}
		num++;
	}
	for (int i = 0; i <= max_ - min_; i++)
	{
		if (is_it[i] == 0)
		{
			cnt++;
		}
	}
	printf("%d\n", cnt);
}
int main()
{
	int min, max;
	scanf("%d %d", &min, &max);
	is_it = (int*)malloc((max - min + 10) * 4);
	for (int i = 0; i <= max - min; i++)
	{
		is_it[i] = 0;
	}
	do_function(min, max);
	return 0;
}