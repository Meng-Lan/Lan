#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 105;
int c[maxn], top[maxn], t, G[maxn][maxn], n, m;
bool dfs(int u) {
	c[u] = -1;
	for (int i = 1; i <= n; i++)
		if (G[u][i]) {
			if (c[i] < 0) return false;
			else if (!c[i] && !dfs(i)) return false;
		}
	c[u] = 1;
	top[--t] = u;
	return true;
}
bool topsort() {
	t = n;
	memset(c, 0, sizeof(c));
	for (int i = 1; i <= n; i++)
		if (!c[i])
			if (!dfs(i))
				return false;
	return true;
}
int main() {
	int u, v;
	while (scanf("%d%d", &n, &m) == 2 && n) {
		memset(G, 0, sizeof(G));
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &u, &v);
			G[u][v] = 1;
		}
		if (topsort()) {
			for (int i = 0; i < n; i++)
				printf("%d ", top[i]);
			putchar('\n');
		}
	}
	return 0;
}