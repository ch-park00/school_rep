#include <stdio.h>
#include <stdlib.h>
#define Sz 8
//전역변수이므로 0으로 초기화됨.
int board[Sz][Sz]; 

// 내 위쪽에 있는 퀸들이 있는지 없는지 검사
// 위에 존재하면 1, 없으면 0 반환
int checkUpside(int i, int j) //i행 j열
{
	for (int k = i - 1; k >= 0; k--)
	{
		if (board[k][j] != 0)
		{
			return 1;
		}
	}
	return 0;
}
//v의 절대값 반환
int makeAbs(int v) 
{
	if (v < 0)
	{
		return -v;
	}
	return v;
}
// 대각선에 퀸들이 존재하는지 검사
//대각선의 경우도 위쪽 방향만 있는지 검사
// 똑같이 존재하면 1, 없으면 0반환
int checkDiagonal(int _i, int _j)
{
	// 두 지점의 행과 열의 차의 절대값이 같으면 
	//서로 대각선에 있는 관계
	for (int i = 0; i < _i; i++)
	{
		for (int j = 0; j < Sz; j++)
		{
			if (board[i][j] != 0) //퀸이 검사하는 곳에 존재하는지 검사
			{
				if (makeAbs(i - _i) == makeAbs(j - _j)) //대각선인지 아닌지 검사
				{
					return 1;
				}
				else
				{
					//해당 행에 퀸이 존재하는데 대각선 아닌곳에 존재하므로
					//해당 행은 더 이상 검사할 필요가 없다
					//다음 열로 넘어가서 검사한다.
					break; 
				}
			}
		}
	}
	return 0;
}
void showBoard()
{
	printf("-------------\n");
	for (int i = 0; i < Sz; i++)
	{
		for (int j = 0; j < Sz; j++)
		{
			printf("%d ", board[i][j]);
		}

		printf("\n");
	}
	printf("-------------\n");
}
//Queen이 있을 자리를 [row, 0 ~ (Sz-1)]부분에 대해 검사
void doBacktracking(int row) 
{
	for (int i = 0; i < Sz; i++)
	{
		//해당 위치에 퀸을 놓을수 있는지 없는지 검사해본다
		if (checkUpside(row, i) == 0 && checkDiagonal(row, i) == 0)
		{
			board[row][i] = 1; //queen을 해당 위치에 놓는다
			if (row  < Sz - 1) 			
			{
				//queen을 새로 놨는데 모든 조건 만족 시 다음 행에 대해 검사 실시
				doBacktracking(row + 1);
			}
			else
			{
				// 맨 마지막 줄에 도달했으므로 체스판 출력 후 종료
				showBoard();
			}
			board[row][i] = 0; //해당 조합을 수행하고 난 후에는 다른 조합을 시행해보도록 해당 퀸을 치워야한다.
		}
	}
}
//backtracking 구현(4queen problem)
int main()
{
	doBacktracking(0); //0행부터 queen을 놓고 backtracking 실행
	return 0;
}