#include <stdio.h>

#define STACK_Sz 10
int stack[STACK_Sz];
int top = -1;
char stk[STACK_Sz];
int tp = -1;
int isEmpty()
{
	return (top == -1);
}
int isEmptystk()
{
	return (tp == -1);
}
int isFull()
{
	return (top == STACK_Sz - 1);
}
int isFullstk()
{
	return (top == STACK_Sz - 1);
}
void push(int i)
{
	if (isFull() == 1)
	{
		return;
	}
	top++;
	stack[top] = i;
	return;
}
void pushstk(char a)
{
	if (isFullstk() == 1)
	{
		return;
	}
	tp++;
	stk[tp] = a;
}
char popstk()
{
	if (isEmptystk() == 1)
	{
		return 0;
	}
	else
	{
		char res = stk[tp];
		tp--;
		return res;
	}
}
int pop()
{
	if (isEmpty() == -1)
	{
		return -999;
	}
	else
	{
		int res = stack[top];
		top--;
		return res;
	}
}
void calcPostfixOperand(int i)
{
	push(i);
}
void calcPostfixOperator(char op)
{
	int a, b, c;
	a = pop();
	b = pop();
	if (a == -999 || b == -999)
	{
		printf("Unexpected error\n");
		return;
	}
	switch (op) 
	{
	case '+':
		c = a + b;  //or push(a+b);
		break;
	case '-':
		c = b - a; //순서중요. 먼저꺼낸것이 뒤로와야한다.
		break;
	case '*':
		c = a*b;
		break;
	case '/':
		c = b / a;
		break;
	default:
		printf("Can't handle the operator\n");
		return;
	}
	push(c);


#if 0
	if (op == '+')
	{
		c = a + b;
	}
	else if (op == '*')
	{
		c = a*b;
	}
	else if (op == '-')
	{
		c = b - a;
	}
	else
	{
		c = b / a;
		
	}
	push(c);
#endif
}

void showresult()
{
	int res = 0;
	while (isEmptystk()!=1) //stk에 남아있는 연산 모두 계산 후 출력
	{
		calcPostfixOperator(popstk());
	}
	res = pop();
	if (res == -999) //stack이 비어있을때
	{
		printf("Unexpected error\n");
		return;
	}
	printf("결과:%d\n", res);
}
void tfpostfixoperand(int i)
{
	calcPostfixOperand(i);
}
void tfpostfixoperator(char op)
{
	//처음에 알맞는 op가 들어왔는지 검사하는 코드 필요
	if (isEmptystk() == 1) //스택이 비어있으면 push
	{
		pushstk(op);
	}
	else
	{
		char temp = stk[tp];
		//op의 우선순위가 stack보다 높은 경우
		if ((op == '*' || op == '/') && (stk[tp] == '+' || stk[tp] == '-'))
		{
			pushstk(op);
		}
		//우선순위가 낮은 경우
		else
		{
			char temp = popstk(); //스택에 있는 값 출력후 
			calcPostfixOperator(temp); //계산하고
			pushstk(op); //입력받은 연산자 push
		}
	}

}
//stack을 이용해 후위식(postfix) 계산하기
void main()
{
	//345+* 계산
	/*
	calcPostfixOperand(3);
	calcPostfixOperand(4);
	calcPostfixOperand(5);
	calcPostfixOperator('+');
	calcPostfixOperator('*');

	showresult();
	*/
	//3+4*5-->345*+ 중위식을 후위식으로 바꾸고 계산하기
	tfpostfixoperand(3); //3출력후 stack대입
	tfpostfixoperator('+');
	tfpostfixoperand(4);
	tfpostfixoperator('*');
	tfpostfixoperand(5); //(3+4)*5변환후계산
	showresult();
	
}