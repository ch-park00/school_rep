#include <stdio.h>
#include <stdlib.h>
#define Sz 6
int board[Sz][Sz];
int cnt = 0;
int queen_cnt = 0;

void showBoard()
{
	printf("정답:\n");
	for (int i = 0; i < Sz; i++)
	{
		for (int j = 0; j < Sz; j++)
		{
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
	cnt++;
}
int checkvertical(int row, int column)
{
	for (int i = 0; i < Sz; i++)
	{
		if (abs(row - i) <= 2)
		{
			if (board[i][column] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}
int checkhorizon(int row, int column)
{
	for (int i = 0; i < Sz; i++)
	{
		if (abs(column - i) <= 2)
		{
			if (board[row][i] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}
int checkdiagonal(int row, int column)
{
	for (int i = 0; i < Sz; i++)
	{
		for (int j = 0; j < Sz; j++)
		{
			if (abs(row - i) == abs(column - j))
			{
				if (abs(row - i) <= 2)
				{
					if (board[i][j] != 0)
					{
						return 0;
					}
				}
			}
		}
	}
	return 1;
}
void doBacktracking(int row, int column)
{

	if (checkvertical(row, column) == 1 && checkhorizon(row, column) == 1 && checkdiagonal(row, column) == 1)
	{
		board[row][column] = 1;
		queen_cnt++;
		if (queen_cnt == Sz)
		{
			showBoard();
			queen_cnt--;
			board[row][column] = 0;
			if (column == Sz - 1)
			{
				if (row == Sz - 1)
				{
					return;
				}
				doBacktracking(row + 1, 0);
			}
			else
			{
				doBacktracking(row, column + 1);
			}
			return;
		}
		else
		{
			if (column == Sz - 1)
			{
				if (row == Sz - 1)
				{
					return;
				}
				doBacktracking(row + 1, 0);
			}
			else
			{
				doBacktracking(row, column + 1);
			}
		}
		board[row][column] = 0;
		queen_cnt--;
	}
	if (column == Sz - 1)
	{
		if (row == Sz - 1)
		{
			return;
		}
		doBacktracking(row + 1, 0);
	}
	else
	{
		doBacktracking(row, column + 1);
	}
}
int main()
{
	doBacktracking(0, 0);
	printf("총 개수:%d개\n", cnt);
	printf("**0은 비어있는 자리, 1은 퀸이 있는 자리를 의미**\n");
	while (1)
	{
		int temp = 0;
		printf("종료하려면 아무거나 입력하세요\n");
		scanf("%d", &temp);
		break;
	}
	return 0;
}