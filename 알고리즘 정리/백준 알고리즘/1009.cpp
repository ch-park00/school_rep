#include <stdio.h>
#include <math.h>
double total_data = 0;
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int a, b;
		int result;
		scanf("%d %d", &a, &b);
		total_data = pow(a, b);
		result = int(long long(total_data) % 10);
		printf("%d\n", result);
	}
	return 0;
}