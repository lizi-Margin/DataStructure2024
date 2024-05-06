#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;
int n;
char p[1000005];
class AC
{
public:
	int trie[500010][26];  //AC自动机需要的搜索树结构
	int fail[500010];      //fail指针
	int mark[500010];      //词典结束标志
	int cnt;               //节点序号
	queue<int>q;		   //建立fail指针时需要的队列
	void initial()         //初始化
	{
		cnt = 0;
		memset(trie, 0, sizeof(trie));
		memset(fail, 0, sizeof(fail));
		memset(mark, 0, sizeof(mark));
		while (!q.empty()) q.pop();
	}
	void insert(char *s)   //添加模板单词
	{
		int i;
		int len = strlen(s);
		int now = 0;       //当前节点
		for (i = 0; i < len; i++)
		{
			int v = s[i] - 'a';
			if (trie[now][v] == 0) 
			{
				cnt++;
				trie[now][v] = cnt;
			}
			now = trie[now][v];
		}
		mark[now]++;
	}
	void build()
	{
		int i;
		for (i = 0; i < 26; i++)
		{
			if (trie[0][i] != 0)
			{
				fail[trie[0][i]] = 0;
				q.push(trie[0][i]);
			}
		}
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (i = 0; i < 26; i++)
			{
				if (trie[u][i] != 0)
				{
					fail[trie[u][i]] = trie[fail[u]][i];
					q.push(trie[u][i]);
				}
				else
				{
					trie[u][i] = trie[fail[u]][i];
				}
			}
		}
	}
	int solve(char *s)
	{
		int i, j;
		int len = strlen(s);
		int now = 0;
		int ans = 0;
		for (i = 0; i < len; i++)
		{
			now = trie[now][s[i] - 'a'];
			for (j = now; j && ~mark[j]; j = fail[j])
			{
				ans = ans + mark[j];
				mark[j] = -1;
			}
		}
		return ans;
	}
};
// int main()
// {
//     AC ac; 
// 	int i, j;
// 	scanf("%d", &n);
// 	//AC.initial();
// 	for (i = 1; i <= n; i++)
// 	{
// 		scanf("%s", p);
// 		ac.insert(p);
// 	}
// 	ac.build();
// 	scanf("%s", p);
// 	int ans = ac.solve(p);
// 	cout << ans;
// 	return 0;
// }

