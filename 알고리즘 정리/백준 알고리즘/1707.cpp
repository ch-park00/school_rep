#include <iostream>
#include <stack>
#include <vector>

using namespace std;
vector<vector<int>> graph;
stack<int> my_stack;
int* found;

bool do_DFS(int start_ver)
{
	my_stack.push(start_ver);
	while (1)
	{
		if (my_stack.empty())
		{
			int tmp = 0;
			for (int i=0;i<graph.size();i++)
			{
				if (found[i] == 0)
				{
					tmp = i;
					break;
				}
			}
			if (tmp==0)			break;
			else
			{
				my_stack.push(tmp + 1);
				continue;
			}
		}
		int cur_ver = my_stack.top();
		my_stack.pop();
		if (found[cur_ver - 1] == 0)
		{
			int tmp=0;
			for (int k = 1; k < graph[cur_ver - 1].size(); k++)
			{
				int sss = graph[cur_ver - 1][k];
				int sss1 = found[graph[cur_ver - 1][k] - 1];
				if (found[graph[cur_ver - 1][k] - 1] == 0)
				{
					my_stack.push(graph[cur_ver - 1][k]);
				}
				else
				{
					if (found[graph[cur_ver - 1][k] - 1] != 0)
					{
						if (tmp == 0)
						{
							tmp += found[graph[cur_ver - 1][k] - 1];
						}
						else
						{
							if (tmp != found[graph[cur_ver - 1][k] - 1])
							{
								tmp += found[graph[cur_ver - 1][k] - 1];
							}
						}
						if (tmp > 2)
						{
							while (!my_stack.empty())   my_stack.pop();
							return false;
						}
					}
				}
			}
			if (tmp == 1)			found[cur_ver - 1] = 2;
			else found[cur_ver - 1] = 1;
		}
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int K;
	cin >> K;
	for (int k = 0; k < K; k++)
	{
		int V, E;
		cin >> V >> E;
		for (int i = 0; i < V; i++)
		{
			graph.push_back({ i + 1 });
		}
		for (int e = 0; e < E; e++)
		{
			int src, dst;
			cin >> src >> dst;
			graph[src - 1].push_back({ dst });
			graph[dst - 1].push_back({ src });
		}
		found = (int*)calloc(V, sizeof(int));
		bool result = do_DFS(1);
		if (result == true)   cout << "YES" << endl;
		else cout << "NO" << endl;
		free(found);
		for (int i = 0; i < V; i++)
		{
			graph[i].clear();
		}
		graph.clear();
	}
	return 0;
}