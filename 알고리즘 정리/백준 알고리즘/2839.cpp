#include <stdio.h>
int main()
{
	int a_num, b_num;
	int N = -1;
	while (1) {
		scanf("%d", &N);
		a_num = N / 5;
		b_num = N / 3;
		if ((N - (a_num * 5)) % 3 != 0)
		{
			int i = 0;
			while (i <= 1)
			{
				a_num--;
				if (a_num < 0)
				{
					a_num = 0;
				}
				if ((N - (a_num * 5)) % 3 == 0)
				{
					b_num = (N - (a_num * 5)) / 3;
					break;
				}
				i++;
			}
			if (i == 2)
			{
				printf("-1\n");
			}
			else
			{
				printf("%d\n", a_num + b_num);
			}
		}
		else
		{
			b_num = (N - (a_num * 5)) / 3;
			printf("%d\n", a_num + b_num);
		}
	}

	return 0;

}