#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Sz 100

struct value //value값 저장하는 구조체
{
	int age;
	char *hometown;
	char *hobby;
};
struct hash //hash table
{
	char *key;
	struct value val;
	struct hash *left;
	struct hash *right;
};
struct hash *hashtable[Sz]; 


//각 글자의 아스키코드값을 더하고 100으로 나눈 나머지로 인덱스위치 결정
int myhashfucntion(char *key)
{
	int sum = 0;
	for (int i = 0; i < strlen(key); i++)
	{
		sum = sum + key[i];
	}
	return (sum%Sz);
}

//hashtable에서 찾는 key값이 있는지 확인
struct hash * searchhashtable(char *key)
{
	int loc = myhashfucntion(key);
	struct hash * cur = hashtable[loc];

	while (1)
	{
		if (cur == 0)
		{
			return 0;
		}
		else
		{
			if (strcmp(cur->key, key) > 0)
			{
				cur = cur->left;
			}
			else if (strcmp(cur->key,key)<0)
			{
				cur = cur->right;
			}
			else
			{
				return cur;
			}
		}
	}
}
void add2hash(char *name, int age, char *city, char *hobby)
{
	int location = -1;
	if (searchhashtable(name) != 0) //키값이 같은 데이터가 들어온 경우
	{
		return;
	}
	struct hash *cur = (struct hash *)malloc(sizeof(struct hash));
	cur->left = 0;
	cur->right = 0;
	cur->val.age = age;
	cur->val.hometown = (char *)malloc(strlen(city) + 1); //뒤에는 null문자가 있어야 한다
	strcpy(cur->val.hometown, city);
	cur->val.hobby = (char *)malloc(strlen(hobby) + 1);
	strcpy(cur->val.hobby, hobby);
	cur->key = (char *)malloc(strlen(name) + 1);
	strcpy(cur->key, name);
	location = myhashfucntion(name);
	if (hashtable[location] == 0) //collision 없음
	{
		hashtable[location] = cur;
		return;
	}
	else
	{
		struct hash *temp = hashtable[location];
		while (1)
		{
			if (strcmp(temp->key, cur->key) > 0)
			{
				if (temp->left == 0)
				{
					temp->left = cur;
					return;
				}
				temp = temp->left;
			}
			else
			{
				if (temp->right == 0)
				{
					temp->right = cur;
					return;
				}
				temp = temp->right;
			}
		}
	}
}

void main()
{
	struct hash *result = 0;
	add2hash("kim", 19, "seoul", "travel");
	add2hash("james", 20, "newyork", "cooking");
	add2hash("jane", 21, "incheon", "book");
	add2hash("tom", 22, "jeju", "hiking");
	add2hash("lee", 18, "busan", "fising");
	add2hash("컥컥", 18, "busan", "fising");
	result = searchhashtable("");
	if (result == 0)
	{
		printf("no key\n");
	}
	else
	{
		printf("%s: %s %d %s\n", result->key, result->val.hometown,
			result->val.age, result->val.hobby);
	}
}