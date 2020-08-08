#include <stdio.h>
#include <string.h>
int main()
{
	int len;
	char data[10] = { 0 };
	scanf("%s", data);
	len = strlen(data);
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (data[j] < data[j + 1])
			{
				int tmp = data[j + 1];
				data[j + 1] = data[j];
				data[j] = tmp;
			}
		}
	}
	printf("%s", data);
	return 0;
}