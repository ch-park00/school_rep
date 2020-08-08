#include<stdio.h>
#include<stdlib.h>
#define SZ 6
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
	struct edge *edgeArray =  (struct edge*)malloc(sizeof(struct edge)*edge_cnt);
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
		if ( family[i] == toBeChanged )
		{
			family[i] = newFamilyMark;
		}
	}
}



int main(void)
{
	addEdge('A','C',1);
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
			printf("MST Edge %c --- %c : %d\n", E.src, E.dst,E.weight);
			justMarried(E.src, E.dst);

			if (mst_edge_cnt == SZ - 1)
			{
				break;
			}
		}
		
	}
	return 0;
} 