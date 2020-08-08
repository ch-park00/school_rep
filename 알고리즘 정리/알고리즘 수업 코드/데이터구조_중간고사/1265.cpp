#include <stdio.h>
#include <math.h>
#include <string.h>
struct node
{
	char city[100];
	int num_odd;
};
typedef struct node travel;
travel name[10] = { 0 };
void identify(int a)
{
	for (int k = 0; k < a; k++)
	{
		char *temp = name[k].city;
		int t = 0;
		while (1)
		{
			if (name[k].city[t] == 'a' || name[k].city[t] == 'u'
				|| name[k].city[t] == 'e' || name[k].city[t] == 'i' || name[k].city[t] == 'o')
			{
				name[k].num_odd++;
			}
			else
			{
				if (name[k].city[t] == 0)
				{
					break;
				}
			}
			t++;
		}
	}
}
void sortname(int a)
{
	for (int i = 1; i < a; i++)
	{
		for (int k = 0; k < a-i; k++)
		{
			if (name[k].num_odd < name[k + 1].num_odd)
			{
				char t[100] = { 0 };
				int temp = name[k].num_odd;
				strcpy(t, name[k].city);
				strcpy(name[k].city, name[k + 1].city);
				name[k].num_odd = name[k + 1].num_odd;
				name[k + 1].num_odd = temp;
				strcpy(name[k + 1].city, t);
			}
			else
			{
				continue;
			}
		}
	}
}
void printall(int a)
{
	for (int i = 0; i < a; i++)
	{
		printf("%s ", name[i].city);
	}
}
void sortname1(int a)
{
	for (int j = 1; j < a; j++)
	{
		for (int i = 0; i < a - j; i++)
		{
			if (name[i].num_odd == name[i + 1].num_odd)
			{
				if (name[i].city[0] > name[i + 1].city[0])
				{
					char t[100] = { 0 };
					int temp = name[i].num_odd;
					strcpy(t, name[i].city);
					strcpy(name[i].city, name[i + 1].city);
					name[i].num_odd = name[i + 1].num_odd;
					name[i + 1].num_odd = temp;
					strcpy(name[i + 1].city, t);
				}
			}
		}
	}
}
void main()
{
	int a;
	scanf("%d", &a);
	for (int k = 0; k < a; k++)
	{
		scanf("%s", name[k].city);
		name[k].num_odd = 0;
	}
	identify(a);
	sortname(a);
	sortname1(a);
	printall(a);
}