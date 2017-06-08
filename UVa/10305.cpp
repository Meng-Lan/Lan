#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#define maxn 105
int G[maxn][maxn], c[maxn], topo[maxn], t, n, m;
bool dfs(int u);
bool toposort();
int main() {
	scanf("%d%d", &n, &m);
	int i, u, v;
	for (i = 0; i < m; i++) {
		scanf("%d%d", &u, &v);
		G[u][v] = 1;
	}
	toposort();
	for (int i = 0; i < n; i++)
		printf("%d ", topo[i]);
	return 0;
}
bool toposort() {
	t = n;
	for (int u = 1; u <= n; u++)
		if (!c[u]&&!dfs(u))
			return false;
	return true;
}
bool dfs(int u) {
	c[u] = -1;
	for (int v = 1; v <= n; v++)
		if (G[u][v]) {
			if (c[v] < 0)
				return false;
			if (!c[v] && !dfs(v))
				return false;
		}
	c[u] = 1;
	topo[--t] = u;
	return true;
}