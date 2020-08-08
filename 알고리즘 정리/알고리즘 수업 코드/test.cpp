
#if 0
#include<stdio.h>
#include<stdlib.h>

//bst 2
struct node {
	int i;
	int num;
	struct node *left;
	struct node *right;
};
struct node *root = 0;



void addBST(int i)
{
	struct node *_new = (struct node*)malloc(sizeof(struct node));
	_new->left = 0;
	_new->right = 0;
	_new->i = i;
	_new->num = 0;

	if (root == 0)
	{
		root = _new;
		return;
	}
	struct node *t = root;

	while (1)
	{
		if (t->i == _new->i) //같은게 있음
		{
			t->num++;
			free(_new);
			return;
		}
		else if (t->i > _new->i)
		{
			if (t->left == 0)
			{
				t->left = _new;
				return;
			}
			t = t->left;
		}
		else //새로 들어온게 더큼
		{
			if (t->right == 0)
			{
				t->right = _new;
				return;
			}
			t = t->right;
		}
	}

}

void Inorder_travel(struct node *t)
{
	if (t == 0)
	{
		return;
	}
	Inorder_travel(t->left);
	printf("%d ", t->i);
	if (t->num != 0)
	{
		printf("%d ", t->num+1);
	}
	Inorder_travel(t->right);
	return;
}

int main(void)
{
	int i;
	while (1)
	{
		scanf_s("%d", &i);
		if (i == -1)
		{
			Inorder_travel(root);
			return 0;
		}
		addBST(i);
	}
	return 0;
}




struct node {
	int i;
	int num;
	struct node *left;
	struct node *right;
};
struct node *root = 0;



void addBST(int i)
{
	struct node *_new = (struct node*)malloc(sizeof(struct node));
	_new->left = 0;
	_new->right = 0;
	_new->i = i;
	_new->num = 0;

	if (root == 0)
	{
		root = _new;
		return;
	}
	struct node *t = root;

	while (1)
	{
		if (t->i == _new->i) //같은게 있음
		{
			t->num++;
			free(_new);
			return;
		}
		else if (t->i > _new->i)
		{
			if (t->left == 0)
			{
				t->left = _new;
				return;
			}
			t = t->left;
		}
		else //새로 들어온게 더큼
		{
			if (t->right == 0)
			{
				t->right = _new;
				return;
			}
			t = t->right;
		}
	}

}

void Inorder_travel(struct node *t)
{
	if (t == 0)
	{
		return;
	}
	Inorder_travel(t->left);
	for (int j = 0; j <= t->num; j++)
	{
		printf("%d ", t->i);
	}
	Inorder_travel(t->right);
	return;
}

int main(void)
{
	int i;
	while (1)
	{
		scanf_s("%d", &i);
		if (i == -1)
		{
			Inorder_travel(root);
			return 0;
		}
		addBST(i);
	}
	return 0;
}




//stack 1
int stack[5];
int top = -1;

void push(int n)
{
	if (top == 4)
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
		return -3414;
	}
	int temp = stack[top];
	top--;
	return temp;
}

int main(void)
{
	int i;
	int sum=0;

	while (1)
	{
		scanf_s("%d", &i);
		if (i == -100)
		{
			if (top == -1)
			{
				return 0;
			}
			printf("%d", stack[top]);
			break;
		}
		if (i == -1)
		{
			while (top != -1)
			{
				sum = sum + pop();
			}
			push(sum);
			continue;
		}
		push(i);

	}
	return 0;
}








//dll 2번
struct node {
	int n;
	struct node *next;
	struct node *prev;
};

struct node *head = 0;

struct node* find(int i)
{
	struct node *t = head;
	while (1)
	{

		if (t == 0)
		{
			return 0;
		}
		if (t->n == i)
		{
			return t;
		}
		t = t->next;
	}
}

void addNode(int _data)
{
	struct node *_new = (struct node*)malloc(sizeof(struct node));
	_new->next = 0;
	_new->prev = 0;
	_new->n = _data;
	if (head == 0)
	{
		head = _new;
		return;
	}
	struct node *t = head;
	while (1)
	{
		if (t->next == 0)
		{
			t->next = _new;
			_new->prev = t;
			return;
		}
		t = t->next;
	}

}

void showReverse(void)
{
	struct node *t = head;
	if (head == 0)
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
		printf("%d", t->n);
		t = t->prev;
	}
}

void delNode(struct node* t)
{
	if (t == head)
	{
		if (t->next == 0)
		{
			free(t);
			head = 0;
			return;
		}
		head = t->next;
		t->next->prev = 0;
		free(t);
		return;
	}
	if (t->next == 0)
	{
		t->prev->next = 0;
		free(t);
		return;
	}
	t->prev->next = t->next;
	t->next->prev = t->prev;
	free(t);
	return;
}


int main(void)
{
	int i;
	struct node *result = 0;
	while (1)
	{
		scanf_s("%d", &i);
		if (i < 0)
		{
			break;
		}
		result = find(i); //찾으면 주소 못찾으면 0반환
		if (result == 0)
		{
			addNode(i);
		}
		else
		{
			delNode(result);
			addNode(i);
		}
	}

	showReverse();



	return 0;

}




//dll 1번
struct node {
	int n;
	struct node *next;
	struct node *prev;
};

struct node *head = 0;

int find(int i)
{
	struct node *t = head;
	while (1)
	{
		if (t == 0)
		{
			return 0;
		}
		if (t->n == i)
		{
			return 1;
		}
		t = t->next;
	}
}

void addNode(int _data)
{
	struct node *_new = (struct node*)malloc(sizeof(struct node));
	_new->next = 0;
	_new->prev = 0;
	_new->n = _data;
	if (head == 0)
	{
		head = _new;
		return;
	}
	struct node *t = head;
	while (1)
	{
		if (t->next == 0)
		{
			t->next = _new;
			_new->prev = t;
			return;
		}
		t = t->next;
	}

}

void showReverse(void)
{
	struct node *t = head;
	if (head == 0)
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
		printf("%d", t->n);
		t = t->prev;
	}
}


int main(void)
{
	int i;
	int result=0;
	while (1)
	{
		scanf_s("%d", &i);
		if (i < 0)
		{
			break;
		}
		result = find(i); //찾으면 1 못찾으면 0반환
		if (result == 0)
		{
			addNode(i);
		}
		else
		{
			continue;
		}
	}

	showReverse();



	return 0;

}
#endif