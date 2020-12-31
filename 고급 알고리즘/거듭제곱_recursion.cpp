#include <stdio.h>
//v^a
int calc_power_recursion(int v, int a)
{
	if (a == 0)
	{
		return 1;
	}
	else
	{
		//Â¦¼ö
		if (a % 2)
		{
			return v * calc_power_recursion(v*v, (a - 1) / 2);
		}
		//È¦¼ö
		else
		{
			return calc_power_recursion(v*v, a / 2);
		}
	}
}
double pow_recursion(double a, int n)
{
	if (n == 0)
	{
		return 1;
	}
	if (n == 1)
	{
		return a;
	}
	double t = pow_recursion(a, n / 2);
	return t * t*pow_recursion(a, n % 2);
}
int main()
{
	// non_recursion
	double a = 3;
	double ret = 1;
	int n = 10;
	while (n)
	{
		if (n % 2 == 1)
		{
			ret *= a;
		}
		a *= a;
		n /= 2;
	}
	printf("%d\n", calc_power_recursion(2, 4));
	printf("%d\n", calc_power_recursion(3, 5));
	printf("%d\n", calc_power_recursion(100, 0));
	return 0;
}