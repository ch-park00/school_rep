#include <stdio.h>
// n개의 접시를 from에서 to까지 이동. tmp를 임시로 활용한다.
void hanoi(int n, int from, int tmp, int to)
{
	if (n == 1)
	{
		printf("%d=>%d\n", from, to);
	}
	else
	{
		//맨 밑판을 제외한 모든 판을 옆으로 이동.
		hanoi(n - 1, from, to, tmp);
		//맨 밑판을 최종 목적지로 이동시킨다.
		hanoi(1, from, tmp, to);
		//이전에 옮긴 판을 다시 원 상태대로 이동시킨다.
		hanoi(n - 1, tmp, from, to);
	}
}
int main()
{
	hanoi(10,1,2,3);
	return 0;
}