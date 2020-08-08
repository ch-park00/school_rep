#if 0
#include<stdio.h>

#define sz 10

int queue[sz];
int rear = 0;
int front = 0;

void enqueue(int i)
{
	if (front == (rear + 1) % sz)
	{
		return;
	}
	queue[rear] = i;
	rear = (rear + 1) % sz;
	return;
}

int dequeue(void)
{
	if (front == rear)
	{
		return -4444;
	}
	int temp = queue[front];
	front = (front + 1) % sz;
	return temp;
}

int main(void)
{
	enqueue(1);
	enqueue(2);
	enqueue(3);

	for (int i = 0; i < 3; i++)
	{
		printf("%d ", dequeue());
	}

	return 0;
}


#include<stdio.h>
#include<stdlib.h>



#define SZ 5

int queue[SZ];

int front = 0;
int rear = 0;

void enqueue(int n)
{
	if (front == rear)
	{
		return;
	}
	queue[rear] = n;
	rear = (rear + 1) % SZ;
	return;
}

int dequeue(void)
{
	if (front == (rear + 1) % SZ)
	{
		return -331244;
	}
	int temp = queue[front];
	rear = (rear + 1) % SZ;
	return temp;
}





#define size 10

int stack[size];

int top = -1;

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
	if (top == -1)
	{
		return -1234567;
	}
	int temp = stack[top];
	top--;
	return temp;
}




//07.09.2018
//dll
struct node {
	int n;
	struct node* next;
	struct node* prev;
};

struct node *head = 0;

struct node* creat(int _data)
{
	struct node *t = (struct node*)malloc(sizeof(struct node));
	t->n = _data;
	t->next = 0;
	t->prev = 0;
	return t;
}

void AddDll(int _data)
{
	struct node *t = creat(_data);
	struct node *p = 0;
	if (head == 0)
	{
		head = t;
		return;
	}
	p = head;
	while (1)
	{
		if (p->next == 0)
		{
			p->next = t;
			t->prev = p;
			return;
		}
		p = p->next;
	}
}

struct node* findNode(int _data)
{
	struct node *t = head;
	while (1)
	{
		if (t == 0)
		{
			printf("Can not find the node(%d)\n",_data);
			return 0;
		}
		if (t->n == _data)
		{
			return t;
		}
		t = t->next;
	}
}
void InsertAfterNode(int where, int _data)
{
	struct node *wher = findNode(where);
	struct node *_new = 0;
	if (wher == 0)
	{
		return;
	}
	_new = creat(_data);
	if (wher->next == 0)
	{
		_new->prev = wher;
		wher->next = _new;
		return;
	}
	_new->next = wher->next;
	_new->prev = wher;
	wher->next->prev = _new;
	wher->next = _new;
	return;
}

void InsertBeforeNode(int where, int _data)
{
	struct node *wher = findNode(where);
	if (wher == 0)
	{
		return;
	}
	struct node *_new = creat(_data);
	if (wher == head)
	{
		_new->next = wher;
		wher->prev = _new;
		head = _new;
		return;
	}
	_new->prev = wher->prev;
	_new->next = wher;
	wher->prev->next = _new;
	wher->prev = _new;
	return;
}

void delDll(int _data)
{
	struct node *del = findNode(_data);
	if (del == 0)
	{
		return;
	}
	if (del == head)
	{
		if (del->next == 0)
		{
			head = 0;
			free(del);
			return;
		}
		head = del->next;
		head->prev = 0;
		free(del);
		return;
	}
	if (del->next == 0)
	{
		del->prev->next = 0;
		free(del);
		return;
	}
	del->prev->next = del->next;
	del->next->prev = del->prev;
	free(del);
	return;
}

void DestroyDll(void)
{
	struct node* t = head;
	while (t != 0)
	{
		head = t->next;
		free(t);
		t = head;
	}
}

int main()
{
	struct node *t = 0;
	AddDll(3);
	AddDll(5);
	AddDll(2);

	t = head;
	while (t != 0)
	{
		printf("%d\n", t->n);
		t = t->next;
	}

	InsertAfterNode(3, 7);
	InsertAfterNode(7, 8);
	InsertAfterNode(2, 9);
	printf("삽입 후\n");

	t = head;
	while (t != 0)
	{
		printf("%d\n", t->n);
		t = t->next;
	}

	InsertBeforeNode(9, 4);
	InsertBeforeNode(3, 1);

	printf("삽입 후\n");

	t = head;
	while (t != 0)
	{
		printf("%d\n", t->n);
		t = t->next;
	}
	delDll(1);
	delDll(8);
	delDll(9);
	
	printf("삭제 후\n");

	t = head;

	while (t != 0)
	{
		printf("%d\n", t->n);
		t = t->next;
	}
}





// sll
struct node {
	int n;
	struct node *next;
};

struct node *head = 0;

struct node* creat(int a)
{
	struct node *t = (struct node*)malloc(sizeof(struct node));
	t->n = a;
	t->next = 0;
	return t;
}

void AddToSll(int _data)
{
	struct node *p = creat(_data);
	struct node *t = 0;
	if (head == 0)
	{
		head = p;
		return;
	}
	t = head;
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

struct node* FindNode(int _data)
{
	struct node *t = head;
	while (1)
	{
		if (t == 0)
		{
			printf("Can not found the node\n");
			return 0;
		}
		else if (t->n == _data)
		{
			return t;
		}
		else
		{
			t = t->next;
		}
	}
}

void InsertNode(int _where, int _data)
{
	struct node *wher = FindNode(_where);
	if (wher == 0)
	{
		return;
	}
	struct node *_new = creat(_data);
	_new->next = wher->next;
	wher->next = _new;
	return;

}

struct node* PointVal(int _data)
{
	struct node *t = head;
	while (1)
	{
		if (t->next->n == _data)
		{
			return t;
		}
		t = t->next;
	}
}

void DeleteNode(int _data)
{
	struct node* del = FindNode(_data);
	if (del == 0)
	{
		printf("Can not find the node you want to delete (%d node)\n",_data);
		return;
	}
	else if (del == head)
	{
		head = del->next;
		free(del);
		return;
	}
	struct node *p = PointVal(_data);
	p->next = del->next;
	free(del);
	return;
}

void DestroyNode(void)
{
	struct node* t = head;
	while (head != 0)
	{
		head = t->next;
		free(t);
		t = head;
	}
}

int main()
{
	struct node *t = 0;
	AddToSll(3);
	AddToSll(4);
	AddToSll(1);
	t = head;
	while (t != 0)
	{
		printf("%d\n", t->n);
		t = t->next;
	}
	InsertNode(3, 7);
	InsertNode(7, 8);
	InsertNode(1, 9);
	t = head;
	printf("추가후\n");
	while (t != 0)
	{
		printf("%d\n", t->n);
		t = t->next;
	}
	
	DeleteNode(3);
	DeleteNode(8);
	DeleteNode(9);
	t = head;
	printf("제거 후\n");
	while (t != 0)
	{
		printf("%d\n", t->n);
		t = t->next;
	}
	DestroyNode();
	t = head;
	printf("%d", t);


}
#endif