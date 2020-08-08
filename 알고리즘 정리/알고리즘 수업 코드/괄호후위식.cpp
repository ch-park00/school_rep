#include <stdio.h>
#define Sz 100
int stack[Sz];
int top = -1;
char stack_c[Sz];
int top_c = -1;
int bottom[10] = { top_c };
int pointer = 0;

int isEmpty()
{
	return (top == -1);
}
int isFull()
{
	return (top == Sz - 1);
}

int iscEmpty()
{
	return (top_c == bottom[pointer]);
}
int iscFull()
{
	return (top_c == Sz - 1);
}
void push(int i)
{
	if (isFull() == 1)
	{
		return;
	}
	top++;
	stack[top] = i;
}
int pop()
{
	if (isEmpty() == 1)
	{
		return -999;
	}
	else
	{
		int temp = stack[top];
		top--;
		return temp;
	}
}
void push_c(char a)
{
	if (iscFull() == 1)
	{
		return;
	}
	top_c++;
	stack_c[top_c] = a;
}
char pop_c()
{
	if (iscEmpty() == 1)
	{
		return 0;
	}
	else
	{
		char temp = stack_c[top_c];
		top_c--;
		return temp;
	}
}
void tfoperand(int i)
{
	push(i);
}
void Calculate(char op)
{
	int a, b;
	a = pop();
	b = pop();
	if (a == -999 || b == -999)
	{
		printf("Error\n");
		return;
	}
	else
	{
		switch (op)
		{
		case '+':
			push(a + b);
			break;
		case '-':
			push(b - a);
			break;
		case '*':
			push(a*b);
			break;
		case '/':
			push(b / a);
			break;
		default:
			printf("unexpected Error\n");
			break;
		}
	}
}
void tfoperator(char a)
{
	if (iscEmpty() == 1)
	{
		push_c(a);
	}
	else
	{
		char temp = stack_c[top_c];
		if ((a == '*' || a == '/') && (temp == '+' || temp == '-'))
		{
			push_c(a);
		}
		else
		{
			top_c--;
			Calculate(temp);
			push_c(a);
		}
	}
}
void postfix(char a)
{
	if (a == '(')
	{
		pointer++;
		bottom[pointer] = top_c;
	}
	else
	{
		while (top_c > bottom[pointer])
		{
			char temp = pop_c();
			Calculate(temp);
		}
		pointer--;
	}
}
void showans()
{
	while (iscEmpty() != 1)
	{
		char temp = pop_c();
		Calculate(temp);
	}
	printf("°á°ú:%d\n", pop());
}
void main()
{
	tfoperand(3);
	tfoperator('*');
	postfix('(');
	tfoperand(3);
	tfoperator('-');
	tfoperand(2);
	postfix(')');
	showans();
}