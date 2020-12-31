int* merge_sort(int *origin_arr, int *result_arr, int start, int end)
{
	//i=첫번째 블록의 현재 합쳐야 할 인덱스
	//j=두번째 블록의 현재 합쳐야 할 인덱스
	//g= 합친 블록의 현재 위치(다음 데이터 쓸 인덱스)

	int m = ((start + end) / 2);
	int i = start;
	int j = m + 1;
	int g = start;
	//합병 범위 체크
	if (start < end)
	{
		//그룹 쪼개는 과정.
		//
		merge_sort(origin_arr, result_arr, start, m);
		merge_sort(origin_arr, result_arr, m + 1, end);

		//다 쪼갠 이후 다시 합치는 과정

		while (i <= m && j <= end)
		{
			if (origin_arr[i] < origin_arr[j])
			{
				result_arr[g] = origin_arr[i];
				i++;
			}
			else
			{
				result_arr[g] = origin_arr[j];
				j++;
			}
			g++;
		}
		//한 쪽 블록의 숫자가 소진된 경우
		//다른 한 쪽을 모두 복자하는 것

		//오른쪽 블록을 모두 사용
		if (i <= m && j > end)
		{
			for (int k = i; k <= m; k++)
			{
				result_arr[g] = origin_arr[i];
				g++;
				i++;
			}
		}
		//왼쪽 모두 사용
		else
		{
			for (int k = j; k <= end; k++)
			{
				result_arr[g] = origin_arr[j];
				g++;
				j++;
			}
		}
		//두개의 블록 모두 합치기 완료한 경우
		memcpy(origin_arr + start, result_arr + start, sizeof(int)*(end - start + 1));
		return result_arr;
	}
}