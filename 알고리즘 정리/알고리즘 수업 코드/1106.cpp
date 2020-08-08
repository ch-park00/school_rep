#include <stdio.h>
#include <stdlib.h>
#define CRT_NO_WARNINGS
struct Huff
{
	char c;
	int cnt;
	struct Huff *next;
	struct Huff *left;
	struct Huff *right;
};
struct Huff *head;
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
int isinHuff(char t)
{
	struct Huff *temp = head;
	while (temp != 0)
	{
		if (temp->c == t)
		{
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}
struct Huff * findHuff(char t)
{
	struct Huff *temp = head;
	while (temp!=0)
	{
		if (temp->c == t)
		{
			return temp;
		}
		temp = temp->next;
	}
}
void addnewchar(char t)
{
	struct Huff *new1 = (struct Huff*)malloc(sizeof(struct Huff));
	new1->c = t;
	new1->cnt = 1;
	new1->next = 0;
	new1->left = new1->right = 0;
	if (head == 0)
	{
		head = new1;
	}
	else
	{
		struct Huff *temp = head;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
void getdatainfo(FILE *f)
{
	while (!feof(f))
	{
		char t;
		fscanf(f, "%c", &t);
		if (t == 0)
		{
			break;
		}
		if (isinHuff(t) == 1)
		{
			struct Huff *temp = findHuff(t);
			temp->cnt = temp->cnt + 1;
		}
		else
		{
			addnewchar(t);
		}
		t = 0;
	}
}
struct Huff* findsmallestfrequency()
{
	int idx = 999999;
	if (head == 0)
	{
		return 0;
	}
	struct Huff *temp = head;
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
			struct Huff *temp1 = temp->next;
			temp->next = temp->next->next;
			temp1->next = 0;
			return temp1;
		}
		temp = temp->next;
	}
}
struct Huff* createTree(struct Huff *first, struct Huff *second)
{
	struct Huff *new1 = (struct Huff *)malloc(sizeof(struct Huff));
	new1->c = 0;
	new1->left = first;
	new1->right = second;
	new1->next = 0;
	new1->cnt = new1->left->cnt + new1->right->cnt;
	return new1;
}
void addToSLL(struct Huff *tree)
{
	struct Huff *temp = head;
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
struct Huff * buildbuffmantree()
{
	while (1)
	{
		struct Huff *first = findsmallestfrequency();
		struct Huff *second = findsmallestfrequency();

		if (second == 0)
		{
			return first;
		}

		struct Huff *temp = createTree(first, second);
		addToSLL(temp);
	}
}


void showall(struct Huff *htree)
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
	char *code = (char *)malloc(sizeof(char)*idx + 1);

	for (int j = 0; j < idx; j++)
	{
		code[j] = stack_show(j);
	}
	code[idx] = 0;
	return code;
}
void inorder_traversal(struct Huff *tree)
{
	if (tree == 0)
	{
		pop();
		return;
	}
	else
	{
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
}
void showhuffmantree(struct Huff *htree)
{
	inorder_traversal(htree);
}
int main()
{
	int idx = 0;
	FILE *f = fopen("alice.txt", "rt");
	getdatainfo(f);
	struct Huff *temp = head;
	while (temp != 0)
	{
		printf("%c %d\n", temp->c, temp->cnt);
		temp = temp->next;
	}
	
	struct Huff *htree = buildbuffmantree();
	// huffman tree로부터 코드 생성
	printf("CODE\n");
	showhuffmantree(htree);//htree로부터 코드 생성하고 출력.;
	fclose(f);
	return 0;
}