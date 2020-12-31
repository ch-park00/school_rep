#include <iostream>
using namespace std;
//맨 마지막 수는 0
int number[9] = { 0,0,0,0,5,0,0,0,0 };
//계산량 비교를 위한 변수.
int cnt;

int makeNumber(int idx)
{
	int sum = 0;
	for (int i = 0; i < idx; i++)
	{
		sum = sum * 10 + number[i];
	}
	return sum;
}
void showNumber()
{
	for (int i = 0; i < 9;i++)
	{
		std::cout << number[i];
	}
	std::cout << 0 << std::endl;
}
void checkNumber(int idx)
{
	cnt++;
	//앞에 중복되는 숫자가 있는지 확인
	//있으면 종료
	for(int i = 0; i < idx; i++)
	{
		if (number[i] == number[idx])
		{
			return;
		}
	}
	//조건 검사를 위해 나누기 위해 사용할 숫자
	int divisor = idx + 1;
	// 현재 자리수까지의 숫자를 만드는 함수
	// 예를 들어 두번째 자리라면, 두 자리 숫자를 return
	int tmp = makeNumber(divisor);

	//자리수 조건 만족
	if (tmp%divisor == 0)
	{
		// 맨 마지막일 경우(모든 경우를 만족하는 수를 찾음)
		//현재 배열을 출력
		if (divisor == 9)
		{
			std::cout << "magic num : ";
			showNumber();
			return;

		}
		// 5번째 자리는 5이므로 5를 넣고 확인해 봄.
		if (divisor == 4)
		{
			number[divisor] = 5;
			checkNumber(divisor);
		}
		// 6~8번째 자리 확인
		//
		else
		{
			// 모든 숫자에 대해 확인
			for (int i = 1; i <= 9; i++)
			{
				//5는 이미 사용되었기 때문에 스킵함.
				
				if (i == 5)
				{
					continue;
				}
				number[divisor] = i;
				checkNumber(divisor);
			}
		}
	}
}
int main()
{
	int idx = 0;
	for (int i=1;i<=9;i+=2)
	{
		if (i == 5)
		{
			continue;
		}
		number[idx] = i;
		checkNumber(idx);
	}
	//printf("cnt is %d\n", cnt);
	//c++ 출력문법.
	//endl : 줄바꿈 역할을 담당
	//cout : printf
	//check_num  함수 호출 횟수
	std::cout << "cnt is : " << cnt << std::endl;
	return 0;
}