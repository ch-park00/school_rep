#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define max 50
//종업원 수
int serving = 0;
//현재 식당 안에 몇명이 있는지 확인
int cur = 0;
//식당에 온 번호
int cnt = 0;
//식사 다 하고 나간 사람 수
int cnt1 = 0;
//대기중인 사람 수
int wait = 0;
//현재 일하고 있는 종업원 수
int serve = 0;
//식사를 마치고 테이블을 치우고 있는지 판별.
//1일 때 치우고 있음을 의미.
int wait1[50] = { 0 };
HANDLE hMutex;
HANDLE hMutex1;
LPCWSTR res;
LPCWSTR res1;

// 종업원
DWORD WINAPI MYThread_2(LPVOID arg)
{
	wait1[(int)arg] = 1;
	// 모든 종업원이 일하고 있을 때
	if (serve >= serving)
	{
		printf("종업원이 #%d 식사한 테이블 치워주길 기다리는중\n", (int)arg);
	}
	WaitForSingleObject(hMutex1, INFINITE);
	//지금부터 치우기 시작
	serve++;
	printf("#%d테이블 치우는중\n", (int)arg);
	Sleep(200);
	printf("#%d테이블 clear\n", (int)arg);
	serve--;
	cnt1++;
	//200ms동안 다 치우고 임계영역 탈출
	ReleaseSemaphore(hMutex1, 1, NULL);
	wait1[(int)arg] = 0;
	return 0;
}
// 식당 내부
DWORD WINAPI MYThread_1(LPVOID arg)
{
	WaitForSingleObject(hMutex, INFINITE);
	// 대기중이던 사람이 들어왔을 경우
	if (wait > 0)
	{
		//대기인원 1명 감소
		wait--;
	}
	cnt++;
	int me = cnt;
	cur++;
	printf("#%d enter, 시간:%d, 현재 식당 안에 사람 수 : %d\n", me, (int)arg,cur);
	Sleep((int)arg*100);
	printf("#%d 퇴장\n", me);
	//
	CreateThread(NULL, 0, MYThread_2, (LPVOID)me, 0, NULL);
	Sleep(1);
	while (wait1[me]);
	cur--;
	ReleaseSemaphore(hMutex, 1, NULL);
	return 0;
}
int main(int argc, char *argv[])
{
	int p;
	printf("확률 입력(1/n), n값을 입력:");
	scanf("%d", &p);
	printf("종업원 수 입력:");
	scanf("%d", &serving);
	srand(time(NULL));
	int c = 0;
	HANDLE hThread[max];
	DWORD THreadid[max];
	hMutex = CreateSemaphore(NULL, 10, 10, res);
	hMutex1 = CreateSemaphore(NULL, serving, serving, res1);
	time_t time1, time2;
	time1 = time(NULL);
	while (1)
	{
		// 식당에 총 50명이 도착
		if (cnt+wait >= max)
		{
			//모든 사람이 나가고 다 치울때까지 대기
			while (cnt1 < max);
			CloseHandle(hMutex);
			CloseHandle(hMutex1);
			break;
		}
		//식사시간과 들어올 확률 계산
		int t = (rand() % 21) + 10;
		int c = (rand() % p);

		//아무도 오지 않은 경우
		if (c)
		{
			Sleep(100);
			continue;
		}
		//누군가 왔을 경우
		else
		{
			//현재 식당안에 10명 이상인 경우
			if (cur == 10)
			{
				wait++;
				printf("%d 대기중\n",cnt+wait);
			}
			// 세마포어 안에 쓰레드 생성
			hThread[c] = CreateThread(NULL, 0, MYThread_1, (LPVOID)t, 0, &THreadid[c]);
			Sleep(100);
		}
	}
	time2 = time(NULL);
	printf("50명이 식사하고 나가는데 걸린시간:%lld\n", (time2 - time1) );
	return 0;
}