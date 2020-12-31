#include <stdio.h>
#include <stdlib.h>
#define arr_size 6
#if 0
struct node
{
	int data;
	struct node *left;
	struct node *right;
};
struct node *root = 0;


void add2BST(int data)
{
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->data = data;
	new1->left = new1->right = 0;
	
	if (root == 0)
	{
		root = new1;
	}
	else
	{
		struct node *cur = root;
		while (cur != 0)
		{
			if (cur->data > data)
			{
				if (cur->left == 0)
				{
					cur->left = new1;
					return;
				}
				cur = cur->left;
			}
			else
			{
				if (cur->right == 0)
				{
					cur->right = new1;
					return;
				}
				cur = cur->right;
			}
		}
	}
}

void inorder(struct node *cur)
{
	if (cur == 0)
	{
		return;
	}
	inorder(cur->left);
	printf("%d\n", cur->data);
	inorder(cur->right);
}
struct node *find_least(struct node *cur)
{
	struct node *tmp = cur;
	while (cur->left != 0)
	{
		cur = cur->left;
	}
	return cur;
}
struct node* remove_node(struct node *cur, int data)
{
	if (cur == 0)
	{
		return 0;
	}
	if (cur->data == data)
	{
		//리프 노드
		if (cur->left == 0 && cur->right == 0)
		{
			free(cur);
			return 0;
		}
		//오른쪽 자식만 존재
		else if (cur->left == 0)
		{
			struct node *ret = cur->right;
			free(cur);
			return ret;
		}
		//왼쪽 자식만 존재
		else if (cur->right == 0)
		{
			struct node *ret = cur->left;
			free(cur);
			return ret;
		}
		//자식이 둘 다 존재
		else
		{
			struct node *tmp = find_least(cur->right);
			cur->data = tmp->data;
			cur->right = remove_node(cur->right, tmp->data);
			return cur;
		}
		
	}
	
	else if (cur->data > data)
	{
		cur->left = remove_node(cur->left, data);
		return cur;
	}
	else
	{
		cur->right = remove_node(cur->right, data);
		return cur;
	}
}
int main()
{
	add2BST(10);
	add2BST(5);
	add2BST(20);
	add2BST(7);
	inorder(root);
	remove_node(root, 10);
	inorder(root);
	return 0;
}
#endif

int find_result(int *arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (arr[i] == i)
		{
			return i;
		}
	}
	return -1;
}
int find_bs(int *arr, int len, int start, int end)
{
	int cur_idx;
	int fst = start;
	int fns = end;
	while (1)
	{
		cur_idx= (fst + fns) / 2;
		if (arr[cur_idx] == cur_idx)
		{
			return cur_idx;
		}
		else
		{
			if (arr[cur_idx] > cur_idx)
			{
				fns = cur_idx - 1;
			}
			else
			{
				fst = cur_idx + 1;
			}
		}
		if (fst < -1 || fns>5)
		{
			return -1;
		}
	}
}
int main()
{
	int arr[arr_size] = { -3,-1,0,3,5,7 };
	int result1 = find_result(arr, arr_size);
	int result2 = find_bs(arr, arr_size, 0, arr_size);
	printf("%d %d\n", result1, result2);
	return 0;
}