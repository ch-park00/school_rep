#include <stdio.h>
int data[20] = { 0,6,3,5,7,10,1,2 }; //맨 처음 0은 쓰는 인덱스가 아니다.

void swap(int i, int j)
{
	int temp = data[i];
	data[i] = data[j];
	data[j] = temp;
}
void findlocation(int cur, int i) //max heap에 맞게 위치를 찾아가는 함수.cur는 현재 인덱스 번호,i는 최대 인덱스 번호.
{
	int left = cur * 2;
	int right = left + 1;
	int big = cur; //가장 큰 값을 저장하고 있는 인덱스 번호를 저장
	if (left <= i && data[left] > data[cur]) //왼쪽 자식이 가장 크고 left가 인덱스 범위 안에 있다.
	{
		big = left; 
	}
	if (right <= i && data[right] > data[big]) //오른쪽 자식이 가장 크고 right가 인덱스 범위 안에 있다.
	{
		big = right; 
	}
	if (big == cur) //바뀐게 없음
	{
		return;
	}
	else
	{
		swap(cur, big); //cur와 big의 인덱스 데이터를 서로 바꾼다
		findlocation(big, i); //바뀐 위치에서 바꾼 뒤 문제가 없는지 확인하는 과정이 필요하다.
	}
}
void heapify(int i) //i는 맨 마지막 인덱스 번호
{
	int cur = i / 2; //cur는 부모 노드의 인덱스 번호
	while (cur >= 1) 
	{
		findlocation(cur, i);
		cur--;
	}
}
void addToheap(int v, int i)//v는 추가할 데이터,i는 현재 최대 인덱스 번호
{
	int cur = i + 1;
	int parent = cur / 2;
	data[cur] = v;
	while (1)
	{
		if (data[parent] > data[cur])
		{
			return;
		}
		else
		{
			swap(parent, cur);
			cur = parent;
			parent = parent / 2;
			if (parent < 1)
			{
				return;
			}
		}
	}
}
int removeroot(int i)
{
	int temp = data[1];
	data[1] = data[i];
	findlocation(1, i - 1);
	return temp;
}
void main()
{
	int a;
	heapify(7); 
	printf("root:%d\n", data[1]);
	addToheap(20, 7);
	printf("root:%d\n", data[1]);
	addToheap(30, 8);
	printf("root:%d\n", data[1]);
	a=removeroot(9);
	printf("삭제한 노드:%d\nroot노드:%d\n", a, data[1]);
	for (int i = 1; i <= 8; i++)
	{
		printf("%d\n", data[i]);
	}
}