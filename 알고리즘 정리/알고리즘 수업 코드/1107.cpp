#include <stdio.h>

#define Sz 100 //99개까지 저장 가능
int mheap[Sz];
int heapend = 0; //현재 heap을 어디까지 사용하고 있는지 표시


void add2heap(int i)
{
	if (heapend == Sz - 1)
	{
		printf("Error : Heap full\n");
		return;
	}
	heapend++;
	mheap[heapend] = i;
	int idx = heapend;
	int parent = idx / 2;
	while (1)
	{
		if (parent < 1) //더이상 비교할 것이없다
		{
			break;
		}
		if (mheap[idx] >= mheap[parent]) //minheap의 조건을 만족
		{
			break;
		}
		else
		{
			//부모가 나보다 큰 경우. 부모와 나의 값을 바꿔야함.
			int temp = mheap[idx];
			mheap[idx] = mheap[parent];
			mheap[parent] = temp;
			idx = parent;
			parent = idx / 2;
		}
	}
}
int delfrominheap()
{
	if (heapend == 0)
	{
		printf("Error : heap empty");
		return -999;
	}
	else
	{
		//heap의 형태 유지한채 데이터 꺼내기
		int result = mheap[1];
		mheap[1] = mheap[heapend];
		heapend--;
		int cur = 1;
		while (1)
		{
			int idx = cur * 2;
			if (idx > heapend)
			{
				return result;
			}
			if (mheap[idx] > mheap[idx + 1])
			{
				idx = idx + 1;
			}
			if (mheap[cur] > mheap[idx])
			{
				int temp = mheap[cur];
				mheap[cur] = mheap[idx];
				mheap[idx] = temp;
			}
			cur = idx;
		}
	}
}
int main()
{
	add2heap(10);
	add2heap(9);
	add2heap(8);
	add2heap(7);
	add2heap(55);
	add2heap(3);
	add2heap(2);
	add2heap(1);
	printf("add\n");
	for (int i = 1; i <= 8; i++)
	{
		printf("%d\n", mheap[i]);
	}
	printf("delete\n");
	for (int i = 0; i < 8; i++)
	{
		printf("%d\n", delfrominheap());
	}
	return 0;
}