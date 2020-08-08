#include <stdio.h>
#include <stdlib.h>
#if 0
struct node
{
	int data;
	struct node *left;
	struct node *right;
};
typedef struct node bst;
bst *root = 0;
void add2bst(int i)
{
	bst *p = (bst *)malloc(sizeof(bst));
	p->data = i;
	p->left = 0;
	p->right = 0;
	if (root == 0)
	{
		root = p;
		return;
	}
	else
	{
		bst *temp = root;
		while (1)
		{
			if (temp->data > p->data)
			{
				if (temp->left == 0)
				{
					temp->left = p;
					return;
				}
				temp = temp->left;
			}
			else
			{
				if (temp->right == 0)
				{
					temp->right = p;
					return;
				}
				temp = temp->right;
			}
		}
	}
}
void inorder(bst *p)
{
	if (p == 0)
	{
		return;
	}
	inorder(p->left);
	printf("%d\n", p->data);
	inorder(p->right);
}
void main()
{
	add2bst(30);
	add2bst(20);
	add2bst(10);
	add2bst(50);
	add2bst(70);
	inorder(root);
}
#endif
int heap[10] = { 0,1,2,10,9,7,6,5 };
void findlocation(int i,int a)
{
	int left = i * 2;
	int right = left + 1;
	int big = i;
	if ((heap[big] < heap[left]) && left <= a)
	{
		big = left;
	}
	if ((heap[big] < heap[right]) && right <= a)
	{
		big = right;
	}
	if (big == i)
	{
		return;
	}
	else
	{
		int temp = heap[big];
		heap[big] = heap[i];
		heap[i] = temp;
		findlocation(big, a);
	}
}
void heapify(int i)
{
	int cur = i / 2;
	while (1)
	{
		findlocation(cur,i);
		cur--;
		if (cur <= 1)
		{
			break;
		}
	}
}
void main()
{
	heapify(7);
	for (int i = 1; i <= 7; i++)
	{
		printf("%d\n", heap[i]);
	}
}