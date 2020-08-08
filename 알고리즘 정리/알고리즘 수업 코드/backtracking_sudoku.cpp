#include <stdio.h>
#include <stdlib.h>
int stk[9][9] = 
{ 
0
};


int checkvertex(int row, int num)
{
	for (int i = 0; i < 9; i++)
	{
		if (stk[row][i] == num)
		{
			return 0;
		}
	}
	return 1;
}
int checkhorizon(int column, int num)
{
	for (int i = 0; i < 9; i++)
	{
		if (stk[i][column] == num)
		{
			return 0;
		}
	}
	return 1;
}
int checkbox(int row, int column, int num)
{
	int b_row = (row / 3) * 3;
	int b_col = (column / 3) * 3;

	for (int i = b_row; i < b_row + 3; i++)
	{
		for (int j = b_col; j < b_col + 3; j++)
		{
			if (stk[i][j] == num)
			{
				return 0;
			}
		}
	}
	return 1;
}
void showBoard()
{
	printf("ans:\n");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", stk[i][j]);
		}
		printf("\n");
	}
}
void doBacktracking(int row, int column)
{
	for (int i = 1; i <= 9; i++)
	{
		if (stk[row][column] != 0)
		{
			if (column == 8)
			{
				if (row == 8)
				{
					showBoard();
				}
				else
				{
					doBacktracking(row + 1, 0);
				}
			}
			else
			{
				doBacktracking(row, column + 1);
			}
			return;
		}
		else
		{
			if (checkvertex(row, i) == 1 && checkhorizon(column, i) == 1 && checkbox(row, column, i) == 1)
			{
				stk[row][column] = i;
				if (column == 8)
				{
					if (row == 8)
					{
						showBoard();
					}
					else
					{
						doBacktracking(row + 1, 0);
					}
				}
				else
				{
					doBacktracking(row, column + 1);
				}
				stk[row][column] = 0;
			}
		}
	}
}
int main()
{
	FILE *f = fopen("alice.txt", "rt");
	for (int i = 0; i < 9; i++)
	{
		int temp;
		for (int j = 0; j < 9; j++)
		{
			fscanf(f, "%d,", &temp);
			stk[i][j] = temp;
		}
		
	}
	printf("½ºÅäÄí ¹®Á¦:\n");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", stk[i][j]);
		}
		printf("\n");

	}
	doBacktracking(0, 0);
	return 0;
}