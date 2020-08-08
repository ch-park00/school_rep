#if 0
#include<stdio.h>
#include<stdlib.h>

//12.09.2018

//Binary Search Tree

struct node{
	int i;
	struct node *left;
	struct node *right;
};

struct node *root = 0;

void addToBST(int n)
{
	struct node *new_ = (struct node*)malloc(sizeof(struct node));
	new_->i = n;
	new_->left = new_->right =  0;

	if (root == 0)
	{
		root = new_;
		return;
	}

	struct node *t = root;
	while (1)
	{
		if (n < t->i)
		{
			if (t->left == 0)
			{
				t->left = new_;
				return;
			}
			t = t->left;
		}
		else
		{
			if (t->right == 0)
			{
				t->right = new_;
				return;
			}
			t = t->right;
		}

	}


}

void inorder_traversal(struct node *_start)
{
	if (_start == 0)
	{
		return;
	}
	inorder_traversal(_start->left);
	printf("%d", _start->i);
	inorder_traversal(_start->right);
	return;
}

int searchBST(int n)
{
	struct node *t = root;
	
	while (1)
	{
		if (t->i == n)
		{
			return 1;
		}
		if (t->i > n)
		{
			
			if (t->left == 0)
			{
				return 0;
			}
			t = t->left;
		}
		else if(t->i < n)
		{
			if (t->right == 0)
			{
				return 0;
			}
			t = t->right;
		}
	}
}

int main(void)
{
	addToBST(100);
	addToBST(50);
	addToBST(150);
	addToBST(25);
	addToBST(75);

	
	//inorder_traversal(root);

	int result = searchBST(25);
	printf("%d\n", result); // ->> 1출력 

	result = searchBST(55);
	printf("%d\n", result);//-> 0출력 (tree에 없음);
	
	return 0;
}



//Queue(Circle Queue)

#define size 10
int queue[size];

int front = 0;
int rear = 0;

void enqueue(int n)
{
	if (front == (rear + 1) % size)
	{
		return;
	}
	queue[rear] = n;
	rear = (rear + 1) % size;
	return;
}

int dequeue(void)
{
	if (front == rear)
	{
		return -123456773;
	}
	int temp = queue[front];
	front = (front + 1) % size;

	return temp;
}

int main(void)
{
	enqueue(10);
	enqueue(20);
	enqueue(5);
	
	for (int i = 0; i < 3; i++)
	{
		printf("%d\n", dequeue());
	}
	
	return 0;
}



//Stack 


#define size 10

int stack[size]; //10개를 저장
int top = -1;    //stack에 저장된 마지막 데이터의 저장 위치

void push(int n)
{
	if (top == size - 1)
	{
		return;
	}

	top++;
	stack[top] = n;
	return;
}

int pop(void)
{
	if (top == -1) //stack empty
	{
		return -123456773; 
	}
	int temp = stack[top];
	top--;
	return temp;
}

int main(void)
{
	push(10);
	push(20);
	push(30);

	for (int i = 0; i < 3; i++)
	{
		printf("%d \n", pop());
	}
	return 0;
}





//07.09.2018

// double linked list(DLL)
// SLL의 단점 보완

struct node {
	int i;
	struct node *next;
	struct node *prev;
};

struct node *head = 0;

void addToDLL(int _data)
{
	struct node *new_ = (struct node*)malloc(sizeof(struct node));
	new_->i = _data;
	new_->next = 0;
	new_->prev = 0;

	if (head == 0)
	{
		head = new_;
		return;
	}
	struct node *t = head;
	while (1)
	{
		if (t->next == 0)
		{
			new_->prev = t;
			t->next = new_;
			return;
		}
		t = t->next;

	}
}

void showDLLReverse(void)
{
	struct node *t = head;
	if (t == 0)
	{
		return;
	}
	while (1)
	{
		if (t->next == 0)
		{
			break;
		}
		t = t->next;
	}
	while (1)
	{
		if (t == 0)
		{
			return;
		}
		printf("%d ", t->i);
		t = t->prev;
	}
}

int main()
{
	addToDLL(10);
	addToDLL(20);
	addToDLL(5);

	showDLLReverse();

	return 0;
}




// singly linked list(SLL)\
// array의 단점 보완

//self-referential struct : 자기참조구조체
struct node {
	int n;
	struct node* next;
};

struct node *head = 0; //never forget head!!

void addToSLL(int _data)
{
	struct node *p = (struct node*)malloc(sizeof(struct node));
	p->n = _data;
	p->next = 0;

	if (head == 0)
	{
		head = p;
		return;
	}
	struct node *t = head;
	while (1)
	{
		if (t->next == 0)
		{
			t->next = p;
			return;
		}
		t = t->next;
	}
}

void showsll(void)
{
	struct node *p = head;
	while (p != 0)
	{
		printf("%d ", p->n);
		p = p->next;
	}
	return;
}

int main()
{
	
	addToSLL(10);
	addToSLL(20);
	addToSLL(5);

	struct node *t = head;

	showsll();

	return 0;
}




struct multi {
	int i;
	float j;
};

typedef struct multi multi;

int main(void)
{
	//동적 할당으로 구조체 저장
	//정적할당과 동적할당의 차이
	struct multi *p = (struct multi*)malloc(sizeof(struct multi));  //malloc 주소 반환 ponter로 받는다

	p->i = 10;
	p->j = 3.14;

	struct multi *q = p;




	//할당 해제
	free(p);
	
	return 0;
}


int main()
{
	//구조체의 포인터 (주소 저장)

	struct multi a;		//변수 a를 저장할 수 있는 공간이 생김
	a.i = 10; a.j = 3.14;
	struct multi *p;
	p = &a;

	printf("변경 전\n%d %0.2f\n", a.i, a.j);
	p->i = a.i+10;
	p->j = 3.33;
	printf("변경 후\n %d %0.2f\n", a.i, a.j);

	return 0;
}




typedef struct {
	int n;
	float t;
}multi;

int main()
{
	struct multi k;
	struct multi u;
	
	k.n = 10;
	k.t = 3.14;

	printf("%d %.2f", k.n, k.t);

	return 0;
}





int sigmasum(int n)
{
	if (n == 1)
	{
		return 1;
	}
	return n + sigmasum(n - 1);
}

int main()
{
	printf("%d", sigmasum(5));
	return 0;
}




int main()
{
	int a[10] = { 10,9,8,7,6,5,4,3,2,1 };
	int i, j,temp;
	for (j = 0; j <= 8; j++)
	{
		for (i = 0; i <= 8 - j; i++)
		{
			if (a[i] > a[i + 1])
			{
				temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
			}
		}
	}
	for (int z = 0; z < 10; z++)
	{
		printf("%d\n", a[z]);
	}
	 
	return 0;
}
#endif