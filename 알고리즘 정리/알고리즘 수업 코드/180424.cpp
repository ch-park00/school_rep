#include <stdio.h>
#define Sz 4
int Queue[Sz]; //큐 생성
int front = 0;
int rear = 0;

int isQempty() //큐가 비어있는지 확인. 비어있으면 1반환.다르면 0반환
{
	return (rear == front);
}
int isQfull() //큐가 꽉 차 있는지 확인. 꽉 차잇으면 1반환.아니면 0
{
	return ((rear + 1) % Sz == front);
}

void enqueue(int v)
{
	if (isQfull() == 1) //꽉 차 있으면 그냥 함수 종료
	{
		return;
	}
	Queue[rear] = v;
	rear = (rear + 1) % Sz; //queue가 circular이기 때문에 돌 경우를 대비
}
int dequeue()
{
	int a;
	if (isQempty() == 1)
	{
		return -1111; //큐가 비었다는 뜻
	}
	a = Queue[front];
	front = (front + 1) % Sz;
	return a;
}
void dequeue_()
{
	int a;
	if (isQempty() == 1)
	{
		printf("출력할 데이터가 없습니다.\n");
	}
	else
	{
		printf("%d\n", Queue[front]);
		front=(front+1)%Sz;
	}
}
void main()
{
	enqueue(1);
	enqueue(2);
	enqueue(3);
	enqueue(4);
	enqueue(5);
	printf("%d\n", dequeue()); // 1
	printf("%d\n", dequeue()); // 2
	printf("%d\n", dequeue()); // 3
	printf("%d\n", dequeue()); // -1111
	printf("%d\n", dequeue()); // -1111
	enqueue(1);
	enqueue(2);
	enqueue(3);
	enqueue(4);
	enqueue(5);
	for (int i = 0; i < 5; i++)
	{
		dequeue_();
	}
}