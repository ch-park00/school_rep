#include <stdio.h>
#include <stdlib.h>

#define SZ 6

struct edge
{
	char src;
	char dst;
	int weight;
};

char family[SZ] = { 'A', 'B', 'C', 'D', 'E', 'F' };

int graph[SZ][SZ]; // all zeros
int edge_cnt = 0;

int areWeFamily(char v1, char v2)
{
	if (family[v1 - 'A'] == family[v2 - 'A'])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void justMarried(char v1, char v2)  // 'A', 'D'
{
	char familyMark_v1 = family[v1 - 'A'];
	char familyMark_v2 = family[v2 - 'A'];

	char newFamilyMark;   // 새로운 family mark
	char toBeChanged;     // 바꿀 애들

	if (familyMark_v1 < familyMark_v2)  // 알파벳 순서로 먼저 나오는 것이 newFamilyMark
	{
		newFamilyMark = familyMark_v1;
		toBeChanged = familyMark_v2;
	}
	else
	{
		newFamilyMark = familyMark_v2;
		toBeChanged = familyMark_v1;
	}
	// family에서, toBeChanged를 다 찾아서, newFamilyMark로 수정
	for (int i = 0; i < SZ; i++)
	{
		if (family[i] == toBeChanged)
		{
			family[i] = newFamilyMark;
		}
	}

}

void addEdge(char src, char dst, int weight)
{
	edge_cnt += 1; // edge가 총 몇 개인지 count
	graph[src - 'A'][dst - 'A'] = weight;
	graph[dst - 'A'][src - 'A'] = weight;
}

struct edge *buildEdgeArray(void)
{
	struct edge * edgeArray = (struct edge *)malloc(sizeof(struct edge)*edge_cnt);
	return edgeArray;
}

int main(void)
{
	addEdge('A', 'C', 1);
	addEdge('A', 'B', 23);
	addEdge('B', 'C', 10);
	addEdge('B', 'D', 173);
	addEdge('B', 'E', 5);
	addEdge('C', 'D', 10);
	addEdge('C', 'F', 5);
	addEdge('D', 'E', 9);
	addEdge('D', 'F', 12);
	addEdge('E', 'F', 9);

	struct edge * edgeArray = buildEdgeArray();
	
	int idx = 0; // edgeArray에 넣기 위한 index

	// graph 정보를 이용해서
	// edge 정보를 edgeArray에 모두 입력
	// 주의!! A-B edge인 경우, 하나만 입력
	for (int i = 0; i < SZ; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			if (graph[i][j] > 0 && i < j)  // A-B만 edgeArray에 넣고, B-A는 넣지 않는다.
			{
				edgeArray[idx].src = 'A' + i;
				edgeArray[idx].dst = 'A' + j;
				edgeArray[idx].weight = graph[i][j];
				idx += 1;
			}
		}
	}

	// edgeArray를 weight의 오름차순으로 정렬 -- by bubble sort
	for (int i = 0; i < edge_cnt; i++)
	{
		for (int j = 0; j < edge_cnt - 1 - i; j++)
		{
			if (edgeArray[j].weight > edgeArray[j + 1].weight)
			{
				struct edge temp = edgeArray[j];
				edgeArray[j] = edgeArray[j + 1];
				edgeArray[j + 1] = temp;
			}
		}
	}
	
	// edgeArray를 출력
	for (int i = 0; i < edge_cnt; i++)
	{
		printf("%c %c %d\n", edgeArray[i].src, edgeArray[i].dst, edgeArray[i].weight);
	}

	// MST를 찾아내서 출력하는 부분.
	// ---> MST에 들어가는 edge들만 모두 출력

	int mst_edge_cnt = 0;

	for (int i = 0; i < edge_cnt; i++)  // 모든 edge를 하나씩 차례로,,,
	{
		struct edge E = edgeArray[i];
		if (areWeFamily(E.src, E.dst) == 0)
		{
			mst_edge_cnt += 1;
			printf("MST Edge %c -- %c : %d\n", E.src, E.dst, E.weight);
			justMarried(E.src, E.dst);

			if (mst_edge_cnt == SZ - 1)
			{
				break;
			}
		}
		else
		{
			continue;
		}

	}





	return 0;
}