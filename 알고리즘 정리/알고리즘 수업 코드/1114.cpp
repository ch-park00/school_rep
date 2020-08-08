//Huffman tree encoding
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
struct node
{
	char c;
	char *code;
	struct node *next;
};
struct hnode
{
	char c;
	struct hnode *left;
	struct hnode *right;
};
struct hnode *root;
struct node *head;
void addHuffcode(char a, const char *code)
{
	struct node *new1 = (struct node *)malloc(sizeof(struct node));
	new1->c = a;
	new1->next = 0;
	new1->code = (char *)malloc(strlen(code) + 1);
	strcpy(new1->code, code);

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
int getNumofcode()
{
	int cnt = 0;
	struct node *temp = head;
	while (temp != 0)
	{
		temp = temp->next;
		cnt++;
	}
	return cnt;
}
//압축 코드.각각은 a,b,c,d를 의미한다.
char *codetable[4] = { (char*)"100",(char*)"11",(char*)"101",(char*)"0" };
//file 복구
int main()
{
	
	FILE *f = fopen("alice.bit", "rb");
	int numofbits = 0;
	fread(&numofbits, sizeof(int), 1, f);
	printf("총 읽을 비트:%d\n", numofbits);
	
	char andMask = 0x80;

	while (1)
	{
		char readbuf;
		int n=fread(&readbuf, sizeof(char), 1, f);
		// 다 읽은 경우
		if (n <= 0)
		{
			break;
		}
		while (1)
		{
			if (!(readbuf&andMask))
			{
				printf("0");
			}
			else
			{
				printf("1");
			}
			andMask = (andMask >> 1) & 0x7F; //이 경우 맨 앞의 비트는 부호 비트인데 시프트 시 0이 될지 1이 될지 알수 없다
			numofbits--;
			//readbuf = readbuf << 1; //이것도 가능  
			if (andMask == 0 || numofbits <= 0)
			{
				andMask = 0x80;
				break;
			}
		}
	}
	fclose(f);
	return 0;
}


int main99()
{
	char *str2write = (char *)"abbccdccbba";
	
	FILE *f = fopen("alice.bit", "wb");
	//파일 위치 이동
	//함수의 입력값은 파일버퍼,움직일 값,기준점
	//seek_set=맨처음 위치
	fseek(f, 4, SEEK_SET);
	//파일에 쓸 1비트 생성
	char oneBytebuffer = 0;
	//7,6,5,4,3,2,1 이런식으로 시프트하면서 쓰면됨.0되는순간 1바이트가 다 찼음을 의미
	int shiftcnt = 7;
	// 비트 개수 세기
	int numofbits = 0;
	//bit 단위로 파일에 입력
	for (int i = 0; i < strlen(str2write); i++)
	{
		char c = str2write[i];
		char *code = codetable[c - 'a'];
		
		for (int j = 0; j < strlen(code); j++)
		{
			//or시킬 비트
			char bitvaule = 0x00;
			if (code[j] == '1')
			{
				bitvaule = 1;
				bitvaule = bitvaule << shiftcnt;
				oneBytebuffer = oneBytebuffer | bitvaule;
			}
			shiftcnt--;
			numofbits+=1;
			if (shiftcnt < 0)
			{
				fwrite(&oneBytebuffer, sizeof(char), 1, f);
				oneBytebuffer = 0;
				shiftcnt = 7;
			}
		}
	}
	if (shiftcnt < 7)
	{
		fwrite(&oneBytebuffer, sizeof(char), 1, f);
	}
	fseek(f, 0, SEEK_SET);
	fwrite(&numofbits, sizeof(int), 1, f);
	fclose(f);
	return 0;
}
int main3(void)
{
	FILE *f = fopen("alice.encoded", "rb");
	//1. 몇개의 알파벳이 있는지 확인
	char num;
	fread(&num, sizeof(char), 1, f);
	printf("%d\n", num);

	root = (struct hnode*)malloc(sizeof(struct hnode));
	root->left = root->right = 0;
	for (int i = 0; i < num; i++)
	{
		struct hnode *temp = root;
		char c;
		fread(&c, sizeof(char), 1, f);
		char len;
		fread(&len, sizeof(char), 1, f);
		printf("%c %d :", c, len);
		for (int j = 0; j < len; j++)
		{
			char v;
			fread(&v, sizeof(char), 1, f);
			if (v == '0')
			{
				//왼쪽으로 내려가기
				if (temp->left == 0)
				{
					temp->left = (struct hnode*)malloc(sizeof(struct hnode));
					temp->left->left = temp->left->right = 0;
				}
				temp = temp->left;
			}
			else
			{
				if (temp->right == 0)
				{
					temp->right = (struct hnode*)malloc(sizeof(struct hnode));
					temp->right->left = temp->left->right = 0;
				}
				temp = temp->right;
			}
		}
		temp->c = c;
	}
	return 0;
}

int main2(void)
{
	FILE *f = fopen("alice.encoded", "rb");
	//huffman tree 복구

	//1. 몇개의 알파벳이 있는지 확인
	char num;
	fread(&num, sizeof(char), 1, f);
	printf("%d\n", num);
	for (int i = 0; i < num; i++)
	{
		char c;
		fread(&c, sizeof(char), 1, f);
		char len;
		fread(&len, sizeof(char), 1, f);
		printf("%c %d :", c, len);
		for (int j = 0; j < len; j++)
		{
			char v;
			fread(&v, sizeof(char), 1, f);
			printf("%c", v);
		}
		printf("\n");
	}
	return 0;
}
int main1(void)
{
	addHuffcode('a', "0");
	addHuffcode('b', "10");
	addHuffcode('c', "11");

	//file하나 오픈해서 바이너리 파일 생성. 읽기모드로 오픈
	FILE *f = fopen("alice.encoded", "wb");//wb->바이너리읽기
	// fwrite 파일에 쓰기
	//1단계. 총 몇개의 코드가 필요한지 확인 후 1바이트에 기록
	char numofchars = (char)getNumofcode();
	fwrite(&numofchars, sizeof(char), 1, f); //numofchars의 내용을 파일에 입력
	//2단계. 각 문자를 '문자'+'길이'+'코드'로 기록
	//3단계. 이 과정을 반복
	struct node *temp = head;
	while (temp != 0)
	{
		char c = temp->c;
		char len = (char)strlen(temp->code);
		fwrite(&c, sizeof(char), 1, f);
		fwrite(&len, sizeof(char), 1, f);

		for (int i = 0; i < len; i++)
		{
			/*
			if code[i]==0
				fwrite(0)-->이런식으로도 가능
			*/
			fwrite(&(temp->code[i]), sizeof(char), 1, f);
		}
		temp = temp->next;
	}
	
	
	// fread 파일에서 읽기
	fclose(f);
	return 0;
}