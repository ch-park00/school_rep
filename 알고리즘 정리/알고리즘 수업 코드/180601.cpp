#include <stdio.h>
#define Sz 10
int data[Sz] = { 10,15,20,10,35,100,99,99,101,7 };
//quick sort
//data는 배열의 이름,p는 pivot index,L은 left index,R은 right index
void qsort(int *data, int P, int L, int R)
{
	int l = L;
	int r = R;
	if (P >= R)
	{
		return;
	}
	while (1)
	{
		while (1)
		{    //맨처음 바꿀 l위치 확인
			if (data[P] > data[l] && l <= R)
			{
				l++;
			}
			else
			{
				break;
			}
		}
		//바꿀 r위치 확인
		while (1)
		{
			if (data[P] < data[r])//P보다 작을 조건은 필요없다.
			{
				r--;
			}

			else
			{
				break;
			}
		}
		if (l < r)
		{
			int temp = data[l];
			data[l] = data[r];
			data[r] = temp;
		}
		else if (l == r) //같은 값이 있을 때
		{
			int temp = P;
			while (temp <= l - 2)
			{
				int temp1 = data[temp];
				data[temp] = data[temp + 1];
				data[temp + 1] = temp1;
				temp++;
			}
			qsort(data, P, P + 1, temp - 1);
			qsort(data, temp + 2, temp + 3, R);
			return;
		}
		else
		{
			int temp = data[P];
			data[P] = data[r];
			data[r] = temp;
			qsort(data,P,P+1,r-1);
			qsort(data,r+1,r+2,R);
			return;
		}
	}
}
void main()
{
	for (int i = 0; i < Sz; i++)
	{
		printf("%d ", data[i]);
	}
	qsort(data, 0, 1, 9);
	printf("\nafter\n");
	for (int i = 0; i < Sz; i++)
	{
		printf("%d ", data[i]);
	}
}