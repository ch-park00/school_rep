#include <stdio.h>
#include <stdlib.h>
struct vertex
{
	int ver;
	struct vertex* next;
};
struct vertex** head = 0;
int* visited = 0;
int* queue = 0;
//큐 삽입 위치
int front = 0;
//큐 인출 위치
int rear = 0;
// 헛간의 개수
int cnt = 0;
//거리 저장 변수
int dist = -1;
int cur_num = 0;
int* prev_visit = 0;
void add2edge(int src, int dst)
{
	int num = src - 1;
	struct vertex* new1 = (struct vertex*)malloc(sizeof(struct vertex));
	new1->ver = dst;
	new1->next = 0;

	struct vertex* tmp = head[num];
	while (tmp->next != 0)
	{
		tmp = tmp->next;
	}
	tmp->next = new1;
}
void add2queue(int vertex)
{
	queue[front] = vertex;
	front = (front + 1) % (cnt + 1);
}
int isin_queue(int ver)
{
	int idx = rear;
	while (idx != front)
	{
		if (queue[idx] == ver)
		{
			return 1;
		}
		idx = (idx + 1);
		if (idx >= cnt+1)
		{
			idx = 0;
		}
	}
	return 0;
}
int dequeue()
{
	int ret = queue[rear];
	rear = (rear + 1) % (cnt + 1);
	return ret;
}
int least_num(int* arr, int num)
{
	int ret = 99999;
	for (int i = 0; i < num; i++)
	{
		if (ret > arr[i])
		{
			ret = arr[i];
		}
	}
	return ret;
}
int get_min()
{
	int flag = 0;
	int prev_num = 1;
	prev_visit = (int*)malloc(cnt * sizeof(int));

	add2queue(1);
	while (1)
	{
		cur_num = prev_num;
		prev_num = 0;
		for (int i = 0; i < cur_num; i++)
		{
			int ver = dequeue();
			if (!visited[ver - 1])
			{
				visited[ver - 1] = 1;
				struct vertex* cur = head[ver - 1]->next;
				while (cur != 0)
				{
					if (visited[cur->ver - 1] == 0 && (isin_queue(cur->ver) == 0))
					{
						prev_visit[prev_num] = cur->ver;
						add2queue(cur->ver);
						prev_num++;
					}
					cur = cur->next;
				}
			}
			else
			{
				continue;
			}
		}
		dist++;
		if (prev_num == 0)
		{
			break;
		}
	}
	return least_num(prev_visit, cur_num);
}
int main()
{
	int min_num;
	int cnt1;
	scanf("%d", &cnt);
	head = (struct vertex**)malloc(sizeof(struct vertex*) * cnt);
	visited = (int*)malloc(sizeof(int) * cnt);
	queue = (int*)malloc(sizeof(int) * (cnt + 1));
	for (int i = 0; i < cnt; i++)
	{
		head[i] = (struct vertex*)malloc(sizeof(struct vertex));
		head[i]->ver = i + 1;
		head[i]->next = 0;
		visited[i] = 0;
		queue[i] = 0;
	}
	queue[cnt] = 0;
	scanf("%d", &cnt1);
	for (int i = 0; i < cnt1; i++)
	{
		int src, dst;
		scanf("%d %d", &src, &dst);
		add2edge(src, dst);
		add2edge(dst, src);

	}
	//vertex번호 구하기
	min_num = get_min();
	printf("%d %d %d\n", min_num, dist, cur_num);
	return 0;
}