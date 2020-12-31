#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define queue_sz 10
#define INVALID_NUM -999
#if 0
int queue[queue_sz] = { 0 };
int front = 0;
int rear = 0;
int isfull()
{
	//return (rear + 1) % queue_sz == front)?1:0;
	if ((rear + 1) % queue_sz == front)
	{
		return 1;
	}
	return 0;
}
int isempty()
{
	/*
	if (front == rear)
	{
		return 1;
	}
	return 0;*/
	return (front == rear) ? 1 : 0;
}
int dequeue()
{
	if (isempty())
	{
		return INVALID_NUM;
	}
	front = (front + 1) % queue_sz;
	int tmp = queue[front];
	return tmp;
}
void enqueue(int data)
{
	if (isfull())
	{
		return;
	}
	rear = (rear + 1) % queue_sz;
	queue[rear] = data;
}
int main()
{
	enqueue(1);
	enqueue(2);
	enqueue(3);
	enqueue(4);
	enqueue(5);
	for (int i = 0; i < 5; i++)
	{
		printf("%d\n", dequeue());
	}
	
	return 0;
}
#endif
char *queue[queue_sz];
int front = 0;
int rear = 0;

int isfull()
{
	
}
int enqueue(char *data)
{
	if ((rear + 1) % queue_sz == front)
	{
		return 0;
	}
	queue[rear] = data;
	rear = (rear + 1) % queue_sz;
	return 1;
}
//큐가 꽉 찰 때까지 문자열 입력받고 큐에 입력받은 뒤, 

//큐 꽉 차면 큐에 있는 모든 데이터 내보내는 코드 작성하기.
int main()
{
	char tmp[30];
	char *v;
	while (1)
	{
		int result;
		printf("Enter word:");
		scanf("%s", tmp);
		v = (char*)malloc(strlen(tmp) + 1);
		strcpy(v, tmp);
		result = enqueue(v);
		if (!result)
		{
			printf("queue full\n");
			while (1)
			{
				
			}
		}

	}
	return 0;
}