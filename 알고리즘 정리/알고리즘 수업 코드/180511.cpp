#include <stdio.h>
#include <stdlib.h>
struct node
{
	int data;

	struct node * leftPtr;  //왼쪽 가리키는 포인터
	struct node * right; //오른쪽 가리키는 포인터
};
typedef struct node TreeNode;
TreeNode * root = 0; //root가 0이면 bst가 없는 것
TreeNode * createNode(int i)
{
	TreeNode * new_one = (TreeNode*)malloc(sizeof(TreeNode));
	new_one->leftPtr = 0;
	new_one->right = 0;
	new_one->data = i;
	return new_one;
}
void addtoBST(int i)
{
	TreeNode *cur = createNode(i);
	TreeNode *p = root;
	if (root == 0)
	{
		root = cur;
		return;
	}
	while (1)
	{
		if (p->data > cur->data) //왼쪽으로 내려가야한다.
		{
			if (p->leftPtr == 0)
			{
				p->leftPtr = cur;
				return;
			}
			else
			{
				p = p->leftPtr;
			}
		}
		else
		{
			if (p->right == 0)
			{
				p->right = cur;
				return;
			}
			else
			{
				p = p->right;
			}
		}
	}
}
void main()
{
	addtoBST(50); //아무것도 없으니까 root에 저장
	addtoBST(25); //꽉 차 있으니까 밑에 저장하는데 작으니까 왼쪽 저장
	addtoBST(75); //root보다 크니까 오른쪽. 비어있으니까 거기 저장
	addtoBST(10); //25보다 작으니까 25 밑 왼쪽 저장
	addtoBST(35); //25보다 크고 50보다 작으니까 25 밑 오른쪽 저장

	printf("%d\n", root->leftPtr->right->data);
}