#include <iostream>
#define num 10

int number[num] = { 56,32,33,4,9,10,98,83,22,68 };
//5번째로 큰 수 찾기
int orderTofind = 5;

void selection(int pivot, int left, int right)
{
	int L = left;
	int R = right;
	if (right < left)
	{
		std::cout << orderTofind << "th number : " << number[orderTofind - 1] << std::endl;
		return;
	}
	while (1)
	{
		while (number[pivot] > number[L])
		{
			L++;
		}
		while (number[pivot] < number[R])
		{
			R--;
		}
		if (L < R)
		{
			int tmp = number[L];
			number[L] = number[R];
			number[R] = tmp;
		}
		else
		{
			if (R == orderTofind - 1)
			{
				std::cout << orderTofind << "th number : " << number[orderTofind - 1] << std::endl;
				return;
			}
			else
			{
				int tmp = number[pivot];
				number[pivot] = number[R];
				number[R] = tmp;
				if (R > orderTofind - 1)
				{
					selection(pivot, left, R - 1);
				}
				else
				{
					selection(R + 1, R + 2, right);
				}
				return;
			}
		}
	}
}
int main()
{
	int pivot = 0;
	selection(pivot, 1, num - 1);
	return 0;
}