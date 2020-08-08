#include <stdio.h>
#include <stdlib.h>
struct edge
{
	char src;
	char dst;
	int weight;
	struct edge *next;
};
struct vertex //vertex SLL에 추가되는 노드
{
	char v;
	char family; //family 정보도 vertex SLL에 추가=>이 SLL을 family table로 활용
	struct vertex *next;
};
struct edge *edges = 0; //edge가 연결될 때마다 여기에 추가되서 모든 엣지가 sll로 연결됨
struct vertex *vertexes = 0; //vertex 맨 앞을 가리키는 포인터
int checkVertex(char v) //v가 vertex에 있으면 1을 반환
{
	struct vertex *temp = vertexes;

	while (temp != 0)
	{
		if (temp->v == v)
		{
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}
int findfamily(char v) 
{
	struct vertex *temp = vertexes;

	while (temp != 0)
	{
		if (temp->v == v)
		{
			return temp->family; //가족정보를 반환
		}
		temp = temp->next;
	}
	return 0;
}
void addVertex(char v)
{
	//vertex SLL에 v가 없을시에만 SLL에 추가.

	//1.v가 vertex에 추가되었는지 확인
	if (checkVertex(v) == 1)
	{
		return;
	}
	//2. 없을시 새로운 노드생성후 맨끝에 추가
	else
	{
		struct vertex *new1 = (struct vertex *)malloc(sizeof(struct vertex));
		new1->v = v;
		new1->family = v; //초기에 가족은 자기 자신
		new1->next = 0;
		if (vertexes == 0)
		{
			vertexes = new1;
			return;
		}
		else
		{
			struct vertex *temp = vertexes;
			while (temp->next != 0)
			{
				temp = temp->next;
			}
			temp->next = new1;
		}
	}
}
int arewefam(char v1, char v2) //v1과 v2가 같은 가족이면 1.아니면 0반환
{
	//v1과 v2의 가족 정보 확인
	if (findfamily(v1) == findfamily(v2))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void changefam(char src, char dst)
{
	struct vertex *temp = vertexes;
	while (temp != 0)
	{
		if (temp->family == src)
		{
			temp->family = dst;
		}
		temp = temp->next;
	}
}
void justmarried(char v1, char v2) //v1과 v2를 같은 가족으로 합가
{
	struct vertex *temp = vertexes;
	struct vertex *temp1 = vertexes;
	while (temp->v != v1) 
	{
		temp = temp->next;
	}
	while (temp1->v!=v2)
	{
		temp1 = temp1->next;
	}
	changefam(temp1->family, temp->family);
}
//새로운 edge 추가
void addEdge(char _src, char _dst, int _weight)
{
	struct edge *new1 = (struct edge *)malloc(sizeof(struct edge));
	new1->src = _src;
	new1->dst = _dst;
	new1->weight = _weight;
	new1->next = 0;
	if (edges == 0)
	{
		edges = new1;
	}
	else
	{
		struct edge *temp = edges;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
//sll에 들어있는 엣지개수 확인
int countsll(struct edge *head)
{
	int cnt = 0;
	struct edge *temp = head;
	while (temp != 0)
	{
		cnt += 1;
		temp = temp->next;
	}
	return cnt;
}
int findvertex()
{
	int cnt = 0;
	struct vertex *temp = vertexes;
	while (temp != 0)
	{
		temp = temp->next;
		cnt++;
	}
	return cnt;
}
int main()
{
	addEdge('A', 'B', 8);
	addEdge('A', 'C', 5);
	addEdge('A', 'D', 3);
	addEdge('B', 'E', 13);
	addEdge('B', 'C', 7);
	addEdge('C', 'E', 20);
	addEdge('C', 'D', 4);
	addEdge('C', 'F', 80);
	addEdge('C', 'G', 17);
	addEdge('E', 'F', 15);
	addEdge('D', 'G', 2);
	//edge 정렬
	//bubble sort 이용(array이용)
	int n = countsll(edges); //edge의 개수 count
	//복사할 배열 생성
	struct edge *edgeArray = (struct edge *)malloc(sizeof(struct edge)*n);
	//sll배열로 복사
	struct edge *temp = edges;
	for (int i = 0; i < n; i++)
	{
		edgeArray[i].src = temp->src;
		edgeArray[i].dst = temp->dst;
		edgeArray[i].weight = temp->weight;
		temp = temp->next;
	}
	//복사한 배열에 대해 bubble sort 정렬
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n - i; j++)
		{
			if (edgeArray[j].weight > edgeArray[j + 1].weight)
			{
				struct edge temp = edgeArray[j];
				edgeArray[j] = edgeArray[j + 1];
				edgeArray[j + 1] = temp;
			}
		}
	}
	// family table 을 구하기 위해 vertex 개수를 구해야한다.
	//vertex가 몇 개이고 이름이 뭔지 알기 위해 배열을 뒤지면서 하나씩 찾아낸다.
	for (int i = 0; i < n; i++)
	{
		//vertex를 새로운 SLL에 추가.단, 중복은 제거
		addVertex(edgeArray[i].src);
		addVertex(edgeArray[i].dst);
	}
	int mstCnt = 0;
	for (int i = 0; i < n; i++) //edge들을 오름차순으로 하나씩 검사하면서 MST에 추가할수있는지 확인
	{
		if (arewefam(edgeArray[i].src, edgeArray[i].dst) == 0)
		{
			printf("add edge %c - %c to MST\n", edgeArray[i].src, edgeArray[i].dst);
			mstCnt += 1;
			if (mstCnt == findvertex() - 1)
			{
				break;
			}
			justmarried(edgeArray[i].src, edgeArray[i].dst); //완벽하게 구현해보기
		}
		else
		{
			continue;
		}
	}
	return 0;
}