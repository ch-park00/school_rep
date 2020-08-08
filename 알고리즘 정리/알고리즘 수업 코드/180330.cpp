#include <stdio.h>
#include <stdlib.h>

struct node // 
{
	int data;
	struct node *next; //자기참조구조체, 다음 노드의 주소 입력받음
};
struct node *head = 0;


#if 0
void main()
{
	int *a = (int *)malloc(4);
	*a = 10; //a가 가르키고 있는 공간에 10 대입
	printf("%d\n", *a);
	free(a);
}

void main()
{
	int *a = (int *)malloc(sizeof(int) * 5);
	for (int k = 0; k <= 4; k++)
	{
		a[k] = k;
		printf("%d\n", a[k]);
	}
	free(a);
}

typedef struct
{
	int a;
	char b;
}A;
void main()
{
	A *aa = (A *)malloc(sizeof(A));
	aa->a = 10; aa->b = 'a';
	printf("%d\n%c\n", aa->a, aa->b);
	free(aa);
}

typedef struct
{
	int a;
	char b;
}A;
void main()
{
	A *aa = (A *)malloc(sizeof(A) * 10);
	for (int i = 0; i <= 9; i++)
	{
		aa[i].a = 10; //(aa+i)->a=10; (*(aa+i)).a=10; 셋 다 같은 명령
		aa[i].b = 'a';
		printf("%d %c\n", aa[i].a, aa[i].b);
	}
	free(aa);
} //malloc과 free


void main()
{
	struct node *p, *q, *t, *head;
	int i;
	p = (struct node *)malloc(sizeof(struct node));
	p->data = 1;
	p->next = 0;
	head = p;
	//p->next=(struct node *)malloc(sizeof(struct node)); 이거는 밑에 문장과 같은 문장
	q = (struct node *)malloc(sizeof(struct node)); //여기서 p를 쓰면 앞에 공간이 unreferenced space가 된다
	q->data = 2;
	q->next = 0;
	p->next = q; // 링크 연결

	t = head;
	for (i = 0; i < 2; i++)
	{
		printf("%d\n", t->data);
		t = t->next; //t에 q 대입.
	}
}
#endif

void addToSLL(int _data) // _붙인건 로컬변수라는 뜻
{
	struct node *p = (struct node *)malloc(sizeof(node));
	p->data = _data;
	p->next = 0;

	if (head == 0)
	{
		head = p;
	}
	else
	{
		struct node *temp = head; //임시 변수
		while (1)
		{
			if (temp->next == 0) // 맨 마지막 노드일 때
			{
				break; // while루프 탈출
			}
			temp = temp->next; // 맨 마지막 노드가 아닐 경우는 다음 노드로 이동
		}
		temp->next = p;
	}
}

struct node * Findnode(int n)
{
	struct node *cur = head;
	while (1)
	{
		if (cur == 0)
		{
			break; //밑에서 return 0말고 여기서 해도 가능.
		}
		if (cur->data == n)
		{
			return cur;
		}
		else
		{
			cur = cur->next;
		}
	}
	return 0;
}
void insertSLL(int where, int what)
{
	struct node *cur = Findnode(where); //어디에 추가할건지 위치 파악
	if (cur == 0)
	{
		return; //함수 종료. break은 사용 불가
	}
	struct node *neW = (struct node *)malloc(sizeof(struct node)); //새로 입력할 노드 생성
	neW->data = what; //새로 생성한 노드에 입력값 입력
	neW->next = 0; //

	neW->next = cur->next;
	cur->next = neW;
}
struct node * findByindex(int n)
{
	/*
	struct node *p = head;
	int a = 0;
	while (1)
	{
	if (a == n)
	{
	return p;
	}
	if (p->next == 0)
	{
	return 0;
	}
	else
	{
	p = p->next;
	a++;
	}
	}*/
	struct node *cur = head;
	int cnt = n;
	while (1)
	{
		if (cur == 0 || cnt == 0)
		{
			return cur;
		}
		cur = cur->next;
		cnt--;
	}
}

struct node * findnodePointingme(struct node *me)
{
	struct node *cur = head;
	while (1)
	{
		if (cur->next == me) //다음 노드가 내가 지울 노드일 때.
		{
			return cur; //지우는 전 주소 반환
		}
		cur = cur->next;
	}
}
void delFromSLL(int n)
{
	struct node *del = Findnode(n);
	if (del == 0) //지우려는 애가 존재하지 않음.
	{
		return;
	}
	if (del == head)
	{
		head = head->next; //헤드만 이동.노드가 하나일시 다음 노드값은 0이므로 문제없다.head에 0이 들어가기 때문.
		free(del);
		return;
	}
	else
	{
		struct node *del_before = findnodePointingme(del);
		del_before->next = del->next;
		free(del);
	}
}

void destroySLL()
{
	struct node *cur = head;
	while (1)
	{
		if (head == 0)
		{
			break;
		}
		head = head->next; //헤드 이동
		free(cur); //맨 처음 공간해제
		cur = head; //cur에 head 입력.
	}

}
void displaySLL()
{
	/*
	struct node *temp = head;
	do
	{
	printf("%d\n", temp->data);
	temp = temp->next;
	} while (temp->next != 0);
	printf("%d\n", temp->data);
	*/
	struct node *cur = head;
	while (1)
	{
		if (cur == 0)
		{
			break;
		}
		printf("%d\n", cur->data);
		cur = cur->next;
	}
}
void main()
{
	addToSLL(5); //노드 맨앞에 5 입력
	addToSLL(4); //그다음 노드 4 입력
	addToSLL(3); //3 입력
	addToSLL(2); //2 입력
	addToSLL(1); //1 입력

	displaySLL(); // 노드에 입력한 값 모두 출력

	insertSLL(3, 10); //3데이터를 찾아서 그뒤에 10데이터를 이어붙임
	displaySLL();
	struct node *q = findByindex(2);
	if (q == 0) //(q>0)도 가능
	{
		printf("없음\n");
	}
	else
	{
		printf("%d\n", q->data);
	}
	delFromSLL(1);
	displaySLL();
	destroySLL();
	if (head == 0)
	{
		printf("SLL 파괴완료\n");
	}
}
