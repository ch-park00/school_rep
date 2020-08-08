#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char name[100][50] = { 0 };

void lineup(int a)
{
	
	for (int i = 1; i < a; i++)
	{
		int cnt = 0;
		for (int j = 0; j <= i-1; j++)
		{
			if (name[i][0] == name[j][0])
			{
				cnt++;
			}
			else
			{
				if (cnt == 0)
				{
					continue;
				}
				else
				{
					int temp = i;
					int cnt1 = 0;
					while (1)
					{
						char t[50] = { 0 };
						strcpy(t, name[temp]);
						strcpy(name[temp], name[temp - 1]);
						strcpy(name[temp - 1], t);
						temp--;
						if (temp == j)
						{
							if (cnt == 1)
							{
								break;
							}
							else
							{
								char t[50] = { 0 };
								strcpy(t, name[temp]);
								strcpy(name[temp], name[temp - 1]);
								strcpy(name[temp - 1], t);
								break;
							}
						}
					}
					break;
				}
			}
		}
	}
}
void main()
{
	int a;
	scanf("%d", &a);
	for (int i = 0; i < a; i++)
	{
		scanf("%s",name[i]);
	}
	lineup(a);
	for (int i = 0; i < a; i++)
	{
		printf("%s ", name[i]);
	}
}