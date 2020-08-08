#include <stdio.h>
#include <stdlib.h>
struct node
{
	int i;
	struct node *next;
	struct node *prev;
};
struct node *head = 0;


struct node * createDLLNode(int _i)  //DLL노드 생성
{
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	new_node->i = _i;
	new_node->next=new_node->prev=0;  //이러면 prev에 0이 들어가고 그에 따라서 next도 0이 들어간다.
	//new_node->next = 0;
	//new_node->prev = 0;
	return new_node;
}
struct node * findlastNode() //DLL마지막 노드 주소 반환, DLL이 없는 상황에서는 0을 반환
{
	/*
	struct node *p = head;
	while (1)
	{
		if (head == 0)
		{
			return 0;
		}
		if (p->next == 0)
		{
			return p;
		}
		p = p->next;
	}
	*/
	if (head == 0)
	{
		return 0;
	}
	{
		struct node *cur = head; //이 변수는 이 블록 안에서만 살아 있다.
		//c언어에서는 문장 시작에서 변수를 선언하지 않는다면 오류. 블록 시작할 때 선언하는것은 괜찮다.
		//{} 이거없으면 컴파일 에러(문법 오류)
		while (1)
		{
			if (cur->next == 0)
			{
				return cur;
			}
			cur = cur->next;
		}
	}
}
void addToDLL(int i) //노드 생성후 DLL맨뒤에 이어붙임
{
	struct node * new_node = createDLLNode(i);
	struct node *lastnode = 0;
	if (head == 0) //예외상황
	{
		head = new_node;
		return;
	}
	lastnode = findlastNode();
	new_node->prev = lastnode;
	lastnode->next = new_node;

}
struct node * Findnode(int i) //i값이 있는 노드 찾기.없다면 0 반환
{
	if (head == 0)
	{
		return 0;
	}     //아래에서 걸러지므로 안써도 무방하다.
	{
		struct node *cur = head;
		while (1)
		{
			if (cur == 0) //i를 담고 있는 노드가 없는 경우
			{
				return 0;
			}
			if (cur->i == i)
			{
				return cur;
			}
			cur = cur->next;
		}
	}
}
void insertAfterDLL(int _where, int _what)
{
	struct node *cur = Findnode(_where);
	struct node *newnode = createDLLNode(_what);
	if (cur == 0)
	{
		return;
	}
	if (cur->next == 0) //맨 마지막 노드 뒤에 추가
	{
		newnode->prev = cur; 
		cur->next = newnode;
	}
	else
	{
		newnode->prev = cur;
		newnode->next = cur->next; //새로 삽입하는 노드 연결
		cur->next->prev = newnode; 
		cur->next = newnode; //기존 노드를 새로운 노드와 연결
	}
}
void insertBeforeDLL(int _where, int _what) //where앞에 노드 삽입.
{
	struct node *cur = Findnode(_where);
	struct node *newnode = createDLLNode(_what);
	if (cur == 0)
	{
		return;
	}
	if (cur == head)
	{
		newnode->next = cur;
		cur->prev = newnode;
		head = newnode;
	}
	else
	{
		newnode->next = cur;
		newnode->prev = cur->prev;
		cur->prev = newnode;
		newnode->prev->next = newnode;
	}
}
void deleteFromDLL(int _what)
{
	struct node *cur = Findnode(_what);
	if (cur == 0)
	{
		return;
	}
	if (cur == head)
	{
		// DLL이 head 하나만 있는 경우
		if (head->next == 0) //노드가 head 한개만 존재
		{
			head = 0;
			free(cur);
			return;
		}
		else //head 뒤에 여러 개의 노드가 있다.
		{
			head = head->next;
			head->prev = 0;
			free(cur);
			return;
		}
	}
	else if (cur->next == 0)//맨뒤에 노드를 삭제
	{
		cur->prev->next = 0;
		free(cur);
		return;
	}
	else //삭제하려는 노드 앞뒤로 존재하는 경우
	{
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		free(cur);
		return;
	}
}

void showDLL() //DLL출력.맨 앞에서부터 맨 뒤의 순서로 출력한다.
{
	struct node *cur = head;
	while (1)
	{
		if (cur == 0)
		{
			return;
		}
		printf("%d\n", cur->i);
		cur = cur->next;
	}
}
void showReverseDLL() //DLL을 거꾸로 출력하는 코드.
{
	struct node *cur = findlastNode();
	/*if (cur == 0) //예외경우 : DLL이 비어있는 경우
	{
		return;
	}*/ //while루프안에 이 조건이 있으므로 딱히 필요없다.
	while (1)
	{
		if (cur == 0)
		{
			return;
		}
		printf("%d\n", cur->i);
		cur = cur->prev;
	}
}
void destroyDLL()
{
	struct node *p = head;
	while (1)
	{
		if (head == 0)
		{
			printf("파기\n");
			break;
		}
		head = head->next;
		free(p);
		p = head;
	}
}
void main()
{
	addToDLL(3);
	addToDLL(4);
	addToDLL(5);
	
	showDLL();
	showReverseDLL();
	insertAfterDLL(3, 1);
	insertBeforeDLL(4, 2);
	showDLL();
	deleteFromDLL(3);
	showDLL();
	destroyDLL(); //SLL과 동일
}