#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define sz 30
struct data
{
	char name[20];
	int student_id;
	unsigned int age;
	//chaining
	struct data *next;
};
typedef data student;
// 이름,학번,나이를 이용해 학생데이터를 저장하는 해시 테이블 구현
//chaining 이용
student *hashtable[sz];

int hashFunction(char *_name)
{
	int len = strlen(_name);
	int result = 0;
	for (int i = 0; i < len; i++)
	{
		result += _name[i];
	}
	return result % sz;
}
void add2hashtable(char *name, int id, int age)
{
	int idx;
	student *new1 = (student*)malloc(sizeof(student));
	new1->age = age;
	new1->student_id = id;
	new1->next = 0;
	strcpy(new1->name, name);
	idx = hashFunction(name);

	if (hashtable[idx] == 0)
	{
		hashtable[idx] = new1;
	}
	else
	{
		student *tmp = hashtable[idx];
		while (tmp->next != 0)	tmp = tmp->next;
		tmp->next = new1;
	}
}
void search_hash(char *name)
{
	int idx = hashFunction(name);
	student *cur = hashtable[idx];
	while (cur != 0)
	{
		if (strcmp(cur->name, name) == 0)
		{
			printf("%s %d %d\n", cur->name, cur->age, cur->student_id);
		}
		cur = cur->next;
	}
	printf("no hit\n");
}
int main()
{
	return 0;
}