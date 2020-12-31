#include <stdio.h>
#include <string.h>
#include <math.h>
//퀸 사이즈
#define SZ 8
//스도쿠 사이즈
#define S_SZ 9
//전역 변수이므로 모두 0으로 초기화됨
int board[SZ][SZ];
int sudoku[S_SZ][S_SZ] = {
	4,0,7,5,0,0,0,0,8,
	0,5,0,7,0,0,4,0,9,
	0,0,6,0,0,4,0,7,0,
	9,0,0,6,0,0,2,4,3,
	0,4,0,9,0,3,0,8,0,
	7,3,1,0,0,2,0,0,5,
	0,2,0,8,0,0,7,0,0,
	3,0,9,0,0,6,0,5,0,
	5,0,0,0,0,7,3,0,4
};
//backtracking 실패 시 이전 상태로 돌아가기 위해 필요한 배열
int read_sudoku[S_SZ][S_SZ];

//board 배열 모두 0으로 초기화
void init_board()
{
	/*
	for (int i = 0; i < SZ; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			board[i][j] = 0;
		}
	}*/
	//board 주소로부터 4*SZ*SZ만큼의 주소값을 모두 0으로 초기화
	//string.h 안에 존재
	memset(board, 0, sizeof(int) * SZ* SZ);
}
//현재 위치에 퀸을 위치해도 되는지 조건 확인
//좌표는 (r,c)
//조건 만족한다면 1, 아니라면 0 반환
//조건 검사 시 위쪽(이전에 퀸을 위치할 수 있는 방향)만 확인한다.
//아래쪽 조건은 나중에 놓을 때 확인하므로 미리부터 확인할 필요가 없다.
int check_if(int r, int c)
{
	for (int i = 0; i < r; i++)
	{
		//현재 위치에서 위쪽으로 퀸이 위치
		if (board[i][c] != 0)
		{
			return 0;
		}
	}
	for (int i = 0; i < c; i++)
	{
		//같은 줄에 퀸이 존재
		if (board[r][i] != 0)
		{
			return 0;
		}
	}
	//대각선 검사
	//대각선에 위치할 조건 => 현재 위치에서 열 차이 = 행 차이
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			if (abs(i - r) == abs(j - c) && board[i][j] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}
void print_sol()
{
	for (int i = 0; i < SZ; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
	printf("-----------------------\n");
}
//행 i를 0으로 초기화
void clear_row(int i)
{
	memset(board[i], 0, sizeof(int)*SZ);
}
//행이 row 위치에 chess 둘수 있는지 확인 후 진행하는 함수
//만약 만족하지 못하는 경우가 있다면 해당 경우의 보드는 초기화 해야한다.
void check_next(int row)
{
	for (int i = 0; i < SZ; i++)
	{
		//좌표 (row,i)에 퀸 둘 수 있는지 확인
		//이후 퀸 위치하고 다음 행으로 이동한다.
		//만약 맨 마지막 행이라면 
		if (check_if(row, i))
		{
			board[row][i] = 1;
			//맨 마지막 행까지 진행 완료(4개의 퀸을 놓는 경우 완성)
			if (row == SZ - 1)
			{
				print_sol();
			}
			else
			{
				check_next(row + 1);
			}
		}
		clear_row(row);
		
	}
}
void do_queen_problem()
{
	for (int i = 0; i < SZ; i++)
	{
		if (check_if(0, i))
		{
			board[0][i] = 1;
			check_next(1);
		}
		clear_row(0);
	}
}


//read_sudoku 배열에 sudoku 저장
void init_read_sudoku()
{
	memcpy(read_sudoku, sudoku, sizeof(int)*S_SZ*S_SZ);
}
//(row,col) 위치에 i값이 들어갈 수 있는지 확인
int check_sudoku_data(int row, int col, int data)
{
	//행 확인
	for (int i = 0; i < S_SZ; i++)
	{
		if (sudoku[i][col] == data && i != row)
		{
			return 0;
		}
	}
	//열 확인
	for (int i = 0; i < S_SZ; i++)
	{
		if (sudoku[row][i] == data && i != col)
		{
			return 0;
		}
	}
	//사각형 확인
	for (int i = (row / 3) * 3; i < (row / 3) * 3 + 3; i++)
	{
		for (int j = (col / 3) * 3; j < (col / 3) * 3 + 3; j++)
		{
			if (sudoku[i][j] == data)
			{
				return 0;
			}
		}
	}
	return 1;
}
void print_result()
{
	for (int i = 0; i < S_SZ; i++)
	{
		for (int j = 0; j < S_SZ; j++)
		{
			printf("%d ", sudoku[i][j]);
		}
		printf("\n");
	}
	printf("------------------------\n");
}
void do_sudoku_problem(int row, int col);
//(row,col) 다음 칸으로 이동시키는 함수
void check_next_sudoku(int row, int col)
{
	int r = row;
	int c = col;
	if (col == S_SZ - 1)
	{
		if (row == S_SZ - 1)
		{
			print_result();
			return;
		}
		r = r + 1;
		c = 0;
	}
	else
	{
		c = c + 1;
	}
	do_sudoku_problem(r, c);
}
//sudoku 문제를 backtracking 이용해 문제 해결.
void do_sudoku_problem(int row, int col)
{
	//미리 입력된 숫자가 있는 경우
	if (sudoku[row][col] != 0)
	{
		check_next_sudoku(row, col);
	}
	else
	{
		for (int i = 1; i <= 9; i++)
		{
			memcpy(&sudoku[row][col], &read_sudoku[row][col], sizeof(int)*((S_SZ*S_SZ) - (row*col)));
			//해당 숫자가 해당 위치에 들어갈 수 있는지 확인
			if (check_sudoku_data(row, col, i))
			{
				sudoku[row][col] = i;
				check_next_sudoku(row, col);
			}
		}
	}
}
int main()
{
	//init_board();
	//do_queen_problem();
	init_read_sudoku();
	do_sudoku_problem(0,0);
	return 0;
}