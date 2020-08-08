#include <stdio.h>
#include <stdlib.h>
struct node
{
	int data;
	struct node* left;
	struct node* right;
};
struct node* root = 0;
int leaf = 0;
struct node **stack = 0;
int top = -1;
void print_all(struct node* cur)
{
	if (cur == 0)
	{
		return;
	}
	print_all(cur->left);
	printf("%d\n", cur->data);
	print_all(cur->right);
}
struct node* pop()
{
	if (top == -1)
	{
		return 0;
	}
	struct node *tmp = stack[top];
	top--;
	return tmp;
}
void push(struct node* data)
{
	top++;
	stack[top] = data;
	return;
}
void cal_leaf()
{
	int in = 0;
	int flag = 0;
	struct node *cur = root;
	struct node *prev = 0;
	while (1)
	{
		if (cur == 0)
		{
			break;
		}
		if (flag==0)
		{
			if (cur->left != 0)
			{
				push(cur->left);
				in = in+1;
			}
			flag = 1;
		}
		else if (flag==1)
		{
			if (cur->right != 0)
			{
				push(cur->right);
				in = in+2;
			}
			flag = 2;
		}
		else
		{
			if (in == 0)
			{
				leaf++;
			}
			cur = pop();
			in = 0;
			flag = 0;
		}
		
	}
}
int main()
{
	struct node* cur, *del_node;
	int N, *tmp, del;
	scanf("%d", &N);
	tmp = (int*)malloc(sizeof(int) * N);
	stack = (struct node**)malloc(sizeof(struct node*)*N);
	for (int i = 0; i < N; i++)
	{
		int data;
		scanf("%d", &data);
		tmp[i] = data;
	}
	scanf("%d", &del);
	for (int i = 0; i < N; i++)
	{
		struct node* new1 = (struct node*)malloc(sizeof(struct node));
		new1->data = i;
		new1->left = new1->right = 0;
		if (root == 0)
		{
			root = new1;
			cur = new1;
		}
		else
		{
			if (cur->data == tmp[i])
			{
				if (cur->left == 0)
				{
					cur->left = new1;
				}
				else
				{
					cur->right = new1;
				}
			}
			else
			{
				if (cur->left->data == tmp[i])
				{
					cur = cur->left;
					cur->left = new1;
				}
				else
				{
					cur = cur->right;
					cur->right = new1;
				}
			}
		}
		if (del == i)
		{
			del_node = cur;
		}
	}
	if (del_node->left->data == del)
	{
		del_node->left = 0;
	}
	else if (del_node->right->data == del)
	{
		del_node->right = 0;
	}
	cal_leaf();
	printf("%d\n", leaf);
	return 0;
}