#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
	char c;
	int cnt;
	struct node *next;
	struct node *left;
	struct node *right;
};
struct node *head = 0;
struct data
{
	char data;
	struct data *next;
};
struct data *stack = 0;
void push(char data)
{
	struct data *new1 = (struct data*)malloc(sizeof(struct data));
	new1->data = data;
	new1->next = stack;
	stack = new1;
}
char pop()
{
	if (stack == 0)
	{
		return -1;
	}
	struct data *temp1 = stack;
	char temp = stack->data;
	stack = stack->next;
	free(temp1);
	return temp;
}
void addcharfreq(char a, int cnt)
{
	struct node *new1 = (struct node *)malloc(sizeof(struct node));
	new1->c = a;
	new1->cnt = cnt;
	new1->next = new1->left = new1->right = 0;

	if (head == 0)
	{
		head = new1;
	}
	else
	{
		struct node *temp = head;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
struct node* findsmallestfrequency()
{
	if (head == 0)
	{
		return 0;
	}
	int idx = 999999;
	struct node *temp = head;
	while (temp != 0)
	{
		if (temp->cnt < idx)
		{
			idx = temp->cnt;
		}
		temp = temp->next;
	}
	temp = head;
	if (head->cnt == idx)
	{
		head = head->next;
		temp->next = 0;
		return temp;
	}
	while (temp != 0)
	{
		if (temp->next->cnt == idx)
		{
			struct node *temp1 = temp->next;
			temp->next = temp->next->next;
			temp1->next = 0;
			return temp1;
		}
		temp = temp->next;
	}
}
struct node* createTree(struct node *first, struct node *second)
{
	struct node *new1 = (struct node *)malloc(sizeof(struct node));
	new1->c = 0;
	new1->left = first;
	new1->right = second;
	new1->next = 0;
	new1->cnt = new1->left->cnt + new1->right->cnt;
	return new1;
}
void addToSLL(struct node *tree)
{
	struct node *temp = head;
	if (head == 0)
	{
		head = tree;
		return;
	}
	while (temp->next != 0)
	{
		temp = temp->next;
	}
	temp->next = tree;
}
struct node * buildbuffmantree()
{
	while (1)
	{
		struct node *first = findsmallestfrequency();
		struct node *second = findsmallestfrequency();

		if (second == 0)
		{
			return first;
		}

		struct node *temp = createTree(first, second);
		addToSLL(temp);
	}
}


void showall(struct node *htree)
{
	if (htree == 0)
	{
		return;
	}
	showall(htree->left);
	printf("%c %d\n", htree->c, htree->cnt);
	showall(htree->right);
}
int howmanystack()
{
	int idx = 0;
	struct data *temp = stack;
	while (temp != 0)
	{
		temp = temp->next;
		idx++;
	}
	return idx;
}
char stack_show(int idx_end)
{
	int idx = howmanystack() - idx_end;
	int cnt = 1;
	struct data *temp = stack;
	while (cnt < idx)
	{
		temp = temp->next;
		cnt++;
	}
	return temp->data;
}
char* showcode()
{
	int idx = howmanystack();
	char *code = (char *)malloc(idx+1);

	for (int j = 0; j < idx; j++)
	{
		code[j] = stack_show(j);
	}
	code[idx] = 0;
	return code;
}
void inorder_traversal(struct node *tree)
{
	if (tree == 0)
	{
		pop();
		return;
	}
	push('0');
	inorder_traversal(tree->left);
	if ((tree->left == 0) && (tree->right == 0))
	{
		printf("%c %s\n", tree->c, showcode());
	}
	push('1');
	inorder_traversal(tree->right);
	pop();
}
void showhuffmantree(struct node *htree)
{
	inorder_traversal(htree);
}
int main()
{
	addcharfreq('a', 10);
	addcharfreq('b', 300);
	addcharfreq('c', 1);
	addcharfreq('k', 50);
	addcharfreq('x', 20);
	struct node *htree = buildbuffmantree(); //최종적으로 완성된 huffmantree 반환
	printf("TREE\n");
	showall(htree);
	// huffman tree로부터 코드 생성
	printf("CODE\n");
	showhuffmantree(htree);//htree로부터 코드 생성하고 출력.

	return 0;
}