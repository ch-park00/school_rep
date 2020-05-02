#include <stdio.h>
//백준 알고리즘 2869번
#if 0
int main()
{
	int V, A, B;
	int cur = 0;
	int cnt = 0;
	int temp = 0;
	scanf_s("%d %d %d", &A, &B, &V);
	cnt = (V - A) / (A - B);
	cur = cnt * (A - B);
	
	while (1)
	{
		cnt++;
		cur = cur + A;
		if (cur >= V)
		{
			break;
		}
		cur = cur - B;
	}
	printf("%d\n",cnt);
	return 0;
}
#endif
//백준 알고리즘 2839번
#if 0
int main()
{
	int a_num, b_num;
	int N = -1;
	while (1) {
		scanf_s("%d", &N);
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
#endif 
#define Sz 8
int main()
{
	int cnt = 0;
	int col, raw;
	char t;
	for (col = 0; col < Sz; col++)
	{
		for (raw = 0; raw < Sz; raw++)
		{
			
			scanf_s("%c", &t);
			if (t == 'F')
			{
				if (col % 2 == 0)
				{
					if (raw % 2 == 0)
					{
						cnt++;
					}
				}
				else
				{
					if (raw % 2 == 1)
					{
						cnt++;
					}
				}
			}
		}
		scanf_s("%c", &t);
	}
	printf("%d\n", cnt);
}