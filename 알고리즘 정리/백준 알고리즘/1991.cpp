#include <stdio.h>
#include <stdlib.h>

int num, last_idx;
char* root = 0;
int findidx(char data)
{
	for (int i = 1; i < num * 3; i++)
	{
		if (root[i] == data)
		{
			return i;
		}
	}
	return -1;
}
void add2bst(char root_, char left_, char right_)
{
	if (root[1] == 0)
	{
		root[1] = root_;
		root[2] = left_;
		root[3] = right_;
		last_idx = 3;
	}
	else
	{
		int idx = findidx(root_);
		if (idx == -1)	return;
		root[idx] = root_;
		root[idx * 2] = left_;
		root[idx * 2 + 1] = right_;
		last_idx = idx * 2 + 1;
	}
}
void do_preorder(int index)
{
	if (index > last_idx || root[index] == '.')	return;
	printf("%c", root[index]);
	do_preorder(index * 2);
	do_preorder(index * 2 + 1);
}

void do_middleorder(int index)
{

	if (index > last_idx || root[index] == '.')	return;
	do_middleorder(index * 2);
	printf("%c", root[index]);
	do_middleorder(index * 2 + 1);
}
void do_postorder(int index)
{
	if (index > last_idx || root[index] == '.')	return;
	do_postorder(index * 2);
	do_postorder(index * 2 + 1);
	printf("%c", root[index]);
}
void print_result(int start)
{
	//전위순회
	do_preorder(start);
	printf("\n");
	//중위순회
	do_middleorder(start);
	printf("\n");
	//후위순회
	do_postorder(start);
}
int main()
{
	scanf("%d", &num);
	root = (char*)calloc(3 * num, sizeof(char));
	getchar();
	for (int i = 1; i <= num; i++)
	{
		char a, b, c;
		scanf("%c %c %c", &a, &b, &c);
		add2bst(a, b, c);
		getchar();
	}
	print_result(1);
	return 0;
}