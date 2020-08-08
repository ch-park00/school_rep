#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_NO_WARNINGS

struct hnode
{
	char data;
	int cnt;
	char *code;
	struct hnode *next;
	struct hnode *left;
	struct hnode *right;
};
struct hnode *head = 0;
struct s
{
	char data;
	struct s *next;
};
struct codetable
{
	char data;
	char *code;
	struct codetable *next;
};
struct s *stack = 0;
struct codetable *key = 0;
void push(char data)
{
	struct s *new1 = (struct s*)malloc(sizeof(struct s));
	new1->data = data;
	new1->next = stack;
	stack = new1;
}
char pop()
{
	if (stack == 0)
	{
		return 0;
	}
	struct s *temp = stack;
	char r = temp->data;
	stack = stack->next;
	free(temp);
	return r;
}
int find_data(char data)
{
	struct hnode *temp = head;
	while (temp != 0)
	{
		if (temp->data == data)
		{
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}
void add2codetable(char data, char *code)
{
	struct codetable *new1 = (struct codetable*)malloc(sizeof(struct codetable));
	new1->data = data;
	new1->code = code;
	new1->next = 0;

	if (key == 0)
	{
		key = new1;
	}
	else
	{
		struct codetable *temp = key;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
void add2hnode(char data)
{
	if (find_data(data)==1)
	{
		struct hnode *temp = head;
		while (temp != 0)
		{
			if (temp->data == data)
			{
				break;
			}
			temp = temp->next;
		}
		temp->cnt++;
	}
	else
	{
		struct hnode *new1 = (struct hnode*)malloc(sizeof(struct hnode));
		new1->data = data;
		new1->cnt = 1;
		new1->next = new1->left = new1->right = 0;

		if (head == 0)
		{
			head = new1;
		}
		else
		{
			struct hnode *temp = head;
			while (temp->next != 0)
			{
				temp = temp->next;
			}
			temp->next = new1;
		}
	}
}
int howmanychar()
{
	struct hnode *temp = head;
	int cnt = 0;
	while(temp!=0)
	{
		temp = temp->next;
		cnt++;
	}
	return cnt;
}
struct hnode* findsmallest()
{
	if (head == 0)
	{
		return 0;
	}
	struct hnode *temp = head;
	int min_cnt = 99999;
	while (temp != 0)
	{
		if (min_cnt > temp->cnt)
		{
			min_cnt = temp->cnt;
		}
		temp = temp->next;
	}

	if (head->cnt == min_cnt)
	{
		struct hnode *r = head;
		head = head->next;
		r->next = 0;
		return r;
	}
	else
	{
		struct hnode *r = head;
		while (r != 0)
		{
			if (r->next->cnt == min_cnt)
			{
				break;
			}
			r = r->next;
		}
		struct hnode *temp1 = r->next;
		r->next = temp1->next;
		temp1->next = 0;
		return temp1;
	}
}
struct hnode* createTree(struct hnode *first, struct hnode *second)
{
	struct hnode *new1 = (struct hnode*)malloc(sizeof(struct hnode));
	new1->left = first;
	new1->right = second;
	new1->cnt = first->cnt + second->cnt;
	new1->next = 0;
	return new1;
}
void add2SLL(struct hnode *new1)
{
	if (head == 0)
	{
		head = new1;
		return;
	}
	struct hnode *temp = head;
	while (temp->next != 0)
	{
		temp = temp->next;
	}
	temp->next = new1;
}
struct hnode* buildhtree()
{
	while (1)
	{
		struct hnode *first = findsmallest();
		struct hnode *second = findsmallest();

		if (second == 0)
		{
			return first;
		}
		struct hnode *new_tree = createTree(first, second);
		add2SLL(new_tree);
	}
}

char * showcode()
{
	int stack_cnt = 0;
	struct s *temp = stack;
	while (temp != 0)
	{
		temp = temp->next;
		stack_cnt++;
	}
	char *s = (char *)malloc(sizeof(char)*stack_cnt + 1);
	temp = stack;
	for (int i = 0; i < stack_cnt; i++)
	{
		temp = stack;
		for (int k = 0; k < i; k++)
		{
			temp = temp->next;
		}
		s[stack_cnt - i-1] = temp->data;
	}
	s[stack_cnt] = 0;
	return s;

}
void inorder_traversal(struct hnode *cur, FILE *f)
{
	if (cur == 0)
	{
		pop();
		return;
	}
	push('0');
	inorder_traversal(cur->left,f);
	if (cur->left == 0 && cur->right == 0)
	{
		char *s = showcode();
		char temp = strlen(s);
		cur->code = (char*)malloc(sizeof(char)*strlen(s) + 1);
		strcpy(cur->code, s);
		add2codetable(cur->data, s);
		printf("%c : %s\n", cur->data, cur->code);
		fwrite(&cur->data, 1, 1, f);
		fwrite(&temp, 1, 1, f);
		fwrite(cur->code, strlen(s), 1, f);
	}
	push('1');
	inorder_traversal(cur->right,f);
	pop();
}
char *getcode(char data)
{
	struct codetable *temp = key;
	while (temp != 0)
	{
		if (temp->data == data)
		{
			return temp->code;
		}
		temp = temp->next;
	}
}
int main()
{
	char data;
	FILE *f = fopen("alice.txt", "rt");
	FILE *f1 = fopen("alice.dec", "wb");
	while (!(feof(f)))
	{
		fscanf(f, "%c", &data);
		if (data == 0)
		{
			break;
		}
		add2hnode(data);
		data = 0;
	}
	char cnt = (char)howmanychar();
	//총 몇개의 문자가 있는지 입력한다
	printf("%d\n", cnt);
	fwrite(&cnt, 1, 1, f1);
	char sk = 0;
	struct hnode *temp = head;
	head=buildhtree();
	
	//inorder로 모든 노드방문하면서 코드 생성. 이때 코드테이블을 입력
	inorder_traversal(head, f1);
	//원 내용을 코드 적용해서 입력
	long k = ftell(f1);
	fseek(f, 0, SEEK_SET);
	fseek(f1, sizeof(int), SEEK_CUR);
	//데이터 입력할 버퍼.1바이트 찰때마다 쓴다.
	char buffer = 0x00;
	int shift_cnt = 7;
	int bit_cnt = 0;
	//파일의 처음부터 끝까지 문자 하나하나씩 보면서 코드로 변환
	while (!(feof(f)))
	{
		fscanf(f, "%c", &data);
		if (data == 0)
		{
			break;
		}
		char *s = getcode(data);
		for (int i = 0; i < strlen(s); i++)
		{
			//0일 경우에는 이미 0이 입력되어 있으므로 굳이 or연산 안해도 됨
			if (s[i] == '1')
			{
				char temp = 1 << shift_cnt;
				buffer = (temp | buffer);
			}
			shift_cnt--;
			bit_cnt++;
			//8비트 모두 다 찼을 경우에는 
			if (shift_cnt < 0)
			{
				shift_cnt = 7;
				fwrite(&buffer, 1, 1, f1);
				buffer = 0x00;
			}
		}
		data = 0;
	}
	if (shift_cnt != 7)
	{
		fwrite(&buffer, 1, 1, f1);
	}
	fseek(f1, k, SEEK_SET);
	fwrite(&bit_cnt, sizeof(int), 1, f1);
	fclose(f);
	fclose(f1);
	return 0;
}