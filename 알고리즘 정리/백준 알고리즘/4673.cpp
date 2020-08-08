#include <stdio.h>

int arr[10000] = { 0 };
void check(int i)
{
	int result = 0;
	int check_1 = 0;
	int check_2 = 0;
	int check_3 = 0;
	int check_4 = 0;
	int check_5 = 0;
	check_1 = i % 10;
	check_2 = (i / 10) % 10;
	check_3 = (i / 10 / 10) % 10;
	check_4 = (i / 10 / 10/10) % 10;
	result = i + check_1 + check_2 + check_3 + check_4;
	if (result <= 10000)
	{
		arr[result - 1] = 1;
	}
}
void print_all()
{
	for (int i = 0; i < 10000; i++)
	{
		if (!arr[i])
		{
			printf("%d\n", i + 1);
		}
	}
}
int main()
{
	for (int i = 1; i < 10000; i++)
	{
		check(i);
	}
	print_all();
	return 0;
}