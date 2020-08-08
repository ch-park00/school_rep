#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>
#define NUM_VERTEX 7
#define SZ 6

#if 0
char family[SZ];
struct edge {
	char src;
	char dst;
	int weight;
};      //edge의 값을 넣어주기 위해 어디와 어디가 연결되어 있고 weight는 얼마인지
int graph[SZ][SZ]; //all zeros  전역변수는 초기화 안해줘도 0임
int edge_cnt = 0;
void addEdge(char src, char dst, int weight)
{
	graph[src - 'A'][dst - 'A'] = weight;
	graph[dst - 'A'][src - 'A'] = weight;
	family[src - 'A'] = src;
	edge_cnt += 1; //총 엣지가 몇개인지 count
}

struct edge* BuildEdgeArray(void)
{
	struct edge *edgeArray = (struct edge*)malloc(sizeof(struct edge)*edge_cnt);
	return edgeArray;

}


int areWeFamily(char v1, char v2)
{
	int idx_1 = v1 - 'A';
	int idx_2 = v2 - 'A';
	if (family[idx_1] == family[idx_2])
	{
		return 1;
	}
	return 0;
}

void justMarried(char v1, char v2)
{

	char familyMark_v1 = family[v1 - 'A'];
	char familyMark_v2 = family[v2 - 'A'];//현재 family마크를 알아야함 

	char newFamilyMark;
	char toBeChanged;
	if (familyMark_v1 < familyMark_v2)
	{
		newFamilyMark = familyMark_v1;
		toBeChanged = familyMark_v2;
	}
	else
	{
		newFamilyMark = familyMark_v2;
		toBeChanged = familyMark_v1;
	}
	//family에서 tobevchanged 다 찾아서 바꿈 
	for (int i = 0; i < SZ; i++)
	{
		if (family[i] == toBeChanged)
		{
			family[i] = newFamilyMark;
		}
	}
}



int main(void)
{
	addEdge('A', 'C', 1);
	addEdge('A', 'B', 23);
	addEdge('B', 'C', 10);
	addEdge('B', 'D', 173);
	addEdge('B', 'E', 10);
	addEdge('C', 'D', 10);
	addEdge('C', 'F', 5);
	addEdge('D', 'E', 9);
	addEdge('D', 'F', 12);
	addEdge('E', 'F', 9);
	struct edge *edgeArray = BuildEdgeArray();
	int idx = 0; //edgeArray에 넣기 위한 index
	for (int i = 0; i < SZ; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			if (graph[i][j] > 0 && i < j) //중복되는 edge를 피하기 위해서
			{
				edgeArray[idx].src = 'A' + i;
				edgeArray[idx].dst = 'A' + j;
				edgeArray[idx].weight = graph[i][j];
				idx += 1;

			}
		}
	}
	//edgeArray를 weight의 오름차순으로 정렬
	for (int i = 0; i < edge_cnt; i++)
	{
		for (int j = 0; j < edge_cnt - 1 - i; j++)
		{
			if (edgeArray[j].weight > edgeArray[j + 1].weight)
			{
				struct edge temp = edgeArray[j]; //배열의 형태는 가르키고 있는거와 같은거임
				edgeArray[j] = edgeArray[j + 1];
				edgeArray[j + 1] = temp;
			}
		}
	}
	//edgeArray를 출력
	for (int i = 0; i < edge_cnt; i++)
	{
		printf("%c %c %d\n", edgeArray[i].src, edgeArray[i].dst, edgeArray[i].weight);
	}

	//MST를 찾아내서 출력하는 부분
	// --->MST에 들어가는 edge들만 모두 출력

	int mst_edge_cnt = 0;

	for (int i = 0; i < edge_cnt; i++) // 모든 edge를 하나씩 차례로
	{
		struct edge E = edgeArray[i];
		if (areWeFamily(E.src, E.dst) == 0) //다른 가족
		{
			mst_edge_cnt += 1;
			printf("MST Edge %c --- %c : %d\n", E.src, E.dst, E.weight);
			justMarried(E.src, E.dst);

			if (mst_edge_cnt == SZ - 1)
			{
				break;
			}
		}

	}
	return 0;
}
#endif
#if 1
struct edge
{
	char data;
	int w;
	struct edge *next;
};
struct node
{
	char v;
	struct edge *con;
};
// MST 사용 시 엣지만 저장하기 위한 구조체
struct tmp
{
	char src;
	char dst;
	int w;
	struct tmp *next;
};
//그래프를 여기에 저장
struct node * graph[NUM_VERTEX];
//MST 구현 시 방문 노드를 체크하기 위해 사용
int visited[NUM_VERTEX] = { 0 };
//MST_Prim시 key값을 확인하는 용도로 사용
int key[NUM_VERTEX] = { 0 };
char key_src[NUM_VERTEX] = { 0 };
struct tmp *head = 0;

char *family;
void Connect_Edge(int src, int dst, int weight)
{
	struct edge *new1 = (struct edge*)malloc(sizeof(struct edge));
	new1->data = dst + 'A';
	new1->next = 0;
	new1->w = weight;
	if (graph[src]->con == 0)
	{
		graph[src]->con = new1;
		return;
	}
	else
	{
		struct edge* cur = graph[src]->con;
		while (cur->next != 0)
		{
			cur = cur->next;
		}
		cur->next = new1;
	}
}
void add2head(const char src, const char dst, int weight)
{
	struct tmp *new1 = (struct tmp*)malloc(sizeof(struct tmp));
	new1->src = src;
	new1->dst = dst;
	new1->w = weight;
	new1->next = 0;
	if (head == 0)
	{
		head = new1;
		return;
	}
	else
	{
		struct tmp *cur = head;
		while (cur->next != 0)	cur = cur->next;
		cur->next = new1;
	}
}
void addEdge(const char src, const char dst, int weight)
{
	int src_index = src - 'A';
	int dst_index = dst - 'A';
	Connect_Edge(src_index, dst_index,weight);
	Connect_Edge(dst_index, src_index,weight);
	add2head(src, dst, weight);
}
//사용되는 변수들을 초기화
void init(int num, ...)
{
	family = (char*)malloc(sizeof(char)*num);
	va_list ap;
	va_start(ap, num);
	for (int i = 0; i < num; i++)
	{
		graph[i] = (struct node*)malloc(sizeof(struct node));
		graph[i]->v = va_arg(ap, char);
		graph[i]->con = 0;
		family[i] = graph[i]->v;
		key[i] = 999999;
		key_src[i] = 'A' + i;
	}
	va_end(ap);
	
}
// 입력받은 vertex와 연결되어 있는 vertex를 출력
void showConnectedVertex(const char d)
{
	int idx = d - 'A';
	struct edge *tmp = graph[idx]->con;
	while (tmp != 0)
	{
		printf("%c\n", tmp->data);
		tmp = tmp->next;
	}
}
void deleteEdge(struct tmp *del)
{
	if (del == head)
	{
		head = head->next;
		free(del);
		return;
	}
	struct tmp *cur = head;
	while (1)
	{
		if (cur->next == del)
		{
			break;
		}
		cur = cur->next;
	}
	cur->next = del->next;
	free(del);
	return;
}
//weight가 가장 작은 edge를 찾아서 돌려줌
struct tmp* findsmallestEdge()
{
	int tmp = 999999;
	struct tmp *cur = head;
	struct tmp *ret = head;
	while (cur != 0)
	{
		if (tmp > cur->w)
		{
			tmp = cur->w;
			ret = cur;
		}
		cur = cur->next;
	}
	return ret;
}

void doMST_K()
{
	int cnt = 0;
	while (1)
	{
		if (cnt >= NUM_VERTEX - 1)	break;
		struct tmp *least = findsmallestEdge();
		if (family[least->src - 'A'] == family[least->dst - 'A'])
		{
			deleteEdge(least);
			continue;
		}
		else
		{
			char src = least->src;
			char dst = least->dst;
			printf("%c <-> %c:%d\n", src, dst,least->w);
			for (int i = 0; i < NUM_VERTEX; i++)
			{
				if (family[i] == family[dst-'A'])
				{
					family[i] = src;
				}
			}
			cnt++;
			deleteEdge(least);
		}
	}
}
int findsmallestkey()
{
	int min = 9999999;
	int ret = -1;
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		if (min > key[i] && visited[i] == 0)
		{
			min = key[i];
			ret = i;
		}
	}
	return ret;
}
// 방문한 vertex 중 수정이 필요한 key값 확인하고 수정.
void fix_key()
{
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		if (visited[i] == 1)
		{
			struct edge *cur = graph[i]->con;
			while (cur != 0)
			{
				char cur_ver = cur->data;
				if (key[cur_ver - 'A'] > cur->w)
				{
					// key값 수정
					key[cur_ver - 'A'] = cur->w;
					// 이때, 해당 edge에 연결되어 있는 vertex 기록.
					key_src[cur_ver - 'A'] = i + 'A';
				}
				cur = cur->next;
			}
		}
	}
}
// Prim 알고리즘을 적용한 MST
void doMST_P(const char start)
{
	int cnt = 0;
	//시작 vertex에 key값=0 부여
	key[start - 'A'] = 0;
	while (1)
	{
		// 모든 vertex 연결 완료
		if (cnt >= NUM_VERTEX)	break;
		// 가장 작은 key값을 가진 vertex를 찾음.
		int cur = findsmallestkey();
		// 예외상황 처리
		if (cur == -1 || cur >= NUM_VERTEX)
		{
			printf("Error\n");
			return;
		}
		// 해당 vertex 방문처리
		visited[cur] = 1;
		if (cnt > 0)
		{
			printf("%c <-> %c:%d\n", key_src[cur], cur + 'A', key[cur]);
		}
		// 방문한 vertex로부터 key값의 수정과정을 적용
		fix_key();
		cnt++;
	}
}
int main(void)
{
	init(NUM_VERTEX, 'A', 'B', 'C', 'D','E','F','G');
	//A-B 방향성 없이 연결(양방향에서 모두 연결)
	addEdge('A', 'B', 8);
	addEdge('A', 'C', 5);
	addEdge('A', 'D', 3);
	addEdge('B', 'C', 7);
	addEdge('B', 'E', 13);
	addEdge('C', 'D', 4);
	addEdge('C', 'E', 20);
	addEdge('C', 'G', 17);
	addEdge('C', 'F', 80);
	addEdge('D', 'G', 2);
	addEdge('E', 'F', 15);

	doMST_K();
	printf("------------------\n");
	doMST_P('E');
}

#endif