#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<stack>
#include<algorithm>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
#define mp make_pair
const int maxn = 22;
int k, cnt = 0, ans[maxn];
bool vis[maxn];
set<int> G[maxn];

void dfs(int u, int idx) {
	if (u == k) {
		++cnt;
		for (int i = 0; i < idx; i++) {
			if (i) putchar(' ');
			printf("%d", ans[i]);
		}
		putchar('\n');
		return;
	}
	for (auto t : G[u])
		if (!vis[t]) {
			vis[t] = true;
			ans[idx] = t;
			dfs(t, idx + 1);
			vis[t] = false;
		}
}

int main() {
	int kase = 0;
	while (scanf("%d", &k) == 1 && k) {
		cnt = 0;
		memset(vis, 0, sizeof(vis));
		for (auto &t : G) t.clear();
		int u, v;
		while (scanf("%d%d", &u, &v) == 2 && u&&v) {
			G[u].insert(v); G[v].insert(u);
		}
		printf("CASE %d:\n", ++kase);
		bool ok = false;
		queue<int> q; q.push(1); vis[1] = true;
		while (!q.empty()) {
			u = q.front(); q.pop();
			if (u == k) {
				ok = true; break;
			}
			for (auto t : G[u])
				if (!vis[t]) {
					vis[t] = true;
					q.push(t);
				}
		}
		memset(vis, 0, sizeof(vis));
		if (ok) {
			ans[0] = 1; vis[1] = true;
			dfs(1, 1);
		}
		printf("There are %d routes from the firestation to streetcorner %d.\n", cnt, k);
	}
	return 0;
}