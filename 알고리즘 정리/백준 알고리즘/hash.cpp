#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Sz 100
typedef struct
{
	int num;
	char* name;
}value;
struct hash
{
	char* key;
	value val;
	struct hash* next;
};
struct hash* table[Sz] = { 0 };


int hashFunction(const char* data)
{
	int tmp = 0;
	for (int i = 0; i < strlen(data); i++)
	{
		tmp += data[tmp];
	}
	return ((tmp / strlen(data)) % Sz);
}
int keycheck(const char* key_, int index)
{
	struct hash *tmp = table[index];
	while (tmp != 0)
	{
		if (strcmp(tmp->key, key_) == 0)	return 1;
		tmp = tmp->next;
	}
	return 0;
}
void add2Hash(const char* key_, int num_, const char* name_)
{
	int index = hashFunction(key_);
	if (keycheck(key_, index) == 1)
	{
		printf("Duplicate key");
		return;
	}
	struct hash* new1 = (struct hash*)malloc(sizeof(struct hash));
	new1->key = (char*)malloc(strlen(key_) + 1);
	strcpy(new1->key, key_);
	new1->val.num = num_;
	new1->val.name = (char*)malloc(strlen(name_) + 1);
	strcpy(new1->val.name, name_);
	new1->next = 0;
	if (table[index] == 0)
	{
		table[index] = new1;
	}
	else
	{
		struct hash* tmp = table[index];
		while (tmp->next != 0)	tmp = tmp->next;
		tmp->next = new1;
	}
}
int main()
{
	add2Hash("incheon", 201401653, "park");

	return 0;
}