#include <stdio.h>

#define STACK_SZ 10 //스택사이즈 10으로 지정.
int stack[STACK_SZ];
int top = -1; //음수값이면 스택이 비었다는 걸 의미.

/*스택이 비어이있으면 1반환
 아니라면 0반환*/
int isEmpty() 
{
	return (top == -1); //top==-1이면 1반환.아니면 0 반환
						//관계연산자.참이면 1,거짓이면 0
}
/* 스택이 꽉 차 있으면 1반환
   아니라면 0 반환*/
int isFull()
{
	return (top == STACK_SZ - 1); //stack은 10개이므로 마지막 인덱스는 9이다.
								//9일때만 1반환.
}

void push(int d) //stack이 꽉 차 있으면 날리는 것으로 가정.
{
	if (isFull() == 1)
	{
		return;
	}
	top++;
	stack[top] = d;
	//stack[++top]=d 이것도 가능하지만 별로
	return;
}
int pop()
{
	int temp;
	if (isEmpty() == 1) //stack이 비어있을 때
	{
		return -666; //스택이 비어있다는 것을 가정하는 음수.stack에 쓰이지 않는 음수 쓰면 된다.
	}
	temp = stack[top];
	top--; //pop해도 데이터가 삭제되지는 않는다.
	return temp;
}
void main()
{
	int i;
	push(1); //push로 입력
	push(2);
	push(3);
	push(4);
	push(5);

	for (i = 0; i < 5; i++) //pop으로 데이터 출력
	{
		printf("%d\n", pop());
	}
}

#if 0
void main()
{
addoperad(2);
addoperand(3);
addoperator('+');
showanswer();
#endif