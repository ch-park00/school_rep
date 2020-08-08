#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_NO_WARNINGS


struct hnode
{
	char data;
	char *code;
	struct hnode *left;
	struct hnode *right;
};
struct hnode *head = 0;
void inorder_traversal(struct hnode *cur)
{
	if (cur == 0)
	{
		return;
	}
	inorder_traversal(cur->left);
	if (cur->data!=0)
	{

		printf("%c : %s\n", cur->data, cur->code);
	}
	inorder_traversal(cur->right);
}
int main()
{
	FILE *f = fopen("alice.dec", "rb");
	FILE *f1 = fopen("alice_dec.txt", "wt");
	head = (struct hnode*)malloc(sizeof(struct hnode));
	head->left = head->right = 0;
	head->data = 0;
	char cnt;
	fscanf(f, "%c", &cnt);
	//허프만 트리 복구.0-->left로 이동
	struct hnode *temp1 = head;
	for (int i = 0; i < cnt; i++)
	{
		char data;
		char len;
		char *code;
		fscanf(f, "%c%c", &data, &len);
		code = (char*)malloc(sizeof(char)*len + 1);
		struct hnode *temp1 = head;
		for (int k = 0; k < len; k++)
		{
			char temp;
			fscanf(f, "%c", &temp);
			code[k] = temp;
			if (temp == '0')
			{
				if (temp1->left == 0)
				{
					temp1->left = (struct hnode*)malloc(sizeof(struct hnode));
					temp1->data = 0;
					temp1->left->left = temp1->left->right = 0;
				}
				temp1 = temp1->left;
			}
			else
			{
				if (temp1->right == 0)
				{
					temp1->right = (struct hnode*)malloc(sizeof(struct hnode));
					temp1->right->left = temp1->right->right = 0;
					temp1->data = 0;
				}
				temp1 = temp1->right;
			}
		}
		code[len] = 0;
		temp1->data = data;
		temp1->code = (char*)malloc(sizeof(char)*len + 1);
		strcpy(temp1->code, code);
	}
	inorder_traversal(head);
	//데이터 복구
	//1.압축된 파일(비트)를 1바이트, 1비트씩 읽으면서 데이터 복구
	int bit_cnt;
	fread(&bit_cnt, sizeof(int), 1, f);
	printf("총 비트 수:%d\n", bit_cnt);
	
	//2.코드 추적하며 쓰기
	int write_bit = 0;
	char mask = 0x80;
	temp1 = head;
	while (1)
	{
		if (write_bit > bit_cnt - 1)
		{
			break;
		}
		char result;
		char temp;
		fscanf(f, "%c", &temp);
		for (int i = 0; i < 8; i++)
		{
			if (write_bit > bit_cnt - 1)
			{
				break;
			}
			result = (temp << i)&mask;
			if (result == 0)
			{
				temp1 = temp1->left;
			}
			else
			{
				temp1 = temp1->right;
			}
			if (temp1->left == 0 && temp1->right == 0)
			{
				fwrite(&temp1->data, 1, 1, f1);
				temp1 = head;
			}
			
			write_bit++;
		}
	}
	printf("쓴 비트:%d\n", write_bit);
	fclose(f);
	fclose(f1);
	return 0;
}