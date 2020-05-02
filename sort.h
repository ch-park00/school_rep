#pragma once
void q_sort(int* data, int p, int L, int R)
{
	int l = L;
	int r = R;
	if (L > R)	return;
	while (1)
	{
		while (1)
		{
			if (data[p] <= data[l] || l >= R)	break;
			l++;
		}
		while (1)
		{
			if (data[p] >= data[r])	break;
			r--;
		}
		if (l < r)
		{
			int temp = data[l];
			data[l] = data[r];
			data[r] = temp;
		}
		else if (l == r)
		{
			int temp = p;
			int tmp = data[temp];
			while (temp < r)
			{
				data[temp] = data[temp + 1];
				data[temp + 1] = tmp;
				temp++;
			}
			q_sort(data, p, p + 1, r - 1);
			q_sort(data, r + 2, r + 3, R);
			return;
		}
		else
		{
			int temp = data[p];
			data[p] = data[r];
			data[r] = temp;
			q_sort(data, p, p + 1, r - 1);
			q_sort(data, l, l + 1, R);
			return;
		}
	}
}
