#include <iostream>
#define num 20
struct node
{
	int data;
	int idx;
	struct node *next;
};
struct node *head = 0;
struct node *merge_result=0;
struct node *quick_result = 0;
int max_merge = 0;
int max_quick = 0;

//그때그때 바꿔가며 사용
int data[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

void mergesort(int start, int end, int cur_level)
{
	//i=첫번째 블록의 현재 합쳐야 할 인덱스
	//j=두번째 블록의 현재 합쳐야 할 인덱스
	//g= 합친 블록의 현재 위치(다음 데이터 쓸 인덱스)
	int m = ((start + end) / 2);
	int i = start;
	int j = m + 1;
	int g = 0;
	//합병 범위 체크
	if (start < end)
	{
		//그룹 쪼개는 과정.
		mergesort(start, m, cur_level+1);
		mergesort(m + 1, end, cur_level+1);
		//다 쪼갠 이후 다시 합치는 과정
		struct node **my_arr = (struct node**)malloc(sizeof(struct node**)*(end - start + 1));
		struct node *i_com = head;
		struct node *j_com = head;
		struct node *s = head;
		struct node *e = head;
		struct node *tmp = head;
		for (int k = 0; k < end + 1; k++)	e = e->next;
		for (int k = 0; k < start - 1; k++)	s = s->next;
		for (int k = 0; k < start; k++)	i_com = i_com->next;
		for (int k = 0; k < j; k++)	j_com = j_com->next;
		while (i <= m && j <= end)
		{
			if (i_com->data <= j_com->data)
			{
				my_arr[g] = i_com;
				i++;
				i_com = i_com->next;
			}
			else
			{
				my_arr[g] = j_com;
				j++;
				j_com = j_com->next;
			}
			g++;
		}
		//한 쪽 블록의 숫자가 소진된 경우
		//다른 한 쪽을 모두 복사하는 것
		//오른쪽 블록을 모두 사용
		if (i <= m && j > end)
		{
			for (int k = i; k <= m; k++)
			{
				my_arr[g] = i_com;
				g++;
				i++;
				i_com = i_com->next;
			}
		}
		//왼쪽 모두 사용
		else
		{
			for (int k = j; k <= end; k++)
			{
				my_arr[g] = j_com;
				g++;
				j++;
				j_com = j_com->next;
			}
		}
		//두개의 블록 모두 합치기 완료
		//나머지 부분과 연결
		if (start == 0)
		{
			head = my_arr[0];
			tmp = head;
			for (int k = 1; k < g; k++)
			{
				tmp->next = my_arr[k];
				tmp = tmp->next;
			}
			tmp->next = e;
		}
		else
		{
			s->next = my_arr[0];
			tmp = s->next;
			for (int k = 1; k < g; k++)
			{
				tmp->next = my_arr[k];
				tmp = tmp->next;
			}
			tmp->next = e;
		}
		if (max_merge < cur_level)	max_merge = cur_level;
		free(my_arr);
	}
}

int check_ok(struct node *L, struct node *R)
{
	struct node *tmp = head;
	while (tmp != 0)
	{
		if (tmp == R)	return 1;
		if (tmp == L)	return 0;
		tmp = tmp->next;
	}
}
void q_sort(int pivot, int left, int right, int cur_level)
{
	if (left > right)	return;
	int R_idx = 0;
	struct node *P, *L, *R, *left_node, *right_node;
	P = L = R = head;
	for (int i = 0; i < pivot; i++)	P = P->next;
	for (int i = 0; i < right; i++)
	{
		if (i < left)
		{
			L = L->next;
		}
		R = R->next;
	}
	left_node = L;
	right_node = R;
	while (1)
	{
		while (L->data <= P->data)
		{
			if (L == right_node)
			{
				//L = L->next;
				break;
			}
			L = L->next;
		}
		while (R->data > P->data)
		{
			struct node *tmp = head;
			if (R == left_node)
			{
				while (tmp->next != R)	tmp = tmp->next;
				R = tmp;
				break;
			}
			while (tmp->next != R)	tmp = tmp->next;
			R = tmp;
		}
		if (check_ok(L,R))
		{
			//pivot 기준으로 정렬 완료
			//R 과 pivot 위치 바꾸기
			struct node *pivot_prev = head;
			struct node *R_prev = head;
			if (P != head)
			{
				while (R_prev->next != R)
				{
					R_prev = R_prev->next;
					R_idx++;
				}
				R_idx++;
			}
			if (P != R) 
			{	
				if (head == P)
				{
					head = head->next;
					R_prev->next = R->next;
					P->next = R_prev->next;
					if (R_prev != P) 
					{
						R_prev->next = P;
						R->next = head;
						head = R;
					}
					else 
					{
						R->next = P;
					}
				}
				else
				{
					while (pivot_prev->next != P)	pivot_prev = pivot_prev->next;
					if (P->next == R)
					{
						pivot_prev->next = R->next;
						R->next = P;
						P->next = pivot_prev->next;
						pivot_prev->next = R;
					}
					else
					{
						pivot_prev->next = P->next;
						R_prev->next = R->next;
						R->next = pivot_prev->next;
						pivot_prev->next = R;
						P->next = R_prev->next;
						R_prev->next = P;
					}
				}
			}
			break;
		}
		else
		{
			//L과 R의 위치 바꾸기
			struct node *L_prev = head;
			struct node *R_prev = head;
			while (R_prev->next != R)	R_prev = R_prev->next;
			while (L_prev->next != L)	L_prev = L_prev->next;
			if (L->next != R)
			{
				L_prev->next = L->next;
				R_prev->next = R->next;
				L->next = R_prev->next;
				R_prev->next = L;
				R->next = L_prev->next;
				L_prev->next = R;
			}
			else
			{
				L_prev->next = R->next;
				R->next = L;
				L->next = L_prev->next;
				L_prev->next = R;
			}
			struct node *temp = L;
			if (L == left_node)
			{
				left_node = R;
			}
			L = R;
			if (R == right_node)
			{
				right_node = temp;
			}
			R = temp;
		}
	}
	q_sort(pivot, left, R_idx - 1, cur_level + 1);
	q_sort(R_idx + 1, R_idx + 2, right, cur_level + 1);
	if (cur_level > max_quick)	max_quick = cur_level;
	return;
}
void init_data()
{
	struct node *prev = 0;
	for (int i = 0; i < num; i++)
	{
		struct node *new1 = (struct node*)malloc(sizeof(struct node));
		new1->data = data[i];
		new1->next = 0;
		new1->idx = 0;
		if (prev == 0)
		{
			prev = new1;
			head = prev;
		}
		else
		{
			prev->next = new1;
			prev = new1;
		}
	}
}
int main()
{
	init_data();
	struct node *cur = head;
	std::cout << "before sort" << std::endl;
	for (int i = 0; i < num; i++)
	{
		std::cout << cur->data << ", " << cur << std::endl;
		cur = cur->next;
	}
	std::cout << "----------------" << std::endl;
	#if 0
	mergesort(0, num - 1, 0);
	cur = head;
	std::cout << "after sort " << std::endl;
	while (cur!=0)
	{
		std::cout << cur->data << "," << cur << std::endl;
		cur = cur->next;
	}
	std::cout << "max merge : " << max_merge << std::endl;
	std::cout << "----------------" << std::endl;
	#endif
	#if 1
	q_sort(0, 1, num - 1, 0);
	cur = head;
	std::cout << "after sort" << std::endl;
	for (int i = 0; i < num; i++)
	{
		std::cout << cur->data << ", " << cur << std::endl;
		cur = cur->next;
	}
	std::cout << "max quick : " << max_quick << std::endl;
	#endif
	return 0;
}