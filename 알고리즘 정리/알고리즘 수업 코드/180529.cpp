#include <Stdio.h>
#define Sz 10
int d[Sz] = {2,1,152,516,365,326,125,64,1521,124};
void main()
{

	// bubble sort
#if 0
	for (int j = 1; j <= Sz - 1; j++)
	{
		for (int i = 0; i < Sz - j; i++)
		{
			if (d[i] > d[i + 1])
			{
				int temp = d[i];
				d[i] = d[i + 1];
				d[i + 1] = temp;
			}
		}
}
#endif
	//insertion sort
#if 0

	for (int i = 1; i < Sz; i++)
	{
		int temp = -1;
		for (int j = i; j >= 0; j--)
		{
			if (d[j] > d[i])
			{
				temp = j;
			}
		}
		if (temp == -1)
		{
			continue;
		}
		else
		{
			int t = 0;
			int t1 = 0;
			for (int k = temp; k <= i; k++)
			{
				if (k == temp)
				{
					t = d[k];
					d[k] = d[i];
				}
				else
				{
					if (t != 0)
					{
						t1 = d[k];
						d[k] = t;
						t = 0;
					}
					else
					{
						t = d[k];
						d[k] = t1;
						t1 = 0;
					}
				}
			}
		}
	}
#endif
	//real insertion sort
#if 0
	for (int i = 1; i < Sz; i++)
	{
		int j = i;
		while (j - 1 >= 0 && d[j - 1] > d[j])
		{
			int temp = d[j - 1];
			d[j - 1] = d[j];
			d[j] = temp;
			j--;
		}
	}
#endif
	//selection sort
#if 0

	for (int j = 1; j < Sz; j++) //selection .
	{
		int temp = d[j - 1];
		int temp2 = j - 1;
		int temp3;
		for (int i = j - 1; i <= Sz - 1; i++)
		{

			if (d[i] < temp)
			{
				temp = d[i];
				temp2 = i;
			}
		}
		temp3 = d[j - 1];
		d[j - 1] = temp;
		d[temp2] = temp3;
	}
#endif
	for (int i = 1; i <= Sz - 1; i++)
	{
		for (int j = Sz - 1; j > i-1; j--)
		{
			if (d[j] < d[j-1])
			{
				int temp = d[j];
				d[j] = d[j-1];
				d[j-1] = temp;
			}
		}
	}
	for (int i = 0; i < Sz; i++)
	{
		printf("%d\n", d[i]);
	}
}
