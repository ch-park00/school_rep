#include <iostream>
#include <queue>
using namespace std;
int map[100001];
queue<pair<int,int>> my_queue;
void do_BFS(int src, int dst)
{
	my_queue.push(make_pair(src,0));
	while (!my_queue.empty())
	{
		int cur_idx;
		pair<int,int> cur = my_queue.front();
		my_queue.pop();
		if (cur.first == dst)
		{
			cout << cur.second << endl;
			break;
		}
		if (map[cur.first] == 0)
		{
			cout << cur.first << ", " << cur.second << endl;
			map[cur.first] = cur.second;
			int tmp[2] = { 1,-1 };
			for (int i = 0; i < 3; i++)
			{
				if (i == 2)
				{
					cur_idx = cur.first * 2;
				}
				else
				{
					cur_idx = cur.first + tmp[i];
				}
				if (cur_idx >= 0 && cur_idx <= 100000 && map[cur_idx] < cur.second + 1)
				{
					my_queue.push(make_pair(cur_idx, cur.second + 1));
				}
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int N, K;
	cin >> N >> K;
	do_BFS(N, K);
	return 0;
}