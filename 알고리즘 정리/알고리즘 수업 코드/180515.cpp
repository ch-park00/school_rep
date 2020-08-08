#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *left;
	struct node *right;
};
struct node *root = 0;
struct node *removenode(struct node* p,int i);
struct node * Findleast(struct node *n) //node n부터 시작해 가장 작은 노드 찾고 그 주소 반환하는 함수
{
	struct node *p = n;
	while (1)
	{
		if (p->left != 0)
		{
			p = p->left;
		}
		else
		{
			return p;
		}
	}
}
struct node * foundMatch(struct node *n) //실제로 노드 n 삭제
{
	if (n->left == 0 && n->right == 0) //child가 존재하지 않는다
	{
		free(n);
		return 0; //child가 없으니까 0반환
	}
	else if (n->left != 0 && n->right != 0)//child 2명 존재
	{
		struct node *successor = Findleast(n->right); //후계자 찾기.오른쪽에서 가장 작은값 찾기
		n->data = successor->data; //후계자의 데이터로 n을 덮어쓴다.
		n->right = removenode(n->right, successor->data); //오른쪽에서 일어난 이동을 처리
		return n;
	}
	else if (n->left != 0) //오른쪽이 비어있을때
	{
		struct node *temp = n->left;
		free(n);
		return temp; //child 주소를 반환함
	}
	else //왼쪽이 비어있을 때
	{
		struct node *temp = n->right;
		free(n);
		return temp;
	}
}
struct node * removenode(struct node *n, int i)
{
	if (n == 0) //찾는 데이터를 가진 노드가 존재하지 않는다
	{
		return 0;
	}

	if (n->data == i) // 지울 노드를 찾았음
	{
		return foundMatch(n); 
	}
	else if (n->data > i) //현 노드값이 지울 데이터보다 크다 왼쪽으로 내려가야함
	{
		n->left=removenode(n->left, i); //삭제 노드가 가진 child가 존재.그리고 연결하는 과정
		return n;
	}
	else
	{
		n->right=removenode(n->right, i);
		return n;
	}
}


struct node * CreateNode(int i)
{
	struct node *p = (struct node *)malloc(sizeof(struct node));
	p->data = i;
	p->left = 0;
	p->right = 0;
	return p;
}
void addToBST(int i)
{
	struct node *p = CreateNode(i);
	if (root == 0)
	{
		root = p;
		return;
	}
	else
	{
		struct node *q = root;
		while (1)
		{
			if (p->data > q->data)
			{
				if (q->right == 0)
				{
					q->right = p;
					return;
				}
				else
				{
					q = q->right;
				}
			}
			else
			{
				if (q->left == 0)
				{
					q->left = p;
					return;
				}
				else
				{
					q = q->left;
				}
			}
		}
	}
}

void main()
{
	addToBST(50);
	addToBST(25);
	addToBST(75);
	addToBST(10);
	addToBST(35);
	addToBST(30);

	printf("%d\n", root->left->right->data);

	root = removenode(root, 35);
	printf("%d\n", root->left->right->data);
}