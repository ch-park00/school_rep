#include <stdio.h>
#define max_size 10
#define INVALID_VALUE -999
#define true 1
#define false 0
typedef int boolean;

//stack 선언
int stack[max_size] = { 0 };
//현재 stack의 가장 윗값 가르키는 변수 선언
int top = -1;

boolean isEmpty(void)
{
	if (top == -1)
	{
		return true;
	}
	return false;
}
boolean isfull()
{
	if (top == max_size - 1)
	{
		return true;
	}
	return false;
}
boolean push(int data)
{
	if (isfull())
	{
		return false;
	}
	top++;
	stack[top] = data;
	return true;
}
int pop()
{
	if (isEmpty())
	{
		return INVALID_VALUE;
	}
	int tmp = stack[top];
	top--;
	return tmp;
}
int main()
{
	/*
	push(1);
	push(2);
	push(3);
	push(4);
	push(5);
	for (int i = 0; i < 6; i++)
	{
		printf("%d\n", pop());
	}*/
	char data;
	while (1)
	{
		printf("enter:");
		fgets(&data, 1, stdin);
		printf("%c\n", data);
		//fflush(stdin);

	}
	return 0;
}