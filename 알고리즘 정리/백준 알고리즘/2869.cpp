#include <stdio.h>

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
	printf("%d\n", cnt);
	return 0;
}