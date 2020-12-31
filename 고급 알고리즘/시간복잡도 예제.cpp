#include <stdio.h>
#include <time.h>
//clock()함수 사용=>시간 측정
int main()
{
	clock_t start_time, end_time;
	start_time = clock();
	double k = 0;
	// 수행 알고리즘 수행
	for (int i = 1; i < 100000; i++)
	{
		k = (k*k*k*k) / double(i);
	}
	end_time = clock();
	//해당 프로그램 동작하는 동안 걸린 클럭 수가 나옴.
	//실제 소모 시간을 알고 싶다면 클럭 스피드로 나누면 실제 소요 시간(초)가 나온다.
	printf("%d\n", end_time - start_time);
}