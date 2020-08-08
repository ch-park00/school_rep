#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *next;
};
struct node *head = 0;
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

struct node * Findnode(int n) //n이 들어간 노드 찾는 함수
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
void insertSLL(int where, int what) //중간에 SLL삽입하는 함수
{
	struct node *cur = Findnode(where); //어디에 추가할건지 위치 파악
	if (cur == 0) //추가하려는 SLL의 위치가 존재하지 않는다 
	{
		return; //함수 종료. break은 사용 불가
	}
	struct node *neW = (struct node *)malloc(sizeof(struct node)); //새로 입력할 노드 생성
	neW->data = what; //새로 생성한 노드에 입력값 입력
	neW->next = 0; //

	neW->next = cur->next;
	cur->next = neW;
}
struct node * findByindex(int n) //n번째 SLL의 노드 주소를 반환해주는 함수
{
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
struct node * findnodePointingme(struct node *me) //삭제하는 노드의 전 노드 찾는 함수
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
void delFromSLL(int n) //SLL에서 특성 노드 삭제하는 함수
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

void destroySLL() //SLL삭제하는 함수
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
	if (head == 0)
	{
		printf("SLL 파괴완료\n");
	}
}
void displaySLL()
{
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
}